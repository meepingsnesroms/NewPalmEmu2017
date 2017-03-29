/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * $Id: XFuConfigurationData.h,v 1.17 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.17 $
 */

#ifndef XFUCONFIGURATIONDATA_H_INCLUDED
#define XFUCONFIGURATIONDATA_H_INCLUDED


#include <xfutil/XFuConfiguration.h>

class XFcGLResourceSurface;
class XFuPrinter;


//! Defines audio info flags for configuration data audio properties.
/*! Audio properties' audio info flags determine which optional fields
 *  have been filled with data read from the configuration data file.
 */
enum XFUCONFIGURATIONDATA_AUDIO_INFO_FLAGS
{
    XFUCDAIF_NONE           = 0x00,     //!< No optional fields present.
    XFUCDAIF_SAMPLING_RATE  = 0x01,     //!< Sampling rate field.
    XFUCDAIF_VOLUME         = 0x02,     //!< Volume field.
    XFUCDAIF_PANNING        = 0x04,     //!< Panning field.
    XFUCDAIF_PRIORITY       = 0x08,     //!< Priority field.
    XFUCDAIF_LOOPING        = 0x10,     //!< Looping field.
    XFUCDAIF_LOOPSTART      = 0x20,     //!< Loop start field.
    XFUCDAIF_LOOPEND        = 0x40,     //!< Loop end field.
};


//! Sound sample configuration data type.
/*! \sa XFUCONFIGURATIONDATA_AUDIO_INFO_FLAGS
 */
class XFuConfigurationDataSoundInfo
{

public:

    CHAR *mFilename;            //!< Filename of the sound sample.
    FLOAT32 mSamplingRate;      //!< Sampling rate.
    REAL mVolume;               //!< Volume (1.0=original volume).
    REAL mPanning;              //!< Panning [0..1].
    UINT16 mPriority;           //!< Priority.
    INT mLooping;               //!< Non-zero if the sample is looping.
    INT32 mLoopStart;           //!< Loop start point.
    INT32 mLoopEnd;             //!< Loop end point.
    UINT32 mFlags;              //!< Flags, see XFUCONFIGURATIONDATA_AUDIO_INFO_FLAGS.

    XFuConfigurationDataSoundInfo() :
        mFilename(NULL), mSamplingRate(0.0f), mVolume(REALi(0)), mPanning(REALi(0)),
        mPriority(0), mLooping(0), mLoopStart(0), mLoopEnd(0), mFlags(0) {}

    virtual ~XFuConfigurationDataSoundInfo()
    {
        delete[] mFilename;
        mFilename = NULL;
    }

};


//! Music configuration data type.
/*! \sa XFUCONFIGURATIONDATA_AUDIO_INFO_FLAGS
 */
class XFuConfigurationDataMusicInfo
{

public:

    CHAR *mFilename;            //!< Filename of the sound sample.
    FLOAT32 mSamplingRate;      //!< Sampling rate.
    INT m16Bit;                 //!< Non-zero if 16 bit mixing requested, otherwise 8 bit.
    INT mStereo;                //!< Non-zero if stereo requested, otherwise mono.
    REAL mVolume;               //!< Volume (1.0=original volume).
    UINT16 mPriority;           //!< Priority.
    UINT32 mFlags;              //!< Flags, see XFUCONFIGURATIONDATA_AUDIO_INFO_FLAGS.

    XFuConfigurationDataMusicInfo() :
        mFilename(NULL), mSamplingRate(0.0f), m16Bit(0), mStereo(0),
        mVolume(REALi(0)), mPriority(0), mFlags(0) {}

    virtual ~XFuConfigurationDataMusicInfo()
    {
        delete[] mFilename;
        mFilename = NULL;
    }

};


//! Configured data container.
/*!
 * Reads and parses a set of configuration data keys from a file.
 * The format of the configuration file is such that there is one property
 * on each row in a text file. Each property is a pair of a key and a value,
 * delimited by a '=' char, for example:
 * \code fileName = HelloWorld.xff \endcode
 *
 * Optionally the key can also have a type prefix which is delimited from the
 * rest of the key with a ':' (colon) char, for example:
 * \code image : cursor = arrow.tga \endcode
 * Recognized builtin types are parsed when the configuration file is processed.
 * For some types the data is also loaded at the same time. Note that for
 * recognized types the key is reformatted to use the short form before adding
 * to the data container, which affects only fetching of data with regular
 * get-method instead of a type specific getType-style method. If multiple keys
 * refer to exact same value which results in loading of a resource, the
 * resource is loaded only once so that the same loaded resource is shared
 * between the keys.
 *
 * Builtin types have getType-style methods which can be used to read the
 * data easily by the key omitting the type prefix. Builtin types also have
 * both long and short forms of the type, so the previous example could be
 * also written:
 * \code i:cursor = arrow.tga \endcode
 *
 * Leading and trailing spaces are trimmed. Lines starting with character '#'
 * are treated as comment lines and are ignored. Optional parts of
 * value strings can be omitted.
 *
 * Recognized builtin types:
 * <table><tr>
 * <th>Long Type<th>Short<br>Type<th>Value String Format and Description
 *
 * <tr><td>\c image <td>\c i
 *   <td>Value string: <tt>filename,type</tt>
 *   \li filename - filename of image which is loaded as a XFcGLResourceSurface
 *                  when the configuration file is processed.
 *   \li type - optional image format as a number (see XFCGFXFORMAT).
 *
 *   Example:
 *   \code
 *   image:menu.cursor = arrow.tga
 *   i:splash = splash.tga \endcode
 *
 * <tr><td>\c printer <td>\c p
 *   <td>Value string: <tt>filename,spacing,type,colorkey</tt>
 *   \li filename - filename where to load the printer font image from.
 *   \li spacing - default spacing for the printer.
 *   \li type - 0:standard printer (XFuPrinter), 1:RLE sprite printer (XFuRLESpritePrinter).
 *   \li colorkey - optional color key, hex strings can be used with 0x or # prefix.
 *
 *   Example:
 *   \code
 *   printer:menu.printer = smallfont.tga,0,1,#0000ff
 *   p:digitprinter = digits.tga,2,0 \endcode
 *
 * <tr><td>\c sound <td>\c s
 *   <td>Value string: <tt>filename,samplingrate,volume,panning,priority,looping,loopstart,loopend</tt>
 *   \li filename - filename of a sound sample.
 *   \li samplingrate - optional sampling rate as a real number (-1 = default).
 *   \li volume - optional volume as a real number (1.0 = original volume, -1 = default).
 *   \li panning - optional panning as a real number [0..1] (-1 = default).
 *   \li priority - optional priority as an integer [0..65535] (-1 = default).
 *   \li looping - optional looping flag, 0:no looping, 1:looping.
 *   \li loopstart - optional loop start point as an integer.
 *   \li loopend - optional loop end point as an integer.
 *
 *   Example:
 *   \code
 *   sound:menu.select = menuselect.wav
 *   s:menu.move = menumove.wav,-1,0.5 \endcode
 *
 * <tr><td>\c music <td>\c m
 *   <td>Value string: <tt>filename,samplingrate,chanmode,bitmode,volume,priority</tt>
 *   \li filename - filename of the music data.
 *   \li samplingrate - sampling rate for mixing the music as a real number.
 *   \li chanmode - channel mode, 0:mono, 1:stereo.
 *   \li bitmode - bits to use, 0:8 bits, 1:16 bits.
 *   \li volume - optional volume as a real number (1.0 = original volume, -1 = default).
 *   \li priority - optional priority as an integer [0..65535].
 *
 *   Example:
 *   \code
 *   music:menumusic = menu.xm,16000,0,0,0.3,0
 *   music:gamemusic = game.xm,8000,0,0,0.15,0 \endcode
 *
 * </table>
 *
 * \note XFuConfigurationData object owns all objects it has loaded, so you shouldn't
 *       delete manually any objects you access via this class.
 * \todo Type handler registration interface.
 *
 * \sa getImage
 * \sa XFcGLResourceSurface
 * \sa getPrinter
 * \sa XFuPrinter
 * \sa XFuRLESpritePrinter
 * \sa getRectangle
 * \sa XFcRectangle
 * \sa getSound
 * \sa XFuConfigurationDataSoundInfo
 * \sa getMusic
 * \sa XFuConfigurationDataMusicInfo
 * \sa XFuConfiguration
 * \sa XFcAudio
 */
class XFuConfigurationData : public XFuConfiguration
{

public:

    //! Static constructor.
    /*! \return new configuration data object if successful, or NULL if unsuccessful.
     */
    static XFuConfigurationData * create();

    //! Static constructor.
    /*! \param aFilename filename of configuration data to load.
     * \return new configuration data object if successful, or NULL if unsuccessful.
     */
    static XFuConfigurationData * create(const CHAR *aFilename);

    //! Static constructor.
    /*! \param aFile open file pointing to configuration data to load.
     * \return new configuration data object if successful, or NULL if unsuccessful.
     * \note Configuration data is assumed to continue to end of the file.
     */
    static XFuConfigurationData * create(XFcFile *aFile);
    
    //! Virtual destructor.
    virtual ~XFuConfigurationData();

    //! Returns the value of a property as a string, or NULL if not found.
    /*! \param aKey key of the property to return.
     */
    virtual CHAR * get(const CHAR *aKey);

    //! Returns a configuration data image by key, or NULL if not found.
    /*! \param aKey key of the image omitting the type prefix and delimiter.
     * \return pointer to the image surface, or NULL if not found.
     */
    virtual XFcGLResourceSurface * getImage(const CHAR *aKey);

    //! Returns a configuration data printer by key, or NULL if not found.
    /*! \param aKey key of the printer omitting the type prefix and delimiter.
     * \return pointer to the printer, or NULL if not found.
     */
    virtual XFuPrinter * getPrinter(const CHAR *aKey);

    //! Returns a configuration data sound info by key, or NULL if not found.
    /*! \param aKey key of the sound omitting the type prefix and delimiter.
     * \return pointer to sound info, or NULL if not found.
     */
    virtual XFuConfigurationDataSoundInfo * getSound(const CHAR *aKey);

    //! Returns a configuration data music info by key, or NULL if not found.
    /*! \param aKey key of the music omitting the type prefix and delimiter.
     * \return pointer to music info, or NULL if not found.
     */
    virtual XFuConfigurationDataMusicInfo * getMusic(const CHAR *aKey);

    //! Gets a property value by key, and then parses and returns the value as a rectangle.
    /*!
     * Rectangle value string format: <tt>x,y,width,height</tt>.
     *   \li x - X-component of the rectangle as an integer.
     *   \li y - optional Y-component of the rectangle as an integer.
     *   \li width - optional width of the rectangle as an integer.
     *   \li height - optional height of the rectangle as an integer.
     *
     *   Example:
     *   \code
     *   rectangle:laptime.position = 10,10
     *   r:viewport = 4,4,160,120 \endcode
     *
     * \param aDest returned rectangle, if successful.
     * \param aKey key of the property value to be parsed.
     * \return 1 if successful (rectangle was found), or 0 if unsuccessful.
     */
    virtual INT getRectangle(XFcRectangle &aDest, const CHAR *aKey);

    //! Sets the value of a property.
    /*! If the key contains a type prefix delimited by ':' character from the
     *  rest of the key, and the type is a recognized builtin type, the value
     *  is parsed and possibly loaded according to the type. Properties with
     *  recognized builtin types can be accessed with type specific
     *  getType-style method. If the possible type prefix is unrecognized then
     *  the value must be accessed with get-method.
     * \param aKey full key of the property to set value for.
     * \param aValue value of the property.
     */
    virtual void put(const CHAR *aKey, const CHAR *aValue);

    //! Loads new configuration file and merges its data to the current set.
    /*! \param aFilename filename of the configuration data file to load.
     * \return 1 if successful, 0 if unsuccessful (e.g. file not found).
     */
    virtual INT load(const CHAR *aFilename);

    //! Loads new configuration file and merges its data to the current set.
    /*! \param aFile open file pointing to the configuration data to load.
     * \return 1 if successful, 0 if unsuccessful (e.g. file not found).
     * \note Configuration data is assumed to continue to end of the file.
     */
    virtual INT load(XFcFile *aFile);
    
    //! Parses a rectangle value string.
    /*! \return rectangle filled with available values, or an empty rectangle (0,0,0,0) if unsuccessful.
     */
    static XFcRectangle parseRectangleString(const CHAR *aValue);

    //! Sets deferred loading mode status.
    /*! When deferred loading mode is enabled, all recognized object types held
     *  by this configuration data container are loaded only when an object is
     *  requested for the first time. By default deferred loading is disabled
     *  and all recognized types are loaded on load of a configuration file.
     *  Deferred loading must be enabled before calling load.
     */
    void setDeferredLoadingEnabled(INT aEnabled);

protected:

    //! Internal image container type.
    /*! \internal */
    typedef XFcHashtable<XFuStringKey, XFcGLResourceSurface *> ImageSet;
    //! Internal printer container type.
    /*! \internal */
    typedef XFcHashtable<XFuStringKey, XFuPrinter *> PrinterSet;
    //! Internal sound info container type.
    /*! \internal */
    typedef XFcHashtable<XFuStringKey, XFuConfigurationDataSoundInfo *> SoundSet;
    //! Internal music info container type.
    /*! \internal */
    typedef XFcHashtable<XFuStringKey, XFuConfigurationDataMusicInfo *> MusicSet;

    //! Protected constructor.
    XFuConfigurationData();

    //! Initializes a newly constructed object.
    /*! \return 1 if successful, 0 if unsuccessful.
     */
    INT init();

    //! Adds and possibly loads a new image to the internal image container.
    void addImage(const CHAR *aValue);
    //! Adds and possibly loads a new printer to the internal printer container.
    void addPrinter(const CHAR *aValue);
    //! Adds a new sound to the internal sound container.
    void addSound(const CHAR *aValue);
    //! Adds a new music to the internal music container.
    void addMusic(const CHAR *aValue);

    //! Loads a new image to the internal image container.
    void loadImage(ImageSet::iterator &aIterator);
    //! Loads a new printer to the internal printer container.
    void loadPrinter(PrinterSet::iterator &aIterator);

    //! Allocates and returns a new key with a specified prefix char.
    CHAR * makePrefixedKey(const CHAR aPrefix, const CHAR *aKey);

    //! Non-zero if deferred loading is enabled.
    INT mDeferredLoadingEnabled;

    ImageSet *mImages;          //!< Internal image container.
    PrinterSet *mPrinters;      //!< Internal printer container.
    SoundSet *mSounds;          //!< Internal sound container.
    MusicSet *mMusics;          //!< Internal music container.

};


#endif // !XFUCONFIGURATIONDATA_H_INCLUDED

