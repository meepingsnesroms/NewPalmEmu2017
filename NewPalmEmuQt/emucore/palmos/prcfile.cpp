#include <sys/types.h>
#include <sys/stat.h>

#include <fstream>

#include "palmwrapper.h"

#include "prcfile.h"
#include "datamanager.h"

//new list
#include "m68k.h"
#include "memmap.h"
#include "resourcelocator.h"
#include "dataexchange.h"
#include "datamanager.h"

typedef struct{
	TYPE type;
	uint16_t id;
	offset_68k location;
}prcresource;

typedef struct{
	offset_68k location;
	uint8_t attr;
	uint8_t pad[3];//not used
}pdbresource;

prcresource getprcresourceheader(uint8_t* rawheader){
	prcresource temp;
	memcpy(temp.type.typec,rawheader,4);//tiny string
	temp.id  = (rawheader[0x04] << 8)  | rawheader[0x05];
	temp.location = (rawheader[0x06] << 24) | (rawheader[0x07] << 16) | (rawheader[0x08] << 8) | rawheader[0x09];
	return temp;
}

pdbresource getpdbresourceheader(uint8_t* rawheader){
	pdbresource temp;
	temp.location = (rawheader[0x00] << 24) | (rawheader[0x01] << 16) | (rawheader[0x02] << 8) | rawheader[0x03];
	temp.attr = rawheader[0x04];
	return temp;
}


//68k malloc info
uint8_t *currealaddr;
offset_68k curmemloc;
offset_68k avbytes;


//helper functions

//returns the 68k address of what was installed
static offset_68k installresource(uint8_t *resource,size_t_68k size){
	if(!IS_EVEN(curmemloc)){
		currealaddr += 1;
		curmemloc += 1;
		avbytes -= 1;
	}

	offset_68k installaddr = curmemloc;
	for(size_t_68k counter = 0;counter < size;counter++){
		put_byte(installaddr + counter,resource[counter]);
	}

	//resources must be installed at EVEN addresses
	//if not attempting to execute them will cause a bus error(68k equivilant of SIGSEGV)
	if(!IS_EVEN(size))size++;

	currealaddr += size;
	curmemloc += size;
	avbytes -= size;
	return installaddr;
}

static void unpackprcresource(uint16_t resourcenum,uint8_t *prcdata,size_t_68k prcsize,int app){
	prcresource thisresource = getprcresourceheader(prcdata + 0x4E/*end of prc header*/ + (resourcenum * 10));
	uint16_t numrecords = prcdata[0x4C] << 8 | prcdata[0x4C + 1];
	size_t_68k size;

	if(resourcenum + 1 == numrecords){
		size = prcsize - thisresource.location;
	}else{
		prcresource nextresource = getprcresourceheader(prcdata + 0x4E/*end of prc header*/ + (resourcenum * 10) + 10);
		size = nextresource.location - thisresource.location;
	}

	palmresource prcchunk;

	prcchunk.id = thisresource.id;
	prcchunk.type = thisresource.type;
	prcchunk.location = installresource((uint8_t*)(prcdata + thisresource.location),size);
	prcchunk.size = size;

	apps[app].parts.push_back(prcchunk);

	//dbgprintf("Resource:%s,Id:%d,Installloc:0x%08x\n",stringfromtype(thisresource->type.typec).c_str(),beword(thisresource->id),apps[app].parts[resourcenum].location);
}

static void unpackpdbresource(uint16_t resourcenum,uint8_t *pdbdata,size_t_68k pdbsize,int dbnum){
	pdbresource thisresource = getpdbresourceheader(pdbdata + 0x4E/*end of pdb header*/ + (resourcenum * 8));
	uint16_t numrecords = pdbdata[0x4C] << 8 | pdbdata[0x4C + 1];
	size_t_68k size;

	if(resourcenum + 1 == numrecords){
		size = pdbsize - thisresource.location;
	}else{
		pdbresource nextresource = getpdbresourceheader(pdbdata + 0x4E/*end of pdb header*/ + (resourcenum * 8) + 8);
		size = nextresource.location - thisresource.location;
	}
	palmresource pdbchunk;
	pdbchunk.id = resourcenum;
	pdbchunk.attr = thisresource.attr;
	pdbchunk.location = installresource(pdbdata + thisresource.location,size);
	pdbchunk.size = size;

	//dbgprintf("Resource:PDB,Id:%d,Installloc:0x%08x\n",resourcenum,pdbchunk.location);
	apps[dbnum].parts.push_back(pdbchunk);
}

static int prcparse(uint8_t *prcfile,size_t_68k prcsize){
	palmdb meep;
	meep.numrecords = prcfile[0x4C] << 8 | prcfile[0x4C + 1];

	memcpy(meep.name,prcfile,32);

	meep.flags	  =	(prcfile[0x20] << 8)  | prcfile[0x21];
	meep.version  = (prcfile[0x22] << 8)  | prcfile[0x23];
	meep.modnum   = (prcfile[0x30] << 24) | (prcfile[0x31] << 16) | (prcfile[0x32] << 8) | prcfile[0x33];
	meep.appinfo  = (prcfile[0x34] << 24) | (prcfile[0x35] << 16) | (prcfile[0x36] << 8) | prcfile[0x37];
	meep.sortinfo = (prcfile[0x38] << 24) | (prcfile[0x39] << 16) | (prcfile[0x3A] << 8) | prcfile[0x3B];

	//these 2 are 4 character strings
	memcpy(meep.type.typec,prcfile + 0x3C,4);
	memcpy(meep.creator.typec,prcfile + 0x40,4);

	meep.uuidseed		= (prcfile[0x44] << 24) | (prcfile[0x45] << 16) | (prcfile[0x46] << 8) | prcfile[0x47];
	meep.nextrecordlist = (prcfile[0x48] << 24) | (prcfile[0x49] << 16) | (prcfile[0x4A] << 8) | prcfile[0x4B];


	//get the needed 68k memory
	curmemloc = getnewlinearchunks(NUM_BANKS(prcsize + meep.numrecords * 4)) << 16;
	if(curmemloc != 0){
		avbytes = NUM_BANKS(prcsize + meep.numrecords * 4) * SIZEOFBANK;
		currealaddr = (uint8_t*)get_real_address(curmemloc);
	}
	else return FAILEDMALLOC;

	meep.open = false;
	meep.resdb = true;

	apps.push_back(meep);
	for(uint16_t robin = 0;robin < meep.numrecords;robin++){
		unpackprcresource(robin,prcfile,prcsize,apps.size() - 1);
	}

	apps[apps.size() - 1].intmain = getresource(apps.size() - 1,1,'code');
	if(apps[apps.size() - 1].intmain != 0){
		apps[apps.size() - 1].exe = true;
	}

	return WORKED;
}

static int pdbparse(uint8_t *pdbfile,size_t_68k pdbsize){
	palmdb meep;
	meep.numrecords = pdbfile[0x4C] << 8 | pdbfile[0x4C + 1];

	memcpy(meep.name,pdbfile,32);

	meep.fileattr = (pdbfile[0x20] << 8)  | pdbfile[0x21];
	meep.version  = (pdbfile[0x22] << 8)  | pdbfile[0x23];
	meep.modnum   = (pdbfile[0x30] << 24) | (pdbfile[0x31] << 16) | (pdbfile[0x32] << 8) | pdbfile[0x33];
	meep.appinfo  = (pdbfile[0x34] << 24) | (pdbfile[0x35] << 16) | (pdbfile[0x36] << 8) | pdbfile[0x37];
	meep.sortinfo = (pdbfile[0x38] << 24) | (pdbfile[0x39] << 16) | (pdbfile[0x3A] << 8) | pdbfile[0x3B];

	//these 2 are 4 character strings
	memcpy(meep.type.typec,pdbfile + 0x3C,4);
	memcpy(meep.creator.typec,pdbfile + 0x40,4);

	meep.uuidseed		= (pdbfile[0x44] << 24) | (pdbfile[0x45] << 16) | (pdbfile[0x46] << 8) | pdbfile[0x47];
	meep.nextrecordlist = (pdbfile[0x48] << 24) | (pdbfile[0x49] << 16) | (pdbfile[0x4A] << 8) | pdbfile[0x4B];


	//get the needed 68k memory
	curmemloc = getnewlinearchunks(NUM_BANKS(pdbsize + meep.numrecords * 4)) << 16;
	if(curmemloc != 0){
		avbytes = NUM_BANKS(pdbsize + meep.numrecords * 4) * SIZEOFBANK;
		currealaddr = (uint8_t*)get_real_address(curmemloc);
	}
	else return FAILEDMALLOC;

	meep.open = false;
	meep.resdb = false;

	apps.push_back(meep);
	for(uint16_t robin = 0;robin < meep.numrecords;robin++){
		unpackpdbresource(robin,pdbfile,pdbsize,apps.size() - 1);
	}

	return WORKED;
}

static inline std::string getfiletype(std::string filename){
	unsigned int found = filename.find_last_of(".");
	return filename.substr(found + 1,3);
}



//lib functions
int loadfiletopalm(std::string path){
	struct stat stat_buf;
	stat(path.c_str(), &stat_buf);
	if(stat_buf.st_size == 0)return LOCKEDFILE;
	size_t_68k size = stat_buf.st_size;
	uint8_t *mempool = new uint8_t[size];
	std::ifstream appfile (path,std::ios::in | std::ios::binary);
	if (appfile.is_open()){
		appfile.read((char*)mempool,size);
	}
	appfile.close();

	uint16_t flags = (uint16_t)mempool[0x20] << 8 | mempool[0x21];

	int pass;
	std::string ftype = getfiletype(path);
	//working area
	if(ftype == "prc" && (flags & dmHdrAttrResDB))pass = prcparse(mempool,size);
	else if(ftype == "pdb" && !(flags & dmHdrAttrResDB))pass = pdbparse(mempool,size);
	else if(ftype == "prc" && !(flags & dmHdrAttrResDB)){
		dbgprintf("Conflicting filetypes: name is .prc but db says it is a record database\n");
		pass = pdbparse(mempool,size);
	}
	else if(ftype == "pdb" && (flags & dmHdrAttrResDB)){
		dbgprintf("Conflicting filetypes: name is .pdb but db says it is a resource database\n");
		pass = prcparse(mempool,size);
	}
	else{
		//PQA is just a formatted web page.(This is not a web browser.)
		pass = NOTPALMFILE;
	}

	delete[] mempool;
	return pass;
}

void releasefilemem(){
	int appvectorsize = apps.size();
	for(int bunfluff = 0;bunfluff < appvectorsize;bunfluff++){
		apps[bunfluff].parts.clear();
	}
	apps.clear();
}

void printprcerror(offset_68k pc){
	dbgprintf("Prc Loc:0x%08x\n",pc - apps[0].intmain);
}
