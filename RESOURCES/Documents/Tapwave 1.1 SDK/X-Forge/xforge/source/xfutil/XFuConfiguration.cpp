/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFuConfiguration.cpp is the implementation file for the XFuConfiguration
 * class. For more information, see XFuConfiguration.h
 *
 * $Id: XFuConfiguration.cpp,v 1.19 2003/09/23 13:33:42 toni Exp $
 * $Date: 2003/09/23 13:33:42 $
 * $Revision: 1.19 $
 */

#include <xfcore/XFcCore.h>
#include <xfutil/XFuConfiguration.h>


XFuConfiguration * XFuConfiguration::create()
{
    return new XFuConfiguration;
}


XFuConfiguration * XFuConfiguration::create(const CHAR *aFilename)
{
    XFuConfiguration *config = new XFuConfiguration;
    if (config != NULL)
    {
        if (!config->load(aFilename))
        {
            delete config;
            return NULL;
        }
    }
    return config;
}


XFuConfiguration * XFuConfiguration::create(XFcFile *aFile)
{
    XFuConfiguration *config = new XFuConfiguration;
    if (config != NULL)
    {
        if (!config->load(aFile))
        {
            delete config;
            return NULL;
        }
    }
    return config;
}


XFuConfiguration::XFuConfiguration() : mProperties(NULL)
{
}


XFuConfiguration::~XFuConfiguration()
{
    clear();
}


CHAR * XFuConfiguration::get(const CHAR *aKey)
{
    if (mProperties == NULL) return NULL;
    XFcHashtableIterator<XFuStringKey, void *> it = mProperties->find(XFuStringKey(aKey));
    return (it.isValid() ? (CHAR *)it.getValue() : NULL);
}


INT32 XFuConfiguration::getINT32(const CHAR *aKey)
{
    CHAR *value = get(aKey);
    if (value == NULL)
        return 0;
    else
        return XFcStringToolkit::toINT32(value);
}


FLOAT32 XFuConfiguration::getFLOAT32(const CHAR *aKey)
{
    CHAR *value = get(aKey);
    if (value == NULL)
        return 0;
    else
        return XFcStringToolkit::toFLOAT32(value);
}


void XFuConfiguration::put(const CHAR *aKey, const CHAR *aValue)
{
    if (mProperties == NULL || aKey == NULL || aValue == NULL) return;
    CHAR *oldVal = get(aKey);
    if (oldVal != NULL)
    {
        delete[] get(aKey);
        mProperties->remove(XFuStringKey(aKey));
    }
    CHAR *val = XFcStringToolkit::copy(aValue);
    mProperties->put(XFuStringKey(aKey), (void *)val);
}


void XFuConfiguration::clear()
{
    if (mProperties != NULL)
    {
        XFcHashtableIterator<XFuStringKey, void *> it;
        for (it = mProperties->begin(); it != mProperties->end(); ++it)
            delete[] (CHAR *)it.getValue();
        delete mProperties;
        mProperties = NULL;
    }
}


INT XFuConfiguration::load(XFcFile *aFile)
{
    if (aFile == NULL)
        return 0;

    if (mProperties == NULL)
        mProperties = new XFcHashtable<XFuStringKey, void *>;
    if (mProperties == NULL)
        return 0;

    // check length of rest of the file
    INT32 orgFilePos = aFile->tell();
    aFile->seek(0, SEEK_END);
    INT32 fileLen = aFile->tell();
    aFile->seek(orgFilePos, SEEK_SET);

    // read until end of file
    while (aFile->tell() < fileLen)
    {
        // read a line, covert it to 16 bit and remove leading and trailing white spaces
        CHAR8 *buffer8 = buffer8 = readLine(aFile);
        CHAR *buffer = XFcStringToolkit::copy(buffer8);
        CHAR *trimmedBuffer = strDupTrim(buffer);

        // parse the line and add the property key and value to the property hashtable
        processLine(trimmedBuffer);

        delete[] trimmedBuffer;
        delete[] buffer;
        delete[] buffer8;
    }

    return 1;
}


INT XFuConfiguration::load(const CHAR *aFilename)
{
    XFcFile *file = XFcFile::open(aFilename, XFCSTR("rb"));
    if (file == NULL)
        return 0;

    INT result = load(file);
   
    file->close();

    return result;
}


void XFuConfiguration::processLine(const CHAR *aStr)
{
    // valid property definition?
    INT32 len = XFcStringToolkit::getLength(aStr);
    if (len > 0 && aStr[0] != '#')
    {

        // find the first = char
        INT32 valStart = 0;
        while (valStart < len && aStr[valStart] != '=') valStart++;

        if (valStart != len && valStart != 0)
        {

            INT32 i, p;

            CHAR * key = new CHAR[valStart + 1];

            p = 0;
            for (i = 0; i < valStart; i++) key[p++] = aStr[i];
            // find last non white space char of the key
            do --p; while (key[p] == ' ' || key[p] == '\t');
            key[p + 1] = '\0';
            
            // find first non white space char of the value
            do valStart++; while (aStr[valStart] == ' ' || aStr[valStart] == '\t');

            CHAR * val = new CHAR[len - valStart + 1];

            p = 0;
            for (i = valStart; i < len; i++) val[p++] = aStr[i];
            val[p] = '\0';

            put(key, val);

            delete[] key;
            delete[] val;

        }

    }
}


CHAR * XFuConfiguration::strDupTrim(const CHAR *aStr)
{
    INT32 len = XFcStringToolkit::getLength(aStr);

    // find first non white space char
    INT32 start = 0;
    while (start < len && (aStr[start] == ' ' || aStr[start] == '\t'))
        start++;

    // find last non white space char
    INT32 end = len - 1;
    while (end >= 0 && (aStr[end] == ' ' || aStr[end] == '\t'))
        end--;

    CHAR *buf;
    INT32 p = 0;
    if (end == -1)
    {
        // only spaces so the result is an empty string
        buf = new CHAR[1];
    }
    else
    {
        // copy the chars between the first and the last white space
        buf = new CHAR[end - start + 2];
        INT32 i;
        for (i = start; i <= end; i++) buf[p++] = aStr[i];
    }

    buf[p] = '\0';
    return buf;
}


CHAR8 * XFuConfiguration::readLine(XFcFile *aFile)
{
    INT32 currentPos = aFile->tell();

    INT32 count = 0;
    CHAR8 c = 0;

    // find end of line
    while (c != 10)
    {
        if (aFile->read(&c, sizeof(CHAR8), 1) == 0) break;
        count++;
    }

    aFile->seek(currentPos, SEEK_SET);

    // read until end of line
    CHAR8 *buffer = new CHAR8[count + 1];
    if (count > 0) aFile->read(buffer, sizeof(CHAR8), count);

    buffer[count] = '\0';

    // remove trailing CR and LF
    if (count >= 1 && buffer[count - 1] == 10) buffer[count - 1] = '\0';
    if (count >= 2 && buffer[count - 2] == 13) buffer[count - 2] = '\0';

    return buffer;
}

