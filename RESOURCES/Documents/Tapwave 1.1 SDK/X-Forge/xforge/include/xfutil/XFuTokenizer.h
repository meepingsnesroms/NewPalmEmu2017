/*! \file 
 * X-Forge Util <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief String tokenizer utility
 * 
 * $Id: XFuTokenizer.h,v 1.9 2003/08/12 13:33:52 lars Exp $
 * $Date: 2003/08/12 13:33:52 $
 * $Revision: 1.9 $
 */

#ifndef XFUTOKENIZER_H_INCLUDED
#define XFUTOKENIZER_H_INCLUDED




//! String tokenizer utility class.
/*! Tokenizes strings by delimiters.
 *  \par Example of use:
 *  \code
 *  const CHAR blah[] = "some; string with ; different tokens";
 *  XFuTokenizer myTokens;
 *  myTokens.tokenize(blah, XFCSTR(";"));
 *  INT i;
 *  for (i = 0; i < myTokens.getTokenCount(); ++i)
 *      if (myTokens.tokenEqualsNocase(i, XFCSTR("String wIth")))
 *          printf("token number %d is our token", i);
 *  \endcode
 */
class XFuTokenizer 
{
public:
    //! Constructor.
    XFuTokenizer();
    
    //! Destructor.
    ~XFuTokenizer();
    
    //! Tokenizes the input string.
    /*! Uses the characters in aSeparators as delimiters for tokens.
     */
    void tokenize(const CHAR *aBuffer, const CHAR *aSeparators);
    
    //! Tokenizes the input string.
    /*! Uses the ',' and '=' characters as delimiters for tokens.
     */
    void tokenize(const CHAR *aBuffer);
    
    //! Case sensitive matching of a token and given string.
    INT tokenEquals(INT32 aIdx, const CHAR *aCompareString);
    
    //! Case insensitive matching of a token and given string.
    INT tokenEqualsNocase(INT32 aIdx, const CHAR *aCompareString);
    
    //! Get the token count.
    INT32 getTokenCount();
    
    //! Get a pointer to a token (as zero-terminated string).
    const CHAR * getToken(INT32 aIdx);
    
    //! Get a duplicate of a token (as zero-terminated string).
    CHAR * duplicateToken(INT32 aIdx);
    
private:
    //! Token strings.
    CHAR **mData;
    //! Number of token strings.
    INT32 mCount;
    //! Upcase function.
    CHAR upcase(CHAR i);
};


#endif // !XFUTOKENIZER_H_INCLUDED

