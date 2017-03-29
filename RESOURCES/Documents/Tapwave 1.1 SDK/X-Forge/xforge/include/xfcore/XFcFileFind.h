/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief File-finding routines
 * 
 * $Id: XFcFileFind.h,v 1.10 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.10 $
 */
#ifndef XFC_CORE_XFCFILEFIND_H_INCLUDED
#define XFC_CORE_XFCFILEFIND_H_INCLUDED


//! Flags for file finding.
enum XFCFILEFINDFLAGS
{
    XFCFF_DISK                  = 1,    //!< Find files on disk.
    XFCFF_CFL                   = 2,    //!< Find files inside CFLs.
    XFCFF_REMOVEDUPLICATES      = 4,    //!< Remove duplicates (if file exists both on disk and inside CFL).
    XFCFF_IGNORECASE            = 8     //!< Ignore case while searching.
};


//! Used to search for files on disk and/or inside CFL files, using wildcard matches.
class XFCDLLEXPORT XFcFileFind 
{
    
public:
    
    //! Destructor.
    XFCIMPORT ~XFcFileFind();
    
    //! Creates a XFcFileFind object.
    /*! Default flags search everywhere and removes duplicates (e.g. same
     *  file may be found in CFL and disk), but does not ignore case.
     * \param aFileMask Wildcard file matching mask, for example XFCSTR("file*.dat").
     * \param aFlags File finding flags.
     * \sa XFCFILEFINDFLAGS
     */
    XFCIMPORT static XFcFileFind * create(const CHAR *aFileMask,
                                          INT32 aFlags = XFCFF_DISK | XFCFF_CFL | XFCFF_REMOVEDUPLICATES);
    
    //! Returns next string, or NULL if there is no more files.
    /*! \note Pointer is valid until the next next() call (or destruction).
     *  \note Remember to delete the XFcFileFind object once you're done.
     */
    XFCIMPORT const CHAR * next();

protected:
    
    //! Pointer to resource file directory.
    void *mCurrentCFLEntry;
    //! Flags passed to create-method.
    /*! \sa XFCFILEFINDFLAGS
     */
    INT32 mFlags;
    //! Platform specific handle to file finding interface.
    void *mDiskFindHandle;
    //! The wildcard file matching mask passed to create-method.
    const CHAR *mFileMask;
    
    //! Returns the next (non-directory) file on disk.
    const CHAR * nextFilenameDisk();
    //! Returns the next filename in resource directory, or NULL if there is no more entries.
    const CHAR * nextFilenameCFL();
    //! Returns the next filename.
    /*! Tries to find file first from CFL directory and then from disk.
     *  \note Removes duplicates if required.
     *  \return Next filename or NULL if no more files found.
     */
    const CHAR * nextFilename();
    //! Initializes disk file finding.
    void initFileFindDisk();
    //! Initializes resource file directory file finding.
    void initFileFindCFL();
    //! Cleans up after disk file finding.
    void closeFileFindDisk();
    
    //! Protected constructor.
    XFcFileFind();
    
};


#endif // !XFC_CORE_XFCFILEFIND_H_INCLUDED

