#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenwad.h"

typedef struct profiledata_ 
{
    int threadid;
    int instruction;
} PROFILEDATA;

typedef struct functionmap_  
{
    char * name;
    char * object;
    int ofs;
    int hits;
} FUNCTIONMAP;

FUNCTIONMAP * fm;
int fmc;
PROFILEDATA * pd;
int pdc;

void load_profile_data(char * fn)
{
    FILE * f = fopen(fn,"rb");
    fseek(f,0,SEEK_END);
    int datalen = ftell(f);
    pdc = datalen/8;
    pd = new PROFILEDATA[pdc];
    fseek(f,0,SEEK_SET);
    fread(pd,datalen,1,f);
    fclose(f);
}

void load_mapfile(char * fn)
{
    FILE * f = fopen(fn,"rb");
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
    fmc = (end - start) / 2;
    fm = new FUNCTIONMAP[fmc];
    memset(fm,0,sizeof(FUNCTIONMAP)*fmc);
    int fmi = 0;
    for (i = start+1; i < end-1; i++)
    {
        tokenwad line;
        line.tokenize(lines.token(i)," ");
        if (line.tokens() > 2)
        {
            int j = 4;
            while (line.tokenequals(j,"")) j++;
            fm[fmi].name = line.tokendup(j);
            char * sah = fm[fmi].name;
            while (*sah) 
            { 
                if (*sah == '@') *sah = ',';
                sah++;
            }
            j++;
            while (line.tokenequals(j,"")) j++;
            fm[fmi].ofs = strtol(line.token(j),NULL,16);
            fm[fmi].object = line.tokendup(line.tokens()-1);
            fmi ++;
        }
    }
}

int * sortlist;

int compare( const void *arg1, const void *arg2 )
{   
   return fm[*(int*)arg2].hits - fm[*(int*)arg1].hits;
}


void analyse()
{
    FILE * f;
    // TODO: handle a thread at a time
    int i;
    for (i = 0; i < pdc; i++)
    {
        int j = 0;
        while (fm[j].ofs < pd[i].instruction) j++;
        fm[j-1].hits++;
    }
    
    sortlist = new int[fmc];
    for (i = 0; i < fmc; i++)
        sortlist[i] = i;
    qsort(sortlist,fmc,sizeof(int),compare);
    

    f = fopen("output.html","w");
    fprintf(f,"<html><body>\n<table border=1 cellspacing=0>\n");
    for (i = 0; i < fmc/* && fm[sortlist[i]].hits*/; i++)
    {
        fprintf(f,"<tr><td colspan=3 bgcolor=%s><font face=\"arial,helvetica\" size=\"-3\">%s:%s"
                  "</font></td></tr><tr><td bgcolor=%s><table border=3 width=%d cellpadding=0 ce"
                  "llspacing=0><tr><td bgcolor=#000000></td></tr></table></td><td bgcolor=%s><font face=\"arial,"
                  "helvetica\" size=\"-2\">%d</font></td><td bgcolor=%s><font face=\"arial,helve"
                  "tica\" size=\"-2\">%3.5f%%</font></td></tr>\n",
                  (i&1)?"#ffffff":"#eeeeee",
                  fm[sortlist[i]].object,
                  fm[sortlist[i]].name,
                  (i&1)?"#ffffff":"#eeeeee",
                  (int)((fm[sortlist[i]].hits * 3000.0f) / pdc),
                  (i&1)?"#ffffff":"#eeeeee",
                  fm[sortlist[i]].hits,
                  (i&1)?"#ffffff":"#eeeeee",
                  (fm[sortlist[i]].hits * 100.0f) / pdc);
    }
    fprintf(f,"</table>\n</body></html>\n");
    fclose(f);
}

int main(int parc, char ** pars)
{
    setbuf(stdout,NULL);
    if (parc < 3)
    {
        printf("ProfileAnalyzer\n"
               "Usage:\n"
               "profileanalyzer profiler_dump.dat application.map\n");
        return 0;
    }
    printf("loading data..\n"); 
    load_profile_data(pars[1]);
    printf("loading mapfile..\n");
    load_mapfile(pars[2]);
    printf("analyzing..\n");
    analyse();
    printf("done.\n");
    return 0;
}