/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Core enumerations
 * 
 * $Id: XFcCoreEnums.h,v 1.30.2.1 2004/01/22 11:15:08 jouni Exp $
 * $Date: 2004/01/22 11:15:08 $
 * $Revision: 1.30.2.1 $
 */

#ifndef XFC_CORE_COREENUMS_H_INCLUDED
#define XFC_CORE_COREENUMS_H_INCLUDED


//! Constants for platform id.
enum XFCPLATFORM
{
    XFCPLATFORM_WINDOWS     = 0x01000000, //!< Desktop windows platform (simulator).
    XFCPLATFORM_EPOC        = 0x02000000, //!< EPOC
    XFCPLATFORM_S60         = 0x024F6001, //!< Nokia Series 60
    XFCPLATFORM_N7650       = 0x024E6001, //!< Nokia 7650
    XFCPLATFORM_N3650       = 0x024F6002, //!< Nokia 3650
    XFCPLATFORM_NGAGE       = 0x024F6003, //!< Nokia N-Gage
    XFCPLATFORM_SENDOX      = 0x024F6004, //!< SendoX
    XFCPLATFORM_SIEMENSSX1  = 0x024F6005, //!< Siemens SX1
    XFCPLATFORM_N6600       = 0x024F6006, //!< Nokia 6600
    XFCPLATFORM_SEP800      = 0x02531e01, //!< Sony-Ericcsson P800
    XFCPLATFORM_LINUX       = 0x03000000, //!< Linux 
    XFCPLATFORM_WINCE       = 0x04000000, //!< WinCE 
    XFCPLATFORM_IPAQ3600    = 0x04013600, //!< Compaq iPaq 3600 (no diagonals)
    XFCPLATFORM_IPAQ3800    = 0x04013800, //!< Compaq iPaq 3800 (needs display hack)
    XFCPLATFORM_PALM        = 0x05000000, //!< PalmOS 
    XFCPLATFORM_MASK        = 0xff000000  //!< Mask for the major platform type
};



//! Constants for sprite blend modes.
enum XFCBLENDMODE_2D
{
    XFCBLEND_NONE,              //!< No blending (default).
    XFCBLEND_ALPHA,             //!< Alpha blend (crossfade).
    XFCBLEND_ALPHA_FAST,        //!< Fast 50:50 (avg) alpha.
    XFCBLEND_MUL,               //!< Multiplicative blending.
    XFCBLEND_MUL_FAST,          //!< Fast 100% mul blend.
    XFCBLEND_ADD,               //!< Additive blend.
    XFCBLEND_ADD_FAST,          //!< Fast 100% add blend.
    XFCBLEND_INVMUL,            //!< Inverse multiplication.
    XFCBLEND_INVMUL_FAST        //!< Fast 100% inverse mul blend.
};


//! Constants for surface transformation flags.
enum XFCSURFACETRANSFORM_2D
{
    XFCTRANSFORM_FLIP_HORIZONTAL = 0x1,         //!< Flip surface horizontally (up/down).
    XFCTRANSFORM_FLIP_VERTICAL = 0x2,           //!< Flip surface vertically (left/right).
    XFCTRANSFORM_ROTATE_0 = (0x0 << 2),         //!< Perform no rotation.
    XFCTRANSFORM_ROTATE_90 = (0x1 << 2),        //!< Rotate 90 degrees clockwise.
    XFCTRANSFORM_ROTATE_180 = (0x2 << 2),       //!< Rotate 180 degrees clockwise.
    XFCTRANSFORM_ROTATE_270 = (0x3 << 2),       //!< Rotate 270 degrees clockwise.
    XFCTRANSFORM_ROTATE_MASK = (0x3 << 2)       //!< Used internally.
};


//! Misc gfx flags.
enum XFCGFXFLAGS 
{
    XFCGFX_DISCARDCONTENTS = 256, //!< Discard contents on lock.
    XFCGFX_DISCARDCHANGES  = 512  //!< Discard changes on unlock.    
};


//! Constants for framebuffer formats.
// Note: Number allocation must be linear and default must be zero.
enum XFCGFXFORMAT 
{
    XFCGF_DEFAULT         = 0,   //!< Preferred (hardware-supported) mode.
    XFCGF_R5G6B5          = 1,   //!< 16-bit color.
    XFCGF_X8R8G8B8        = 2,   //!< 8+24-bit color (8 bit for padding).
    XFCGF_A1R5G5B5        = 3,   //!< 16-bit color with 1-bit alpha.
    XFCGF_A8R8G8B8        = 4,   //!< 32-bit color with 8-bit alpha.
    XFCGF_X6X5X5          = 5,   //!< Special 32-bit format with 5:6:5:5:6:5 bit mask, XGXRXB.
    XFCGF_1X5X5X5         = 6,   //!< same as XFCGF_X6X5X5, with topmost bit as alpha.
    XFCGF_PAL55X5         = 7,   //!< Paletted 55X5bit format (512B palette in the beginning of 8bit surface)
    XFCGF_R5G5X1B5        = 8,   //!< 16-bit color with 5 bits in green component.
    XFCGF_R5G5A1B5        = 9,   //!< 16-bit color with 5 bits in green component, 1-bit alpha in LSB of green component.
    XFCGF_PREMULA8R8G8B8  = 10   //!< 32-bit color with 8-bit alpha, color components are premultiplied with the alpha
};


//! Bitmasks for resource type.
enum XFCRESOURCEFLAGS
{
    XFCRESOURCE_DEFAULT         = 0x0,  //!< Resource is movable and removable.
    XFCRESOURCE_NONREMOVABLE    = 0x1,  //!< Resource is movable and non-removable.
    XFCRESOURCE_NONMOVABLE      = 0x3   //!< Resource is non-movable and non-removable.
};


//! Device state events.
enum XFCDEVICESTATEEVENTS
{
    XFCDSE_FOCUSLOST = 1, //!< Application has lost focus.
    XFCDSE_FOCUSGAIN,     //!< Application has (re)gained focus.
    XFCDSE_AUDIOLOST,     //!< Application has lost audio. Application can try to re-init audio later.
    XFCDSE_KILLSIGNAL,    //!< Operating system tells program to terminate.
    XFCDSE_MEDIACHANGED,  //!< Removable media has been removed or inserted.
    XFCDSE_LOWMEMORY,     //!< Operating system is low on memory. (Freeing memory from X-Forge memory pool won't help).
    XFCDSE_PHONEEVENT,    //!< Some phone event (incoming call, SMS, etc) has occured.
    XFCDSE_LOWBATTERY     //!< Low battery warning; game should not start any power-intensive operations (such as a race in a racing game)
};

enum XFCPHONEEVENT
{
    XFCPE_IDLE,
    XFCPE_DIALLING,
    XFCPE_RINGING,
    XFCPE_ANSWERING,
    XFCPE_CONNECTING,
    XFCPE_CONNECTED,
    XFCPE_HANGINGUP
};

//! Recommendations what to do when some device state event happens.
enum XFCDEVICESTATEEVENTSEVERITY
{
    XFCDSE_SEVERITY_NOTE = 0, //!< Application may choose to ignore this event.
    XFCDSE_SEVERITY_MODERATE, //!< Application should go to a pause mode, and shut down audio.
    XFCDSE_SEVERITY_CRITICAL  //!< Application should shut down its threads and terminate immediately.
};


//! Memory allocation flags
enum XFCMEMORYFLAGS
{
    XFCMEMORY_DEFAULT = 0,     //! Normal memory allocation.
    XFCMEMORY_TEMPORARY = 1    //! Hint that the allocation is temporary and short term.
};

//! Out of memory action flags
enum XFCOUTOFMEMORYACTION
{
    XFCOMA_NONE = 0,           //! Do nothing when memory runs out.
    XFCOMA_PANIC = 1,          //! Cause a system panic when memory runs out
    XFCOMA_ASSERT = 2          //! Cause assertion failure in debug builds
};

//! Device idle mode flags
enum XFCIDLEMODE
{
    XFCIM_ACTIVE = 0,          //! Default: keep device active even though user does nothing
    XFCIM_IDLE = 1             //! Let the device's idle timeouts run
};

//! List of all possible locales
enum XFCLOCALES
{
    XFCLOC_NONE = 0,
    XFCLOC_AFAR, 
    XFCLOC_ABKHAZIAN,
    XFCLOC_AFRIKAANS,
    XFCLOC_AMHARIC,
    XFCLOC_ARABIC,
    XFCLOC_ASSAMESE,
    XFCLOC_AYMARA,
    XFCLOC_AZERBAIJANI,

    XFCLOC_BASHKIR,
    XFCLOC_BYELORUSSIAN,
    XFCLOC_BULGARIAN,
    XFCLOC_BIHARI,
    XFCLOC_BISLAMA,
    XFCLOC_BENGALI,
    XFCLOC_TIBETAN,
    XFCLOC_BRETON,

    XFCLOC_CATALAN,
    XFCLOC_CORSICAN,
    XFCLOC_CZECH,
    XFCLOC_WELSH,

    XFCLOC_DANISH,
    XFCLOC_GERMAN,
    XFCLOC_BHUTANI,

    XFCLOC_GREEK,
    XFCLOC_ENGLISH,
    XFCLOC_ESPERANTO,
    XFCLOC_SPANISH,
    XFCLOC_ESTONIAN,
    XFCLOC_BASQUE,

    XFCLOC_PERSIAN,
    XFCLOC_FINNISH,
    XFCLOC_FIJI,
    XFCLOC_FAROESE,
    XFCLOC_FRENCH,
    XFCLOC_FRISIAN,

    XFCLOC_IRISH,
    XFCLOC_GAELIC,
    XFCLOC_GALICIAN,
    XFCLOC_GUARANI,
    XFCLOC_GUJARATI,

    XFCLOC_HAUSA,
    XFCLOC_HEBREW,
    XFCLOC_HINDI,
    XFCLOC_CROATIAN,
    XFCLOC_HUNGARIAN,
    XFCLOC_ARMENIAN,

    XFCLOC_INTERLINGUA,
    XFCLOC_INDONESIAN,
    XFCLOC_INTERLINGUE,
    XFCLOC_INUPIAK,
    XFCLOC_ICELANDIC,
    XFCLOC_ITALIAN,
    XFCLOC_INUKTITUT,

    XFCLOC_JAPANESE,
    XFCLOC_JAVANESE,

    XFCLOC_GEORGIAN,
    XFCLOC_KAZAKH,
    XFCLOC_GREENLANDIC,
    XFCLOC_CAMBODIAN,
    XFCLOC_KANNADA,
    XFCLOC_KOREAN,
    XFCLOC_KASHMIRI,
    XFCLOC_KURDISH,
    XFCLOC_KIRGHIZ,

    XFCLOC_LATIN,
    XFCLOC_LINGALA,
    XFCLOC_LAOTHIAN,
    XFCLOC_LITHUANIAN,
    XFCLOC_LATVIAN,

    XFCLOC_MALAGASY,
    XFCLOC_MAORI,
    XFCLOC_MACEDONIAN,
    XFCLOC_MALAYALAM,
    XFCLOC_MONGOLIAN,
    XFCLOC_MOLDAVIAN,
    XFCLOC_MARATHI,
    XFCLOC_MALAY,
    XFCLOC_MALTESE,
    XFCLOC_BURMESE,

    XFCLOC_NAURU,
    XFCLOC_NEPALI,
    XFCLOC_DUTCH,
    XFCLOC_NORWEGIAN,

    XFCLOC_OCCITAN,
    XFCLOC_OROMO,
    XFCLOC_ORIYA,

    XFCLOC_PUNJABI,
    XFCLOC_POLISH,
    XFCLOC_PASHTO,
    XFCLOC_PORTUGUESE,

    XFCLOC_QUECHUA,

    XFCLOC_RHAETO,
    XFCLOC_KIRUNDI,
    XFCLOC_ROMANIAN,
    XFCLOC_RUSSIAN,
    XFCLOC_KINYARWANDA,

    XFCLOC_SANSKRIT,
    XFCLOC_SINDHI,
    XFCLOC_SANGHO,
    XFCLOC_SINHALESE,
    XFCLOC_SLOVAK,
    XFCLOC_SLOVENIAN,
    XFCLOC_SAMOAN,
    XFCLOC_SHONA,
    XFCLOC_SOMALI,
    XFCLOC_ALBANIAN,
    XFCLOC_SERBIAN,
    XFCLOC_SISWATI,
    XFCLOC_SESOTHO,
    XFCLOC_SUNDANESE,
    XFCLOC_SWEDISH,
    XFCLOC_SWAHILI,

    XFCLOC_TAMIL,
    XFCLOC_TELUGU,
    XFCLOC_TAJIK,
    XFCLOC_THAI,
    XFCLOC_TIGRINYA,
    XFCLOC_TURKMEN,
    XFCLOC_TAGALOG,
    XFCLOC_SETSWANA,
    XFCLOC_TONGA,
    XFCLOC_TURKISH,
    XFCLOC_TSONGA,
    XFCLOC_TATAR,
    XFCLOC_TWI,

    XFCLOC_UIGHUR,
    XFCLOC_UKRAINIAN,
    XFCLOC_URDU,
    XFCLOC_UZBEK,

    XFCLOC_VIETNAMESE,
    XFCLOC_VOLAPUK,

    XFCLOC_WOLOF,

    XFCLOC_XHOSA,

    XFCLOC_YIDDISH,
    XFCLOC_YORUBA,

    XFCLOC_ZHUANG,
    XFCLOC_CHINESE,
    XFCLOC_ZULU

};

#endif // XFC_CORE_COREENUMS_H_INCLUDED

