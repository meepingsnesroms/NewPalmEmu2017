/*
 * X-Forge - MultiPlayerExample
 * Copyright 2003 Fathammer Ltd
 *
 * $Id: Packets.h,v 1.2 2003/07/11 12:47:23 lars Exp $
 * $Date: 2003/07/11 12:47:23 $
 * $Revision: 1.2 $
 */

#ifndef PACKETS_H_INCLUDED
#define PACKETS_H_INCLUDED

#include <xfutil/XFuSerializable.h>


enum PACKETTYPE
{
    PACKET_BASE = 0,               // base packet - subclasses by other packets
    PACKET_HANDSHAKE = 1,          // participant sends to initiator once it gets the handleClientAccepted() call
    PACKET_INIT = 2,               // initiator sends to participants to let them know of the game parameters
    PACKET_GAME_STATE_UPDATE = 3,  // update packet for game state (led lights)
    PACKET_DISCONNECT = 4          // inform about disconnection
};


class Packet : public XFuSerializable
{

public:

    Packet()
    {
        mType = PACKET_BASE;
    }

    virtual ~Packet()
    {

    }

    static UINT8 getType(const CHAR8 *aBuffer)
    {
        UINT8 type;
        memcpy(&type, aBuffer, sizeof(UINT8));
        return type;
    }

    //! Serializes this object into the buffer. Returns the length of the data.
    virtual INT32 serialize(CHAR8 *aBuffer, INT32 /*aMaxSize*/)
    {
        writeUINT8(aBuffer + 0, mType);
        return 1;
    }

    //! Deserializes from the data buffer into this object.
    virtual INT32 deserialize(const CHAR8 *aBuffer, INT32 /*aLen*/)
    {
        readUINT8(aBuffer + 0, &mType);
        return 1;
    }

    UINT8 mType;

};


class HandshakePacket : public Packet
{

public:

    HandshakePacket()
    {
        mType = PACKET_HANDSHAKE;
    }

    //! Serializes this object into the buffer. Returns the length of the data.
    virtual INT32 serialize(CHAR8 *aBuffer, INT32 /*aMaxSize*/)
    {
        INT32 headerLen = Packet::serialize(aBuffer, 0);
        return headerLen;
    }

    //! Deserializes from the data buffer into this object.
    virtual INT32 deserialize(const CHAR8 *aBuffer, INT32 aLen)
    {
        INT32 headerLen = Packet::deserialize(aBuffer, aLen);
        return headerLen;
    }

};


class InitPacket : public Packet
{

public:

    InitPacket()
    {
        mType = PACKET_INIT;
    }

    //! Serializes this object into the buffer. Returns the length of the data.
    virtual INT32 serialize(CHAR8 *aBuffer, INT32 /*aMaxSize*/)
    {
        INT32 headerLen = Packet::serialize(aBuffer, 0);
        writeINT8(aBuffer + headerLen + 0, mParticipantCount);
        writeINT8(aBuffer + headerLen + 1, mYourPlayerId);
        return headerLen + 2;
    }

    //! Deserializes from the data buffer into this object.
    virtual INT32 deserialize(const CHAR8 *aBuffer, INT32 aLen)
    {
        INT32 headerLen = Packet::deserialize(aBuffer, aLen);
        readINT8(aBuffer + headerLen + 0, &mParticipantCount);
        readINT8(aBuffer + headerLen + 1, &mYourPlayerId);
        return headerLen + 2;
    }

    INT8 mParticipantCount;
    INT8 mYourPlayerId;

};



class GameStateUpdatePacket : public Packet
{

public:

    GameStateUpdatePacket()
    {
        mType = PACKET_GAME_STATE_UPDATE;
    }

    //! Serializes this object into the buffer. Returns the length of the data.
    virtual INT32 serialize(CHAR8 *aBuffer, INT32 /*aMaxSize*/)
    {
        INT32 headerLen = Packet::serialize(aBuffer, 0);
        writeINT8(aBuffer + headerLen + 0, mPlayerId);
        writeINT8(aBuffer + headerLen + 1, mLedState);
        return headerLen + 2;
    }

    //! Deserializes from the data buffer into this object.
    virtual INT32 deserialize(const CHAR8 *aBuffer, INT32 aLen)
    {
        INT32 headerLen = Packet::deserialize(aBuffer, aLen);
        readINT8(aBuffer + headerLen + 0, &mPlayerId);
        readINT8(aBuffer + headerLen + 1, &mLedState);
        return headerLen + 2;
    }

    INT8 mPlayerId;
    INT8 mLedState;

};


class DisconnectPacket : public Packet
{

public:

    DisconnectPacket()
    {
        mType = PACKET_DISCONNECT;
    }

    //! Serializes this object into the buffer. Returns the length of the data.
    virtual INT32 serialize(CHAR8 *aBuffer, INT32 /*aMaxSize*/)
    {
        INT32 headerLen = Packet::serialize(aBuffer, 0);
        writeINT8(aBuffer + headerLen + 0, mPlayerId);
        return headerLen + 1;
    }

    //! Deserializes from the data buffer into this object.
    virtual INT32 deserialize(const CHAR8 *aBuffer, INT32 aLen)
    {
        INT32 headerLen = Packet::deserialize(aBuffer, aLen);
        readINT8(aBuffer + headerLen + 0, &mPlayerId);
        return headerLen + 1;
    }

    INT8 mPlayerId;

};


#endif //! PACKETS_H_INCLUDED

