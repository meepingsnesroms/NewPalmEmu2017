#include "timing.h"
#include "types.h"

#include <chrono>
#include <thread>

using namespace std;

void palmabrt();//hack

#define DURATION 50000

int32 cputicks;

void resetcycles(){
	cputicks = 0;
}

void cycle(){
	cputicks++;
	while(cputicks >= DURATION){
		this_thread::sleep_for(chrono::milliseconds(1));
		cputicks -= DURATION;
	}
}

void simulatecycles(uint32 amount){
	int32 oldticks = cputicks;
	cputicks += amount;
	if(oldticks > cputicks)palmabrt();//hack //counter overflowed
	while(cputicks >= DURATION){
		this_thread::sleep_for(chrono::milliseconds(1));
		cputicks -= DURATION;
	}
}

void freecycles(){
	palmabrt();//hack //function no finished

	//speed hack to catch up

	//if you need * opcodes completed in * milliseconds
	//but the requirement was not met free ((needed opcodes) - (completed opcodes)) opcodes
	//to prevent the wait until complete
}
