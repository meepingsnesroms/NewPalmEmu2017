/*! \file
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief Logger class.
 *
 * $Id: XFcLogger.h,v 1.15 2003/08/12 13:33:48 lars Exp $
 * $Date: 2003/08/12 13:33:48 $
 * $Revision: 1.15 $
 */
#ifndef XFCLOGGER_H_INCLUDED
#define XFCLOGGER_H_INCLUDED


#ifdef XFC_WRITE_LOG

//! Used to log program flow information.
#define XFCLOGFUNC(aFuncName, aLevel) XFcLogFlow xfcLogFlow(aFuncName, aLevel)
//! Used to log text information, aFlag specifies the type of information.
#define XFCLOG(aFlag, aTxt) XFcLogger::log(aTxt, aFlag)
//! Formatted log with 1 argument, aFlag specifies the type of information.
#define XFCLOG1(aFlag, aTxt, aArg1) do { CHAR t[256]; XFcStringToolkit::format(t, aTxt, aArg1); XFcLogger::log(t, aFlag); } while (0)
//! Formatted log with 2 arguments, aFlag specifies the type of information.
#define XFCLOG2(aFlag, aTxt, aArg1, aArg2) do { CHAR t[256]; XFcStringToolkit::format(t, aTxt, aArg1, aArg2); XFcLogger::log(t, aFlag); } while (0)
//! Formatted log with 3 arguments, aFlag specifies the type of information.
#define XFCLOG3(aFlag, aTxt, aArg1, aArg2, aArg3) do { CHAR t[256]; XFcStringToolkit::format(t, aTxt, aArg1, aArg2, aArg3); XFcLogger::log(t, aFlag); } while (0)
//! Formatted log with 4 arguments, aFlag specifies the type of information.
#define XFCLOG4(aFlag, aTxt, aArg1, aArg2, aArg3, aArg4) do { CHAR t[256]; XFcStringToolkit::format(t, aTxt, aArg1, aArg2, aArg3, aArg4); XFcLogger::log(t, aFlag); } while (0)
//! Formatted log with 5 arguments, aFlag specifies the type of information.
#define XFCLOG5(aFlag, aTxt, aArg1, aArg2, aArg3, aArg4, aArg5) do { CHAR t[256]; XFcStringToolkit::format(t, aTxt, aArg1, aArg2, aArg3, aArg4, aArg5); XFcLogger::log(t, aFlag); } while (0)

#define XFCLOGDATA(aFlag, aTxt, aLength) do { XFcLogger::log(aTxt, aLength, aFlag); } while (0)

#else // or !XFC_WRITE_LOG

#define XFCLOGFUNC(aFuncName, aLevel)
#define XFCLOG(aFlag, aTxt)
#define XFCLOG1(aFlag, aTxt, aArg1)
#define XFCLOG2(aFlag, aTxt, aArg1, aArg2)
#define XFCLOG3(aFlag, aTxt, aArg1, aArg2, aArg3)
#define XFCLOG4(aFlag, aTxt, aArg1, aArg2, aArg3, aArg4)
#define XFCLOG5(aFlag, aTxt, aArg1, aArg2, aArg3, aArg4, aArg5)
#define XFCLOGDATA(aFlag, aTxt, aLength);

#endif // !XFC_WRITE_LOG


/* Specify an identity character for each log type,
 * each log entry will start with this character.
 */
const CHAR XFC_LOG_CHAR_INFO = 'I';     //!< General information log entry char.
const CHAR XFC_LOG_CHAR_DATA = 'D';     //!< General data log entry char.
const CHAR XFC_LOG_CHAR_FLOW = 'F';     //!< Program flow information log entry char.
const CHAR XFC_LOG_CHAR_ERR = 'E';      //!< Error log entry char.
const CHAR XFC_LOG_CHAR_WARN = 'W';     //!< Warning log entry char.
const CHAR XFC_LOG_CHAR_CRIT = '!';     //!< Critical error log entry char.


//! Logger constants.
enum XFCLOGGER_ENUMS
{
    LOG_INDENT_SIZE     = 2,    //!< Log indent size.
    MAX_NUM_LOGTHREADS  = 10    //!< Maximum number of logging threads.
};


//! Data logger class.
/*! \todo Support for multiple threads.
 */
class XFCDLLEXPORT XFcLogger
{

public:

    //! XFCLOGFLAGS can be used to mask out specific types of logging.
    enum XFCLOGFLAGS
    {
        XFCLOG_INFO     = 1,            //!< Log general information.
        XFCLOG_DATA     = 2,            //!< Log general data.
        XFCLOG_FLOW     = 4,            //!< Log program flow information.
        XFCLOG_ERR      = 8,            //!< Log an error.
        XFCLOG_WARN     = 16,           //!< Log a warning.
        XFCLOG_CRIT     = 32,           //!< Log a critical error.
        XFCLOG_INDENT   = 64,           //!< Log indents.
        XFCLOG_UNDENT   = 128,          //!< Log undents.
        XFCLOG_ALL      = 0xffffffff    //!< Log everything.
    };

    //! Destructor.
    XFCIMPORT ~XFcLogger();
    //! Static constructor.
    XFCIMPORT static XFcLogger * create();

    //! Logs a string, with a specific log entry type.
    /*!
     * \param aTxt string to log.
     * \param aFlag type of log entry.
     */
    XFCIMPORT static void log(const CHAR *aTxt, XFCLOGFLAGS aFlag);

    //! Logs a data buffer as hex string values, with a specific log entry type.
    /*!
     * \param aTxt data buffer to log.
     * \param aLength length of the data buffer.
     * \param aFlag type of log entry.
     */
    XFCIMPORT static void log(const CHAR8 *aTxt, INT32 aLength, XFCLOGFLAGS aFlag);

    //! Sets logging mask.
    /*!
     * \param aMask disabled logging types, see XFCLOGFLAGS.
     * \sa XFCLOGFLAGS
     */
    XFCIMPORT static void setMask(UINT32 aMask);

    //! Returns current logging mask.
    XFCIMPORT static UINT32 getMask();

    //! Sets the maximum size of the log file.
    /*!
     * \param aSizeLimit new maximum size for the log, in bytes.
     */
    XFCIMPORT static void setFileSizeLimit(UINT32 aSizeLimit);

    //! Returns the maximum size of the log file, in bytes.
    XFCIMPORT static UINT32 getFileSizeLimit();

    //! Indents log entries.
    XFCIMPORT static void indent();

    //! Undents log entries.
    XFCIMPORT static void undent();

    //! Sets current log level for program flow.
    XFCIMPORT static void setLogLevel(INT aLevel);

    //! Returns current log level for program flow.
    XFCIMPORT static INT getLogLevel();

protected:

    //! Finds the number of the current thread.
    UINT32 findThreadNum();

    //! Creates and returns a filename for a specific thread.
    /*!
     * \param aThreadId thread id to create the filename for.
     */
    CHAR * createFileName(UINT32 aThreadId);

    //! Writes the type header with the given flag.
    /*!
     * \param aFlag log entry type.
     * \param aFile file to write in.
     */
    void writeTypeInfo(XFCLOGFLAGS aFlag, XFcFile *aFile);

    //! Does the real logging.
    /*! \internal */
    void doLog(const CHAR *aTxt, XFCLOGFLAGS aFlag);

    //! Does the real logging.
    /*! \internal */
    void doLog(const CHAR8 *aTxt, INT32 aLength, XFCLOGFLAGS aFlag);

    //! Does the real set mask.
    /*! \internal */
    void doSetMask(UINT32 aMask);
    //! Does the real get mask.
    /*! \internal */
    UINT32 doGetMask();
    //! Does the real setFileSizeLimit.
    /*! \internal */
    void doSetFileSizeLimit(UINT32 aSizeLimit);
    //! Does the real getFileSizeLimit.
    /*! \internal */
    UINT32 doGetFileSizeLimit();
    //! Does the real indent.
    /*! \internal */
    void doIndent();
    //! Does the real undent.
    /*! \internal */
    void doUndent();
    //! Does the real setLogLevel.
    /*! \internal */
    void doSetLogLevel(INT aLevel);
    //! Does the real getLogLevel.
    /*! \internal */
    INT doGetLogLevel();

    //! Number of threads.
    INT mNumThreads;
    //! Thread ids.
    UINT32 mThreadIds[MAX_NUM_LOGTHREADS];

    //! The current indentation level.
    INT mCurrentIndent[MAX_NUM_LOGTHREADS];
    //! The current file size limit, default is -1 which means no limit.
    INT32 mFileSizeLimit[MAX_NUM_LOGTHREADS];
    //! The current log flags (mask).
    UINT32 mLogFlags[MAX_NUM_LOGTHREADS];
    //! Is logging started.
    INT mLoggingStarted[MAX_NUM_LOGTHREADS];
    //! Is file size exceeded.
    INT mFileSizeLimitExceeded[MAX_NUM_LOGTHREADS];
    //! The current logging level for program flow.
    INT mLogLevel[MAX_NUM_LOGTHREADS];
};


//! A helper class to log program flow information.
class XFcLogFlow
{
public:

    //! Constructor.
    /*!
     * \param aFuncName function/method name for the entry.
     * \param aLevel logging level.
     */
    XFcLogFlow(const CHAR *aFuncName, INT aLevel);

    //! Destructor.
    ~XFcLogFlow();

protected:

    CHAR *mFuncName;    //!< Function/method name.
    INT mLogLevel;      //!< Logging level.
};


#endif // !XFCLOGGER_H_INCLUDED

