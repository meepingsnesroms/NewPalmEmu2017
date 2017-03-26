#ifndef EVENTQUEUE
#define EVENTQUEUE

#include "m68k.h"
#include <vector>
#include <chrono> //for palmTicks macro


//eventtype size = header size + 4 longs


//events
#define  evtWaitForever    -1
#define  evtNoWait          0

enum{
	nilEvent = 0,				// system level
	penDownEvent,				// system level
	penUpEvent,					// system level
	penMoveEvent,				// system level
	keyDownEvent,				// system level
	winEnterEvent,				// system level
	winExitEvent,				// system level
	ctlEnterEvent,
	ctlExitEvent,
	ctlSelectEvent,
	ctlRepeatEvent,
	lstEnterEvent,
	lstSelectEvent,
	lstExitEvent,
	popSelectEvent,
	fldEnterEvent,
	fldHeightChangedEvent,
	fldChangedEvent,
	tblEnterEvent,
	tblSelectEvent,
	daySelectEvent,
	menuEvent,
	appStopEvent = 22,			// system level
	frmLoadEvent,
	frmOpenEvent,
	frmGotoEvent,
	frmUpdateEvent,
	frmSaveEvent,
	frmCloseEvent,
	frmTitleEnterEvent,
	frmTitleSelectEvent,
	tblExitEvent,
	sclEnterEvent,
	sclExitEvent,
	sclRepeatEvent,
	tsmConfirmEvent = 35,		// system level
	tsmFepButtonEvent,			// system level
	tsmFepModeEvent,				// system level
//DOLATER - peter: remove this:	frmTitleChangedEvent,		// system level
	attnIndicatorEnterEvent,	// for attention manager's indicator
	attnIndicatorSelectEvent,	// for attention manager's indicator

	// add future UI level events in this numeric space
	// to save room for new system level events
	menuCmdBarOpenEvent = 0x0800,
	menuOpenEvent,
	menuCloseEvent,
	frmGadgetEnterEvent,
	frmGadgetMiscEvent,

	// <chg 2-25-98 RM> Equates added for library events
	firstINetLibEvent = 0x1000,
	firstWebLibEvent = 0x1100,

	//palm os 5 only
	keyUpEvent 			= 0x4000,
	keyHoldEvent 		= 0x4001,
	frmObjectFocusTakeEvent 	= 0x4002,
	frmObjectFocusLostEvent 	= 0x4003,
	firstLicenseeEvent	= 0x5000,
	lastLicenseeEvent	= 0x5FFF,
	//palm os 5 only

	// <chg 10/9/98 SCL> Changed firstUserEvent from 32767 (0x7FFF) to 0x6000
	// Enums are signed ints, so 32767 technically only allowed for ONE event.
	firstUserEvent = 0x6000,
	lastUserEvent  = 0x7FFF
};

#define evtDataOffset 8

#define TICKSPERSECOND 100//00
//#define palmTicks(x) std::chrono::milliseconds((x) * 10)
#define palmTicks(x) std::chrono::milliseconds((x))

typedef struct{
	UWORD type = 0;
	UBYTE pendown = 0;
	UBYTE tapcount = 0;
	UWORD screenx = 0;
	UWORD screeny = 0;
	std::vector<ULONG> data;
	ULONG id = 0;//not officialy part of the event struct(used by sysTrapEvtAddUniqueEventToQueue)
}osevent;


//event functions
osevent getoldestevent();
void addnewevent(const osevent& ev);
bool hasevent();
void wipeeventqueue();

//apis
void evtgetevent();
void evtresetautoofftimer();
void evtenqueuekey();
void evtaddeventtoqueue();
void evtadduniqueeventtoqueue();

void syshandleevent();

#endif // EVENTQUEUE

