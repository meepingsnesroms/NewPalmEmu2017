#include "eventqueue.h"
#include "displaydriver.h"
#include "dataexchange.h"

#include <mutex>
#include <queue>
#include <chrono>
#include <thread>

//new list
#include "palmdefines.h"

using namespace std;


void palmabrt();//hack

std::mutex event_data_access;
std::deque<osevent> osevtqueue;

osevent getoldestevent(){
	event_data_access.lock();
	osevent ev = osevtqueue.front();
	osevtqueue.pop_front();
	event_data_access.unlock();
	return ev;
}

void addnewevent(const osevent& ev){
	event_data_access.lock();
	osevtqueue.push_back(ev);
	event_data_access.unlock();
}

osevent readevtqueuepos(size_t pos){
	event_data_access.lock();
	osevent temp = osevtqueue[pos];
	event_data_access.unlock();
	return temp;
}

void writeevtqueuepos(size_t pos,const osevent& value){
	event_data_access.lock();
	osevtqueue[pos] = value;
	event_data_access.unlock();
}

bool hasevent(){
	//remove this later HACK
	event_data_access.lock();
	bool result = !osevtqueue.empty();
	event_data_access.unlock();
	return result;

	//events are never deleted from the input thread
	//return !osevtqueue.empty();
}

size_t availevents(){
	//remove this later
	event_data_access.lock();
	size_t result = osevtqueue.size();
	event_data_access.unlock();
	return result;

	//events are never deleted from the input thread
	//return osevtqueue.size();
}

void wipeeventqueue(){
	event_data_access.lock();//mutex probably not nessecary(but dosent hurt)
	//while(!osevtqueue.empty())osevtqueue.pop();
	while(!osevtqueue.empty())osevtqueue.pop_front();
	event_data_access.unlock();
}

//needed for uninterupted access to osevtqueue by sysTrapEvtAddUniqueEventToQueue
void replaceeventtype(const osevent& newevent,bool inplace,ULONG eventid){
	event_data_access.lock();

	size_t evtcounter,totalevents = osevtqueue.size();
	inc_for(evtcounter,totalevents){
		if(newevent.type == osevtqueue[evtcounter].type && (!eventid || eventid == osevtqueue[evtcounter].id)){
			if(inplace)osevtqueue[evtcounter] = newevent;
			else{
				//wants to place it at the end
				osevtqueue.erase(osevtqueue.begin() + evtcounter);//still need to remove the old one!!!
				osevtqueue.push_back(newevent);
			}
			break;
		}
	}

	//event doesent exist,create it
	if(evtcounter == totalevents)osevtqueue.push_back(newevent);

	event_data_access.unlock();
}



static void writeeventtoptr(CPTR eventptr,const osevent& thisevent){
	put_word(eventptr,thisevent.type);//always need the type

	//dosent hurt to add the pen values just incase
	put_byte(eventptr + 2,thisevent.pendown);
	put_byte(eventptr + 3,thisevent.tapcount);
	put_word(eventptr + 4,thisevent.screenx);
	put_word(eventptr + 6,thisevent.screeny);

	eventptr += evtDataOffset;
	switch(thisevent.type){
		case penUpEvent:
			put_word(eventptr,thisevent.data[0]);
			put_word(eventptr + 2,thisevent.data[1]);
			put_word(eventptr + 4,thisevent.data[2]);
			put_word(eventptr + 6,thisevent.data[3]);
			return;
		case frmCloseEvent:
		case frmLoadEvent:
		case frmOpenEvent:
			put_word(eventptr,thisevent.data[0]);
			return;
		case winEnterEvent:
		case winExitEvent:
			put_long(eventptr,thisevent.data[0]);
			put_long(eventptr + 4,thisevent.data[1]);
			return;
		case keyDownEvent:
			put_word(eventptr,thisevent.data[0]);
			put_word(eventptr + 2,thisevent.data[1]);
			put_word(eventptr + 4,thisevent.data[2]);
			return;
		case frmGadgetEnterEvent:
			put_word(eventptr,thisevent.data[0]);
			put_long(eventptr + 2,thisevent.data[1]);
			return;
		case frmGadgetMiscEvent:
			put_word(eventptr,thisevent.data[0]);//id
			put_long(eventptr + 2,thisevent.data[1]);//gadget ptr
			put_word(eventptr + 6,thisevent.data[2]);//selector
			put_long(eventptr + 8,thisevent.data[3]);//data ptr
			return;
		case ctlEnterEvent:
		case ctlExitEvent:
			put_word(eventptr,thisevent.data[0]);
			put_long(eventptr + 2,thisevent.data[1]);
			return;
		case ctlSelectEvent:
			put_word(eventptr,thisevent.data[0]);
			put_long(eventptr + 2,thisevent.data[1]);
			put_byte(eventptr + 6,thisevent.data[2]);
			put_byte(eventptr + 7,thisevent.data[3]);
			put_word(eventptr + 8,thisevent.data[4]);
			return;
		case fldEnterEvent:
			put_word(eventptr,thisevent.data[0]);
			put_long(eventptr + 2,thisevent.data[1]);
			return;


		case penDownEvent:
		case penMoveEvent:
		case nilEvent:
			//nothing
			return;
		default:
			if(thisevent.type < firstUserEvent){
				dbgprintf("EventType:%d not supported by writeeventtoptr\n",thisevent.type);
				palmabrt();
			}
			break;
	}


	//must be a user defined event(just a raw copy of sizeof(EventType) to eventptr)
	put_long(eventptr,thisevent.data[0]);
	put_long(eventptr + 4,thisevent.data[1]);
	put_long(eventptr + 8,thisevent.data[2]);
	put_long(eventptr + 12,thisevent.data[3]);
}

static osevent readeventfromptr(CPTR eventptr){
	osevent temp;
	temp.type = get_word(eventptr);//always need the type

	//dosent hurt to add the pen values just incase
	temp.pendown = get_byte(eventptr + 2);
	temp.tapcount = get_byte(eventptr + 3);
	temp.screenx = get_word(eventptr + 4);
	temp.screeny = get_word(eventptr + 6);

	eventptr += evtDataOffset;
	switch(temp.type){
		case penUpEvent:
			temp.data.push_back(get_word(eventptr));
			temp.data.push_back(get_word(eventptr + 2));
			temp.data.push_back(get_word(eventptr + 4));
			temp.data.push_back(get_word(eventptr + 6));
			return temp;
		case frmCloseEvent:
		case frmLoadEvent:
		case frmOpenEvent:
			temp.data.push_back(get_word(eventptr));
			return temp;
		case winEnterEvent:
		case winExitEvent:
			temp.data.push_back(get_long(eventptr));
			temp.data.push_back(get_long(eventptr + 4));
			return temp;
		case keyDownEvent:
			temp.data.push_back(get_word(eventptr));
			temp.data.push_back(get_word(eventptr + 2));
			temp.data.push_back(get_word(eventptr + 4));
			return temp;
		case frmGadgetEnterEvent:
			temp.data.push_back(get_word(eventptr));
			temp.data.push_back(get_long(eventptr + 2));
			return temp;
		case frmGadgetMiscEvent:
			temp.data.push_back(get_word(eventptr));
			temp.data.push_back(get_long(eventptr + 2));
			temp.data.push_back(get_word(eventptr + 6));
			temp.data.push_back(get_long(eventptr + 8));
			return temp;
		case ctlEnterEvent:
		case ctlExitEvent:
			temp.data.push_back(get_word(eventptr));
			temp.data.push_back(get_long(eventptr + 2));
			return temp;
		case ctlSelectEvent:
			temp.data.push_back(get_word(eventptr));
			temp.data.push_back(get_long(eventptr + 2));
			temp.data.push_back(get_byte(eventptr + 6));
			temp.data.push_back(get_byte(eventptr + 7));
			temp.data.push_back(get_word(eventptr + 8));
			return temp;
		case fldEnterEvent:
			temp.data.push_back(get_word(eventptr));
			temp.data.push_back(get_long(eventptr + 2));
			return temp;


		case penDownEvent:
		case penMoveEvent:
		case nilEvent:
			//nothing
			return temp;

		default:
			if(temp.type < firstUserEvent){
				dbgprintf("EventType:%d not supported by readeventfromptr\n",temp.type);
				palmabrt();
			}
			break;
	}


	//must be a user defined event(just a raw copy of sizeof(EventType) to an osevent struct)
	temp.data.push_back(get_long(eventptr));
	temp.data.push_back(get_long(eventptr + 4));
	temp.data.push_back(get_long(eventptr + 8));
	temp.data.push_back(get_long(eventptr + 12));
	return temp;
}



//apis
void evtgetevent(){
	stackptr(eventptr);
	stacklong(uwaittime);
	LONG waittime = (LONG)uwaittime;

	//dbgprintf("EvtPtr:%08x,WaitTime:%d\n",eventptr,waittime);

	//window flags
	evtgeteventWIN();

	if(!hasevent()){
		//wait for event here
		if(waittime == evtWaitForever){
			//wait forever
			while(!hasevent()){
				//this_thread::sleep_for(chrono::milliseconds(1));
				this_thread::sleep_for(palmTicks(1));
			}
		}else if(waittime > evtNoWait){
			int32 count;
			inc_for(count,waittime){
				this_thread::sleep_for(palmTicks(1));
				if(hasevent())break;
			}
		}
		else if(waittime < evtWaitForever)palmabrt();//should never happen

		if(!hasevent()){
			//dbgprintf("NilEvent\n");
			put_word(eventptr,0x0000);
			return;
		}
	}

	//its not empty

	osevent thisevent = getoldestevent();

	//use event writer
	writeeventtoptr(eventptr,thisevent);

	/*
	put_word(eventptr,thisevent.type);//always need the type

	//dosent hurt to add the pen values just incase
	put_byte(eventptr + 2,thisevent.pendown);
	put_byte(eventptr + 3,thisevent.tapcount);
	put_word(eventptr + 4,thisevent.screenx);
	put_word(eventptr + 6,thisevent.screeny);

	eventptr += evtDataOffset;
	switch(thisevent.type){
		case penUpEvent:
			put_word(eventptr,thisevent.data[0]);
			put_word(eventptr + 2,thisevent.data[1]);
			put_word(eventptr + 4,thisevent.data[2]);
			put_word(eventptr + 6,thisevent.data[3]);
			break;
		case frmCloseEvent:
		case frmLoadEvent:
		case frmOpenEvent:
			put_word(eventptr,thisevent.data[0]);
			break;
		case winEnterEvent:
		case winExitEvent:
			put_long(eventptr,thisevent.data[0]);
			put_long(eventptr + 4,thisevent.data[1]);
			break;
		case keyDownEvent:
			put_word(eventptr,thisevent.data[0]);
			put_word(eventptr + 2,thisevent.data[1]);
			put_word(eventptr + 4,thisevent.data[2]);
			break;
		case frmGadgetEnterEvent:
			put_word(eventptr,thisevent.data[0]);
			put_long(eventptr + 2,thisevent.data[1]);
			break;
		case frmGadgetMiscEvent:
			put_word(eventptr,thisevent.data[0]);//id
			put_long(eventptr + 2,thisevent.data[1]);//gadget ptr
			put_word(eventptr + 6,thisevent.data[2]);//selector
			put_long(eventptr + 8,thisevent.data[3]);//data ptr
			break;
		case ctlEnterEvent:
		case ctlExitEvent:
			put_word(eventptr,thisevent.data[0]);
			put_long(eventptr + 2,thisevent.data[1]);
			break;
		case ctlSelectEvent:
			put_word(eventptr,thisevent.data[0]);
			put_long(eventptr + 2,thisevent.data[1]);
			put_byte(eventptr + 6,thisevent.data[2]);
			put_byte(eventptr + 7,thisevent.data[3]);
			put_word(eventptr + 8,thisevent.data[4]);
			break;
		case fldEnterEvent:
			put_word(eventptr,thisevent.data[0]);
			put_long(eventptr + 2,thisevent.data[1]);
			break;


		case penDownEvent:
		case penMoveEvent:
		case nilEvent:
			//nothing
			break;
		default:
			dbgprintf("EventType:%d not supported by evtgetevent\n",thisevent.type);
			palmabrt();
			break;
	}
	*/

	dbgprintf("EventType:%d\n",thisevent.type);

	//no return value
}

TEMPHACK
//may use for android/ios and send a native sleep timer reset
void evtresetautoofftimer(){
	//this device has no auto off timer
	D0 = errNone;//always set to 0/errNone
}

TEMPHACK
//keys go directly to event queue not key queue (may or may not be ok)
void evtenqueuekey(){
	stackword(asciichar);
	stackword(keycode);
	stackword(modifiers);

	osevent keyevt;
	keyevt.data.push_back(asciichar);
	keyevt.data.push_back(keycode);
	keyevt.data.push_back(modifiers);

	TEMPHACK;
	//keys go directly to event queue not key queue (may or may not be ok)
	keyevt.type = keyDownEvent;
	addnewevent(keyevt);
	keyevt.type = keyUpEvent;
	addnewevent(keyevt);

	D0 = errNone;
}

void evtaddeventtoqueue(){
	stackptr(eventptr);
	osevent temp = readeventfromptr(eventptr);
	addnewevent(temp);
	//addnewevent(readeventfromptr(eventptr));

	//no return value
}

void evtadduniqueeventtoqueue(){
	stackptr(eventptr);
	stacklong(eventid);//0 means ignore(from api reference)
	stackbool(inplace);

	osevent temp = readeventfromptr(eventptr);
	replaceeventtype(temp,inplace,eventid);

	//no return value
}

void syshandleevent(){
	stackptr(eventptr);
	ULONG handled = 0;//handled means the event is over not that it was read/modifyed
	switch(get_word(eventptr)){//event type
		case keyDownEvent:
			//exit app or nothing
			break;
		case keyUpEvent:
			//exit app or nothing
			break;

		case nilEvent:
		case penDownEvent:
		case penUpEvent:
		case penMoveEvent:
		case winEnterEvent:
		case winExitEvent:
			break;
		default:
			break;
	}
	D0 = handled;
}
