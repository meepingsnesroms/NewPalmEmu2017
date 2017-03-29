 /*
	File:			JpegLoader.h	

	Description:	Jpeg loader class description.

	Author:		

	Copyright:		Copyright © 2003 by Tapwave, Inc.

	Disclaimer:		IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
					use is subject to and governed by terms and conditions of the Software Development 
					Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
					into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
					to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
					You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
					or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

#ifndef JpegLoader_h___
#define JpegLoader_h___

// A simple sample utility class that manages loading a jpeg image from a resource into a TwGfx
// surface.

class JpegLoader {
public:
    static Err LoadJpeg(TwGfxType* aLib, UInt16 aResID, TwGfxSurfaceType** aSurfaceResult,
                        TwJpgImageInfoType* aInfoResult) {
        JpegLoader* loader = new JpegLoader();
        Err err = loader->Load(aLib, aResID, aSurfaceResult, aInfoResult);
        delete loader;
        return err;
    }

protected:
    JpegLoader() {
        mJpgData = NULL;
        mJpgSize = 0;
        mOffset = 0;
    }

    Err Load(TwGfxType* aLib, UInt16 aResID, TwGfxSurfaceType** aSurfaceResult,
             TwJpgImageInfoType* aInfoResult) {
        if (!aSurfaceResult) {
            return sysErrParamErr;
        }

        Err err = errNone;
        TwGfxSurfaceType* surf = NULL;
        MemHandle jpegResHandle = DmGet1Resource('JPEG', aResID);
        if (jpegResHandle) {
            mJpgData = (char*) MemHandleLock(jpegResHandle);
            mJpgSize = MemHandleSize(jpegResHandle);
            mOffset = 0;

            TwJpgImageInfoType info;
            if (!aInfoResult) {
                aInfoResult = &info;
            }
            aInfoResult->size = sizeof(info);

            TwJpgImageType* img = NULL;
            do {
                err = TwJpgOpenImage(&img, JpgMemReader, (void*) this);
                if (err) {
                    ErrDisplayFileLineMsg("JpegLoader", (UInt16) err, "TwJpgOpenImage failed");
                    break;
                }

                err = TwJpgGetImageInfo(img, aInfoResult);
                if (err) {
                    ErrDisplayFileLineMsg("JpegLoader", (UInt16) err, "TwJpgGetImageInfo failed");
                    break;
                }

                TwGfxSurfaceInfoType surfInfo;
                surfInfo.size = sizeof(surfInfo);
                surfInfo.width = aInfoResult->width;
                surfInfo.height = aInfoResult->height;
                surfInfo.location = twGfxLocationAcceleratorMemory;
                surfInfo.pixelFormat = twGfxPixelFormatRGB565;
                err = TwGfxAllocSurface(aLib, &surf, &surfInfo);
                if (err) {
                    ErrDisplayFileLineMsg("JpegLoader", (UInt16) err, "TwGfxAllocSurface failed");
                    break;
                }

                err = TwJpgDecodeImageToSurface(img, false, surf);
                if (err) {
                    ErrDisplayFileLineMsg("JpegLoader", (UInt16) err, "TwJpgDecodeImageToSurface failed");
                    TwGfxFreeSurface(surf);
                    break;
                }
                break;
            } while (0);

            if (img) {
                TwJpgCloseImage(img);
            }
            MemHandleUnlock(jpegResHandle);
            DmReleaseResource(jpegResHandle);
        }
        else {
            // Can't find that resource
            err = dmErrCantFind;
        }

        *aSurfaceResult = surf;
        return err;
    }

    // Callback used by the jpeg library to read more data for decoding the jpeg
    static Int32 JpgMemReader(void* aHandle, void* aBuffer, UInt32 aAmount) {
        JpegLoader* loader = (JpegLoader*) aHandle;

        UInt32 count = aAmount;
        UInt32 remainder = loader->mJpgSize - loader->mOffset;
        if (count > remainder) {
            count = remainder;
        }

        if (count) {
            memcpy(aBuffer, loader->mJpgData + loader->mOffset, count);
            loader->mOffset += count;
        }

        return count;
    }

    char* mJpgData;
    UInt32 mJpgSize;
    UInt32 mOffset;
};

#endif /* JpegLoader_h___ */
