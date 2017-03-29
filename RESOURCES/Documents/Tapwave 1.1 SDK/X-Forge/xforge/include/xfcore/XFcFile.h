/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief File handling interface.
 * 
 * $Id: XFcFile.h,v 1.16 2003/09/19 09:19:50 jari Exp $
 * $Date: 2003/09/19 09:19:50 $
 * $Revision: 1.16 $
 */

#ifndef XFC_CORE_XFCFILE_H_INCLUDED
#define XFC_CORE_XFCFILE_H_INCLUDED

#ifndef SEEK_CUR
//! "Seek current" - seek from the current position.
#define SEEK_CUR    1
#endif
#ifndef SEEK_END
//! "Seek end" - seek from the end of file (typically with a negative offset).
#define SEEK_END    2
#endif
#ifndef SEEK_SET
//! "Seek set" - seek from the beginning of the file.
#define SEEK_SET    0
#endif

//! Handle returned by seeking methods. Platform-specific, thus a 'void *' type.
typedef void *XFCFINDHANDLE;

enum XFCFILEOPENSTRATEGY
{
    XFCFO_DEFAULT = 0,      //!< Use the currently active default strategy
    XFCFO_DISKFIRST,        //!< Search for files from disk first, read-only storage last
    XFCFO_CFLFIRST,         //!< Search for files first from read-only storage, then from disk
    XFCFO_DISKONLY,         //!< Only search for files on disk
    XFCFO_CFLONLY,          //!< Only search for files in read-only storage
};

//! File handling operations.
/*!
 * Used in same way compared to C standard library FILE * handling functions.
 * You can use XFuFileDef.h from xfutil library to hack stdio.h FILE *-using
 * sources to use this class instead. Include that file \b after the standard
 * library headers.
 * \note It is possible that some systems only have a read-only filesystem.
 */
class XFCDLLEXPORT XFcFile 
{    
public:

    //! Opens a file.
    /*! First tries to load from disk, then tries the CFL resource file(s). 
     *  Files are opened from the same directory as the executable. Trying
     *  to reach upper directories is normally impossible (as 'upper directory'
     *  is platform-specific) but you can prefix filename with two slashes
     *  to go around the root directory setting to enter platform specific
     *  file names.<br>
     *  Examples:<br>
     *  \li "file.dat" - file in the same directory with the executable.
     *  \li "dat/file.dat" - file in dat-directory from the executable directory.
     *  \li "c:\\file.dat" - file called "c:\file.dat" in the directory where the executable is.
     *  \li "//c:\\file.dat" - on Windows, file.dat in the root of C-drive (platform specific).
     * \param aFilename name of the file to open.
     * \param aMode string specifying the file mode, as specified for C standard library \c fopen.
     * \param aFindStrategy defines whether to open disk file rather than cfl file if both exist, 
     *        or to open only cfl file or only disk file. See XFCFILEOPENSTRATEGY enum in XFcFile.h.
     * \return new file object if successful, NULL if unsuccessful.
     * \note Write and append modes are not supported for CFL resource files.
     */
    XFCIMPORT static XFcFile * open(const CHAR *aFilename, const CHAR *aMode, UINT32 aFindStrategy = XFCFO_DEFAULT);
    
    //! Creates XFcFile object using a memory buffer as read-only file
    /*!
     * \note Closing the file calls delete[] on the memory buffer.
     */
    XFCIMPORT static XFcFile * open(const CHAR *aFilename, const INT8 *aBuffer, const UINT32 aBufferLength);

    //! Opens a file from disk (to force loading only from disk). DEPRECATED
    /*! \sa open
     *  This method is deprecated; use open with open strategy XFCFO_DISKONLY instead.
     */
    XFCIMPORT static XFcFile * openDiskFile(const CHAR *aFilename,
                                            const CHAR *aMode);

    
    //! Opens from resource file (to force loading only from resource files). DEPRECATED
    /*! \sa open
     *  This method is deprecated; use open with open strategy XFCFO_CFLONLY instead.
     */
    XFCIMPORT static XFcFile * openCFLFile(const CHAR *aFilename,
                                           const CHAR *aMode);

    //! Removes file from disk. This function will not touch files inside read-only storage.
    /*! \note Removing a .cfl file while it is mounted will cause unpredictable behavior.
     */
    XFCIMPORT static INT remove(const CHAR *aFilename);

    //! Renames file on disk. This function will not touch files inside read-only storage.
    /*! \note Renaming a .cfl file while it is mounted will cause unpredictable behavior.
     */
    XFCIMPORT static INT rename(const CHAR *aOldFilename, CHAR *aNewFilename);

    //! Creates a directory in the filesystem
    /*!
     * If the parameter isn't prefixed with "//", the directory
     * will be created under the application's root directory.
     * 
     * Some platforms may be able to create whole directory hierarchies
     * with one call, and some platforms may not support directories at all.
     *
     * You can create a directory on a different drive, etc, using the "//" 
     * prefix. See open() for description.
     * \sa open()
     * \sa rmdir()
     */
    XFCIMPORT static INT mkdir(const CHAR *aDirectoryname);

    //! Removes a directory in the filesystem
    /*!
     * The directory removal will most likely fail if the
     * directory is not empty.
     *
     * \sa open()
     * \sa mkdir()
     */
    XFCIMPORT static INT rmdir(const CHAR *aDirectoryname);

    //! Seeks to a certain position in the file.
    /*! \param aDisplacement defines how much to seek from the position specified by aMode.
     *  \param aMode \li SEEK_SET to seek from start of the file,
     *               \li SEEK_END to seek from end of the file or
     *               \li SEEK_CURR to seek from the current file position.
     * \return 0 if successful.
     */
    XFCIMPORT virtual INT32 seek(INT32 aDisplacement, INT32 aMode);
    
    //! Returns the file position.
    XFCIMPORT virtual INT32 tell();

    //! Returns pointer to the filename used to create this XFcFile object.
    XFCIMPORT virtual const CHAR * getFilename();

    //! Gets one byte from file. Returns EOF if end of file.
    XFCIMPORT virtual INT32 getChar();
    
    //! Puts one byte in the file.
    XFCIMPORT virtual INT32 putChar(INT32 aChar);
    
    //! Read chunk(s) from file at once.
    /*! \param aBuf destination for the read data.
     *  \param aSize size of one chunk of data.
     *  \param aCount number of chunks to read.
     * \return number of chunks successfully read from the file.
     * \note aBuf must point to at least aSize*aCount bytes of allocated memory.
     */
    XFCIMPORT virtual INT32 read(void *aBuf, INT32 aSize, INT32 aCount);
    
    //! Writes chunk(s) to file at once.
    /*! \param aBuf pointer to the data to be written.
     *  \param aSize size of one chunk of data.
     *  \param aCount number of chunks to write.
     * \return number of chunks successfully written to the file.
     * \note aBuf must point to at least aSize*aCount bytes of data.
     */
    XFCIMPORT virtual INT32 write(const void *aBuf, INT32 aSize, INT32 aCount);
    
    //! Closes file (also deletes the file object).
    XFCIMPORT virtual INT32 close();

    //! Returns 1 if at end of file.
    XFCIMPORT virtual INT endOfFile();
    
    //! Allocates sufficient amount of memory and reads the whole file in it.
    /*!
     * \param aFilename file name to load.
     * \param aFindStrategy defines whether to open disk file rather than cfl file if both exist, 
     *        or to open only cfl file or only disk file. See XFCFILEOPENSTRATEGY enum in XFcFile.h.
     * \return pointer into newly allocated buffer containing the file data.
     */
    XFCIMPORT static INT8 * getFile(const CHAR *aFilename, UINT32 aFindStrategy = XFCFO_DEFAULT);
    
    //! Returns the file size.
    /*!
     * \param aFilename file name to request size for.
     * \param aFindStrategy defines whether to open disk file rather than cfl file if both exist, 
     *        or to open only cfl file or only disk file. See XFCFILEOPENSTRATEGY enum in XFcFile.h.
     * \return file size.
     */
    XFCIMPORT static INT32 getFileSize(const CHAR *aFilename, UINT32 aFindStrategy = XFCFO_DEFAULT);
    
    //! Tests if a file exists.
    /*!
     * \param aFilename file name to test.
     * \return 0, if file does not exist.
     * \return 1, if file exists in read-only storage.
     * \return 2, if file exists on disk.
     * \return 3, if file exists on both.
     */
    XFCIMPORT static INT fileExists(const CHAR *aFilename);
   
    // Convenience functions.
    
    //! Writes FLOAT32.
    XFCIMPORT INT32 writeFLOAT32(FLOAT32 aValue);
    //! Writes FLOAT64.
    XFCIMPORT INT32 writeFLOAT64(FLOAT64 aValue);
    //! Writes INT32.
    XFCIMPORT INT32 writeINT32(INT32 aValue);
    //! Writes INT16.
    XFCIMPORT INT32 writeINT16(INT16 aValue);
    //! Writes INT8.
    XFCIMPORT INT32 writeINT8(INT8 aValue);
    //! Writes UINT32.
    XFCIMPORT INT32 writeUINT32(UINT32 aValue);
    //! Writes UINT16.
    XFCIMPORT INT32 writeUINT16(UINT16 aValue);
    //! Writes UINT8.
    XFCIMPORT INT32 writeUINT8(UINT8 aValue);

    //! Reads and returns FLOAT32.
    XFCIMPORT FLOAT32 readFLOAT32();
    //! Reads and returns  FLOAT64.
    XFCIMPORT FLOAT64 readFLOAT64();
    //! Reads and returns  INT32.
    XFCIMPORT INT32 readINT32();
    //! Reads and returns  INT16.
    XFCIMPORT INT16 readINT16();
    //! Reads and returns  INT8.
    XFCIMPORT INT8 readINT8();
    //! Reads and returns  UINT32.
    XFCIMPORT UINT32 readUINT32();
    //! Reads and returns  UINT16.
    XFCIMPORT UINT16 readUINT16();
    //! Reads and returns  UINT8.
    XFCIMPORT UINT8 readUINT8();
    
    //! Reads FLOAT32 to reference.
    XFCIMPORT INT32 readFLOAT32(FLOAT32 &aValue);
    //! Reads FLOAT64 to reference.
    XFCIMPORT INT32 readFLOAT64(FLOAT64 &aValue);
    //! Reads INT32 to reference.
    XFCIMPORT INT32 readINT32(INT32 &aValue);
    //! Reads INT16 to reference.
    XFCIMPORT INT32 readINT16(INT16 &aValue);
    //! Reads INT8 to reference.
    XFCIMPORT INT32 readINT8(INT8 &aValue);
    //! Reads UINT32 to reference.
    XFCIMPORT INT32 readUINT32(UINT32 &aValue);
    //! Reads UINT16 to reference.
    XFCIMPORT INT32 readUINT16(UINT16 &aValue);
    //! Reads UINT8 to reference.
    XFCIMPORT INT32 readUINT8(UINT8 &aValue);    

    //! Writes a null-terminated CHAR string.
    /*!
     * \note performs CHAR8<->CHAR16 conversion.
     * \param aValue string to write.
     * \note also stores the NULL.
     */
    XFCIMPORT void writeCHARString(CHAR *aValue);
    
    //! Reads a null-terminated CHAR string.
    /*!
     * \note performs CHAR8<->CHAR16 conversion.
     * \return read string.
     * \note also reads the NULL.
     */
    XFCIMPORT CHAR * readCHARString();
    
    //! Writes a null-terminated CHAR8 string.
    /*!
     * \param aValue string to write.
     * \note also stores the NULL.
     */
    XFCIMPORT void writeCHAR8String(CHAR8 *aValue);
    
    //! Reads a null-terminated CHAR8 string.
    /*!
     * \return read string.
     * \note also reads the NULL.
     */
    XFCIMPORT CHAR8 * readCHAR8String();
    
    //! Writes a null-terminated CHAR16 string.
    /*!
     * \param aValue string to write.
     * \note also stores the NULL.
     */
    XFCIMPORT void writeCHAR16String(CHAR16 *aValue);
    
    //! Reads a null-terminated CHAR16 string.
    /*!
     * \return read string.
     * \note also reads the NULL.
     */
    XFCIMPORT CHAR16 * readCHAR16String();


protected:

    //! Opens a stdio file
    XFCIMPORT static XFcFile * openStdFile(const CHAR *aFilename,
                                            const CHAR *aMode);

    //! Creates a platform specific representation of a file name.
    /*! \note Client must delete[] the returned file name.
     * \param aFilename filename to create a platform specific representation for.
     * \return newly allocated string with the platform specific mangled filename.
     */
    static CHAR * makeDiskFilenameString(const CHAR *aFilename);

    //! Protected constructor.
    XFcFile();
    //! Protected destructor.
    virtual ~XFcFile();
    
    //! Copy of the filename.
    CHAR *mFilename;
    //! File pointer, usually FILE *, or char * for ram-based files.
    void *mFile;
    //! 0 for disk file, 1 for CFL-stored file.
    INT32 mFilemode;
    //! Flags for the file state.
    INT32 mFlag;
};


#endif // !XFC_CORE_XFCFILE_H_INCLUDED

