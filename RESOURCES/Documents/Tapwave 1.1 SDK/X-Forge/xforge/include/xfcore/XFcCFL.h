/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Compressed File Library routines.
 * 
 * $Id: XFcCFL.h,v 1.11 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.11 $
 */

#ifndef XFC_CORE_XFCCFL_H_INCLUDED
#define XFC_CORE_XFCCFL_H_INCLUDED

class XFcFile;


//! Resource handler flags.
/*! \note Most of these have not been really implemented,
 *        but are specified just in case someone wants to do so.
 */
enum XFCCFLHANDLEXFCCFLLAGS
{
    //! No compression.
    XFCCFLCOMPRESS_NONE         = 0x00000000,
    //! Zlib, normal compression.
    XFCCFLCOMPRESS_ZLIB         = 0x00000001,
    //! Zlib, maximum compression.
    XFCCFLCOMPRESS_ZLIB9        = 0x00000901,
    //! LZSS.
    XFCCFLCOMPRESS_LZSS         = 0x00000002,
    //! BZip2.
    XFCCFLCOMPRESS_BZIP2        = 0x00000003,
    //! Tries out all registered compressors, uses the best result.
    XFCCFLCOMPRESS_BEST         = 0x0000FFFF,

    //! No preprocess.
    XFCCFLPREPROCESS_NONE       = 0x00000000,
    //! 8-bit delta encoding.
    XFCCFLPREPROCESS_DELTA8     = 0x00010000,
    //! 16-bit delta encoding.
    XFCCFLPREPROCESS_DELTA16    = 0x00020000,
    //! 32-bit delta encoding.
    XFCCFLPREPROCESS_DELTA32    = 0x00030000,
    //! Burrows-Wheeler transform.
    XFCCFLPREPROCESS_BWT        = 0x00040000,

    //! No encryption.
    XFCCFLENCRYPT_NONE          = 0x00000000,
    //! Simple XOR crypt (generally stops casual hex-editor), key is one char.
    XFCCFLENCRYPT_XOR           = 0x01000000,
    //! XORs every byte with data from pseudorandom generator, key is the random seed.
    XFCCFLENCRYPT_PRANDXOR      = 0x02000000,
    //! XORs every byte with a letter from entered string.
    /*! Somewhat easy to crack if string is short, but is an easy way to
     *  implement very weak password protection.
     */
    XFCCFLENCRYPT_STRINGXOR     = 0x03000000,
    //! Pretty Good Privacy.
    XFCCFLENCRYPT_PGP           = 0x10000000,
    //! GPG.
    XFCCFLENCRYPT_GPG           = 0x20000000,
    //! Data Encryption Standard.
    XFCCFLENCRYPT_DES           = 0x30000000,
    //! Triple-DES.
    XFCCFLENCRYPT_3DES          = 0x40000000,
    //! Blowfish.
    XFCCFLENCRYPT_BLOWFISH      = 0x50000000,
    //! IDEA.
    XFCCFLENCRYPT_IDEA          = 0x60000000,
    //! RC4.
    XFCCFLENCRYPT_RC4           = 0x70000000
};


//! Callback enumerator for handlers.
class XFCDLLEXPORT XFcCFLEnumerator
{
public:
    XFCIMPORT virtual void infoCallback(UINT32 aTag, const CHAR *aInfoString,
                                        const CHAR *aShortName) = 0;
};


//! Resource header and handler.
class XFCDLLEXPORT XFcCFLResource 
{
public:
    
    UINT32 mCompressedSize;     //!< From beginning of block.
    INT8 *mData;
    
    //! Loads a resource from the current file position.
    XFCIMPORT static XFcCFLResource * load(XFcFile *aFile);
    //! Saves a resource to the current file position.
    XFCIMPORT void save(XFcFile *aFile);
    XFCIMPORT XFcCFLResource();
    XFCIMPORT ~XFcCFLResource();
};


//! Class factory to handle compressors, preprocessors and encryptors.
class XFCDLLEXPORT XFcCFLResourceFilter 
{
protected:
    
    //! Pointer to a printable info string.
    CHAR *mInfoString;
    //! Pointer to a printable short name (10 chars or less preferably).
    CHAR *mShortName;
    //! Boolean flag, indicates if this handler is enabled or not.
    INT mEnabled;
    //! Tag of the current handler. 
    /*! Tag format:<br>
     * EPOC<br>
     * |||+- Compressor<br>
     * ||+-- Compressor variant (option)<br>
     * |+--- Preprocessor<br>
     * +---- Encryptor<br>
     * Each handler must leave the rest of the bits to zero.<br>
     * (e.g. 000Z, 00D0, 0X00)
     */
    UINT32 mTag;
    
    //! Protected constructor.
    /*! Constructor must:
     * \li set tag and infostring
     * \li call registerHandler(tag, this)
     */
    XFcCFLResourceFilter();
    //! Registers a handler.
    static void registerHandler(XFcCFLResourceFilter *aHandler);
    //! Processes (e.g. compress, encrypt..) data.
    virtual void process(INT8 *aDataIn, INT8 **aDataOut, UINT32 aDataInSize,
                         UINT32 &aDataOutSize) = 0;
    //! Reverse processes (e.g. decompress, decrypt..) data.
    virtual void reverseProcess(INT8 *aDatain, INT8 **aDataout,
                                UINT32 aDataInSize, UINT32 &aDataOutSize) = 0;
    //! Finds a handler for a tag.
    static XFcCFLResourceFilter * findHandler(UINT32 aTag);
    //! Sets the cipher key.
    virtual void setCipherKey(void *aKey);
    
public:
    
    //! Pointer to the next handler, or NULL if at end of list.
    XFcCFLResourceFilter *mNext;
    //! Virtual destructor.
    XFCIMPORT virtual ~XFcCFLResourceFilter();
    
    //! Decompresses, decrypts and reverse processes data.
    XFCIMPORT static INT8 * unhandle(const XFcCFLResource *aRes,
                                     UINT32 aCompressionFlags);
    //! Compresses, encrypts and processes data.
    /*! \note CompressionFlags may change during handling.
     */
    XFCIMPORT static XFcCFLResource * handle(const INT8 *aData,
                                             UINT32 aDataSize,
                                             UINT32 &aCompressionFlags);
    //! Returns a printable string of the handler.
    XFCIMPORT static const CHAR * handlerInfoString(UINT32 aTag);
    //! Returns a printable short name of the handler.
    XFCIMPORT static const CHAR * handlerShortName(UINT32 aTag);
    //! Enumerates handlers (for GUI use generally).
    XFCIMPORT static void enumerateHandlers(XFcCFLEnumerator *aEnumerator);
    //! Enables or disables handlers (for GUI use generally).
    XFCIMPORT static void enableHandler(UINT32 aTag, INT aState);
    //! Sets key for encrypter.
    XFCIMPORT static void setKey(UINT32 aTag, void *aKey);
};


//! Container for all information CFL needs about a single .cfl file.
class XFCDLLEXPORT XFcCFLLibrary
{
public:
    //! File pointer for libraries that are opened with file pointer for some reason.
    /*! \note Normally NULL; XFcCFL doesn't keep files open for no reason.
     */
    XFcFile *mFilePtr;
    //! Filename to the library, or NULL if mFilePtr is not NULL.
    CHAR *mFilename;
    //! Offset to the library, from start of file (0 for standalone XFcCFL's).
    INT32 mOffset;
    //! Pointer to the next library.
    XFcCFLLibrary *mNext;
    
    XFCIMPORT XFcCFLLibrary();
    XFCIMPORT ~XFcCFLLibrary();
    
    //! Opens the library file if mFilePtr is NULL, otherwise returns it.
    XFCIMPORT XFcFile * open();
    //! Closes the library file if mFilePtr is NULL, otherwise does nothing.
    XFCIMPORT void close(XFcFile *aFile);
};


//! Container for all information CFL needs about one file inside CFLs.
class XFCDLLEXPORT XFcCFLDirectoryEntry
{
public:
    //! Name is stored as short int size + char string.
    CHAR *mName;
    UINT32 mCompression;
    UINT32 mUnpackedSize;
    UINT32 mOffset;
    //! Hash is not loaded from a file, but rather calculated on the run.
    INT32 mNameHash;
    XFcCFLLibrary *mLib;
    //! Pointer to the next entry.
    XFcCFLDirectoryEntry *mNext;
    
    //! Calculates required buffer size for a directory.
    XFCIMPORT INT32 byteRequirement(); 
    //! Encodes an entry to a buffer.
    XFCIMPORT void store(INT8 *buffer, INT32 &offset); 
    //! Loads an entry from a buffer.
    XFCIMPORT static XFcCFLDirectoryEntry * restore(INT8 *buffer,
                                                    INT32 &offset); 
    XFCIMPORT ~XFcCFLDirectoryEntry();
    //! Compares two directory entries, first by hash and then by the name.
    XFCIMPORT INT equals(const CHAR *name, INT32 hash);
    //! Calculates a hash from a name.
    XFCIMPORT static INT32 calcHash(const CHAR *name);
    //! Replaces this entry with new one.
    XFCIMPORT void replaceEntry(XFcCFLDirectoryEntry *replacement);
};


//! Compressed File Library object.
/*! This class can be used to access files within compressed file library (.cfl)
 *  files. Multiple .cfl files can be 'mounted' to a single XFcCFL object, and
 *  multiple XFcCFL objects can exist. If several .cfl files have a file with 
 *  the same name, only the last instance is found when opened. This enables
 *  the developer to override any default data, which is useful when doing
 *  localization or different levels (or mods).
 */
class XFCDLLEXPORT XFcCFL 
{
    friend class XFcFileFind;
    
protected:
    
    //! Pointer to the first XFcCFLLibrary object (linked list).
    XFcCFLLibrary *mRootLib;
    //! Pointer to the first XFcCFLDirectoryEntry object (linked list).
    XFcCFLDirectoryEntry *mRootDir;
    
    //! Finds directory entries by a filename.
    XFcCFLDirectoryEntry * findEntry(const CHAR *aName);
    
public:
    
    //! Constructor.
    XFCIMPORT XFcCFL();
    //! Creates a XFcCFL object and opens library from a file (checks beginning and end of file).
    XFCIMPORT static XFcCFL * create(const CHAR *aLibFilename);
    //! Creates a XFcCFL object and opens library from a file (checks offset and end of file).
    XFCIMPORT static XFcCFL * create(const CHAR * aLibFilename,
                                     INT32 aOffset);
    //! Creates a XFcCFL object and opens library from a file pointer (file position must be at start of the library).
    XFCIMPORT static XFcCFL * create(XFcFile *aLibFilePtr);
    //! Opens library from a file (checks beginning and end of file).
    XFCIMPORT INT openLibrary(const CHAR *aLibFilename);
    //! Opens library from a file (checks offset and end of file).
    XFCIMPORT INT openLibrary(const CHAR *aLibFilename, INT32 aOffset);
    //! Opens library from a file pointer (file position must be at start of the library).
    XFCIMPORT INT openLibrary(XFcFile *aLibFilePtr);
    
    //! Returns file data.
    /*! \note The returned memory is allocated with new INT8[filesize].
     */
    XFCIMPORT INT8 * getFile(const CHAR *aName);
    //! Returns file data and data length.
    /*! \note The returned memory is allocated with new INT8[filesize].
     */
    XFCIMPORT INT8 * getFile(const CHAR *aName, INT32 &aSize);
    //! Writes file data into preallocated buffer, returns bytes written.
    XFCIMPORT INT getFile(const CHAR *aName, INT8 *aBuffer, INT32 aMaxSize);
    //! Returns uncompressed file size in bytes.
    XFCIMPORT INT32 getFileSize(const CHAR *aName);  
    //! Returns non-zero if file exists in directory.
    XFCIMPORT INT fileExists(const CHAR *aName);
    //! Returns a file pointer pointing at the beginning of (possibly compressed) data.
    /*! \note Client must use dropFilePtr to close the file pointer!
     */
    XFCIMPORT XFcFile * getFilePtr(const CHAR *aName);
    //! Drops a file pointer.
    XFCIMPORT void dropFilePtr(XFcFile *aFile);
    //! Returns file offset to the beginning of (possibly compressed) data.
    XFCIMPORT INT32 getFileOfs(const CHAR *aName);
    //! Returns a printable string information about compression of this file.
    XFCIMPORT const CHAR * compressionInfoString(const CHAR *aName);
    //! Returns a printable string information about encryption of this file.
    XFCIMPORT const CHAR * encryptionInfoString(const CHAR *aName);
    //! Returns a printable string information about preprocessing of this file.
    XFCIMPORT const CHAR * preprocessorInfoString(const CHAR *aName);

    //! Destructor.
    XFCIMPORT ~XFcCFL();
};


//! Creates new CFL files at runtime.
/*! Usage:
 * \code
 * XFcCFLMaker *mak = XFcCFLMaker::create(XFCSTR("targetfn.cfl"));
 * mak->store(XFCSTR("datafilename.dat"), dataptr, datasize, compressflags);
 * mak->finish(compressflags);
 * \endcode
 * See makecfl program generated .ini file for details on compress flags.
 */
class XFCDLLEXPORT XFcCFLMaker 
{
protected:
    
    XFcCFLMaker();
    ~XFcCFLMaker();
    //! Internal: list of directory entries in the file.
    XFcCFLDirectoryEntry *mRootDir;
    //! Internal: file pointer.
    XFcFile *mFile;
    
public:
    
    //! Starts building a CFL file, returns new XFcCFLMaker object.
    /*! \param aTargetFileName target .cfl file name.
    */
    XFCIMPORT static XFcCFLMaker * create(const CHAR *aTargetFileName);  
    //! Stores a single chunk of data inside the CFL.
    /*! \param aFname Filename by which the file can be found inside the CFL.
     *  \param aData Pointer to the raw data to be stored.
     *  \param aDataSize Size, in bytes, of the data to be stored.
     *  \param aCompressionFlags Flags that select the compressor. 0xffff tries to find the best automatically.
     */
    XFCIMPORT INT32 store(const CHAR *aFname, const INT8 *aData,
                          INT32 aDataSize, UINT32 aCompressionFlags);
    //! Finishes the CFL file, storing the library information.
    /*! \note Also deletes the object.
     */
    XFCIMPORT INT32 finish(UINT32 aLibraryCompressionFlags); 
};


//! CFL filter that uses ZLib for compression.
/*! \note This class is initialized and cleaned up by the X-Forge core.
 */
class XFCDLLEXPORT XFcCFLFilterZlib : public XFcCFLResourceFilter
{
public:
    //! Constructor.
    /*! \note Constructor must
     * \li set tag and infostring.
     * \li call registerHandler(tag,this).
     */
    XFCIMPORT XFcCFLFilterZlib();
    //! Processes (e.g. compress, encrypt..) data.
    XFCIMPORT virtual void process(INT8 *aDataIn, INT8 **aDataOut,
                                   UINT32 aDataInSize,
                                   UINT32 &aDataOutSize);
    //! Reverse processes data (e.g. decompress, decrypt..) data.
    XFCIMPORT virtual void reverseProcess(INT8 *datain, INT8 **dataout,
                                          UINT32 aDataInSize,
                                          UINT32 &aDataOutSize);
};


//! CFL filter that does no processing with the data.
/*! This filter is useful when you want to store non-compressed data
 * within a CFL.
 * \note This class is initialized and cleaned up by the X-Forge core.
 */
class XFCDLLEXPORT XFcCFLFilterNone : public XFcCFLResourceFilter
{
public:
    //! Constructor.
    /*! \note Constructor must
     * \li set tag and infostring.
     * \li call registerHandler(tag,this).
     */
    XFCIMPORT XFcCFLFilterNone();
    //! Processes (e.g. compress, encrypt..) data.
    XFCIMPORT virtual void process(INT8 *aDataIn, INT8 **aDataOut,
                                   UINT32 aDataInSize,
                                   UINT32 &aDataOutSize);
    //! Reverse processes data (e.g. decompress, decrypt..) data.
    XFCIMPORT virtual void reverseProcess(INT8 *aDataIn, INT8 **aDataOut,
                                          UINT32 aDataInSize,
                                          UINT32 &aDataOutSize);
};


#endif // XFC_CORE_XFCCFL_H_INCLUDED

