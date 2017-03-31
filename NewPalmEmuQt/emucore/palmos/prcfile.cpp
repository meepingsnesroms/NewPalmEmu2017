#include <sys/types.h>
#include <sys/stat.h>

#include <fstream>

#include "palmwrapper.h"

#include "prcfile.h"
#include "datamanager.h"

//new list
#include "m68k.h"
#include "resourcelocator.h"
#include "dataexchange.h"
#include "datamanager.h"

//dont pad this struct
//(i hate that this is non standard
//but there is no other way except UBYTE x[10])
typedef struct __attribute__((packed)){
	TYPE type;
	UWORD id;
	CPTR location;
}prcresource;

//dont pad this struct
typedef struct __attribute__((packed)){
	CPTR location;
	UBYTE attr;
	UBYTE pad[3];//not used
}pdbresource;

/*
typedef struct{
	TYPE type;
	UWORD id;
	CPTR location;
}prcresource;

typedef struct{
	CPTR location;
	UBYTE attr;
	UBYTE pad[3];//not used
}pdbresource;

prcresource getprcresourceheader(UBYTE* rawheader){
	prcresource temp;
	memcpy(temp.type.typec,rawheader,4);//tiny string
	temp.id  = (rawheader[0x04] << 8)  | rawheader[0x05];
	temp.location = (rawheader[0x06] << 24) | (rawheader[0x07] << 16) | (rawheader[0x08] << 8) | rawheader[0x09];
	return temp;
}

pdbresource getpdbresourceheader(UBYTE* rawheader){
	pdbresource temp;
	temp.location = (rawheader[0x00] << 24) | (rawheader[0x01] << 16) | (rawheader[0x02] << 8) | rawheader[0x03];
	temp.attr = rawheader[0x04];
	return temp;
}
*/


//68k malloc info
UBYTE *currealaddr;
CPTR curmemloc;
CPTR avbytes;


//helper functions

//returns the 68k address of what was installed
static CPTR installresource(UBYTE *resource,size_t_68k size){
	if(!IS_EVEN(curmemloc)){
		currealaddr += 1;
		curmemloc += 1;
		avbytes -= 1;
	}

	CPTR installaddr = curmemloc;
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

static void unpackprcresource(UWORD resourcenum,UBYTE *prcdata,size_t_68k prcsize,int app){
	prcresource* thisresource = (prcresource*)(prcdata + 0x4E/*end of prc header*/ + (resourcenum * 10));
	UWORD numrecords = prcdata[0x4C] << 8 | prcdata[0x4C + 1];
	ULONG nextresourcestart = belong(((prcresource*)(prcdata + 0x4E/*end of prc header*/ + (resourcenum * 10) + 10))->location);
	size_t_68k size;

	if(resourcenum + 1 == numrecords){
		size = prcsize - belong(thisresource->location);
	}else{
		size = nextresourcestart - belong(thisresource->location);
	}

	palmresource prcchunk;

	prcchunk.id = beword(thisresource->id);
	prcchunk.type = thisresource->type;
	prcchunk.location = installresource((UBYTE*)(prcdata + belong(thisresource->location)),size);
	prcchunk.size = size;

	apps[app].parts.push_back(prcchunk);

	//dbgprintf("Resource:%s,Id:%d,Installloc:0x%08x\n",stringfromtype(thisresource->type.typec).c_str(),beword(thisresource->id),apps[app].parts[resourcenum].location);
}

static void unpackpdbresource(UWORD resourcenum,UBYTE *pdbdata,size_t_68k pdbsize,int dbnum){
	pdbresource* thisresource = (pdbresource*)(pdbdata + 0x4E/*end of pdb header*/ + (resourcenum * 8));
	UWORD numrecords = pdbdata[0x4C] << 8 | pdbdata[0x4C + 1];
	ULONG nextresourcestart = belong(((pdbresource*)(pdbdata + 0x4E/*end of pdb header*/ + (resourcenum * 8) + 8))->location);
	size_t_68k size;

	if(resourcenum + 1 == numrecords){
		size = pdbsize - belong(thisresource->location);
	}else{
		size = nextresourcestart - belong(thisresource->location);
	}
	palmresource pdbchunk;
	pdbchunk.id = resourcenum;
	pdbchunk.attr = thisresource->attr;
	pdbchunk.location = installresource((UBYTE*)(pdbdata + belong(thisresource->location)),size);
	pdbchunk.size = size;

	//dbgprintf("Resource:PDB,Id:%d,Installloc:0x%08x\n",resourcenum,pdbchunk.location);
	apps[dbnum].parts.push_back(pdbchunk);
}

static int prcparse(UBYTE *prcfile,size_t_68k prcsize){
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
		currealaddr = (UBYTE*)get_real_address(curmemloc);
	}
	else return FAILEDMALLOC;

	meep.open = false;
	meep.resdb = true;

	apps.push_back(meep);
	for(uint16 robin = 0;robin < meep.numrecords;robin++){
		unpackprcresource(robin,prcfile,prcsize,apps.size() - 1);
	}

	apps[apps.size() - 1].intmain = getresource(apps.size() - 1,1,'code');
	if(apps[apps.size() - 1].intmain != 0){
		apps[apps.size() - 1].exe = true;
		hasbootableapp = true;
	}

	return WORKED;
}

static int pdbparse(UBYTE *pdbfile,size_t_68k pdbsize){
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
		currealaddr = (UBYTE*)get_real_address(curmemloc);
	}
	else return FAILEDMALLOC;

	meep.open = false;
	meep.resdb = false;

	apps.push_back(meep);
	for(uint16 robin = 0;robin < meep.numrecords;robin++){
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
	UBYTE *mempool = new UBYTE[size];
	std::ifstream appfile (path,std::ios::in | std::ios::binary);
	if (appfile.is_open()){
		appfile.read((char*)mempool,size);
	}
	appfile.close();

	UWORD flags = (UWORD)mempool[0x20] << 8 | mempool[0x21];

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

void printprcerror(CPTR pc){
	dbgprintf("Prc Loc:0x%08x\n",pc - apps[0].intmain);
}
