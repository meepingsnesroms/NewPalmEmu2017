/*! \file 
 * X-Forge Tool <br>
 * Copyright 2002 Fathammer Ltd
 * 
 * \brief GL Profile Analyzer
 * 
 * $Id: GLProfileAnalyzer.cpp,v 1.4 2002/10/31 09:31:54 jari Exp $
 * $Date: 2002/10/31 09:31:54 $
 * $Revision: 1.4 $
 *
 * This little tool converts the profiler GL device binary logs (xflogXXX.dat)
 * into tabbed text files which can then easily be imported into Microsoft Excel 
 * or other spreadsheet program for analysis.
 *
 * The log is in a very simple format; each sample is a 16-bit value consisting of
 * id (6 bits) and value (10 bits). In 'frame' sample, the value is in milliseconds,
 * while the fillers report pixels rendered. The pixel count is an approximate value,
 * not neccessarily the exact one. Also, huge triangles are capped at 1023 pixels,
 * so the 'total pixels drawn' value cannot be used to calculate overdraw complexity.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h> // memset

enum XFC_GLPROFILER_EVENTFLAGS
{
    XFCGLP_LOG_FRAME = 0,
    XFCGLP_LOG_TRIFLAT,
    XFCGLP_LOG_TRIGOURAUD,
    XFCGLP_LOG_TRITEXTURE,
    XFCGLP_LOG_TRITEXTURE1555,
    XFCGLP_LOG_TRITEXTUREFLAT,
    XFCGLP_LOG_TRITEXTUREGOURAUD,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVE,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVE1555,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEFLAT,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEGOURAUD,
    XFCGLP_LOG_TRIFLATADD,
    XFCGLP_LOG_TRIGOURAUDADD,
    XFCGLP_LOG_TRITEXTUREADD,
    XFCGLP_LOG_TRITEXTUREADD1555,
    XFCGLP_LOG_TRITEXTUREFLATADD,
    XFCGLP_LOG_TRITEXTUREGOURAUDADD,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEADD,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEADD1555,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEFLATADD,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEGOURAUDADD,
    XFCGLP_LOG_TRIFLATALPHA,
    XFCGLP_LOG_TRIGOURAUDALPHA,
    XFCGLP_LOG_TRITEXTUREALPHA,
    XFCGLP_LOG_TRITEXTUREALPHA1555,
    XFCGLP_LOG_TRITEXTUREFLATALPHA,
    XFCGLP_LOG_TRITEXTUREGOURAUDALPHA,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEALPHA,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEALPHA1555,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEFLATALPHA,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEGOURAUDALPHA,
    XFCGLP_LOG_TRIFLATINVMUL,
    XFCGLP_LOG_TRIGOURAUDINVMUL,
    XFCGLP_LOG_TRITEXTUREINVMUL,
    XFCGLP_LOG_TRITEXTUREINVMUL1555,
    XFCGLP_LOG_TRITEXTUREFLATINVMUL,
    XFCGLP_LOG_TRITEXTUREGOURAUDINVMUL,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEINVMUL,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEINVMUL1555,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEFLATINVMUL,
    XFCGLP_LOG_TRITEXTUREPERSPECTIVEGOURAUDINVMUL
};

// Used to print out filler names in outputs.
char *gFillerNames[] = 
{
    "Flat",                          
    "Gouraud",                       
    "Texture",                       
    "Texture1555",                   
    "TextureFlat",                   
    "TextureGouraud",                
    "TexturePerspective",            
    "TexturePerspective1555",        
    "TexturePerspectiveFlat",        
    "TexturePerspectiveGouraud",     
    "FlatAdd",                       
    "GouraudAdd",                    
    "TextureAdd",                    
    "TextureAdd1555",                
    "TextureFlatAdd",                
    "TextureGouraudAdd",             
    "TexturePerspectiveAdd",         
    "TexturePerspectiveAdd1555",     
    "TexturePerspectiveFlatAdd",     
    "TexturePerspectiveGouraudAdd",  
    "FlatAlpha",                     
    "GouraudAlpha",                  
    "TextureAlpha",                  
    "TextureAlpha1555",              
    "TextureFlatAlpha",              
    "TextureGouraudAlpha",           
    "TexturePerspectiveAlpha",       
    "TexturePerspectiveAlpha1555",   
    "TexturePerspectiveFlatAlpha",   
    "TexturePerspectiveGouraudAlpha",
    "FlatInvmul",                    
    "GouraudInvmul",                 
    "TextureInvmul",                 
    "TextureInvmul1555",             
    "TextureFlatInvmul",             
    "TextureGouraudInvmul",          
    "TexturePerspectiveInvmul",      
    "TexturePerspectiveInvmul1555",  
    "TexturePerspectiveFlatInvmul",  
    "TexturePerspectiveGouraudInvmul"
};

// Structure that holds information we gather from each gFrameData.
typedef struct frame_stat_struct
{
    int mTimeMS;            // Frame time, in milliseconds.
    int mFPS;               // Frame FPS (1000 / ms)
    int mPixelsFilled;      // How many pixels were filled this frame by triangle fillers
    int mPixelsByType[40];  // ..by filler type
    int mPolycount;         // How many filler calls were made this frame
    int mPolycountByType[40]; // ..by filler type
} FRAME_STATS;

FRAME_STATS *gFrameData;
int gFrameDataCount;

int * gPolySizes[41];

void parse(char * aFileName)
{
    printf("Parsing '%s'.. ", aFileName);
    FILE * f = fopen(aFileName, "rb");
    if (f == NULL)
    {
        printf("not found.\n");
        exit(1);
    }
    fseek(f,0,SEEK_END);
    int len = ftell(f);
    fseek(f,0,SEEK_SET);
    printf("%d samples found, loading.. ",len / 2);
    unsigned short * raw = new unsigned short[len / 2];
    fread(raw,len,1,f);
    fclose(f);
    printf("done.\n");
    printf("Parsing frames.. ");
    gFrameDataCount = 0;
    int i;
    for (i = 0; i < len / 2; i++)
        if (((raw[i] >> 10) & 63) == 0)
            gFrameDataCount++;
    printf("%d frames found, allocating.. ");
    gFrameData = new FRAME_STATS[gFrameDataCount];
    memset(gFrameData,0,sizeof(FRAME_STATS) * gFrameDataCount);
    printf("analysing.. ");
    int curframe = 0;    
    for (i = 0; i < len / 2; i++)
    {
        switch ((raw[i] >> 10) & 63)
        {
        case XFCGLP_LOG_FRAME:
            gFrameData[curframe].mTimeMS = raw[i] & 1023;
            gFrameData[curframe].mFPS = (raw[i] & 1023) ? 1000 / (raw[i] & 1023) : 1000;
            curframe++;
            break;
        default:
            if (((raw[i] >> 10) & 63) < 41)
            {
                gFrameData[curframe].mPolycountByType[((raw[i] >> 10) & 63) - 1]++;
                gFrameData[curframe].mPolycount++;
                gFrameData[curframe].mPixelsFilled += (raw[i] & 1023);
                gFrameData[curframe].mPixelsByType[((raw[i] >> 10) & 63) - 1] += (raw[i] & 1023);
            }
            else
            {
                printf("\nfound unknown event (%d)..",(raw[i] >> 10) & 63);
            }
            break;
        }
    }
    printf("done.\n");
    printf("Allocating memory for polygon sizes.. ");

    for (i = 0; i < 41; i++)
    {
        gPolySizes[i] = new int[1024];
        memset(gPolySizes[i], 0, sizeof(int) * 1024);
    }
    printf("counting.. ");
    for (i = 0; i < len / 2; i++)
    {
        if (((raw[i] >> 10) & 63) != 0 && ((raw[i] >> 10) & 63) < 41)
        {
            gPolySizes[0][raw[i] & 1023] ++; // total poly size
            gPolySizes[(raw[i] >> 10) & 63][raw[i] & 1023] ++; // poly size by type
        }
    }
    printf("done.\n");
    delete[] raw;
}

void output_frames()
{
    printf("Outputting frame stats..\n");
    int i, j;
    FILE * f = fopen("framestats.txt","w");
    fprintf(f,"frameFPS\tpolycount\tpixels\n");
    for (i = 0; i < gFrameDataCount; i++)
        fprintf(f,"%d\t%d\t%d\n",gFrameData[i].mFPS, gFrameData[i].mPolycount,gFrameData[i].mPixelsFilled);
    fclose(f);
    f = fopen("framestats_detailed.txt","w");
    fprintf(f,"frameTimeMS\t\t");
    for (i = 0; i < 40; i++)
    {
        fprintf(f,"%s count\t",gFillerNames[i]);
    }
    fprintf(f,"\t");
    for (i = 0; i < 40; i++)
    {
        fprintf(f,"%s pixels\t",gFillerNames[i]);
    }
    fprintf(f,"\n");
    for (i = 0; i < gFrameDataCount; i++)
    {
        fprintf(f,"%d\t\t",gFrameData[i].mTimeMS);
        for (j = 0; j < 40; j++)
            fprintf(f,"%d\t",gFrameData[i].mPolycountByType[j]);
        fprintf(f,"\t");
        for (j = 0; j < 40; j++)
            fprintf(f,"%d\t",gFrameData[i].mPixelsByType[j]);
        fprintf(f,"\n");
    }
    fclose(f);
}

void output_polysizes()
{
    printf("Outputting polygon sizes..\n");
    int i,j;
    FILE * f;
    f = fopen("PolySizeTotal.txt","w");
    for (i = 0; i < 1023; i++)
        fprintf(f,"%d\n",gPolySizes[0][i]);
    fclose(f);
    f = fopen("PolySizeDetailed.txt","w");
    for (i = 0; i < 40; i++)
        fprintf(f,"%s\t", gFillerNames[i]);
    fprintf(f,"\n");
    for (i = 0; i < 1023; i++)
    {
        for (j = 0; j < 40; j++)
        {
            fprintf(f,"%d\t",gPolySizes[j+1][i]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

int main(int parc, char ** pars)
{
   printf("GLProfileAnalyzer - Copyright 2002 Fathammer Ltd\n"
          "GLProfiler output to tabbed text file converter\n");
   if (parc < 2)
    {
        printf("Usage: GLProfileAnalyzer xflog###.dat\n");
        return 0;
    }
    parse(pars[1]);
    output_frames();
    output_polysizes();
    return 0;
}