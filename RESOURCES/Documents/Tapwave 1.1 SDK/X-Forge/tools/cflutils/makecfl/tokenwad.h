///////////////////////////////////////////////
// Copyright
///////////////////////////////////////////////
//
// Compressed File Library 3 makecfl util
// Copyright (c) 2001-2002 Jari Komppa and Fathammer Ltd
//
//
///////////////////////////////////////////////
// License
///////////////////////////////////////////////
// 
//     This software is provided 'as-is', without any express or implied
//     warranty.    In no event will the authors be held liable for any damages
//     arising from the use of this software.
// 
//     Permission is granted to anyone to use this software for any purpose,
//     including commercial applications, and to alter it and redistribute it
//     freely, subject to the following restrictions:
// 
//     1. The origin of this software must not be misrepresented; you must not
//        claim that you wrote the original software. If you use this software
//        in a product, an acknowledgment in the product documentation would be
//        appreciated but is not required.
//     2. Altered source versions must be plainly marked as such, and must not be
//        misrepresented as being the original software.
//     3. This notice may not be removed or altered from any source distribution.
// 
// (eg. same as ZLIB license)
// 
//
///////////////////////////////////////////////
//
// This class splits input string into handy tokens. 
// Used only by makecfl.

class tokenwad 
{
public:
    tokenwad();
    ~tokenwad();
    void tokenize(const char *aBuf, const char *aSeparators = "=,");
    int tokens();
    const char * token(int aIdx);
    char * tokendup(int aIdx);
    int tokenEquals(int aIdx, const char *aString);
    int tokenEqualsNocase(int aIdx, const char *aString);

private:
    char **mData;  
    int mCount;
};
