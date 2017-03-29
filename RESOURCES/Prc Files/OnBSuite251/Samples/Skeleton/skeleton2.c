#define AppCreator 'Demo'
#define OptionsMenuAbout 1000
#define AboutAlert 1000
#define MainForm 1000

typedef struct {
    int skeletonData;
} Prefs;

Prefs prefs;

static void mainFormInit(FormPtr frmP)
{
	// allocate memory
	Handle h = MemHandleNew(100);
	CharPtr p = MemHandleLock(h);

	//write some text
	CharPtr suffix = "th";
	if ((prefs.skeletonData < 11) || (prefs.skeletonData > 20)) {
	    switch (prefs.skeletonData % 10) {
		case 1: suffix = "st";
			break;
		case 2: suffix = "nd";
			break;
		case 3: suffix = "rd";
			break;
	    }
	}			
	StrPrintF(p, "Hello, World ! (for the %d%s time...)", prefs.skeletonData, suffix);
	WinDrawChars(p,StrLen(p),10,40);

	// free memory
	MemHandleUnlock (h);
	MemHandleFree(h);
}

static Boolean doMenu(FormPtr frmP, UInt16 command)
{
	Boolean handled = false;
	switch (command) {
	    case OptionsMenuAbout :
		FrmAlert(AboutAlert);
		handled = true;
		break;
	    }
	    return handled;
}

Boolean mainFormEventHandler(EventPtr eventP) {
Boolean handled = false;
FormPtr frmP= FrmGetActiveForm();
switch (eventP->eType) {
    case frmOpenEvent:
        FrmDrawForm(frmP);
        mainFormInit(frmP);
        handled = true;
        break;
    case menuEvent:
        handled = doMenu(frmP, eventP->data.menu.itemID);
        break;                  
    }
return handled;
}

void startApp() {
UInt16 prefSize = sizeof(Prefs);
if ((PrefGetAppPreferences (AppCreator, 1000, &prefs, &prefSize, true) == noPreferenceFound) 
    || (prefSize != sizeof(Prefs))) {
        // default initialization, since discovered Prefs was missing or old.
        prefs.skeletonData=1;
    }
}

void stopApp() {
prefs.skeletonData++;
PrefSetAppPreferences(AppCreator, 1000, 1, &prefs, sizeof(Prefs), true);
}


Boolean appHandleEvent(EventPtr event) {
FormPtr frm;
Int16             formId;
Boolean handled = false;
if (event->eType == frmLoadEvent) {
    formId = event->data.frmLoad.formID;
    frm = FrmInitForm(formId);
    FrmSetActiveForm(frm);
    if (formId == MainForm)
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
	    startApp();
	    FrmGotoForm(MainForm);
	    do {
		EvtGetEvent(&event, evtWaitForever);
		if (!SysHandleEvent (&event))
		if (!MenuHandleEvent (0, &event, &error))
		if (!appHandleEvent (&event))
			FrmDispatchEvent (&event);
	    } while (event.eType != appStopEvent);
	    stopApp();
	    FrmCloseAllForms();
	}
	return 0;
}
