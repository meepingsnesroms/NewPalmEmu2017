/*
	File:			utils.c

	Description:	Utility Functions

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

#include <TapWave.h>
#include "utils.h"

#if defined(__arm) && CPU_TYPE == CPU_68K
#error fix me
#endif

#if CPU_TYPE == CPU_68K
#define LittleEndianSwap16(x) \
	((((x) >> 8) & 0xFF) | \
	 (((x) & 0xFF) << 8))
#else
#define LittleEndianSwap16(x) \
    (x)
#endif

typedef struct 
{
	UInt16   signature;
	UInt16   _pad_;
	UInt32   size;
	UInt32   reserved;
	UInt32   dataOffset;
} BitmapFileHeader;

typedef struct 
{
	UInt32	sizeInfoHeader;
	UInt32	width;
	UInt32	height;
	UInt16	planes;
	UInt16	bitCount;
	UInt32	compression;
	UInt32	sizeGlyph;
	UInt32	xPixelsPerM;
	UInt32	yPixelsPerM;
	UInt32	colorsUsed;
	UInt32	colorsImportant;
} BitmapInfoHeader;

#if defined(__arm) || defined(_MSC_VER)
#define ENDIAN '<'
#else
#define ENDIAN '>'
#endif

const char*
pack(const char* format, char* buf, const void* source)
{
    int bswap = 0;
    const char* src = (char*) source;

    for (;;) {
        char ch = *format++;
        switch (ch) {
        case 0:
            return src;
        case '<': case '>':
            bswap = (ch != ENDIAN);
            continue;
        case '=':
            bswap = 0;
            continue;
        case '!':
            bswap = 1;
            continue;
        case 'b': case 'B':
            *buf++ = *src++;
            continue;
        case 'h': case 'H':
            if (bswap) {
                buf[1] = src[0];
                buf[0] = src[1];
            } else {
                buf[0] = src[0];
                buf[1] = src[1];
            }
            buf += 2;
            src += 2;
            continue;
        case 'i': case 'I': case 'f':
            if (bswap) {
                buf[3] = src[0];
                buf[2] = src[1];
                buf[1] = src[2];
                buf[0] = src[3];
            } else {
                buf[0] = src[0];
                buf[1] = src[1];
                buf[2] = src[2];
                buf[3] = src[3];
            }
            buf += 4;
            src += 4;
            continue;
        case 'l': case 'L': case 'd':
            if (bswap) {
                buf[7] = src[0];
                buf[6] = src[1];
                buf[5] = src[2];
                buf[4] = src[3];
                buf[3] = src[4];
                buf[2] = src[5];
                buf[1] = src[6];
                buf[0] = src[7];
            } else {
                buf[0] = src[0];
                buf[1] = src[1];
                buf[2] = src[2];
                buf[3] = src[3];
                buf[0] = src[4];
                buf[1] = src[5];
                buf[2] = src[6];
                buf[3] = src[7];
            }
            buf += 4;
            src += 4;
            continue;
        case 'x':
            buf += 1;
            continue;
        case 'X':
            buf -= 1;
            continue;
        case 'y':
            src += 1;
            continue;
        case 'Y':
            src -= 1;
            continue;
		case ' ': case ',':
			continue;
        default:
            DbgBreak();
            continue;
        }
    }

	return src;
}


extern Err
AppReadBMP(TwGfxType* aGfx,
    TwGfxSurfaceType** aResult,
    const void * dataP,
    Int32 dataSize)
{
    TwGfxSurfaceInfoType surfDesc;
    int compression;
    int row;
    int column;
    Int32 sourceBytesPerRow;
    Err error;
	BitmapFileHeader fileHeader;
	BitmapInfoHeader infoHeader;
	const void * p = dataP;
	const void * newDataP = NULL;
	int red;
	int green;
	int blue;
    
	// unpack the fileHeader structure.  This is to solve alignment differences on
	// 68K, x86, and ARM.
	p = pack("<hxxiii", (char*)&fileHeader, (const char*)p);
	pack("<iiihhiiiiii", (char*)&infoHeader, (const char*)p);
    
	if (fileHeader.signature != 'MB' && fileHeader.signature != 'BM') return 1; // 'BM' for 68K
	
    surfDesc.size = sizeof(surfDesc);
    surfDesc.width = (Int32) infoHeader.width;
    surfDesc.height = (Int32) infoHeader.height;
    surfDesc.location = twGfxLocationAcceleratorMemory;
    
    compression = (int) infoHeader.compression;
    
    sourceBytesPerRow = (((infoHeader.bitCount * surfDesc.width + 7) / 8 + 3) / 4) * 4;
    
    switch (infoHeader.bitCount)
    {
        case 16:
            surfDesc.pixelFormat = twGfxPixelFormatRGB565;
            error = TwGfxAllocSurface(aGfx, aResult, &surfDesc);
            
            // 16 bit glyphs can not be compressed.
            if (compression == 0)
            {
                UInt8 *pixelsDestP;
                UInt8 *pixelsSourceP;
                UInt16 *destP;
                UInt16 *sourceP;
                
                // The data must be converted to 565 RGB.
                pixelsDestP = (UInt8 *) MemPtrNew((UInt32) (surfDesc.rowBytes * surfDesc.height));
                pixelsSourceP = (UInt8 *) dataP + fileHeader.dataOffset;
                
                for (row = 0; row < surfDesc.height; row++)
                {
                    destP = (UInt16 *) (pixelsDestP + row * surfDesc.rowBytes);
                    sourceP = (UInt16 *) (pixelsSourceP + 
                        ((surfDesc.height - 1) - row) * sourceBytesPerRow);
                    
                    for (column = 0; column < surfDesc.width; column++)
                    {
                        // Convert from 555 to 565.
                        *destP = *sourceP & 31 | ((*sourceP & (0x7fff ^ 31)) << 1);
                        destP++;
                        sourceP++;
                    }
                }
                
                // The data may really be padded out to 32 bit boundaries.
                error = TwGfxWriteSurface(*aResult, pixelsDestP, false);
                MemPtrFree(pixelsDestP);
            }
            else if (compression == 3)
            {
                // DOLATER
                // Convert RGB from the bitmasks in RGBQUAD
            }
            break;
            
        case 24:
            surfDesc.pixelFormat = twGfxPixelFormatRGB565;
            error = TwGfxAllocSurface(aGfx, aResult, &surfDesc);
			if (0) //HostGetHostID() == hostIDPalmOS)
			{
	            // round up to 8
	            surfDesc.rowBytes += 7;
	            surfDesc.rowBytes -= surfDesc.rowBytes % 8;
			}
			            
            // 24 bit glyphs can not be compressed.
            if (compression == 0)
            {
                UInt8 *pixelsDestP;
                UInt8 *pixelsSourceP;
                UInt16 *destP;
                UInt8 *sourceP;
                UInt16 pixel;
                
                // The data must be converted to 565 RGB.
                pixelsDestP = MemPtrNew((UInt32) (surfDesc.rowBytes * surfDesc.height));
                pixelsSourceP = (UInt8 *) dataP + fileHeader.dataOffset;
                
                for (row = 0; row < surfDesc.height; row++)
                {
                    destP = (UInt16 *) (pixelsDestP + row * surfDesc.rowBytes);
                    sourceP = pixelsSourceP + ((surfDesc.height - 1) - row) * sourceBytesPerRow;
                    
                    for (column = 0; column < surfDesc.width; column++)
                    {
                        // Convert from BGR 888 to RGB 565.
#if 1
                        blue = *sourceP++;
                        green = *sourceP++;
                        red = *sourceP++;
                        pixel = TwGfxMakeDisplayRGB(red, green, blue);
#else
                        pixel = (UInt16) (*sourceP++ >> 3);
                        pixel |= (UInt16) ((*sourceP++ >> 2) << 5);
                        pixel |= (UInt16) ((*sourceP++ >> 3) << 11);
#endif
                        pixel = LittleEndianSwap16(pixel);
                        *destP++ = pixel;
                    }
                }
                
                // The data may really be padded out to 32 bit boundaries.
                error = TwGfxWriteSurface(*aResult, pixelsDestP, false);
                MemPtrFree(pixelsDestP);
            }
            else if (compression == 3)
            {
                // DOLATER - 
                // Convert RGB from the bitmasks in RGBQUAD
            }
            break;
    }
    
    if (newDataP != NULL)
    	MemPtrFree((void *) newDataP);
        	
    return error;
    
}

typedef struct
{
    Coord x;
    Coord y;
    Coord width;
} FontCharDataType;

typedef struct
{
    TwGfxSurfaceType * fontGlyphs;
    UInt16 fontColorBorder;
    TwGfxPackedRGBType fontColorBackground;
    Coord lineHeight;
    FontCharDataType chars[128];
} FontInfoType;

static FontInfoType FontInfo;

// Those wanting more info on font formats in general would enjoy reading
// http://pfaedit.sourceforge.net/
// http://freetype.sourceforge.net/index2.html 
// and especially http://freetype.sourceforge.net/freetype2/docs/glyphs/glyphs-7.html

extern Err
FontInit(TwGfxType* aGfx)
{
    Err error;
    UInt16 * glyphP;
    TwGfxSurfaceInfoType surfInfo;
    Int32 rowWords;
    Coord rootX;
    Coord rootY;
    Coord x;
    Coord y;
    MemHandle fontGlyphsH;
    void * fontGlyphsP;
    void * fontGlyphsUncompressedP = NULL;
    Int32 imageSize;
    int row;
    int column;
    int c;
    

//    return errNone;

    fontGlyphsH = DmGetResource('BMPf', 1000);
    fontGlyphsP = MemHandleLock(fontGlyphsH);

    imageSize = MemHandleSize(fontGlyphsH);
    
    // Some of the images are compressed using gzip.  BMP images > 256 colors
    // are not compressed.  GZip is quite effective, quick and portable and makes a 
    // good choice.
    fontGlyphsUncompressedP = gunzip(fontGlyphsP, imageSize);
    
    error = AppReadBMP(aGfx, &FontInfo.fontGlyphs, 
        fontGlyphsUncompressedP == NULL ? fontGlyphsP : fontGlyphsUncompressedP, imageSize);
    
    if (fontGlyphsUncompressedP != NULL)
        MemPtrFree(fontGlyphsUncompressedP);
    
    MemHandleUnlock(fontGlyphsH);
    DmReleaseResource(fontGlyphsH);
    
    TwGfxLockSurface(FontInfo.fontGlyphs, (void**)&glyphP);
    surfInfo.size = sizeof(surfInfo);
    error = TwGfxGetSurfaceInfo(FontInfo.fontGlyphs, &surfInfo);
    rowWords = (int) surfInfo.rowBytes / 2;
    
    FontInfo.fontColorBorder = *glyphP; 
    
    // Scan for the root x, y;
    rootX = 0;
    rootY = 0;
    while (glyphP[rootX + rootY * rowWords] == FontInfo.fontColorBorder)
    {
        rootX++;
        rootY++;
    }
    FontInfo.fontColorBackground = TwGfxDisplayRGBToPackedRGB(
    	glyphP[rootX + rootY * rowWords]);
    
    // Find the height.  The height of all chars is assumed to the same, and the
    // chars are positioned as desired within the vertical space.
    // Find the right border.
    y = rootY;
    while (glyphP[rootX + y * rowWords] != FontInfo.fontColorBorder)
    {
        y++;
    }
    FontInfo.lineHeight = (y - 1 - rootY + 1);
    
    // Skip the border
    x = rootX;
    while (glyphP[x + rootY * rowWords] == FontInfo.fontColorBorder)
    {
        x++;
    }
    
    
    // scan through the glyph picking out characters and adding them to the 
    // tables for quick access.
    for (row = 2; row < 8; row++)
    {
        x = rootX;
        y = rootY + (FontInfo.lineHeight + rootY) * (row - 2);
        
        for (column = 0; column < 16; column++)
        {
            c = row * 16 + column;
            
            // All characters are fully boxed so that bounds can easily be determined.
            // Top
            FontInfo.chars[c].x = x;
            FontInfo.chars[c].y = y;
            
            // Find the right border.
            while (glyphP[x + y * rowWords] != FontInfo.fontColorBorder)
            {
                x++;
            }
            FontInfo.chars[c].width = x - FontInfo.chars[c].x;
            
            // Skip the border
            while (glyphP[x + y * rowWords] == FontInfo.fontColorBorder &&
                x < surfInfo.width)
            {
                x++;
            }
        }
    }
    
    TwGfxUnlockSurface(FontInfo.fontGlyphs, true);
    
    return error;
}


extern Int16
FontGetLineHeight()
{
    if (FontInfo.fontGlyphs != NULL)
        return FontInfo.lineHeight;
    
    return 0;
}


extern Int16
FontGetCharWidth(char c)
{
    if (FontInfo.fontGlyphs != NULL)
        return FontInfo.chars[c].width;
    
    return 0;
}


extern void
FontGetCharsInWidth(const char * s, 
    Int32 * lengthP, //! pass in the length, the length that fits is returned
    Int32 * widthP,  //! pass in the width, the width used is returned.
    char * truncationCharP //! pass in the truncation char, the char (if any) used
    )
{
    Int32 width = 0;
    Int32 length = *lengthP;
    Int32 truncationWidth;
    Int32 charWidth;
    Int32 truncationLength = 0;
    
    if (*widthP == 0)
        *widthP = 0x7fff;
    
    truncationWidth = *widthP;
    if (truncationCharP != NULL)
        truncationWidth -= FontGetCharWidth(*truncationCharP);
    
    if (FontInfo.fontGlyphs != NULL)
    {
        while (length > 0 && width < *widthP)
        {
            if (0x20 <= *s && *s <= 0x7f)
            {
                charWidth = FontGetCharWidth(*s);
                if (width + charWidth <= *widthP)
                    width += charWidth;
                else
                    break;
                
                // If the char can be added without exceeding the truncation area, do so
                if (width <= truncationWidth)
                    truncationLength++;
            }
            s++;
            length--;
        }
        
        if (width <= truncationWidth && truncationCharP != NULL)
            *truncationCharP = '\0';
    }
    
    *widthP = width;
    *lengthP -= length;
}


Int32
FontDrawChars(const char * s, Int32 length, TwGfxSurfaceType * destSurface, Int32 x, Int32 y)
{
    Int32 width = 0;
    TwGfxRectType sourceBounds;
    TwGfxPointType destPoint;
    
    if (FontInfo.fontGlyphs != NULL)
    {
        destPoint.x = x;
        destPoint.y = y;
        
        sourceBounds.h = FontInfo.lineHeight;
        
        while (length > 0)
        {
            if (0x20 <= *s && *s <= 0x7f)
            {
                sourceBounds.x = FontInfo.chars[*s].x;
                sourceBounds.y = FontInfo.chars[*s].y;
                sourceBounds.w = FontInfo.chars[*s].width;
                
                // Copy the source window (contains the image to draw) to the draw window.
                TwGfxTransparentBlt(destSurface, &destPoint,
                    FontInfo.fontGlyphs, &sourceBounds,
                    FontInfo.fontColorBackground);

                destPoint.x += FontInfo.chars[*s].width;
            }
            s++;
            length--;
        }
        
        width = destPoint.x - x;
    }
    
    return width;
}
