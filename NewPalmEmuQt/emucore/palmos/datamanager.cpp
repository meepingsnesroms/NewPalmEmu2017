#include "palmwrapper.h"//for app list
#include "datamanager.h"
#include "palmapi.h"

//new list
#include "m68k.h"
#include "memmap.h"
#include "minifunc.h"
#include "dataexchange.h"
#include "stdlib68k.h"
#include "palmmalloc.h"
#include "resourcelocator.h"
#include "palmdefines.h"

#include <string.h>
#include <string>


int recentresdb,recentoverlay;
uint16_t dmlasterror;

inline bool caselessequ(char c1,char c2){
	if(c1 >= 97 && c1 <= 122)c1 -= 32;
	if(c2 >= 97 && c2 <= 122)c2 -= 32;

	if(c1 == c2)return true;
	return false;
}

uint32_t uniqueidseed;

uint32_t nextuid(){
	//palm just increments by one each iteration
	uint32_t curuid = uniqueidseed;
	uniqueidseed++;
	return curuid;
}

void forgeuniqueids(){
	int totalapps = apps.size();
	for(int count = 0;count < totalapps;count++){
		if(!apps[count].resdb){
			uniqueidseed = apps[count].uuidseed;
			//dbgprintf("Seed:%08x\n",uniqueidseed);
			uint16_t records = apps[count].parts.size();
			for(uint16_t reccount = 0;reccount < records;reccount++){
				apps[count].parts[reccount].uniqueid = nextuid();
			}
		}
	}
}

void reindexrecords(int db){
	uint16_t recordnum = apps[db].parts.size();
	for(uint16_t count = 0;count < recordnum;count++){
		apps[db].parts[count].id = count;
	}
	apps[db].numrecords = recordnum;
}



//database
void dmopendatabasebytypecreator(){
	stacklong(type);
	stacklong(creator);
	stackword(mode);

	dbgprintf("Type:%.4s,Creator:%.4s\n",(char*)&type,(char*)&creator);
	//A0 = numfromtypecreator(0,type,creator);
	int dbnum = numfromtypecreator(0,type,creator);
	if(dbnum == -1){
		dmlasterror = dmErrCantFind;
		A0 = nullptr_68k;
	}else{
		apps[dbnum].open = true;
		apps[dbnum].openmode = mode;
		A0 = dbnum;
		A0 += dmOpenRefOffset;

		TEMPHACK;
		//something with overlay
	}

	dbgprintf("A0:%08x\n",A0);
}

void dmcreatedatabase(){
	stackword(card);
	stackptr(nameptr);
	stacklong(creator);
	stacklong(type);
	stackbool(resdb);


	dbinfo newdbinfo;
	newdbinfo.name = readstring(nameptr);
	newdbinfo.type = type;
	newdbinfo.creator = creator;

	if(doesdbexist(newdbinfo)){
		D0 = dmErrAlreadyExists;
		palmabrt();//hack
		return;
	}

	if(card != 0)dbgprintf("invalid card");

	palmdb newdb;

	offset_68k fish;
	for(fish = 0;fish < 32;fish++){
		newdb.name[fish] = (char)get_byte(nameptr + fish);
		if(newdb.name[fish] == '\0')break;
	}
	for(;fish < 32;fish++){
		newdb.name[fish] = '\0';
	}

	newdb.creator.typen = belong(creator);
	newdb.type.typen = belong(type);

	newdb.waschanged = true;
	newdb.fileattr = (resdb != 0);
	newdb.resdb = (resdb != 0);

	newdb.numrecords = 0;

	TEMPHACK;
	//add creation time

	apps.push_back(newdb);
	dbgprintf("ResDb (bool):%d\n",resdb);

	D0 = errNone;
}

void dmnewrecord(){
	stackptr(dmopenref);
	stackptr(atp);//uint16_t
	stacklong(size);
	dmopenref -= dmOpenRefOffset;

	//check if is record database
	if(apps[dmopenref].resdb){
		//palmabrt();//hack
		dmlasterror = dmErrNotRecordDB;
		A0 = nullptr_68k;
	}

	uint16_t index = get_word(atp);

	dbgprintf("Atp:%d,Index:%d,Dbptr:%d,Size:%d\n",atp,index,dmopenref,size);

	offset_68k recaddr = getfreestorageramhandle(size);

	dbgprintf("Addr:%08x\n",recaddr);

	if(recaddr){
		palmresource newrec;
		newrec.location = recaddr;
		newrec.size = size;
		newrec.id = index;//give record an id
		newrec.attr = dmRecAttrBusy | dmRecAttrDirty;//mark record busy/dirty

		if(index >= apps[dmopenref].parts.size() || index == dmMaxRecordIndex){
			newrec.id = apps[dmopenref].parts.size();//give record an id!!
			apps[dmopenref].parts.push_back(newrec);
			apps[dmopenref].numrecords += 1;
			put_word(atp,apps[dmopenref].parts.size() - 1);
		}else apps[dmopenref].parts[index] = newrec;
		A0 = recaddr;
	}else{
		palmabrt();//hack //not enough memory (This palm has no memory limit so THIS SHOULD NEVER HAPPEN)
		dmlasterror = dmErrMemError;
		A0 = nullptr_68k;
	}
}

TEMPHACK
void dmnewresource(){
	stackptr(dmopenref);
	stacklong(type);
	stackword(id);
	stacklong(size);
	dmopenref -= dmOpenRefOffset;

	//check if is resource database
	if(!apps[dmopenref].resdb){
		//palmabrt();//hack
		dmlasterror = dmErrNotRecordDB;
		A0 = nullptr_68k;
	}

	//check if resource already exists
	if(getresource(dmopenref,id,type)){
		dmlasterror = dmErrAlreadyExists;
		A0 = nullptr_68k;
		return;
	}

	offset_68k newresource = getfreeheaphandle(size);
	if(newresource){
		palmresource resinfo;
		resinfo.type.typen = belong(type);//fix endian swap //hack
		resinfo.id = id;
		resinfo.size = size;
		resinfo.location = newresource;
		//resources dont use record attributes
		apps[dmopenref].parts.push_back(resinfo);
		A0 = newresource;
	}else{
		palmabrt();//hack //not enough memory (This palm has no memory limit so THIS SHOULD NEVER HAPPEN)
		dmlasterror = dmErrMemError;
		A0 = nullptr_68k;
	}
}

void dmqueryrecord(){
	stackptr(dmopenref);
	stackword(index);
	dmopenref -= dmOpenRefOffset;
	A0 = getrecord(dmopenref,index);
	if(!A0)dmlasterror = dmErrCantFind;
}

void dmnewhandle(){
	stackptr(dmopenref);//unused
	stacklong(size);
	if(size > 0xFFFF)palmabrt();//hack
	dmopenref -= dmOpenRefOffset;
	A0 = getfreestorageramhandle(size);
}

void dmwrite(){
	stackptr(record);
	stacklong(offset);
	stackptr(src);//location
	stacklong(bytes);//amount

	offset_68k total = record + offset;//get address of destination
	//dbgprintf("Record:%08x,Offset:%08x\n",record,offset);

	memcpy68k(total,src,bytes);

	D0 = errNone;
}

void dmreleaserecord(){
	stackptr(dmopenref);
	stackword(index);
	stackbool(dirty);
	dmopenref -= dmOpenRefOffset;

	dbgprintf("DB:%08x,Index:%d\n",dmopenref,index);

	//check if record database
	if(apps[dmopenref].resdb){
		D0 = dmErrNotRecordDB;
		return;
	}

	if(index > apps[dmopenref].parts.size() - 1){
		D0 = dmErrIndexOutOfRange;
	}else{
		apps[dmopenref].parts[index].attr &= ~dmRecAttrBusy;
		if(dirty)apps[dmopenref].parts[index].attr |= dmRecAttrDirty;
		else apps[dmopenref].parts[index].attr &= ~dmRecAttrDirty;

		dbgprintf("Db:%08x,Index:%08x,RECORD RELEASED\n",dmopenref,index);//hack

		D0 = errNone;
	}
}

void dmgetrecord(){
	stacklong(dmopenref);
	stackword(index);
	dmopenref -= dmOpenRefOffset;

	dbgprintf("DB:%08x,Index:%d\n",dmopenref,index);

	//check if record database
	if(apps[dmopenref].resdb){
		//palmabrt();//hack
		dmlasterror = dmErrNotRecordDB;
		A0 = nullptr_68k;
	}

	apps[dmopenref].parts[index].attr |= dmRecAttrBusy;
	A0 = apps[dmopenref].parts[index].location;

	dbgprintf("A0:%08x\n",A0);
}

TEMPHACK
void dmattachrecord(){
	stackptr(dmopenref);
	stackptr(atp);
	stackptr(newhand);
	stackptr(oldhand);//pointer to pointer
	dmopenref -= dmOpenRefOffset;

	//check if is record database
	if(apps[dmopenref].resdb){
		dmlasterror = dmErrNotRecordDB;
		A0 = nullptr_68k;
		return;
	}

	if(ishandle(memisalloc(newhand)) == false)palmabrt();//hack

	uint16_t index = get_word(atp);

	dbgprintf("AttachRecord:(DB:%d,At:%d,OldPtr:%08x,NewPtr:%08x)\n",dmopenref,index,oldhand,newhand);

	if(index == dmMaxRecordIndex || index >= apps[dmopenref].parts.size()){
		palmresource record;
		record.id = apps[dmopenref].parts.size();
		record.location = newhand;
		record.attr = 0;//fix //hack
		apps[dmopenref].parts.push_back(record);
		put_word(atp,apps[dmopenref].parts.size() - 1);
	}else{
		if(!oldhand){
			palmresource record;
			record.location = newhand;
			record.size = 0;//fix //may get size from malloc list
			apps[dmopenref].parts.insert(apps[dmopenref].parts.begin() + index,record);

			//palmabrt();//hack
		}else{
			offset_68k oldaddr = apps[dmopenref].parts[index].location;

			//replace record
			apps[dmopenref].parts[index].location = newhand;
			apps[dmopenref].parts[index].size = 0;//fix //may get size from malloc list
			apps[dmopenref].parts[index].lockcount = 0;

			put_long(oldhand,oldaddr);
		}
		//atp remains the same
	}

	TEMPHACK;
	//this crashes for some reason

	apps[dmopenref].parts[index].attr |= dmRecAttrDirty;

	reindexrecords(dmopenref);
	D0 = errNone;
}

void dmopendatabaseinfo(){
	offset_68k dmopenref = poplonglink();
	//below are pointers for data output!
	offset_68k dbidptr = poplonglink();//palm struct
	offset_68k opencountptr = poplonglink();//uint16_t
	offset_68k modeptr = poplonglink();//uint16_t
	offset_68k cardnumptr = poplonglink();//uint16_t
	offset_68k resdbptr = poplonglink();//bool

	//dbgprintf("Db:%08x\n",dmopenref);

	dmopenref -= dmOpenRefOffset;

	if(dbidptr)put_long(dbidptr,dmopenref + dmOpenRefOffset);
	if(cardnumptr)put_word(cardnumptr,0);
	if(opencountptr)put_word(opencountptr,1);//only 1 app is running and it is reading this so always 1
	if(modeptr)put_word(modeptr,apps[dmopenref].openmode);
	if(resdbptr)put_word(resdbptr,apps[dmopenref].resdb);//maybe uint8_t

	D0 = errNone;
}

void dmget1resource(){
	stacklong(type);
	stackword(id);

	offset_68k resource = nullptr_68k;

	TEMPHACK;
	//should search the most recently opened resource database(and its overlay) not the one launched

	//search overlay
	if(curoverlay > -1){
		resource = getresource(curoverlay,id,type);
		if(resource){
			A0 = resource;
			return;
		}
	}

	//resource not in overlay or overlay dosent exist,try app resources instead
	if(!resource)resource = getresource(curapp,id,type);

	//resource does not exist
	if(!resource)dmlasterror = dmErrCantFind;

	A0 = resource;
}

void dmgetresource(){
	stacklong(type);
	stackword(id);

	int totalapps = apps.size();
	int openappscan;
	offset_68k resource;
	for(openappscan = 0;openappscan < totalapps;openappscan++){
		if(apps[openappscan].open)resource = getresource(openappscan,id,type);
		if(resource)break;
	}

	if(!resource){
		dmlasterror = dmErrCantFind;
		uint32_t buns = belong(type);
		dbgprintf("ErrorResNotFound Type:%.4s,Id:%04x,resourceptr:0x%08x,App:%d\n",(char*)&buns,id,resource,openappscan);
	}

	A0 = resource;
}

void dmreleaseresource(){
	//this function just signals the memhandle of the resoure can now be changed
	D0 = errNone;
}

void dmremoverecord(){
	stackptr(dmopenref);
	stackword(index);
	dmopenref -= dmOpenRefOffset;

	dbgprintf("DB:%d,Index:%04x\n",dmopenref,index);

	offset_68k dataloc = getrecord(dmopenref,index);
	abstractfree(dataloc);

	//more
	TEMPHACK;
	//palmabrt();
	apps[dmopenref].parts.erase(apps[dmopenref].parts.begin() + index);
	reindexrecords(dmopenref);

	D0 = errNone;
}

TEMPHACK
void dmgetnextdatabasebytypecreator(){
	stackbool(newsearch);
	stackptr(searchstateptr);
	stacklong(type);
	stacklong(creator);
	stackbool(onlylatest);
	stackptr(cardnoptr);//dummy uint16_t
	stackptr(dbidptr);//write uint32_t

	//palmabrt();//hack

	uint32_t thisdb;

	if(newsearch){
		thisdb = numfromtypecreatorwildcard(0,type,creator);
		put_long(searchstateptr,thisdb);
	}
	else{
		thisdb = numfromtypecreatorwildcard(get_long(searchstateptr) + 1,type,creator);
		put_long(searchstateptr,thisdb);
	}

	//dbgprintf("Dbnum:%d\n",thisdb);

	if(thisdb >= 0xFFFF)D0 = dmErrCantFind;
	else {
		put_word(cardnoptr,0);
		put_long(dbidptr,thisdb + dmOpenRefOffset);
		D0 = errNone;
	}
}

void dmnextopenresdatabase(){
	stackptr(dmopenref);

	//dbgprintf("DBnum:%d\n",dmopenref);

	if(dmopenref)dmopenref -= dmOpenRefOffset;

	int appvectorsize = apps.size();
	int i;
	for(i = dmopenref;i < appvectorsize;i++){//if dmopenref is null it already == 0
		if(apps[i].resdb && apps[i].open){
			A0 = i + dmOpenRefOffset;
			return;
		}
	}

	palmabrt();//hacl
	A0 = nullptr_68k;
}

void dmdatabaseinfo(){
	stackword(cardno);
	stacklong(localid);//LocalID (uint32_t) //treat the same as dmOpenRef
	stackptr(dbnameptr);//char array
	stackptr(attrptr);//uint16_t
	stackptr(versionptr);//uint16_t
	stackptr(crdateptr);//uint32_t
	stackptr(moddateptr);//uint32_t
	stackptr(bkupdateptr);//uint32_t
	stackptr(modnumptr);//uint32_t
	stackptr(appinfoidptr);//uint32_t
	stackptr(sortinfoptr);//uint32_t
	stackptr(typeptr);//uint32_t
	stackptr(creatorptr);//uint32_t

	//dbgprintf("DBid:%d,(in HEX):%08x\n",localid,localid);

	uint16_t dbid = localid - dmOpenRefOffset;

	if(dbnameptr)writestring(dbnameptr,(char*)apps[dbid].name);
	putwordifvptr(attrptr,apps[dbid].flags);
	putwordifvptr(versionptr,apps[dbid].version);
	putlongifvptr(crdateptr,apps[dbid].creationtime);
	putlongifvptr(moddateptr,apps[dbid].modificationtime);
	putlongifvptr(bkupdateptr,apps[dbid].backuptime);
	putlongifvptr(modnumptr,apps[dbid].modnum);

	if(appinfoidptr || sortinfoptr){
		dbgprintf("Nope not yet\n");
	}
	//putlongifvptr(appinfoidptr,apps[dbid].creationtime);
	//putlongifvptr(sortinfoptr,apps[dbid].creationtime);

	putlongifvptr(typeptr,belong(apps[dbid].type.typen));
	putlongifvptr(creatorptr,belong(apps[dbid].creator.typen));
}

TEMPHACK
void dmsetdatabaseinfo(){
	stackword(cardno);//dummy
	stacklong(localid);
	stackptr(nameptr);//uint16_t
	stackptr(versionptr);//uint16_t
	stackptr(crdateptr);//uint32_t
	stackptr(moddateptr);//uint32_t
	stackptr(lstbkpdateptr);//uint32_t
	stackptr(modnumptr);//uint32_t
	stackptr(appinfoidptr);//uint32_t
	stackptr(sortinfoidptr);//uint32_t
	stackptr(typeptr);//uint32_t
	stackptr(creatorptr);//uint32_t
	localid -= dmOpenRefOffset;

	/*
	//check for errors
	if(nameptr || creatorptr || typeptr){
		uint32_t cmpcreator = belong(apps[localid].creator.typen);
		uint32_t cmptype = belong(apps[localid].type.typen);
		string cmpname = string(apps[localid].name);

		//swap to new values
		setlongifvptr(creatorptr,cmpcreator);
		setlongifvptr(typeptr,cmptype);
		if(nameptr)cmpname = readstring(nameptr);


		getnumfromname(0,cmpname)

		int count;
		int end = apps.size();
		inc_for(count,end){
			if(count != localid){

			}
		}

		D0 = dmErrAlreadyExists;
	}
	*/


	if(nameptr){
		std::string appname = readstring(nameptr);
		if(appname.size() > 32){
			D0 = dmErrInvalidDatabaseName;
			return;
		}
		copy(appname.begin(), appname.end(), apps[localid].name);
	}

	if(versionptr)apps[localid].version = get_word(versionptr);

	if(crdateptr)apps[localid].creationtime = get_long(crdateptr);

	if(moddateptr)apps[localid].modificationtime = get_long(moddateptr);

	if(lstbkpdateptr)apps[localid].backuptime = get_long(lstbkpdateptr);

	if(modnumptr)apps[localid].modnum = get_long(modnumptr);

	if(appinfoidptr)apps[localid].appinfo = get_long(appinfoidptr);

	if(sortinfoidptr)apps[localid].sortinfo = get_long(sortinfoidptr);

	if(typeptr)apps[localid].type.typen = belong(get_long(typeptr));

	if(creatorptr)apps[localid].creator.typen = belong(get_long(creatorptr));

	D0 = errNone;
}

void dmopendatabase(){
	stackword(cardno);
	stacklong(localid);
	stackword(mode);

	uint16_t dbindex = localid - dmOpenRefOffset;//HACK use a different offset for localids



	if(dbindex < apps.size()){
		A0 = localid;
		apps[dbindex].open = true;
		apps[dbindex].openmode = mode;

		//HACK may or may not open overlay if opened in any mode other than read only
		//open overlay next (not done) //if(apps[dbindex].resdb)(process);
		/*
		if(apps[dbindex].resdb){

			recentresdb = dbindex;
			recentoverlay = numfromtypecreator(0,'ovly',belong(apps[dbindex].creator.typen));//will be -1 if no overlay exists

		}
		*/
	}
	else A0 = nullptr_68k;
}

TEMPHACK
//does not check for overlay or recycle bit
void dmclosedatabase(){
	stackptr(dmopenref);
	dmopenref -= dmOpenRefOffset;

	if(dmopenref > apps.size() - 1){
		palmabrt();//hack
		D0 = dmErrInvalidParam;
		return;
	}

	apps[dmopenref].open = false;

	TEMPHACK;
	//If the database has the recyclable bit set (dmHdrAttrRecyclable),
	//DmCloseDatabase calls DmDeleteDatabase to delete it.

	D0 = errNone;
}

void dmnumrecords(){
	stacklong(dmopenref);
	dmopenref -= dmOpenRefOffset;
	D0 = apps[dmopenref].parts.size();
}

//a return value of 0xFFFF means resource not found
void dmfindresource(){
	stackptr(dmopenref);
	stacklong(type);
	stackword(id);
	stackptr(resourceptr);
	dmopenref -= dmOpenRefOffset;

	D0 = resourcenumfromtypeid(dmopenref,id,type);
}

void dmfinddatabase(){
	stackword(cardno);//dummy
	stackptr(nameptr);

	std::string name = readstring(nameptr);

	dbgprintf("Name:%s\n",name.c_str());

	uint32_t database = getnumfromname(0,name);

	//type is localid not dmopenref (localid is not a pointer,use D0)
	if(database != 0xFFFFFFFF)D0 = database + dmOpenRefOffset;
	else D0 = 0;
}

TEMPHACK
//may display fatal error on invalid uniqueid
void dmfindrecordbyid(){
	stackptr(dmopenref);
	stacklong(uniqueid);
	stackptr(indexptr);//uint16_t
	dmopenref -= dmOpenRefOffset;

	if(apps[dmopenref].resdb){
		D0 = dmErrUniqueIDNotFound;//may be dmErrNotRecordDB
		return;
	}

	//check records
	uint16_t records = apps[dmopenref].parts.size();
	for(uint16_t count = 0;count < records;count++){
		if(apps[dmopenref].parts[count].uniqueid == uniqueid){
			put_word(indexptr,count);
			D0 = errNone;
			return;
		}
	}

	D0 = dmErrUniqueIDNotFound;
}

void dmgetresourceindex(){
	stackptr(dmopenref);
	stackword(id);
	dmopenref -= dmOpenRefOffset;

	A0 = apps[dmopenref].parts[id].location;
}

TEMPHACK
void dmwritecheck(){
	stackptr(recordptr);
	stacklong(offset);
	stacklong(bytes);

	dbgprintf("Record:%08x,Offset:%08x,Bytes:%08x\n",recordptr,offset,bytes);

	TEMPHACK;
	//actualy check record

	D0 = errNone;
}

void dmsearchresource(){
	stacklong(restype);
	stackword(resid);
	stackptr(resptr);//if this is not null check this instead
	stackptr(dmopenrefout);//write offset_68k

	//D0 = indexofresource(not id of resource!);

	//pointer mode //DONE
	if(resptr){
		int appout = -1;
		uint16_t idbunny = 0xFFFF;
		getnumfromptr(resptr,&appout,&idbunny);
		//no need to check for overlay or duplicates since 2 data chunks cant share one pointer
		if(appout > -1 && apps[appout].open){
			put_long(dmopenrefout,appout + dmOpenRefOffset);
			D0 = idbunny;
		}else{
			//that pointer does not correspond to a resource
			palmabrt();//hack //replace with error code or popup
		}
		return;
	}


	//type,id mode //DONE
	//if resource db has an overlay return the resource from the overlay
	//(regardless of wether the overlay is first in the app vector or not)
	int appbackup = -1;
	uint16_t indexbackup;
	int appvectorsize = apps.size();
	for(int appscnt = 0;appscnt < appvectorsize;appscnt++){
		if(apps[appscnt].resdb && apps[appscnt].open){
			uint16_t resloc = resourcenumfromtypeid(appscnt,resid,restype);
			if(resloc < 0xFFFF){
				dbinfo appcheck = getdbinfo(appscnt);
				if(appcheck.type == 'appl'){//hack //may apply to non application resource dbs aswell
					//may have overlay
					appbackup = appscnt;
					indexbackup = resloc;
				}else{
					put_long(dmopenrefout,appscnt + dmOpenRefOffset);
					D0 = resloc;
					return;
				}
			}
		}
	}
	if(appbackup > -1){
		put_long(dmopenrefout,appbackup + dmOpenRefOffset);
		D0 = indexbackup;
	}
}

void dmresetrecordstates(){
	stackptr(dmopenref);
	dmopenref -= dmOpenRefOffset;

	//from sdk header DataMgr.h vvv
	//Utility to unlock all records and clear busy bits

	uint16_t itemnum = apps[dmopenref].parts.size();
	for(uint16_t index = 0;index < itemnum;index++){
		apps[dmopenref].parts[index].lockcount = 0;
		apps[dmopenref].parts[index].attr &= ~dmRecAttrBusy;
	}

	D0 = errNone;//this is an undocumented system use only function
}



//memory
TEMPHACK
//unsure of purpose,most likely multithreading
void memsemaphorereserve(){
	stackbool(writeaccess);

	//undocumented

	D0 = errNone;
}

TEMPHACK
//unsure of purpose,most likely multithreading
void memsemaphorerelease(){
	stackbool(writeaccess);

	//undocumented

	D0 = errNone;
}

void memptrnew(){
	stacklong(size);
	if(size > 0xFFFF)palmabrt();//hack
	A0 = getfreeheap(size);
	dbgprintf("A0:%08x,Size:%08x\n",A0,size);
}

void memptrunlock(){
	stackptr(ptr);
	if(abstractunlock(ptr))D0 = errNone;//a handle can also be unlocked as a pointer
	else D0 = memErrInvalidParam;//maybe memErrChunkNotLocked
}

void memptrrecoverhandle(){
	stackptr(ptr);
	A0 = ptr;
}

void memptrheapid(){
	stackptr(testptr);

	if(testptr >= HEAP && testptr <= HEAPEND)D0 = 0;/*dynamic heap*/
	else if(testptr >= SAVEDATA && testptr <= SAVEDATAEND)D0 = 1;/*storage heap*/
	else if(testptr >= dyn_start && testptr < lcd_start)D0 = 1;/*storage heap*/
	else palmabrt();//hack /*unknown heap*/
}



void memhandlenew(){
	stacklong(size);
	if(size > 0xFFFF)palmabrt();//hack
	A0 = getfreeheaphandle(size);
	dbgprintf("A0:%08x,Size:%08x\n",A0,size);
}

void memhandlefree(){
	stackptr(handle);
	dbgprintf("Handle:%08x\n",handle);
	if(freememaddr(handle,true))D0 = errNone;
	else D0 = memErrInvalidParam;
}

void memhandlelock(){
	stackptr(handle);
	//dbgprintf("Handle:%08x\n",handle);
	if(lockmemaddr(handle,true)){
		A0 = handle;
	}else{
		A0 = nullptr_68k;
		palmabrt();
	}
}

void memhandleunlock(){
	stackptr(handle);
	//dbgprintf("Handle:%08x\n",handle);
	if(unlockmemaddr(handle,true))D0 = errNone;
	else D0 = memErrInvalidParam;//maybe memErrChunkNotLocked
}

void memhandlesize(){
	stackptr(handle);
	D0 = getsizememaddr(handle,true);//hack fix size of app resource handles
	//dbgprintf("Handle:%08x,Size:%08x\n",handle,D0);
}



TEMPHACK
void memchunknew(){
	stackword(heapid);
	stacklong(size);
	stackword(attr);//flags for allocation //got 0x1245 once

	offset_68k chunk;
	bool prelock = (attr & memNewChunkFlagPreLock);
	bool limitsize = !(attr & memNewChunkFlagAllowLarge);

	//cant allocate more than 64k
	if(size > 0xFFFF && limitsize)palmabrt();//hack

	//invalid bit(+s) is set
	//if(attr & ~0x0F00)palmabrt();//hack

	//cant currently set where to get the memory from
	if(attr & (memNewChunkFlagAtStart | memNewChunkFlagAtEnd))palmabrt();//hack

	if(attr & memNewChunkFlagNonMovable){
		//cant lock nonmovable chunk
		if(prelock)palmabrt();//hack
		chunk = getfreeheap(size);
	}else{
		chunk = getfreeheaphandle(size);
		if(prelock)lockmemaddr(chunk,true);
	}


	A0 = chunk;
}

//system use only (apps ignore it though)
void memchunkfree(){
	stackptr(chunk);
	dbgprintf("Chunk:%08x\n",chunk);
	if(abstractfree(chunk))D0 = errNone;
	else D0 = memErrInvalidParam;
}

TEMPHACK
void memheapfreebytes(){
	stackword(heapid);//heapid 0=dynamic(application ram),1=storage,2=rom
	stackptr(free);//uint32_t
	stackptr(max);//uint32_t

	dbgprintf("HeapNum:%d\n",heapid);

	switch(heapid){
		case 0://dynamic
			putlongifvptr(free,avheapmem());
			put_long(max,avlinearheapmem());
			break;
		case 1://storage
			TEMPHACK;
			//unknown
			//(must represent undefined quantity of memory without
			//always returning the same value or the value being random?)
			putlongifvptr(free,0x2000000);
			put_long(max,0xFFFF);
			break;
		case 2://rom
			putlongifvptr(free,0);
			put_long(max,0);
			break;
	}
	D0 = errNone;//palm os always sets this to errNone
}

void memcardinfo(){
	stackword(cardno);//uint16_t
	stackptr(cardname);//string char[32]
	stackptr(manufname);//string char[32]
	stackptr(version);//uint16_t
	stackptr(crdate);//uint32_t
	stackptr(romsize);//uint32_t
	stackptr(ramsize);//uint32_t
	stackptr(freebytes);//uint32_t

	if(cardno != 0)palmabrt();//hack //only one card
	//(This does not reference sd,cf,usb otg or other memory
	//expansions it is palms reference to chips on the motherboard
	//or RAM carts(Palm Pilot/1000/5000/Personal/Professional/iii/iiix))

	dbgprintf("Cardnum:%d,cardname:%08x,cardmanuf:%08x,version:%d,Date:%08x,RomSize:%08x,RamSize:%08x,FreeBytes:%08x\n",
		   cardno,cardname,manufname,version,crdate,romsize,ramsize,freebytes);

	if(cardname)writestring(cardname,"4GB Duck Waddler",32);//force size to 32
	if(manufname)writestring(manufname,"The Communist Rabbit Soviet",32);//force size to 32

	putwordifvptr(version,3);
	putlongifvptr(crdate,0xBF3E786B);//2005 sept 2 21:45:15
	putlongifvptr(romsize,0xFE68);//fake rom
	putlongifvptr(ramsize,0x4000000);//fix hardcoding//hack //64MB
	putlongifvptr(freebytes,0x1683800);//fix hardcoding//hack

	D0 = errNone;
}

void memheapid(){
	stackword(cardno);//only one card
	stackword(heapindex);
	D0 = heapindex;
}

void memheapdynamic(){
	stackword(heapid);
	if(heapid == 0)D0 = 1;
	else D0 = 0;
}

TEMPHACK
void memheapcompact(){
	stackword(heapid);//dynamic/0 or storage/1

	TEMPHACK;
	//may implement heap compacting but
	//since this device dosent have memory constraints
	//all memhandle == memptr so the heap cant be compacted

	D0 = errNone;//palm os always returns errNone
}



//prefs
void prefgetapppreferencesv10(){
	uint32_t appid = poplonglink();
	uint16_t version = popwordlink();
	stackptr(prefptr);
	uint16_t size = popwordlink();

	//dbgprintf("Appid:%s\n",stringfromtype(appid).c_str());
	TEMPHACK
	offset_68k resourceptr = getresource(0,130,'pref');

	dbgprintf("Resptr:%08x,Prefptr:%08x,Size:%d\n",resourceptr,prefptr,size);

	if(resourceptr)memcpy68k(prefptr,resourceptr,size);

	D0 = errNone;
}

TEMPHACK
void prefsetapppreferences(){
	stacklong(creator);
	stackword(id);
	stackword(version);//signed word
	stackptr(prefs);
	stackword(prefssize);
	stackbool(saved);

	TEMPHACK;
	//do something!

	//no return value
}

void prefgetapppreferences(){
	stacklong(creator);
	stackword(id);
	stackptr(prefptr);//buffer to hold prefs
	stackptr(sizeptr);//ptr to size in uint16_t format
	stackbool(saved);

	uint16_t size = get_word(sizeptr);

	uint32_t melsk = belong(creator);
	dbgprintf("Creator:%.4s,Id:%d,prefptr:%08x,szptr:%08x,size:%04x\n",(char*)&melsk,id,prefptr,sizeptr,size);

	offset_68k resourceptr = getresource(curapp,id,'pref');

	dbgprintf("Resptr:%08x,Prefptr:%08x,Size:%d\n",resourceptr,prefptr,size);

	if(resourceptr)memcpy68k(prefptr,resourceptr,size);


	D0 = noPreferenceFound;
}

void prefgetpreferences(){
	stackptr(sysprefbuffptr);

	dbgprintf("sysprefbuff:%08x\n",sysprefbuffptr);

	put_word(sysprefbuffptr,0x78);//version
	put_byte(sysprefbuffptr + 2,4);//country(4 is canada)
	put_byte(sysprefbuffptr + 3,0);//dateformat(0 is mm/dd/yyyy)
	put_byte(sysprefbuffptr + 4,0);//dateformat(0 is mm/dd/yyyy)
	put_byte(sysprefbuffptr + 5,1);//week start day (0x1 is monday)
	put_byte(sysprefbuffptr + 6,1);//timeformat(1 is h:m s)

	TEMPHACK
	put_byte(sysprefbuffptr + 7,0);//numberformat

	put_byte(sysprefbuffptr + 8,2);//auto off min(2)
	put_byte(sysprefbuffptr + 9,0);//syssound on
	put_byte(sysprefbuffptr + 10,0);//gamesound on
	put_byte(sysprefbuffptr + 11,0);//alarmsound on
	put_byte(sysprefbuffptr + 12,1);//hide secret records
	put_byte(sysprefbuffptr + 13,0);//device locked
	put_byte(sysprefbuffptr + 14,0);//local sync needs code
	put_byte(sysprefbuffptr + 15,0);//remote sync needs code

	TEMPHACK
	put_word(sysprefbuffptr + 16,0);//pref flags

	put_byte(sysprefbuffptr + 18,0);//battery type(2 is LIion)
	put_byte(sysprefbuffptr + 19,0);//reserved

	TEMPHACK
	put_long(sysprefbuffptr + 20,0);//minutes west of gmt



	TEMPHACK
	//no return value
}

void prefgetpreference(){
	stackbyte(pref);
	switch(pref){
		case prefGameSoundVolume:
			D0 = 10;//hack
			return;
	}
	dbgprintf("prefnum:%d\n",pref);
	D0 = 0;
}



//init DataManager
void init_filesystem_driver(){
	dmlasterror = errNone;
}
