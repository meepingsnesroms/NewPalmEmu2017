/*	EventLoop.c	*/

/*
	Common code for OnBoardC examples.
	
	- Provides main entry point (PilotMain)
	that responds to normalLaunch only.

	- Expects an event handler defined in another
	application file:
	
        Boolean mainFormEventHandler(EventPtr event)

	that gets installed as the handler for
	the initial form.
	
	- Assumes MAINFORM 1000
	
	- Initializes MathLib if possible.
*/

#define MAINFORM 1000
extern Boolean mainFormEventHandler(EventPtr evt);

Boolean appHandleEvent(EventPtr event)
{
	FormPtr	frm;
	UInt16		formId;
	Boolean	handled = false;
	if (event->eType == frmLoadEvent) {
		formId = event->data.frmLoad.formID;
		frm = FrmInitForm(formId);
		FrmSetActiveForm(frm);
		if (formId == MAINFORM)
			FrmSetEventHandler (frm, mainFormEventHandler);
		handled = true;
	}	
	return handled;
}

UInt32 PilotMain(UInt16 cmd, char *cmdPBP, UInt16 launchFlags)
{
	EventType event;
	UInt16 error;
	if (cmd == sysAppLaunchCmdNormalLaunch) {
		FrmGotoForm(MAINFORM);
		do {
			EvtGetEvent(&event, 30);
			if (!SysHandleEvent(&event))
				if (!MenuHandleEvent(0, &event, &error))
    					if (!appHandleEvent(&event))
						FrmDispatchEvent(&event);
		} while (event.eType != appStopEvent);
		FrmCloseAllForms();
	}
	return 0;
}
 
