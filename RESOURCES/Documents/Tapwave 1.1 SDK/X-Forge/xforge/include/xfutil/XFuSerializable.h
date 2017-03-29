/*!
 * \file
 * X-Forge Engine <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Base class for classes that need to be able to serialize and deserialize.
 *
 * $Id: XFuSerializable.h,v 1.2 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.2 $
 */

#ifndef XFUSERIALIZABLE_H_INCLUDED
#define XFUSERIALIZABLE_H_INCLUDED


//! Base class for classes that need to be able to serialize and deserialize.
class XFuSerializable
{

public:

    //! Virtual destructor
    virtual ~XFuSerializable() {}

    //! Serializes this object into the buffer. Returns the length of the data.
    virtual INT32 serialize(CHAR8 *aBuffer, INT32 aMaxSize) = 0;

    //! Deserializes from the data buffer into this object. Returns length of handled data.
    virtual INT32 deserialize(const CHAR8 *aBuffer, INT32 aLen) = 0;

protected:

    // For reading data from a buffer:

    void readCHAR8(const CHAR8 *aBuffer, CHAR8 *aVal) { memcpy(aVal, aBuffer, sizeof(CHAR8)); }
    void readCHAR16(const CHAR8 *aBuffer, CHAR16 *aVal) { memcpy(aVal, aBuffer, sizeof(CHAR16)); }

    void readINT(const CHAR8 *aBuffer, INT *aVal) { readINT32(aBuffer, aVal); }

    void readINT8(const CHAR8 *aBuffer, INT8 *aVal) { memcpy(aVal, aBuffer, sizeof(INT8)); }
    void readUINT8(const CHAR8 *aBuffer, UINT8 *aVal) { memcpy(aVal, aBuffer, sizeof(UINT8)); }

    void readINT16(const CHAR8 *aBuffer, INT16 *aVal) { memcpy(aVal, aBuffer, sizeof(INT16)); }
    void readUINT16(const CHAR8 *aBuffer, UINT16 *aVal) { memcpy(aVal, aBuffer, sizeof(UINT16)); }

    void readINT32(const CHAR8 *aBuffer, INT32 *aVal) { memcpy(aVal, aBuffer, sizeof(INT32)); }
    void readUINT32(const CHAR8 *aBuffer, UINT32 *aVal) { memcpy(aVal, aBuffer, sizeof(UINT32)); }

    void readREAL(const CHAR8 *aBuffer, REAL *aVal) { memcpy(aVal, aBuffer, sizeof(REAL)); }

    void readFLOAT32(const CHAR8 *aBuffer, FLOAT32 *aVal) { memcpy(aVal, aBuffer, sizeof(FLOAT32)); }

    // For writing data to a buffer:

    void writeCHAR8(CHAR8 *aBuffer, CHAR8 aVal) { memcpy(aBuffer, &aVal, sizeof(CHAR8)); }
    void writeCHAR16(CHAR8 *aBuffer, CHAR16 aVal) { memcpy(aBuffer, &aVal, sizeof(CHAR16)); }

    void writeINT(CHAR8 *aBuffer, INT aVal) { writeINT32(aBuffer, aVal); }

    void writeINT8(CHAR8 *aBuffer, INT8 aVal) { memcpy(aBuffer, &aVal, sizeof(INT8)); }
    void writeUINT8(CHAR8 *aBuffer, UINT8 aVal) { memcpy(aBuffer, &aVal, sizeof(UINT8)); }

    void writeINT16(CHAR8 *aBuffer, INT16 aVal) { memcpy(aBuffer, &aVal, sizeof(INT16)); }
    void writeUINT16(CHAR8 *aBuffer, UINT16 aVal) { memcpy(aBuffer, &aVal, sizeof(UINT16)); }

    void writeINT32(CHAR8 *aBuffer, INT32 aVal) { memcpy(aBuffer, &aVal, sizeof(INT32)); }
    void writeUINT32(CHAR8 *aBuffer, UINT32 aVal) { memcpy(aBuffer, &aVal, sizeof(UINT32)); }

    void writeREAL(CHAR8 *aBuffer, REAL aVal) { memcpy(aBuffer, &aVal, sizeof(REAL)); }

    void writeFLOAT32(CHAR8 *aBuffer, FLOAT32 aVal) { memcpy(aBuffer, &aVal, sizeof(FLOAT32)); }

};


#endif // !XFUSERIALIZABLE_H_INCLUDED

