/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief RIFF Wave loader
 * 
 * $Id: XFuWavLoad.cpp,v 1.8.2.1 2003/12/15 09:26:22 jari Exp $
 * $Date: 2003/12/15 09:26:22 $
 * $Revision: 1.8.2.1 $
 */

#include <xfcore/XFcCore.h>
#include <xfutil/XFuWavLoad.h>


class WavLoaderTempData
{
public:
    XFcFile *mFile;
    INT16 mWavFormat;
    INT16 mChannels;
    INT32 mSamplingRate;
    INT16 mBitsPerSample;
    INT32 mTotalBytes;
    INT32 mTotalSamples;
    void *mData;
};


// All the formats we're even remotely likely to support here:
//#define WAVE_FORMAT_PCM         0x0001
//#define WAVE_FORMAT_ADPCM       0x0002  /*  Microsoft Corporation  */
//#define WAVE_FORMAT_IEEE_FLOAT  0x0003  /*  Microsoft Corporation  */
//                                        /*  IEEE754: range (+1, -1]  */
//                                        /*  32-bit/64-bit format as defined by */
//                                        /*  MSVC++ float/double type */
//#define  WAVE_FORMAT_ALAW       0x0006  /*  Microsoft Corporation  */
//#define  WAVE_FORMAT_MULAW      0x0007  /*  Microsoft Corporation  */
//#define  WAVE_FORMAT_MPEGLAYER3 0x0055  /*  ISO/MPEG Layer3 Format Tag */

// currently this loader only supports 8bit mono PCM data.


static INT loadHeader(WavLoaderTempData &d)
{
    INT32 t; 
    INT32 chunkSize;
    
    d.mFile->read(&t, 4, 1);
    if (t != 0x46464952) return 0; // "RIFF" reversed

    d.mFile->read(&t, 4, 1); // skip file len

    d.mFile->read(&t, 4, 1);
    if (t != 0x45564157) return 0; // "WAVE" reversed

    d.mFile->read(&t, 4, 1);
    if (t != 0x20746d66) return 0; // "fmt " reversed

    d.mFile->read(&chunkSize, 4, 1);

    d.mFile->read(&d.mWavFormat, 2, 1);
    if (!(d.mWavFormat == 0x0001)) return 0; // unsupported format

    d.mFile->read(&d.mChannels, 2, 1);

    d.mFile->read(&d.mSamplingRate, 4, 1);

    d.mFile->read(&t, 4, 1); // skip "avgbytespersec"

    d.mFile->read(&t, 2, 1); // skip "bytespersample"

    d.mFile->read(&d.mBitsPerSample, 2, 1);

    chunkSize -= 2 + 2 + 4 + 4 + 2 + 2;
    
    // skip the rest of the header, if any: 
    // (microsoft PCM has 2 more bytes, bits per sample,
    // which we can figure out already)
    d.mFile->seek(d.mFile->tell() + chunkSize, SEEK_SET);
    
    return 1;
}

//#define PANIC(x) XFcCore::systemPanic(x);
#define PANIC(x)

XFcAudioBuffer * xfuLoadWav(const CHAR *aFilename, UINT32 aFlags)
{
    WavLoaderTempData d;
    
    d.mData = NULL;
    d.mFile = XFcFile::open(aFilename, XFCSTR("rb"));

    if (d.mFile == NULL) 
    {
    	PANIC("LoadWav:File not found");
    	return NULL;
   	}

    if (!loadHeader(d)) 
    {
        d.mFile->close();
    	PANIC("LoadWav:Bad header");
        return NULL;
    }

    aFlags &= ~(XFCAUDIO_16BIT | XFCAUDIO_STEREO);

    if (d.mBitsPerSample == 16) aFlags |= XFCAUDIO_16BIT;
    if (d.mChannels == 2) aFlags |= XFCAUDIO_STEREO;

    INT32 tgtXor = 0;
    if (aFlags & XFCAUDIO_SIGNED)
    {
        if (!(aFlags & XFCAUDIO_16BIT)) tgtXor = -128;
    }
    else
        if (aFlags & XFCAUDIO_16BIT) tgtXor = -32768;

    XFcAudioBuffer *sndBuf = NULL;
    INT dataFound = 0;
    INT32 chunkId;
    INT32 index = 0;
    // while not end of file
    while (d.mFile->read(&chunkId, 4, 1) && !dataFound) 
    {
        INT32 chunkSize;
        d.mFile->read(&chunkSize, 4, 1);

        if (chunkId == 0x61746164 && d.mData == NULL)
        {
            d.mTotalBytes = chunkSize;
            d.mTotalSamples = d.mTotalBytes / (d.mChannels * (d.mBitsPerSample / 8));

            sndBuf = XFcAudioBuffer::create((FLOAT32)d.mSamplingRate, aFlags, d.mTotalSamples, 1.0, 0.5);
            if (sndBuf == NULL) 
            {
		    	PANIC("LoadWav:Sound buffer alloc failed");
                d.mFile->close();
                return NULL;
            }

            dataFound = 1;

            if (d.mBitsPerSample == 8)     // Sound is 8-bit
            {
                INT8 *buf = (INT8 *)XFcAudio::lock(sndBuf);
                UINT8 value;

                if (d.mChannels == 1)   // Sound is 8-bit mono
                {
                    while (index < d.mTotalSamples)
                    {
                        d.mFile->readUINT8(value);
                        buf[index] = (INT8)(value ^ tgtXor);
                        index++;
                    }
                }
                else    // Sound is 8-bit stereo
                {
                    while (index < d.mTotalSamples)
                    {
                        d.mFile->readUINT8(value);
                        buf[(index * 2)] = (INT8)(value ^ tgtXor);

                        d.mFile->readUINT8(value);
                        buf[(index * 2) + 1] = (INT8)(value ^ tgtXor);

                        index++;
                    }
                }

                XFcAudio::unlock(sndBuf);
            }
            else    // Sound is 16-bit
            {
                INT16 *buf = (INT16 *)XFcAudio::lock(sndBuf);
                INT16 value;

                if (d.mChannels == 1)   // Sound is 16-bit mono
                {
                    while (index < d.mTotalSamples)
                    {
                        d.mFile->readINT16(value);
                        buf[index] = (INT16)(value ^ tgtXor);
                        index++;
                    }
                }
                else    // Sound is 16-bit stereo
                {
                    while (index < d.mTotalSamples)
                    {
                        d.mFile->readINT16(value);
                        buf[(index * 2)] = (INT16)(value ^ tgtXor);

                        d.mFile->readINT16(value);
                        buf[(index * 2) + 1] = (INT16)(value ^ tgtXor);

                        index++;
                    }
                }

                XFcAudio::unlock(sndBuf);
            }
        }
        else
        {
            // skip chunk:
            d.mFile->seek(d.mFile->tell() + chunkSize, SEEK_SET);
        }
    }

    d.mFile->close();

    if (!dataFound)
    {
    	PANIC("LoadWav:No data block");
        delete sndBuf;
        return NULL;
    }

    return sndBuf;
}


XFcAudioBuffer * xfuLoadWav(const CHAR *filename)
{
    return xfuLoadWav(filename, 0);
}

