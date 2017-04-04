#ifndef RESOURCELOCATOR
#define RESOURCELOCATOR

#include "m68k.h"
#include "types.h"
#include <string>

struct dbinfo{
	std::string name;
	uint32_t type;
	uint32_t creator;
	bool operator==(dbinfo& cmp){
		if(cmp.type == type && cmp.creator == creator && cmp.name == name)return true;
		return false;
	}
};

bool typecreatorCMP(uint32_t type, uint32_t creator, uint32_t cmptype, uint32_t cmpcreator, bool zeroiswild, bool swapendian);

offset_68k getresource(int dbnum, uint16_t id, uint32_t tp);
offset_68k getappresource(uint16_t id, uint32_t tp);
offset_68k getrecord(int dbnum, uint16_t index);
//only applies to resource dbs
uint16_t resourcenumfromtypeid(int appnum, uint16_t id, uint32_t tp);

int getnumfromname(int startdb,std::string& name);
void getnumfromptr(offset_68k addr, int* app, uint16_t* index);
int numfromtypecreator(int startdb, uint32_t tp, uint32_t ctr);
int numfromtypecreatorwildcard(int startdb, uint32_t tp, uint32_t ctr);



offset_68k getfontaddr(uint8_t fontid);

//index to database info without endian wierdness
dbinfo getdbinfo(int num);
//uint32_t getdbtype(int num);//DO NOT DELETE

bool doesdbexist(dbinfo& dbstats);

#endif // RESOURCELOCATOR

