/*
	File:			HighScoreTest.c	

	Description:	Source file for testing the high score API.

	Author:		

	Copyright:		Copyright © 2003 by Tapwave, Inc.

	Disclaimer:		IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
					use is subject to and governed by terms and conditions of the Software Development 
					Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
					into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
					to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
					You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
					or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

#include <PalmOS.h>
#include <Tapwave.h>
#include "HighScoreTestRsc.h"


/***********************************************************************
 *
 *	Entry Points
 *
 ***********************************************************************/
static void * GetObjectPtr(UInt16 objectID);
static Err RomVersionCompatible(UInt32 requiredVersion, UInt16 launchFlags);
static Boolean FldVisible(FieldType *fieldP);
#define FrmObjPtr(formP, objectID) FrmGetObjectPtr(formP, FrmGetObjectIndex(formP, objectID))


/***********************************************************************
 *
 *	Internal Structures
 *
 ***********************************************************************/
typedef struct 
	{
		UInt32 creatorID;
		UInt16 scoreType;
		UInt16 numLocalScoresToKeep;
		UInt16 numServerScoresToKeep;
		Boolean reportScoresToServer;
		Char gameName[41];
		Char tournamentCode[6];
	} HighScoreTestPreferenceType;

/***********************************************************************
 *
 *	Global variables
 *
 ***********************************************************************/
//static Boolean HideSecretRecords;
HighScoreTestPreferenceType gPrefs;
TwHighScoreSummaryType *gSummaryP;
struct {
	MemHandle creatorIDH;
	MemHandle scoreTypeH;
	MemHandle gameNameH;
	MemHandle numLocalScoresToKeepH;
	MemHandle numServerScoresToKeepH;
	MemHandle localSummaryH;
	MemHandle serverSummaryH;
	MemHandle serverSyncDateH;
} gEditBuffer;

/***********************************************************************
 *
 *	Internal Constants
 *
 ***********************************************************************/
#define appFileCreator			'TWHS'	// register your own at http://www.palmos.com/dev/creatorid/
#define appVersionNum			0x01
#define appPrefID				0x00
#define appPrefVersionNum		0x01

// Define the minimum OS version we support (2.0 for now).
#define ourMinVersion	sysMakeROMVersion(5,2,0,sysROMStageRelease,0)
#define kPalmOS10Version	sysMakeROMVersion(1,0,0,sysROMStageRelease,0)

#define MAXUINT32 0xFFFFFFFF

/***********************************************************************
 *
 *	Internal Functions
 *
 ***********************************************************************/

static Err PrvAddNewScore(void)
{
	Err err;
	TwHighScoreType tempScore;
	Char buffer[32];
	UInt32 newScore;
	UInt32 minScore, maxScore;

	// timestamp the score	
	tempScore.dateAndTime = TimGetSeconds();

	// generate 32 bit random number
	newScore = SysRandom(0);
	newScore <<= 16;
	newScore += SysRandom(0);
	
	// limit the range
	if (gSummaryP)
	{
		minScore = gSummaryP->lowestLocalScore + 1;
		if (gSummaryP->highestLocalScore < 66)
			maxScore = 100;
		else if (gSummaryP->highestLocalScore < MAXUINT32 - MAXUINT32/3)
			maxScore = gSummaryP->highestLocalScore + gSummaryP->highestLocalScore/2;
		else
			maxScore = MAXUINT32;
	}
	else
	{
		minScore = 1;
		maxScore = 100;
	}
	newScore %= (maxScore - minScore);
	newScore += minScore;
	tempScore.score = newScore;
	
	tempScore.checksum = newScore;
	
	// generate the score description	
	StrPrintF(buffer, "%lu points", tempScore.score);
	tempScore.userString = buffer;

	err = TwHighScoreReport(gPrefs.creatorID, gPrefs.scoreType, &tempScore);
	return err;
}

static void PrvGetSummary()
{
	if (gSummaryP)
		MemPtrFree(gSummaryP);
		
	gSummaryP = TwHighScoreGetSummary(gPrefs.creatorID, gPrefs.scoreType);
	
	// copy summary data into prefs in case we unregister, quit, etc.
	if (gSummaryP)
	{
		gPrefs.numLocalScoresToKeep = gSummaryP->numLocalScoresToKeep;
		gPrefs.numServerScoresToKeep = gSummaryP->numServerScoresToKeep;
		gPrefs.reportScoresToServer = gSummaryP->reportScoresToServer;
		StrNCopy(gPrefs.gameName, gSummaryP->gameName, 40);
	}
}


static Char *PrvAppendText(Char *in, const Char *add)
{
    Char *out = in;
    if (add)
    {
        if (!out && add && StrLen(add))
        {
            out = MemPtrNew(StrLen(add)+1);
            *out = '\0';
        }
        else if (MemPtrResize(out, StrLen(in) + StrLen(add) + 1) != errNone)
        {
            out = MemPtrNew(StrLen(in) + StrLen(add) + 1);
            StrCopy(out, in);
            MemPtrFree(in);
        }
        StrCat(out, add);
    }
    return out;
}


static void PrvUpdateScrollBar(FieldType *fieldP, ScrollBarType *barP)
{
	UInt16 scrollPos;
	UInt16 textHeight;
	UInt16 fieldHeight;
	Int16 maxValue;

	FldGetScrollValues (fieldP, &scrollPos, &textHeight,  &fieldHeight);

	if (textHeight > fieldHeight)
		maxValue = (textHeight - fieldHeight) + FldGetNumberOfBlankLines (fieldP);
	else if (scrollPos)
		maxValue = scrollPos;
	else
		maxValue = 0;

	SclSetScrollBar (barP, scrollPos, 0, maxValue, fieldHeight-1);
}


static Boolean PrvDetailsHandleEvent (EventType * eventP)
{
    FormType *formP;
	FieldType *fieldP;
    Int16 linesToScroll;
	ScrollBarType *barP;

	switch (eventP->eType)
	{
		case fldChangedEvent:
			formP = FrmGetActiveForm ();
        	fieldP = FrmObjPtr (formP, DetailsDetailsField);
        	barP = FrmObjPtr (formP, DetailsDetailsScrollBar);
        	PrvUpdateScrollBar(fieldP, barP);
			return false;
		
		case sclRepeatEvent:
            linesToScroll = eventP->data.sclRepeat.newValue - eventP->data.sclRepeat.value;
			formP = FrmGetActiveForm ();
        	fieldP = FrmObjPtr (formP, DetailsDetailsField);
        	barP = FrmObjPtr (formP, DetailsDetailsScrollBar);

        	if (linesToScroll < 0)
        		FldScrollField (fieldP, -linesToScroll, winUp);
        	else if (linesToScroll > 0)
        		FldScrollField (fieldP, linesToScroll, winDown);
        	PrvUpdateScrollBar(fieldP, barP);
            return false;
            
		default:
		    return false;
    }
}

static void PrvDoDetails(void)
{
    FormType *formP = FrmInitForm(DetailsForm);
    FieldType *fieldP;
    ScrollBarType *barP;
    Char *textP = NULL;
    Char buffer[50];
    Char *endP;
    TwHighScoreType *detailsP;
    UInt16 i;
    DateTimeType dateTime;
    
    PrvGetSummary();

    if (!gSummaryP)
        textP = PrvAppendText(textP, "No scores available.");
    else
    {
        if (gSummaryP->numLocalScores == 0)
            textP = PrvAppendText(textP, "No local scores.");
        else
        {
            StrPrintF(buffer, "Top %u local scores:", gSummaryP->numLocalScores);
            textP = PrvAppendText(textP, buffer);
            
            for (i = 0; i < gSummaryP->numLocalScores; i++)
            {
                detailsP = TwHighScoreGetDetails(gPrefs.creatorID, gPrefs.scoreType, twHighScorePoolLocal, i);
                if (!detailsP)
                {
                    StrPrintF(buffer, "\nError getting score %d", i);
                    textP = PrvAppendText(textP, buffer);
                }
                else
                {
                    textP = PrvAppendText(textP, "\n");
                    textP = PrvAppendText(textP, detailsP->userString);
                    
                    TimSecondsToDateTime(detailsP->dateAndTime, &dateTime);
                    StrPrintF(buffer, "\n  (");
                    endP = &buffer[4];
                    TimeToAscii(dateTime.hour, dateTime.minute, tfColon24h, endP);
                    endP += StrLen(endP);
                    *endP++ = ' ';
                    DateToAscii(dateTime.month, dateTime.day, dateTime.year, dfMDYWithSlashes, endP);
                    endP += StrLen(endP);
                    StrPrintF(endP, ", %lu %lx)", detailsP->score, detailsP->checksum);
                    textP = PrvAppendText(textP, buffer);
                    MemPtrFree(detailsP);
                }
            }
        }
         
        if (gSummaryP->numServerScores > 0)
        {
            StrPrintF(buffer, "\n\nTop %u worldwide scores:", gSummaryP->numServerScores);
            textP = PrvAppendText(textP, buffer);
            
            for (i = 0; i < gSummaryP->numServerScores; i++)
            {
                detailsP = TwHighScoreGetDetails(gPrefs.creatorID, gPrefs.scoreType, twHighScorePoolServer, i);
                if (!detailsP)
                {
                    StrPrintF(buffer, "\nError getting score %d", i);
                    textP = PrvAppendText(textP, buffer);
                }
                else
                {
                    textP = PrvAppendText(textP, "\n");
                    textP = PrvAppendText(textP, detailsP->userString);
                    
                    TimSecondsToDateTime(detailsP->dateAndTime, &dateTime);
                    StrPrintF(buffer, "\n  (");
                    endP = &buffer[4];
                    TimeToAscii(dateTime.hour, dateTime.minute, tfColon24h, endP);
                    endP += StrLen(endP);
                    *endP++ = ' ';
                    DateToAscii(dateTime.month, dateTime.day, dateTime.year, dfMDYWithSlashes, endP);
                    endP += StrLen(endP);
                    StrPrintF(endP, ", %lu %lx)", detailsP->score, detailsP->checksum);
                    textP = PrvAppendText(textP, buffer);
                    MemPtrFree(detailsP);
                }
            }
         }

    }
    
    fieldP = FrmObjPtr(formP, DetailsDetailsField);
	FldSetTextPtr(fieldP, textP);
    FldRecalculateField(fieldP, false);
    
 	barP = FrmObjPtr (formP, DetailsDetailsScrollBar);
    PrvUpdateScrollBar(fieldP, barP);
    FrmSetEventHandler(formP, &PrvDetailsHandleEvent);
    FrmDoDialog(formP);
    
    FrmDeleteForm(formP);
    if (textP)
        MemPtrFree(textP);
}


static void PrvGetFormValues(FormType *formP, Boolean typeCreatorOnly)
{
	Char * textP;
	
	textP = FldGetTextPtr(FrmObjPtr(formP, MainCreatorIDField));
	gPrefs.creatorID = (UInt32)textP[0] << 24;
	gPrefs.creatorID += (UInt32)textP[1] << 16;
	gPrefs.creatorID += (UInt32)textP[2] << 8;
	gPrefs.creatorID += (UInt32)textP[3];

	textP = FldGetTextPtr(FrmObjPtr(formP, MainScoreTypeField));
	gPrefs.scoreType = StrAToI(textP);
	
	if (typeCreatorOnly)
	    return;
	
	textP = FldGetTextPtr(FrmObjPtr(formP, MainMaxLocalField));
	gPrefs.numLocalScoresToKeep = StrAToI(textP);
	
	textP = FldGetTextPtr(FrmObjPtr(formP, MainMaxServerField));
	gPrefs.numServerScoresToKeep = StrAToI(textP);
	
	gPrefs.reportScoresToServer = CtlGetValue(FrmObjPtr(formP, MainReportToServerCheckbox));
	
	textP = FldGetTextPtr(FrmObjPtr(formP, MainGameNameField));
	StrNCopy(gPrefs.gameName, textP, 40);
}

static void PrvSetFormValues(FormType *formP)
{
	Char* textP;
	FieldType *fieldP;
	DateTimeType dateTime;

	// update the form objects to reflect prefs data
	fieldP = FrmObjPtr(formP, MainCreatorIDField);
	textP = MemHandleLock(gEditBuffer.creatorIDH);
	textP[0] = (gPrefs.creatorID >> 24) & 0xFF;
	textP[1] = (gPrefs.creatorID >> 16) & 0xFF;
	textP[2] = (gPrefs.creatorID >> 8) & 0xFF;
	textP[3] = (gPrefs.creatorID >> 0) & 0xFF;
	textP[4] = '\0';
	MemPtrUnlock(textP);
	FldSetTextHandle(fieldP, gEditBuffer.creatorIDH);
	if (FldVisible(fieldP))
		FldDrawField(fieldP);

	fieldP = FrmObjPtr(formP, MainScoreTypeField);
	textP = MemHandleLock(gEditBuffer.scoreTypeH);
	StrPrintF(textP, "%hu", gPrefs.scoreType);
	MemPtrUnlock(textP);
	FldSetTextHandle(fieldP, gEditBuffer.scoreTypeH);
	if (FldVisible(fieldP))
		FldDrawField(fieldP);

	fieldP = FrmObjPtr(formP, MainMaxLocalField);
	textP = MemHandleLock(gEditBuffer.numLocalScoresToKeepH);
	StrPrintF(textP, "%hu", gPrefs.numLocalScoresToKeep);
	MemPtrUnlock(textP);
	FldSetTextHandle(fieldP, gEditBuffer.numLocalScoresToKeepH);
	if (FldVisible(fieldP))
		FldDrawField(fieldP);

	fieldP = FrmObjPtr(formP, MainMaxServerField);
	textP = MemHandleLock(gEditBuffer.numServerScoresToKeepH);
	StrPrintF(textP, "%hu", gPrefs.numServerScoresToKeep);
	MemPtrUnlock(textP);
	FldSetTextHandle(fieldP, gEditBuffer.numServerScoresToKeepH);
	if (FldVisible(fieldP))
		FldDrawField(fieldP);

	CtlSetValue(FrmObjPtr(formP, MainReportToServerCheckbox), gPrefs.reportScoresToServer);

	fieldP = FrmObjPtr(formP, MainGameNameField);
	textP = MemHandleLock(gEditBuffer.gameNameH);
	StrNCopy(textP, gPrefs.gameName, 40);
	MemPtrUnlock(textP);
	FldSetTextHandle(fieldP, gEditBuffer.gameNameH);
	if (FldVisible(fieldP))
		FldDrawField(fieldP);

	// update the score summary readonly fields to reflect high score summary data
	fieldP = FrmObjPtr(formP, MainLocalSummaryField);
	textP = MemHandleLock(gEditBuffer.localSummaryH);
	if (gSummaryP)
		StrPrintF(textP, "%u local scores, from %lu to %lu.",
			gSummaryP->numLocalScores, gSummaryP->highestLocalScore, gSummaryP->lowestLocalScore);
	else
		StrCopy(textP, "No local scores.");
	MemPtrUnlock(textP);
	FldSetTextHandle(fieldP, gEditBuffer.localSummaryH);
	if (FldVisible(fieldP))
		FldDrawField(fieldP);
	
	fieldP = FrmObjPtr(formP, MainServerSummaryField);
	textP = MemHandleLock(gEditBuffer.serverSummaryH);
	if (gSummaryP)
		StrPrintF(textP, "%u server scores, from %lu to %lu.",
			gSummaryP->numServerScores, gSummaryP->highestServerScore, gSummaryP->lowestServerScore);
	else
		StrCopy(textP, "No server scores available.");
	MemPtrUnlock(textP);
	FldSetTextHandle(fieldP, gEditBuffer.serverSummaryH);
	if (FldVisible(fieldP))
		FldDrawField(fieldP);
				
	fieldP = FrmObjPtr(formP, MainServerSyncDateField);
	textP = MemHandleLock(gEditBuffer.serverSyncDateH);
	if (gSummaryP)
	{
	    if (gSummaryP->timeSynced != 0)
    	{
    	    TimSecondsToDateTime(gSummaryP->timeSynced, &dateTime);
            TimeToAscii(dateTime.hour, dateTime.minute, tfColon24h, textP);
            textP += StrLen(textP);
            *textP++ = ' ';
            DateToAscii(dateTime.month, dateTime.day, dateTime.year, dfMDYLongWithComma, textP);
        }
        else
            StrCopy(textP, "Never");
    }
    else
        StrCopy(textP, "");
        
	MemHandleUnlock(gEditBuffer.serverSyncDateH);
	FldSetTextHandle(fieldP, gEditBuffer.serverSyncDateH);
	if (FldVisible(fieldP))
		FldDrawField(fieldP);
}

/***********************************************************************
 *
 * FUNCTION:    MainFormInit
 *
 * DESCRIPTION: This routine initializes the MainForm form.
 *
 * PARAMETERS:  frm - pointer to the MainForm form.
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void MainFormInit(FormType * formP)
{
	gSummaryP = NULL;
	
	gEditBuffer.creatorIDH = MemHandleNew(5);
	gEditBuffer.scoreTypeH = MemHandleNew(6);
	gEditBuffer.gameNameH = MemHandleNew(41);
	gEditBuffer.numLocalScoresToKeepH = MemHandleNew(6);
	gEditBuffer.numServerScoresToKeepH = MemHandleNew(6);
	gEditBuffer.localSummaryH = MemHandleNew(80);
	gEditBuffer.serverSummaryH = MemHandleNew(80);
	gEditBuffer.serverSyncDateH = MemHandleNew(30);

	PrvGetSummary();
	PrvSetFormValues(formP);
}


static void MainFormClose(FormType *formP)
{
	if (gSummaryP)
	{
		MemPtrFree(gSummaryP);
		gSummaryP = NULL;
	}
	
	// fields do this for us
	//MemHandleFree(gEditBuffer.creatorIDH);
	//MemHandleFree(gEditBuffer.scoreTypeH);
	//MemHandleFree(gEditBuffer.gameNameH);
	//MemHandleFree(gEditBuffer.numLocalScoresToKeepH);
	//MemHandleFree(gEditBuffer.numServerScoresToKeepH);
	//MemHandleFree(gEditBuffer.localSummaryH);
	//MemHandleFree(gEditBuffer.serverSummaryH);
	//MemHandleFree(gEditBuffer.serverSyncDateH);
}


/***********************************************************************
 *
 * FUNCTION:    MainFormDoCommand
 *
 * DESCRIPTION: This routine performs the menu command specified.
 *
 * PARAMETERS:  command  - menu item id
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean MainFormDoCommand(UInt16 command)
{
	Boolean handled = false;
	FormType * formP;
	UInt16 newScoreType;

	switch (command)
	{
		case MainOptionsAboutHighScoreTest:
			MenuEraseStatus(0);					// Clear the menu status from the display.
			formP = FrmInitForm (AboutForm);
			FrmDoDialog (formP);					// Display the About Box.
			FrmDeleteForm (formP);
			handled = true;
			break;

        case MainOptionsEnterTournamentCode:
            MenuEraseStatus(0);
            formP = FrmGetActiveForm();
	        PrvGetFormValues(formP, true);
            newScoreType = TwHighScoreGetTournament(gPrefs.creatorID, gPrefs.scoreType, gPrefs.tournamentCode);
            
            if (newScoreType == gPrefs.scoreType)
                newScoreType = TwHighScoreGetTournament(gPrefs.creatorID, 1, gPrefs.tournamentCode);
                
            gPrefs.scoreType = newScoreType;
			PrvGetSummary();
         	if (!gSummaryP)
        	{
        		gPrefs.numLocalScoresToKeep = 0;
        		gPrefs.numServerScoresToKeep = 0;
        		gPrefs.reportScoresToServer = false;
        		StrNCopy(gPrefs.gameName, "", 40);
        	}
			PrvSetFormValues(formP);
			break;
	}
	
	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    MainFormHandleEvent
 *
 * DESCRIPTION: This routine is the event handler for the 
 *              "MainForm" of this application.
 *
 * PARAMETERS:  eventP  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean MainFormHandleEvent(EventType * eventP)
{
	Err err;
	Boolean handled = false;
	FormType * formP;

	switch (eventP->eType) 
		{
		case menuEvent:
			return MainFormDoCommand(eventP->data.menu.itemID);

		case frmOpenEvent:
			formP = FrmGetActiveForm();
			MainFormInit( formP);
			FrmDrawForm ( formP);
			handled = true;
			break;
			
		case frmCloseEvent:
			formP = FrmGetActiveForm();
			MainFormClose(formP);
			break;
			
		case frmUpdateEvent:
			// To do any custom drawing here, first call FrmDrawForm(), then do your
			// drawing, and then set handled to true.
			break;
		
		case ctlSelectEvent:
			formP = FrmGetActiveForm();
			switch (eventP->data.ctlSelect.controlID)
			{
			    case MainGetButton:
			        PrvGetFormValues(formP, true);
					PrvGetSummary();
                 	if (!gSummaryP)
                	{
                		gPrefs.numLocalScoresToKeep = 0;
                		gPrefs.numServerScoresToKeep = 0;
                		gPrefs.reportScoresToServer = false;
                		StrNCopy(gPrefs.gameName, "", 40);
                	}
 					PrvSetFormValues(formP);
                    break;
                                      			        
				case MainRegisterButton:
					PrvGetFormValues(formP, false);
					err = TwHighScoreRegister(
						gPrefs.creatorID,
						gPrefs.scoreType,
						gPrefs.numLocalScoresToKeep,
						gPrefs.numServerScoresToKeep,
						gPrefs.reportScoresToServer,
						gPrefs.gameName);
					PrvGetSummary();
					PrvSetFormValues(formP);
					break;
					
				case MainUnregisterButton:
					PrvGetFormValues(formP, false);
					err = TwHighScoreUnregister(gPrefs.creatorID, gPrefs.scoreType);
					PrvGetSummary();
					PrvSetFormValues(formP);
					break;
					
				case MainDetailsButton:
                    PrvDoDetails();
                    break;				    
				
				case MainNewScoreButton:
					PrvAddNewScore();
					PrvGetSummary();
					PrvSetFormValues(formP);
					break;
								
				case MainReportToServerCheckbox:
					gPrefs.reportScoresToServer = eventP->data.ctlSelect.on;
					break;
			}
			break;
            
		default:
			break;
		
		}
	
	return handled;
}


/***********************************************************************
 *
 * FUNCTION:    AppHandleEvent
 *
 * DESCRIPTION: This routine loads form resources and set the event
 *              handler for the form loaded.
 *
 * PARAMETERS:  event  - a pointer to an EventType structure
 *
 * RETURNED:    true if the event has handle and should not be passed
 *              to a higher level handler.
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Boolean AppHandleEvent(EventType * eventP)
{
	UInt16 formId;
	FormType * formP;

	if (eventP->eType == frmLoadEvent)
		{
		// Load the form resource.
		formId = eventP->data.frmLoad.formID;
		formP = FrmInitForm(formId);
		FrmSetActiveForm(formP);

		// Set the event handler for the form.  The handler of the currently
		// active form is called by FrmHandleEvent each time is receives an
		// event.
		switch (formId)
			{
			case MainForm:
				FrmSetEventHandler(formP, MainFormHandleEvent);
				break;

			default:
//				ErrFatalDisplay("Invalid Form Load Event");
				break;

			}
		return true;
		}
	
	return false;
}


/***********************************************************************
 *
 * FUNCTION:    AppEventLoop
 *
 * DESCRIPTION: This routine is the event loop for the application.  
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void AppEventLoop(void)
{
	UInt16 error;
	EventType event;
	Boolean handled;

	do {
		EvtGetEvent(&event, 2 * SysTicksPerSecond());

		if (! SysHandleEvent(&event))
			if (! MenuHandleEvent(0, &event, &error))
				if (! AppHandleEvent(&event))
					handled = FrmDispatchEvent(&event);
					
	} while (event.eType != appStopEvent || handled);
}


/***********************************************************************
 *
 * FUNCTION:     AppStart
 *
 * DESCRIPTION:  Get the current application's preferences.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     Err value 0 if nothing went wrong
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Err AppStart(void)
{
	UInt16 prefsSize;

	// Read the saved preferences / saved-state information.
	prefsSize = sizeof(HighScoreTestPreferenceType);
	if ((PrefGetAppPreferences(appFileCreator, appPrefID, &gPrefs, &prefsSize, true)
		== noPreferenceFound)
		|| prefsSize != sizeof(HighScoreTestPreferenceType))
	{
		// create initial UI details
		gPrefs.creatorID = 'TWHS';
		gPrefs.scoreType = 0;
		gPrefs.numLocalScoresToKeep = 10;
		gPrefs.numServerScoresToKeep = 10;
		gPrefs.reportScoresToServer = true;
		StrNCopy(gPrefs.gameName, "High Score Test", 41);
		StrNCopy(gPrefs.tournamentCode, "00000", 6);
	}
	
	return errNone;
}


/***********************************************************************
 *
 * FUNCTION:    AppStop
 *
 * DESCRIPTION: Save the current state of the application.
 *
 * PARAMETERS:  nothing
 *
 * RETURNED:    nothing
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void AppStop(void)
{
	// Write the saved preferences / saved-state information.  This data 
	// will saved during a HotSync backup.
	PrefSetAppPreferences (appFileCreator, appPrefID, appPrefVersionNum, 
		&gPrefs, sizeof (HighScoreTestPreferenceType), true);
		
	// Close all the open forms.
	FrmCloseAllForms ();
}


/***********************************************************************
 *
 * FUNCTION:    HighScoreTestPalmMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  cmd - word value specifying the launch code. 
 *              cmdPB - pointer to a structure that is associated with the launch code. 
 *              launchFlags -  word value providing extra information about the launch.
 *
 * RETURNED:    Result of launch
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static UInt32 HighScoreTestPalmMain(UInt16 cmd, MemPtr /*cmdPBP*/, UInt16 launchFlags)
{
	Err error;

	error = RomVersionCompatible (ourMinVersion, launchFlags);
	if (error) return (error);

	switch (cmd)
		{
		case sysAppLaunchCmdNormalLaunch:
			error = AppStart();
			if (error) 
				return error;
				
			FrmGotoForm(MainForm);
			AppEventLoop();
			AppStop();
			break;

		default:
			break;

		}
	
	return errNone;
}

/***********************************************************************
 *
 * FUNCTION:    RomVersionCompatible
 *
 * DESCRIPTION: This routine checks that a ROM version is meet your
 *              minimum requirement.
 *
 * PARAMETERS:  requiredVersion - minimum rom version required
 *                                (see sysFtrNumROMVersion in SystemMgr.h 
 *                                for format)
 *              launchFlags     - flags that indicate if the application 
 *                                UI is initialized.
 *
 * RETURNED:    error code or zero if rom is compatible
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static Err RomVersionCompatible(UInt32 requiredVersion, UInt16 launchFlags)
{
	UInt32 romVersion;

	// See if we're on in minimum required version of the ROM or later.
	FtrGet(sysFtrCreator, sysFtrNumROMVersion, &romVersion);
	if (romVersion < requiredVersion)
		{
		if ((launchFlags & (sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp)) ==
			(sysAppLaunchFlagNewGlobals | sysAppLaunchFlagUIApp))
			{
			FrmAlert (RomIncompatibleAlert);
		
			// Palm OS 1.0 will continuously relaunch this app unless we switch to 
			// another safe one.
			if (romVersion <= kPalmOS10Version)
				{
				AppLaunchWithCommand(sysFileCDefaultApp, sysAppLaunchCmdNormalLaunch, NULL);
				}
			}
		
		return sysErrRomIncompatible;
		}

	return errNone;
}


/***********************************************************************
 *
 * FUNCTION:    GetObjectPtr
 *
 * DESCRIPTION: This routine returns a pointer to an object in the current
 *              form.
 *
 * PARAMETERS:  formId - id of the form to display
 *
 * RETURNED:    void *
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
static void * GetObjectPtr(UInt16 objectID)
{
	FormType * formP;

	formP = FrmGetActiveForm();
	return FrmGetObjectPtr(formP, FrmGetObjectIndex(formP, objectID));
}


static Boolean FldVisible(FieldType *fieldP)
{
	FieldAttrType attributes;
	FldGetAttributes(fieldP, &attributes);
	return attributes.visible;
}


/***********************************************************************
 *
 * FUNCTION:    PilotMain
 *
 * DESCRIPTION: This is the main entry point for the application.
 *
 * PARAMETERS:  cmd - word value specifying the launch code. 
 *              cmdPB - pointer to a structure that is associated with the launch code. 
 *              launchFlags -  word value providing extra information about the launch.
 * RETURNED:    Result of launch
 *
 * REVISION HISTORY:
 *
 *
 ***********************************************************************/
UInt32 PilotMain( UInt16 cmd, MemPtr cmdPBP, UInt16 launchFlags)
{
	return HighScoreTestPalmMain(cmd, cmdPBP, launchFlags);
}
