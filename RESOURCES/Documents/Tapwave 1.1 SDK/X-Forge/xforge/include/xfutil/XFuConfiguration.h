/*! \file
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 *
 * \brief XFuConfiguration.h is the header file for the XFuConfiguration class.
 *
 * $Id: XFuConfiguration.h,v 1.15 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.15 $
 */

#ifndef XFUCONFIGURATION_H_INCLUDED
#define XFUCONFIGURATION_H_INCLUDED



#include <xfutil/XFuStringKey.h>
#include <xfcore/XFcHashtable.h>


//! Configuration container.
/*!
 * Reads and parses a set of configuration keys from a file.
 * The format of the configuration file is such that there is one property
 * on each row in a text file. Each property is a pair of a key and a value,
 * delimited by a '=' char, for example: fileName=HelloWorld.xff. Leading and
 * trailing spaces are trimmed. Lines starting with character '#' are treated
 * as comment lines and are ignored.
 */
class XFuConfiguration
{

public:

    //! Constructor.
    XFuConfiguration();

    //! Static constructor.
    /*! \return new configuration data object if successful, or NULL if unsuccessful.
     */
    static XFuConfiguration * create();

    //! Static constructor.
    /*! \param aFilename filename of configuration data to load.
     * \return new configuration data object if successful, or NULL if unsuccessful.
     */
    static XFuConfiguration * create(const CHAR *aFilename);

    //! Static constructor.
    /*! \param aFile open file pointing to configuration data to load.
     * \return new configuration data object if successful, or NULL if unsuccessful.
     * \note Configuration data is assumed to continue to end of the file.
     */
    static XFuConfiguration * create(XFcFile *aFile);

    //! Destructor.
    virtual ~XFuConfiguration();

    //! Returns the value of the property (NULL if none).
    virtual CHAR * get(const CHAR *aKey);

    //! Returns the value of a property as an INT32, or 0 if not found.
    virtual INT32 getINT32(const CHAR *aKey);

    //! Returns the value of a property as a FLOAT32, or 0 if not found.
    virtual FLOAT32 getFLOAT32(const CHAR *aKey);

    //! Sets the value of a property.
    virtual void put(const CHAR *aKey, const CHAR *aValue);

    //! Clears the current properties.
    virtual void clear();

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

protected:

    //! Parses a line of the config file.
    /*! Extracts the property key and value from it and adds these to the property hashtable.
     */
    virtual void processLine(const CHAR *aStr);

    //! Reads a line from a file.
    CHAR8 * readLine(XFcFile *aFile);

    //! Returns a new string where the leading and trailing spaces are removed.
    CHAR * strDupTrim(const CHAR *aStr);

    //! Properties hashtable.
    XFcHashtable<XFuStringKey, void *> *mProperties;

};


#endif // !XFUCONFIGURATION_H_INCLUDED

