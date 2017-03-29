/* CaseHack.c */ 
/* a HackMaster extension */ 
 
#pragma segment 1000 

// the routine we're hacking :
// void EvtGetEvent(EventPtr event, SDWord timeout)

void caseHack(EventPtr evt, SDWord timeout) 
{ 
	Boolean (*oldtrap)(EventPtr, SDWord);
	
	FtrGet('CaSe', 1000, (DWordPtr)&oldtrap);
	oldtrap(evt, timeout);
	if ((evt->eType == keyDownEvent) &&
		(evt->data.keyDown.modifiers == 0))
		if ((evt->data.keyDown.chr >= 'a') 
			&& (evt->data.keyDown.chr <= 'z'))
			evt->data.keyDown.chr -= 0x20;
} 
 
 
