/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Image loader class factory
 * 
 * $Id: XFcImageLoader.h,v 1.9 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.9 $
 */

#ifndef XFC_CORE_XFCIMAGELOADER_H_INCLUDED
#define XFC_CORE_XFCIMAGELOADER_H_INCLUDED



//! Image loading class factory base class.
/*! 
 * All image loaders in the system are made as plugins that extend this class.
 */
class XFCDLLEXPORT XFcImageLoader 
{

public:

    //! Pointer to the next plugin.
    /*! \internal
     */
    XFcImageLoader *mNext;

    //! Virtual destructor; core makes sure the object is deleted.
    XFCIMPORT virtual ~XFcImageLoader();

    //! Loads an image into a new surface.
    /*! By default XFCGF_R5G5X1B5 is used for non-alpha pictures and
     *  XFCGF_R5G5A1B5 for pictures with alpha.
     * \param aFilename image filename to load.
     * \param aSurfaceFormat surface format to use.
     * \return new surface containing the image, or NULL if unsuccessful.
     */
    XFCIMPORT static XFcGLSurface * load(const CHAR *aFilename,
                                         INT32 aSurfaceFormat = XFCGF_DEFAULT);

    //! Loads information on image.
    /*! \note Parameters can be set to NULL if not needed.
     * \param aFilename filename of the image.
     * \param aWidth returned width, or NULL if width is not requested.
     * \param aHeight returned height, or NULL if height is not requested.
     * \param aAlphaLayer returned alpha layer availability, or NULL if it is not requested.
     * \param aPaletted returned palette availability, or NULL if it is not requested.
     */
    XFCIMPORT static void loadImageInfo(const CHAR *aFilename, INT32 *aWidth,
                                        INT32 *aHeight, INT *aAlphaLayer,
                                        INT *aPaletted);

    //! Loads an image into a linear XFCGF_A8R8G8B8 buffer (32 bits per pixel).
    /*!
     * \param aFilename filename to load.
     * \return new buffer containing the image, or NULL if unsuccessful.
     */
    XFCIMPORT static UINT32 * loadImage8888(const CHAR *aFilename);

    //! Loads an image in paletted mode.
    /*! If file format does not support paletted mode, palette and bitmap
     *  return pointers are set to NULL.
     * \param aFilename filename to load.
     * \param aPalettePtr returned pointer to the palette, set to NULL if unsuccessful.
     * \param aBitmapPtr returned pointer to the bitmap, set to NULL if unsuccessful.
     */
    XFCIMPORT static void loadImagePaletted(const CHAR *aFilename,
                                            UINT8 **aPalettePtr,
                                            UINT8 **aBitmapPtr);
    
    //! Loads an image into a buffer.
    /*! Pitch is in bytes. By default XFCGF_R5G6B5 is used for non-alpha pictures
     *  and XFCGF_A1R5G5B5 for pictures with alpha.
     * \param aFilename filename to load.
     * \param aBuffer destination buffer for the image data.
     * \param aPitch pitch of the destination buffer in bytes.
     * \param aFormat format of the destination buffer, see XFCGFXFORMAT.
     * \sa XFCGFXFORMAT
     */
    XFCIMPORT static INT loadImageToBuffer(const CHAR *aFilename, void *aBuffer,
                                          INT32 aPitch,
                                          INT32 aFormat = XFCGF_DEFAULT);

protected:

    //! Called by a plugin to register itself in its constructor.
    static void registerImageLoader(XFcImageLoader *aFilter);
    
    //! Determines if this plugin can load a specified file.
    /*! With as little work as possible, this function should return 1 if
     *  this plugin can load this file, or 0 if cannot.
     * \param aFilename filename of the file for validation.
     * \param aFile file to validate.
     * \return 1 if this plugin can load this file, or 0 if cannot.
     */
    virtual INT validateImage(const CHAR *aFilename, XFcFile *aFile) = 0;
    
    //! Returns the requested info on the image.
    /*!
     * \note Parameters can be set to NULL; in this case that parameter should be ignored.
     * \param aFilename filename of the image (may be unused).
     * \param aFile file to get the information from.
     * \param aWidth returned width, or NULL if width is not requested.
     * \param aHeight returned height, or NULL if height is not requested.
     * \param aAlphaLayer returned alpha layer availability, or NULL if it is not requested.
     * \param aPaletted returned palette availability, or NULL if it is not requested.
     */
    virtual void getImageInfo(const CHAR *aFilename, XFcFile *aFile,
                              INT32 *aWidth, INT32 *aHeight, INT *aAlphaLayer,
                              INT *aPaletted) = 0;
    
    //! Loads an image to a 8:8:8:8 ARGB buffer.
    /*!
     * \note Default implementation calls getImagePaletted and converts the image.
     * \param aFilename filename of the file to load.
     * \param aFile file to load from.
     */
    virtual UINT32 * getImage8888(const CHAR *aFilename, XFcFile *aFile);
    
    //! Loads image and its palette.
    /*!
     * \note Default implementation does nothing.
     * \note Don't extend this function if file format has no paletted mode
     *       support. Palettes should be triplets of bytes for red, green and
     *       blue colors (R8G8B8).
     * \param aFilename filename to load.
     * \param aFile file to load from.
     * \param aPalettePtr returned pointer to the palette, set to NULL if unsuccessful.
     * \param aBitmapPtr returned pointer to the bitmap, set to NULL if unsuccessful.
     */
    virtual void getImagePaletted(const CHAR *aFilename, XFcFile *aFile,
                                  UINT8 **aPalettePtr, UINT8 **aBitmapPtr);

    //! Does the actual gruntwork of loading the image for load() and loadimagetobuffer()
    static INT doLoadImage(const CHAR *aFilename, XFcImageLoader *aLoadPlugin, 
                           XFcFile *aFile, INT32 aFormat, INT32 aWidth, 
                           INT32 aHeight, INT32 aAlpha, INT32 aPaletted, 
                           INT32 aPitch, void *aBuffer);
    
private:

    //! Internal: goes through the plugin link list and finds a proper filter.
    static XFcImageLoader * findPlugin(const CHAR *aFilename, XFcFile *aFile);
};


#endif // !XFC_CORE_XFCIMAGELOADER_H_INCLUDED

