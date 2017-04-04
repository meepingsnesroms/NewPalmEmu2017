#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "palmwrapper.h"

#include "palmapi.h"

#include "palmdatatypes.h"
#include "eventqueue.h"
#include "sdfilesystem.h"
#include "dataexchange.h"
#include "palmdefines.h"
#include "armv5te.h"

//new list
#include "m68k.h"
#include "resourcelocator.h"
#include "zodiacapi.h"
#include "datamanager.h"
#include "displaydriver.h"
#include "audiodriver.h"
#include "floatlib.h"
#include "stdlib68k.h"
#include "palmlibc.h"

//rom api calling
#include "romutils.h"

//debug
#include "trapnumtoname.h"

//used by FtrGet() api to determine devices hardware, also used for some licence tricks along with FtrSet();
static std::vector<feature> featuretable;

//this is the callback list for the 68k rom
static offset_68k api_entrypoints[0x1000];


void dump_api_list_from_addr(uint32_t offset){
	for(uint32_t current_api = 0;current_api < 0x1000;current_api++){
		api_entrypoints[current_api] = get_long(offset + (current_api * 4));
		dbgprintf("Loaded API from ROM:%s,0x%04x,Addr:0x%08x\n", lookup_trap(0xA000 | current_api), 0xA000 | current_api, api_entrypoints[current_api]);
	}
}

void make_api_list_from_rom(offset_68k rom_SysGetTrapAddress){
	//dump_api_list_from_addr(0x10010122);//this is a hack for now
	//dump_api_list_from_addr(0x10010230);//this is a hack for now
	for(uint32_t current_api = 0;current_api < 0x1000;current_api++){
		CPU_pushwordstack(current_api);

		//call SysGetTrapAddress for each api and log the result
		//0x00011056 is arbitrary but looks official since it is close to the reset vector
		CPU_68kfunction(rom_SysGetTrapAddress, 0x00011056/*address to pretend to call from*/);

		if(A0 == nullptr_68k)dbgprintf("ROM Does not contain API:%s,0x%04x\n", lookup_trap(current_api), current_api);
		else dbgprintf("Loaded API from ROM:%s,0x%04x\n", lookup_trap(current_api), current_api);

		api_entrypoints[current_api] = A0;
		CPU_popwordstack();
	}
}

//returns if the api may have failed, since it is only testing the output you may get many incorrect answers
static int call_rom_api(uint16_t apinum){
	if(!rom_active())return 2;//guaranteed fail, cant call rom that does not exist

	dbgprintf("Using API from ROM:%s,0x%04x\n", lookup_trap(apinum),apinum);

	//no arguments need to be added or removed from the stack since this
	//function is only a passthrough to the ROMs version of the api

	//args are "function to call" and "address to pretend to call from"
	CPU_68kfunction(api_entrypoints[apinum & 0xFFF], MC68000_getpc());

	if(D0 != 0)			 return 1;//may have failed
	if(A0 == nullptr_68k)return 1;//may have failed

	return 0;//did not fail
}

void reset_and_load_default_features(){
	feature newftr;
	newftr.read_only = true;


	//wipe feature table
	featuretable.clear();


	//sysFileCSystem
	newftr.creator = sysFileCSystem;

	newftr.id = sysFtrNumROMVersion;
	newftr.value = 0x05493028;//V5.49028 (Palm TX version of palm os)
	featuretable.push_back(newftr);

	newftr.id = sysFtrNumProcessorID;
	newftr.value = sysFtrNumProcessorXscale;
	featuretable.push_back(newftr);

	newftr.id = sysFtrNumOEMDeviceID;
	newftr.value = 'D050';
	featuretable.push_back(newftr);

	newftr.id = sysFtrNumOEMHALID;
	newftr.value = 'P050';
	featuretable.push_back(newftr);

	newftr.id = sysFtrNumWinVersion;
	newftr.value = 5;//unsure of value
	featuretable.push_back(newftr);

	newftr.id = sysFtrNumHwrMiscFlags;
	newftr.value = hwrMiscFlagHasSWContrast |
	        hwrMiscFlagHasCradleDetect |
	        hwrMiscFlagNoRTCBug |
	        hwrMiscFlagHasMbdIrDA |
	        hwrMiscFlagHasBacklight |
	        0xF000/*all hard keys*/;
	featuretable.push_back(newftr);

	newftr.id = sysFtrNumOEMCompanyID;
	newftr.value = 'Palm';
	featuretable.push_back(newftr);


	//navFtrCreator
	newftr.creator = navFtrCreator;

	newftr.id = navFtrVersion;
	newftr.value = navVersion;
	featuretable.push_back(newftr);


	//pinCreator

	newftr.creator = pinCreator;

	newftr.id = pinFtrAPIVersion;
	newftr.value = pinAPIVersion1_1;
	featuretable.push_back(newftr);


	//twFtrCreator //tapwave zodiac identifier

	newftr.creator = twFtrCreator;

	newftr.id = twFtrAPIVersion;
	newftr.value = TAPWAVE_API_VERSION;
	featuretable.push_back(newftr);

	newftr.id = twFtrAPIGlue;
	newftr.value = TAPWAVE_API_VERSION;
	featuretable.push_back(newftr);

}

void ftrget(){
	stacklong(creator);
	stackword(ftrnum);
	stackptr(retval);//write feature value to this address, uint32_t

	size_t tblsize = featuretable.size();
	for(size_t count = 0;count < tblsize;count++){
		if(featuretable[count].creator == creator && featuretable[count].id == ftrnum){
			put_long(retval, featuretable[count].value);
			D0 = errNone;
			return;
		}
	}

	/*
	uint32_t dys = belong(creator);
	if(!ftrexists)
		dbgprintf("Creator:%.4s,Ftrnum:%d,Exists:%s\n", (char*)&dys, ftrnum, (ftrexists ? "True" : "False"));
	*/

	D0 = ftrErrNoSuchFeature;
}

void ftrset(){
	stacklong(creator);
	stackword(ftrnum);
	stacklong(value);

	//dbgprintf("FTRSET: Creator:%.4s,Ftrnum:%d,Value:%d\n", (char*)&creator, ftrnum,value);

	size_t tblsize = featuretable.size();
	for(size_t count = 0;count < tblsize;count++){
		if(featuretable[count].creator == creator && featuretable[count].id == ftrnum){
			if(!featuretable[count].read_only){
				featuretable[count].value = value;
			}
			D0 = errNone;
			return;
		}
	}

	feature newftr;
	newftr.creator = creator;
	newftr.id = ftrnum;
	newftr.value = value;
	newftr.read_only = false;
	featuretable.push_back(newftr);

	D0 = errNone;
}

void keysetmask(){
	stacklong(newmask);
	D0 = keymask;
	keymask = newmask;
}

TEMPHACK
void keycurrentstate(){
	D0 = BTNTBL;
	TEMPHACK;
	//add key mask if needed
}

void systaskdelay(){
	stacklong(uticks);
	int32_t ticks = (int32_t)uticks;

	if(ticks < 0)palmabrt();//hack //cant wait less than 0 ticks
	//palmabrt();

	if(ticks > 0)std::this_thread::sleep_for(palmTicks(ticks));
	D0 = errNone;
}

void syslibfind(){
	stackptr(nameptr);
	stackptr(libnum);//write this value

	dbgprintf("Find lib:%s,Addr:%08x\n",readstring(nameptr).c_str(),nameptr);

	//void *meepcheek = get_real_address(nameptr);

	TEMPHACK;//find lib

	//D0 = errNone;
	D0 = sysErrLibNotFound;
}

TEMPHACK
void syslibload(){
	stacklong(type);
	stacklong(creator);
	stackptr(result);//write lib start here

	dbgprintf("Type:%.4s,Creator:%.4s\n",(char*)&type,(char*)&creator);

	int lib = numfromtypecreator(0,type,creator);

	if(lib != -1){
		TEMPHACK;//loadlib
		D0 = errNone;
	}
	else{
		put_word(result,sysInvalidRefNum);
		D0 = sysErrLibNotFound;//may be fatal error
	}
}

void sysappstartup(){
	stackptr(appinfoptr);
	stackptr(prevglobalsptr);
	stackptr(appglobalsptr);
	//^^ are pointers to pointers
	put_long(appinfoptr,appcall);
	//put_long(prevglobalsptr,0xFFFFFFFD);//cant be at odd address
	put_long(prevglobalsptr,0x878745FD);//hack/test for platypus
	put_long(appglobalsptr,apps[curapp].thisglobals);

	//there might be more

	D0 = errNone;
}

void sysappexit(){
	stackptr(sysappinfoptr);
	stackptr(prevgblptr);
	stackptr(gblptr);


	dbgprintf("Appinfptr:%08x,Prevgblptr:%08x,Gblptr:%08x\n",sysappinfoptr,prevgblptr,gblptr);
	//palmabrt();//hack

	D0 = errNone;
}

void syscurappdatabase(){
	stackptr(cardnoptr);//uint16_t
	stackptr(localidptr);//uint32_t

	put_word(cardnoptr,0);//app storage flash memory
	put_long(localidptr,curapp + dmOpenRefOffset);

	D0 = errNone;
}

//there are 100 ticks per second on a palm os device
void systickspersecond(){
	D0 = TICKSPERSECOND;
}

//from palm os password cracker,this is the original rng from palm os converted back to c++
void sysrandom(){
	stacklong(newseed);

	static uint32_t seed;

	if(newseed != 0)seed = newseed;
	seed = (seed * 22695477) + 1;
	D0 = ((seed >> 16) & 0x7fff);
}

void syscopystringresource(){
	stackptr(chrptr);
	stackword(id);
	offset_68k resptr = getappresource(id,'tSTR');
	size_t_68k strsize = strlen68k(resptr) + 1;//+1 to count the null terminator
	memcpy68k(chrptr,resptr,strsize);
	//no return value
}

TEMPHACK
//params are ignored
void sysgetappinfo(){
	stackptr(uiappptr);//pointer to SysAppInfoPtr (pointer to pointer)
	stackptr(actioncodeappptr);//pointer to SysAppInfoPtr (pointer to pointer)

	TEMPHACK;
	//dont know what to do
	//(just returning the sysappinfo of the running app)
	A0 = appcall;
}

void sysnotifyregister(){
	stackword(cardno);//dummy
	stacklong(localid);//dmopenref format
	stacklong(notifytype);
	stackptr(callback);
	stackbyte(upriority);
	stackptr(userdataptr);
	int8_t priority = (int8_t)upriority;
	localid -= dmOpenRefOffset;

	if(cardno != 0)palmabrt();//hack

	dbgprintf("NotificationType:%.4s,ASnum:%08x,DBnum:%d,Callback:%08x\n",(char*)&notifytype,notifytype,localid,callback);

	switch(notifytype){
		//safe to ignore
		case sysNotifySyncFinishEvent:
		case sysNotifyAppLaunchingEvent:
			break;

		//unknown
		default:
			palmabrt();//hack
			break;
	}

	D0 = errNone;
}


void timgetticks(){

	timer_lock.lock();

	std::chrono::high_resolution_clock::duration timepassed = std::chrono::high_resolution_clock::now() - starttime;
	uint32_t fulltickspassed = (uint32_t)(timepassed / palmTicks(1));//how many full ticks have passed since the last call to this function
	float partialtickspassed = (timepassed / palmTicks(1)) - fulltickspassed;
	fullticks   += fulltickspassed;
	partialticks += partialtickspassed;

	if(partialticks > 1.0){
		fullticks   += (uint32_t)partialticks;//reclaim any leftover time that previosly did not exceed 1 tick
		partialticks -= (uint32_t)partialticks;//remove any full ticks from the partial tick counter
	}

	timer_lock.unlock();

	D0 = fullticks;
}

void timgetseconds(){
	time_t now = time(nullptr);
	D0 = now + 2082844800;//unix to palm os timestamp offset (seconds from 1904-1970)
}

void dlkgetsyncinfo(){
	offset_68k ssdateptr = poplonglink();
	offset_68k lastsdateptr = poplonglink();
	offset_68k syncstateptr = poplonglink();
	offset_68k usernameptr = poplonglink();
	offset_68k logptr = poplonglink();
	offset_68k loglengthptr = poplonglink();

	if(ssdateptr){
		dbgprintf("Why syncdate?\n");
	}
	if(lastsdateptr){
		dbgprintf("Why llamaptr?\n");
	}
	putbyteifvptr(syncstateptr,dlkSyncStateNeverSynced);
	if(usernameptr){
		writestring(usernameptr,username);
	}
	if(logptr){
		dbgprintf("Why logptr?\n");
	}
	putlongifvptr(loglengthptr,0);
}

void locgetnumberseparators(){
	stackbyte(localization);//unused
	stackptr(thousandsep);
	stackptr(decimalsep);

	put_byte(thousandsep,',');
	put_byte(decimalsep,'.');

	//no return value
}

void errexceptionlist(){
	A0 = appexceptionlist;
}

bool hastextclipbank = true;//use dynalloc chunk for clipboard
offset_68k textclipbank = 0;
void clipboardgetitem(){
	stackbyte(cliptype);
	stackptr(lengthptr);//uint16_t length in bytes of clipboard item

	switch(cliptype){
		case clipboardText:{
				if(!hastextclipbank)textclipbank = getnewlinearchunks(1) << 16;//64k clipboard
				std::string curclip = emu_getclipboard();
				put_word(lengthptr,curclip.size());
				writestring(textclipbank,curclip);
				A0 = textclipbank;
				return;
			}
			break;
		case clipboardBitmap:
			palmabrt();//hack
			break;
		default:
			palmabrt();//hack
			break;
	}

}


/*
typedef struct _tagEmulState {
	UInt32	unknown;
	UInt32	d[8];		// 0x04
	UInt32	a[7];		// 0x24
	UInt32	usp;		// 0x40
	UInt32	pc;			// 0x44
	UInt16	sr;
	UInt16	pad;
	UInt32	more[33];
} EmulStateType, *EmulStateRef;
*/

//switch to ARM instruction set
bool hasemulstate = true;
offset_68k emulstate;
void pcenativecall(){
	stackptr(callptr);
	stackptr(datablock);

	dbgprintf("Trying to run arm stuff.\n");

	//palmabrt();//hack

	//stackptr(data1);
	//stackptr(data2);
	//dbgprintf("RandomData1:%08x,RandomData2:%08x\n",data1,data2);

	/*
	//must be an api
	if(callptr > 0x1000){

	}
	*/

	dbgprintf("Call:%08x,DataBlock:%08x\n",callptr,datablock);

	//printregs();
	//palmabrt();//hack

	//r0-r3 are used as function arguments in arm (with aapcs)

	/*
	pushstackARM(emulstate);
	pushstackARM(datablock);
	pushstackARM(CALL68KFUNC);
	*/

	setregARM(0,emulstate);
	setregARM(1,datablock);
	setregARM(2,CALL68KFUNC);


	callARM(callptr);

	//arm passes and returns values in regesters not on the stack
	//offset_68k armreturn = popstackARM();
	offset_68k armreturn = getregARM(0);//arm r0

	//Palm OS API Reference
	/*This value is placed in both the A0 and D0
	 * registers in the emulated 68k CPU,
	 * allowing PceNativeCall to support both pointer
	 * and immediate return value conventions.*/
	D0 = armreturn;
	A0 = armreturn;
}


#include "bsod.h"

//apis (and call to ARM)
bool emulateapi(uint16_t api){

	if(currentactivewindow == nullptr_68k)palmabrt();//hack


	//to catch errors without printing every api call
	char fakestring[100];//100 is way overestimateing
	sprintf(fakestring,"Trap At:%#010x,Api:%s,0x%04x\n",MC68000_getpc(),lookup_trap(api),api);
	lasttrap = fakestring;
	//*/

	if(api != sysTrapMemMove && api != sysTrapMemSet && api != sysTrapDmWrite && api != sysTrapFlpEmDispatch && api != sysTrapTimGetTicks)dbgprintf("Trap At:%#010x,Api:%s,0x%04x\n",MC68000_getpc(),lookup_trap(api),api);
	//dbgprintf("Trap At:%#010x,Api:%s,0x%04x\n",MC68000_getpc(),lookup_trap(api),api);

	LINK(SP);//No longer in every api call
	switch(api){
		/*
		//things apps should not even be calling
		case sysTrapSysSetTrapAddress:
		case sysTrapSysGetTrapAddress:
		case sysTrapDbgSerDrvReadChar:
			break;
		*/
		case sysTrapErrDisplayFileLineMsg:{
				stackptr(fname);
				stackword(line);
				stackptr(errstr);
				dbgprintf("Palm says:%s",readstring(fname).c_str());
				dbgprintf(" %d ",line);
				dbgprintf("%s\n",readstring(errstr).c_str());
			}
			return true;

		case sysTrapStrPrintF:{
				stackptr(outstring);
				stackptr(formatstring);
				stackptr(args);
				dbgprintf("OutPtr:%08x,InPtr:%08x,ArgPtr:%08x\n",outstring,formatstring,args);
				std::string str = readstring(formatstring);
				dbgprintf("Start:%s,ArgPtr:%08x\n",str.c_str(),args);
				writestring(outstring,str);
				//D0 = sprintf68k(outstring,formatstring,args);
				palmabrt();
			}
			return true;

		case sysTrapErrSetJump:

			TEMPHACK;
			//implement

			//stackregs(regs);

			//change in jump value
			//backup regs |D3-D7,PC,A2-A7|

			//D0 = returnvaluefromlongjump;
			return true;
		case sysTrapErrLongJump:

			palmabrt();//hack

			//stackregs(regs);

			//change in jump value
			//put regs back

			//no return value
			return true;

		//graphics apis
		API(sysTrapWinCreateOffscreenWindow,wincreateoffscreenwindow());
		API(sysTrapWinCreateBitmapWindow,wincreatebitmapwindow());
		API(sysTrapWinDeleteWindow,windeletewindow());
		API(sysTrapWinSetDrawWindow,winsetdrawwindow());
		API(sysTrapWinEraseRectangle,wineraserectangle());
		API(sysTrapWinDrawBitmap,windrawbitmap());
		API(sysTrapWinScreenMode,winscreenmode());
		API(sysTrapWinGetDrawWindow,wingetdrawwindow());
		API(sysTrapWinGetBitmap,wingetbitmap());
		API(sysTrapWinSetForeColor,winsetforecolor());
		API(sysTrapWinSetBackColor,winsetbackcolor());
		API(sysTrapWinSetTextColor,winsettextcolor());
		API(sysTrapWinDrawPixel,windrawpixel());
		API(sysTrapWinGetDisplayWindow,wingetdisplaywindow());
		API(sysTrapWinSetActiveWindow,winsetactivewindow());
		API(sysTrapWinSetClip,winsetclip());
		API(sysTrapWinDrawChars,windrawchars());
		API(sysTrapWinResetClip,winresetclip());
		API(sysTrapWinCopyRectangle,wincopyrectangle());
		API(sysTrapWinPalette,winpalette());
		API(sysTrapWinRGBToIndex,winrgbtoindex());
		API(sysTrapWinPushDrawState,winpushdrawstate());
		API(sysTrapWinPopDrawState,winpopdrawstate());
		API(sysTrapWinDrawRectangle,windrawrectangle());
		API(sysTrapWinDrawRectangleFrame,windrawrectangleframe());
		API(sysTrapWinScreenLock,winscreenlock());
		API(sysTrapWinScreenUnlock,winscreenunlock());
		API(sysTrapWinGetDisplayExtent,wingetdisplayextent());
		API(sysTrapWinEraseWindow,winerasewindow());
		API(sysTrapWinDrawLine,windrawline());
		API(sysTrapWinErasePixel,winerasepixel());
		API(sysTrapWinPaintBitmap,winpaintbitmap());

		//uicolor
		API(sysTrapUIColorGetTableEntryIndex,uicolorgettableentryindex());
		API(sysTrapUIColorGetTableEntryRGB,uicolorgettableentryrgb());
		API(sysTrapUIColorSetTableEntry,uicolortablesettableentry());

		//field
		API(sysTrapFldSetUsable,fldsetuseable());
		API(sysTrapFldEraseField,flderasefield());
		API(sysTrapFldSetTextPtr,fldsettextptr());
		API(sysTrapFldSetTextHandle,fldsettexthandle());
		API(sysTrapFldDrawField,flddrawfield());
		API(sysTrapFldGetTextPtr,fldgettextptr());
		API(sysTrapFldGetTextHandle,fldgettexthandle());

		//controls
		API(sysTrapCtlSetUsable,ctlsetusable());

		//bitmaps
		API(sysTrapBmpGetBits,bmpgetbits());
		API(sysTrapBmpBitsSize,bmpbitssize());
		API(sysTrapBmpCreate,bmpcreate());
		API(sysTrapBmpGetDimensions,bmpgetdimensions());

		//font
		API(sysTrapFntSetFont,fntsetfont());
		API(sysTrapFntCharsWidth,fntcharswidth());
		API(sysTrapFntGetFontPtr,fntgetfontptr());

		//forms
		API(sysTrapFrmAlert,frmalert());
		API(sysTrapFrmCustomAlert,frmcustomalert());
		API(sysTrapFrmGotoForm,frmgotoform());
		API(sysTrapFrmGetFormPtr,frmgetformptr());
		API(sysTrapFrmGetWindowHandle,frmgetwindowhandle());
		API(sysTrapFrmDispatchEvent,frmdispatchevent());
		API(sysTrapFrmInitForm,frminitform());
		API(sysTrapFrmDeleteForm,frmdeleteform());
		API(sysTrapFrmCloseAllForms,frmcloseallforms());
		API(sysTrapFrmSetActiveForm,frmsetactiveform());
		API(sysTrapFrmSetEventHandler,frmseteventhandler());
		API(sysTrapFrmGetActiveForm,frmgetactiveform());
		API(sysTrapFrmGetActiveFormID,frmgetactiveformid());
		API(sysTrapFrmSetTitle,frmsettitle());
		//put on display!!
		API(sysTrapFrmDrawForm,frmdrawform());
		API(sysTrapFrmGetObjectIndex,frmgetobjectindex());
		API(sysTrapFrmSetGadgetHandler,frmsetgadgethandler());
		API(sysTrapFrmGetObjectPtr,frmgetobjectptr());
		API(sysTrapFrmHideObject,frmhideobject());
		API(sysTrapFrmSetFocus,frmsetfocus());
		API(sysTrapFrmSetControlValue,frmsetcontrolvalue());

		//menu
		API(sysTrapMenuHandleEvent,menuhandleevent());

		//misc gui
		API(sysTrapRctSetRectangle,rctsetrectangle());
		API(sysTrapRctPtInRectangle,rctptinrectangle());

		//buttons
		API(sysTrapKeyCurrentState,keycurrentstate());
		API(sysTrapKeySetMask,keysetmask());
		API(sysTrapEvtGetPenBtnList,evtgetpenbuttonlist());

		//time
		API(sysTrapTimGetTicks,timgetticks());
		API(sysTrapTimGetSeconds,timgetseconds());
		API(sysTrapSysTicksPerSecond,systickspersecond());
		API(sysTrapSysTaskDelay,systaskdelay());

		//system
		API(sysTrapSysAppStartup,sysappstartup());
		API(sysTrapSysLibFind,syslibfind());
		API(sysTrapSysLibLoad,syslibload());
		API(sysTrapSysRandom,sysrandom());
		API(sysTrapSysHandleEvent,syshandleevent());
		API(sysTrapSysCopyStringResource,syscopystringresource());
		API(sysTrapSysCurAppDatabase,syscurappdatabase());
		API(sysTrapSysAppExit,sysappexit());//some games use this to kill the window manager
		API(sysTrapSysGetAppInfo,sysgetappinfo());
		API(sysTrapSysNotifyRegister,sysnotifyregister());

		//feature manager
		API(sysTrapFtrGet,ftrget());
		API(sysTrapFtrSet,ftrset());

		//event queue
		API(sysTrapEvtGetEvent,evtgetevent());
		API(sysTrapEvtResetAutoOffTimer,evtresetautoofftimer());
		API(sysTrapEvtEnqueueKey,evtenqueuekey());
		API(sysTrapEvtAddEventToQueue,evtaddeventtoqueue());
		API(sysTrapEvtAddUniqueEventToQueue,evtadduniqueeventtoqueue());

		//memory
		API(sysTrapMemSemaphoreReserve,memsemaphorereserve());
		API(sysTrapMemSemaphoreRelease,memsemaphorerelease());
		API(sysTrapMemMove,memmoveAPI());
		API(sysTrapMemSet,memsetAPI());
		//memory subset (pointers)
		API(sysTrapMemPtrNew,memptrnew());
		API(sysTrapMemPtrUnlock,memptrunlock());
		API(sysTrapMemPtrRecoverHandle,memptrrecoverhandle());
		API(sysTrapMemPtrHeapID,memptrheapid());
		//memory subset (handles)
		API(sysTrapMemHandleNew,memhandlenew());
		API(sysTrapMemHandleFree,memhandlefree());
		API(sysTrapMemHandleLock,memhandlelock());
		API(sysTrapMemHandleUnlock,memhandleunlock());
		API(sysTrapMemHandleSize,memhandlesize());
		//memory subset (chunks)
		API(sysTrapMemChunkNew,memchunknew());
		API(sysTrapMemChunkFree,memchunkfree());
		API(sysTrapMemHeapFreeBytes,memheapfreebytes());
		API(sysTrapMemCardInfo,memcardinfo());
		API(sysTrapMemNumCards,D0 = 1);//hack
		API(sysTrapMemNumHeaps,D0 = 3);//hack
		API(sysTrapMemNumRAMHeaps,D0 = 2);//hack //dynamic and storage
		API(sysTrapMemHeapID,memheapid());
		API(sysTrapMemHeapDynamic,memheapdynamic());
		API(sysTrapMemHeapCompact,memheapcompact());

		//preferences
		API(sysTrapPrefGetAppPreferencesV10,prefgetapppreferencesv10());
		API(sysTrapPrefSetAppPreferences,prefsetapppreferences());
		API(sysTrapPrefGetAppPreferences,prefgetapppreferences());
		API(sysTrapPrefGetPreferences,prefgetpreferences());
		API(sysTrapPrefGetPreference,prefgetpreference());

		//string
		API(sysTrapStrCopy,strcopyAPI());
		API(sysTrapStrLen,strlenAPI());
		API(sysTrapStrNCompare,strncompare());
		API(sysTrapStrNCopy,strncopy());
		API(sysTrapStrCompare,strcompare());
		API(sysTrapStrChr,strchr());
		API(sysTrapStrIToA,stritoa());

		//data manager
		//get
		API(sysTrapDmFindDatabase,dmfinddatabase());
		API(sysTrapDmFindRecordByID,dmfindrecordbyid());
		API(sysTrapDmGetNextDatabaseByTypeCreator,dmgetnextdatabasebytypecreator());
		API(sysTrapDmGetRecord,dmgetrecord());
		API(sysTrapDmGetResource,dmgetresource());
		API(sysTrapDmGet1Resource,dmget1resource());
		API(sysTrapDmGetResourceIndex,dmgetresourceindex());
		API(sysTrapDmFindResource,dmfindresource());
		API(sysTrapDmNextOpenResDatabase,dmnextopenresdatabase());
		API(sysTrapDmSearchResource,dmsearchresource());
		//create
		API(sysTrapDmCreateDatabase,dmcreatedatabase());
		API(sysTrapDmNewHandle,dmnewhandle());
		API(sysTrapDmNewRecord,dmnewrecord());
		API(sysTrapDmNewResource,dmnewresource());
		//modify
		API(sysTrapDmAttachRecord,dmattachrecord());
		API(sysTrapDmReleaseRecord,dmreleaserecord());
		API(sysTrapDmRemoveRecord,dmremoverecord());
		API(sysTrapDmSetDatabaseInfo,dmsetdatabaseinfo());
		API(sysTrapDmWrite,dmwrite());
		API(sysTrapDmWriteCheck,dmwritecheck());
		API(sysTrapDmResetRecordStates,dmresetrecordstates());
		//get current state
		API(sysTrapDmDatabaseInfo,dmdatabaseinfo());
		API(sysTrapDmOpenDatabaseInfo,dmopendatabaseinfo());
		API(sysTrapDmNumRecords,dmnumrecords());
		//open and close
		API(sysTrapDmOpenDatabase,dmopendatabase());
		API(sysTrapDmOpenDatabaseByTypeCreator,dmopendatabasebytypecreator());
		API(sysTrapDmCloseDatabase,dmclosedatabase());
		//misc
		API(sysTrapDmQueryRecord,dmqueryrecord());
		API(sysTrapDmReleaseResource,dmreleaseresource());

		//sound
		API(sysTrapSndGetDefaultVolume,sndgetdefaultvolume());
		API(sysTrapSndDoCmd,snddocmd());
		API(sysTrapSndStreamSetVolume,sndstreamsetvolume());

		//sysTrap****Dispatch (switch statement for real apis)
		//high density displays
		API(sysTrapHighDensityDispatch,highdensitydispatch());
		//floating point math
		API(sysTrapFlpDispatch,flpdispatch());//Float Library trap
		API(sysTrapFlpEmDispatch,flpemdispatch());//FPU emulator trap
		//other
		API(sysTrapPinsDispatch,pinsdispatch());

		//misc
		API(sysTrapHostControl,D0 = 0);
		API(sysTrapLocGetNumberSeparators,locgetnumberseparators());
		API(sysTrapErrExceptionList,errexceptionlist());
		API(sysTrapClipboardGetItem,clipboardgetitem());
		API(sysTrapDlkGetSyncInfo,dlkgetsyncinfo());

		//tapwave zodiac api
		API(sysTrapOEMDispatch2,tapwavedispatch());

		//switch to ARM instruction set
		API(sysTrapPceNativeCall,pcenativecall());

		//filesystem
		API(sysTrapFileSystemDispatch,filesystemdispatch());

		default:
			{
				//int rom_api_failed = call_rom_api(api);
				//if(rom_api_failed == 0)return false;
				//rom_api_failed == 1, could have failed but may be fine
				//rom_api_failed == 2, no rom present

				dbgprintf("Trap At:%#010x,Api:%s,0x%04x\n",MC68000_getpc(),lookup_trap(api),api);
				char meep[1000];
				sprintf(meep,"Trap At:%#010x,Api:%s,0x%04x",MC68000_getpc(),lookup_trap(api),api);
				std::string output = meep;
				showBSOD(output);
				palmabrt();
				return false;
			}

	}
	//0xA460 sound related,sysTrapSndPlayResource,sysTrapWinEraseWindow,sysTrapLstSetSelection
	//sysTrapSysStringByIndex,sysTrapFntGetFont,sysTrapFrmCopyLabel,sysTrapLstSetListChoices,
	//sysTrapFntCharHeight

	//(*apilist[api & 0xFFF])();
	//dbgprintf("Trap At:%#010x,Api:%s,0x%04x\n",MC68000_getpc(),lookup_trap(api),api);
	return false;
}
