/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * $Id: XFuConfigurationData.cpp,v 1.12 2003/08/12 13:34:08 lars Exp $
 * $Date: 2003/08/12 13:34:08 $
 * $Revision: 1.12 $
 */

#include <xforge.h>
#include <xfutil/XFuPrinter.h>
#include <xfutil/XFuRLESpritePrinter.h>
#include <xfutil/XFuTokenizer.h>
#include <xfutil/XFuConfigurationData.h>


#define XFUCD_TYPE_DELIMITER_CHAR       (CHAR)':'
#define XFUCD_TYPE_DELIMITER_STR        XFCSTR(":")
#define XFUCD_TYPE_IMAGE_SHORT_CHAR     (CHAR)'i'
#define XFUCD_TYPE_IMAGE_SHORT_STR      XFCSTR("i")
#define XFUCD_TYPE_IMAGE_LONG           XFCSTR("image")
#define XFUCD_TYPE_PRINTER_SHORT_CHAR   (CHAR)'p'
#define XFUCD_TYPE_PRINTER_SHORT_STR    XFCSTR("p")
#define XFUCD_TYPE_PRINTER_LONG         XFCSTR("printer")
#define XFUCD_TYPE_SOUND_SHORT_CHAR     (CHAR)'s'
#define XFUCD_TYPE_SOUND_SHORT_STR      XFCSTR("s")
#define XFUCD_TYPE_SOUND_LONG           XFCSTR("sound")
#define XFUCD_TYPE_MUSIC_SHORT_CHAR     (CHAR)'m'
#define XFUCD_TYPE_MUSIC_SHORT_STR      XFCSTR("m")
#define XFUCD_TYPE_MUSIC_LONG           XFCSTR("music")


XFuConfigurationData::XFuConfigurationData() :
    mImages(NULL), mPrinters(NULL), mSounds(NULL), mMusics(NULL)
{
}


XFuConfigurationData * XFuConfigurationData::create()
{
    XFuConfigurationData *res = new XFuConfigurationData;
    if (res != NULL && !res->init())
    {
        delete res;
        return NULL;
    }
    return res;
}


XFuConfigurationData * XFuConfigurationData::create(const CHAR *aFilename)
{
    XFuConfigurationData *res = create();
    if (res != NULL)
    {
        if (!res->load(aFilename))
        {
            delete res;
            return NULL;
        }
    }
    return res;
}


XFuConfigurationData * XFuConfigurationData::create(XFcFile *aFile)
{
    XFuConfigurationData *res = create();
    if (res != NULL)
    {
        if (!res->load(aFile))
        {
            delete res;
            return NULL;
        }
    }
    return res;
}


INT XFuConfigurationData::init()
{
    mImages = new ImageSet;
    mPrinters = new PrinterSet;
    mSounds = new SoundSet;
    mMusics = new MusicSet;
    if (mImages == NULL ||
        mPrinters == NULL ||
        mSounds == NULL ||
        mMusics == NULL)
    {
        delete mImages;
        delete mPrinters;
        delete mSounds;
        delete mMusics;
        return 0;
    }
    return 1;
}


XFuConfigurationData::~XFuConfigurationData()
{
    // delete all images
    ImageSet::iterator imageIt = mImages->begin();
    for (; imageIt != mImages->end(); ++imageIt)
        delete imageIt.getValue();
    delete mImages;
    mImages = NULL;

    // delete all printers
    PrinterSet::iterator printerIt = mPrinters->begin();
    for (; printerIt != mPrinters->end(); ++printerIt)
        delete printerIt.getValue();
    delete mPrinters;
    mPrinters = NULL;

    // delete all sounds
    SoundSet::iterator soundIt = mSounds->begin();
    for (; soundIt != mSounds->end(); ++soundIt)
        delete soundIt.getValue();
    delete mSounds;
    mSounds = NULL;

    // delete all music
    MusicSet::iterator musicIt = mMusics->begin();
    for (; musicIt != mMusics->end(); ++musicIt)
        delete musicIt.getValue();
    delete mMusics;
    mMusics = NULL;

    // parent cleanup
    XFuConfiguration::clear();
}


CHAR * XFuConfigurationData::get(const CHAR *aKey)
{
    XFCASSERT(aKey != NULL && "XFuConfigurationData::get");
    return XFuConfiguration::get(aKey);
}


CHAR * XFuConfigurationData::makePrefixedKey(const CHAR aPrefix, const CHAR *aKey)
{
    CHAR *key = new CHAR[XFcStringToolkit::getLength(aKey) + 3];
    XFcStringToolkit::format(key, "%c%c%s", aPrefix, XFUCD_TYPE_DELIMITER_CHAR, aKey);
    return key;
}


XFcGLResourceSurface * XFuConfigurationData::getImage(const CHAR *aKey)
{
    XFCASSERT(aKey != NULL && "XFuConfigurationData::getImage");
    CHAR *key = makePrefixedKey(XFUCD_TYPE_IMAGE_SHORT_CHAR, aKey);
    ImageSet::iterator it = mImages->find(XFuStringKey(get(key)));
    delete[] key;
    if (it.isValid())
    {
        if (it.getValue() == NULL)
            loadImage(it);
        return it.getValue();
    }
    else
        return NULL;
}


XFuPrinter * XFuConfigurationData::getPrinter(const CHAR *aKey)
{
    XFCASSERT(aKey != NULL && "XFuConfigurationData::getPrinter");
    CHAR *key = makePrefixedKey(XFUCD_TYPE_PRINTER_SHORT_CHAR, aKey);
    PrinterSet::iterator it = mPrinters->find(XFuStringKey(get(key)));
    delete[] key;
    if (it.isValid())
    {
        if (it.getValue() == NULL)
            loadPrinter(it);
        return it.getValue();
    }
    else
        return NULL;
}


XFcRectangle XFuConfigurationData::parseRectangleString(const CHAR *aValue)
{
    XFcRectangle rect(0, 0, 0, 0);
    XFuTokenizer tok;
    INT32 tokens;

    if (aValue != NULL)
    {
        tok.tokenize(aValue, XFCSTR(","));
        tokens = tok.getTokenCount();
        XFCASSERT(tokens >= 1 && tokens <= 4 && "XFuConfigurationData::parseRectangleString: Invalid tokens.");
        
        if (tokens >= 1) rect.mX = XFcStringToolkit::toINT32(tok.getToken(0));
        if (tokens >= 2) rect.mY = XFcStringToolkit::toINT32(tok.getToken(1));
        if (tokens >= 3) rect.mWidth = XFcStringToolkit::toINT32(tok.getToken(2));
        if (tokens >= 4) rect.mHeight = XFcStringToolkit::toINT32(tok.getToken(3));
    }

    return rect;
}


INT XFuConfigurationData::getRectangle(XFcRectangle &aDest, const CHAR *aKey)
{
    XFCASSERT(aKey != NULL && "XFuConfigurationData::getRectangle");
    const CHAR *value = get(aKey);

    if (value != NULL)
    {
        aDest = parseRectangleString(value);
        return 1;
    }
    return 0;
}


XFuConfigurationDataSoundInfo * XFuConfigurationData::getSound(const CHAR *aKey)
{
    XFCASSERT(aKey != NULL && "XFuConfigurationData::getSound");
    CHAR *key = makePrefixedKey(XFUCD_TYPE_SOUND_SHORT_CHAR, aKey);
    SoundSet::iterator it = mSounds->find(XFuStringKey(get(key)));
    delete[] key;
    if (it.isValid())
        return it.getValue();
    else
        return NULL;
}


XFuConfigurationDataMusicInfo * XFuConfigurationData::getMusic(const CHAR *aKey)
{
    XFCASSERT(aKey != NULL && "XFuConfigurationData::getMusic");
    CHAR *key = makePrefixedKey(XFUCD_TYPE_MUSIC_SHORT_CHAR, aKey);
    MusicSet::iterator it = mMusics->find(XFuStringKey(get(key)));
    delete[] key;
    if (it.isValid())
        return it.getValue();
    else
        return NULL;
}


INT XFuConfigurationData::load(const CHAR *aFilename)
{
    XFCASSERT(aFilename != NULL && "XFuConfigurationData::load(const CHAR *)");
    return XFuConfiguration::load(aFilename);
}


INT XFuConfigurationData::load(XFcFile *aFile)
{
    XFCASSERT(aFile != NULL && "XFuConfigurationData::load(XFcFile *)");
    return XFuConfiguration::load(aFile);
}


void XFuConfigurationData::put(const CHAR *aKey, const CHAR *aValue)
{
    XFCASSERT(aKey != NULL && aValue != NULL && "XFuConfigurationData::put");
    if (aKey == NULL || aKey[0] == 0)
        return;

    XFuTokenizer tok;
    tok.tokenize(aKey, XFUCD_TYPE_DELIMITER_STR);

    if (tok.getTokenCount() > 1)
    {
        CHAR reformatPrefix = 0;
        const CHAR *type = tok.getToken(0);
        // TODO: Add type registration interface.
        if (XFcStringToolkit::compare(type, XFUCD_TYPE_IMAGE_SHORT_STR) == 0 ||
            XFcStringToolkit::compare(type, XFUCD_TYPE_IMAGE_LONG) == 0)
        {
            reformatPrefix = XFUCD_TYPE_IMAGE_SHORT_CHAR;
            addImage(aValue);
        }
        else if (XFcStringToolkit::compare(type, XFUCD_TYPE_PRINTER_SHORT_STR) == 0 ||
                 XFcStringToolkit::compare(type, XFUCD_TYPE_PRINTER_LONG) == 0)
        {
            reformatPrefix = XFUCD_TYPE_PRINTER_SHORT_CHAR;
            addPrinter(aValue);
        }
        else if (XFcStringToolkit::compare(type, XFUCD_TYPE_SOUND_SHORT_STR) == 0 ||
                 XFcStringToolkit::compare(type, XFUCD_TYPE_SOUND_LONG) == 0)
        {
            reformatPrefix = XFUCD_TYPE_SOUND_SHORT_CHAR;
            addSound(aValue);
        }
        else if (XFcStringToolkit::compare(type, XFUCD_TYPE_MUSIC_SHORT_STR) == 0 ||
                 XFcStringToolkit::compare(type, XFUCD_TYPE_MUSIC_LONG) == 0)
        {
            reformatPrefix = XFUCD_TYPE_MUSIC_SHORT_CHAR;
            addMusic(aValue);
        }

        // If reformatPrefix is set, reformat the key with the shortened prefix
        // and add the entry with the revised key. Otherwise the original key
        // is added.
        if (reformatPrefix != 0)
        {
            const CHAR *key = tok.getToken(1);
            CHAR *newkey = new CHAR[XFcStringToolkit::getLength(key) + 3];
            XFcStringToolkit::format(newkey, "%c%c%s", reformatPrefix, XFUCD_TYPE_DELIMITER_CHAR, key);
            XFuConfiguration::put(newkey, aValue);
            delete[] newkey;
        }
        else
            XFuConfiguration::put(aKey, aValue);
    }
    else
        XFuConfiguration::put(aKey, aValue);
}


void XFuConfigurationData::addImage(const CHAR *aValue)
{
    ImageSet::iterator it = mImages->find(XFuStringKey(aValue));
    if (!it.isValid())
    {
        XFuStringKey valueKey(aValue);
        mImages->put(valueKey, NULL);

        if (!mDeferredLoadingEnabled)
        {
            ImageSet::iterator it = mImages->find(valueKey);
            XFCASSERT(it.isValid() && "XFuConfigurationData::addImage: Image property not found!");
            loadImage(it);
        }
    }
}


void XFuConfigurationData::loadImage(ImageSet::iterator &aIterator)
{
    // don't try load the image if it has already been loaded
    if (aIterator.getValue() != NULL)
        return;

    XFuTokenizer tok;

    CHAR *key = XFcStringToolkit::copy(aIterator.getKey().mKey);
    tok.tokenize(key, XFCSTR(","));
    const CHAR *filename = NULL;
    INT32 format = XFCGF_DEFAULT;

    if (tok.getTokenCount() > 1)
    {
        filename = tok.getToken(0);
        format = XFcStringToolkit::toINT32(tok.getToken(1));
    }
    else
        filename = key;

    XFcGLResourceSurface *rs = XFcGLResourceSurface::create(filename, format);
    XFCASSERT(rs && "XFuConfigurationData::loadImage: Cannot create resource surface image!");
    aIterator.setValue(rs);

    delete[] key;
}


void XFuConfigurationData::addPrinter(const CHAR *aValue)
{
    PrinterSet::iterator it = mPrinters->find(XFuStringKey(aValue));
    if (!it.isValid())
    {
        XFuStringKey valueKey(aValue);
        mPrinters->put(valueKey, NULL);

        if (!mDeferredLoadingEnabled)
        {
            PrinterSet::iterator it = mPrinters->find(valueKey);
            XFCASSERT(it.isValid() && "XFuConfigurationData::addPrinter: Printer property not found!");
            loadPrinter(it);
        }
    }
}


void XFuConfigurationData::loadPrinter(PrinterSet::iterator &aIterator)
{
    // don't try load the printer if it has already been loaded
    if (aIterator.getValue() != NULL)
        return;

    XFuPrinter *pr = NULL;
    XFuTokenizer tok;

    CHAR *key = XFcStringToolkit::copy(aIterator.getKey().mKey);
    tok.tokenize(key, XFCSTR(","));
    const CHAR *filename = tok.getToken(0);
    XFCASSERT(tok.getTokenCount() >= 3 && "XFuConfigurationData::addPrinter: Not enough tokens for printer!");
    INT32 type = XFcStringToolkit::toINT32(tok.getToken(2));
    XFCASSERT((type == 0 || type == 1) && "XFuConfigurationData::addPrinter: Unknown printer type!");

    if (tok.getTokenCount() > 3)
    {
        UINT32 colorkey = (UINT32)XFcStringToolkit::toINT32(tok.getToken(3));
        if (type == 0)
            pr = XFuPrinter::create(filename, colorkey);
        else if (type == 1)
            pr = XFuRLESpritePrinter::create(filename, 0xffffff, colorkey);
    }
    else
    {
        if (type == 0)
            pr = XFuPrinter::create(filename);
        else if (type == 1)
            pr = XFuRLESpritePrinter::create(filename);
    }
    XFCASSERT(pr != NULL && "XFuConfigurationData::loadPrinter: Cannot create printer!");
    pr->setLetterSpacing(XFcStringToolkit::toINT32(tok.getToken(1)));
    aIterator.setValue(pr);
    
    delete[] key;
}


// TODO: Add possible loading of sound when sounds are changed to resources.
void XFuConfigurationData::addSound(const CHAR *aValue)
{
    SoundSet::iterator it = mSounds->find(XFuStringKey(aValue));
    if (!it.isValid())
    {
        XFuTokenizer tok;

        tok.tokenize(aValue, XFCSTR(","));

        XFuConfigurationDataSoundInfo *si = new XFuConfigurationDataSoundInfo;

        if (tok.getTokenCount() == 1)
        {
            si->mFilename = XFcStringToolkit::copy(aValue);
        }
        else
        {
            si->mFilename = XFcStringToolkit::copy(tok.getToken(0));
            if ((tok.getTokenCount() > 1) && (XFcStringToolkit::toINT32(tok.getToken(1)) != -1))
            {
                si->mSamplingRate = XFcStringToolkit::toFLOAT32(tok.getToken(1));
                si->mFlags |= XFUCDAIF_SAMPLING_RATE;
            }
            if ((tok.getTokenCount() > 2) && (XFcStringToolkit::toINT32(tok.getToken(2)) != -1))
            {
                si->mVolume = XFcStringToolkit::toFLOAT32(tok.getToken(2));
                si->mFlags |= XFUCDAIF_VOLUME;
            }
            if ((tok.getTokenCount() > 3) && (XFcStringToolkit::toINT32(tok.getToken(3)) != -1))
            {
                si->mPanning = XFcStringToolkit::toFLOAT32(tok.getToken(3));
                si->mFlags |= XFUCDAIF_PANNING;
            }
            if ((tok.getTokenCount() > 4) && (XFcStringToolkit::toINT32(tok.getToken(4)) != -1))
            {
                si->mPriority = (UINT16)XFcStringToolkit::toINT32(tok.getToken(4));
                si->mFlags |= XFUCDAIF_PRIORITY;
            }
            if ((tok.getTokenCount() > 5) && (XFcStringToolkit::toINT32(tok.getToken(5)) != -1))
            {
                si->mLooping = XFcStringToolkit::toINT32(tok.getToken(5));
                if (si->mLooping) si->mFlags |= XFUCDAIF_LOOPING;
            }
            if ((tok.getTokenCount() > 6) && (XFcStringToolkit::toINT32(tok.getToken(6)) != -1))
            {
                si->mLoopStart = XFcStringToolkit::toINT32(tok.getToken(6));
                si->mFlags |= XFUCDAIF_LOOPSTART;
            }
            if ((tok.getTokenCount() > 7) && (XFcStringToolkit::toINT32(tok.getToken(7)) != -1))
            {
                si->mLoopEnd = XFcStringToolkit::toINT32(tok.getToken(7));
                si->mFlags |= XFUCDAIF_LOOPEND;
            }
        }

        mSounds->put(XFuStringKey(aValue), si);
    }
}


// TODO: Add possible loading of music when musics are changed to resources.
void XFuConfigurationData::addMusic(const CHAR *aValue)
{
    MusicSet::iterator it = mMusics->find(XFuStringKey(aValue));
    if (!it.isValid())
    {
        XFuTokenizer tok;

        tok.tokenize(aValue, XFCSTR(","));

        XFuConfigurationDataMusicInfo *mi = new XFuConfigurationDataMusicInfo;

        XFCASSERT("addMusic: Invalid amount of parameters for music resource" && tok.getTokenCount() >= 4);

        mi->mFilename = XFcStringToolkit::copy(tok.getToken(0));
        mi->mSamplingRate = XFcStringToolkit::toFLOAT32(tok.getToken(1));
        mi->m16Bit = XFcStringToolkit::toINT32(tok.getToken(2));
        mi->mStereo = XFcStringToolkit::toINT32(tok.getToken(3));
        mi->mFlags |= XFUCDAIF_SAMPLING_RATE;

        if ((tok.getTokenCount() > 4) && (XFcStringToolkit::toINT32(tok.getToken(4)) != -1))
        {
            mi->mVolume = XFcStringToolkit::toFLOAT32(tok.getToken(4));
            mi->mFlags |= XFUCDAIF_VOLUME;
        }
        if ((tok.getTokenCount() > 5) && (XFcStringToolkit::toINT32(tok.getToken(5)) != -1))
        {
            mi->mPriority = (UINT16)XFcStringToolkit::toINT32(tok.getToken(5));
            mi->mFlags |= XFUCDAIF_PRIORITY;
        }

        mMusics->put(XFuStringKey(aValue), mi);
    }
}


void XFuConfigurationData::setDeferredLoadingEnabled(INT aEnabled)
{
    mDeferredLoadingEnabled = aEnabled;
}

