/*! \file 
 * X-Forge Example<br>
 * Copyright 2000-2002 Fathammer Ltd
 * 
 * \brief Image loader filter for BMPs
 * 
 * $Id: ImageLoadFilterBMP.cpp,v 1.1.1.1 2002/09/30 08:14:51 jari Exp $
 * $Date: 2002/09/30 08:14:51 $
 * $Revision: 1.1.1.1 $
 */

#include <xforge.h>
#include "ImageLoadFilterBMP.h"

#pragma pack(1)
typedef struct BMPHEADER_ 
{ 
    WORD   bfType; 
    DWORD  bfSize; 
    WORD   bfReserved1; 
    WORD   bfReserved2; 
    DWORD  bfOffBits; 

    DWORD  biSize; 
    LONG   biWidth; 
    LONG   biHeight; 
    WORD   biPlanes; 
    WORD   biBitCount;
    DWORD  biCompression; 
    DWORD  biSizeImage; 
    LONG   biXPelsPerMeter; 
    LONG   biYPelsPerMeter; 
    DWORD  biClrUsed; 
    DWORD  biClrImportant; 
} BMPHEADER; 
#pragma pack()

//! Return 1 if this plugin can load this file, or 0 if cannot.
INT ImageLoadFilterBMP::validateImage(const CHAR *aFilename, XFcFile *aFile)
{
    BMPHEADER hdr;
    aFile->seek(0, SEEK_SET);
    aFile->read(&hdr, sizeof(hdr), 1);
    aFile->seek(0, SEEK_SET);
    if (hdr.bfType != 0x4D42 || // 'BM'
        hdr.biWidth < 1 ||      // sanity cheks
        hdr.biHeight < 1 ||
        hdr.biPlanes != 1 ||    // only one plane is supported
        hdr.biBitCount != 8 ||  // only paleted format supported
        hdr.biCompression != BI_RGB) // only uncompressed format is supported
        return 0;
    return 1;
}


//! Returns the requested info on the image.
/*! \note parameters can be NULL; in this case that parameter should be
 *  ignored. */
void ImageLoadFilterBMP::getImageInfo(const CHAR *aFilename, XFcFile *aFile,
                          INT32 *aWidth, INT32 *aHeight,
                          INT *aAlphaLayer, INT *aPaletted)
{
    BMPHEADER hdr;
    aFile->seek(0, SEEK_SET);
    aFile->read(&hdr, sizeof(hdr), 1);
    aFile->seek(0, SEEK_SET);
    if (aWidth) *aWidth = hdr.biWidth;
    if (aHeight) *aHeight = hdr.biHeight;
    if (aAlphaLayer) *aAlphaLayer = 0;
    if (aPaletted) 
    {
        if (hdr.biBitCount == 8) 
            *aPaletted = 1;
        else
            *aPaletted = 0;
    }
}


//! Loads image and its palette.
void ImageLoadFilterBMP::getImagePaletted(const CHAR *aFilename, XFcFile *aFile,
                              UINT8 **aPalettePtr, UINT8 **aBitmapPtr)
{
    // If we get this far, the validate call, above, has been made.
    UINT8 *rawpal;
    UINT8 *pal;
    UINT8 *pic;
    BMPHEADER hdr;
    aFile->seek(0, SEEK_SET);
    aFile->read(&hdr, sizeof(hdr), 1);
    // Seek past the bitmap file header and the bitmap info header
    aFile->seek(hdr.biSize + 14, SEEK_SET);
    // If colors used is reported as zero, all 256 colors are actually in use.
    if (hdr.biClrUsed == 0)
        hdr.biClrUsed = 256;
    
    // bitmap uses 4 bytes per palette entry.
    rawpal = new UINT8[hdr.biClrUsed * 4];
    if (rawpal == NULL)
    {
        *aPalettePtr = NULL;
        *aBitmapPtr = NULL;
        return;
    }

    // Allocate our own palette, 3 bytes per entry.
    pal = new UINT8[3 * 256];
    if (pal == NULL)
    {
        delete[] rawpal;
        *aPalettePtr = NULL;
        *aBitmapPtr = NULL;
        return;
    }
    // Allocate memory for the bitmap
    pic = new UINT8[hdr.biWidth * hdr.biHeight]; 
    if (pic == NULL)
    {
        delete[] rawpal;
        delete[] pal;
        *aPalettePtr = NULL;
        *aBitmapPtr = NULL;
        return;
    }
    // Load the bitmap palette
    aFile->read(rawpal, hdr.biClrUsed, 4);
    // Load the bitmap itself
    aFile->read(pic, hdr.biWidth * hdr.biHeight, 1);
    int i;
    // Convert palette
    for (i = 0; i < (signed)hdr.biClrUsed; i++)
    {
        pal[i * 3 + 0] = rawpal[i * 4 + 2];
        pal[i * 3 + 1] = rawpal[i * 4 + 1];
        pal[i * 3 + 2] = rawpal[i * 4 + 0];
    }
    delete[] rawpal;
    *aPalettePtr = pal;
    *aBitmapPtr = pic;
}

    
//! Virtual destructor; core makes sure the object is deleted.
ImageLoadFilterBMP::~ImageLoadFilterBMP()
{
}

//! Constructor.
ImageLoadFilterBMP::ImageLoadFilterBMP()
{
    registerImageLoader(this);
}

