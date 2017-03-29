/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Image loader filter for TGAs.
 * 
 * $Id: XFcImageLoadFilterTGA.h,v 1.9 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.9 $
 */

#ifndef XFC_CORE_XFCIMAGELOADFILTERTGA_H_INCLUDED
#define XFC_CORE_XFCIMAGELOADFILTERTGA_H_INCLUDED


//! TGA-loading image filter.
/*!
 * This filter can load most common variants of the TGA format, including
 * RLE compressed ones. Greyscale images are not currently supported.
 * \par
 * If the TGA file has an alpha layer, XFcImageLoader automatically creates
 * surface in 16-bit 5515 format instead of 55X5 format.
 */
class XFCDLLEXPORT XFcImageLoadFilterTGA : public XFcImageLoader
{

public:

    //! Virtual destructor; core makes sure the object is deleted.
    XFCIMPORT virtual ~XFcImageLoadFilterTGA();

    //! Constructor.
    XFCIMPORT XFcImageLoadFilterTGA();

protected:

    //! Determines if this plugin can load a specified file.
    /*!
     * \param aFilename filename of the file for validation.
     * \param aFile file to validate.
     * \return 1 if this plugin can load this file, or 0 if cannot.
     */
    virtual INT validateImage(const CHAR *aFilename, XFcFile *aFile);

    //! Inherited from XFcImageLoader.
    /*! \sa XFcImageLoader::getImageInfo
     */
    virtual void getImageInfo(const CHAR *aFilename, XFcFile *aFile,
                              INT32 *aWidth, INT32 *aHeight, INT *aAlphaLayer,
                              INT *aPaletted);

    //! Inherited from XFcImageLoader.
    /*! \sa XFcImageLoader::getImage8888
     */
    virtual UINT32 * getImage8888(const CHAR *aFilename, XFcFile *aFile);

    //! Inherited from XFcImageLoader.
    /*! \sa XFcImageLoader::getImagePaletted
     */
    virtual void getImagePaletted(const CHAR *aFilename, XFcFile *aFile,
                                  UINT8 **aPalettePtr, UINT8 **aBitmapPtr);

};


#endif // !XFC_CORE_XFCIMAGELOADFILTERTGA_H_INCLUDED

