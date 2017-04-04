#include "palmapi.h"
#include "m68k.h"
#include "minifunc.h"
#include "palmwrapper.h"
#include "sdfilesystem.h"
#include "dataexchange.h"
#include "errorcodes.h"

//VFSVolumeEnumerate
static void volumeenumerate(){
	stackptr(volrefnumptr);//uint16_t ptr
	stackptr(voliteratorptr);//uint32_t ptr

	if(get_long(voliteratorptr) == vfsIteratorStart){
		//the first index has a sd card,all others are empty
		put_word(volrefnumptr,1);//0 means invalid volume number
		put_long(voliteratorptr,vfsIteratorStop);
		D0 = errNone;
	}
	else{
		//not sdcard one,its invalid
		dbgprintf("Invalid Vol:%d\n",get_long(voliteratorptr));
		put_word(volrefnumptr,vfsInvalidVolRef);
		put_long(voliteratorptr,vfsIteratorStop);
		D0 = sysErrParamErr;
	}
}

//VFSDirCreate
static void dircreate(){

}

void filesystemdispatch(){
	//This trap is just a switch statement!

	SELECTOR{
		SELAPI(vfsTrapVolumeEnumerate,volumeenumerate());
		/*
		SELAPI(HDSelectorBmpCreateBitmapV3,bmpcreatebitmapv3());
		SELAPI(HDSelectorBmpGetDensity,bmpgetdensity());
		SELAPI(HDSelectorWinGetCoordinateSystem,wingetcoordinatesystem());
		SELAPI(HDSelectorWinSetCoordinateSystem,winsetcoordinatesystem());
		*/

		default:
			//invalid command
			dbgprintf("filesystem INV_CMD:%d\n",D2);
			palmabrt();//hack
			break;
	}
}
