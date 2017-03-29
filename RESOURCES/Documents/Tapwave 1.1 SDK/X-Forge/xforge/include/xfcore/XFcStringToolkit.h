/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief Static string functions (this is not a string class).
 *
 * \todo add more string to value conversions (toUINT32, toREAL, toFLOAT, ...)
 * 
 * $Id: XFcStringToolkit.h,v 1.22.4.1 2003/12/01 12:00:36 jetro Exp $
 * $Date: 2003/12/01 12:00:36 $
 * $Revision: 1.22.4.1 $
 */

#ifndef XFC_CORE_XFCSTR_H_INCLUDED
#define XFC_CORE_XFCSTR_H_INCLUDED


//! String toolkit. Contains static functions used to manipulate zero-terminated character strings.
class XFCDLLEXPORT XFcStringToolkit 
{
public:

    //! Formats string using standard printf-like format string.
    /*!
     * \par Supported commands:
     * \li % : output '%' char
     * \li n : store out CHAR count to a pointer to INT
     * \li s : string
     * \li c : CHAR
     * \li d : signed decimal integer
     * \li i : signed decimal integer
     * \li u : unsigned decimal integer
     * \li x : hexadecimal lowercase unsigned integer
     * \li X : hexadecimal uppercase unsigned integer
     * \li o : octal unsigned integer
     * \li b : binary unsigned integer (xfc extension)
     * \li f : floating point (double) using nnn.nnnn notation
     * \li e : floating point (double) using n.nnnne+nnn notation
     * \li E : floating point (double) using n.nnnnE+nnn notation
     * \li g : floating point (double) chooses between f and e modes
     * \li G : floating point (double) chooses between f and E modes
     * 
     * \par Supported formatting flags:
     * \li + : prefix sign even if positive
     * \li - : left align (as opposed to right align)
     * \li 0 : pad with zeros
     * \li * : read width and/or precision from parameter
     * \li nnn.nnn : width and/or precision
     * \li # : read but ignored
     *
     * \par Supported prefixes:
     * \li l : read but ignored
     * \li L : read but ignored
     * \li h : read but ignored
     *
     * \return number of characters outputted
     *
     * \note Floating point output is not accurate, but should be able to
     *       output values of sane ranges (16.16 digits).
     * \sa Standard C library printf documentation.
     */
    XFCIMPORT static INT32 format(CHAR *aTarget, const CHAR *aFormat, ...);

    //! va_list version of format()
    /*! \sa Standard C library vsprintf documentation
     *  \sa format()
     */
    XFCIMPORT static INT32 formatVarArgs(CHAR *aTarget, const CHAR *aFormat, va_list aVaList);

    //! Format() call that also makes sure target buffer is not overrun
    /*! \sa format()
     */
    XFCIMPORT static INT32 format(CHAR *aTarget, INT32 aBufferLength, const CHAR *aFormat, ...);

    //! Format() call that also makes sure target buffer is not overrun (va_list version).
    /*! \sa format()
     */
    XFCIMPORT static INT32 formatVarArgs(CHAR *aTarget, INT32 aBufferLength, const CHAR *aFormat, va_list aVaList);

    //! Format() call that also allocates the target buffer.
    /*! \note Application must delete[] the buffer after use.
     *  \sa format()
     */
    XFCIMPORT static CHAR * allocatedFormat(const CHAR *aFormat, ...);

    //! Format() call that also allocates the target buffer (va_list version).
    /*! \note Application must delete[] the buffer after use.
     *  \sa format()
     */
    XFCIMPORT static CHAR * allocatedFormatVarArgs(const CHAR *aFormat, va_list aVaList);

    //! Calculates the amount of non-overlapping matches of a string in another string.
    /*! \param aMask mask string to look for in another string.
     *  \param aData string to be searched.
     * \sa matchIgnoreCase
     * \return number of non-overlapping matches of the aMask in aData.
     */ 
    XFCIMPORT static UINT32 match(const CHAR *aMask, const CHAR *aData);

    //! Calculates the amount of non-overlapping matches of a string in another string ignoring case.
    /*! \sa match
     */
    XFCIMPORT static UINT32 matchIgnoreCase(const CHAR *aMask, const CHAR *aData);

    //! Matches wildcards (? and * supported).
    /*! Checks whether the given string matches a wildcard mask. 
     *  ? (question mark) is a single-character wildcard while * (asterisk) matches
     *  zero or more characters. "foo?ar" matches "foobar" but not "foobaar"; "f*r" matches
     *  all strings that start with f and end with r, including "fr" and "foobar".
     * \sa matchWildcardIgnoreCase
     */ 
    XFCIMPORT static INT matchWildcard(const CHAR *aMask, const CHAR *aData);

    //! Matches wildcards (? and * supported), ignore case -version.
    /*! \sa matchWildcard
     */
    XFCIMPORT static INT matchWildcardIgnoreCase(const CHAR *aMask, const CHAR *aData);

    //! Duplicates string from 8-bit characters to internal format.
    /*! \note The newly allocated buffer must be cleaned up by the application by using the delete[] operator. */
    XFCIMPORT static CHAR * copy(const CHAR8 *aString);

    //! Duplicates string from 16-bit characters to internal format.
    /*! \note The newly allocated buffer must be cleaned up by the application by using the delete[] operator. */
    XFCIMPORT static CHAR * copy(const CHAR16 *aString);

    //! Duplicates string from internal format to 8-bit format.
    /*! \note The newly allocated buffer must be cleaned up by the application by using the delete[] operator. */
    XFCIMPORT static CHAR8 * copyToCHAR8(const CHAR *aString);

    //! Duplicates string from internal format to 16-bit format.
    /*! \note The newly allocated buffer must be cleaned up by the application by using the delete[] operator. */
    XFCIMPORT static CHAR16 * copyToCHAR16(const CHAR *aString);

    //! Compares two strings (0 = equal).
    /*! This method can also be used to sort strings, as the result can be negative or positive depending on
     *  the characters compared.
     *  \sa compareIgnoreCase
     */
    XFCIMPORT static INT compare(const CHAR *aString1, const CHAR *aString2);

    //! Compares two strings in a case-insensitive way (0 = equal).
    /*! \sa compare
     */
    XFCIMPORT static INT compareIgnoreCase(const CHAR *aString1, const CHAR *aString2);

    //! Finds string in string, returns NULL if not found.
    /*! Returned pointer points at the beginning of the found string, not a newly-allocated one. 
     */
    XFCIMPORT static const CHAR * find(const CHAR *aStringSrc, const CHAR *aStringToFind);

    //! Returns length of string, in characters.
    /*! String must be zero-terminated.
     * \sa getLengthInBytes
     */
    XFCIMPORT static INT32 getLength(const CHAR *aString);

    //! Returns length of string, in bytes.
    /*! Returns the byte size of the character string regardless of the internal character format.
     * \sa getLength
     */ 
    XFCIMPORT static INT32 getLengthInBytes(const CHAR *aString);

    //! Returns a pointer to the last occurrence of a character, or NULL if not found.
    XFCIMPORT static CHAR * findLast(const CHAR *aString, const CHAR aChar);

    //! Joins two strings, allocating new buffer.
    /*! \note The newly allocated buffer must be cleaned by the application by using the delete[] operator.
     */
    XFCIMPORT static CHAR * concat(const CHAR *aString1, const CHAR *aString2, CHAR aDelimiter = 0);

    //! Converts string to an integer.
    /*! String to be converted must contain a string representation of numerical
     *  value in range of INT32. 
     *  String format may be in decimal, octal, binary or hexadecimal. There may
     *  be an optional '-' or '+' sign prefix. Values that have prefix 0o are considered octal,
     *  and values prefixed by 0x or # are considered hexadecimal, and values prefixed
     *  by 0b are considered binary.
     * \note Result is zero if the argument string is not valid. Also aSuccess is zero.
     * \param aString string to return as a number
     * \param aSuccess a pointer to an INT that indicates if the parsing was successfull.
     * \return 0 if aString is NULL.
     * \return numerical value the aString represents.
     */
    XFCIMPORT static INT32 toINT32(const CHAR *aString, INT *aSuccess = NULL);

    //! Converts string to a float.
    /*! String to be converted must contain a string representation of numerical
     *  value in range of FLOAT32. The string can contain only characters '0' to '9'
     *  with optionally '-' or '+' sign on the front, '.' as decimal separator and the exponent
     *  symbol 'e' or 'E' possibly suffixed with the '+' or '-' sign.
     * \note Result is zero if the argument string is not valid. Also aSuccess is zero.
     * \param aString string to return as a number
     * \param aSuccess a pointer to an INT that indicates if the parsing was successfull.
     * \return 0 if aString is NULL.
     * \return numerical value the aString represents.
     */
    XFCIMPORT static FLOAT32 toFLOAT32(const CHAR *aString, INT *aSuccess = NULL);

    //! Converts a string to lower case.
    /*! Character conversion supports only characters from A to Z. All other characters
     * are to be considered as non-convertable.
     * \param aString string to be converted.
     */
    XFCIMPORT static void toLowerCase(CHAR *aString);

    //! Converts a string to upper case.
    /*! Character conversion supports only characters from A to Z. All other characters
     *  are to be considered as non-convertable.
     * \param aString string to be converted.
     */
    XFCIMPORT static void toUpperCase(CHAR *aString);    

    //! Converts escaped character string to literal one.
    /*! If the input string contains escaped characters such as \n, 
     *  this function can be used to create literal version of
     *  the same string (ie. one 'newline' character instead of
     *  'backslash' and 'n' characters).
     *  Currently supports the following escaped sequence:
     *  \n (newline)
     *  Any other character following a backslash is returned
     *  as is (the backslash is removed).
     */
    /*! \note The newly allocated buffer must be cleaned up by the application by using the delete[] operator. */
    XFCIMPORT static CHAR * unescape(const CHAR *aStr);
};


#endif // !XFC_CORE_XFCSTR_H_INCLUDED

