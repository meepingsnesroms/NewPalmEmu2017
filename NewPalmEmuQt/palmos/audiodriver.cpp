#include "m68k.h"
#include "dataexchange.h"
#include "audiodriver.h"

#include <chrono>
#include <thread>

#include "palmdefines.h"//hack

void palmabrt();//hack

using namespace std;

//SndStreamRef is ULONG

/*
SndStreamSetVolume
Sets the amplitude scalar for a sound stream.
Err SndStreamSetVolume (SndStreamRef stream,
Int32 ampScale);
-> stream
-> ampScale
errNone
sndErrBadParam
Stream token, as returned through SndCreateRawStream.
Amplitude scalar in the range [0, 32k]. Values less than 0 are converted to 1024 (unity gain).
Success. Invalid stream.
The ampScale value is applied as an amplitude scalar on the samples that this stream’s callback function produces. The scalar is
 Palm OS Programmer’s API Reference 893
amplitude scalar
Sound Manager
Sampled Sound Functions
  Compatibility
in the range [0, 32k], where 1024 is unity gain (i.e. the samples are multiplied by 1.0). The mapping of ampScale to scalar is linear; thus a volume of 512 scales the samples by ~.5, 2048 scales by ~2.0, and so on.
To specify a user preference volume setting, use one of sndSystemVolume, sndGameVolume, or sndAlarmVolume. These values are guaranteed to be less than unity gain.
If the stream is stereo, both channels are scaled by the same amplitude scalar. To adjust the balance between the channels, use SndStreamSetPan.
Implemented if Sound Stream Feature Set is present.
*/

//UWORD currentfreq;

void sndstreamsetvolume(){
	stacklong(sndstreamref);
	stacklong(ampscale);

	dbgprintf("Stream:%d,ScaleFactor:%d\n",sndstreamref,ampscale);

	D0 = errNone;
}

void sndgetdefaultvolume(){
	stackptr(alarmvol);
	stackptr(systemvol);
	stackptr(mastervol);

	//hacks vv
	putwordifvptr(alarmvol,sndMaxAmp);
	putwordifvptr(systemvol,sndMaxAmp);
	putwordifvptr(mastervol,sndMaxAmp);
	//hacks ^^

	//palmabrt();

	//no return value
}

TEMPHACK
//audio driver later
void snddocmd(){
	stackptr(channel);//must be nullptr_68k
	stackptr(command);
	stackbool(nowait);//not used (even by palm)


	if(channel != nullptr_68k){
		palmabrt();//hack

		D0 = sndErrBadChannel;
		return;
	}

	//from palm os api reference
	//IMPORTANT: The Sound Manager only supports one channel of
	//sound synthesis: You must pass NULL as the value of channel.


	UBYTE cmd = get_byte(command);
	LONG pram1 = (LONG)get_long(command + 2);
	UWORD pram2 = get_word(command + 6);
	UWORD pram3 = get_word(command + 8);

	switch(cmd){
		case sndCmdFreqDurationAmp:
			if(pram3 == 0)break;//if amplitude is 0 return

			//this function is blocking wait for (pram2) milliseconds
			this_thread::sleep_for(chrono::milliseconds(pram2));
			break;
		case sndCmdFrqOn:
			//same as above but dosent wait
			break;
		case sndCmdNoteOn:
		case sndCmdQuiet:

			//dbgprintf("No audio driver!\n");
			break;

		default:
			palmabrt();//hack

			/*
			D0 = sndErrBadParam;
			return;
			*/

			break;
	}

	D0 = errNone;
}
