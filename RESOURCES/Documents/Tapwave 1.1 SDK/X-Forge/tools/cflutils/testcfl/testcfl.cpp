///////////////////////////////////////////////
// Copyright
///////////////////////////////////////////////
//
// Compressed File Library 3 test tool
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
// (ie. same as ZLIB license)
// 
//
///////////////////////////////////////////////
//
// This is a tool application for debugging CFL and resource handler plugins.
//
///////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "CFL.h"
#include "CFLMaker.h"
#include "CFLEnumerator.h"
#include "CFLResourceFilter.h"

static const int TESTDATA_BYTES = 1024 * 1024 + 1;

CFLMaker *gMaker;
CFL *gCfl;
char *gTestData;

class handler_enum : public CFLEnumerator
{
public:
    int mStage;
    virtual void infoCallback(unsigned int aTag, const char *aInfoString, const char *aShortName);
};

void test_data(const char *aFilename)
{
    printf("\n- Testing '%s'.. ", aFilename);
    if (!gCfl->fileExists(aFilename))
    {
        printf("error: file not found");
        return;
    }
    printf("file ok");
    int size;
    char *d;
    d = gCfl->getFile(aFilename, size);
    if (size != TESTDATA_BYTES)
    {
        printf(", size mismatch (reported %d)", size);
        return;
    }
    printf(", size ok");
    for (int i = 0; i < TESTDATA_BYTES; i++)
    {
        if ((d[i] & 0xff) != (gTestData[i] & 0xff))
        {
            printf(", data mismatch (at position %d)", i);
            return;
        }
    }
    printf(", data ok");
    delete[] d;
}

void handler_enum::infoCallback(unsigned int aTag, const char *aInfoString, const char *aShortName)
{
    if (mStage == 0)
    {
        printf("\n- Processing with '%s'.. ", aShortName);
        int size=gMaker->store(aShortName, gTestData, TESTDATA_BYTES, aTag);
        printf("%d bytes (%3.3f%%)", size, size * 100.0f / TESTDATA_BYTES);
    } 
    else
    {
        test_data(aShortName);
    }
}

void generate_testdata()
{
    gTestData = new char[TESTDATA_BYTES];
    int a, b, c;
    a = 10;
    b = 20;
    c = 30;
    for (int i = 0; i < TESTDATA_BYTES; i++)
    {
        c += b >> 12;
        b += a >> 12;
        a += 1;
        gTestData[i] = c >> 12;
    }
}

int main(int parc, char **pars)
{
    setbuf(stdout, NULL);
    printf("TestCFL\n"
           "CFL testing tool\n\n");
    
    printf("\n- Generating test data.. ");
    generate_testdata();
    printf("%d bytes",TESTDATA_BYTES);

    printf("\n- Creating CFL..");
    gMaker=CFLMaker::create("testcfl.cfl");
    handler_enum e;
    e.mStage=0;
    CFLResourceFilter::enumerateHandlers(&e);
    
    printf("\n- Processing with 'find best'.. ");
    int size = gMaker->store("find best", gTestData, TESTDATA_BYTES, CFLCOMPRESS_BEST);
    printf("%d bytes (%3.3f%%)", size, size * 100.0f / TESTDATA_BYTES);
    
    printf("\n- Closing CFL");
    gMaker->finish(CFLCOMPRESS_BEST);
    
    printf("\n- Mounting CFL.. ");    
    gCfl = CFL::create("testcfl.cfl");
    if (gCfl == NULL)
    {
        printf("Failed!");
        delete[] gTestData;
        return 1;
    }
    printf("OK");

    e.mStage = 1;
    CFLResourceFilter::enumerateHandlers(&e);
    test_data("find best");

    printf("\n- Closing CFL");
    delete gCfl;    

    printf("\n(you may delete testcfl.cfl)");
    printf("\n");
    delete[] gTestData;
    return 0;
}