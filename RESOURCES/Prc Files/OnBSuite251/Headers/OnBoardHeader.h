
/*
 * 							 Pilot Software
 *
 *	Copyright (c) 1994-1998, Palm Computing Inc., All Rights Reserved
 *
*/


enum events {
	nilEvent = 0,
	penDownEvent,
	penUpEvent,
	penMoveEvent,
	keyDownEvent,
	winEnterEvent,
	winExitEvent,
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
	appStopEvent,
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
	
	firstUserEvent = 0x6000
};

typedef char Int8;
typedef short Int16;	
typedef long Int32;
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned long UInt32;
typedef void *MemPtr;

typedef unsigned char Byte;
typedef int Word;
typedef int SWord;
typedef long SDWord;
typedef long DWord;
typedef unsigned char Boolean;
typedef short Short;
typedef long Long;
typedef char *CharPtr;
typedef unsigned int UInt;
typedef UInt *UIntPtr;
typedef unsigned long ULong;
typedef ULong *ULongPtr;
typedef short Err;
typedef char Char;
typedef int Int;
typedef Int *IntPtr;
typedef void *VoidPtr;
typedef Word *WordPtr;
typedef DWord *DWordPtr;
typedef VoidPtr *VoidHand;
typedef char *Ptr;
typedef Ptr *Handle;
typedef UInt8 IndexedColorType;

typedef struct {
  SWord left;
  SWord top;
  SWord right;
  SWord bottom;
} AbsRectType;

typedef struct{
	SWord fontType;
	SWord firstChar;
	SWord lastChar;
	SWord maxWidth;
	SWord kernMax;
	SWord nDescent;
	SWord fRectWidth;
	SWord fRectHeight;
	SWord owTLoc;
	SWord ascent;
	SWord descent;
	SWord leading;
	SWord rowWords;
} FontType;

typedef FontType * FontPtr;
enum fontID { stdFont, boldFont, largeFont, symbolFont, symbol11Font, 
				  symbol7Font, ledFont };
typedef enum fontID FontID;

typedef struct {
  SWord x;
  SWord y;
} PointType;

typedef Word FrameType;

#define noFrame         0
#define simpleFrame     1
#define rectangleFrame  1
#define simple3DFrame   0x0012
#define roundFrame      0x0401
#define boldRoundFrame  0x0702
#define popupFrame      0x0205
#define dialogFrame     0x0302
#define menuFrame       popupFrame

typedef struct {
  PointType  topLeft;
  PointType  extent;
} RectangleType;
typedef RectangleType *RectanglePtr;

typedef struct {
	Word format:1;
	Word offscreen:1;
	Word modal:1;
	Word focusable:1;
	Word enabled:1;
	Word visible:1;
	Word dialog:1;
	Word compressed:1;
	Word reserved :8;
} WindowFlagsType;

enum windowFormats { screenFormat = 0, genericFormat };
typedef enum windowFormats WindowFormatType;
typedef enum {scrCopy, scrAND, scrANDNOT, scrXOR, scrOR, scrCopyNOT} ScrOperation;
enum patterns { blackPattern, whitePattern, grayPattern, customPattern };
typedef enum patterns PatternType;
enum underlineModes { noUnderline, grayUnderline, solidUnderline };
typedef enum underlineModes UnderlineModeType;

typedef struct {
	Word compressed:1;
	Word reserved :15;
} BitmapFlagsType;

typedef struct {
	Word  					width;
	Word  					height;
	Word  					rowBytes;
	BitmapFlagsType		flags;
	Word	 					reserved [4];
} BitmapType;
typedef BitmapType * BitmapPtr;

typedef Word CustomPatternType [4];

typedef struct {
	ScrOperation		grafMode;
	Boolean				patternMode;
	PatternType			pattern;
	CustomPatternType	customPtn;
	FontID				fontId;
	Byte					padding1;
	FontPtr           font;
	UnderlineModeType	underlineMode;
} GraphicStateType;
typedef GraphicStateType * GraphicStatePtr;

typedef union {
	struct {
		Word cornerDiam   : 8;
		Word reserved     : 4;     
		Word shadowWidth  : 2;
		Word width        : 2;
	} bits;
	Word word;
} FrameBitsType;

enum directions { up = 0, down, left, right };
typedef enum directions DirectionType;

typedef struct WinTypeStruct {
  Word					displayWidth;
  Word					displayHeight;
  VoidPtr				displayAddr;
  WindowFlagsType		windowFlags;
  RectangleType			windowBounds;
  AbsRectType			clippingBounds;
  PointType				viewOrigin;
  FrameBitsType   		frameType;
  GraphicStatePtr		gstate;
  struct WinTypeStruct *nextWindow;
} WindowType;

typedef WindowType * WinPtr;
typedef WinPtr   		WinHandle;

typedef struct {
	Byte usable :1;
	Byte enabled :1;
	Byte visible :1;
	Byte on :1;
	Byte leftAnchor :1;
    Byte frame :3;
} ControlAttrType;

enum controlStyles {buttonCtl, pushButtonCtl, checkboxCtl, popupTriggerCtl,
							 selectorTriggerCtl, repeatingButtonCtl};
typedef enum controlStyles ControlStyleType;

typedef struct {
	Word						id;
	RectangleType			bounds;
	CharPtr				   text;	
	ControlAttrType		attr;
	ControlStyleType		style;
	FontID					font;
	Byte						group;
} ControlType;
typedef ControlType * ControlPtr;

typedef struct {
enum events    eType;
Boolean        penDown;
SWord          screenX;
SWord          screenY;
union data {
	struct generic {
		Word data1;
		Word data2;
		Word data3;
		Word data4;
		Word data5;
		Word data6;
		Word data7;
		Word data8;
		} generic;
	struct {
		PointType	start;
		PointType	end;
		} penUp;
	struct {
		Word chr;
		Word keyCode;
		Word modifiers;			
		} keyDown;
	struct winEnter {
		WinHandle    enterWindow; 
		WinHandle    exitWindow;
		} winEnter;
	struct winExit {
		WinHandle    enterWindow; 
		WinHandle    exitWindow;
		} winExit;
	struct ctlEnter {
		Word 	controlID;
		void *  pControl;
		} ctlEnter;
	struct ctlSelect {
		Word controlID;
		void *  pControl;
		Boolean	on;
		} ctlSelect;
	struct ctlRepeat {
		Word 	controlID;
		void *  pControl;
		DWord	time;
		} ctlRepeat;
	struct fldEnter {
		Word 	fieldID;
		void *  pField;
		} fldEnter;
	struct fldHeightChanged {
		Word 	fieldID;
		void *  pField;
		Word	newHeight;
		Word	currentPos;
		} fldHeightChanged;
	struct fldChanged {
		Word 	fieldID;
		void *   pField;
		} fldChanged;
	struct fldExit {
		Word 	fieldID;
		void *  pField;
		} fldExit;
	struct lstEnter {
		Word 	listID;
		void *  pList;
		Word selection;
		} lstEnter;
	struct lstExit {
		Word 	listID;
		void * pList;
		} lstExit;
	struct lstSelect {
		Word 	listID;
		void *  pList;
		Word selection;
		} lstSelect;

	struct tblEnter {
		Word tableID;
		void *  pTable;
		Word row;
		Word column;
		} tblEnter;

	struct tblExit {
		Word 	tableID;
		void *  pTable;
		Word 	row;
		Word 	column;
		} tblExit;
	struct tblSelect {
		Word 	tableID;
		void *  pTable;
		Word	row;
		Word 	column;
		} tblSelect;
	struct frmLoad {
		Word 	formID;
		} frmLoad;
	struct frmOpen {
		Word 	formID;
		} frmOpen;
	struct frmGoto {
		Word 	formID;
		Word 	recordNum;
		Word	matchPos;
		Word	matchLen;
		Word	matchFieldNum;
		DWord	matchCustom;
		} frmGoto;
	struct frmClose {
		Word formID;
		} frmClose;
	struct frmUpdate {
		Word 	formID;
		Word 	updateCode;
		} frmUpdate;
	struct frmTitleEnter {
		Word formID;
		} frmTitleEnter;
	struct frmTitleSelect {
		Word formID;
		} frmTitleSelect;
	struct daySelect {
		void *	pSelector;
		Word	selection;
		Boolean	useThisDate;
		} daySelect;
	struct menu {
		Word itemID;
		} menu;
	struct popSelect {
		Word	controlID;
		void *	controlP;
		Word	listID;
		void *  listP;
		Word	selection;
		Word	priorSelection;
		} popSelect;
	struct sclEnter {
		Word 	scrollBarID;
		void *	pScrollBar;
		} sclEnter;
	struct sclExit {
		Word 	scrollBarID;
		void *	pScrollBar;
		Short	value;
		Short	newValue;
		} sclExit;
	struct sclRepeat {
		Word 	scrollBarID;
		void *	pScrollBar;
		Short	value;
		Short	newValue;
		Long time;
		} sclRepeat;
	} data;
} EventType;

typedef EventType * EventPtr;

typedef struct {
	Word usable	:1;
	Word visible	:1;
	Word editable	:1;
	Word singleLine	:1;
	Word hasFocus	:1;
	Word dynamicSize	:1;
	Word insPtVisible	:1;
	Word dirty	:1;
	Word underlined	:2;
	Word justification	:2;
	Word autoShift	:1;
	Word hasScrollBar	:1;
	Word numeric	:1;
} FieldAttrType;
typedef FieldAttrType * FieldAttrPtr;

typedef struct {
Word	start;
Word	length;
} LineInfoType;
typedef LineInfoType * LineInfoPtr;

typedef struct {
Word	id;
RectangleType	rect;
FieldAttrType	attr;
CharPtr	text;
VoidHand	textHandle;
LineInfoPtr	lines;
Word	textLen;
Word	textBlockSize;
Word	maxChars;
Word	selFirstPos;
Word	selLastPos;
Word	insPtXPos;
Word	insPtYPos;
FontID	fontID;
} FieldType;
typedef FieldType * FieldPtr;

typedef struct {
Word usable:1;
Word enabled:1;
Word visible:1;
Word dirty:1;
Word saveBehind:1;
Word graffitiShift:1;
Word reserved:11;
} FormAttrType;

typedef Boolean FormEventHandlerType (EventPtr eventP);
typedef FormEventHandlerType * FormEventHandlerPtr;

typedef struct {
	Word usable :1;	
	Word enabled :1;
	Word visible :1;
   Word poppedUp :1;
	Word hasScrollBar :1;
	Word search	:1;
   Word reserved:2;
} ListAttrType;

typedef char *ListDrawDataFuncPtr;

typedef struct {
	Word			id;
   RectangleType	bounds;
   ListAttrType		attr;
   CharPtr			*itemsText;
   Word				numItems;
   Word   			currentItem;
   Word   			topItem;
   FontID           font;
	WinHandle   	popupWin;
   ListDrawDataFuncPtr drawItemsCallback;
} ListType;

typedef ListType * ListPtr;

typedef struct GraphicControlType GraphicControlType;
typedef struct SliderControlType SliderControlType;
typedef struct TableType TableType;
typedef struct FormBitmapType FormBitmapType;
typedef struct FormLabelType FormLabelType;
typedef struct FormTitleType FormTitleType;	
typedef struct FormPopupType FormPopupType;
typedef struct FrmGraffitiStateType FrmGraffitiStateType;
typedef struct FormGadgetType FormGadgetType;

typedef struct {
	Word usable	:1;
	Word visible	:1;
	Word hilighted	:1;
	Word shown	:1;
	Word activeRegion	:4;
} ScrollBarAttrType;

typedef struct {
	RectangleType	bounds;
	Word	id;
	ScrollBarAttrType	attr;
	Short	value;
	Short	minValue;
	Short	maxValue;
	Short	pageSize;
	Short	penPosInCar;
	Short	savePos;
} ScrollBarType;

typedef ScrollBarType * ScrollBarPtr;

typedef union {
	void *ptr;
	FieldType *field;
	ControlType *control;
	GraphicControlType *graphicControl;
	SliderControlType *sliderControl;
	ListType *list;
	TableType *table;
	FormBitmapType *bitmap;
	FormLabelType *label;
	FormTitleType *title;	
	FormPopupType *popup;
	FrmGraffitiStateType *grfState;
	FormGadgetType *gadget;
	ScrollBarType *scrollBar;
} FormObjectType;

enum formObjects {
	frmFieldObj,
	frmControlObj,
	frmListObj,
	frmTableObj,
	frmBitmapObj,
	frmLineObj,
	frmFrameObj,
	frmRectangleObj,
	frmLabelObj,
	frmTitleObj,
	frmPopupObj,
	frmGraffitiStateObj,
	frmGadgetObj,
	frmScrollBarObj };
typedef enum formObjects FormObjectKind;

typedef struct {
	FormObjectKind				objectType;
	UInt8 						reserved;
	FormObjectType				object;
} FormObjListType;

typedef struct {
	WindowType	window;
	Word	formId;
	FormAttrType	attr;
	WinHandle	bitsBehindForm;
	FormEventHandlerPtr	handler;
	Word	focus;
	Word	defaultButton;
	Word	helpRscId;
	Word	menuRscId;
	Word	numObjects;
	FormObjListType *objects;
} FormType;

typedef FormType * FormPtr;


typedef DWord LocalID;
typedef	VoidPtr DmOpenRef;

typedef struct {
	Byte attributes;
	Byte uniqueID[3];
} SortRecordInfoType;
typedef SortRecordInfoType * SortRecordInfoPtr;
typedef Int DmComparF(void *, void *, Int other, SortRecordInfoPtr, SortRecordInfoPtr, VoidHand appInfoH);

typedef enum SndSysBeepType {
	sndInfo = 1,
	sndWarning,
	sndError,
	sndStartUp,
	sndAlarm,
	sndConfirmation,
	sndClick
	} SndSysBeepType;

typedef struct {
	Word	id;
	Char	command;
	CharPtr	itemStr;
} MenuItemType;

typedef struct {
	WinHandle	menuWin;
	RectangleType	bounds;
	WinHandle	bitsBehind;
	RectangleType	titleBounds;
	CharPtr	title;
	Word	numItems;
	MenuItemType *	items;
} MenuPullDownType;

typedef MenuPullDownType *MenuPullDownPtr;

typedef struct {
	Word visible	:1;
	Word commandPending	:1;
	Word insPtEnabled	:1;
} MenuBarAttrType;


typedef struct {
	WinHandle	barWin;
	WinHandle	bitsBehind;
	WinHandle	savedActiveWin;
	WinHandle	bitsBehindStatus;
	MenuBarAttrType	attr;
	SWord	curMenu;
	SWord	curItem;
	SDWord	commandTick;
	SWord	numMenus;
	MenuPullDownPtr	menus;
} MenuBarType;

typedef MenuBarType *MenuBarPtr;

typedef struct {
	SDWord high;
	SDWord low;
} FlpDouble;											// for internal use only

typedef union {
        double	d;
        FlpDouble	fd;
        DWord	ul[2];
} FlpCompDouble;

typedef struct {
	Word	searchStrLen;
	Word	dbCardNo;	
	LocalID	dbID;
	Word	recordNum;
	Word	matchPos;
	Word	matchFieldNum;
	DWord	matchCustom;
} GoToParamsType;

typedef enum {
	winScreenModeGetDefaults,
	winScreenModeGet,
	winScreenModeSetToDefaults,
	winScreenModeSet,
	winScreenModeGetSupportedDepths,
	winScreenModeGetSupportsColor
} WinScreenModeOperation;

typedef enum UIColorTableEntries {
	UIObjectFrame = 0,
	UIObjectFill,
	UIObjectForeground,
	UIObjectSelectedFill,
	UIObjectSelectedForeground,
	UIMenuFrame,
	UIMenuFill,
	UIMenuForeground,
	UIMenuSelectedFill,
	UIMenuSelectedForeground,
	UIFieldBackground,
	UIFieldText,
	UIFieldTextLines,
	UIFieldCaret,
	UIFieldTextHighlightBackground,
	UIFieldTextHighlightForeground,
	UIFieldFepRawText,
	UIFieldFepRawBackground,
	UIFieldFepConvertedText,
	UIFieldFepConvertedBackground,
	UIFieldFepUnderline,
	UIFormFrame,
	UIFormFill,
	UIDialogFrame,
	UIDialogFill,
	UIAlertFrame,
	UIAlertFill,
	UIOK,
	UICaution,
	UIWarning,
	UILastColorTableEntry
} UIColorTableEntries;

typedef struct RGBColorType {
	UInt8   index;
	UInt8   r;
	UInt8   g;
	UInt8   b;
} RGBColorType;

typedef struct {
UInt32 info[8];
} DmSearchStateType;
typedef DmSearchStateType*	DmSearchStatePtr;	

#define SYS_TRAP(x) = { 0x4e4f, x }
#define FLOAT_TRAP(x) = { 0x7400 + x, 0x4e4f, sysTrapFlpDispatch }

void EvtGetEvent(EventPtr event, SDWord timeout) SYS_TRAP(sysTrapEvtGetEvent);
void EvtGetPen(SWord *pScreenX, SWord *pScreenY, Boolean *pPenDown)	SYS_TRAP(sysTrapEvtGetPen);
void FrmDeleteForm(const FormPtr frm) SYS_TRAP(sysTrapFrmDeleteForm);
void FrmDrawForm(FormPtr frm) SYS_TRAP(sysTrapFrmDrawForm);
FormPtr FrmGetActiveForm(void) SYS_TRAP(sysTrapFrmGetActiveForm);
void FrmSetActiveForm(FormPtr frm) SYS_TRAP(sysTrapFrmSetActiveForm);
Boolean FrmHandleEvent(FormPtr frm, EventPtr eventP) SYS_TRAP(sysTrapFrmHandleEvent);
void FrmHelp(const Word helpMsgId) SYS_TRAP(sysTrapFrmHelp);
void FrmGotoForm(Word formId) SYS_TRAP(sysTrapFrmGotoForm);
Boolean SysHandleEvent(EventPtr eventP)	SYS_TRAP(sysTrapSysHandleEvent);
Word FrmAlert(Word alertId) SYS_TRAP(sysTrapFrmAlert);
Word FrmCustomAlert(Word alertId, CharPtr s1, CharPtr s2, CharPtr s3) SYS_TRAP(sysTrapFrmCustomAlert);
Boolean FrmDispatchEvent(EventPtr eventP) SYS_TRAP(sysTrapFrmDispatchEvent);
void FrmSetEventHandler(FormPtr frm, FormEventHandlerPtr) SYS_TRAP(sysTrapFrmSetEventHandler);
Word FrmGetObjectIndex(FormPtr frm, Word objID)	SYS_TRAP(sysTrapFrmGetObjectIndex);
VoidPtr FrmGetObjectPtr(FormPtr frm, Word objIndex)	SYS_TRAP(sysTrapFrmGetObjectPtr);
Word FrmGetObjectId(FormPtr formP, UInt16 objIndex)	SYS_TRAP(sysTrapFrmGetObjectId);
void LstSetListChoices(ListPtr list, char ** itemsText, Word numItems) SYS_TRAP(sysTrapLstSetListChoices);
Word LstGetSelection(ListPtr list) SYS_TRAP(sysTrapLstGetSelection);
char *LstGetSelectionText(ListType *listP, Int16 itemNum) SYS_TRAP(sysTrapLstGetSelectionText);
void LstEraseList(ListPtr list) SYS_TRAP(sysTrapLstEraseList);
void LstSetSelection(ListPtr list, Word itemNum) SYS_TRAP(sysTrapLstSetSelection);
UInt DmNumDatabases(UInt cardNo)	SYS_TRAP(sysTrapDmNumDatabases);
LocalID DmGetDatabase(UInt cardNo, UInt index) SYS_TRAP(sysTrapDmGetDatabase);
DmOpenRef DmOpenDatabaseByTypeCreator(ULong type, ULong creator, UInt mode) SYS_TRAP(sysTrapDmOpenDatabaseByTypeCreator);
Err DmCreateDatabase(UInt cardNo, const CharPtr nameP, ULong creator, ULong type, Boolean resDB) SYS_TRAP(sysTrapDmCreateDatabase);
Err DmWrite(VoidPtr recordP, ULong offset, VoidPtr srcP, ULong bytes) SYS_TRAP(sysTrapDmWrite);						
Err DmStrCopy(VoidPtr recordP, ULong offset, CharPtr srcP) SYS_TRAP(sysTrapDmStrCopy);
Err DmSet(VoidPtr recordP, ULong offset, ULong bytes, Byte value) SYS_TRAP(sysTrapDmSet);
UInt DmNumResources(DmOpenRef dbP) SYS_TRAP(sysTrapDmNumResources);
Err DmResourceInfo(DmOpenRef dbP, int index, ULongPtr resTypeP,
IntPtr resIDP, LocalID* chunkLocalIDP) SYS_TRAP(sysTrapDmResourceInfo);
VoidHand DmGetRecord(DmOpenRef dbP, UInt index) SYS_TRAP(sysTrapDmGetRecord);
Err DmDetachRecord(DmOpenRef dbP, UInt index, Handle* oldHP) SYS_TRAP(sysTrapDmDetachRecord);
Err DmReleaseRecord(DmOpenRef dbP, UInt index, Boolean dirty) SYS_TRAP(sysTrapDmReleaseRecord);
Err	DmRemoveRecord(DmOpenRef dbP, UInt index) SYS_TRAP(sysTrapDmRemoveRecord);
UInt DmNumRecords(DmOpenRef dbP) SYS_TRAP(sysTrapDmNumRecords);
VoidHand DmNewRecord(DmOpenRef dbP, UIntPtr atP, ULong size) SYS_TRAP(sysTrapDmNewRecord);
VoidHand DmQueryRecord(DmOpenRef dbP, UInt index) SYS_TRAP(sysTrapDmQueryRecord);
VoidHand DmResizeRecord(DmOpenRef dbP, UInt index, ULong newSize) SYS_TRAP(sysTrapDmResizeRecord);
VoidHand DmGetResource(ULong type, int id) SYS_TRAP(sysTrapDmGetResource);
VoidHand DmNewResource(DmOpenRef dbP, ULong resType, int resID,	ULong size)	SYS_TRAP(sysTrapDmNewResource);
Err DmReleaseResource(VoidHand resourceH) SYS_TRAP(sysTrapDmReleaseResource);
Err DmRemoveResource(DmOpenRef dbP, int index) SYS_TRAP(sysTrapDmRemoveResource);
VoidHand DmGetResourceIndex(DmOpenRef dbP, int index) SYS_TRAP(sysTrapDmGetResourceIndex);
Err DmSetResourceInfo(DmOpenRef dbP, int index,	ULongPtr resTypeP, IntPtr resIDP) SYS_TRAP(sysTrapDmSetResourceInfo);
Err DmQuickSort(const DmOpenRef dbP, DmComparF *compar, int other) SYS_TRAP(sysTrapDmQuickSort);
int	DmFindResourceType(DmOpenRef dbP, ULong resType, int typeIndex)	SYS_TRAP(sysTrapDmFindResourceType);
int DmFindResource(DmOpenRef dbP, ULong resType, int resID, VoidHand resH) SYS_TRAP(sysTrapDmFindResource);
Err	DmGetNextDatabaseByTypeCreator(Boolean newSearch, DmSearchStatePtr stateInfoP, UInt32	type, UInt32 creator, 
Boolean onlyLatestVers, UInt16 *cardNoP, LocalID *dbIDP) SYS_TRAP(sysTrapDmGetNextDatabaseByTypeCreator);

VoidPtr MemHandleLock(VoidHand h) SYS_TRAP(sysTrapMemHandleLock);							
Err MemHandleUnlock(VoidHand h)	SYS_TRAP(sysTrapMemHandleUnlock);
ULong MemHandleSize(VoidHand h) SYS_TRAP(sysTrapMemHandleSize);
VoidHand MemHandleNew(ULong size) SYS_TRAP(sysTrapMemHandleNew);
Err MemHandleFree(VoidHand h) SYS_TRAP(sysTrapMemHandleFree);
VoidPtr MemPtrNew(ULong size) SYS_TRAP(sysTrapMemPtrNew);
Err MemPtrFree(VoidPtr chunkDataP) SYS_TRAP(sysTrapMemChunkFree);
Err MemMove(VoidPtr dstP, VoidPtr srcP, ULong numBytes) SYS_TRAP(sysTrapMemMove);
Err MemSet(VoidPtr dstP, ULong numBytes, Byte value) SYS_TRAP(sysTrapMemSet);
Err	MemHandleResize(VoidHand h, ULong newSize) SYS_TRAP(sysTrapMemHandleResize);

WinHandle WinCreateOffscreenWindow(SWord width, SWord height, WindowFormatType format, WordPtr error) SYS_TRAP(sysTrapWinCreateOffscreenWindow);
WinHandle WinSetDrawWindow(WinHandle winHandle) SYS_TRAP(sysTrapWinSetDrawWindow);
void WinDeleteWindow(WinHandle winHandle, Boolean eraseIt) SYS_TRAP(sysTrapWinDeleteWindow);
void WinDrawBitmap(BitmapPtr bitmapP, SWord x, SWord y) SYS_TRAP(sysTrapWinDrawBitmap);
void WinDrawChars(CharPtr chars, Word len, SWord x, SWord y) SYS_TRAP(sysTrapWinDrawChars);
void WinDrawInvertedChars(CharPtr chars, Word len, SWord x, SWord y) SYS_TRAP(sysTrapWinDrawInvertedChars);
void WinDrawLine(SWord x1, SWord y1, SWord x2, SWord y2) SYS_TRAP(sysTrapWinDrawLine);
void WinDrawGrayLine(SWord x1, SWord y1, SWord x2, SWord y2) SYS_TRAP(sysTrapWinDrawGrayLine);
void WinEraseLine(SWord x1, SWord y1, SWord x2, SWord y2) SYS_TRAP(sysTrapWinEraseLine);
void WinInvertLine(SWord x1, SWord y1, SWord x2, SWord y2) SYS_TRAP(sysTrapWinInvertLine);
void WinFillLine(SWord x1, SWord y1, SWord x2, SWord y2) SYS_TRAP(sysTrapWinFillLine);
void WinDrawRectangle(RectanglePtr r, Word cornerDiam) SYS_TRAP(sysTrapWinDrawRectangle);
void WinDrawRectangleFrame(FrameType frame, RectanglePtr r) SYS_TRAP(sysTrapWinDrawRectangleFrame);
void WinEraseRectangle(RectanglePtr r, Word cornerDiam) SYS_TRAP(sysTrapWinEraseRectangle);
void WinInvertRectangle(RectanglePtr r, Word cornerDiam) SYS_TRAP(sysTrapWinInvertRectangle);
void WinFillRectangle(RectanglePtr r, Word cornerDiam) SYS_TRAP(sysTrapWinFillRectangle);
void WinCopyRectangle(WinHandle srcWin, WinHandle dstWin, RectanglePtr srcRect, SWord destX, SWord destY, ScrOperation mode)
	SYS_TRAP(sysTrapWinCopyRectangle);
void WinSetClip(RectanglePtr r)	SYS_TRAP(sysTrapWinSetClip);
void WinResetClip(void)	SYS_TRAP(sysTrapWinResetClip);
void WinScrollRectangle(RectanglePtr r, enum directions direction, SWord distance, RectanglePtr vacated)
	SYS_TRAP(sysTrapWinScrollRectangle);
IndexedColorType WinSetForeColor(IndexedColorType foreColor) SYS_TRAP(sysTrapWinSetForeColor);
IndexedColorType WinSetBackColor(IndexedColorType backColor) SYS_TRAP(sysTrapWinSetBackColor);
Err WinScreenMode(WinScreenModeOperation operation, UInt32 *widthP, UInt32 *heightP, UInt32 *depthP, Boolean *enableColorP) SYS_TRAP(sysTrapScrDisplayMode);
void WinPushDrawState(void) SYS_TRAP(sysTrapWinPushDrawState);
void WinPopDrawState(void) SYS_TRAP(sysTrapWinPopDrawState);
IndexedColorType WinSetTextColor(IndexedColorType textColor) SYS_TRAP(sysTrapWinSetTextColor);
IndexedColorType WinRGBToIndex(const RGBColorType *rgbP) SYS_TRAP(sysTrapWinRGBToIndex);
Err UIColorSetTableEntry(UIColorTableEntries which, const RGBColorType *rgbP) SYS_TRAP(sysTrapUIColorSetTableEntry);
SWord FntSetFont(FontID fontID) SYS_TRAP(sysTrapFntSetFont);

void SndPlaySystemSound(SndSysBeepType beepID) SYS_TRAP(sysTrapSndPlaySystemSound);

DmOpenRef DmOpenDatabase(UInt cardNo, LocalID dbID, UInt mode) SYS_TRAP(sysTrapDmOpenDatabase);
Err DmCloseDatabase(DmOpenRef dbP) SYS_TRAP(sysTrapDmCloseDatabase);
LocalID	DmFindDatabase(UInt cardNo, const CharPtr nameP) SYS_TRAP(sysTrapDmFindDatabase);
Err DmDatabaseInfo(UInt cardNo, LocalID	dbID, CharPtr nameP,
					UIntPtr attributesP, UIntPtr versionP, ULongPtr crDateP,
					ULongPtr	modDateP, ULongPtr bckUpDateP,
					ULongPtr	modNumP, LocalID* appInfoIDP,
					LocalID* sortInfoIDP, ULongPtr typeP,
					ULongPtr creatorP) SYS_TRAP(sysTrapDmDatabaseInfo);
Err DmSetDatabaseInfo(UInt16 cardNo, LocalID dbID, const char *nameP,
					UInt16 *attributesP, UInt16 *versionP, UInt32 *crDateP,
					UInt32 *modDateP, UInt32 *bckUpDateP,
					UInt32 *modNumP, LocalID *appInfoIDP,
					LocalID *sortInfoIDP, UInt32 *typeP,
					UInt32 *creatorP) SYS_TRAP(sysTrapDmSetDatabaseInfo);
Err DmDatabaseSize(UInt16 cardNo, LocalID dbID, UInt32 *numRecordsP,
					UInt32 *totalBytesP, UInt32 *dataBytesP) SYS_TRAP(sysTrapDmDatabaseSize);
Err DmDeleteDatabase(UInt16 cardNo, LocalID dbID) SYS_TRAP(sysTrapDmDeleteDatabase);

MenuBarPtr MenuInit(Word resourceId) SYS_TRAP(sysTrapMenuInit);
Boolean MenuHandleEvent(MenuBarPtr pMenu, EventPtr event, WordPtr error) SYS_TRAP(sysTrapMenuHandleEvent);
void MenuDispose(MenuBarPtr pMenu) SYS_TRAP(sysTrapMenuDispose);
void MenuEraseStatus(MenuBarPtr pMenu) SYS_TRAP(sysTrapMenuEraseStatus);
MenuBarPtr MenuGetActiveMenu(void) SYS_TRAP(sysTrapMenuGetActiveMenu);
MenuBarPtr MenuSetActiveMenu( MenuBarPtr MenuP) SYS_TRAP(sysTrapMenuSetActiveMenu);

CharPtr StrCopy(CharPtr dst, const char* src) SYS_TRAP(sysTrapStrCopy);
CharPtr StrNCopy(CharPtr dst, const char* src, Word n) SYS_TRAP(sysTrapStrNCopy);
CharPtr StrCat(CharPtr dst, const char* src) SYS_TRAP(sysTrapStrCat);
CharPtr StrNCat(CharPtr dst, const char* src, Word n) SYS_TRAP(sysTrapStrNCat);
UInt StrLen(const char* src) SYS_TRAP(sysTrapStrLen);
int StrCompare(const char* s1, const char* s2) SYS_TRAP(sysTrapStrCompare);
int StrNCompare(const char* s1, const char* s2, DWord n) SYS_TRAP(sysTrapStrNCompare);
CharPtr StrToLower(CharPtr dst, const char* src) SYS_TRAP(sysTrapStrToLower);
CharPtr StrIToA(CharPtr s, long i) SYS_TRAP(sysTrapStrIToA);
CharPtr StrIToH(CharPtr s, ULong i) SYS_TRAP(sysTrapStrIToH);
CharPtr StrChr(const char* str, int chr) SYS_TRAP(sysTrapStrChr);
CharPtr StrStr(const char* str, const char* token) SYS_TRAP(sysTrapStrStr);
long StrAToI(const char* str) SYS_TRAP(sysTrapStrAToI);
SWord StrPrintF(CharPtr s, const char* formatStr, ...) SYS_TRAP(sysTrapStrPrintF);							
SWord StrVPrintF(CharPtr s, const char* formatStr, VoidPtr arg) SYS_TRAP(sysTrapStrVPrintF);

void CtlHideControl(ControlPtr pControl) SYS_TRAP(sysTrapCtlHideControl);
void CtlShowControl(ControlPtr pControl) SYS_TRAP(sysTrapCtlShowControl);
SWord CtlGetValue(ControlPtr pControl) SYS_TRAP(sysTrapCtlGetValue);
void CtlSetValue(ControlPtr pControl, SWord newValue) SYS_TRAP(sysTrapCtlSetValue);
void CtlSetEnabled(ControlPtr pControl, Boolean usable) SYS_TRAP(sysTrapCtlSetEnabled);

Word FrmDoDialog(FormPtr frm) SYS_TRAP(sysTrapFrmDoDialog);
Byte FrmGetControlGroupSelection(FormPtr frm, Byte groupNum) SYS_TRAP(sysTrapFrmGetControlGroupSelection);
void FrmSetControlGroupSelection(FormPtr frm, Byte groupNum, Word controlID) SYS_TRAP(sysTrapFrmSetControlGroupSelection);
void FrmCloseAllForms(void)	SYS_TRAP(sysTrapFrmCloseAllForms);
FormPtr FrmGetFormPtr(Word formId) SYS_TRAP(sysTrapFrmGetFormPtr);
FormPtr FrmGetFirstForm(void) SYS_TRAP(sysTrapFrmGetFirstForm);
void FrmUpdateScrollers(FormPtr frm, Word upIndex, Word downIndex, Boolean scrollableUp, Boolean scrollabledown) SYS_TRAP(sysTrapFrmUpdateScrollers);
FormPtr FrmInitForm(Word rscID) SYS_TRAP(sysTrapFrmInitForm);
void FrmEraseForm(FormType *formP) SYS_TRAP(sysTrapFrmEraseForm);
void FrmSetFocus(FormType *formP, UInt16 fieldIndex) SYS_TRAP(sysTrapFrmSetFocus);

void FldGetAttributes(FieldPtr fld, FieldAttrPtr attrP) SYS_TRAP(sysTrapFldGetAttributes);
void FldSetAttributes(FieldPtr fld, FieldAttrPtr attrP) SYS_TRAP(sysTrapFldSetAttributes);
void FldGrabFocus(FieldPtr fld) SYS_TRAP(sysTrapFldGrabFocus);
void FldReleaseFocus(FieldPtr fld) SYS_TRAP(sysTrapFldReleaseFocus);
Handle FldGetTextHandle(FieldPtr fld) SYS_TRAP(sysTrapFldGetTextHandle);
void FldSetText(FieldPtr fld, VoidHand textHandle, Word offset, Word size)	SYS_TRAP(sysTrapFldSetText);
void FldSetTextHandle(FieldPtr fld, Handle textHandle) SYS_TRAP(sysTrapFldSetTextHandle);
CharPtr FldGetTextPtr(FieldPtr fld) SYS_TRAP(sysTrapFldGetTextPtr);
void FldDelete(FieldPtr fld, Word start, Word end) SYS_TRAP(sysTrapFldDelete);
void FldDrawField(FieldPtr fld) SYS_TRAP(sysTrapFldDrawField);
Boolean FldHandleEvent(FieldPtr fld, EventPtr pEvent) SYS_TRAP(sysTrapFldHandleEvent);
UInt16 FldGetTextLength(FieldPtr fld) SYS_TRAP(sysTrapFldGetTextLength);
void FldSetSelection(FieldPtr fld, UInt16 startPosition, UInt16 endPosition) SYS_TRAP(sysTrapFldSetSelection);

SWord PrefGetAppPreferences(DWord creator, Word id, VoidPtr prefs, Word *prefsSize, Boolean saved) SYS_TRAP(sysTrapPrefGetAppPreferences);
void PrefSetAppPreferences(DWord creator, Word id, SWord version, VoidPtr prefs, Word prefsSize, Boolean saved) SYS_TRAP(sysTrapPrefSetAppPreferences);

#define	sysFtrCreator sysFileCSystem
#define	sysFtrNumROMVersion	1
Err FtrGet(DWord creator, UInt featureNum, DWordPtr valueP)	SYS_TRAP(sysTrapFtrGet);
Err FtrSet(DWord creator, UInt featureNum, DWord newValue) SYS_TRAP(sysTrapFtrSet);
Err FtrUnregister(DWord creator, UInt featureNum) SYS_TRAP(sysTrapFtrUnregister);

typedef Int16 _comparF (void *, void *, Int32 other);
typedef _comparF * CmpFuncPtr;

void SysInsertionSort(void *baseP, Int16 numOfElements, Int16 width, const CmpFuncPtr comparF, const Int32 other) SYS_TRAP(sysTrapSysInsertionSort);
int SysRandom(ULong newSeed) SYS_TRAP(sysTrapSysRandom);
Err SysTaskDelay(SDWord delay) SYS_TRAP(sysTrapSysTaskDelay);
ULong TimGetTicks(void) SYS_TRAP(sysTrapTimGetTicks);

SWord FntCharsWidth(char *chars, Word len) SYS_TRAP(sysTrapFntCharsWidth);
SWord FntCharWidth(const char ch) SYS_TRAP(sysTrapFntCharWidth);
SWord FntCharHeight(void) SYS_TRAP(sysTrapFntCharHeight);
SWord FntDescenderHeight(void) SYS_TRAP(sysTrapFntDescenderHeight);

Err FlpFToA(FlpDouble a, char* s) FLOAT_TRAP(1);
FlpDouble FlpAToF(char* s) FLOAT_TRAP(2);

void SclSetScrollBar(const ScrollBarPtr bar, short value, const short min, const short max, const short pageSize) SYS_TRAP(sysTrapSclSetScrollBar);

typedef enum DlkSyncStateType {
dlkSyncStateNeverSynced = 0,
dlkSyncStateInProgress,
dlkSyncStateLostConnection,
dlkSyncStateLocalCan,
dlkSyncStateRemoteCan,
dlkSyncStateLowMemoryOnTD,
dlkSyncStateAborted,
dlkSyncStateCompleted,	
dlkSyncStateIncompatibleProducts
} DlkSyncStateType;

Err	DlkGetSyncInfo(UInt32 * succSyncDateP, UInt32 * lastSyncDateP, DlkSyncStateType* syncStateP, char * nameBufP, char * logBufP, Int32 * logLenP) SYS_TRAP(sysTrapDlkGetSyncInfo);


#define	sysLibTrapBase 0xA800
typedef enum {
	sysLibTrapName = sysLibTrapBase,
	sysLibTrapOpen,
	sysLibTrapClose,
	sysLibTrapSleep,
	sysLibTrapWake,
	sysLibTrapCustom
} SysLibTrapNumber;

Err SysLibLoad(DWord libType, DWord libCreator, UIntPtr refNumP) SYS_TRAP(sysTrapSysLibLoad);
Err SysLibRemove(UInt refNum) SYS_TRAP(sysTrapSysLibRemove);
Err SysLibFind(CharPtr nameP, UIntPtr refNumP) SYS_TRAP(sysTrapSysLibFind);

Err MathLibOpen(UInt refnum, UInt version) SYS_TRAP(sysLibTrapOpen);
Err MathLibClose(UInt refnum, UIntPtr usecountP) SYS_TRAP(sysLibTrapClose);

Err MathLibPow(UInt refnum, double x, double y, double *result)	SYS_TRAP(sysLibTrapCustom+24);
Err MathLibSqrt(UInt refnum, double x, double *result)	SYS_TRAP(sysLibTrapCustom+25);

#define	sysRandomMax 0x7FFF

#define strRsc 'tSTR'
#define ainRsc 'tAIN'
#define iconType 'tAIB'
#define bitmapRsc 'Tbmp'
#define alertRscType 'Talt'
#define MenuRscType 'MBAR'
#define verRsc 'tver'
#define sysFileCDefaultApp 'appl'
#define	sysFileCSystem 'psys'
#define evtWaitForever -1

#define	sysAppLaunchCmdNormalLaunch	0
#define	sysAppLaunchCmdFind	1
#define	sysAppLaunchCmdGoTo 2

#define	sysAppLaunchFlagNewGlobals 0x04
#define	sysAppLaunchFlagUIApp 0x08

#define	sysErrParamErr 0x0502

#define	dmHdrAttrResDB 0x0001
#define dmHdrAttrReadOnly 0x0002
#define	dmHdrAttrAppInfoDirty 0x0004
#define	dmHdrAttrBackup 0x0008

#define	dmModeReadOnly 0x0001
#define	dmModeReadWrite	0x0003
#define dmDBNameLength 32

#define	hwrGraffitiTop 164
#define	hwrGraffitiLeft 27
#define	hwrGraffitiWidth 106
#define	hwrGraffitiHeight 56
#define	hwrGraffitiSplit 89

#define noPreferenceFound -1

#define backspaceChr 0x08
#define tabChr 0x09
#define linefeedChr 0x0A
#define crChr 0x0D
#define spaceChr 0x20

#define pageUpChr 0x0B
#define pageDownChr	0x0C
#define leftArrowChr 0x1C
#define rightArrowChr 0x1D

#define dlkMaxUserNameLength 40
#define dlkUserNameBufSize (dlkMaxUserNameLength + 1)

#define true 1
#define false 0
#define NULL 0
#define errNone 0


