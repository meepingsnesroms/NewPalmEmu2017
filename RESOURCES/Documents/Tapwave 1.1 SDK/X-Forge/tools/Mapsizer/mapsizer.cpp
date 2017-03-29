/*! \file 
 * X-Forge Tool <br>
 * Copyright 2002 Fathammer Ltd
 * 
 * \brief GL Profile Analyzer
 * 
 * $Id: mapsizer.cpp,v 1.1.1.1 2002/11/04 11:01:40 jari Exp $
 * $Date: 2002/11/04 11:01:40 $
 * $Revision: 1.1.1.1 $
 *
 * This little tool converts eVC .map files into object- and function based
 * lists of sizes for size-optimization purposes.
 *
 * From the output you can easily see which fillers, gl devices, etc, get 
 * linked to your application, and you can also check whether some application 
 * objects are strangely large.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenwad.h"

typedef struct objectmapstruct  
{
    char * name;
    char * object;
    int len;
    int ofs;
} OBJECTMAP;

OBJECTMAP * gObjectInfo;
int gObjectInfoCount;

void load_mapfile(char * aFilename)
{
    FILE * f = fopen(aFilename,"rb");
    if (f == NULL)
    {
        printf("Failed.\n");
        exit(1);
    }
    fseek(f,0,SEEK_END);
    int datalen = ftell(f);
    char * data = new char[datalen+1];
    data[datalen] = 0;
    fseek(f,0,SEEK_SET);
    fread(data,1,datalen,f);
    fclose(f);
    tokenwad lines;
    lines.tokenize(data,"\r\n");
    int i;
    int start, end;
    for (i = 0; i < lines.tokens(); i++)
    {
        tokenwad line;
        line.tokenize(lines.token(i)," ");
        if (line.tokens() > 2)
        {
            if (line.tokenequalsnocase(2,"Address")) start = i;
            if (line.tokenequalsnocase(1,"entry")) end = i;
        }
    }
    gObjectInfoCount = (end - start) / 2;
    gObjectInfo = new OBJECTMAP[gObjectInfoCount];
    memset(gObjectInfo,0,sizeof(OBJECTMAP)*gObjectInfoCount);
    int fmi = 0;
    for (i = start+1; i < end-1; i++)
    {
        tokenwad line;
        line.tokenize(lines.token(i)," ");
        if (line.tokens() > 2)
        {
            int j = 4;
            while (line.tokenequals(j,"")) j++;
            gObjectInfo[fmi].name = line.tokendup(j);
            char * sah = gObjectInfo[fmi].name;
            while (*sah) 
            { 
                if (*sah == '@') *sah = ',';
                sah++;
            }
            j++;
            while (line.tokenequals(j,"")) j++;
            gObjectInfo[fmi].ofs = strtol(line.token(j),NULL,16);
            gObjectInfo[fmi].object = line.tokendup(line.tokens()-1);
            if (gObjectInfo[fmi].object == NULL)
                gObjectInfo[fmi].object = "(NULL)\0";
            fmi ++;
        }
    }
}


void analyse()
{    
    FILE * f;
    for (int i = 0; i < gObjectInfoCount - 1; i++)
        gObjectInfo[i].len = gObjectInfo[i + 1].ofs - gObjectInfo[i].ofs;
    
    gObjectInfo[gObjectInfoCount].len = 0;
    
    f = fopen("results_func.txt","wb");

    for (i = 0; i < gObjectInfoCount; i++)
        fprintf(f,"%d\t%s\t%s\r\n",gObjectInfo[i].len,gObjectInfo[i].object,gObjectInfo[i].name);
    
    fclose(f);

    f = fopen("results_obj.txt","wb");
    int size = 0;
    int last = 0;
    for (i = 0; i < gObjectInfoCount - 2; i++)
    {
        if (gObjectInfo[i].object == NULL || (strcmp(gObjectInfo[i].object, gObjectInfo[last].object) != 0))
        {
            fprintf(f,"%d\t%s\r\n", size, gObjectInfo[last].object);
            last = i;
            size = 0;
        }
        size += gObjectInfo[i].len;
    }
    fclose(f);
}


int main(int aParc, char ** aPars)
{
    setbuf(stdout, NULL); // de-buffer stdout (immediate printf:s)

    printf("Mapsizer - Copyright 2002 Fathammer Ltd\n"
           "eVC .map to object size converter (for size optimization)\n");
    if (aParc < 2)
    {
        printf("Usage:\n"
               "mapsizer application.map\n");
        return 0;
    }
    printf("loading mapfile ('%s')..\n", aPars[1]);
    load_mapfile(aPars[1]);
    printf("analyzing.. (saving output to results_func.txt and results_obj.txt)\n");
    analyse();
    printf("done.\n");
    return 0;
}