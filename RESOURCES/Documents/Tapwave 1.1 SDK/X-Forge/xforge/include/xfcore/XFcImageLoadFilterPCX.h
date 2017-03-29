/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Image loader filter for PCXes.
 * 
 * $Id: XFcImageLoadFilterPCX.h,v 1.8 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.8 $
 */

#ifndef XFC_CORE_XFCIMAGELOADFILTERPCX_H_INCLUDED
#define XFC_CORE_XFCIMAGELOADFILTERPCX_H_INCLUDED


//! PCX loading image filter.
/*!
 * This filter can only load 8-bit paletted PCX files.
 */
class XFCDLLEXPORT XFcImageLoadFilterPCX : public XFcImageLoader
{

public:

    //! Virtual destructor; core makes sure the object is deleted.
    XFCIMPORT virtual ~XFcImageLoadFilterPCX();

    //! Constructor.
    XFCIMPORT XFcImageLoadFilterPCX();

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
                              INT32 *aWidth, INT32 *aHeight,
                              INT *aAlphaLayer, INT *aPaletted);

    //! Inherited from XFcImageLoader.
    /*! \sa XFcImageLoader::getImagePaletted
     */
    virtual void getImagePaletted(const CHAR *aFilename, XFcFile *aFile,
                                  UINT8 **aPalettePtr, UINT8 **aBitmapPtr);
};


#endif // !XFC_CORE_XFCIMAGELOADFILTERPCX_H_INCLUDED

