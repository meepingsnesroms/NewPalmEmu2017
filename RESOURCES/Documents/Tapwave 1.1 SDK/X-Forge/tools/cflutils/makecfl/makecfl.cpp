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
// If you make new resource handlers you will need to add them to a project
// with this source and recompile in order to be able to create cfl files
// with those handlers.
//
// NOTE:
// This source is somewhat dos/windows specific due to the findfirst/findnext
// system used. Some work is needed in order to have all features under *nix.
// If someone would like to contribute the linux conversion, I'd be grateful.
//
///////////////////////////////////////////////
//
// Changes:
// r2 - ini file is now created as "w" instead of "wb"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <io.h>
#include "CFL.h"
#include "CFLEnumerator.h"
#include "CFLResourceFilter.h"
#include "CFLMaker.h"
#include "tokenwad.h"


class handler_enum : public CFLEnumerator
{
public:
    virtual void infoCallback(unsigned int aTag, const char *aInfoString, const char *aShortName);
};

void handler_enum::infoCallback(unsigned int aTag, const char *aInfoString, const char *aShortName)
{
    printf("'%s' ",aShortName);
}

int equalsNocase(const char *aStringA, const char *aStringB)
{
    char * s1=(char*)aStringA, * s2=(char*)aStringB;
    while (*s1 && *s2 && toupper(*s1) == toupper(*s2)) 
    {
        s1++;
        s2++;
    }
    if (!*s1 && !*s2) return 1;
    return 0;
}

void printhelp()
{
    printf(
        "Usage:\n"
        "\n"
        "makecfl has three modes of operation:\n"
        " -h Printing help (this one)\n"
        "    aliases: /h -?, /?, -h, help, -help or --help\n"
        " -i Build .ini files with which you can make .cfl files\n"
        "    aliases: /i, ini, -ini, --ini, makeini, -makeini or --makeini\n"
        " -c Build .cfl files using parameters read from .ini file\n"
        "    aliases: -m, /m, make, -make, --make, -b, /b, build, -build, --build,\n"
        "             /c, cfl, -cfl, --cfl, buildcfl, -buildcfl or --buildcfl\n"
        "\n"
        "(The various parameters are there just to make it easier to\n"
        "remember how to invoke a given function)\n"
        "\n"
        "Making ini files:\n"
        "  makecfl -i inifilename\n"
        "or\n"
        "  makecfl -i inifilename filemask\n"
        "will create inifile with default options and a list of files\n"
        "found using the given filemask.\n"
        "\n"
        "Making cfl files:\n"
        "  makecfl -c inifilename\n"
        "will create .cfl file based on parameters found in the ini file.\n"
        "\n"
        "This copy of makecfl supports the following resource handlers:\n");
    handler_enum e;
    CFLResourceFilter::enumerateHandlers(&e);
    printf("\n");

}

void buildini(char * fname, char * filemask)
{
    FILE *f;
    f = fopen(fname,"w");
    if (f == NULL)
    {
        printf("Unable to open '%s' for writing.\n",fname);
        return;
    }
    char defaultcflname[512];
    int i = 0;
    while (fname[i] && fname[i] != '.')
    {
        defaultcflname[i] = fname[i];
        i++;
    }
    defaultcflname[i+0] = '.'; 
    defaultcflname[i+1] = 'c'; 
    defaultcflname[i+2] = 'f'; 
    defaultcflname[i+3] = 'l'; 
    defaultcflname[i+4] = 0;
    i+=4;

    fprintf(f,
        "; CFL3 creation ini file\n"
        "; Automatically generated using makecfl util\n"
        ";\n"
        "; Compression flags are in hex. You can combine any preprocessor,\n"
        "; encryption and compression flags (note: most of these may not be\n"
        "; supported by your copy of makecfl. See makecfl --help for a list\n"
        "; of supported flags)\n"
        ";\n"
        ";\n"
        "; Compression (byte mask ....XXXX)\n"
        "; 0x00000000 = NONE \n"
        "; 0x00000001 = ZLIB \n"
        "; 0x00000901 = ZLIB9\n"
        "; 0x00000002 = LZSS \n"
        "; 0x00000003 = BZIP2\n"
        "; 0x0000FFFF = BEST (finds the best compression ratio with brute force)\n"
        ";\n"
        "; Preprocessor (byte mask ..XX....)\n"
        "; 0x00000000 = NONE   \n"
        "; 0x00010000 = DELTA8 \n"
        "; 0x00020000 = DELTA16\n"
        "; 0x00030000 = DELTA32\n"
        "; 0x00040000 = BWT    \n"
        ";\n"
        "; Encryption (byte mask XX......)\n"
        "; 0x00000000 = NONE     \n"
        "; 0x01000000 = XOR      \n"
        "; 0x02000000 = PRANDXOR \n"
        "; 0x03000000 = STRINGXOR\n"
        "; 0x10000000 = PGP      \n"
        "; 0x20000000 = GPG      \n"
        "; 0x30000000 = DES      \n"
        "; 0x40000000 = 3DES     \n"
        "; 0x50000000 = BLOWFISH \n"
        "; 0x60000000 = IDEA     \n"
        "; 0x70000000 = RC4      \n"
        ";\n"
        ";\n"
        "; So for example if you want to preprocess with DELTA32, compress with BZIP2,\n"
        "; and encrypt with 3DES, you'd use 0x40030003.\n"
        "; By default makecfl sets all to 0x0000FFFF, eg. don't preprocess or encrypt,\n"
        "; and try out all supported compressors, choosing the best compression ratio.\n"
        ";\n"
        "; Please note that using the 'BEST' mode eats up a lot of RAM and depending on\n"
        "; how many compressors you have in your copy of makecfl may be extremely slow.\n"
        ";\n"
        ";\n"
        "; In order to disable some compressors, uncomment the following line and \n"
        "; add handler flags after it, delimited by commas.\n"
        ";DISABLE=0x00000002,0x00000901\n"
        ";\n"
        ";\n"
        "; The following line sets the method of compression for the library directory\n"
        "LIBRARY_COMPRESS=0x0000FFFF\n"
        ";\n"
        ";\n"
        "; The following line sets the target CFL filename (required)\n"
        "CFLNAME=%s\n"
        ";\n"
        ";\n"
        "; The rest of the file contains only DATA lines. The format of a DATA line is\n"
        "; as follows:\n"
        "; DATA=diskfilename,cflfilename,compressionflags,cipherkeyfilename\n"
        "; diskfilename is the filename of the file as it appears on disk. (required)\n"
        "; cflfilename is the filename of the file as it appears inside the cfl.\n"
        "; compressionflags are the ones explained above.\n"
        "; cipherkeyfilename is a file that contains the cipher key for this file.\n"
        "; Please note that only diskfilename is required.\n"
        ";\n"
        "; Examples:\n"
        ";    DATA=defaultstoredfile.txt\n"
        ";    DATA=uncompressedfile.dat,,0x00000000\n"
        ";    DATA=data\\with\\simpler\\name\\inside\\cfl.dat,data.dat\n"
        ";    DATA=secret.data,,0x4000FFFF,deskey.dat\n"
        ";\n"
        ";\n"
        ";\n",defaultcflname);
   
#ifdef _WIN32
    long hFile;
    struct _finddata_t fileinfo;
    if ((hFile = _findfirst( filemask, &fileinfo )) == -1L)
    {
        printf("Could not find any files with the mask '%s'\n",filemask);
    }
    else
    {
        do 
        {
            if ((fileinfo.attrib&(_A_SUBDIR|_A_SYSTEM|_A_HIDDEN))==0)
            {
                // don't store the ini file itself inside the ini file:
                if (equalsNocase(fname, fileinfo.name) == 0)
                {
                    fprintf(f,"DATA=%s,,0x0000FFFF\n",fileinfo.name);
                }
            }
        } 
        while (_findnext( hFile, &fileinfo ) == 0);
    }   
#else

    printf("NOTE: non-windows file searching code has not been implemented.\n");
    fprintf(f,"DATA=ExampleFilename.dat,,0x0000FFFF\n");

#endif

    fclose(f);
    printf("Ini file '%s' created.\n",fname);
}

void buildcfl(char * inifile)
{
    CFLMaker *m = NULL;
    FILE *f;
    char *rawdata;
    int warnings = 0;
    int filesize;
    f = fopen(inifile, "rb");
    if (f == NULL)
    {
        printf("Unable to open '%s' for reading.\n", inifile);
        return;
    }
    fseek(f, 0, SEEK_END);
    filesize = ftell(f);
    rawdata = new char[filesize];
    if (rawdata == NULL)
    {
        fclose(f);
        printf("Out of memory.\n");
        return;
    }
    fseek(f, 0, SEEK_SET);
    fread(rawdata, 1, filesize, f);
    fclose(f);
    tokenwad lines;
    lines.tokenize(rawdata, "\r\n");
    delete[] rawdata;
    unsigned int library_pack = 0x0000ffff;
    for (int i = 0; i < lines.tokens(); i++) 
    {
        tokenwad token;
        token.tokenize(lines.token(i));
        if (token.tokens() > 1 && token.token(0)[0] != ';')
        {
            if (token.tokenEqualsNocase(0, "DISABLE"))
            {
                for (int j = 1; j < token.tokens(); j++)
                {
                    unsigned int d = strtoul(token.token(j), NULL, 16);
                    CFLResourceFilter::enableHandler(d, 0);
                }
            }
            else
            if (token.tokenEqualsNocase(0, "LIBRARY_COMPRESS"))
            {
                library_pack=strtoul(token.token(1), NULL, 16);
            }
            else
            if (token.tokenEqualsNocase(0, "CFLNAME"))
            {
                if (m != NULL)
                {
                    printf("Warning: CFLNAME appears more than once in the ini file.\n");
                    warnings++;
                }
                else
                {
                    printf("Opening '%s' for writing..", token.token(1));
                    m = CFLMaker::create(token.token(1));
                    if (m == NULL)
                    {
                        printf("Failed.\n");
                        return;
                    }
                    printf("ok\n");
                }
            }
            else
            if (token.tokenEqualsNocase(0, "DATA"))
            {
                if (m == NULL)
                {
                    printf("Warning: DATA defined before CFLNAME or CFLNAME\n"
                           "missing completely in the ini file. DATA is being ignored.\n");
                    warnings++;
                }
                else
                {
                    char *cipher = NULL;
                    char *cflfilename;
                    unsigned int compressflags = 0x0000FFFF;
                    if (token.tokens() > 2 && !token.tokenEquals(2, ""))
                    {
                        cflfilename = (char*)token.token(2);
                    }
                    else
                    {
                        cflfilename = (char*)token.token(1);
                    }
                    if (token.tokens() > 3 && !token.tokenEquals(3, ""))
                    {
                        compressflags = strtoul(token.token(3), NULL, 16);
                    }
                    if (token.tokens() > 4 && !token.tokenEquals(4, ""))
                    {
                        FILE *cf;
                        cf = fopen(token.token(4), "rb");
                        if (cf == NULL)
                        {
                            printf("Warning: unable to open cipher key file '%s' for reading\n", token.token(4));
                            warnings++;
                        }
                        else
                        {
                            fseek(cf, 0, SEEK_END);
                            filesize = ftell(cf);
                            fseek(cf, 0, SEEK_SET);
                            cipher = new char[filesize];
                            if (cipher == NULL)
                            {
                                if (filesize == 0)
                                {
                                    printf("Warning: cipher key file '%s' is 0 bytes long\n", token.token(4));
                                    warnings++;
                                }
                                else
                                {
                                    printf("Warning: out of memory reading cipher key file '%s'\n", token.token(4));
                                    warnings++;
                                }
                                fclose(cf);
                            }
                            else
                            {
                                fread(cipher, 1, filesize, cf);
                                fclose(cf);
                                printf("Cipher key file '%s' loaded.", token.token(4));
                            }
                        }
                    }
                    CFLResourceFilter::setKey(compressflags & 0xff000000, cipher);
                    if (cipher != NULL)
                        delete[] cipher;

                    f = fopen(token.token(1), "rb");
                    if (f==NULL)
                    {
                        printf("Warning: could not open '%s' for reading. DATA is being ignored.\n", token.token(1));
                        warnings++;
                    } 
                    else
                    {
                        fseek(f, 0, SEEK_END);
                        filesize = ftell(f);
                        fseek(f, 0, SEEK_SET);
                        rawdata = new char[filesize];
                        if (rawdata == NULL)
                        {
                            printf("Warning: out of memory reading '%s'. DATA is being ignored.\n", token.token(1));
                            warnings++;
                            fclose(f);
                        }
                        else
                        {
                            fread(rawdata, 1, filesize, f);
                            fclose(f);
                            printf("\nStoring '%s' as '%s' with\n", token.token(1), cflfilename);
                            if (compressflags & 0x00ff0000)                            
                                printf("'%s' - '%s'\n", CFLResourceFilter::handlerShortName(compressflags & 0x00ff0000),
                                                        CFLResourceFilter::handlerInfoString(compressflags & 0x00ff0000));
                            printf("'%s' - '%s'\n", CFLResourceFilter::handlerShortName(compressflags & 0x0000ffff),
                                                    CFLResourceFilter::handlerInfoString(compressflags & 0x0000ffff));
                            if (compressflags & 0xff000000)
                                printf("'%s' - '%s'\n", CFLResourceFilter::handlerShortName(compressflags & 0xff000000),
                                                        CFLResourceFilter::handlerInfoString(compressflags & 0xff000000));
                            printf("%d bytes -> ", filesize);
                            int packedsize = m->store(cflfilename, rawdata, filesize, compressflags);
                            delete[] rawdata;
                            if (packedsize == 0 && filesize != 0)
                            {
                                printf("Failed.\nWarning: storing failed. DATA is being ignored.\n");                               
                                warnings++;
                            } 
                            else
                            {
                                if (filesize != 0)
                                {
                                    printf("%d bytes (%3.3f%%)\n", packedsize, packedsize * 100.0f / filesize);
                                }
                                else
                                {
                                    printf("%d bytes\n", packedsize);
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                printf("Unrecognized token found in ini file: '%s' on line:\n", token.token(0));
                printf("> %s\n", lines.token(i));
                warnings++;
            }
        }
    }
    if (m == NULL)
    {
        printf("No CFLNAME token found in the ini file, so no cfl file was created.\n");
        warnings++;
    }
    else
    {
        m->finish(library_pack);
        printf("\ncfl file created.\n");
    }
    if (warnings)
    {
        printf("\n!! WARNING: %d warnings issued while building.\n", warnings);
        exit(1);
    }
}

int main(int parc, char **pars)
{
    printf("makecfl\nCFL creation util\nCopyright (c) 2001-2002 Jari Komppa and Fathammer Ltd\n\n");

    int mode = 0;
    if (parc < 2)
    {
        mode = 1;
    } 
    else
    if (equalsNocase(pars[1], "-h") || 
        equalsNocase(pars[1], "/h") ||
        equalsNocase(pars[1], "/?") ||
        equalsNocase(pars[1], "-?") ||
        equalsNocase(pars[1], "help") ||
        equalsNocase(pars[1], "-help") ||
        equalsNocase(pars[1], "--help"))
    {
        mode = 2;
    } 
    else
    if (equalsNocase(pars[1], "make") ||
        equalsNocase(pars[1], "-make") ||
        equalsNocase(pars[1], "--make") ||
        equalsNocase(pars[1], "build") ||
        equalsNocase(pars[1], "-build") ||
        equalsNocase(pars[1], "--build") ||
        equalsNocase(pars[1], "buildcfl") ||
        equalsNocase(pars[1], "-buildcfl") ||
        equalsNocase(pars[1], "--buildcfl") ||
        equalsNocase(pars[1], "-m") ||
        equalsNocase(pars[1], "/m") ||
        equalsNocase(pars[1], "-b") ||
        equalsNocase(pars[1], "/b") ||
        equalsNocase(pars[1], "-c") ||
        equalsNocase(pars[1], "/c") ||
        equalsNocase(pars[1], "cfl") ||
        equalsNocase(pars[1], "-cfl") ||
        equalsNocase(pars[1], "--cfl"))
    {
        mode = 3;
    } 
    else
    if (equalsNocase(pars[1], "ini") ||
        equalsNocase(pars[1], "-ini") ||
        equalsNocase(pars[1], "--ini") ||
        equalsNocase(pars[1], "-i") ||
        equalsNocase(pars[1], "/i") ||
        equalsNocase(pars[1], "makeini") ||
        equalsNocase(pars[1], "-makeini") ||
        equalsNocase(pars[1], "--makeini"))
    {
        mode = 4;
    } 
    else
    {
        mode = 1;
    }
    
    switch (mode)
    {
    case 1: 
        printf("Try -h for usage info\n");
        break;
    case 2:
        printhelp();
        break;
    case 3:
        if (parc < 3)
        {
            printf("Insufficient parameters. Use -h for usage info.\n");
            return 0;
        }
        buildcfl(pars[2]);
        break;
    case 4:
        if (parc < 3)
        {
            printf("Insufficient parameters. Use -h for usage info.\n");
            return 0;
        }
        if (parc < 4)
        {
            buildini(pars[2], "*.*");
        }
        else
        {
            buildini(pars[2], pars[3]);
        }
        break;
    }
    return 0;
}
