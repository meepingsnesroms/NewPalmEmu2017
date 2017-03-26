#include "palmwrapper.h"//for app list

#include "m68k.h"
#include "minifunc.h"
#include "dataexchange.h"
#include "resourcelocator.h"
#include "rawimagetools.h"

bool typecreatorCMP(ULONG type,ULONG creator,ULONG cmptype,ULONG cmpcreator,bool zeroiswild,bool cmpisbigendian){
	bool typeequ = false;
	bool creatorequ = false;

	if(cmpisbigendian){
		swaplong(cmptype);
		swaplong(cmpcreator);
	}

	if(type == cmptype)typeequ = true;
	if(creator == cmpcreator)creatorequ = true;

	if(zeroiswild){
		if(type == 0)typeequ = true;
		if(creator == 0)creatorequ = true;
	}

	if(typeequ && creatorequ)return true;
	return false;
}

CPTR getresource(int dbnum, UWORD id, ULONG tp){
	if(!apps[dbnum].resdb)return nullptr_68k;

	uint16 end = apps[dbnum].parts.size();
	uint16 cnt;
	inc_for(cnt,end){
		//dbgprintf("In:(Type:0x%08x,Id:%d),Cmp:(Type:0x%08x,Id:%d)\n",type,id,belong(apps[appnum].parts[cnt].type.typen),apps[appnum].parts[cnt].id);
		if(apps[dbnum].parts[cnt].id == id && belong(apps[dbnum].parts[cnt].type.typen) == tp){
			return apps[dbnum].parts[cnt].location;
		}
	}
	return nullptr_68k;
}

//above for current app and includes overlay
CPTR getappresource(UWORD id, ULONG tp){
	CPTR addr = nullptr_68k;
	//check overlay
	if(curoverlay > -1)addr = getresource(curoverlay,id,tp);
	//resource not in overlay,check app
	if(!addr)addr = getresource(curapp,id,tp);
	//resource does not exist
	return addr;
}

CPTR getrecord(int dbnum, uint16 index){
	if(apps[dbnum].resdb)return nullptr_68k;

	return apps[dbnum].parts[index].location;
}

unsigned int resourcenumfromtypeid(int appnum, UWORD id, ULONG tp){
	uint16 end = apps[appnum].parts.size();
	uint16 cnt;
	inc_for(cnt,end){
		//dbgprintf("In:(Type:0x%08x,Id:%d),Cmp:(Type:0x%08x,Id:%d)\n",type,id,belong(apps[appnum].parts[cnt].type.typen),apps[appnum].parts[cnt].id);
		if(apps[appnum].parts[cnt].id == id && belong(apps[appnum].parts[cnt].type.typen) == tp)return cnt;
	}

	TEMPHACK;
	//change to uint16 (index <= numrecords - 1 && numrecords is 16bit)

	return 0xFFFFFFFF;
}

int getnumfromname(int startdb,string name){
	int goo;
	int appvectorsize = apps.size();
	for(goo = startdb;goo < appvectorsize;goo++){
		if(string(apps[goo].name) == name)return goo;
	}
	return -1;
}

void getnumfromptr(CPTR addr,int* app,UWORD* index){
	//apps can append records/resources so every record/resource must be checked
	int count;
	int appvectorsize = apps.size();
	inc_for(count,appvectorsize){
		UWORD partvectorsize = apps[count].parts.size();
		UWORD curindex;
		inc_for(curindex,partvectorsize){
			CPTR start = apps[count].parts[curindex].location;
			CPTR end = start + apps[count].parts[curindex].size;
			if(addr >= start && addr <= end){
				*app = count;
				*index = curindex;
				return;
			}
		}
	}
}

int numfromtypecreator(int startdb, ULONG tp, ULONG ctr){
	int goo;
	int appvectorsize = apps.size();
	bool correct;
	for(goo = startdb;goo < appvectorsize;goo++){
		correct = typecreatorCMP(tp,ctr,apps[goo].type.typen,apps[goo].creator.typen,false,true);
		if(correct)return goo;
	}
	return -1;
}

int numfromtypecreatorwildcard(int startdb, ULONG tp, ULONG ctr){
	int goo;
	int appvectorsize = apps.size();
	bool correct;
	for(goo = startdb;goo < appvectorsize;goo++){
		correct = typecreatorCMP(tp,ctr,apps[goo].type.typen,apps[goo].creator.typen,true,true);
		if(correct)return goo;
	}
	return -1;
}



CPTR getfontaddr(UBYTE fontid){
	//font type 'NFNT',extended font type 'nfnt'

	//font prc resource ids
	//system fonts = 10000 + fontid
	//system extended fonts = 10100 + fontid
	//user fonts = 1000 + fontid
	//(maybe)extended user fonts = 1100 + fontid

	UWORD fntresid;


	if(fontid < fntAppFontCustomBase)fntresid = 10000 + fontid;//+ 1 is a hack
	else fntresid = 1000 + fontid - fntAppFontCustomBase;

	CPTR fontres = nullptr_68k;
	int totalapps = apps.size();
	int count = 0;
	while(!fontres && count < totalapps){
		if(!fontres)fontres = getresource(count,fntresid + 100,'nfnt');//hack
		fontres = getresource(count,fntresid,'NFNT');
		count++;
	}

	if(!fontres)palmabrt();//hack //cant find font

	return fontres;
}


//index to database info without endian wierdness
dbinfo getdbinfo(int num){
	dbinfo thisdb = {
		string(apps[num].name),
		belong(apps[num].type.typen),
		belong(apps[num].creator.typen)
	};
	return thisdb;
}

/*
ULONG getdbtype(int num){
	return belong(apps[num].type.typen);
}
*/



bool doesdbexist(dbinfo& dbstats){
	int goo;
	int appvectorsize = apps.size();
	inc_for(goo,appvectorsize){
		dbinfo cmp = getdbinfo(goo);
		if(cmp == dbstats)return true;//that db already exists
	}
	return false;
}
