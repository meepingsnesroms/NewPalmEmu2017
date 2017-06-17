#include "palmwrapper.h"//for app list

#include "m68k.h"
#include "minifunc.h"
#include "dataexchange.h"
#include "resourcelocator.h"
#include "rawimagetools.h"

bool typecreatorCMP(uint32_t type, uint32_t creator, uint32_t cmptype, uint32_t cmpcreator, bool zeroiswild, bool swapendian) {
	bool typeequ = false;
	bool creatorequ = false;

	if(swapendian) {
		swaplong(cmptype);
		swaplong(cmpcreator);
	}

	if(type == cmptype) {
		typeequ = true;
	}

	if(creator == cmpcreator) {
		creatorequ = true;
	}

	if(zeroiswild) {
		if(type == 0) {
			typeequ = true;
		}

		if(creator == 0) {
			creatorequ = true;
		}
	}

	if(typeequ && creatorequ) {
		return true;
	}

	return false;
}

offset_68k getresource(int dbnum, uint16_t id, uint32_t tp) {
	if(!apps[dbnum].resdb) {
		return nullptr_68k;
	}

	uint16_t end = apps[dbnum].parts.size();

	for(uint16_t cnt = 0; cnt < end; cnt++) {
		//dbgprintf("In:(Type:0x%08x,Id:%d),Cmp:(Type:0x%08x,Id:%d)\n",type,id,belong(apps[appnum].parts[cnt].type.typen),apps[appnum].parts[cnt].id);
		if(apps[dbnum].parts[cnt].id == id && belong(apps[dbnum].parts[cnt].type.typen) == tp) {
			return apps[dbnum].parts[cnt].location;
		}
	}

	return nullptr_68k;
}

//above for current app and includes overlay
offset_68k get_app_resource(uint16_t id, uint32_t tp) {
	offset_68k addr = nullptr_68k;

	//check overlay
	if(curoverlay > -1) {
		addr = getresource(curoverlay, id, tp);
	}

	//resource not in overlay,check app
	if(!addr) {
		addr = getresource(curapp, id, tp);
	}

	//resource does not exist
	return addr;
}

offset_68k getrecord(int dbnum, uint16_t index) {
	if(apps[dbnum].resdb) {
		return nullptr_68k;
	}

	return apps[dbnum].parts[index].location;
}

uint16_t resourcenumfromtypeid(int appnum, uint16_t id, uint32_t tp) {
	int end = apps[appnum].parts.size();

	for(int cnt = 0; cnt < end; cnt++) {
		//dbgprintf("In:(Type:0x%08x,Id:%d),Cmp:(Type:0x%08x,Id:%d)\n",type,id,belong(apps[appnum].parts[cnt].type.typen),apps[appnum].parts[cnt].id);
		if(apps[appnum].parts[cnt].id == id && belong(apps[appnum].parts[cnt].type.typen) == tp) {
			return cnt;
		}
	}

	return 0xFFFF;//0xFFFF = not found
}

int getnumfromname(int startdb, std::string& name) {
	int index;

	for(index = startdb; index < apps.size(); index++) {
		if(std::string(apps[index].name) == name) {
			return index;
		}
	}

	return -1;
}

void getnumfromptr(offset_68k addr, int* app, uint16_t* index) {
	//apps can append records/resources so every record/resource must be checked
	for(int count = 0; count < apps.size(); count++) {
		uint16_t partvectorsize = apps[count].parts.size();

		for(uint16_t curindex = 0; curindex < partvectorsize; curindex++) {
			offset_68k start = apps[count].parts[curindex].location;
			offset_68k end = start + apps[count].parts[curindex].size;

			if(addr >= start && addr <= end) {
				*app = count;
				*index = curindex;
				return;
			}
		}
	}
}

int numfromtypecreator(int startdb, uint32_t tp, uint32_t ctr) {
	int  index;
	int  appvectorsize = apps.size();
	bool correct;

	for(index = startdb; index < appvectorsize; index++) {
		correct = typecreatorCMP(tp, ctr, apps[index].type.typen, apps[index].creator.typen, false, true);

		if(correct) {
			return index;
		}
	}

	return -1;
}

int numfromtypecreatorwildcard(int startdb, uint32_t tp, uint32_t ctr) {
	int index;
	int appvectorsize = apps.size();
	bool correct;

	for(index = startdb; index < appvectorsize; index++) {
		correct = typecreatorCMP(tp, ctr, apps[index].type.typen, apps[index].creator.typen, true, true);

		if(correct) {
			return index;
		}
	}

	return -1;
}



offset_68k getfontaddr(uint8_t fontid) {
	//font type 'NFNT',extended font type 'nfnt'
	//font prc resource ids
	//system fonts = 10000 + fontid
	//system extended fonts = 10100 + fontid
	//user fonts = 1000 + fontid
	//(maybe)extended user fonts = 1100 + fontid
	uint16_t fntresid;

	if(fontid < fntAppFontCustomBase) {
		fntresid = 10000 + fontid;    //+ 1 is a hack
	}
	else {
		fntresid = 1000 + fontid - fntAppFontCustomBase;
	}

	offset_68k fontres = nullptr_68k;
	int totalapps = apps.size();
	int count = 0;

	while(!fontres && count < totalapps) {
		if(!fontres) {
			fontres = getresource(count, fntresid + 100, 'nfnt');    //hack
		}

		fontres = getresource(count, fntresid, 'NFNT');
		count++;
	}

	if(!fontres) {
		palmabrt();    //hack //cant find font
	}

	return fontres;
}


//index to database info without endian wierdness
dbinfo getdbinfo(int num) {
	dbinfo thisdb = {
	    std::string(apps[num].name),
		belong(apps[num].type.typen),
		belong(apps[num].creator.typen)
	};
	return thisdb;
}

bool doesdbexist(dbinfo& dbstats) {
	for(int index = 0; index < apps.size(); index++) {
		dbinfo cmp = getdbinfo(index);

		if(cmp == dbstats) {
			return true;    //that db already exists
		}
	}

	return false;
}
