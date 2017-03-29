/* Copyright (c) 2002-2003, Tapwave, Inc. All rights reserved. */

#ifndef __TAPWAVEGLUE_H__
#define __TAPWAVEGLUE_H__

#ifndef TAPWAVEGLUE_INTERNAL

/*
 * The following statement is a special compile-time assertion that is
 * used to enforce the sizeof(eventEnums) == 2. Since the sizeof(enum)
 * depends on compiler and compiler options, we have to use
 * alternative way to define eventsEnums, here is a possible solution:
 *
 *      typedef Int16 eventsEnums;
 */
typedef int _twassert_[sizeof(eventsEnum) == 2 ? 1 : -1];

/*
 * This trick prevents include of <winsock.h>. --hz 12/02/2003
 */
#define _MSWSOCK_
#define _WINSOCKAPI_
#define _WINSOCK2API_

#include <TwMidi.h>
#include <poll.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
 * Prototype for Tapwave Native Application entrypoint.
 */
struct TwGlue
{
    Boolean             (*DbgBreak_)(void);
    void                (*DbgMessage_)(const Char *aStr);

    Err                 (*DmArchiveRecord_)(DmOpenRef dbP, UInt16 index);
    Err                 (*DmAttachRecord_)(DmOpenRef dbP, UInt16 *atP, MemHandle newH, MemHandle *oldHP);
    Err                 (*DmAttachResource_)(DmOpenRef dbP, MemHandle newH, DmResType resType, DmResID resID);
    Err                 (*DmCloseDatabase_)(DmOpenRef dbP);
    Err                 (*DmCreateDatabase_)(const Char *nameP, UInt32 creator, UInt32 type, Boolean resDB);
    Err                 (*DmCreateDatabaseFromImage_)(MemPtr bufferP);
    Err                 (*DmDatabaseInfo_)(MemHandle dbH, Char *nameP, UInt16 *attributesP, UInt16 *versionP, UInt32 *crDateP, UInt32 * modDateP, UInt32 *bckUpDateP, UInt32 * modNumP, MemHandle *appInfoHP, MemHandle *sortInfoHP, UInt32 *typeP, UInt32 *creatorP);
    Err                 (*DmDatabaseSize_)(MemHandle dbH, UInt32 *numRecordsP, UInt32 * totalBytesP, UInt32 *dataBytesP);
    Err                 (*DmDeleteDatabase_)(MemHandle dbH);
    Err                 (*DmDeleteRecord_)(DmOpenRef dbP, UInt16 index);
    Err                 (*DmDetachRecord_)(DmOpenRef dbP, UInt16 index, MemHandle *oldHP);
    Err                 (*DmDetachResource_)(DmOpenRef dbP, UInt16 index, MemHandle *oldHP);
    MemHandle           (*DmFindDatabase_)(const Char *nameP);
    Err                 (*DmFindRecordByID_)(DmOpenRef dbP, UInt32 uniqueID, UInt16 *indexP);
    UInt16              (*DmFindResource_)(DmOpenRef dbP, DmResType resType, DmResID resID, MemHandle resH);
    UInt16              (*DmFindResourceType_)(DmOpenRef dbP, DmResType resType, UInt16 typeIndex);
    UInt16              (*DmFindSortPosition_)(DmOpenRef dbP, void *newRecord, SortRecordInfoType *newRecordInfo, DmComparF *compar, Int16 other);
    MemHandle           (*DmGet1Resource_)(DmResType type, DmResID resID);
    MemHandle           (*DmGetAppInfoH_)(DmOpenRef dbP);
    MemHandle           (*DmGetDatabase_)(UInt16 index);
    Err                 (*DmGetLastErr_)(void);
    Err                 (*DmGetNextDatabaseByTypeCreator_)(Boolean newSearch, DmSearchStateType *stateInfoP, UInt32 type, UInt32 creator, Boolean onlyLatestVers, MemHandle *dbP);
    MemHandle           (*DmGetRecord_)(DmOpenRef dbP, UInt16 index);
    MemHandle           (*DmGetResource_)(DmResType type, DmResID resID);
    MemHandle           (*DmGetResourceIndex_)(DmOpenRef dbP, UInt16 index);
    Err                 (*DmInsertionSort_)(DmOpenRef dbR, DmComparF *compar, Int16 other);
    Err                 (*DmMoveCategory_)(DmOpenRef dbP, UInt16 toCategory, UInt16 fromCategory, Boolean dirty);
    Err                 (*DmMoveRecord_)(DmOpenRef dbP, UInt16 from, UInt16 to);
    MemHandle           (*DmNewHandle_)(DmOpenRef dbP, UInt32 size);
    MemHandle           (*DmNewRecord_)(DmOpenRef dbP, UInt16 *atP, UInt32 size);
    MemHandle           (*DmNewResource_)(DmOpenRef dbP, DmResType resType, DmResID resID, UInt32 size);
    UInt16              (*DmNumDatabases_)(void);
    UInt16              (*DmNumRecords_)(DmOpenRef dbP);
    UInt16              (*DmNumRecordsInCategory_)(DmOpenRef dbP, UInt16 category);
    UInt16              (*DmNumResources_)(DmOpenRef dbP);
    DmOpenRef           (*DmOpenDatabase_)(MemHandle dbH, UInt16 mode);
    DmOpenRef           (*DmOpenDatabaseByTypeCreator_)(UInt32 type, UInt32 creator, UInt16 mode);
    Err                 (*DmOpenDatabaseInfo_)(DmOpenRef dbP, MemHandle *dbHP, UInt16 *openCountP, UInt16 *modeP, Boolean *resDBP);
    UInt16              (*DmPositionInCategory_)(DmOpenRef dbP, UInt16 index, UInt16 category);
    MemHandle           (*DmQueryNextInCategory_)(DmOpenRef dbP, UInt16 *indexP, UInt16 category);
    MemHandle           (*DmQueryRecord_)(DmOpenRef dbP, UInt16 index);
    Err                 (*DmQuickSort_)(DmOpenRef dbP, DmComparF *compar, Int16 other);
    Err                 (*DmRecordInfo_)(DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP, MemHandle *chunkHP);
    Err                 (*DmReleaseRecord_)(DmOpenRef dbP, UInt16 index, Boolean dirty);
    Err                 (*DmReleaseResource_)(MemHandle resourceH);
    Err                 (*DmRemoveRecord_)(DmOpenRef dbP, UInt16 index);
    Err                 (*DmRemoveResource_)(DmOpenRef dbP, UInt16 index);
    Err                 (*DmRemoveSecretRecords_)(DmOpenRef dbP);
    Err                 (*DmResetRecordStates_)(DmOpenRef dbP);
    MemHandle           (*DmResizeRecord_)(DmOpenRef dbP, UInt16 index, UInt32 newSize);
    MemHandle           (*DmResizeResource_)(MemHandle resourceH, UInt32 newSize);
    Err                 (*DmResourceInfo_)(DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP, MemHandle *chunkHP);
    UInt16              (*DmSearchRecord_)(MemHandle recH, DmOpenRef *dbPP);
    UInt16              (*DmSearchResource_)(DmResType resType, DmResID resID, MemHandle resH, DmOpenRef *dbPP);
    Err                 (*DmSeekRecordInCategory_)(DmOpenRef dbP, UInt16 *indexP, UInt16 offset, Int16 direction, UInt16 category);
    Err                 (*DmSet_)(void *recordP, UInt32 offset, UInt32 bytes, UInt8 value);
    Err                 (*DmSetDatabaseInfo_)(MemHandle dbH, const Char *nameP, UInt16 *attributesP, UInt16 *versionP, UInt32 *crDateP, UInt32 * modDateP, UInt32 *bckUpDateP, UInt32 * modNumP, MemHandle *appInfoHP, MemHandle *sortInfoHP, UInt32 *typeP, UInt32 *creatorP);
    Err                 (*DmSetRecordInfo_)(DmOpenRef dbP, UInt16 index, UInt16 *attrP, UInt32 *uniqueIDP);
    Err                 (*DmSetResourceInfo_)(DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP);
    Err                 (*DmStrCopy_)(void *recordP, UInt32 offset, const Char *srcP);
    Err                 (*DmWrite_)(void *recordP, UInt32 offset, const void *srcP, UInt32 bytes);
    Err                 (*DmWriteCheck_)(void *recordP, UInt32 offset, UInt32 bytes);

    void                (*ErrDisplayFileLineMsg_)(const Char* filename, UInt16 lineNo, const Char* msg);

    void                (*EvtAddEventToQueue_)(const EventType *event);
    Err                 (*EvtDequeuePenPoint_)(PointType *retP);
    Boolean             (*EvtEventAvail_)(void);
    void                (*EvtGetEvent_)(EventType *event, Int32 timeout);
    void                (*EvtGetPen_)(Int16 *x, Int16 *y, Boolean *down);
    Err                 (*EvtResetAutoOffTimer_)(void);
    Err                 (*EvtSetAutoOffTimer_)(EvtSetAutoOffCmd cmd, UInt16 timeout);

    Err                 (*ExgConnect_)(ExgSocketType *socketP);
    Err                 (*ExgPut_)(ExgSocketType *socketP);
    Err                 (*ExgGet_)(ExgSocketType *socketP);
    Err                 (*ExgAccept_)(ExgSocketType *socketP);
    Err                 (*ExgDisconnect_)(ExgSocketType *socketP, Err error);
    UInt32              (*ExgSend_)(ExgSocketType *socketP, const void * const bufP, UInt32 bufLen, Err *err);
    UInt32              (*ExgReceive_)(ExgSocketType *socketP, void *bufP, UInt32 bufLen, Err *err);
    Err                 (*ExgControl_)(ExgSocketType *socketP, UInt16 op, void *valueP, UInt16 *valueLenP);
    Err                 (*ExgRegisterData_)(UInt32 creatorID, UInt16 id, const Char *dataTypesP);
    Err                 (*ExgRegisterDatatype_)(UInt32 creatorID, UInt16 id, const Char *dataTypesP, const Char *descriptionsP, UInt16 flags);
    Err                 (*ExgNotifyReceive_)(ExgSocketType *socketP, UInt16 flags);
    Err                 (*ExgNotifyGoto_)(ExgSocketType *socketP, UInt16 flags);
    Err                 (*ExgDBRead_)(ExgDBReadProcPtr readProcP, ExgDBDeleteProcPtr deleteProcP, void* userDataP, MemHandle* dbHP, Boolean* needResetP, Boolean keepDates);
    Err                 (*ExgDBWrite_)(ExgDBWriteProcPtr writeProcP, void* userDataP, const char* nameP, MemHandle dbH);
    Boolean             (*ExgDoDialog_)(ExgSocketType *socketP, ExgDialogInfoType *infoP, Err *errP);
    Err                 (*ExgRequest_)(ExgSocketType *socketP);
    Err                 (*ExgSetDefaultApplication_)(UInt32 creatorID, UInt16 id, const Char *dataTypeP);
    Err                 (*ExgGetDefaultApplication_)(UInt32 *creatorIDP, UInt16 id, const Char *dataTypeP);
    Err                 (*ExgGetTargetApplication_)(ExgSocketType *socketP, Boolean unwrap, UInt32 *creatorIDP, Char *descriptionP, UInt32 descriptionSize);
    Err                 (*ExgGetRegisteredApplications_)(UInt32 **creatorIDsP, UInt32 *numAppsP, Char **namesP, Char **descriptionsP, UInt16 id, const Char *dataTypeP);
    Err                 (*ExgGetRegisteredTypes_)(Char **dataTypesP, UInt32 *sizeP, UInt16 id);
    Err                 (*ExgNotifyPreview_)(ExgPreviewInfoType *infoP);

    Err                 (*ExpCardInfo_)(UInt16 slotRefNum, ExpCardInfoType *infoP);
    Err                 (*ExpCardInserted_)(UInt16 slotRefNum);
    Err                 (*ExpCardPresent_)(UInt16 slotRefNum);
    Err                 (*ExpCardRemoved_)(UInt16 slotRefNum);
    Err                 (*ExpSlotEnumerate_)(UInt16 *slotRefNumP, UInt32 *slotIteratorP);

    Int16               (*FntAverageCharWidth_)(void);
    Int16               (*FntBaseLine_)(void);
    Int16               (*FntCharHeight_)(void);
    Int16               (*FntCharWidth_)(Char ch);
    void                (*FntCharsInWidth_)(Char const *string, Int16 *stringWidthP, Int16 *stringLengthP, Boolean *fitWithinWidth);
    Int16               (*FntCharsWidth_)(Char const *chars, Int16 len);
    Err                 (*FntDefineFont_)(FontID font, FontType *fontP);
    Int16               (*FntDescenderHeight_)(void);
    FontID              (*FntGetFont_)(void);
    FontType *          (*FntGetFontPtr_)(void);
    void                (*FntGetScrollValues_)(Char const *chars, UInt16 width, UInt16 scrollPos, UInt16 *linesP, UInt16 *topLine);
    Int16               (*FntLineHeight_)(void);
    Int16               (*FntLineWidth_)(Char const *pChars, UInt16 length);
    FontID              (*FntSetFont_)(FontID font);
    Int16               (*FntWCharWidth_)(WChar iChar);
    Int16               (*FntWidthToOffset_)(Char const *pChars, UInt16 length, Int16 pixelWidth, Boolean *leadingEdge, Int16 *truncWidth);
    UInt16              (*FntWordWrap_)(Char const *chars, UInt16 maxWidth);
    void                (*FntWordWrapReverseNLines_)(Char const *const chars, UInt16 maxWidth, UInt16 *linesToScrollP, UInt16 *scrollPosP);

    Boolean             (*FrmDispatchEvent_)(EventType *event);
    Boolean             (*MenuHandleEvent_)(EventType *event);

    Err                 (*FtrGet_)(UInt32 creator, UInt16 featureNum, UInt32 *valueP);
    Err                 (*FtrPtrFree_)(UInt32 creator, UInt16 featureNum);
    Err                 (*FtrPtrNew_)(UInt32 creator, UInt16 featureNum, UInt32 size, void **newPtrP);
    Err                 (*FtrPtrResize_)(UInt32 creator, UInt16 featureNum, UInt32 newSize, void **newPtrP);
    Err                 (*FtrSet_)(UInt32 creator, UInt16 featureNum, UInt32 newValue);
    Err                 (*FtrUnregister_)(UInt32 creator, UInt16 featureNum);

    UInt32              (*KeyCurrentState_)(void);
    UInt32              (*KeySetMask_)(UInt32 keyMask);

    Int16               (*MemCmp_)(const void *s1, const void *s2, Int32 numBytes);
    Err                 (*MemMove_)(void *dstP, const void *sP, Int32 numBytes);
    Err                 (*MemSet_)(void *dstP, Int32 numBytes, UInt8 value);

    Err                 (*MemHandleFree_)(MemHandle h);
    MemPtr              (*MemHandleLock_)(MemHandle h);
    MemHandle           (*MemHandleNew_)(UInt32 size);
    Err                 (*MemHandleResize_)(MemHandle h, UInt32 newSize);
    UInt32              (*MemHandleSize_)(MemHandle h);
    Err                 (*MemHandleUnlock_)(MemHandle h);

    Err                 (*MemPtrFree_)(MemPtr ptr);
    MemPtr              (*MemPtrNew_)(UInt32 size) ;
    Err                 (*MemPtrResize_)(MemPtr p, UInt32 newSize);
    UInt32              (*MemPtrSize_)(MemPtr p);

    Int16               (*PrefGetAppPreferences_)(UInt32 creator, UInt16 id, void *prefs, UInt16 *prefsSize, Boolean saved);
    UInt32              (*PrefGetPreference_)(SystemPreferencesChoice choice);
    void                (*PrefSetAppPreferences_)(UInt32 creator, UInt16 id, Int16 version, const void *prefs, UInt16 prefsSize, Boolean saved);
    void                (*PrefSetPreference_)(SystemPreferencesChoice choice, UInt32 value);

    void                (*SndSetDefaultVolume_)(UInt16 *alarmAmpP, UInt16 *sysAmpP, UInt16 *defAmpP);
    void                (*SndGetDefaultVolume_)(UInt16 *alarmAmpP, UInt16 *sysAmpP, UInt16 *masterAmpP);

    Err                 (*SndPlayResource_)(SndPtr sndP, Int32 volume, UInt32 flags);

    Err                 (*SndStreamCreate_)(SndStreamRef *channel, SndStreamMode mode, UInt32 samplerate, SndSampleType type, SndStreamWidth width, SndStreamBufferCallback func, void *userdata, UInt32 buffsize); 
    Err                 (*SndStreamDelete_)(SndStreamRef channel);
    Err                 (*SndStreamGetPan_)(SndStreamRef channel, Int32 *panposition);
    Err                 (*SndStreamGetVolume_)(SndStreamRef channel, Int32 *volume);
    Err                 (*SndStreamPause_)(SndStreamRef channel, Boolean pause);
    Err                 (*SndStreamSetPan_)(SndStreamRef channel, Int32 panposition);
    Err                 (*SndStreamSetVolume_)(SndStreamRef channel, Int32 volume);
    Err                 (*SndStreamStart_)(SndStreamRef channel);
    Err                 (*SndStreamStop_)(SndStreamRef channel);

    Boolean             (*SysHandleEvent_)(EventType *event);

    Err                 (*SysNotifyBroadcast_)(SysNotifyParamType *notify);
    Err                 (*SysNotifyBroadcastDeferred_)(SysNotifyParamType *notify, Int16 paramSize);
    Err                 (*SysNotifyRegister_)(MemHandle dbH, UInt32 notifyType, SysNotifyProcPtr callbackP, Int8 priority, void *userData);
    Err                 (*SysNotifyUnregister_)(MemHandle dbH, UInt32 notifyType, Int8 priority);

    Err                 (*SysTaskDelay_)(UInt32 delay);

    Err                 (*SysUIAppSwitch_)(MemHandle dbH, UInt16 cmd, MemPtr cmdPBP);

    Int32               (*TimGetSeconds_)(void);
    Int32               (*TimGetTicks_)(void);

    Char*               (*StrCopy_)(Char *dst, const Char *src);
    Char*               (*StrNCopy_)(Char *dst, const Char *src, Int16 n);
    Char*               (*StrCat_)(Char *dst, const Char *src);
    Char*               (*StrNCat_)(Char *dst, const Char *src, Int16 n);
    UInt16              (*StrLen_)(const Char *src);
    Int16               (*StrCompareAscii_)(const Char *s1, const Char *s2);
    Int16               (*StrCompare_)(const Char *s1, const Char *s2);
    Int16               (*StrNCompareAscii_)(const Char *s1, const Char *s2, Int32 n);
    Int16               (*StrNCompare_)(const Char *s1, const Char *s2, Int32 n);
    Int16               (*StrCaselessCompare_)(const Char *s1, const Char *s2);
    Int16               (*StrNCaselessCompare_)(const Char *s1, const Char *s2, Int32 n);
    Char*               (*StrToLower_)(Char *dst, const Char *src);
    Char*               (*StrIToA_)(Char *s, Int32 i);
    Char*               (*StrIToH_)(Char *s, UInt32 i);
    Char*               (*StrLocalizeNumber_)(Char *s, Char thousandSeparator, Char decimalSeparator);
    Char*               (*StrDelocalizeNumber_)(Char *s, Char thousandSeparator, Char decimalSeparator);
    Char*               (*StrChr_)(const Char *str, WChar chr);
    Char*               (*StrStr_)(const Char *str, const Char *token);
    Int32               (*StrAToI_)(const Char *str);
    Int16               (*StrPrintF_)(Char *s, const Char *formatStr, ...);
    Int16               (*StrVPrintF_)(Char *s, const Char *formatStr, _Palm_va_list arg);

    UInt8               (*TxtByteAttr_)(UInt8 inByte);
    Int16               (*TxtCaselessCompare_)(const Char *s1, UInt16 s1Len, UInt16 *s1MatchLen, const Char *s2, UInt16 s2Len, UInt16 *s2MatchLen);
    UInt16              (*TxtCharAttr_)(WChar inChar);
    WChar               (*TxtCharBounds_)(const Char *inText, UInt32 inOffset, UInt32 *outStart, UInt32 *outEnd);
    CharEncodingType    (*TxtCharEncoding_)(WChar inChar);
    Boolean             (*TxtCharIsValid_)(WChar inChar);
    UInt16              (*TxtCharSize_)(WChar inChar);
    Int16               (*TxtCharWidth_)(WChar inChar);
    UInt16              (*TxtCharXAttr_)(WChar inChar);
    Int16               (*TxtCompare_)(const Char *s1, UInt16 s1Len, UInt16 *s1MatchLen, const Char *s2, UInt16 s2Len, UInt16 *s2MatchLen);
    Err                 (*TxtConvertEncoding_)(Boolean newConversion, TxtConvertStateType *ioStateP, const Char* srcTextP, UInt16* ioSrcBytes, CharEncodingType srcEncoding, Char* dstTextP, UInt16* ioDstBytes, CharEncodingType dstEncoding, const Char* substitutionStr, UInt16 substitutionLen);
    Char*               (*TxtEncodingName_)(CharEncodingType inEncoding);
    Boolean             (*TxtFindString_)(const Char *inSourceStr, const Char *inTargetStr, UInt32 *outPos, UInt16 *outLength);
    WChar               (*TxtGetChar_)(const Char *inText, UInt32 inOffset);
    UInt16              (*TxtGetNextChar_)(const Char *inText, UInt32 inOffset, WChar *outChar);
    UInt16              (*TxtGetPreviousChar_)(const Char *inText, UInt32 inOffset, WChar *outChar);
    UInt32              (*TxtGetTruncationOffset_)(const Char *inText, UInt32 inOffset);
    UInt32              (*TxtGetWordWrapOffset_)(const Char *iTextP, UInt32 iOffset);
    CharEncodingType    (*TxtMaxEncoding_)(CharEncodingType a, CharEncodingType b);
    CharEncodingType    (*TxtNameToEncoding_)(const Char* iEncodingName);
    Char*               (*TxtParamString_)(const Char *inTemplate, const Char *param0, const Char *param1, const Char *param2, const Char *param3);
    UInt16              (*TxtReplaceStr_)(Char *ioStr, UInt16 inMaxLen, const Char *inParamStr, UInt16 inParamNum);
    UInt16              (*TxtSetNextChar_)(Char *ioText, UInt32 inOffset, WChar inChar);
    CharEncodingType    (*TxtStrEncoding_)(const Char *inStr);
    Err                 (*TxtTransliterate_)(const Char *inSrcText, UInt16 inSrcLength, Char *outDstText, UInt16 *ioDstLength, TranslitOpType inOp);
    Boolean             (*TxtWordBounds_)(const Char *inText, UInt32 inLength, UInt32 inOffset, UInt32 *outStart, UInt32 *outEnd);

    Err                 (*VFSCustomControl_)(UInt32 fsCreator, UInt32 apiCreator, UInt16 apiSelector, void *valueP, UInt16 *valueLenP);
    Err                 (*VFSDirCreate_)(UInt16 volRefNum, const Char *dirNameP);
    Err                 (*VFSDirEntryEnumerate_)(FileRef dirRef, UInt32 *dirEntryIteratorP, FileInfoType *infoP);
    Err                 (*VFSExportDatabaseToFile_)(UInt16 volRefNum, const Char *pathNameP, MemHandle dbH);
    Err                 (*VFSExportDatabaseToFileCustom_)(UInt16 volRefNum, const Char *pathNameP, MemHandle dbH, VFSExportProcPtr exportProcP, void *userDataP);
    Err                 (*VFSFileClose_)(FileRef fileRef);
    Err                 (*VFSFileCreate_)(UInt16 volRefNum, const Char *pathNameP);
    Err                 (*VFSFileDelete_)(UInt16 volRefNum, const Char *pathNameP);
    Err                 (*VFSFileEOF_)(FileRef fileRef);
    Err                 (*VFSFileGetAttributes_)(FileRef fileRef, UInt32 *attributesP);
    Err                 (*VFSFileGetDate_)(FileRef fileRef, UInt16 whichDate, UInt32 *dateP);
    Err                 (*VFSFileOpen_)(UInt16 volRefNum, const Char *pathNameP, UInt16 openMode, FileRef *fileRefP);
    Err                 (*VFSFileRead_)(FileRef fileRef, UInt32 numBytes, void *bufP, UInt32 *numBytesReadP);
    Err                 (*VFSFileReadData_)(FileRef fileRef, UInt32 numBytes, void *bufBaseP, UInt32 offset, UInt32 *numBytesReadP);
    Err                 (*VFSFileRename_)(UInt16 volRefNum, const Char *pathNameP, const Char *newNameP);
    Err                 (*VFSFileResize_)(FileRef fileRef, UInt32 newSize);
    Err                 (*VFSFileSeek_)(FileRef fileRef, FileOrigin origin, Int32 offset);
    Err                 (*VFSFileSetAttributes_)(FileRef fileRef, UInt32 attributes);
    Err                 (*VFSFileSetDate_)(FileRef fileRef, UInt16 whichDate, UInt32 date);
    Err                 (*VFSFileSize_)(FileRef fileRef, UInt32 *fileSizeP);
    Err                 (*VFSFileTell_)(FileRef fileRef, UInt32 *filePosP);
    Err                 (*VFSFileWrite_)(FileRef fileRef, UInt32 numBytes, const void *dataP, UInt32 *numBytesWrittenP);
    Err                 (*VFSGetDefaultDirectory_)(UInt16 volRefNum, const Char *fileTypeStr, Char *pathStr, UInt16 *bufLenP);
    Err                 (*VFSImportDatabaseFromFile_)(UInt16 volRefNum, const Char *pathNameP, MemHandle *dbHP);
    Err                 (*VFSImportDatabaseFromFileCustom_)(UInt16 volRefNum, const Char *pathNameP, MemHandle *dbHP, VFSImportProcPtr importProcP, void *userDataP);
    Err                 (*VFSInstallFSLib_)(UInt32 creator, UInt16 *fsLibRefNumP);
    Err                 (*VFSRegisterDefaultDirectory_)(const Char *fileTypeStr, UInt32 mediaType, const Char *pathStr);
    Err                 (*VFSRemoveFSLib_)(UInt16 fsLibRefNum);
    Err                 (*VFSUnregisterDefaultDirectory_)(const Char *fileTypeStr, UInt32 mediaType);
    Err                 (*VFSVolumeEnumerate_)(UInt16 *volRefNumP, UInt32 *volIteratorP);
    Err                 (*VFSVolumeFormat_)(UInt8 flags, UInt16 fsLibRefNum, VFSAnyMountParamType *vfsMountParamP);
    Err                 (*VFSVolumeGetLabel_)(UInt16 volRefNum, Char *labelP, UInt16 bufLen);
    Err                 (*VFSVolumeInfo_)(UInt16 volRefNum, VolumeInfoType *volInfoP);
    Err                 (*VFSVolumeMount_)(UInt8 flags, UInt16 fsLibRefNum, VFSAnyMountParamType *vfsMountParamP);
    Err                 (*VFSVolumeSetLabel_)(UInt16 volRefNum, const Char *labelP);
    Err                 (*VFSVolumeSize_)(UInt16 volRefNum, UInt32 *volumeUsedP, UInt32 *volumeTotalP);
    Err                 (*VFSVolumeUnmount_)(UInt16 volRefNum);

    void                (*WinClipRectangle_)(RectangleType *rP);
    void                (*WinCopyRectangle_)(WinHandle srcWin, WinHandle dstWin, const RectangleType *srcRect, Coord destX, Coord destY, WinDrawOperation mode);

    WinHandle           (*WinCreateOffscreenWindow_)(Coord width, Coord height, WindowFormatType format, UInt16 *error);
    WinHandle           (*WinCreateWindow_)(const RectangleType *bounds, FrameType frame, Boolean modal, Boolean focusable, UInt16 *error);
    void                (*WinDeleteWindow_)(WinHandle winHandle, Boolean eraseIt);

    void                (*WinDisableWindow_)(WinHandle winHandle);
    void                (*WinEnableWindow_)(WinHandle winHandle);

    void                (*WinGetBounds_)(WinHandle winH, RectangleType *rP);
    void                (*WinSetBounds_)(WinHandle winH, const RectangleType *rP);

    IndexedColorType    (*WinGetPixel_)(Coord x, Coord y);
    Err                 (*WinGetPixelRGB_)(Coord x, Coord y, RGBColorType *rgpP);

    void                (*WinGetFramesRectangle_)(FrameType frame, const RectangleType *rP, RectangleType *obscuredRect);
    Err                 (*WinGetSupportedDensity_)(UInt16* densityP);
    void                (*WinGetWindowFrameRect_)(WinHandle winHandle, RectangleType *r);

    void                (*WinPaintBitmap_)(BitmapType *bitmapP, Coord x, Coord y);
    void                (*WinPaintChar_)(WChar theChar, Coord x, Coord y);
    void                (*WinPaintChars_)(const Char *chars, Int16 len, Coord x, Coord y);
    void                (*WinPaintLine_)(Coord x1, Coord y1, Coord x2, Coord y2);
    void                (*WinPaintLines_)(UInt16 numLines, WinLineType lines[]);
    void                (*WinPaintPixel_)(Coord x, Coord y);
    void                (*WinPaintPixels_)(UInt16 numPoints, PointType pts[]);
    void                (*WinPaintRectangle_)(const RectangleType *rP, UInt16 cornerDiam);
    void                (*WinPaintRectangleFrame_)(FrameType frame, const RectangleType *rP);
    void                (*WinPaintRoundedRectangleFrame_)(const RectangleType *rP, Coord width, Coord cornerRadius, Coord shadowWidth);

    void                (*WinPushDrawState_)(void);
    void                (*WinPopDrawState_)(void);

    void                (*WinRestoreBits_)(WinHandle winHandle, Coord destX, Coord destY);
    WinHandle           (*WinSaveBits_)(const RectangleType *source, UInt16 *error);

    Err                 (*WinScreenGetAttribute_)(WinScreenAttrType selector, UInt32* attrP);
    Err                 (*WinScreenMode_)(WinScreenModeOperation operation, UInt32 *widthP, UInt32 *heightP, UInt32 *depthP, Boolean *enableColorP);

    UInt8*              (*WinScreenLock_)(WinLockInitType initMode);
    void                (*WinScreenUnlock_)(void);

    void                (*WinScrollRectangle_)(const RectangleType *rP, WinDirectionType direction, Coord distance, RectangleType *vacatedP);

    void                (*WinIndexToRGB_)(IndexedColorType i, RGBColorType *rgbP);
    IndexedColorType    (*WinRGBToIndex_)(const RGBColorType *rgbP);

    WinHandle           (*WinGetDisplayWindow_)(void);

    WinHandle           (*WinGetActiveWindow_)(void);
    void                (*WinSetActiveWindow_)(WinHandle winHandle);

    WinHandle           (*WinGetDrawWindow_)(void);
    WinHandle           (*WinSetDrawWindow_)(WinHandle winHandle);

    void                (*WinGetClip_)(RectangleType *rP);
    void                (*WinSetClip_)(const RectangleType *rP);
    void                (*WinResetClip_)(void);

    UInt16              (*WinGetCoordinateSystem_)(void);
    UInt16              (*WinSetCoordinateSystem_)(UInt16 coordSys);

    void                (*WinSetBackColor_)(IndexedColorType backColor);
    void                (*WinSetBackColorRGB_)(const RGBColorType *newRgbP, RGBColorType *oldRgbP);

    void                (*WinSetForeColor_)(IndexedColorType foreColor);
    void                (*WinSetForeColorRGB_)(const RGBColorType *newRgbP, RGBColorType *oldRgbP);

    void                (*WinSetTextColor_)(IndexedColorType textColor);
    void                (*WinSetTextColorRGB_)(const RGBColorType *newRgbP, RGBColorType * oldRgbP);

    void                (*WinSetDrawMode_)(WinDrawOperation newMode);
    void                (*WinSetUnderlineMode_)(UnderlineModeType mode);

    void                (*WinSetPattern_)(const CustomPatternType *patternP);
    void                (*WinSetPatternType_)(PatternType newPattern);

    Coord               (*WinScaleCoord_)(Coord coord, Boolean ceiling);
    Coord               (*WinUnscaleCoord_)(Coord coord, Boolean ceiling);

    void                (*WinScalePoint_)(PointType *pointP, Boolean ceiling);
    void                (*WinUnscalePoint_)(PointType *pointP, Boolean ceiling);

    void                (*WinScaleRectangle_)(RectangleType *rectP);
    void                (*WinUnscaleRectangle_)(RectangleType *rectP);

    void                (*WinDisplayToWindowPt_)(Coord *extentX, Coord *extentY);
    void                (*WinWindowToDisplayPt_)(Coord *extentX, Coord *extentY);

    void                (*WinGetBitmapDimensions_)(BitmapType *bmP, Coord *widthP, Coord *heightP);

    UInt16              (*PINGetInputAreaState_)(void);
    Err                 (*PINSetInputAreaState_)(UInt16 state);
    UInt16              (*PINGetInputTriggerState_)(void);
    Err                 (*PINSetInputTriggerState_)(UInt16 state);

    Err                 (*StatHide_)(void);
    Err                 (*StatShow_)(void);
    Err                 (*StatGetAttribute_)(UInt16 selector, UInt32* dataP);

    UInt16              (*SysGetOrientation_)(void);
    Err                 (*SysSetOrientation_)(UInt16 orientation);
    UInt16              (*SysGetOrientationTriggerState_)(void);
    Err                 (*SysSetOrientationTriggerState_)(UInt16 state);

    Err                 (*TwInputOpen_)(TwInputHandle* input, const Char* name, const Char* mode);
    Err                 (*TwInputClose_)(TwInputHandle input);
    Err                 (*TwInputActivate_)(TwInputHandle input);
    Err                 (*TwInputDeactivate_)(TwInputHandle input);
    Err                 (*TwInputGetPeriod_)(TwInputHandle input, Int32* millis);
    Err                 (*TwInputSetPeriod_)(TwInputHandle input, Int32 millis);
    Err                 (*TwInputGetCapacity_)(TwInputHandle input, Int32* sizeInEvents);
    Err                 (*TwInputSetCapacity_)(TwInputHandle input, Int32 sizeInEvents);
    Err                 (*TwInputGetFormat_)(TwInputHandle input, Int32* features, Int32* sizeInBytes);
    Err                 (*TwInputSetFormat_)(TwInputHandle input, Int32* features, Int32 sizeInBytes);
    Err                 (*TwInputPeek_)(TwInputHandle input, Int32* event, Int32 sizeInBytes);
    Err                 (*TwInputRead_)(TwInputHandle input, Int32* event, Int32 sizeInBytes);
    Err                 (*TwInputPoll_)(TwInputHandle input, Int32* event, Int32 sizeInBytes);
    Err                 (*TwInputControl_)(TwInputHandle input, Int32 cmd, void* buf, Int32 sizeInBytes);

    Err                 (*TwDeviceOpen_)(TwDeviceHandle* handle, const char* name, const char* mode);
    Err                 (*TwDeviceClose_)(TwDeviceHandle handle);
    Err                 (*TwDeviceRead_)(TwDeviceHandle handle, void* buf, Int32* len);
    Err                 (*TwDeviceWrite_)(TwDeviceHandle handle, const void* buf, Int32* len);
    Err                 (*TwDeviceGetProperty_)(TwDeviceHandle handle, Int32 property, void* buf, Int32* len);
    Err                 (*TwDeviceSetProperty_)(TwDeviceHandle handle, Int32 property, const void* buf, Int32 len);
    Err                 (*TwDeviceControl_)(TwDeviceHandle handle, Int32 cmd, void* buf, Int32 len);

    Err                 (*TwHighScoreRegister_)(UInt32 creatorID, UInt16 scoreType, UInt16 numLocalScoresToKeep, UInt16 numServerScoresToKeep, Boolean reportScoresToServer, Char *gameName);
    Err                 (*TwHighScoreUnregister_)(UInt32 creatorID, UInt16 scoreType);
    Err                 (*TwHighScoreReport_)(UInt32 creatorID, UInt16 scoreType, TwHighScoreType *highScoreP);
    TwHighScoreSummaryType*    (*TwHighScoreGetSummary_)(UInt32 creatorID, UInt16 scoreType);
    TwHighScoreType*    (*TwHighScoreGetDetails_)(UInt32 creatorID, UInt16 scoreType, UInt16 whichPool, UInt16 index);

    Err                 (*TwGfxOpen_)(TwGfxType** aResult, TwGfxInfoType* aInfoResult);
    Err                 (*TwGfxClose_)(TwGfxType* aGfx);
    Err                 (*TwGfxGetInfo_)(TwGfxType* aGfx, TwGfxInfoType* aResult);
    Err                 (*TwGfxGetMemoryUsage_)(TwGfxType* aGfx, Int32 aLocation, Int32* aUsedResult);
    Err                 (*TwGfxGetDisplaySurface_)(TwGfxType* aGfx, TwGfxSurfaceType** aResult);
    Err                 (*TwGfxInVBlank_)(TwGfxType* aGfx, Boolean* aInVBlankResult);
    Err                 (*TwGfxWaitForVBlank_)(TwGfxType* aGfx);
    Err                 (*TwGfxAllocSurface_)(TwGfxType* aGfx, TwGfxSurfaceType** aResult, TwGfxSurfaceInfoType* aDescription);
    Err                 (*TwGfxFreeSurface_)(TwGfxSurfaceType* aSurface);
    Err                 (*TwGfxSetClip_)(TwGfxSurfaceType* aSurface, const TwGfxRectType* aClipRect);
    Err                 (*TwGfxGetClip_)(TwGfxSurfaceType* aSurface, TwGfxRectType* aClipRectResult);
    Err                 (*TwGfxGetSurfaceInfo_)(TwGfxSurfaceType* aSurface, TwGfxSurfaceInfoType* aResult);
    Err                 (*TwGfxLockSurface_)(TwGfxSurfaceType* aSurface, void** aAddressResult);
    Err                 (*TwGfxUnlockSurface_)(TwGfxSurfaceType* aSurface, Boolean aUpdate);
    Err                 (*TwGfxReadSurface_)(TwGfxSurfaceType* aSurface, void* aDest, UInt8 aAsync);
    Err                 (*TwGfxWriteSurface_)(TwGfxSurfaceType* aSurface, const void* aSource, UInt8 aAsync);
    Err                 (*TwGfxIsSurfaceReady_)(TwGfxSurfaceType* aSurface);
    Err                 (*TwGfxBitBlt_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aDestPoint, TwGfxSurfaceType* aSourceSurface, const TwGfxRectType* aSourceRect);
    Err                 (*TwGfxTransformBlt_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aDestPoint, TwGfxSurfaceType* aSourceSurface, const TwGfxRectType* aSourceRect, Int32 aRotationFlags, Int32 aMirrorFlags);
    Err                 (*TwGfxDrawPoints_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aPoints, Int32 aNumberOfPoints, TwGfxPackedRGBType aColor);
    Err                 (*TwGfxDrawColorPoints_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aPoints, Int32 aNumberOfPoints, const TwGfxPackedRGBType* aColors);
    Err                 (*TwGfxDrawLines_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aPoints, Int32 aNumberOfPoints, TwGfxPackedRGBType aColor);
    Err                 (*TwGfxDrawLineSegments_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aPoints, Int32 aNumberOfPoints, TwGfxPackedRGBType aColor);
    Err                 (*TwGfxDrawRect_)(TwGfxSurfaceType* aDestSurface, const TwGfxRectType* aRect, TwGfxPackedRGBType aColor);
    Err                 (*TwGfxFillRect_)(TwGfxSurfaceType* aDestSurface, const TwGfxRectType* aRect, TwGfxPackedRGBType aColor);
    Err                 (*TwGfxDrawSpans_)(TwGfxSurfaceType* aDestSurface, const TwGfxSpanType* aSpans, Int32 aNumberOfSpans, TwGfxPackedRGBType aColor);
    Err                 (*TwGfxDrawBitmap_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aDestPoint, const TwGfxBitmapType* aBitmap);

    Err                 (*TwAppStart_)(Boolean(*AppHandleEvent)(EventType* eventP));
    Err                 (*TwAppStop_)(void);
    Err                 (*TwNextEvent_)(EventType* event, Int32 timeout);

    Err                 (*TwGfxGetPalmDisplaySurface_)(TwGfxType* aGfx, TwGfxSurfaceType** aResult);
    Err                 (*TwGfxReadSurfaceRegion_)(TwGfxSurfaceType* aSurface, const TwGfxRectType* aBounds, void* aDestPixels, UInt32 aDestRowBytes, UInt8 aAsync);
    Err                 (*TwGfxWriteSurfaceRegion_)(TwGfxSurfaceType* aSurface, const TwGfxRectType* aBounds, const void* aSourcePixels, UInt32 aSourceRowBytes, UInt8 aAsync);
    Err                 (*TwGfxAsyncBlt_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aDestPoint, TwGfxSurfaceType* aSourceSurface, const TwGfxRectType* aSourceRect);
    Err                 (*TwGfxTransparentBlt_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aDestPoint, TwGfxSurfaceType* aSourceSurface, const TwGfxRectType* aSourceRect, TwGfxPackedRGBType aTransparentColor);
    Err                 (*TwGfxMaskBlt_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aDestPoint, TwGfxSurfaceType* aSourceSurface, const TwGfxRectType* aSourceRect, const TwGfxBitmapType* aMask);
    Err                 (*TwGfxBlendBlt_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aDestPoint, TwGfxSurfaceType* aSourceSurface, const TwGfxRectType* aSourceRect, TwGfxPackedRGBType aSourceAlpha);
    Err                 (*TwGfxMaskBlendBlt_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aDestPoint, TwGfxSurfaceType* aSourceSurface, const TwGfxRectType* aSourceRect, const TwGfxBitmapType* aAlphaMask);
    Err                 (*TwGfxStretchBlt_)(TwGfxSurfaceType* aDestSurface, const TwGfxRectType* aDestRect, TwGfxSurfaceType* aSourceSurface, const TwGfxRectType* aSourceRect);
    Err                 (*TwGfxTileBlt_)(TwGfxSurfaceType* aDestSurface, const TwGfxRectType* aDestRect, TwGfxSurfaceType* aSourceSurface, const TwGfxPointType* aSourceAlignmentPoint);

    Err                 (*BtLibOpen_)(Boolean allowStackToFail);
    Err                 (*BtLibClose_)(void);
    Err                 (*BtLibHandleEvent_)(void *eventP);

    Err                 (*BtLibRegisterManagementNotification_)(BtLibManagementProcPtr callbackP, UInt32 refCon);
    Err                 (*BtLibUnregisterManagementNotification_)(BtLibManagementProcPtr callbackP);
    Err                 (*BtLibStartInquiry_)(UInt8 timeOut, UInt8 maxResp);
    Err                 (*BtLibCancelInquiry_)(void);
    Err                 (*BtLibDiscoverSingleDevice_)(Char* instructionTxt, BtLibClassOfDeviceType* deviceFilterList, UInt8 deviceFilterListLen, BtLibDeviceAddressType *selectedDeviceP, Boolean addressAsName, Boolean showLastList);
    Err                 (*BtLibDiscoverMultipleDevices_)(Char* instructionTxt, Char* buttonTxt, BtLibClassOfDeviceType* deviceFilterList, UInt8 deviceFilterListLen , UInt8 *numDevicesSelected, Boolean addressAsName, Boolean showLastList);
    Err                 (*BtLibGetSelectedDevices_)(BtLibDeviceAddressType* selectedDeviceArray, UInt8 arraySize, UInt8 *numDevicesReturned);
    Err                 (*BtLibGetRemoteDeviceName_)(BtLibDeviceAddressTypePtr remoteDeviceP, BtLibFriendlyNameType* nameP, BtLibGetNameEnum retrievalMethod);
    Err                 (*BtLibLinkConnect_)(BtLibDeviceAddressTypePtr remoteDeviceP);
    Err                 (*BtLibLinkDisconnect_)(BtLibDeviceAddressTypePtr remoteDeviceP);
    Err                 (*BtLibPiconetCreate_)(Boolean unlockInbound, Boolean discoverable);
    Err                 (*BtLibPiconetDestroy_)(void);
    Err                 (*BtLibPiconetUnlockInbound_)(Boolean discoverable);
    Err                 (*BtLibPiconetLockInbound_)(void);
    Err                 (*BtLibLinkSetState_)(BtLibDeviceAddressTypePtr remoteDeviceP, BtLibLinkPrefsEnum pref, void* linkState, UInt16 linkStateSize);
    Err                 (*BtLibLinkGetState_)(BtLibDeviceAddressTypePtr remoteDeviceP, BtLibLinkPrefsEnum pref, void* linkState, UInt16 linkStateSize);
    Err                 (*BtLibSetGeneralPreference_)(BtLibGeneralPrefEnum pref, void* prefValue, UInt16 prefValueSize);
    Err                 (*BtLibGetGeneralPreference_)(BtLibGeneralPrefEnum pref, void* prefValue, UInt16 prefValueSize);

    Err                 (*BtLibSocketCreate_)(BtLibSocketRef* socketRefP, BtLibSocketProcPtr callbackP, UInt32 refCon,BtLibProtocolEnum socketProtocol);
    Err                 (*BtLibSocketClose_)(BtLibSocketRef socket);
    Err                 (*BtLibSocketListen_)(BtLibSocketRef socket, BtLibSocketListenInfoType *listenInfo);
    Err                 (*BtLibSocketConnect_)(BtLibSocketRef socket, BtLibSocketConnectInfoType* connectInfo);
    Err                 (*BtLibSocketRespondToConnection_)(BtLibSocketRef socket, Boolean accept);
    Err                 (*BtLibSocketSend_)(BtLibSocketRef socket, UInt8 *data, UInt32 dataLen);
    Err                 (*BtLibSocketAdvanceCredit_)(BtLibSocketRef socket, UInt8 credit);
    Err                 (*BtLibSocketGetInfo_)(BtLibSocketRef socket, BtLibSocketInfoEnum infoType, void * valueP, UInt32 valueSize);

    Err                 (*BtLibSdpGetServerChannelByUuid_)(BtLibSocketRef socket, BtLibDeviceAddressType *rDev, BtLibSdpUuidType* serviceUUIDList, UInt8 uuidListLen);
    Err                 (*BtLibSdpGetPsmByUuid_)(BtLibSocketRef socket, BtLibDeviceAddressType *rDev, BtLibSdpUuidType* serviceUUIDList, UInt8 uuidListLen);
    Err                 (*BtLibSdpServiceRecordCreate_)(BtLibSdpRecordHandle* recordH);
    Err                 (*BtLibSdpServiceRecordDestroy_)(BtLibSdpRecordHandle recordH);
    Err                 (*BtLibSdpServiceRecordStartAdvertising_)(BtLibSdpRecordHandle recordH);
    Err                 (*BtLibSdpServiceRecordStopAdvertising_)(BtLibSdpRecordHandle recordH);
    Err                 (*BtLibSdpServiceRecordSetAttributesForSocket_)(BtLibSocketRef socket, BtLibSdpUuidType* serviceUUIDList, UInt8 uuidListLen, const Char* serviceName, UInt16 serviceNameLen, BtLibSdpRecordHandle recordH);
    Err                 (*BtLibSdpServiceRecordsGetByServiceClass_)(BtLibSocketRef socket, BtLibDeviceAddressType *rDev, BtLibSdpUuidType* uuidList,  UInt16 uuidListLen, BtLibSdpRemoteServiceRecordHandle *serviceRecordList, UInt16 *numSrvRec);
    Err                 (*BtLibSdpServiceRecordMapRemote_)(BtLibSocketRef socket, BtLibDeviceAddressType* rDev, BtLibSdpRemoteServiceRecordHandle remoteHandle, BtLibSdpRecordHandle recordH);
    Err                 (*BtLibSdpServiceRecordGetStringOrUrlLength_)(BtLibSdpRecordHandle recordH, BtLibSdpAttributeIdType attributeID, UInt16* size);
    Err                 (*BtLibSdpServiceRecordGetNumListEntries_)(BtLibSdpRecordHandle recordH, BtLibSdpAttributeIdType attributeID, UInt16 listNumber, UInt16 *numEntries);
    Err                 (*BtLibSdpServiceRecordGetNumLists_)(BtLibSdpRecordHandle recordH, BtLibSdpAttributeIdType attributeID, UInt16 *numLists);
    Err                 (*BtLibSdpCompareUuids_)(BtLibSdpUuidType *uuid1, BtLibSdpUuidType *uuid2);

    Err                 (*BtLibSecurityFindTrustedDeviceRecord_)(BtLibDeviceAddressTypePtr addrP, UInt16 *index);
    Err                 (*BtLibSecurityRemoveTrustedDeviceRecord_)(UInt16 index);
    Err                 (*BtLibSecurityGetTrustedDeviceRecordInfo_)(UInt16 index, BtLibDeviceAddressTypePtr addrP, Char* nameBuffer, UInt8 NameBufferSize, BtLibClassOfDeviceType *cod, UInt32 *lastConnected, Boolean *persistentP);
    UInt16              (*BtLibSecurityNumTrustedDeviceRecords_)(Boolean persistentOnly);
    Err                 (*BtLibAddrBtdToA_)(BtLibDeviceAddressType *btDevP, Char *spaceP, UInt16 spaceSize);
    Err                 (*BtLibAddrAToBtd_)(const Char *a, BtLibDeviceAddressType *btDevP);

    Err                 (*BtLibServiceOpen_)(void);
    Err                 (*BtLibServiceClose_)(void);
    Err                 (*BtLibServiceIndicateSessionStart_)(void);
    Err                 (*BtLibServicePlaySound_)(void);

    const char*         (*zlibVersion_)(void);
    int                 (*deflateInit__)(struct z_stream_s* strm, int level, const char* version, int stream_size);
    int                 (*deflateInit2__)(struct z_stream_s* strm, int level, int method, int windowBits, int memLevel, int strategy, const char* version, int stream_size);
    int                 (*deflate_)(struct z_stream_s* strm, int flush);
    int                 (*deflateEnd_)(struct z_stream_s* strm);
    int                 (*inflateInit__)(struct z_stream_s* strm, const char* version, int stream_size);
    int                 (*inflateInit2__)(struct z_stream_s* strm, int windowBits, const char* version, int stream_size);
    int                 (*inflate_)(struct z_stream_s* strm, int flush);
    int                 (*inflateEnd_)(struct z_stream_s* strm);
    int                 (*deflateSetDictionary_)(struct z_stream_s* strm, const unsigned char* dictionary, unsigned int dictLength);
    int                 (*deflateCopy_)(struct z_stream_s* dest, struct z_stream_s* source);
    int                 (*deflateReset_)(struct z_stream_s* strm);
    int                 (*deflateParams_)(struct z_stream_s* strm, int level, int strategy);
    int                 (*inflateSetDictionary_)(struct z_stream_s* strm, const unsigned char* dictionary, unsigned int dictLength);
    int                 (*inflateSync_)(struct z_stream_s* strm);
    int                 (*inflateReset_)(struct z_stream_s* strm);
    int                 (*compress_)(unsigned char* dest,  unsigned long* destLen, const unsigned char* source, unsigned long sourceLen);
    int                 (*compress2_)(unsigned char* dest,  unsigned long* destLen, const unsigned char* source, unsigned long sourceLen, int level);
    int                 (*uncompress_)(unsigned char* dest,  unsigned long* destLen, const unsigned char* source, unsigned long sourceLen);
    unsigned long       (*adler32_)(unsigned long adler, const unsigned char* buf, unsigned int len);
    unsigned long       (*crc32_)(unsigned long crc, const unsigned char* buf, unsigned int len);

    Err                 (*TwGfxDrawPalmBitmap_)(TwGfxSurfaceType* aDestSurface, const TwGfxPointType* aDestPoint, BitmapType* aBitmap);
    Int32               (*TwGetMicroSeconds_)(void);

    void                (*TimSecondsToDateTime_)(UInt32 seconds, DateTimeType *dateTimeP);
    UInt32              (*TimDateTimeToSeconds_)(const DateTimeType *dateTimeP);

    Err                 (*TwAppRun_)(Int32* timeout);

    Err                 (*TwSemaphoreCreate_)(TwSemaphoreType* sema, Int32 initValue);
    Err                 (*TwSemaphoreDelete_)(TwSemaphoreType sema);
    Err                 (*TwSemaphoreAcquire_)(TwSemaphoreType sema, Int32 timeout);
    Err                 (*TwSemaphoreRelease_)(TwSemaphoreType sema);

    Err                 (*TwGetDBDataDirectory_)(MemHandle dbH, UInt16 *volRefNumP, Char *pathNameP, UInt16 maxLen);
    Err                 (*TwGetPRCDataDirectory_)(FileRef fileRef, Char *pathNameP, UInt16 maxLen);
    Int16               (*TwGetSlotNumberForVolume_)(UInt16 volRef);
    UInt16              (*TwHighScoreGetTournament_)(UInt32 creatorID, UInt16 scoreTypeIn, Char *code);

    int                 (*NetInit_)(int* timeout, int* error);
    int                 (*NetFini_)(void);

    int                 (*accept_)(int socket, struct sockaddr* addr, socklen_t addrlen);
    int                 (*bind_)(int socket, struct sockaddr* addr, socklen_t addrlen);
    int                 (*closesocket_)(int socket);
    int                 (*connect_)(int socket, struct sockaddr* addr, socklen_t addrlen);
    int                 (*getpeername_)(int socket, struct sockaddr* name, socklen_t* namelen);
    int                 (*getsockname_)(int socket, struct sockaddr* name, socklen_t* namelen);
    int                 (*getsockopt_)(int socket, int level, int opt, void* optval, socklen_t* optlen);
    int                 (*listen_)(int socket, int backlog);
    int                 (*poll_)(struct pollfd* fds, int nfds, int timeout);
    int                 (*recv_)(int socket, void* buffer, int buflen, int flags);
    int                 (*recvfrom_)(int socket, void* buffer, int buflen, int flags, struct sockaddr* from, socklen_t* fromlen);
    int                 (*send_)(int socket, void* buf, int buflen, int flags);
    int                 (*sendto_)(int socket, void* buf, int buflen, int flags, struct sockaddr* to, socklen_t tolen);
    int                 (*setsockopt_)(int socket, int level, int opt, void* optval, socklen_t optlen);
    int                 (*shutdown_)(int socket, int direction);
    int                 (*socket_)(int domain, int type, int protocol);

    struct hostent*     (*gethostbyname_)(const char* name);
    struct hostent*     (*gethostbyaddr_)(const char* addr, int len, int type);

    int                 (*inet_aton_)(const char* s, struct in_addr* inp);
    char*               (*inet_ntoa_)(struct in_addr in);

    UInt16              (*SysBatteryInfo_)(Boolean set, UInt16 *warnThresholdPercentP, UInt16 *criticalThresholdPercentP, UInt16 *shutdownThresholdPercentP, UInt32 *maxTicksP, SysBatteryKind* kindP, Boolean *pluggedIn, UInt8 *percentP);
    Err                 (*SysGetROMToken_)(UInt32 token, UInt8 **dataP, UInt16 *sizeP);

    Int32               (*TwThreadCurrent_)(void);

    Err                 (*SndStreamCreateExtended_)(SndStreamRef *channel, SndStreamMode mode, SndFormatType format, UInt32 samplerate, SndSampleType type, SndStreamWidth width, SndStreamVariableBufferCallback func, void *userdata, UInt32 buffsize);
    Err                 (*SndStreamDeviceControl_)(SndStreamRef channel, Int32 cmd, void* param, Int32 size);

    UInt32              (*PceNativeCall_)(NativeFuncType *nativeFuncP, void *userDataP);

    Err                 (*TwFindModule_)(void* addr, TwModuleInfo* info, UInt32 size);
    Err                 (*TwLoadModule_)(UInt32 dbType, UInt32 dbCreator, UInt32 rsrcType, UInt32 rsrcID, UInt32 flags, NativeFuncType** entry);
    Err                 (*TwUnloadModule_)(NativeFuncType* entry);

    Err                 (*TwCreateDatabaseFromImage_)(MemPtr image, Char name[]);
    UInt16              (*TwGetSlotRefNumForSlot_)(Int16 physicalSlot);
    const BitmapType*   (*TwGetGraphicForButton_)(WChar chr, Int32 size);

    MemPtr              (*gunzip_)(MemPtr image, UInt32 length);
    MemPtr              (*gzip_)(MemPtr image, UInt32 length);

    UInt16              (*FrmAlert_)(UInt16 alertId);
    UInt16              (*FrmCustomAlert_)(UInt16 alertId, const Char *s1, const Char *s2, const Char *s3);

    void*               (*Calloc_)(size_t count, size_t size);
    void*               (*Malloc_)(size_t size);
    void*               (*Realloc_)(void* ptr, size_t size);
    char*               (*Strdup_)(const char* str);
    void                (*Free_)(void* ptr);

    void                (*dprintf_)(const char * format, ...);
    Boolean             (*TwConfirmQuit_)(const Char *message);
    SysBatteryState     (*TwBatteryState_)(void);

    Err                 (*TwJpgOpenImage_)(TwJpgImageType** aResult, TwJpgImageReader aReader, void* aHandle);
    Err                 (*TwJpgSetAbortCheck_)(TwJpgImageType* aImage, TwJpgAbortCheck aChecker, void* aHandle);
    Err                 (*TwJpgGetAbortCheck_)(TwJpgImageType* aImage, TwJpgAbortCheck* aCheckerResult, void** aHandleResult);
    Err                 (*TwJpgCloseImage_)(TwJpgImageType* aImage);
    Err                 (*TwJpgGetImageInfo_)(TwJpgImageType* aImage, TwJpgImageInfoType* aInfoResult);
    Err                 (*TwJpgDecodeImage_)(TwJpgImageType* aImage, Int32 aPixelFormat, void** aBufferResult);
    Err                 (*TwJpgDecodeAndScaleImage_)(TwJpgImageType* aImage, Int32 aScaledWidth, Int32 aScaledHeight, Boolean aAntiAlias, void** aBufferResult);
    Err                 (*TwJpgDecodeImageToSurface_)(TwJpgImageType* aImage, Boolean aAntiAlias, TwGfxSurfaceType* aDestSurface);
    Err                 (*TwJpgDecodeImageToNewSurface_)(TwJpgImageType* aImage, Int32 aScaledWidth, Int32 aScaledHeight, Boolean aAntiAlias, TwGfxType* aGfxLib, TwGfxSurfaceType** aSurfaceResult);
    Err                 (*TwJpgScaleImageBuffer_)(void* aBufferIn, Int32 aInWidth, Int32 aInHeight, Int32 aScaledWidth, Int32 aScaledHeight, Boolean aAntiAlias, void** aBufferResult);

    const TwSecTableType* (*TwSecGetFunctions_)(Int32 version, TwSecSignatureType *codeSignature, UInt8 **codeStart, UInt32 *codeSize);

    UInt16              (*TwSndGetVolume_)(void);
    Err                 (*TwSndSetVolume_)(UInt16 newVolume);
    void                (*TwSndSetMute_)(Boolean mute, UInt32 unmuteAt);
    Boolean             (*TwSndGetMute_)(UInt32 *unmuteAt);
    Err                 (*TwSndSetBassBoost_)(UInt16 boostLevel);
    UInt16              (*TwSndGetBassBoost_)(void);
    Err                 (*TwSndPlaySystemSound_)(TwSysBeepTagType beepID, Int16 volume);
    Err                 (*TwSndSetAlarmPlaying_)(Boolean isAlarm);

    void                (*ClipboardAddItem_)(const ClipboardFormatType format, const void *ptr, UInt16 length);
    Err                 (*ClipboardAppendItem_)(const ClipboardFormatType format, const void *ptr, UInt16 length);
    MemHandle           (*ClipboardGetItem_)(const ClipboardFormatType format, UInt16 *length);

    FontID              (*FontSelect_)(FontID fontID);

    UInt16              (*FrmCustomResponseAlert_)(UInt16 alertId, const Char *s1, const Char *s2, const Char *s3, Char *entryStringBuf, Int16 entryStringBufLength, FormCheckResponseFuncPtr callback);
    FormType*           (*FrmGetActiveForm_)(void);
    WinHandle           (*FrmGetWindowHandle_)(const FormType *formP);

    void                (*TimeZoneToAscii_)(Int16 timeZone, const LmLocaleType *localeP, Char *stringP);

    UInt32              (*AlmGetAlarm_)(MemHandle dbH, UInt32 *refP);
    Err                 (*AlmSetAlarm_)(MemHandle dbH, UInt32 ref, UInt32 alarmSeconds, Boolean quiet, AlmAlarmProcPtr procP);

    UInt16              (*DateTemplateToAscii_)(const Char *templateP, UInt8 months, UInt8 days, UInt16 years, Char *stringP, Int16 stringLen);
    void                (*DateToAscii_)(UInt8 months, UInt8 days, UInt16 years, DateFormatType dateFormat, Char *stringP);

    void                (*EvtAddUniqueEventToQueue_)(const SysEventType *eventP, UInt32 id, Boolean inPlace);
    void                (*EvtGetPenNative_)(WinHandle winH, Int16 *pScreenX, Int16 *pScreenY, Boolean *pPenDown);

    Err                 (*MemHeapCheck_)(UInt16 heapID);
    Err                 (*MemHeapFreeBytes_)(UInt16 heapID, UInt32 *freeP, UInt32 *maxP);
    UInt32              (*MemHeapSize_)(UInt16 heapID); 
    Err                 (*MemHeapCompact_)(UInt16 heapID);
    Err                 (*MemHeapScramble_)(UInt16 heapID);

    UInt16              (*MemDebugMode_)(void);
    Err                 (*MemSetDebugMode_)(UInt16 flags);

    UInt16              (*MemHandleOwner_)(MemHandle h);
    Err                 (*MemHandleSetOwner_)( MemHandle h,  UInt16 owner);

    UInt16              (*MemPtrOwner_)(MemPtr p);
    Err                 (*MemPtrSetOwner_)(MemPtr p, UInt16 owner);

    Err                 (*SndDoCmd_)(void *channelP, SndCommandPtr cmdP, Boolean noWait);
    Err                 (*SndPlaySmf_)(void *chanP, SndSmfCmdEnum cmd, UInt8 *smfP, SndSmfOptionsType *selP, SndSmfChanRangeType *chanRangeP, SndSmfCallbacksType *callbacksP, Boolean bNoWait);
    Err                 (*SndPlaySmfResource_)(UInt32 resType, Int16 resID, SystemPreferencesChoice volumeSelector);

    Err                 (*SysAppLaunch_)(MemHandle dbH, UInt16 launchFlags, UInt16 cmd, MemPtr cmdPBP, UInt32 *resultP);

    Char*               (*SysErrString_)(Err err, Char *strP, UInt16 maxLen);

    Err                 (*SysCurAppDatabase_)(MemHandle *dbHP);

    Boolean             (*SysGetStackInfo_)(void** startPP, void** endPP);

    Char*               (*SysStringByIndex_)(UInt16 resID, UInt16 index, Char *strP, UInt16 maxLen);

    void                (*TimeToAscii_)(UInt8 hours, UInt8 minutes, TimeFormatType timeFormat, Char *stringP);
    UInt32              (*TimTimeZoneToUTC_)(UInt32 seconds, Int16 timeZone, Int16 daylightSavingAdjustment);
    UInt32              (*TimUTCToTimeZone_)(UInt32 seconds, Int16 timeZone, Int16 daylightSavingAdjustment);

#if TAPWAVE_API_VERSION >= 0x0203
    Err                 (*SysLoadModule_)(UInt32 dbType, UInt32 dbCreator, UInt16 rsrcID, UInt32 flags, UInt32 *refNumP);
    Err                 (*SysUnloadModule_)(UInt32 refNum);
    Err                 (*SysGetEntryAddresses_)(UInt32 refNum, UInt32 entryNumStart, UInt32 entryNumEnd, void **addressP);

    Err                 (*TwGfxStretchBlt2_)(TwGfxSurfaceType* aDestSurface, const TwGfxRectType* aDestRect, TwGfxSurfaceType* aSourceSurface, const TwGfxRectType* aSourceRect, UInt32 aStretchFlags);
    Err                 (*TwConvert68KBitmapToNative_)(void* aBitmap68KP, BitmapType** aBitmapResult, Boolean* aAllocatedResult);
#endif // TAPWAVE_API_VERSION >= 0x0203

#if TAPWAVE_API_VERSION >= 0x0204
    Err                 (*TwMpOpen_)(void);
    Err                 (*TwMpClose_)(void);
    Err                 (*TwMpHostGame_)(UInt32 creator, TwMpProcPtr callbackP, UInt32 refcon);
    Err                 (*TwMpHostInvitePlayer_)(BtLibDeviceAddressTypePtr bdAddrP);
    Err                 (*TwMpGuestAcceptInvitation_)(TwMpProcPtr callbackP, UInt32 refCon);
    Err                 (*TwMpHostDisinvitePlayer_)(BtLibDeviceAddressTypePtr bdAddrP);
    Err                 (*TwMpHostStartGame_)(void);
    Err                 (*TwMpCancelGame_)(void);
    Err                 (*TwMpGetPlayerInfo_)(BtLibDeviceAddressTypePtr bdAddrP, TwMpPlayerInfoType* infoP);
    Err                 (*TwMpGetNumPlayers_)(UInt8* numPlayers);
    Err                 (*TwMpGetAllPlayers_)(BtLibDeviceAddressType bdAddr[], UInt8 arraySize, UInt8* numPlayersReturnedP);
    Err                 (*TwMpGetNumAcceptedPlayers_)(UInt8* numPlayers);
    Err                 (*TwMpGetAcceptedPlayers_)(BtLibDeviceAddressType bdAddr[], UInt8 arraySize, UInt8* numPlayersReturnedP);
#endif // TAPWAVE_API_VERSION >= 0x0204

#if TAPWAVE_API_VERSION >= 0x0205
    Err                 (*TwSmfOpen_)(TwSmfHandle* aResult, UInt8* aSMFData, UInt32* aDurationMillisecResult);
    Err                 (*TwSmfClose_)(TwSmfHandle aSmf);
    Err                 (*TwSmfPlay_)(TwSmfHandle aSmf, SndSmfOptionsType* aOptions, SndSmfChanRangeType* aRangeInfo, SndCallbackInfoType* aCallback);
    Err                 (*TwSmfIsPlaying_)(TwSmfHandle aSmf, Boolean* aIsPlayingResult);
    Err                 (*TwSmfStop_)(TwSmfHandle aSmf);
    Err                 (*TwMidiOpen_)(TwMidiHandle* aResult);
    Err                 (*TwMidiClose_)(TwMidiHandle aMidi);
    Err                 (*TwMidiNoteOn_)(TwMidiHandle aMidi, UInt8 aChannel, UInt8 aKey, UInt8 aVelocity);
    Err                 (*TwMidiNoteOff_)(TwMidiHandle aMidi, UInt8 aChannel, UInt8 aKey, UInt8 aVelocity);
    Err                 (*TwMidiProgramChange_)(TwMidiHandle aMidi, UInt8 aChannel, UInt8 aProgramChange);
    Err                 (*TwMidiPitchBend_)(TwMidiHandle aMidi, UInt8 aChannel, Int32 aBend);
    Err                 (*TwMidiSysEx_)(TwMidiHandle aMidi, UInt8 aChannel, UInt8* aData, UInt16 aSize);
    Err                 (*TwMidiSetMasterVolume_)(Int32 aVolume);
    Err                 (*TwMidiGetMasterVolume_)(Int32* aVolumeResult);
    Err                 (*TwMidiGetLimits_)(Int32 aLimit, Int32* aLimitResult);
    Err                 (*TwMidiControlChange_)(TwMidiHandle aMidi, UInt8 aChannel, Int32 aControlChange, Int32 aValue);
    Err                 (*TwMidiPlaySmf_)(UInt8* aSMFData, UInt32* aDurationMillisecResult, Boolean aAsync);
#endif // TAPWAVE_API_VERSION >= 0x0205

    UInt32              TwGlueReserved[64];
};

#endif /* TAPWAVEGLUE_INTERNAL */

#ifdef __PALMOS_ARMLET__

#ifdef __cplusplus
extern "C" {
#endif

extern struct TwGlue*   twGlue;
extern const void*      twEmulState;
extern Call68KFuncType* twCall68KFunc;

#ifdef __cplusplus
}
#endif

    #undef  SysTicksPerSecond
    #define SysTicksPerSecond()     1000

    #undef DbgBreak
    #undef DbgMessage

    #undef DmArchiveRecord
    #undef DmAttachRecord
    #undef DmAttachResource
    #undef DmCloseDatabase
    #undef DmCreateDatabase
    #undef DmCreateDatabaseFromImage
    #undef DmDatabaseInfo
    #undef DmDatabaseSize
    #undef DmDeleteDatabase
    #undef DmDeleteRecord
    #undef DmDetachRecord
    #undef DmDetachResource
    #undef DmFindDatabase
    #undef DmFindRecordByID
    #undef DmFindResource
    #undef DmFindResourceType
    #undef DmFindSortPosition
    #undef DmGet1Resource
    #undef DmGetAppInfoH
    #undef DmGetDatabase
    #undef DmGetLastErr
    #undef DmGetNextDatabaseByTypeCreator
    #undef DmGetRecord
    #undef DmGetResource
    #undef DmGetResourceIndex
    #undef DmInsertionSort
    #undef DmMoveCategory
    #undef DmMoveRecord
    #undef DmNewHandle
    #undef DmNewRecord
    #undef DmNewResource
    #undef DmNumDatabases
    #undef DmNumRecords
    #undef DmNumRecordsInCategory
    #undef DmNumResources
    #undef DmOpenDatabase
    #undef DmOpenDatabaseByTypeCreator
    #undef DmOpenDatabaseInfo
    #undef DmPositionInCategory
    #undef DmQueryNextInCategory
    #undef DmQueryRecord
    #undef DmQuickSort
    #undef DmRecordInfo
    #undef DmReleaseRecord
    #undef DmReleaseResource
    #undef DmRemoveRecord
    #undef DmRemoveResource
    #undef DmRemoveSecretRecords
    #undef DmResetRecordStates
    #undef DmResizeRecord
    #undef DmResizeResource
    #undef DmResourceInfo
    #undef DmSearchRecord
    #undef DmSearchResource
    #undef DmSeekRecordInCategory
    #undef DmSet
    #undef DmSetDatabaseInfo
    #undef DmSetRecordInfo
    #undef DmSetResourceInfo
    #undef DmStrCopy
    #undef DmWrite
    #undef DmWriteCheck

    #undef ErrDisplayFileLineMsg

    #undef EvtAddEventToQueue
    #undef EvtDequeuePenPoint
    #undef EvtEventAvail
    #undef EvtGetEvent
    #undef EvtGetPen
    #undef EvtResetAutoOffTimer
    #undef EvtSetAutoOffTimer

    #undef ExgConnect
    #undef ExgPut
    #undef ExgGet
    #undef ExgAccept
    #undef ExgDisconnect
    #undef ExgSend
    #undef ExgReceive
    #undef ExgControl
    #undef ExgRegisterData
    #undef ExgRegisterDatatype
    #undef ExgNotifyReceive
    #undef ExgNotifyGoto
    #undef ExgDBRead
    #undef ExgDBWrite
    #undef ExgDoDialog
    #undef ExgRequest
    #undef ExgSetDefaultApplication
    #undef ExgGetDefaultApplication
    #undef ExgGetTargetApplication
    #undef ExgGetRegisteredApplications
    #undef ExgGetRegisteredTypes
    #undef ExgNotifyPreview

    #undef ExpCardInfo
    #undef ExpCardInserted
    #undef ExpCardPresent
    #undef ExpCardRemoved
    #undef ExpSlotEnumerate

    #undef FntAverageCharWidth
    #undef FntBaseLine
    #undef FntCharHeight
    #undef FntCharWidth
    #undef FntCharsInWidth
    #undef FntCharsWidth
    #undef FntDefineFont
    #undef FntDescenderHeight
    #undef FntGetFont
    #undef FntGetFontPtr
    #undef FntGetScrollValues
    #undef FntLineHeight
    #undef FntLineWidth
    #undef FntSetFont
    #undef FntWCharWidth
    #undef FntWidthToOffset
    #undef FntWordWrap
    #undef FntWordWrapReverseNLines

    #undef FrmDispatchEvent
    #undef MenuHandleEvent

    #undef FtrGet
    #undef FtrPtrFree
    #undef FtrPtrNew
    #undef FtrPtrResize
    #undef FtrSet
    #undef FtrUnregister

    #undef KeyCurrentState
    #undef KeySetMask

    #undef MemCmp
    #undef MemMove
    #undef MemSet

    #undef MemHandleFree
    #undef MemHandleLock
    #undef MemHandleNew
    #undef MemHandleResize
    #undef MemHandleSize
    #undef MemHandleUnlock

    #undef MemPtrFree
    #undef MemPtrNew
    #undef MemPtrResize
    #undef MemPtrSize

    #undef PrefGetAppPreferences
    #undef PrefGetPreference
    #undef PrefSetAppPreferences
    #undef PrefSetPreference

    #undef SndSetDefaultVolume
    #undef SndGetDefaultVolume

    #undef SndPlayResource

    #undef SndStreamCreate
    #undef SndStreamDelete
    #undef SndStreamGetPan
    #undef SndStreamGetVolume
    #undef SndStreamPause
    #undef SndStreamSetPan
    #undef SndStreamSetVolume
    #undef SndStreamStart
    #undef SndStreamStop

    #undef SysHandleEvent

    #undef SysNotifyBroadcast
    #undef SysNotifyBroadcastDeferred
    #undef SysNotifyRegister
    #undef SysNotifyUnregister

    #undef SysTaskDelay

    #undef SysUIAppSwitch

    #undef TimGetSeconds
    #undef TimGetTicks

    #undef StrCopy
    #undef StrNCopy
    #undef StrCat
    #undef StrNCat
    #undef StrLen
    #undef StrCompareAscii
    #undef StrCompare
    #undef StrNCompareAscii
    #undef StrNCompare
    #undef StrCaselessCompare
    #undef StrNCaselessCompare
    #undef StrToLower
    #undef StrIToA
    #undef StrIToH
    #undef StrLocalizeNumber
    #undef StrDelocalizeNumber
    #undef StrChr
    #undef StrStr
    #undef StrAToI
    #undef StrPrintF
    #undef StrVPrintF

    #undef TxtByteAttr
    #undef TxtCaselessCompare
    #undef TxtCharAttr
    #undef TxtCharBounds
    #undef TxtCharEncoding
    #undef TxtCharIsValid
    #undef TxtCharSize
    #undef TxtCharWidth
    #undef TxtCharXAttr
    #undef TxtCompare
    #undef TxtConvertEncoding
    #undef TxtEncodingName
    #undef TxtFindString
    #undef TxtGetChar
    #undef TxtGetNextChar
    #undef TxtGetPreviousChar
    #undef TxtGetTruncationOffset
    #undef TxtGetWordWrapOffset
    #undef TxtMaxEncoding
    #undef TxtNameToEncoding
    #undef TxtParamString
    #undef TxtReplaceStr
    #undef TxtSetNextChar
    #undef TxtStrEncoding
    #undef TxtTransliterate
    #undef TxtWordBounds

    #undef VFSCustomControl
    #undef VFSDirCreate
    #undef VFSDirEntryEnumerate
    #undef VFSExportDatabaseToFile
    #undef VFSExportDatabaseToFileCustom
    #undef VFSFileClose
    #undef VFSFileCreate
    #undef VFSFileDelete
    #undef VFSFileEOF
    #undef VFSFileGetAttributes
    #undef VFSFileGetDate
    #undef VFSFileOpen
    #undef VFSFileRead
    #undef VFSFileReadData
    #undef VFSFileRename
    #undef VFSFileResize
    #undef VFSFileSeek
    #undef VFSFileSetAttributes
    #undef VFSFileSetDate
    #undef VFSFileSize
    #undef VFSFileTell
    #undef VFSFileWrite
    #undef VFSGetDefaultDirectory
    #undef VFSImportDatabaseFromFile
    #undef VFSImportDatabaseFromFileCustom
    #undef VFSInstallFSLib
    #undef VFSRegisterDefaultDirectory
    #undef VFSRemoveFSLib
    #undef VFSUnregisterDefaultDirectory
    #undef VFSVolumeEnumerate
    #undef VFSVolumeFormat
    #undef VFSVolumeGetLabel
    #undef VFSVolumeInfo
    #undef VFSVolumeMount
    #undef VFSVolumeSetLabel
    #undef VFSVolumeSize
    #undef VFSVolumeUnmount

    #undef WinClipRectangle
    #undef WinCopyRectangle

    #undef WinCreateOffscreenWindow
    #undef WinCreateWindow
    #undef WinDeleteWindow

    #undef WinDisableWindow
    #undef WinEnableWindow

    #undef WinGetBounds
    #undef WinSetBounds

    #undef WinGetPixel
    #undef WinGetPixelRGB

    #undef WinGetFramesRectangle
    #undef WinGetSupportedDensity
    #undef WinGetWindowFrameRect

    #undef WinPaintBitmap
    #undef WinPaintChar
    #undef WinPaintChars
    #undef WinPaintLine
    #undef WinPaintLines
    #undef WinPaintPixel
    #undef WinPaintPixels
    #undef WinPaintRectangle
    #undef WinPaintRectangleFrame
    #undef WinPaintRoundedRectangleFrame

    #undef WinPushDrawState
    #undef WinPopDrawState

    #undef WinRestoreBits
    #undef WinSaveBits

    #undef WinScreenGetAttribute
    #undef WinScreenMode

    #undef WinScreenLock
    #undef WinScreenUnlock

    #undef WinScrollRectangle

    #undef WinIndexToRGB
    #undef WinRGBToIndex

    #undef WinGetDisplayWindow

    #undef WinGetActiveWindow
    #undef WinSetActiveWindow

    #undef WinGetDrawWindow
    #undef WinSetDrawWindow

    #undef WinGetClip
    #undef WinSetClip
    #undef WinResetClip

    #undef WinGetCoordinateSystem
    #undef WinSetCoordinateSystem

    #undef WinSetBackColor
    #undef WinSetBackColorRGB

    #undef WinSetForeColor
    #undef WinSetForeColorRGB

    #undef WinSetTextColor
    #undef WinSetTextColorRGB

    #undef WinSetDrawMode
    #undef WinSetUnderlineMode

    #undef WinSetPattern
    #undef WinSetPatternType

    #undef WinScaleCoord
    #undef WinUnscaleCoord

    #undef WinScalePoint
    #undef WinUnscalePoint

    #undef WinScaleRectangle
    #undef WinUnscaleRectangle

    #undef WinDisplayToWindowPt
    #undef WinWindowToDisplayPt

    #undef WinGetBitmapDimensions

    #undef PINGetInputAreaState
    #undef PINSetInputAreaState
    #undef PINGetInputTriggerState
    #undef PINSetInputTriggerState

    #undef StatHide
    #undef StatShow
    #undef StatGetAttribute

    #undef SysGetOrientation
    #undef SysSetOrientation
    #undef SysGetOrientationTriggerState
    #undef SysSetOrientationTriggerState

    #undef TwInputOpen
    #undef TwInputClose
    #undef TwInputActivate
    #undef TwInputDeactivate
    #undef TwInputGetPeriod
    #undef TwInputSetPeriod
    #undef TwInputGetCapacity
    #undef TwInputSetCapacity
    #undef TwInputGetFormat
    #undef TwInputSetFormat
    #undef TwInputPeek
    #undef TwInputRead
    #undef TwInputPoll
    #undef TwInputControl

    #undef TwDeviceOpen
    #undef TwDeviceClose
    #undef TwDeviceRead
    #undef TwDeviceWrite
    #undef TwDeviceGetProperty
    #undef TwDeviceSetProperty
    #undef TwDeviceControl

    #undef TwHighScoreRegister
    #undef TwHighScoreUnregister
    #undef TwHighScoreReport
    #undef TwHighScoreGetSummary
    #undef TwHighScoreGetDetails

    #undef TwGfxOpen
    #undef TwGfxClose
    #undef TwGfxGetInfo
    #undef TwGfxGetMemoryUsage
    #undef TwGfxGetDisplaySurface
    #undef TwGfxInVBlank
    #undef TwGfxWaitForVBlank
    #undef TwGfxAllocSurface
    #undef TwGfxFreeSurface
    #undef TwGfxSetClip
    #undef TwGfxGetClip
    #undef TwGfxGetSurfaceInfo
    #undef TwGfxLockSurface
    #undef TwGfxUnlockSurface
    #undef TwGfxReadSurface
    #undef TwGfxWriteSurface
    #undef TwGfxIsSurfaceReady
    #undef TwGfxBitBlt
    #undef TwGfxTransformBlt
    #undef TwGfxDrawPoints
    #undef TwGfxDrawColorPoints
    #undef TwGfxDrawLines
    #undef TwGfxDrawLineSegments
    #undef TwGfxDrawRect
    #undef TwGfxFillRect
    #undef TwGfxDrawSpans
    #undef TwGfxDrawBitmap

    #undef TwAppStart
    #undef TwAppStop
    #undef TwNextEvent

    #undef TwGfxGetPalmDisplaySurface
    #undef TwGfxReadSurfaceRegion
    #undef TwGfxWriteSurfaceRegion
    #undef TwGfxAsyncBlt
    #undef TwGfxTransparentBlt
    #undef TwGfxMaskBlt
    #undef TwGfxBlendBlt
    #undef TwGfxMaskBlendBlt
    #undef TwGfxStretchBlt
    #undef TwGfxTileBlt

    #undef BtLibOpen
    #undef BtLibClose
    #undef BtLibHandleEvent

    #undef BtLibRegisterManagementNotification
    #undef BtLibUnregisterManagementNotification
    #undef BtLibStartInquiry
    #undef BtLibCancelInquiry
    #undef BtLibDiscoverSingleDevice
    #undef BtLibDiscoverMultipleDevices
    #undef BtLibGetSelectedDevices
    #undef BtLibGetRemoteDeviceName
    #undef BtLibLinkConnect
    #undef BtLibLinkDisconnect
    #undef BtLibPiconetCreate
    #undef BtLibPiconetDestroy
    #undef BtLibPiconetUnlockInbound
    #undef BtLibPiconetLockInbound
    #undef BtLibLinkSetState
    #undef BtLibLinkGetState
    #undef BtLibSetGeneralPreference
    #undef BtLibGetGeneralPreference

    #undef BtLibSocketCreate
    #undef BtLibSocketClose
    #undef BtLibSocketListen
    #undef BtLibSocketConnect
    #undef BtLibSocketRespondToConnection
    #undef BtLibSocketSend
    #undef BtLibSocketAdvanceCredit
    #undef BtLibSocketGetInfo

    #undef BtLibSdpGetServerChannelByUuid
    #undef BtLibSdpGetPsmByUuid
    #undef BtLibSdpServiceRecordCreate
    #undef BtLibSdpServiceRecordDestroy
    #undef BtLibSdpServiceRecordStartAdvertising
    #undef BtLibSdpServiceRecordStopAdvertising
    #undef BtLibSdpServiceRecordSetAttributesForSocket
    #undef BtLibSdpServiceRecordsGetByServiceClass
    #undef BtLibSdpServiceRecordMapRemote
    #undef BtLibSdpServiceRecordGetStringOrUrlLength
    #undef BtLibSdpServiceRecordGetNumListEntries
    #undef BtLibSdpServiceRecordGetNumLists
    #undef BtLibSdpCompareUuids

    #undef BtLibSecurityFindTrustedDeviceRecord
    #undef BtLibSecurityRemoveTrustedDeviceRecord
    #undef BtLibSecurityGetTrustedDeviceRecordInfo
    #undef BtLibSecurityNumTrustedDeviceRecords
    #undef BtLibAddrBtdToA
    #undef BtLibAddrAToBtd

    #undef BtLibServiceOpen
    #undef BtLibServiceClose
    #undef BtLibServiceIndicateSessionStart
    #undef BtLibServicePlaySound

    #undef zlibVersion
    #undef deflateInit_
    #undef deflateInit2_
    #undef deflate
    #undef deflateEnd
    #undef inflateInit_
    #undef inflateInit2_
    #undef inflate
    #undef inflateEnd
    #undef deflateSetDictionary
    #undef deflateCopy
    #undef deflateReset
    #undef deflateParams
    #undef inflateSetDictionary
    #undef inflateSync
    #undef inflateReset
    #undef compress
    #undef compress2
    #undef uncompress
    #undef adler32
    #undef crc32

    #undef TwGfxDrawPalmBitmap
    #undef TwGetMicroSeconds

    #undef TimSecondsToDateTime
    #undef TimDateTimeToSeconds

    #undef TwAppRun

    #undef TwSemaphoreCreate
    #undef TwSemaphoreDelete
    #undef TwSemaphoreAcquire
    #undef TwSemaphoreRelease

    #undef TwGetDBDataDirectory
    #undef TwGetPRCDataDirectory
    #undef TwGetSlotNumberForVolume
    #undef TwHighScoreGetTournament

    #undef NetInit
    #undef NetFini

    #undef accept
    #undef bind
    #undef closesocket
    #undef connect
    #undef getpeername
    #undef getsockname
    #undef getsockopt
    #undef listen
    #undef poll
    #undef recv
    #undef recvfrom
    #undef send
    #undef sendto
    #undef setsockopt
    #undef shutdown
    #undef socket

    #undef gethostbyname
    #undef gethostbyaddr

    #undef inet_aton
    #undef inet_ntoa

    #undef SysBatteryInfo
    #undef SysGetROMToken

    #undef TwThreadCurrent

    #undef SndStreamCreateExtended
    #undef SndStreamDeviceControl

    #undef PceNativeCall

    #undef TwFindModule
    #undef TwLoadModule
    #undef TwUnloadModule

    #undef TwCreateDatabaseFromImage
    #undef TwGetSlotRefNumForSlot
    #undef TwGetGraphicForButton

    #undef gunzip
    #undef gzip

    #undef FrmAlert
    #undef FrmCustomAlert

    #undef Calloc
    #undef Malloc
    #undef Realloc
    #undef Strdup
    #undef Free

    #undef dprintf
    #undef TwConfirmQuit
    #undef TwBatteryState

    #undef TwJpgOpenImage
    #undef TwJpgSetAbortCheck
    #undef TwJpgGetAbortCheck
    #undef TwJpgCloseImage
    #undef TwJpgGetImageInfo
    #undef TwJpgDecodeImage
    #undef TwJpgDecodeAndScaleImage
    #undef TwJpgDecodeImageToSurface
    #undef TwJpgDecodeImageToNewSurface
    #undef TwJpgScaleImageBuffer

    #undef TwSecGetFunctions

    #undef TwSndGetVolume
    #undef TwSndSetVolume
    #undef TwSndSetMute
    #undef TwSndGetMute
    #undef TwSndSetBassBoost
    #undef TwSndGetBassBoost
    #undef TwSndPlaySystemSound
    #undef TwSndSetAlarmPlaying

    #undef ClipboardAddItem
    #undef ClipboardAppendItem
    #undef ClipboardGetItem

    #undef FontSelect

    #undef FrmCustomResponseAlert
    #undef FrmGetActiveForm
    #undef FrmGetWindowHandle

    #undef TimeZoneToAscii

    #undef AlmGetAlarm
    #undef AlmSetAlarm

    #undef DateTemplateToAscii
    #undef DateToAscii

    #undef EvtAddUniqueEventToQueue
    #undef EvtGetPenNative

    #undef MemHeapCheck
    #undef MemHeapFreeBytes
    #undef MemHeapSize
    #undef MemHeapCompact
    #undef MemHeapScramble

    #undef MemDebugMode
    #undef MemSetDebugMode

    #undef MemHandleOwner
    #undef MemHandleSetOwner

    #undef MemPtrOwner
    #undef MemPtrSetOwner

    #undef SndDoCmd
    #undef SndPlaySmf
    #undef SndPlaySmfResource

    #undef SysAppLaunch

    #undef SysErrString

    #undef SysCurAppDatabase

    #undef SysGetStackInfo

    #undef SysStringByIndex

    #undef TimeToAscii
    #undef TimTimeZoneToUTC
    #undef TimUTCToTimeZone

#if TAPWAVE_API_VERSION >= 0x0203
    #undef SysLoadModule
    #undef SysUnloadModule
    #undef SysGetEntryAddresses

    #undef TwGfxStretchBlt2
    #undef TwConvert68KBitmapToNative
#endif // TAPWAVE_API_VERSION >= 0x0203

#if TAPWAVE_API_VERSION >= 0x0204
    #undef TwMpOpen
    #undef TwMpClose
    #undef TwMpHostGame
    #undef TwMpHostInvitePlayer
    #undef TwMpGuestAcceptInvitation
    #undef TwMpHostDisinvitePlayer
    #undef TwMpHostStartGame
    #undef TwMpCancelGame
    #undef TwMpGetPlayerInfo
    #undef TwMpGetNumPlayers
    #undef TwMpGetAllPlayers
    #undef TwMpGetNumAcceptedPlayers
    #undef TwMpGetAcceptedPlayers
#endif // TAPWAVE_API_VERSION >= 0x0204

#if TAPWAVE_API_VERSION >= 0x0205
    #undef TwSmfOpen
    #undef TwSmfClose
    #undef TwSmfPlay
    #undef TwSmfIsPlaying
    #undef TwSmfStop
    #undef TwMidiOpen
    #undef TwMidiClose
    #undef TwMidiNoteOn
    #undef TwMidiNoteOff
    #undef TwMidiProgramChange
    #undef TwMidiPitchBend
    #undef TwMidiSysEx
    #undef TwMidiSetMasterVolume
    #undef TwMidiGetMasterVolume
    #undef TwMidiGetLimits
    #undef TwMidiControlChange
    #undef TwMidiPlaySmf
#endif // TAPWAVE_API_VERSION >= 0x0205

    #define DbgBreak    twGlue->DbgBreak_
    #define DbgMessage    twGlue->DbgMessage_

    #define DmArchiveRecord    twGlue->DmArchiveRecord_
    #define DmAttachRecord    twGlue->DmAttachRecord_
    #define DmAttachResource    twGlue->DmAttachResource_
    #define DmCloseDatabase    twGlue->DmCloseDatabase_
    #define DmCreateDatabase    twGlue->DmCreateDatabase_
    #define DmCreateDatabaseFromImage    twGlue->DmCreateDatabaseFromImage_
    #define DmDatabaseInfo    twGlue->DmDatabaseInfo_
    #define DmDatabaseSize    twGlue->DmDatabaseSize_
    #define DmDeleteDatabase    twGlue->DmDeleteDatabase_
    #define DmDeleteRecord    twGlue->DmDeleteRecord_
    #define DmDetachRecord    twGlue->DmDetachRecord_
    #define DmDetachResource    twGlue->DmDetachResource_
    #define DmFindDatabase    twGlue->DmFindDatabase_
    #define DmFindRecordByID    twGlue->DmFindRecordByID_
    #define DmFindResource    twGlue->DmFindResource_
    #define DmFindResourceType    twGlue->DmFindResourceType_
    #define DmFindSortPosition    twGlue->DmFindSortPosition_
    #define DmGet1Resource    twGlue->DmGet1Resource_
    #define DmGetAppInfoH    twGlue->DmGetAppInfoH_
    #define DmGetDatabase    twGlue->DmGetDatabase_
    #define DmGetLastErr    twGlue->DmGetLastErr_
    #define DmGetNextDatabaseByTypeCreator    twGlue->DmGetNextDatabaseByTypeCreator_
    #define DmGetRecord    twGlue->DmGetRecord_
    #define DmGetResource    twGlue->DmGetResource_
    #define DmGetResourceIndex    twGlue->DmGetResourceIndex_
    #define DmInsertionSort    twGlue->DmInsertionSort_
    #define DmMoveCategory    twGlue->DmMoveCategory_
    #define DmMoveRecord    twGlue->DmMoveRecord_
    #define DmNewHandle    twGlue->DmNewHandle_
    #define DmNewRecord    twGlue->DmNewRecord_
    #define DmNewResource    twGlue->DmNewResource_
    #define DmNumDatabases    twGlue->DmNumDatabases_
    #define DmNumRecords    twGlue->DmNumRecords_
    #define DmNumRecordsInCategory    twGlue->DmNumRecordsInCategory_
    #define DmNumResources    twGlue->DmNumResources_
    #define DmOpenDatabase    twGlue->DmOpenDatabase_
    #define DmOpenDatabaseByTypeCreator    twGlue->DmOpenDatabaseByTypeCreator_
    #define DmOpenDatabaseInfo    twGlue->DmOpenDatabaseInfo_
    #define DmPositionInCategory    twGlue->DmPositionInCategory_
    #define DmQueryNextInCategory    twGlue->DmQueryNextInCategory_
    #define DmQueryRecord    twGlue->DmQueryRecord_
    #define DmQuickSort    twGlue->DmQuickSort_
    #define DmRecordInfo    twGlue->DmRecordInfo_
    #define DmReleaseRecord    twGlue->DmReleaseRecord_
    #define DmReleaseResource    twGlue->DmReleaseResource_
    #define DmRemoveRecord    twGlue->DmRemoveRecord_
    #define DmRemoveResource    twGlue->DmRemoveResource_
    #define DmRemoveSecretRecords    twGlue->DmRemoveSecretRecords_
    #define DmResetRecordStates    twGlue->DmResetRecordStates_
    #define DmResizeRecord    twGlue->DmResizeRecord_
    #define DmResizeResource    twGlue->DmResizeResource_
    #define DmResourceInfo    twGlue->DmResourceInfo_
    #define DmSearchRecord    twGlue->DmSearchRecord_
    #define DmSearchResource    twGlue->DmSearchResource_
    #define DmSeekRecordInCategory    twGlue->DmSeekRecordInCategory_
    #define DmSet    twGlue->DmSet_
    #define DmSetDatabaseInfo    twGlue->DmSetDatabaseInfo_
    #define DmSetRecordInfo    twGlue->DmSetRecordInfo_
    #define DmSetResourceInfo    twGlue->DmSetResourceInfo_
    #define DmStrCopy    twGlue->DmStrCopy_
    #define DmWrite    twGlue->DmWrite_
    #define DmWriteCheck    twGlue->DmWriteCheck_

    #define ErrDisplayFileLineMsg    twGlue->ErrDisplayFileLineMsg_

    #define EvtAddEventToQueue    twGlue->EvtAddEventToQueue_
    #define EvtDequeuePenPoint    twGlue->EvtDequeuePenPoint_
    #define EvtEventAvail    twGlue->EvtEventAvail_
    #define EvtGetEvent    twGlue->EvtGetEvent_
    #define EvtGetPen    twGlue->EvtGetPen_
    #define EvtResetAutoOffTimer    twGlue->EvtResetAutoOffTimer_
    #define EvtSetAutoOffTimer    twGlue->EvtSetAutoOffTimer_

    #define ExgConnect    twGlue->ExgConnect_
    #define ExgPut    twGlue->ExgPut_
    #define ExgGet    twGlue->ExgGet_
    #define ExgAccept    twGlue->ExgAccept_
    #define ExgDisconnect    twGlue->ExgDisconnect_
    #define ExgSend    twGlue->ExgSend_
    #define ExgReceive    twGlue->ExgReceive_
    #define ExgControl    twGlue->ExgControl_
    #define ExgRegisterData    twGlue->ExgRegisterData_
    #define ExgRegisterDatatype    twGlue->ExgRegisterDatatype_
    #define ExgNotifyReceive    twGlue->ExgNotifyReceive_
    #define ExgNotifyGoto    twGlue->ExgNotifyGoto_
    #define ExgDBRead    twGlue->ExgDBRead_
    #define ExgDBWrite    twGlue->ExgDBWrite_
    #define ExgDoDialog    twGlue->ExgDoDialog_
    #define ExgRequest    twGlue->ExgRequest_
    #define ExgSetDefaultApplication    twGlue->ExgSetDefaultApplication_
    #define ExgGetDefaultApplication    twGlue->ExgGetDefaultApplication_
    #define ExgGetTargetApplication    twGlue->ExgGetTargetApplication_
    #define ExgGetRegisteredApplications    twGlue->ExgGetRegisteredApplications_
    #define ExgGetRegisteredTypes    twGlue->ExgGetRegisteredTypes_
    #define ExgNotifyPreview    twGlue->ExgNotifyPreview_

    #define ExpCardInfo    twGlue->ExpCardInfo_
    #define ExpCardInserted    twGlue->ExpCardInserted_
    #define ExpCardPresent    twGlue->ExpCardPresent_
    #define ExpCardRemoved    twGlue->ExpCardRemoved_
    #define ExpSlotEnumerate    twGlue->ExpSlotEnumerate_

    #define FntAverageCharWidth    twGlue->FntAverageCharWidth_
    #define FntBaseLine    twGlue->FntBaseLine_
    #define FntCharHeight    twGlue->FntCharHeight_
    #define FntCharWidth    twGlue->FntCharWidth_
    #define FntCharsInWidth    twGlue->FntCharsInWidth_
    #define FntCharsWidth    twGlue->FntCharsWidth_
    #define FntDefineFont    twGlue->FntDefineFont_
    #define FntDescenderHeight    twGlue->FntDescenderHeight_
    #define FntGetFont    twGlue->FntGetFont_
    #define FntGetFontPtr    twGlue->FntGetFontPtr_
    #define FntGetScrollValues    twGlue->FntGetScrollValues_
    #define FntLineHeight    twGlue->FntLineHeight_
    #define FntLineWidth    twGlue->FntLineWidth_
    #define FntSetFont    twGlue->FntSetFont_
    #define FntWCharWidth    twGlue->FntWCharWidth_
    #define FntWidthToOffset    twGlue->FntWidthToOffset_
    #define FntWordWrap    twGlue->FntWordWrap_
    #define FntWordWrapReverseNLines    twGlue->FntWordWrapReverseNLines_

    #define FrmDispatchEvent    twGlue->FrmDispatchEvent_
    #define MenuHandleEvent    twGlue->MenuHandleEvent_

    #define FtrGet    twGlue->FtrGet_
    #define FtrPtrFree    twGlue->FtrPtrFree_
    #define FtrPtrNew    twGlue->FtrPtrNew_
    #define FtrPtrResize    twGlue->FtrPtrResize_
    #define FtrSet    twGlue->FtrSet_
    #define FtrUnregister    twGlue->FtrUnregister_

    #define KeyCurrentState    twGlue->KeyCurrentState_
    #define KeySetMask    twGlue->KeySetMask_

    #define MemCmp    twGlue->MemCmp_
    #define MemMove    twGlue->MemMove_
    #define MemSet    twGlue->MemSet_

    #define MemHandleFree    twGlue->MemHandleFree_
    #define MemHandleLock    twGlue->MemHandleLock_
    #define MemHandleNew    twGlue->MemHandleNew_
    #define MemHandleResize    twGlue->MemHandleResize_
    #define MemHandleSize    twGlue->MemHandleSize_
    #define MemHandleUnlock    twGlue->MemHandleUnlock_

    #define MemPtrFree    twGlue->MemPtrFree_
    #define MemPtrNew    twGlue->MemPtrNew_
    #define MemPtrResize    twGlue->MemPtrResize_
    #define MemPtrSize    twGlue->MemPtrSize_

    #define PrefGetAppPreferences    twGlue->PrefGetAppPreferences_
    #define PrefGetPreference    twGlue->PrefGetPreference_
    #define PrefSetAppPreferences    twGlue->PrefSetAppPreferences_
    #define PrefSetPreference    twGlue->PrefSetPreference_

    #define SndSetDefaultVolume    twGlue->SndSetDefaultVolume_
    #define SndGetDefaultVolume    twGlue->SndGetDefaultVolume_

    #define SndPlayResource    twGlue->SndPlayResource_

    #define SndStreamCreate    twGlue->SndStreamCreate_
    #define SndStreamDelete    twGlue->SndStreamDelete_
    #define SndStreamGetPan    twGlue->SndStreamGetPan_
    #define SndStreamGetVolume    twGlue->SndStreamGetVolume_
    #define SndStreamPause    twGlue->SndStreamPause_
    #define SndStreamSetPan    twGlue->SndStreamSetPan_
    #define SndStreamSetVolume    twGlue->SndStreamSetVolume_
    #define SndStreamStart    twGlue->SndStreamStart_
    #define SndStreamStop    twGlue->SndStreamStop_

    #define SysHandleEvent    twGlue->SysHandleEvent_

    #define SysNotifyBroadcast    twGlue->SysNotifyBroadcast_
    #define SysNotifyBroadcastDeferred    twGlue->SysNotifyBroadcastDeferred_
    #define SysNotifyRegister    twGlue->SysNotifyRegister_
    #define SysNotifyUnregister    twGlue->SysNotifyUnregister_

    #define SysTaskDelay    twGlue->SysTaskDelay_

    #define SysUIAppSwitch    twGlue->SysUIAppSwitch_

    #define TimGetSeconds    twGlue->TimGetSeconds_
    #define TimGetTicks    twGlue->TimGetTicks_

    #define StrCopy    twGlue->StrCopy_
    #define StrNCopy    twGlue->StrNCopy_
    #define StrCat    twGlue->StrCat_
    #define StrNCat    twGlue->StrNCat_
    #define StrLen    twGlue->StrLen_
    #define StrCompareAscii    twGlue->StrCompareAscii_
    #define StrCompare    twGlue->StrCompare_
    #define StrNCompareAscii    twGlue->StrNCompareAscii_
    #define StrNCompare    twGlue->StrNCompare_
    #define StrCaselessCompare    twGlue->StrCaselessCompare_
    #define StrNCaselessCompare    twGlue->StrNCaselessCompare_
    #define StrToLower    twGlue->StrToLower_
    #define StrIToA    twGlue->StrIToA_
    #define StrIToH    twGlue->StrIToH_
    #define StrLocalizeNumber    twGlue->StrLocalizeNumber_
    #define StrDelocalizeNumber    twGlue->StrDelocalizeNumber_
    #define StrChr    twGlue->StrChr_
    #define StrStr    twGlue->StrStr_
    #define StrAToI    twGlue->StrAToI_
    #define StrPrintF    twGlue->StrPrintF_
    #define StrVPrintF    twGlue->StrVPrintF_

    #define TxtByteAttr    twGlue->TxtByteAttr_
    #define TxtCaselessCompare    twGlue->TxtCaselessCompare_
    #define TxtCharAttr    twGlue->TxtCharAttr_
    #define TxtCharBounds    twGlue->TxtCharBounds_
    #define TxtCharEncoding    twGlue->TxtCharEncoding_
    #define TxtCharIsValid    twGlue->TxtCharIsValid_
    #define TxtCharSize    twGlue->TxtCharSize_
    #define TxtCharWidth    twGlue->TxtCharWidth_
    #define TxtCharXAttr    twGlue->TxtCharXAttr_
    #define TxtCompare    twGlue->TxtCompare_
    #define TxtConvertEncoding    twGlue->TxtConvertEncoding_
    #define TxtEncodingName    twGlue->TxtEncodingName_
    #define TxtFindString    twGlue->TxtFindString_
    #define TxtGetChar    twGlue->TxtGetChar_
    #define TxtGetNextChar    twGlue->TxtGetNextChar_
    #define TxtGetPreviousChar    twGlue->TxtGetPreviousChar_
    #define TxtGetTruncationOffset    twGlue->TxtGetTruncationOffset_
    #define TxtGetWordWrapOffset    twGlue->TxtGetWordWrapOffset_
    #define TxtMaxEncoding    twGlue->TxtMaxEncoding_
    #define TxtNameToEncoding    twGlue->TxtNameToEncoding_
    #define TxtParamString    twGlue->TxtParamString_
    #define TxtReplaceStr    twGlue->TxtReplaceStr_
    #define TxtSetNextChar    twGlue->TxtSetNextChar_
    #define TxtStrEncoding    twGlue->TxtStrEncoding_
    #define TxtTransliterate    twGlue->TxtTransliterate_
    #define TxtWordBounds    twGlue->TxtWordBounds_

    #define VFSCustomControl    twGlue->VFSCustomControl_
    #define VFSDirCreate    twGlue->VFSDirCreate_
    #define VFSDirEntryEnumerate    twGlue->VFSDirEntryEnumerate_
    #define VFSExportDatabaseToFile    twGlue->VFSExportDatabaseToFile_
    #define VFSExportDatabaseToFileCustom    twGlue->VFSExportDatabaseToFileCustom_
    #define VFSFileClose    twGlue->VFSFileClose_
    #define VFSFileCreate    twGlue->VFSFileCreate_
    #define VFSFileDelete    twGlue->VFSFileDelete_
    #define VFSFileEOF    twGlue->VFSFileEOF_
    #define VFSFileGetAttributes    twGlue->VFSFileGetAttributes_
    #define VFSFileGetDate    twGlue->VFSFileGetDate_
    #define VFSFileOpen    twGlue->VFSFileOpen_
    #define VFSFileRead    twGlue->VFSFileRead_
    #define VFSFileReadData    twGlue->VFSFileReadData_
    #define VFSFileRename    twGlue->VFSFileRename_
    #define VFSFileResize    twGlue->VFSFileResize_
    #define VFSFileSeek    twGlue->VFSFileSeek_
    #define VFSFileSetAttributes    twGlue->VFSFileSetAttributes_
    #define VFSFileSetDate    twGlue->VFSFileSetDate_
    #define VFSFileSize    twGlue->VFSFileSize_
    #define VFSFileTell    twGlue->VFSFileTell_
    #define VFSFileWrite    twGlue->VFSFileWrite_
    #define VFSGetDefaultDirectory    twGlue->VFSGetDefaultDirectory_
    #define VFSImportDatabaseFromFile    twGlue->VFSImportDatabaseFromFile_
    #define VFSImportDatabaseFromFileCustom    twGlue->VFSImportDatabaseFromFileCustom_
    #define VFSInstallFSLib    twGlue->VFSInstallFSLib_
    #define VFSRegisterDefaultDirectory    twGlue->VFSRegisterDefaultDirectory_
    #define VFSRemoveFSLib    twGlue->VFSRemoveFSLib_
    #define VFSUnregisterDefaultDirectory    twGlue->VFSUnregisterDefaultDirectory_
    #define VFSVolumeEnumerate    twGlue->VFSVolumeEnumerate_
    #define VFSVolumeFormat    twGlue->VFSVolumeFormat_
    #define VFSVolumeGetLabel    twGlue->VFSVolumeGetLabel_
    #define VFSVolumeInfo    twGlue->VFSVolumeInfo_
    #define VFSVolumeMount    twGlue->VFSVolumeMount_
    #define VFSVolumeSetLabel    twGlue->VFSVolumeSetLabel_
    #define VFSVolumeSize    twGlue->VFSVolumeSize_
    #define VFSVolumeUnmount    twGlue->VFSVolumeUnmount_

    #define WinClipRectangle    twGlue->WinClipRectangle_
    #define WinCopyRectangle    twGlue->WinCopyRectangle_

    #define WinCreateOffscreenWindow    twGlue->WinCreateOffscreenWindow_
    #define WinCreateWindow    twGlue->WinCreateWindow_
    #define WinDeleteWindow    twGlue->WinDeleteWindow_

    #define WinDisableWindow    twGlue->WinDisableWindow_
    #define WinEnableWindow    twGlue->WinEnableWindow_

    #define WinGetBounds    twGlue->WinGetBounds_
    #define WinSetBounds    twGlue->WinSetBounds_

    #define WinGetPixel    twGlue->WinGetPixel_
    #define WinGetPixelRGB    twGlue->WinGetPixelRGB_

    #define WinGetFramesRectangle    twGlue->WinGetFramesRectangle_
    #define WinGetSupportedDensity    twGlue->WinGetSupportedDensity_
    #define WinGetWindowFrameRect    twGlue->WinGetWindowFrameRect_

    #define WinPaintBitmap    twGlue->WinPaintBitmap_
    #define WinPaintChar    twGlue->WinPaintChar_
    #define WinPaintChars    twGlue->WinPaintChars_
    #define WinPaintLine    twGlue->WinPaintLine_
    #define WinPaintLines    twGlue->WinPaintLines_
    #define WinPaintPixel    twGlue->WinPaintPixel_
    #define WinPaintPixels    twGlue->WinPaintPixels_
    #define WinPaintRectangle    twGlue->WinPaintRectangle_
    #define WinPaintRectangleFrame    twGlue->WinPaintRectangleFrame_
    #define WinPaintRoundedRectangleFrame    twGlue->WinPaintRoundedRectangleFrame_

    #define WinPushDrawState    twGlue->WinPushDrawState_
    #define WinPopDrawState    twGlue->WinPopDrawState_

    #define WinRestoreBits    twGlue->WinRestoreBits_
    #define WinSaveBits    twGlue->WinSaveBits_

    #define WinScreenGetAttribute    twGlue->WinScreenGetAttribute_
    #define WinScreenMode    twGlue->WinScreenMode_

    #define WinScreenLock    twGlue->WinScreenLock_
    #define WinScreenUnlock    twGlue->WinScreenUnlock_

    #define WinScrollRectangle    twGlue->WinScrollRectangle_

    #define WinIndexToRGB    twGlue->WinIndexToRGB_
    #define WinRGBToIndex    twGlue->WinRGBToIndex_

    #define WinGetDisplayWindow    twGlue->WinGetDisplayWindow_

    #define WinGetActiveWindow    twGlue->WinGetActiveWindow_
    #define WinSetActiveWindow    twGlue->WinSetActiveWindow_

    #define WinGetDrawWindow    twGlue->WinGetDrawWindow_
    #define WinSetDrawWindow    twGlue->WinSetDrawWindow_

    #define WinGetClip    twGlue->WinGetClip_
    #define WinSetClip    twGlue->WinSetClip_
    #define WinResetClip    twGlue->WinResetClip_

    #define WinGetCoordinateSystem    twGlue->WinGetCoordinateSystem_
    #define WinSetCoordinateSystem    twGlue->WinSetCoordinateSystem_

    #define WinSetBackColor    twGlue->WinSetBackColor_
    #define WinSetBackColorRGB    twGlue->WinSetBackColorRGB_

    #define WinSetForeColor    twGlue->WinSetForeColor_
    #define WinSetForeColorRGB    twGlue->WinSetForeColorRGB_

    #define WinSetTextColor    twGlue->WinSetTextColor_
    #define WinSetTextColorRGB    twGlue->WinSetTextColorRGB_

    #define WinSetDrawMode    twGlue->WinSetDrawMode_
    #define WinSetUnderlineMode    twGlue->WinSetUnderlineMode_

    #define WinSetPattern    twGlue->WinSetPattern_
    #define WinSetPatternType    twGlue->WinSetPatternType_

    #define WinScaleCoord    twGlue->WinScaleCoord_
    #define WinUnscaleCoord    twGlue->WinUnscaleCoord_

    #define WinScalePoint    twGlue->WinScalePoint_
    #define WinUnscalePoint    twGlue->WinUnscalePoint_

    #define WinScaleRectangle    twGlue->WinScaleRectangle_
    #define WinUnscaleRectangle    twGlue->WinUnscaleRectangle_

    #define WinDisplayToWindowPt    twGlue->WinDisplayToWindowPt_
    #define WinWindowToDisplayPt    twGlue->WinWindowToDisplayPt_

    #define WinGetBitmapDimensions    twGlue->WinGetBitmapDimensions_

    #define PINGetInputAreaState    twGlue->PINGetInputAreaState_
    #define PINSetInputAreaState    twGlue->PINSetInputAreaState_
    #define PINGetInputTriggerState    twGlue->PINGetInputTriggerState_
    #define PINSetInputTriggerState    twGlue->PINSetInputTriggerState_

    #define StatHide    twGlue->StatHide_
    #define StatShow    twGlue->StatShow_
    #define StatGetAttribute    twGlue->StatGetAttribute_

    #define SysGetOrientation    twGlue->SysGetOrientation_
    #define SysSetOrientation    twGlue->SysSetOrientation_
    #define SysGetOrientationTriggerState    twGlue->SysGetOrientationTriggerState_
    #define SysSetOrientationTriggerState    twGlue->SysSetOrientationTriggerState_

    #define TwInputOpen    twGlue->TwInputOpen_
    #define TwInputClose    twGlue->TwInputClose_
    #define TwInputActivate    twGlue->TwInputActivate_
    #define TwInputDeactivate    twGlue->TwInputDeactivate_
    #define TwInputGetPeriod    twGlue->TwInputGetPeriod_
    #define TwInputSetPeriod    twGlue->TwInputSetPeriod_
    #define TwInputGetCapacity    twGlue->TwInputGetCapacity_
    #define TwInputSetCapacity    twGlue->TwInputSetCapacity_
    #define TwInputGetFormat    twGlue->TwInputGetFormat_
    #define TwInputSetFormat    twGlue->TwInputSetFormat_
    #define TwInputPeek    twGlue->TwInputPeek_
    #define TwInputRead    twGlue->TwInputRead_
    #define TwInputPoll    twGlue->TwInputPoll_
    #define TwInputControl    twGlue->TwInputControl_

    #define TwDeviceOpen    twGlue->TwDeviceOpen_
    #define TwDeviceClose    twGlue->TwDeviceClose_
    #define TwDeviceRead    twGlue->TwDeviceRead_
    #define TwDeviceWrite    twGlue->TwDeviceWrite_
    #define TwDeviceGetProperty    twGlue->TwDeviceGetProperty_
    #define TwDeviceSetProperty    twGlue->TwDeviceSetProperty_
    #define TwDeviceControl    twGlue->TwDeviceControl_

    #define TwHighScoreRegister    twGlue->TwHighScoreRegister_
    #define TwHighScoreUnregister    twGlue->TwHighScoreUnregister_
    #define TwHighScoreReport    twGlue->TwHighScoreReport_
    #define TwHighScoreGetSummary    twGlue->TwHighScoreGetSummary_
    #define TwHighScoreGetDetails    twGlue->TwHighScoreGetDetails_

    #define TwGfxOpen    twGlue->TwGfxOpen_
    #define TwGfxClose    twGlue->TwGfxClose_
    #define TwGfxGetInfo    twGlue->TwGfxGetInfo_
    #define TwGfxGetMemoryUsage    twGlue->TwGfxGetMemoryUsage_
    #define TwGfxGetDisplaySurface    twGlue->TwGfxGetDisplaySurface_
    #define TwGfxInVBlank    twGlue->TwGfxInVBlank_
    #define TwGfxWaitForVBlank    twGlue->TwGfxWaitForVBlank_
    #define TwGfxAllocSurface    twGlue->TwGfxAllocSurface_
    #define TwGfxFreeSurface    twGlue->TwGfxFreeSurface_
    #define TwGfxSetClip    twGlue->TwGfxSetClip_
    #define TwGfxGetClip    twGlue->TwGfxGetClip_
    #define TwGfxGetSurfaceInfo    twGlue->TwGfxGetSurfaceInfo_
    #define TwGfxLockSurface    twGlue->TwGfxLockSurface_
    #define TwGfxUnlockSurface    twGlue->TwGfxUnlockSurface_
    #define TwGfxReadSurface    twGlue->TwGfxReadSurface_
    #define TwGfxWriteSurface    twGlue->TwGfxWriteSurface_
    #define TwGfxIsSurfaceReady    twGlue->TwGfxIsSurfaceReady_
    #define TwGfxBitBlt    twGlue->TwGfxBitBlt_
    #define TwGfxTransformBlt    twGlue->TwGfxTransformBlt_
    #define TwGfxDrawPoints    twGlue->TwGfxDrawPoints_
    #define TwGfxDrawColorPoints    twGlue->TwGfxDrawColorPoints_
    #define TwGfxDrawLines    twGlue->TwGfxDrawLines_
    #define TwGfxDrawLineSegments    twGlue->TwGfxDrawLineSegments_
    #define TwGfxDrawRect    twGlue->TwGfxDrawRect_
    #define TwGfxFillRect    twGlue->TwGfxFillRect_
    #define TwGfxDrawSpans    twGlue->TwGfxDrawSpans_
    #define TwGfxDrawBitmap    twGlue->TwGfxDrawBitmap_

    #define TwAppStart    twGlue->TwAppStart_
    #define TwAppStop    twGlue->TwAppStop_
    #define TwNextEvent    twGlue->TwNextEvent_

    #define TwGfxGetPalmDisplaySurface    twGlue->TwGfxGetPalmDisplaySurface_
    #define TwGfxReadSurfaceRegion    twGlue->TwGfxReadSurfaceRegion_
    #define TwGfxWriteSurfaceRegion    twGlue->TwGfxWriteSurfaceRegion_
    #define TwGfxAsyncBlt    twGlue->TwGfxAsyncBlt_
    #define TwGfxTransparentBlt    twGlue->TwGfxTransparentBlt_
    #define TwGfxMaskBlt    twGlue->TwGfxMaskBlt_
    #define TwGfxBlendBlt    twGlue->TwGfxBlendBlt_
    #define TwGfxMaskBlendBlt    twGlue->TwGfxMaskBlendBlt_
    #define TwGfxStretchBlt    twGlue->TwGfxStretchBlt_
    #define TwGfxTileBlt    twGlue->TwGfxTileBlt_

    #define BtLibOpen    twGlue->BtLibOpen_
    #define BtLibClose    twGlue->BtLibClose_
    #define BtLibHandleEvent    twGlue->BtLibHandleEvent_

    #define BtLibRegisterManagementNotification    twGlue->BtLibRegisterManagementNotification_
    #define BtLibUnregisterManagementNotification    twGlue->BtLibUnregisterManagementNotification_
    #define BtLibStartInquiry    twGlue->BtLibStartInquiry_
    #define BtLibCancelInquiry    twGlue->BtLibCancelInquiry_
    #define BtLibDiscoverSingleDevice    twGlue->BtLibDiscoverSingleDevice_
    #define BtLibDiscoverMultipleDevices    twGlue->BtLibDiscoverMultipleDevices_
    #define BtLibGetSelectedDevices    twGlue->BtLibGetSelectedDevices_
    #define BtLibGetRemoteDeviceName    twGlue->BtLibGetRemoteDeviceName_
    #define BtLibLinkConnect    twGlue->BtLibLinkConnect_
    #define BtLibLinkDisconnect    twGlue->BtLibLinkDisconnect_
    #define BtLibPiconetCreate    twGlue->BtLibPiconetCreate_
    #define BtLibPiconetDestroy    twGlue->BtLibPiconetDestroy_
    #define BtLibPiconetUnlockInbound    twGlue->BtLibPiconetUnlockInbound_
    #define BtLibPiconetLockInbound    twGlue->BtLibPiconetLockInbound_
    #define BtLibLinkSetState    twGlue->BtLibLinkSetState_
    #define BtLibLinkGetState    twGlue->BtLibLinkGetState_
    #define BtLibSetGeneralPreference    twGlue->BtLibSetGeneralPreference_
    #define BtLibGetGeneralPreference    twGlue->BtLibGetGeneralPreference_

    #define BtLibSocketCreate    twGlue->BtLibSocketCreate_
    #define BtLibSocketClose    twGlue->BtLibSocketClose_
    #define BtLibSocketListen    twGlue->BtLibSocketListen_
    #define BtLibSocketConnect    twGlue->BtLibSocketConnect_
    #define BtLibSocketRespondToConnection    twGlue->BtLibSocketRespondToConnection_
    #define BtLibSocketSend    twGlue->BtLibSocketSend_
    #define BtLibSocketAdvanceCredit    twGlue->BtLibSocketAdvanceCredit_
    #define BtLibSocketGetInfo    twGlue->BtLibSocketGetInfo_

    #define BtLibSdpGetServerChannelByUuid    twGlue->BtLibSdpGetServerChannelByUuid_
    #define BtLibSdpGetPsmByUuid    twGlue->BtLibSdpGetPsmByUuid_
    #define BtLibSdpServiceRecordCreate    twGlue->BtLibSdpServiceRecordCreate_
    #define BtLibSdpServiceRecordDestroy    twGlue->BtLibSdpServiceRecordDestroy_
    #define BtLibSdpServiceRecordStartAdvertising    twGlue->BtLibSdpServiceRecordStartAdvertising_
    #define BtLibSdpServiceRecordStopAdvertising    twGlue->BtLibSdpServiceRecordStopAdvertising_
    #define BtLibSdpServiceRecordSetAttributesForSocket    twGlue->BtLibSdpServiceRecordSetAttributesForSocket_
    #define BtLibSdpServiceRecordsGetByServiceClass    twGlue->BtLibSdpServiceRecordsGetByServiceClass_
    #define BtLibSdpServiceRecordMapRemote    twGlue->BtLibSdpServiceRecordMapRemote_
    #define BtLibSdpServiceRecordGetStringOrUrlLength    twGlue->BtLibSdpServiceRecordGetStringOrUrlLength_
    #define BtLibSdpServiceRecordGetNumListEntries    twGlue->BtLibSdpServiceRecordGetNumListEntries_
    #define BtLibSdpServiceRecordGetNumLists    twGlue->BtLibSdpServiceRecordGetNumLists_
    #define BtLibSdpCompareUuids    twGlue->BtLibSdpCompareUuids_

    #define BtLibSecurityFindTrustedDeviceRecord    twGlue->BtLibSecurityFindTrustedDeviceRecord_
    #define BtLibSecurityRemoveTrustedDeviceRecord    twGlue->BtLibSecurityRemoveTrustedDeviceRecord_
    #define BtLibSecurityGetTrustedDeviceRecordInfo    twGlue->BtLibSecurityGetTrustedDeviceRecordInfo_
    #define BtLibSecurityNumTrustedDeviceRecords    twGlue->BtLibSecurityNumTrustedDeviceRecords_
    #define BtLibAddrBtdToA    twGlue->BtLibAddrBtdToA_
    #define BtLibAddrAToBtd    twGlue->BtLibAddrAToBtd_

    #define BtLibServiceOpen    twGlue->BtLibServiceOpen_
    #define BtLibServiceClose    twGlue->BtLibServiceClose_
    #define BtLibServiceIndicateSessionStart    twGlue->BtLibServiceIndicateSessionStart_
    #define BtLibServicePlaySound    twGlue->BtLibServicePlaySound_

    #define zlibVersion    twGlue->zlibVersion_
    #define deflateInit_    twGlue->deflateInit__
    #define deflateInit2_    twGlue->deflateInit2__
    #define deflate    twGlue->deflate_
    #define deflateEnd    twGlue->deflateEnd_
    #define inflateInit_    twGlue->inflateInit__
    #define inflateInit2_    twGlue->inflateInit2__
    #define inflate    twGlue->inflate_
    #define inflateEnd    twGlue->inflateEnd_
    #define deflateSetDictionary    twGlue->deflateSetDictionary_
    #define deflateCopy    twGlue->deflateCopy_
    #define deflateReset    twGlue->deflateReset_
    #define deflateParams    twGlue->deflateParams_
    #define inflateSetDictionary    twGlue->inflateSetDictionary_
    #define inflateSync    twGlue->inflateSync_
    #define inflateReset    twGlue->inflateReset_
    #define compress    twGlue->compress_
    #define compress2    twGlue->compress2_
    #define uncompress    twGlue->uncompress_
    #define adler32    twGlue->adler32_
    #define crc32    twGlue->crc32_

    #define TwGfxDrawPalmBitmap    twGlue->TwGfxDrawPalmBitmap_
    #define TwGetMicroSeconds    twGlue->TwGetMicroSeconds_

    #define TimSecondsToDateTime    twGlue->TimSecondsToDateTime_
    #define TimDateTimeToSeconds    twGlue->TimDateTimeToSeconds_

    #define TwAppRun    twGlue->TwAppRun_

    #define TwSemaphoreCreate    twGlue->TwSemaphoreCreate_
    #define TwSemaphoreDelete    twGlue->TwSemaphoreDelete_
    #define TwSemaphoreAcquire    twGlue->TwSemaphoreAcquire_
    #define TwSemaphoreRelease    twGlue->TwSemaphoreRelease_

    #define TwGetDBDataDirectory    twGlue->TwGetDBDataDirectory_
    #define TwGetPRCDataDirectory    twGlue->TwGetPRCDataDirectory_
    #define TwGetSlotNumberForVolume    twGlue->TwGetSlotNumberForVolume_
    #define TwHighScoreGetTournament    twGlue->TwHighScoreGetTournament_

    #define NetInit    twGlue->NetInit_
    #define NetFini    twGlue->NetFini_

    #define accept    twGlue->accept_
    #define bind    twGlue->bind_
    #define closesocket    twGlue->closesocket_
    #define connect    twGlue->connect_
    #define getpeername    twGlue->getpeername_
    #define getsockname    twGlue->getsockname_
    #define getsockopt    twGlue->getsockopt_
    #define listen    twGlue->listen_
    #define poll    twGlue->poll_
    #define recv    twGlue->recv_
    #define recvfrom    twGlue->recvfrom_
    #define send    twGlue->send_
    #define sendto    twGlue->sendto_
    #define setsockopt    twGlue->setsockopt_
    #define shutdown    twGlue->shutdown_
    #define socket    twGlue->socket_

    #define gethostbyname    twGlue->gethostbyname_
    #define gethostbyaddr    twGlue->gethostbyaddr_

    #define inet_aton    twGlue->inet_aton_
    #define inet_ntoa    twGlue->inet_ntoa_

    #define SysBatteryInfo    twGlue->SysBatteryInfo_
    #define SysGetROMToken    twGlue->SysGetROMToken_

    #define TwThreadCurrent    twGlue->TwThreadCurrent_

    #define SndStreamCreateExtended    twGlue->SndStreamCreateExtended_
    #define SndStreamDeviceControl    twGlue->SndStreamDeviceControl_

    #define PceNativeCall    twGlue->PceNativeCall_

    #define TwFindModule    twGlue->TwFindModule_
    #define TwLoadModule    twGlue->TwLoadModule_
    #define TwUnloadModule    twGlue->TwUnloadModule_

    #define TwCreateDatabaseFromImage    twGlue->TwCreateDatabaseFromImage_
    #define TwGetSlotRefNumForSlot    twGlue->TwGetSlotRefNumForSlot_
    #define TwGetGraphicForButton    twGlue->TwGetGraphicForButton_

    #define gunzip    twGlue->gunzip_
    #define gzip    twGlue->gzip_

    #define FrmAlert    twGlue->FrmAlert_
    #define FrmCustomAlert    twGlue->FrmCustomAlert_

    #define Calloc    twGlue->Calloc_
    #define Malloc    twGlue->Malloc_
    #define Realloc    twGlue->Realloc_
    #define Strdup    twGlue->Strdup_
    #define Free    twGlue->Free_

    #define dprintf    twGlue->dprintf_
    #define TwConfirmQuit    twGlue->TwConfirmQuit_
    #define TwBatteryState    twGlue->TwBatteryState_

    #define TwJpgOpenImage    twGlue->TwJpgOpenImage_
    #define TwJpgSetAbortCheck    twGlue->TwJpgSetAbortCheck_
    #define TwJpgGetAbortCheck    twGlue->TwJpgGetAbortCheck_
    #define TwJpgCloseImage    twGlue->TwJpgCloseImage_
    #define TwJpgGetImageInfo    twGlue->TwJpgGetImageInfo_
    #define TwJpgDecodeImage    twGlue->TwJpgDecodeImage_
    #define TwJpgDecodeAndScaleImage    twGlue->TwJpgDecodeAndScaleImage_
    #define TwJpgDecodeImageToSurface    twGlue->TwJpgDecodeImageToSurface_
    #define TwJpgDecodeImageToNewSurface    twGlue->TwJpgDecodeImageToNewSurface_
    #define TwJpgScaleImageBuffer    twGlue->TwJpgScaleImageBuffer_

    #define TwSecGetFunctions    twGlue->TwSecGetFunctions_

    #define TwSndGetVolume    twGlue->TwSndGetVolume_
    #define TwSndSetVolume    twGlue->TwSndSetVolume_
    #define TwSndSetMute    twGlue->TwSndSetMute_
    #define TwSndGetMute    twGlue->TwSndGetMute_
    #define TwSndSetBassBoost    twGlue->TwSndSetBassBoost_
    #define TwSndGetBassBoost    twGlue->TwSndGetBassBoost_
    #define TwSndPlaySystemSound    twGlue->TwSndPlaySystemSound_
    #define TwSndSetAlarmPlaying    twGlue->TwSndSetAlarmPlaying_

    #define ClipboardAddItem    twGlue->ClipboardAddItem_
    #define ClipboardAppendItem    twGlue->ClipboardAppendItem_
    #define ClipboardGetItem    twGlue->ClipboardGetItem_

    #define FontSelect    twGlue->FontSelect_

    #define FrmCustomResponseAlert    twGlue->FrmCustomResponseAlert_
    #define FrmGetActiveForm    twGlue->FrmGetActiveForm_
    #define FrmGetWindowHandle    twGlue->FrmGetWindowHandle_

    #define TimeZoneToAscii    twGlue->TimeZoneToAscii_

    #define AlmGetAlarm    twGlue->AlmGetAlarm_
    #define AlmSetAlarm    twGlue->AlmSetAlarm_

    #define DateTemplateToAscii    twGlue->DateTemplateToAscii_
    #define DateToAscii    twGlue->DateToAscii_

    #define EvtAddUniqueEventToQueue    twGlue->EvtAddUniqueEventToQueue_
    #define EvtGetPenNative    twGlue->EvtGetPenNative_

    #define MemHeapCheck    twGlue->MemHeapCheck_
    #define MemHeapFreeBytes    twGlue->MemHeapFreeBytes_
    #define MemHeapSize    twGlue->MemHeapSize_
    #define MemHeapCompact    twGlue->MemHeapCompact_
    #define MemHeapScramble    twGlue->MemHeapScramble_

    #define MemDebugMode    twGlue->MemDebugMode_
    #define MemSetDebugMode    twGlue->MemSetDebugMode_

    #define MemHandleOwner    twGlue->MemHandleOwner_
    #define MemHandleSetOwner    twGlue->MemHandleSetOwner_

    #define MemPtrOwner    twGlue->MemPtrOwner_
    #define MemPtrSetOwner    twGlue->MemPtrSetOwner_

    #define SndDoCmd    twGlue->SndDoCmd_
    #define SndPlaySmf    twGlue->SndPlaySmf_
    #define SndPlaySmfResource    twGlue->SndPlaySmfResource_

    #define SysAppLaunch    twGlue->SysAppLaunch_

    #define SysErrString    twGlue->SysErrString_

    #define SysCurAppDatabase    twGlue->SysCurAppDatabase_

    #define SysGetStackInfo    twGlue->SysGetStackInfo_

    #define SysStringByIndex    twGlue->SysStringByIndex_

    #define TimeToAscii    twGlue->TimeToAscii_
    #define TimTimeZoneToUTC    twGlue->TimTimeZoneToUTC_
    #define TimUTCToTimeZone    twGlue->TimUTCToTimeZone_

#if TAPWAVE_API_VERSION >= 0x0203
    #define SysLoadModule    twGlue->SysLoadModule_
    #define SysUnloadModule    twGlue->SysUnloadModule_
    #define SysGetEntryAddresses    twGlue->SysGetEntryAddresses_

    #define TwGfxStretchBlt2    twGlue->TwGfxStretchBlt2_
    #define TwConvert68KBitmapToNative    twGlue->TwConvert68KBitmapToNative_
#endif // TAPWAVE_API_VERSION >= 0x0203

#if TAPWAVE_API_VERSION >= 0x0204
    #define TwMpOpen    twGlue->TwMpOpen_
    #define TwMpClose    twGlue->TwMpClose_
    #define TwMpHostGame    twGlue->TwMpHostGame_
    #define TwMpHostInvitePlayer    twGlue->TwMpHostInvitePlayer_
    #define TwMpGuestAcceptInvitation    twGlue->TwMpGuestAcceptInvitation_
    #define TwMpHostDisinvitePlayer    twGlue->TwMpHostDisinvitePlayer_
    #define TwMpHostStartGame    twGlue->TwMpHostStartGame_
    #define TwMpCancelGame    twGlue->TwMpCancelGame_
    #define TwMpGetPlayerInfo    twGlue->TwMpGetPlayerInfo_
    #define TwMpGetNumPlayers    twGlue->TwMpGetNumPlayers_
    #define TwMpGetAllPlayers    twGlue->TwMpGetAllPlayers_
    #define TwMpGetNumAcceptedPlayers    twGlue->TwMpGetNumAcceptedPlayers_
    #define TwMpGetAcceptedPlayers    twGlue->TwMpGetAcceptedPlayers_
#endif // TAPWAVE_API_VERSION >= 0x0204

#if TAPWAVE_API_VERSION >= 0x0205
    #define TwSmfOpen    twGlue->TwSmfOpen_
    #define TwSmfClose    twGlue->TwSmfClose_
    #define TwSmfPlay    twGlue->TwSmfPlay_
    #define TwSmfIsPlaying    twGlue->TwSmfIsPlaying_
    #define TwSmfStop    twGlue->TwSmfStop_
    #define TwMidiOpen    twGlue->TwMidiOpen_
    #define TwMidiClose    twGlue->TwMidiClose_
    #define TwMidiNoteOn    twGlue->TwMidiNoteOn_
    #define TwMidiNoteOff    twGlue->TwMidiNoteOff_
    #define TwMidiProgramChange    twGlue->TwMidiProgramChange_
    #define TwMidiPitchBend    twGlue->TwMidiPitchBend_
    #define TwMidiSysEx    twGlue->TwMidiSysEx_
    #define TwMidiSetMasterVolume    twGlue->TwMidiSetMasterVolume_
    #define TwMidiGetMasterVolume    twGlue->TwMidiGetMasterVolume_
    #define TwMidiGetLimits    twGlue->TwMidiGetLimits_
    #define TwMidiControlChange    twGlue->TwMidiControlChange_
    #define TwMidiPlaySmf    twGlue->TwMidiPlaySmf_
#endif // TAPWAVE_API_VERSION >= 0x0205

#undef accept
#undef bind
#undef closesocket
#undef connect
#undef getpeername
#undef getsockname
#undef getsockopt
#undef listen
#undef poll
#undef recv
#undef recvfrom
#undef send
#undef sendto
#undef setsockopt
#undef shutdown
#undef socket
#undef gethostbyname
#undef gethostbyaddr
#undef inet_addr
#undef inet_aton
#undef inet_ntoa


inline int accept(int socket, struct sockaddr* addr, socklen_t addrlen)
{
	return twGlue->accept_(socket, addr, addrlen);
}
	
inline int bind(int socket, struct sockaddr* addr, socklen_t addrlen)
{
    return twGlue->bind_(socket, addr, addrlen);
}
	
inline int closesocket(int socket)
{
    return twGlue->closesocket_(socket);
}
	
inline int connect(int socket, struct sockaddr* addr, socklen_t addrlen)
{
    return twGlue->connect_(socket, addr, addrlen);
}
	
inline int getpeername(int socket, struct sockaddr* name, socklen_t* namelen)
{
    return twGlue->getpeername_(socket, name, namelen);
}
	
inline int getsockname(int socket, struct sockaddr* name, socklen_t* namelen)
{
    return twGlue->getsockname_(socket, name, namelen);
}

inline int getsockopt(int socket, int level, int opt, void* optval, socklen_t* optlen)
{
    return twGlue->getsockopt_(socket, level, opt, optval, optlen);
}
	
inline int listen(int socket, int backlog)
{
    return twGlue->listen_(socket, backlog);
}

inline int poll(struct pollfd* fds, int nfds, int timeout)
{
    return twGlue->poll_(fds, nfds, timeout);
}
	
inline int recv(int socket, void* buffer, int buflen, int flags)
{
    return twGlue->recv_(socket, buffer, buflen, flags);
}
	
inline int recvfrom(int socket, void* buffer, int buflen, int flags, struct sockaddr* from, socklen_t* fromlen)
{
    return twGlue->recvfrom_(socket, buffer, buflen, flags, from, fromlen);
}
	
inline int send(int socket, void* buf, int buflen, int flags)
{
    return twGlue->send_(socket, buf, buflen, flags);
}
	
inline int sendto(int socket, void* buf, int buflen, int flags, struct sockaddr* to, socklen_t tolen)
{
    return twGlue->sendto_(socket, buf, buflen, flags, to, tolen);
}
	
inline int setsockopt(int socket, int level, int opt, void* optval, socklen_t optlen)
{
    return twGlue->setsockopt_(socket, level, opt, optval, optlen);
}

inline int shutdown(int socket, int direction)
{
    return twGlue->shutdown_(socket, direction);
}
	
inline int socket(int domain, int type, int protocol)
{
    return twGlue->socket_(domain, type, protocol);
}

inline struct hostent* gethostbyname(const char* name)
{
    return twGlue->gethostbyname_(name);
}

inline struct hostent* gethostbyaddr(const char* addr, int len, int type)
{
    return twGlue->gethostbyaddr_(addr, len, type);
}

inline in_addr_t inet_addr(const char* s)
{
    struct in_addr in;
    twGlue->inet_aton_(s, &in);
    return in.s_addr;
}

inline int inet_aton(const char* s, struct in_addr* inp)
{
    return twGlue->inet_aton_(s, inp);
}

inline char* inet_ntoa(struct in_addr in)
{
    return twGlue->inet_ntoa_(in);
}

#endif /* __PALMOS_ARMLET__ */

#ifdef TAPWAVEGLUE_INTERNAL

    twGlue->DbgBreak_ = &DbgBreak;
    twGlue->DbgMessage_ = &DbgMessage;

    twGlue->DmArchiveRecord_ = &DmArchiveRecord;
    twGlue->DmAttachRecord_ = &DmAttachRecord;
    twGlue->DmAttachResource_ = &DmAttachResource;
    twGlue->DmCloseDatabase_ = &DmCloseDatabase;
    twGlue->DmCreateDatabase_ = &DmCreateDatabase;
    twGlue->DmCreateDatabaseFromImage_ = &DmCreateDatabaseFromImage;
    twGlue->DmDatabaseInfo_ = &DmDatabaseInfo;
    twGlue->DmDatabaseSize_ = &DmDatabaseSize;
    twGlue->DmDeleteDatabase_ = &DmDeleteDatabase;
    twGlue->DmDeleteRecord_ = &DmDeleteRecord;
    twGlue->DmDetachRecord_ = &DmDetachRecord;
    twGlue->DmDetachResource_ = &DmDetachResource;
    twGlue->DmFindDatabase_ = &DmFindDatabase;
    twGlue->DmFindRecordByID_ = &DmFindRecordByID;
    twGlue->DmFindResource_ = &DmFindResource;
    twGlue->DmFindResourceType_ = &DmFindResourceType;
    twGlue->DmFindSortPosition_ = &DmFindSortPosition;
    twGlue->DmGet1Resource_ = &DmGet1Resource;
    twGlue->DmGetAppInfoH_ = &DmGetAppInfoH;
    twGlue->DmGetDatabase_ = &DmGetDatabase;
    twGlue->DmGetLastErr_ = &DmGetLastErr;
    twGlue->DmGetNextDatabaseByTypeCreator_ = &DmGetNextDatabaseByTypeCreator;
    twGlue->DmGetRecord_ = &DmGetRecord;
    twGlue->DmGetResource_ = &DmGetResource;
    twGlue->DmGetResourceIndex_ = &DmGetResourceIndex;
    twGlue->DmInsertionSort_ = &DmInsertionSort;
    twGlue->DmMoveCategory_ = &DmMoveCategory;
    twGlue->DmMoveRecord_ = &DmMoveRecord;
    twGlue->DmNewHandle_ = &DmNewHandle;
    twGlue->DmNewRecord_ = &DmNewRecord;
    twGlue->DmNewResource_ = &DmNewResource;
    twGlue->DmNumDatabases_ = &DmNumDatabases;
    twGlue->DmNumRecords_ = &DmNumRecords;
    twGlue->DmNumRecordsInCategory_ = &DmNumRecordsInCategory;
    twGlue->DmNumResources_ = &DmNumResources;
    twGlue->DmOpenDatabase_ = &DmOpenDatabase;
    twGlue->DmOpenDatabaseByTypeCreator_ = &DmOpenDatabaseByTypeCreator;
    twGlue->DmOpenDatabaseInfo_ = &DmOpenDatabaseInfo;
    twGlue->DmPositionInCategory_ = &DmPositionInCategory;
    twGlue->DmQueryNextInCategory_ = &DmQueryNextInCategory;
    twGlue->DmQueryRecord_ = &DmQueryRecord;
    twGlue->DmQuickSort_ = &DmQuickSort;
    twGlue->DmRecordInfo_ = &DmRecordInfo;
    twGlue->DmReleaseRecord_ = &DmReleaseRecord;
    twGlue->DmReleaseResource_ = &DmReleaseResource;
    twGlue->DmRemoveRecord_ = &DmRemoveRecord;
    twGlue->DmRemoveResource_ = &DmRemoveResource;
    twGlue->DmRemoveSecretRecords_ = &DmRemoveSecretRecords;
    twGlue->DmResetRecordStates_ = &DmResetRecordStates;
    twGlue->DmResizeRecord_ = &DmResizeRecord;
    twGlue->DmResizeResource_ = &DmResizeResource;
    twGlue->DmResourceInfo_ = &DmResourceInfo;
    twGlue->DmSearchRecord_ = &DmSearchRecord;
    twGlue->DmSearchResource_ = &DmSearchResource;
    twGlue->DmSeekRecordInCategory_ = &DmSeekRecordInCategory;
    twGlue->DmSet_ = &DmSet;
    twGlue->DmSetDatabaseInfo_ = &DmSetDatabaseInfo;
    twGlue->DmSetRecordInfo_ = &DmSetRecordInfo;
    twGlue->DmSetResourceInfo_ = &DmSetResourceInfo;
    twGlue->DmStrCopy_ = &DmStrCopy;
    twGlue->DmWrite_ = &DmWrite;
    twGlue->DmWriteCheck_ = &DmWriteCheck;

    twGlue->ErrDisplayFileLineMsg_ = &ErrDisplayFileLineMsg;

    twGlue->EvtAddEventToQueue_ = &EvtAddEventToQueue;
    twGlue->EvtDequeuePenPoint_ = &EvtDequeuePenPoint;
    twGlue->EvtEventAvail_ = &EvtEventAvail;
    twGlue->EvtGetEvent_ = &EvtGetEvent;
    twGlue->EvtGetPen_ = &EvtGetPen;
    twGlue->EvtResetAutoOffTimer_ = &EvtResetAutoOffTimer;
    twGlue->EvtSetAutoOffTimer_ = &EvtSetAutoOffTimer;

    twGlue->ExgConnect_ = &ExgConnect;
    twGlue->ExgPut_ = &ExgPut;
    twGlue->ExgGet_ = &ExgGet;
    twGlue->ExgAccept_ = &ExgAccept;
    twGlue->ExgDisconnect_ = &ExgDisconnect;
    twGlue->ExgSend_ = &ExgSend;
    twGlue->ExgReceive_ = &ExgReceive;
    twGlue->ExgControl_ = &ExgControl;
    twGlue->ExgRegisterData_ = &ExgRegisterData;
    twGlue->ExgRegisterDatatype_ = &ExgRegisterDatatype;
    twGlue->ExgNotifyReceive_ = &ExgNotifyReceive;
    twGlue->ExgNotifyGoto_ = &ExgNotifyGoto;
    twGlue->ExgDBRead_ = &ExgDBRead;
    twGlue->ExgDBWrite_ = &ExgDBWrite;
    twGlue->ExgDoDialog_ = &ExgDoDialog;
    twGlue->ExgRequest_ = &ExgRequest;
    twGlue->ExgSetDefaultApplication_ = &ExgSetDefaultApplication;
    twGlue->ExgGetDefaultApplication_ = &ExgGetDefaultApplication;
    twGlue->ExgGetTargetApplication_ = &ExgGetTargetApplication;
    twGlue->ExgGetRegisteredApplications_ = &ExgGetRegisteredApplications;
    twGlue->ExgGetRegisteredTypes_ = &ExgGetRegisteredTypes;
    twGlue->ExgNotifyPreview_ = &ExgNotifyPreview;

    twGlue->ExpCardInfo_ = &ExpCardInfo;
    twGlue->ExpCardInserted_ = &ExpCardInserted;
    twGlue->ExpCardPresent_ = &ExpCardPresent;
    twGlue->ExpCardRemoved_ = &ExpCardRemoved;
    twGlue->ExpSlotEnumerate_ = &ExpSlotEnumerate;

    twGlue->FntAverageCharWidth_ = &FntAverageCharWidth;
    twGlue->FntBaseLine_ = &FntBaseLine;
    twGlue->FntCharHeight_ = &FntCharHeight;
    twGlue->FntCharWidth_ = &FntCharWidth;
    twGlue->FntCharsInWidth_ = &FntCharsInWidth;
    twGlue->FntCharsWidth_ = &FntCharsWidth;
    twGlue->FntDefineFont_ = &FntDefineFont;
    twGlue->FntDescenderHeight_ = &FntDescenderHeight;
    twGlue->FntGetFont_ = &FntGetFont;
    twGlue->FntGetFontPtr_ = &FntGetFontPtr;
    twGlue->FntGetScrollValues_ = &FntGetScrollValues;
    twGlue->FntLineHeight_ = &FntLineHeight;
    twGlue->FntLineWidth_ = &FntLineWidth;
    twGlue->FntSetFont_ = &FntSetFont;
    twGlue->FntWCharWidth_ = &FntWCharWidth;
    twGlue->FntWidthToOffset_ = &FntWidthToOffset;
    twGlue->FntWordWrap_ = &FntWordWrap;
    twGlue->FntWordWrapReverseNLines_ = &FntWordWrapReverseNLines;

    twGlue->FrmDispatchEvent_ = &FrmDispatchEvent;
    twGlue->MenuHandleEvent_ = &MenuHandleEvent;

    twGlue->FtrGet_ = &FtrGet;
    twGlue->FtrPtrFree_ = &FtrPtrFree;
    twGlue->FtrPtrNew_ = &FtrPtrNew;
    twGlue->FtrPtrResize_ = &FtrPtrResize;
    twGlue->FtrSet_ = &FtrSet;
    twGlue->FtrUnregister_ = &FtrUnregister;

    twGlue->KeyCurrentState_ = &KeyCurrentState;
    twGlue->KeySetMask_ = &KeySetMask;

    twGlue->MemCmp_ = &MemCmp;
    twGlue->MemMove_ = &MemMove;
    twGlue->MemSet_ = &MemSet;

    twGlue->MemHandleFree_ = &MemHandleFree;
    twGlue->MemHandleLock_ = &MemHandleLock;
    twGlue->MemHandleNew_ = &MemHandleNew;
    twGlue->MemHandleResize_ = &MemHandleResize;
    twGlue->MemHandleSize_ = &MemHandleSize;
    twGlue->MemHandleUnlock_ = &MemHandleUnlock;

    twGlue->MemPtrFree_ = &MemPtrFree;
    twGlue->MemPtrNew_ = &MemPtrNew;
    twGlue->MemPtrResize_ = &MemPtrResize;
    twGlue->MemPtrSize_ = &MemPtrSize;

    twGlue->PrefGetAppPreferences_ = &PrefGetAppPreferences;
    twGlue->PrefGetPreference_ = &PrefGetPreference;
    twGlue->PrefSetAppPreferences_ = &PrefSetAppPreferences;
    twGlue->PrefSetPreference_ = &PrefSetPreference;

    twGlue->SndSetDefaultVolume_ = &SndSetDefaultVolume;
    twGlue->SndGetDefaultVolume_ = &SndGetDefaultVolume;

    twGlue->SndPlayResource_ = &SndPlayResource;

    twGlue->SndStreamCreate_ = &SndStreamCreate;
    twGlue->SndStreamDelete_ = &SndStreamDelete;
    twGlue->SndStreamGetPan_ = &SndStreamGetPan;
    twGlue->SndStreamGetVolume_ = &SndStreamGetVolume;
    twGlue->SndStreamPause_ = &SndStreamPause;
    twGlue->SndStreamSetPan_ = &SndStreamSetPan;
    twGlue->SndStreamSetVolume_ = &SndStreamSetVolume;
    twGlue->SndStreamStart_ = &SndStreamStart;
    twGlue->SndStreamStop_ = &SndStreamStop;

    twGlue->SysHandleEvent_ = &SysHandleEvent;

    twGlue->SysNotifyBroadcast_ = &SysNotifyBroadcast;
    twGlue->SysNotifyBroadcastDeferred_ = &SysNotifyBroadcastDeferred;
    twGlue->SysNotifyRegister_ = &SysNotifyRegister;
    twGlue->SysNotifyUnregister_ = &SysNotifyUnregister;

    twGlue->SysTaskDelay_ = &SysTaskDelay;

    twGlue->SysUIAppSwitch_ = &SysUIAppSwitch;

    twGlue->TimGetSeconds_ = &TimGetSeconds;
    twGlue->TimGetTicks_ = &TimGetTicks;

    twGlue->StrCopy_ = &StrCopy;
    twGlue->StrNCopy_ = &StrNCopy;
    twGlue->StrCat_ = &StrCat;
    twGlue->StrNCat_ = &StrNCat;
    twGlue->StrLen_ = &StrLen;
    twGlue->StrCompareAscii_ = &StrCompareAscii;
    twGlue->StrCompare_ = &StrCompare;
    twGlue->StrNCompareAscii_ = &StrNCompareAscii;
    twGlue->StrNCompare_ = &StrNCompare;
    twGlue->StrCaselessCompare_ = &StrCaselessCompare;
    twGlue->StrNCaselessCompare_ = &StrNCaselessCompare;
    twGlue->StrToLower_ = &StrToLower;
    twGlue->StrIToA_ = &StrIToA;
    twGlue->StrIToH_ = &StrIToH;
    twGlue->StrLocalizeNumber_ = &StrLocalizeNumber;
    twGlue->StrDelocalizeNumber_ = &StrDelocalizeNumber;
    twGlue->StrChr_ = &StrChr;
    twGlue->StrStr_ = &StrStr;
    twGlue->StrAToI_ = &StrAToI;
    twGlue->StrPrintF_ = &StrPrintF;
    twGlue->StrVPrintF_ = &StrVPrintF;

    twGlue->TxtByteAttr_ = &TxtByteAttr;
    twGlue->TxtCaselessCompare_ = &TxtCaselessCompare;
    twGlue->TxtCharAttr_ = &TxtCharAttr;
    twGlue->TxtCharBounds_ = &TxtCharBounds;
    twGlue->TxtCharEncoding_ = &TxtCharEncoding;
    twGlue->TxtCharIsValid_ = &TxtCharIsValid;
    twGlue->TxtCharSize_ = &TxtCharSize;
    twGlue->TxtCharWidth_ = &TxtCharWidth;
    twGlue->TxtCharXAttr_ = &TxtCharXAttr;
    twGlue->TxtCompare_ = &TxtCompare;
    twGlue->TxtConvertEncoding_ = &TxtConvertEncoding;
    twGlue->TxtEncodingName_ = &TxtEncodingName;
    twGlue->TxtFindString_ = &TxtFindString;
    twGlue->TxtGetChar_ = &TxtGetChar;
    twGlue->TxtGetNextChar_ = &TxtGetNextChar;
    twGlue->TxtGetPreviousChar_ = &TxtGetPreviousChar;
    twGlue->TxtGetTruncationOffset_ = &TxtGetTruncationOffset;
    twGlue->TxtGetWordWrapOffset_ = &TxtGetWordWrapOffset;
    twGlue->TxtMaxEncoding_ = &TxtMaxEncoding;
    twGlue->TxtNameToEncoding_ = &TxtNameToEncoding;
    twGlue->TxtParamString_ = &TxtParamString;
    twGlue->TxtReplaceStr_ = &TxtReplaceStr;
    twGlue->TxtSetNextChar_ = &TxtSetNextChar;
    twGlue->TxtStrEncoding_ = &TxtStrEncoding;
    twGlue->TxtTransliterate_ = &TxtTransliterate;
    twGlue->TxtWordBounds_ = &TxtWordBounds;

    twGlue->VFSCustomControl_ = &VFSCustomControl;
    twGlue->VFSDirCreate_ = &VFSDirCreate;
    twGlue->VFSDirEntryEnumerate_ = &VFSDirEntryEnumerate;
    twGlue->VFSExportDatabaseToFile_ = &VFSExportDatabaseToFile;
    twGlue->VFSExportDatabaseToFileCustom_ = &VFSExportDatabaseToFileCustom;
    twGlue->VFSFileClose_ = &VFSFileClose;
    twGlue->VFSFileCreate_ = &VFSFileCreate;
    twGlue->VFSFileDelete_ = &VFSFileDelete;
    twGlue->VFSFileEOF_ = &VFSFileEOF;
    twGlue->VFSFileGetAttributes_ = &VFSFileGetAttributes;
    twGlue->VFSFileGetDate_ = &VFSFileGetDate;
    twGlue->VFSFileOpen_ = &VFSFileOpen;
    twGlue->VFSFileRead_ = &VFSFileRead;
    twGlue->VFSFileReadData_ = &VFSFileReadData;
    twGlue->VFSFileRename_ = &VFSFileRename;
    twGlue->VFSFileResize_ = &VFSFileResize;
    twGlue->VFSFileSeek_ = &VFSFileSeek;
    twGlue->VFSFileSetAttributes_ = &VFSFileSetAttributes;
    twGlue->VFSFileSetDate_ = &VFSFileSetDate;
    twGlue->VFSFileSize_ = &VFSFileSize;
    twGlue->VFSFileTell_ = &VFSFileTell;
    twGlue->VFSFileWrite_ = &VFSFileWrite;
    twGlue->VFSGetDefaultDirectory_ = &VFSGetDefaultDirectory;
    twGlue->VFSImportDatabaseFromFile_ = &VFSImportDatabaseFromFile;
    twGlue->VFSImportDatabaseFromFileCustom_ = &VFSImportDatabaseFromFileCustom;
    twGlue->VFSInstallFSLib_ = &VFSInstallFSLib;
    twGlue->VFSRegisterDefaultDirectory_ = &VFSRegisterDefaultDirectory;
    twGlue->VFSRemoveFSLib_ = &VFSRemoveFSLib;
    twGlue->VFSUnregisterDefaultDirectory_ = &VFSUnregisterDefaultDirectory;
    twGlue->VFSVolumeEnumerate_ = &VFSVolumeEnumerate;
    twGlue->VFSVolumeFormat_ = &VFSVolumeFormat;
    twGlue->VFSVolumeGetLabel_ = &VFSVolumeGetLabel;
    twGlue->VFSVolumeInfo_ = &VFSVolumeInfo;
    twGlue->VFSVolumeMount_ = &VFSVolumeMount;
    twGlue->VFSVolumeSetLabel_ = &VFSVolumeSetLabel;
    twGlue->VFSVolumeSize_ = &VFSVolumeSize;
    twGlue->VFSVolumeUnmount_ = &VFSVolumeUnmount;

    twGlue->WinClipRectangle_ = &WinClipRectangle;
    twGlue->WinCopyRectangle_ = &WinCopyRectangle;

    twGlue->WinCreateOffscreenWindow_ = &WinCreateOffscreenWindow;
    twGlue->WinCreateWindow_ = &WinCreateWindow;
    twGlue->WinDeleteWindow_ = &WinDeleteWindow;

    twGlue->WinDisableWindow_ = &WinDisableWindow;
    twGlue->WinEnableWindow_ = &WinEnableWindow;

    twGlue->WinGetBounds_ = &WinGetBounds;
    twGlue->WinSetBounds_ = &WinSetBounds;

    twGlue->WinGetPixel_ = &WinGetPixel;
    twGlue->WinGetPixelRGB_ = &WinGetPixelRGB;

    twGlue->WinGetFramesRectangle_ = &WinGetFramesRectangle;
    twGlue->WinGetSupportedDensity_ = &WinGetSupportedDensity;
    twGlue->WinGetWindowFrameRect_ = &WinGetWindowFrameRect;

    twGlue->WinPaintBitmap_ = &WinPaintBitmap;
    twGlue->WinPaintChar_ = &WinPaintChar;
    twGlue->WinPaintChars_ = &WinPaintChars;
    twGlue->WinPaintLine_ = &WinPaintLine;
    twGlue->WinPaintLines_ = &WinPaintLines;
    twGlue->WinPaintPixel_ = &WinPaintPixel;
    twGlue->WinPaintPixels_ = &WinPaintPixels;
    twGlue->WinPaintRectangle_ = &WinPaintRectangle;
    twGlue->WinPaintRectangleFrame_ = &WinPaintRectangleFrame;
    twGlue->WinPaintRoundedRectangleFrame_ = &WinPaintRoundedRectangleFrame;

    twGlue->WinPushDrawState_ = &WinPushDrawState;
    twGlue->WinPopDrawState_ = &WinPopDrawState;

    twGlue->WinRestoreBits_ = &WinRestoreBits;
    twGlue->WinSaveBits_ = &WinSaveBits;

    twGlue->WinScreenGetAttribute_ = &WinScreenGetAttribute;
    twGlue->WinScreenMode_ = &WinScreenMode;

    twGlue->WinScreenLock_ = &WinScreenLock;
    twGlue->WinScreenUnlock_ = &WinScreenUnlock;

    twGlue->WinScrollRectangle_ = &WinScrollRectangle;

    twGlue->WinIndexToRGB_ = &WinIndexToRGB;
    twGlue->WinRGBToIndex_ = &WinRGBToIndex;

    twGlue->WinGetDisplayWindow_ = &WinGetDisplayWindow;

    twGlue->WinGetActiveWindow_ = &WinGetActiveWindow;
    twGlue->WinSetActiveWindow_ = &WinSetActiveWindow;

    twGlue->WinGetDrawWindow_ = &WinGetDrawWindow;
    twGlue->WinSetDrawWindow_ = &WinSetDrawWindow;

    twGlue->WinGetClip_ = &WinGetClip;
    twGlue->WinSetClip_ = &WinSetClip;
    twGlue->WinResetClip_ = &WinResetClip;

    twGlue->WinGetCoordinateSystem_ = &WinGetCoordinateSystem;
    twGlue->WinSetCoordinateSystem_ = &WinSetCoordinateSystem;

    twGlue->WinSetBackColor_ = &WinSetBackColor;
    twGlue->WinSetBackColorRGB_ = &WinSetBackColorRGB;

    twGlue->WinSetForeColor_ = &WinSetForeColor;
    twGlue->WinSetForeColorRGB_ = &WinSetForeColorRGB;

    twGlue->WinSetTextColor_ = &WinSetTextColor;
    twGlue->WinSetTextColorRGB_ = &WinSetTextColorRGB;

    twGlue->WinSetDrawMode_ = &WinSetDrawMode;
    twGlue->WinSetUnderlineMode_ = &WinSetUnderlineMode;

    twGlue->WinSetPattern_ = &WinSetPattern;
    twGlue->WinSetPatternType_ = &WinSetPatternType;

    twGlue->WinScaleCoord_ = &WinScaleCoord;
    twGlue->WinUnscaleCoord_ = &WinUnscaleCoord;

    twGlue->WinScalePoint_ = &WinScalePoint;
    twGlue->WinUnscalePoint_ = &WinUnscalePoint;

    twGlue->WinScaleRectangle_ = &WinScaleRectangle;
    twGlue->WinUnscaleRectangle_ = &WinUnscaleRectangle;

    twGlue->WinDisplayToWindowPt_ = &WinDisplayToWindowPt;
    twGlue->WinWindowToDisplayPt_ = &WinWindowToDisplayPt;

    twGlue->WinGetBitmapDimensions_ = &WinGetBitmapDimensions;

    twGlue->PINGetInputAreaState_ = &PINGetInputAreaState;
    twGlue->PINSetInputAreaState_ = &PINSetInputAreaState;
    twGlue->PINGetInputTriggerState_ = &PINGetInputTriggerState;
    twGlue->PINSetInputTriggerState_ = &PINSetInputTriggerState;

    twGlue->StatHide_ = &StatHide;
    twGlue->StatShow_ = &StatShow;
    twGlue->StatGetAttribute_ = &StatGetAttribute;

    twGlue->SysGetOrientation_ = &SysGetOrientation;
    twGlue->SysSetOrientation_ = &SysSetOrientation;
    twGlue->SysGetOrientationTriggerState_ = &SysGetOrientationTriggerState;
    twGlue->SysSetOrientationTriggerState_ = &SysSetOrientationTriggerState;

    twGlue->TwInputOpen_ = &TwInputOpen;
    twGlue->TwInputClose_ = &TwInputClose;
    twGlue->TwInputActivate_ = &TwInputActivate;
    twGlue->TwInputDeactivate_ = &TwInputDeactivate;
    twGlue->TwInputGetPeriod_ = &TwInputGetPeriod;
    twGlue->TwInputSetPeriod_ = &TwInputSetPeriod;
    twGlue->TwInputGetCapacity_ = &TwInputGetCapacity;
    twGlue->TwInputSetCapacity_ = &TwInputSetCapacity;
    twGlue->TwInputGetFormat_ = &TwInputGetFormat;
    twGlue->TwInputSetFormat_ = &TwInputSetFormat;
    twGlue->TwInputPeek_ = &TwInputPeek;
    twGlue->TwInputRead_ = &TwInputRead;
    twGlue->TwInputPoll_ = &TwInputPoll;
    twGlue->TwInputControl_ = &TwInputControl;

    twGlue->TwDeviceOpen_ = &TwDeviceOpen;
    twGlue->TwDeviceClose_ = &TwDeviceClose;
    twGlue->TwDeviceRead_ = &TwDeviceRead;
    twGlue->TwDeviceWrite_ = &TwDeviceWrite;
    twGlue->TwDeviceGetProperty_ = &TwDeviceGetProperty;
    twGlue->TwDeviceSetProperty_ = &TwDeviceSetProperty;
    twGlue->TwDeviceControl_ = &TwDeviceControl;

    twGlue->TwHighScoreRegister_ = &TwHighScoreRegister;
    twGlue->TwHighScoreUnregister_ = &TwHighScoreUnregister;
    twGlue->TwHighScoreReport_ = &TwHighScoreReport;
    twGlue->TwHighScoreGetSummary_ = &TwHighScoreGetSummary;
    twGlue->TwHighScoreGetDetails_ = &TwHighScoreGetDetails;

    twGlue->TwGfxOpen_ = &TwGfxOpen;
    twGlue->TwGfxClose_ = &TwGfxClose;
    twGlue->TwGfxGetInfo_ = &TwGfxGetInfo;
    twGlue->TwGfxGetMemoryUsage_ = &TwGfxGetMemoryUsage;
    twGlue->TwGfxGetDisplaySurface_ = &TwGfxGetDisplaySurface;
    twGlue->TwGfxInVBlank_ = &TwGfxInVBlank;
    twGlue->TwGfxWaitForVBlank_ = &TwGfxWaitForVBlank;
    twGlue->TwGfxAllocSurface_ = &TwGfxAllocSurface;
    twGlue->TwGfxFreeSurface_ = &TwGfxFreeSurface;
    twGlue->TwGfxSetClip_ = &TwGfxSetClip;
    twGlue->TwGfxGetClip_ = &TwGfxGetClip;
    twGlue->TwGfxGetSurfaceInfo_ = &TwGfxGetSurfaceInfo;
    twGlue->TwGfxLockSurface_ = &TwGfxLockSurface;
    twGlue->TwGfxUnlockSurface_ = &TwGfxUnlockSurface;
    twGlue->TwGfxReadSurface_ = &TwGfxReadSurface;
    twGlue->TwGfxWriteSurface_ = &TwGfxWriteSurface;
    twGlue->TwGfxIsSurfaceReady_ = &TwGfxIsSurfaceReady;
    twGlue->TwGfxBitBlt_ = &TwGfxBitBlt;
    twGlue->TwGfxTransformBlt_ = &TwGfxTransformBlt;
    twGlue->TwGfxDrawPoints_ = &TwGfxDrawPoints;
    twGlue->TwGfxDrawColorPoints_ = &TwGfxDrawColorPoints;
    twGlue->TwGfxDrawLines_ = &TwGfxDrawLines;
    twGlue->TwGfxDrawLineSegments_ = &TwGfxDrawLineSegments;
    twGlue->TwGfxDrawRect_ = &TwGfxDrawRect;
    twGlue->TwGfxFillRect_ = &TwGfxFillRect;
    twGlue->TwGfxDrawSpans_ = &TwGfxDrawSpans;
    twGlue->TwGfxDrawBitmap_ = &TwGfxDrawBitmap;

    twGlue->TwAppStart_ = &TwAppStart;
    twGlue->TwAppStop_ = &TwAppStop;
    twGlue->TwNextEvent_ = &TwNextEvent;

    twGlue->TwGfxGetPalmDisplaySurface_ = &TwGfxGetPalmDisplaySurface;
    twGlue->TwGfxReadSurfaceRegion_ = &TwGfxReadSurfaceRegion;
    twGlue->TwGfxWriteSurfaceRegion_ = &TwGfxWriteSurfaceRegion;
    twGlue->TwGfxAsyncBlt_ = &TwGfxAsyncBlt;
    twGlue->TwGfxTransparentBlt_ = &TwGfxTransparentBlt;
    twGlue->TwGfxMaskBlt_ = &TwGfxMaskBlt;
    twGlue->TwGfxBlendBlt_ = &TwGfxBlendBlt;
    twGlue->TwGfxMaskBlendBlt_ = &TwGfxMaskBlendBlt;
    twGlue->TwGfxStretchBlt_ = &TwGfxStretchBlt;
    twGlue->TwGfxTileBlt_ = &TwGfxTileBlt;

    twGlue->BtLibOpen_ = &BtLibOpen;
    twGlue->BtLibClose_ = &BtLibClose;
    twGlue->BtLibHandleEvent_ = &BtLibHandleEvent;

    twGlue->BtLibRegisterManagementNotification_ = &BtLibRegisterManagementNotification;
    twGlue->BtLibUnregisterManagementNotification_ = &BtLibUnregisterManagementNotification;
    twGlue->BtLibStartInquiry_ = &BtLibStartInquiry;
    twGlue->BtLibCancelInquiry_ = &BtLibCancelInquiry;
    twGlue->BtLibDiscoverSingleDevice_ = &BtLibDiscoverSingleDevice;
    twGlue->BtLibDiscoverMultipleDevices_ = &BtLibDiscoverMultipleDevices;
    twGlue->BtLibGetSelectedDevices_ = &BtLibGetSelectedDevices;
    twGlue->BtLibGetRemoteDeviceName_ = &BtLibGetRemoteDeviceName;
    twGlue->BtLibLinkConnect_ = &BtLibLinkConnect;
    twGlue->BtLibLinkDisconnect_ = &BtLibLinkDisconnect;
    twGlue->BtLibPiconetCreate_ = &BtLibPiconetCreate;
    twGlue->BtLibPiconetDestroy_ = &BtLibPiconetDestroy;
    twGlue->BtLibPiconetUnlockInbound_ = &BtLibPiconetUnlockInbound;
    twGlue->BtLibPiconetLockInbound_ = &BtLibPiconetLockInbound;
    twGlue->BtLibLinkSetState_ = &BtLibLinkSetState;
    twGlue->BtLibLinkGetState_ = &BtLibLinkGetState;
    twGlue->BtLibSetGeneralPreference_ = &BtLibSetGeneralPreference;
    twGlue->BtLibGetGeneralPreference_ = &BtLibGetGeneralPreference;

    twGlue->BtLibSocketCreate_ = &BtLibSocketCreate;
    twGlue->BtLibSocketClose_ = &BtLibSocketClose;
    twGlue->BtLibSocketListen_ = &BtLibSocketListen;
    twGlue->BtLibSocketConnect_ = &BtLibSocketConnect;
    twGlue->BtLibSocketRespondToConnection_ = &BtLibSocketRespondToConnection;
    twGlue->BtLibSocketSend_ = &BtLibSocketSend;
    twGlue->BtLibSocketAdvanceCredit_ = &BtLibSocketAdvanceCredit;
    twGlue->BtLibSocketGetInfo_ = &BtLibSocketGetInfo;

    twGlue->BtLibSdpGetServerChannelByUuid_ = &BtLibSdpGetServerChannelByUuid;
    twGlue->BtLibSdpGetPsmByUuid_ = &BtLibSdpGetPsmByUuid;
    twGlue->BtLibSdpServiceRecordCreate_ = &BtLibSdpServiceRecordCreate;
    twGlue->BtLibSdpServiceRecordDestroy_ = &BtLibSdpServiceRecordDestroy;
    twGlue->BtLibSdpServiceRecordStartAdvertising_ = &BtLibSdpServiceRecordStartAdvertising;
    twGlue->BtLibSdpServiceRecordStopAdvertising_ = &BtLibSdpServiceRecordStopAdvertising;
    twGlue->BtLibSdpServiceRecordSetAttributesForSocket_ = &BtLibSdpServiceRecordSetAttributesForSocket;
    twGlue->BtLibSdpServiceRecordsGetByServiceClass_ = &BtLibSdpServiceRecordsGetByServiceClass;
    twGlue->BtLibSdpServiceRecordMapRemote_ = &BtLibSdpServiceRecordMapRemote;
    twGlue->BtLibSdpServiceRecordGetStringOrUrlLength_ = &BtLibSdpServiceRecordGetStringOrUrlLength;
    twGlue->BtLibSdpServiceRecordGetNumListEntries_ = &BtLibSdpServiceRecordGetNumListEntries;
    twGlue->BtLibSdpServiceRecordGetNumLists_ = &BtLibSdpServiceRecordGetNumLists;
    twGlue->BtLibSdpCompareUuids_ = &BtLibSdpCompareUuids;

    twGlue->BtLibSecurityFindTrustedDeviceRecord_ = &BtLibSecurityFindTrustedDeviceRecord;
    twGlue->BtLibSecurityRemoveTrustedDeviceRecord_ = &BtLibSecurityRemoveTrustedDeviceRecord;
    twGlue->BtLibSecurityGetTrustedDeviceRecordInfo_ = &BtLibSecurityGetTrustedDeviceRecordInfo;
    twGlue->BtLibSecurityNumTrustedDeviceRecords_ = &BtLibSecurityNumTrustedDeviceRecords;
    twGlue->BtLibAddrBtdToA_ = &BtLibAddrBtdToA;
    twGlue->BtLibAddrAToBtd_ = &BtLibAddrAToBtd;

    twGlue->BtLibServiceOpen_ = &BtLibServiceOpen;
    twGlue->BtLibServiceClose_ = &BtLibServiceClose;
    twGlue->BtLibServiceIndicateSessionStart_ = &BtLibServiceIndicateSessionStart;
    twGlue->BtLibServicePlaySound_ = &BtLibServicePlaySound;

    twGlue->zlibVersion_ = &zlibVersion;
    twGlue->deflateInit__ = &deflateInit_;
    twGlue->deflateInit2__ = &deflateInit2_;
    twGlue->deflate_ = &deflate;
    twGlue->deflateEnd_ = &deflateEnd;
    twGlue->inflateInit__ = &inflateInit_;
    twGlue->inflateInit2__ = &inflateInit2_;
    twGlue->inflate_ = &inflate;
    twGlue->inflateEnd_ = &inflateEnd;
    twGlue->deflateSetDictionary_ = &deflateSetDictionary;
    twGlue->deflateCopy_ = &deflateCopy;
    twGlue->deflateReset_ = &deflateReset;
    twGlue->deflateParams_ = &deflateParams;
    twGlue->inflateSetDictionary_ = &inflateSetDictionary;
    twGlue->inflateSync_ = &inflateSync;
    twGlue->inflateReset_ = &inflateReset;
    twGlue->compress_ = &compress;
    twGlue->compress2_ = &compress2;
    twGlue->uncompress_ = &uncompress;
    twGlue->adler32_ = &adler32;
    twGlue->crc32_ = &crc32;

    twGlue->TwGfxDrawPalmBitmap_ = &TwGfxDrawPalmBitmap;
    twGlue->TwGetMicroSeconds_ = &TwGetMicroSeconds;

    twGlue->TimSecondsToDateTime_ = &TimSecondsToDateTime;
    twGlue->TimDateTimeToSeconds_ = &TimDateTimeToSeconds;

    twGlue->TwAppRun_ = &TwAppRun;

    twGlue->TwSemaphoreCreate_ = &TwSemaphoreCreate;
    twGlue->TwSemaphoreDelete_ = &TwSemaphoreDelete;
    twGlue->TwSemaphoreAcquire_ = &TwSemaphoreAcquire;
    twGlue->TwSemaphoreRelease_ = &TwSemaphoreRelease;

    twGlue->TwGetDBDataDirectory_ = &TwGetDBDataDirectory;
    twGlue->TwGetPRCDataDirectory_ = &TwGetPRCDataDirectory;
    twGlue->TwGetSlotNumberForVolume_ = &TwGetSlotNumberForVolume;
    twGlue->TwHighScoreGetTournament_ = &TwHighScoreGetTournament;

    twGlue->NetInit_ = &NetInit;
    twGlue->NetFini_ = &NetFini;

    twGlue->accept_ = &accept;
    twGlue->bind_ = &bind;
    twGlue->closesocket_ = &closesocket;
    twGlue->connect_ = &connect;
    twGlue->getpeername_ = &getpeername;
    twGlue->getsockname_ = &getsockname;
    twGlue->getsockopt_ = &getsockopt;
    twGlue->listen_ = &listen;
    twGlue->poll_ = &poll;
    twGlue->recv_ = &recv;
    twGlue->recvfrom_ = &recvfrom;
    twGlue->send_ = &send;
    twGlue->sendto_ = &sendto;
    twGlue->setsockopt_ = &setsockopt;
    twGlue->shutdown_ = &shutdown;
    twGlue->socket_ = &socket;

    twGlue->gethostbyname_ = &gethostbyname;
    twGlue->gethostbyaddr_ = &gethostbyaddr;

    twGlue->inet_aton_ = &inet_aton;
    twGlue->inet_ntoa_ = &inet_ntoa;

    twGlue->SysBatteryInfo_ = &SysBatteryInfo;
    twGlue->SysGetROMToken_ = &SysGetROMToken;

    twGlue->TwThreadCurrent_ = &TwThreadCurrent;

    twGlue->SndStreamCreateExtended_ = &SndStreamCreateExtended;
    twGlue->SndStreamDeviceControl_ = &SndStreamDeviceControl;

    twGlue->PceNativeCall_ = &PceNativeCall;

    twGlue->TwFindModule_ = &TwFindModule;
    twGlue->TwLoadModule_ = &TwLoadModule;
    twGlue->TwUnloadModule_ = &TwUnloadModule;

    twGlue->TwCreateDatabaseFromImage_ = &TwCreateDatabaseFromImage;
    twGlue->TwGetSlotRefNumForSlot_ = &TwGetSlotRefNumForSlot;
    twGlue->TwGetGraphicForButton_ = &TwGetGraphicForButton;

    twGlue->gunzip_ = &gunzip;
    twGlue->gzip_ = &gzip;

    twGlue->FrmAlert_ = &FrmAlert;
    twGlue->FrmCustomAlert_ = &FrmCustomAlert;

    twGlue->Calloc_ = &Calloc;
    twGlue->Malloc_ = &Malloc;
    twGlue->Realloc_ = &Realloc;
    twGlue->Strdup_ = &Strdup;
    twGlue->Free_ = &Free;

    twGlue->dprintf_ = &dprintf;
    twGlue->TwConfirmQuit_ = &TwConfirmQuit;
    twGlue->TwBatteryState_ = &TwBatteryState;

    twGlue->TwJpgOpenImage_ = &TwJpgOpenImage;
    twGlue->TwJpgSetAbortCheck_ = &TwJpgSetAbortCheck;
    twGlue->TwJpgGetAbortCheck_ = &TwJpgGetAbortCheck;
    twGlue->TwJpgCloseImage_ = &TwJpgCloseImage;
    twGlue->TwJpgGetImageInfo_ = &TwJpgGetImageInfo;
    twGlue->TwJpgDecodeImage_ = &TwJpgDecodeImage;
    twGlue->TwJpgDecodeAndScaleImage_ = &TwJpgDecodeAndScaleImage;
    twGlue->TwJpgDecodeImageToSurface_ = &TwJpgDecodeImageToSurface;
    twGlue->TwJpgDecodeImageToNewSurface_ = &TwJpgDecodeImageToNewSurface;
    twGlue->TwJpgScaleImageBuffer_ = &TwJpgScaleImageBuffer;

    twGlue->TwSecGetFunctions_ = &TwSecGetFunctions;

    twGlue->TwSndGetVolume_ = &TwSndGetVolume;
    twGlue->TwSndSetVolume_ = &TwSndSetVolume;
    twGlue->TwSndSetMute_ = &TwSndSetMute;
    twGlue->TwSndGetMute_ = &TwSndGetMute;
    twGlue->TwSndSetBassBoost_ = &TwSndSetBassBoost;
    twGlue->TwSndGetBassBoost_ = &TwSndGetBassBoost;
    twGlue->TwSndPlaySystemSound_ = &TwSndPlaySystemSound;
    twGlue->TwSndSetAlarmPlaying_ = &TwSndSetAlarmPlaying;

    twGlue->ClipboardAddItem_ = &ClipboardAddItem;
    twGlue->ClipboardAppendItem_ = &ClipboardAppendItem;
    twGlue->ClipboardGetItem_ = &ClipboardGetItem;

    twGlue->FontSelect_ = &FontSelect;

    twGlue->FrmCustomResponseAlert_ = &FrmCustomResponseAlert;
    twGlue->FrmGetActiveForm_ = &FrmGetActiveForm;
    twGlue->FrmGetWindowHandle_ = &FrmGetWindowHandle;

    twGlue->TimeZoneToAscii_ = &TimeZoneToAscii;

    twGlue->AlmGetAlarm_ = &AlmGetAlarm;
    twGlue->AlmSetAlarm_ = &AlmSetAlarm;

    twGlue->DateTemplateToAscii_ = &DateTemplateToAscii;
    twGlue->DateToAscii_ = &DateToAscii;

    twGlue->EvtAddUniqueEventToQueue_ = &EvtAddUniqueEventToQueue;
    twGlue->EvtGetPenNative_ = &EvtGetPenNative;

    twGlue->MemHeapCheck_ = &MemHeapCheck;
    twGlue->MemHeapFreeBytes_ = &MemHeapFreeBytes;
    twGlue->MemHeapSize_ = &MemHeapSize;
    twGlue->MemHeapCompact_ = &MemHeapCompact;
    twGlue->MemHeapScramble_ = &MemHeapScramble;

    twGlue->MemDebugMode_ = &MemDebugMode;
    twGlue->MemSetDebugMode_ = &MemSetDebugMode;

    twGlue->MemHandleOwner_ = &MemHandleOwner;
    twGlue->MemHandleSetOwner_ = &MemHandleSetOwner;

    twGlue->MemPtrOwner_ = &MemPtrOwner;
    twGlue->MemPtrSetOwner_ = &MemPtrSetOwner;

    twGlue->SndDoCmd_ = &SndDoCmd;
    twGlue->SndPlaySmf_ = &SndPlaySmf;
    twGlue->SndPlaySmfResource_ = &SndPlaySmfResource;

    twGlue->SysAppLaunch_ = &SysAppLaunch;

    twGlue->SysErrString_ = &SysErrString;

    twGlue->SysCurAppDatabase_ = &SysCurAppDatabase;

    twGlue->SysGetStackInfo_ = &SysGetStackInfo;

    twGlue->SysStringByIndex_ = &SysStringByIndex;

    twGlue->TimeToAscii_ = &TimeToAscii;
    twGlue->TimTimeZoneToUTC_ = &TimTimeZoneToUTC;
    twGlue->TimUTCToTimeZone_ = &TimUTCToTimeZone;

#if TAPWAVE_API_VERSION >= 0x0203
    twGlue->SysLoadModule_ = &SysLoadModule;
    twGlue->SysUnloadModule_ = &SysUnloadModule;
    twGlue->SysGetEntryAddresses_ = &SysGetEntryAddresses;

    twGlue->TwGfxStretchBlt2_ = &TwGfxStretchBlt2;
    twGlue->TwConvert68KBitmapToNative_ = &TwConvert68KBitmapToNative;
#endif // TAPWAVE_API_VERSION >= 0x0203

#if TAPWAVE_API_VERSION >= 0x0204
    twGlue->TwMpOpen_ = &TwMpOpen;
    twGlue->TwMpClose_ = &TwMpClose;
    twGlue->TwMpHostGame_ = &TwMpHostGame;
    twGlue->TwMpHostInvitePlayer_ = &TwMpHostInvitePlayer;
    twGlue->TwMpGuestAcceptInvitation_ = &TwMpGuestAcceptInvitation;
    twGlue->TwMpHostDisinvitePlayer_ = &TwMpHostDisinvitePlayer;
    twGlue->TwMpHostStartGame_ = &TwMpHostStartGame;
    twGlue->TwMpCancelGame_ = &TwMpCancelGame;
    twGlue->TwMpGetPlayerInfo_ = &TwMpGetPlayerInfo;
    twGlue->TwMpGetNumPlayers_ = &TwMpGetNumPlayers;
    twGlue->TwMpGetAllPlayers_ = &TwMpGetAllPlayers;
    twGlue->TwMpGetNumAcceptedPlayers_ = &TwMpGetNumAcceptedPlayers;
    twGlue->TwMpGetAcceptedPlayers_ = &TwMpGetAcceptedPlayers;
#endif // TAPWAVE_API_VERSION >= 0x0204

#if TAPWAVE_API_VERSION >= 0x0205
    twGlue->TwSmfOpen_ = &TwSmfOpen;
    twGlue->TwSmfClose_ = &TwSmfClose;
    twGlue->TwSmfPlay_ = &TwSmfPlay;
    twGlue->TwSmfIsPlaying_ = &TwSmfIsPlaying;
    twGlue->TwSmfStop_ = &TwSmfStop;
    twGlue->TwMidiOpen_ = &TwMidiOpen;
    twGlue->TwMidiClose_ = &TwMidiClose;
    twGlue->TwMidiNoteOn_ = &TwMidiNoteOn;
    twGlue->TwMidiNoteOff_ = &TwMidiNoteOff;
    twGlue->TwMidiProgramChange_ = &TwMidiProgramChange;
    twGlue->TwMidiPitchBend_ = &TwMidiPitchBend;
    twGlue->TwMidiSysEx_ = &TwMidiSysEx;
    twGlue->TwMidiSetMasterVolume_ = &TwMidiSetMasterVolume;
    twGlue->TwMidiGetMasterVolume_ = &TwMidiGetMasterVolume;
    twGlue->TwMidiGetLimits_ = &TwMidiGetLimits;
    twGlue->TwMidiControlChange_ = &TwMidiControlChange;
    twGlue->TwMidiPlaySmf_ = &TwMidiPlaySmf;
#endif // TAPWAVE_API_VERSION >= 0x0205

#endif /* TAPWAVEGLUE_INTERNAL */

#endif /* __TAPWAVEGLUE_H__ */
