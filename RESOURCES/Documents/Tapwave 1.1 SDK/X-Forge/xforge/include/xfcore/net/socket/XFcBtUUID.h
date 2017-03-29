/*
 * \file
 * X-Forge Engine <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief
 *
 * $Id: XFcBtUUID.h,v 1.1 2003/09/17 11:09:57 slehti Exp $
 * $Date: 2003/09/17 11:09:57 $
 * $Revision: 1.1 $
 */

#ifndef XFCBTUUID_H_INCLUDED
#define XFCBTUUID_H_INCLUDED


// {7D97B361-6221-4459-9241-227576CC6AB8}
//static const BtLibSdpUuidType kRfCommUUID = {btLibUuidSize128,
//                                             { 0x7d, 0x97, 0xb3, 0x61, 0x62, 0x21, 0x44, 0x59, 0x92, 0x41, 
//                                               0x22, 0x75, 0x76, 0xcc, 0x6a, 0xb8 } };


#include <xfcore/net/socket/XFcUUID.h>

class XFcBtUUID : public XFcUUID
{
private:
    
public:
    // 128 bit uuid.
    UINT8 UUID[16];

    //! Constructor for uuid.
    /*!
     * \param aUuidHighHigh is highest order word (bits 96 - 127).
     * \param aUuidHighLow is second highest order word (bits 64 - 95).
     * \param aUuidLowHigh is second lowset order word (bits 32 - 63).
     * \param aUuidLowLow is low order word (bits 0 - 31).
     */
    XFcBtUUID(UINT32 aUuidHighHigh, UINT32 aUuidHighLow, UINT32 aUuidLowHigh, UINT32 aUuidLowLow)
        {   
            UUID[15] = (UINT8) (aUuidHighHigh >> 24);
            UUID[14] = (UINT8) ((aUuidHighHigh >> 16) & 0xff);
            UUID[13] = (UINT8) ((aUuidHighHigh >> 8) & 0xff);
            UUID[12] = (UINT8) (aUuidHighHigh & 0xff);

            UUID[11] = (UINT8) (aUuidHighLow >> 24);
            UUID[10] = (UINT8) ((aUuidHighLow >> 16) & 0xff);
            UUID[9] = (UINT8) ((aUuidHighLow >> 8) & 0xff);
            UUID[8] = (UINT8) (aUuidHighLow & 0xff);

            UUID[7] = (UINT8) (aUuidLowHigh >> 24);
            UUID[6] = (UINT8) ((aUuidLowHigh >> 16) & 0xff);
            UUID[5] = (UINT8) ((aUuidLowHigh >> 8) & 0xff);
            UUID[4] = (UINT8) (aUuidLowHigh & 0xff);

            UUID[3] = (UINT8) (aUuidLowLow >> 24);
            UUID[2] = (UINT8) ((aUuidLowLow >> 16) & 0xff);
            UUID[1] = (UINT8) ((aUuidLowLow >> 8) & 0xff);
            UUID[0] = (UINT8) (aUuidLowLow & 0xff);        
        }
    
    XFcBtUUID()
        {
        }
    
    virtual ~XFcBtUUID()
        {
        }
};

#endif // XFCBTUUID_H_INCLUDED
    
