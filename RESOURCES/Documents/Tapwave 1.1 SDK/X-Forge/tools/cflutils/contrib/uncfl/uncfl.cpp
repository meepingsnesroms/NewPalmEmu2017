/*
 * uncfl - utility to unpack CFL files
 * Copyright 2001 Jetro Lauha <jetro@iki.fi>
 *
 * License
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 * 
 * $Id: uncfl.cpp,v 1.4 2001/11/20 12:29:48 jetro Exp $
 * $Revision: 1.4 $
 */

#include <stdlib.h>
#include <stdio.h>
#include "CFL.h"
#include "CFLEnumerator.h"
#include "CFLResourceFilter.h"
#include "CFLDirectoryEntry.h"


const char versionStr[] = "uncfl 1.0.0";


class CFLFilterPrinter : public CFLEnumerator
{
public:
    virtual void infoCallback(unsigned int tag,
                              const char *infostring,
                              const char *shortname);
};


class CFLUnpacker : public CFL
{
private:
    void saveFile(const char *name);
public:
    void unpack();
};


void CFLFilterPrinter::infoCallback(unsigned int tag,
                               const char *infostring,
                               const char *shortname)
{
    printf(" %s", shortname);
}


void CFLUnpacker::saveFile(const char *name)
{
    int size, written;
    char *data = getFile(name, size);

    FILE *fp = fopen(name, "wb");
    
    if (fp == NULL)
    {
        fprintf(stderr, "WARNING: Unable to save %d bytes as %s\n",
                size, name);
        return;
    }

    written = fwrite(data, 1, size, fp);
    
    if (written != size)
    {
        fprintf(stderr, "WARNING: Only %d/%d bytes saved as %s\n",
                written, size, name);
    } else {
        printf("Saved %d bytes as %s\n", size, name);
    }
    
    fclose(fp);
}


void CFLUnpacker::unpack()
{
    CFLDirectoryEntry *de = mRootDir;

    while (de != NULL)
    {
        saveFile(de->mName);
        de = de->mNext;
    }
}


static void banner()
{
    CFLFilterPrinter hp;
    
    printf("%s\n", versionStr);
    printf("(Builtin Filters:");
    CFLResourceFilter::enumerateHandlers(&hp);
    printf(")\n\n");
}


static void usage(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: uncfl file.cfl\n\n");
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[])
{
    CFLUnpacker *unp = new CFLUnpacker();
    
    banner();
    usage(argc, argv);

    if (!unp->openLibrary(argv[1]))
    {
        printf("Unable to open input file.\n");
        return EXIT_FAILURE;
    }

    unp->unpack();
    
    delete(unp);
    
    return EXIT_SUCCESS;
}
