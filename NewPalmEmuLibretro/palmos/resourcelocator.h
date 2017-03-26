#ifndef RESOURCELOCATOR
#define RESOURCELOCATOR

#include "m68k.h"
#include "types.h"
#include <string>

struct dbinfo{
	std::string name;
	ULONG type;
	ULONG creator;
	bool operator==(dbinfo& cmp){
		if(cmp.type == type && cmp.creator == creator && cmp.name == name)return true;
		return false;
	}
};

bool typecreatorCMP(ULONG type,ULONG creator,ULONG cmptype,ULONG cmpcreator,bool zeroiswild,bool cmpisbigendian);

CPTR getresource(int dbnum, UWORD id, ULONG tp);
CPTR getappresource(UWORD id, ULONG tp);
CPTR getrecord(int dbnum, uint16 index);
//only applies to resource dbs
unsigned int resourcenumfromtypeid(int appnum, UWORD id, ULONG tp);

int getnumfromname(int startdb,std::string name);
void getnumfromptr(CPTR addr, int* app, UWORD* index);
int numfromtypecreator(int startdb, ULONG tp, ULONG ctr);
int numfromtypecreatorwildcard(int startdb, ULONG tp, ULONG ctr);



CPTR getfontaddr(UBYTE fontid);

//index to database info without endian wierdness
dbinfo getdbinfo(int num);
//ULONG getdbtype(int num);//DO NOT DELETE

bool doesdbexist(dbinfo &dbstats);

#endif // RESOURCELOCATOR

