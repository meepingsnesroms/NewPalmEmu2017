/*! \file 
 * X-Forge Example<br>
 * Copyright 2000-2002 Fathammer Ltd
 * 
 * \brief Image loader filter for BMPs
 * 
 * $Id: ImageLoadFilterBMP.h,v 1.1.1.1 2002/09/30 08:14:51 jari Exp $
 * $Date: 2002/09/30 08:14:51 $
 * $Revision: 1.1.1.1 $
 */

#ifndef IMAGELOADFILTERBMP_H_INCLUDED
#define IMAGELOADFILTERBMP_H_INCLUDED

class ImageLoadFilterBMP : public XFcImageLoader
{
protected:
    //! Return 1 if this plugin can load this file, or 0 if cannot.
    virtual INT validateImage(const CHAR *aFilename, XFcFile *aFile);
    //! Returns the requested info on the image.
    /*! \note parameters can be NULL; in this case that parameter should be
     *  ignored. */
    virtual void getImageInfo(const CHAR *aFilename, XFcFile *aFile,
                              INT32 *aWidth, INT32 *aHeight,
                              INT *aAlphaLayer, INT *aPaletted);
    //! Loads image and its palette.
    virtual void getImagePaletted(const CHAR *aFilename, XFcFile *aFile,
                                  UINT8 **aPalettePtr, UINT8 **aBitmapPtr);
    
public:
    
    //! Virtual destructor; core makes sure the object is deleted.
    virtual ~ImageLoadFilterBMP();
    
    ImageLoadFilterBMP();
};

#endif // !IMAGELOADFILTERBMP_H_INCLUDED
