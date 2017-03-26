#ifndef DATAMGR
#define DATAMGR

#include "m68k.h"

#define	dmHdrAttrResDB				0x0001
#define dmHdrAttrReadOnly			0x0002
#define	dmHdrAttrAppInfoDirty		0x0004
#define	dmHdrAttrBackup				0x0008
#define	dmHdrAttrOKToInstallNewer 	0x0010
#define	dmHdrAttrResetAfterInstall	0x0020
#define	dmHdrAttrCopyPrevention		0x0040
#define	dmHdrAttrStream				0x0080
#define	dmHdrAttrHidden				0x0100
#define	dmHdrAttrLaunchableData		0x0200
#define	dmHdrAttrOpen				0x8000

#define	dmModeReadOnly			0x0001		// read  access
#define	dmModeWrite				0x0002		// write access
#define	dmModeReadWrite			0x0003		// read & write access
#define	dmModeLeaveOpen			0x0004		// leave open when app quits
#define	dmModeExclusive			0x0008		// don't let anyone else open it
#define	dmModeShowSecret		0x0010		// force show of secret records
//custom,define readable bit
#define	dmModeReadable			0x0001

#define	dmRecAttrDelete			0x80	// delete this record next sync
#define	dmRecAttrDirty			0x40	// archive this record next sync
#define	dmRecAttrBusy			0x20	// record currently in use
#define	dmRecAttrSecret			0x10	// "secret" record - password protected

#define dmDBNameLength 		32
#define dmMaxRecordIndex 	0xffff

#define dmMaxCardNo			3
#define dmMaxFileName 		255
#define dmCardNoFolderRoot  ".\\"
#define dmApplType			'appl'
#define dmDataType			'data'


//custom,used to reference index in app vector
#define dmOpenRefOffset 0x5550

extern int recentresdb,recentoverlay;

void forgeuniqueids();

//database
void dmopendatabasebytypecreator();
void dmcreatedatabase();
void dmnewrecord();
void dmnewresource();
void dmqueryrecord();
void dmnewhandle();
void dmwrite();
void dmreleaserecord();
void dmremoverecord();
void dmgetrecord();
void dmattachrecord();
void dmopendatabaseinfo();
void dmget1resource();
void dmgetresource();
void dmreleaseresource();
void dmgetnextdatabasebytypecreator();
void dmnextopenresdatabase();
void dmdatabaseinfo();
void dmsetdatabaseinfo();
void dmopendatabase();
void dmclosedatabase();
void dmnumrecords();
void dmfindresource();
void dmfinddatabase();
void dmfindrecordbyid();
void dmgetresourceindex();
void dmwritecheck();
void dmsearchresource();
void dmresetrecordstates();


//memory
void memsemaphorereserve();
void memsemaphorerelease();
void memmoveAPI();
void memsetAPI();

void memptrnew();
void memptrunlock();
void memptrrecoverhandle();
void memptrheapid();

void memhandlenew();
void memhandlefree();
void memhandlelock();
void memhandleunlock();
void memhandlesize();

void memchunknew();
void memchunkfree();
void memheapfreebytes();
void memcardinfo();
void memheapid();
void memheapdynamic();
void memheapcompact();


//strings
void strcopyAPI();
void strlenAPI();
void strncompare();
void strncopy();
void strcompare();
void strchr();
void stritoa();


//preferences
void prefgetapppreferencesv10();
void prefsetapppreferences();
void prefgetapppreferences();
void prefgetpreferences();
void prefgetpreference();



//init DataManager
void initfilesystemdriver();

#endif // DATAMGR

