/* Copyright (c) 2003-2004 Tapwave, Inc. All rights reserved. */

#ifndef __twSec_H__
#define __twSec_H__

#include <TwTraps.h>

#ifdef __cplusplus
extern "C" {
#endif

// Version of the Security API
#define twSecVersion  1

// Opaque security data structures
#define twSecHardwareIdSize 128
#define twSecPublicKeySize 162
#define twSecSignatureSize 128

typedef struct TwSecHardwareIdTag {
    UInt8 data[twSecHardwareIdSize];
} TwSecHardwareIdType;

typedef struct TwSecSignatureTag {
    UInt8 data[twSecSignatureSize];
} TwSecSignatureType;

typedef struct TwSecPublicKeyTag {
    UInt8 data[twSecPublicKeySize];
} TwSecPublicKeyType;

// Organization of keys by number
#define twSecSystemKey 0xFFFF
#define twSecFixedKeyBase 0
#define twSecNumFixedKeys 14

// Types of locking information (these are bits in a 8bit field)
#define twSecDevice     (1 << 0)
#define twSecCard       (1 << 1)

// Options for failureAction
#define twSecReturnOnFail   0
#define twSecResetOnFail    (1 << 0)

// Reset codes
// carefully chosen so endianness doesn't matter
#define twResetReasonFirstBoot          0x00000000
#define twResetReasonUser               0x01010101
#define twResetReasonErrMgr             0x02020202
#define twResetReasonInvalidOS          0x03030303
#define twResetReasonUnsignedAPIAccess  0x04040404
#define twResetReasonInvalidAppSig      0x05050505
#define twResetReasonInvalidCodeSig     0x06060606
#define twResetReasonInvalidReqHwrSig   0x07070707
#define twResetReasonInvalidOptHwrSig   0x08080808
#define twResetReasonPointerNotOwned	0x09090909
#define twResetReasonFailedDevCheck		0x0A0A0A0A
#define twResetReasonWatchdogTimer      0x0B0B0B0B
#define twResetReasonErrorDuringReset   0x0C0C0C0C
#define twResetReasonReportInProgress   0xFFFFFFFF

// Security function table

#if CPU_TYPE == CPU_68K

typedef struct TwSecTableTag {
    Int32 version;

    Err (*TwSecGetPublicKey) (TwSecPublicKeyType *publicKey, Int32 keyNumber);

    Err (*TwSecGetHardwareId) (TwSecHardwareIdType *hardwareId, UInt8 hardwareInfoType, Int16 slotNum);

    Boolean (*TwSecVerifyDatabase)(UInt16 cardNo, LocalID dbId, UInt32 *failureReason, UInt32 failureAction);

    Boolean (*TwSecVerifyCurrentApp)(UInt32 *failureReason, UInt32 failureAction);

    Boolean (*TwSecVerifyMemory)(const UInt8 *mem, UInt32 memSize, const TwSecPublicKeyType *key, const TwSecSignatureType *sig, UInt32 *failureReason, UInt32 failureAction); 

    void (*TwSecFailureReset)(const char *filename, UInt32 reason, const char *message);

    Boolean (*TwSecVerifyDatabaseWithKey)(UInt16 cardNo, LocalID dbId, const TwSecPublicKeyType *key, UInt32 *failureReason, UInt32 failureAction);

    Boolean (*TwSecVerifyPointerOwnership)(UInt16 cardNo, LocalID dbId, const TwSecPublicKeyType *key, const void *ptr, UInt32 *failureReason, UInt32 failureAction);
} TwSecTableType;

#else // CPU_TYPE != CPU_68K

typedef struct TwSecTableTag {
    Int32 version;

    Err (*TwSecGetPublicKey) (TwSecPublicKeyType *publicKey, Int32 keyNumber);

    Err (*TwSecGetHardwareId) (TwSecHardwareIdType *hardwareId, UInt8 hardwareInfoType, Int16 slotNum);

    Boolean (*TwSecVerifyDatabase)(MemHandle dbH, UInt32 *failureReason, UInt32 failureAction);

    Boolean (*TwSecVerifyCurrentApp)(UInt32 *failureReason, UInt32 failureAction);

    Boolean (*TwSecVerifyMemory)(const UInt8 *mem, UInt32 memSize, const TwSecPublicKeyType *key, const TwSecSignatureType *sig, UInt32 *failureReason, UInt32 failureAction); 

    void (*TwSecFailureReset)(const char *filename, UInt32 reason, const char *message);

    Boolean (*TwSecVerifyDatabaseWithKey)(MemHandle dbH, const TwSecPublicKeyType *key, UInt32 *failureReason, UInt32 failureAction);

    Boolean (*TwSecVerifyPointerOwnership)(MemHandle dbH, const TwSecPublicKeyType *key, const void *ptr, UInt32 *failureReason, UInt32 failureAction);
} TwSecTableType;

#endif // CPU_TYPE == CPU_68K

#define ROM_HI 0xFFFFFFFF
#define ROM_LO 0x00000001

const TwSecTableType *TwSecGetFunctions(Int32 version, TwSecSignatureType *codeSignature, UInt8 **codeStart, UInt32 *codeSize)
    TAL_TRAP(trapTwSecGetFunctions);

inline Err TwSecGetPublicKey(TwSecPublicKeyType *publicKey, Int32 keyNumber)
{
    const TwSecTableType *tableP = TwSecGetFunctions(twSecVersion, 0, 0, 0);
    Err result;

    if ((UInt32)(tableP) > ROM_HI || (UInt32)(tableP) < ROM_LO)
        goto Invalid;
    if ((UInt32)(tableP->TwSecGetPublicKey) > ROM_HI || (UInt32)(tableP->TwSecGetPublicKey) < ROM_LO)
        goto Invalid;

    result = (*(tableP->TwSecGetPublicKey))(publicKey, keyNumber);
    return result;

Invalid:
    ErrFatalDisplay("Invalid public key source.");
    return sysErrNotAllowed;
}


#ifdef __cplusplus
}
#endif

#endif /* __twSec_H__ */

/*
 * Local variables:
 * c-basic-offset: 4
 * c-indentation-style: bsd
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
 */
