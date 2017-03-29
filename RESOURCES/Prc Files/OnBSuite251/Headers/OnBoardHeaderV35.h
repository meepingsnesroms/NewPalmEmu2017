
/*
 *  OnBoardHeader.h, assembled from Palm SDK 3.5 header files.
 *
 *	Copyright (c) 1994-1999, Palm Computing Inc., All Rights Reserved
 *
*/


typedef enum {
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
} eventsEnum;

typedef char Int8;
typedef short Int16;	
typedef long Int32;
typedef unsigned char UInt8;
typedef unsigned short UInt16;
typedef unsigned long UInt32;
typedef void *MemPtr;
typedef struct _opaque *MemHandle;

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
typedef Word *WordPtr;
typedef DWord *DWordPtr;
typedef MemPtr VoidPtr;
typedef MemHandle VoidHand;
typedef char *Ptr;
typedef UInt8 IndexedColorType;
typedef UInt16 WChar;
typedef Int16 Coord;
typedef UInt32 DmResType;
typedef UInt16 DmResID;
typedef MemHandle Handle;

typedef struct {
Coord left;
Coord top;
Coord right;
Coord bottom;
} AbsRectType;

typedef struct{
Int16 fontType;
Int16 firstChar;
Int16 lastChar;
Int16 maxWidth;
Int16 kernMax;
Int16 nDescent;
Int16 fRectWidth;
Int16 fRectHeight;
Int16 owTLoc;
Int16 ascent;
Int16 descent;
Int16 leading;
Int16 rowWords;
} FontType;

typedef FontType * FontPtr;
enum fontID { stdFont, boldFont, largeFont, symbolFont, symbol11Font, symbol7Font, ledFont };
typedef enum fontID FontID;

typedef struct {
Coord x;
Coord y;
} PointType;

typedef UInt16 FrameType;

#define noFrame 0
#define simpleFrame 1
#define rectangleFrame 1
#define simple3DFrame 0x0012
#define roundFrame 0x0401
#define boldRoundFrame 0x0702
#define popupFrame 0x0205
#define dialogFrame 0x0302
#define menuFrame  popupFrame

typedef struct {
PointType  topLeft;
PointType  extent;
} RectangleType;
typedef RectangleType *RectanglePtr;

typedef struct {
UInt16 format:1;
UInt16 offscreen:1;
UInt16 modal:1;
UInt16 focusable:1;
UInt16 enabled:1;
UInt16 visible:1;
UInt16 dialog:1;
UInt16 compressed:1;
UInt16 reserved :8;
} WindowFlagsType;

enum windowFormats { screenFormat = 0, genericFormat };
typedef enum windowFormats WindowFormatType;
typedef enum {scrCopy, scrAND, scrANDNOT, scrXOR, scrOR, scrCopyNOT} ScrOperation;
enum patterns { blackPattern, whitePattern, grayPattern, customPattern };
typedef enum patterns PatternType;
enum underlineModes { noUnderline, grayUnderline, solidUnderline };
typedef enum underlineModes UnderlineModeType;

typedef struct {
UInt16 compressed:1;
UInt16 hasColorTable:1;
UInt16 hasTransparency:1;
UInt16 indirect:1;
UInt16 forScreen:1;
UInt16 reserved:11;
} BitmapFlagsType;

typedef struct {
Int16 width;
Int16 height;
UInt16 rowBytes;
BitmapFlagsType	flags;
UInt8 pixelSize;
UInt8 version;
UInt16 nextDepthOffset;
UInt8 transparentIndex;
UInt8 compressionType;
UInt16 reserved;
} BitmapType;
typedef BitmapType * BitmapPtr;

typedef struct ColorTableType {
UInt16 numEntries;
} ColorTableType;

typedef UInt8 CustomPatternType[8];

typedef union FrameBitsType {
struct {
UInt16 cornerDiam:8;
UInt16 reserved_3:3; 
UInt16 threeD:1; 
UInt16 shadowWidth:2;
UInt16 width:2;
} bits;
UInt16 word;
} FrameBitsType;

enum directions { up = 0, down, left, right };
typedef enum directions DirectionType;

typedef struct DrawStateType DrawStateType;
typedef enum {winPaint, winErase, winMask, winInvert, winOverlay, winPaintInverse, winSwap} WinDrawOperation;
typedef enum { winUp = 0, winDown, winLeft, winRight } WinDirectionType;

typedef struct WindowType {
Coord displayWidthV20;
Coord displayHeightV20;
void *displayAddrV20;
WindowFlagsType windowFlags;
RectangleType windowBounds;
AbsRectType clippingBounds;
BitmapPtr bitmapP;
FrameBitsType frameType;
DrawStateType *drawStateP;
struct WindowType *nextWindow;
} WindowType;

typedef WindowType *WinPtr;
typedef WindowType *WinHandle;

typedef struct {
UInt8 usable:1;
UInt8 enabled:1;
UInt8 visible:1;
UInt8 on:1;
UInt8 leftAnchor:1;
UInt8 frame:3;
UInt8 drawnAsSelected:1;
UInt8 graphical:1;
UInt8 vertical:1;
UInt8 reserved:5;
} ControlAttrType;

enum controlStyles {buttonCtl, pushButtonCtl, checkboxCtl, popupTriggerCtl,
							 selectorTriggerCtl, repeatingButtonCtl};
typedef enum controlStyles ControlStyleType;

typedef struct {
UInt16 id;
RectangleType bounds;
Char *text;	
ControlAttrType	attr;
ControlStyleType style;
FontID font;
UInt8 group;
UInt8 reserved;
} ControlType;
typedef ControlType * ControlPtr;

typedef struct {
eventsEnum eType;
Boolean penDown;
UInt8 tapCount;
Int16 screenX;
Int16 screenY;
union data {
struct generic {
	UInt16 datum[8];
	} generic;
struct {
	PointType start;
	PointType end;
	} penUp;
struct {
	WChar chr;
	UInt16 keyCode;
	UInt16 modifiers;			
	} keyDown;
struct winEnter {
	WinHandle enterWindow; 
	WinHandle exitWindow;
	} winEnter;
struct winExit {
	WinHandle enterWindow; 
	WinHandle exitWindow;
	} winExit;
struct ctlEnter {
	UInt16 controlID;
	ControlPtr pControl;
	} ctlEnter;
struct ctlSelect {
	UInt16 controlID;
	ControlPtr pControl;
	Boolean	on;
	UInt8 reserved1;
	UInt16 value;
	} ctlSelect;
struct ctlRepeat {
	UInt16 controlID;
	ControlPtr pControl;
	DWord time;
	UInt16 value;
	} ctlRepeat;
struct fldEnter {
	UInt16 fieldID;
	void *pField;
	} fldEnter;
struct fldHeightChanged {
	UInt16 fieldID;
	void *pField;
	Int16 newHeight;
	UInt16 currentPos;
	} fldHeightChanged;
struct fldChanged {
	UInt16 fieldID;
	void *pField;
	} fldChanged;
struct fldExit {
	UInt16 fieldID;
	void *pField;
	} fldExit;
struct lstEnter {
	UInt16 listID;
	void *pList;
	Int16 selection;
	} lstEnter;
struct lstExit {
	UInt16 listID;
	void *pList;
	} lstExit;
struct lstSelect {
	UInt16 listID;
	void *pList;
	Int16 selection;
	} lstSelect;
struct tblEnter {
	UInt16 tableID;
	void *pTable;
	Int16 row;
	Int16 column;
	} tblEnter;
struct tblExit {
	UInt16 tableID;
	void *pTable;
	Int16 row;
	Int16 column;
	} tblExit;
struct tblSelect {
	UInt16 tableID;
	void *pTable;
	Int16 row;
	Int16 column;
	} tblSelect;
struct frmLoad {
	UInt16 formID;
	} frmLoad;
struct frmOpen {
	UInt16 formID;
	} frmOpen;
struct frmGoto {
	UInt16 formID;
	UInt16 recordNum;
	UInt16 matchPos;
	UInt16 matchLen;
	UInt16 matchFieldNum;
	UInt32 matchCustom;
	} frmGoto;
struct frmClose {
	UInt16 formID;
	} frmClose;
struct frmUpdate {
	UInt16 formID;
	UInt16 updateCode;
	} frmUpdate;
struct frmTitleEnter {
	UInt16 formID;
	} frmTitleEnter;
struct frmTitleSelect {
	UInt16 formID;
	} frmTitleSelect;
struct daySelect {
	void *pSelector;
	Int16 selection;
	Boolean	useThisDate;
	UInt8 reserved1;
	} daySelect;
struct menu {
	UInt16 itemID;
	} menu;
struct popSelect {
	UInt16 controlID;
	void *controlP;
	UInt16 listID;
	void *listP;
	Int16 selection;
	Int16 priorSelection;
	} popSelect;
struct sclEnter {
	UInt16 scrollBarID;
	void *ScrollBar;
	} sclEnter;
struct sclExit {
	UInt16 scrollBarID;
	void *pScrollBar;
	Int16 value;
	Int16 newValue;
	} sclExit;
struct sclRepeat {
	UInt16 scrollBarID;
	void *pScrollBar;
	Int16 value;
	Int16 newValue;
	Int32 time;
	} sclRepeat;
} data;
} EventType;

typedef EventType *EventPtr;

typedef struct {
UInt16 usable:1;
UInt16 visible:1;
UInt16 editable:1;
UInt16 singleLine:1;
UInt16 hasFocus:1;
UInt16 dynamicSize:1;
UInt16 insPtVisible:1;
UInt16 dirty:1;
UInt16 underlined:2;
UInt16 justification:2;
UInt16 autoShift:1;
UInt16 hasScrollBar:1;
UInt16 numeric:1;
} FieldAttrType;
typedef FieldAttrType *FieldAttrPtr;

typedef struct {
UInt16 start;
UInt16 length;
} LineInfoType;
typedef LineInfoType *LineInfoPtr;

typedef struct {
UInt16 id;
RectangleType rect;
FieldAttrType attr;
Char *text;
MemHandle textHandle;
LineInfoPtr	lines;
UInt16 textLen;
UInt16 textBlockSize;
UInt16 maxChars;
UInt16 selFirstPos;
UInt16 selLastPos;
UInt16 insPtXPos;
UInt16 insPtYPos;
FontID fontID;
UInt8 reserved;
} FieldType;
typedef FieldType *FieldPtr;

typedef struct {
UInt16 usable:1;
UInt16 enabled:1;
UInt16 visible:1;
UInt16 dirty:1;
UInt16 saveBehind:1;
UInt16 graffitiShift:1;
UInt16 globalsAvailable:1;
UInt16 doingDialog:1;
UInt16 exitDialog:1;
UInt16 reserved:7;
UInt16 reserved2;
} FormAttrType;

typedef Boolean FormEventHandlerType (EventType *eventP);
typedef FormEventHandlerType * FormEventHandlerPtr;

typedef struct {
UInt16 usable:1;	
UInt16 enabled:1;
UInt16 visible:1;
UInt16 poppedUp:1;
UInt16 hasScrollBar:1;
UInt16 search:1;
UInt16 reserved:2;
} ListAttrType;

typedef char *ListDrawDataFuncPtr;

typedef struct {
UInt16 id;
RectangleType bounds;
ListAttrType attr;
Char **itemsText;
Int16 numItems;
Int16 currentItem;
Int16 topItem;
FontID font;
WinHandle popupWin;
ListDrawDataFuncPtr drawItemsCallback;
} ListType;

typedef ListType *ListPtr;

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
UInt16 usable:1;
UInt16 visible:1;
UInt16 hilighted:1;
UInt16 shown:1;
UInt16 activeRegion:4;
} ScrollBarAttrType;

typedef struct {
RectangleType bounds;
UInt16 id;
ScrollBarAttrType attr;
Int16 value;
Int16 minValue;
Int16 maxValue;
Int16 pageSize;
Int16 penPosInCar;
Int16 savePos;
} ScrollBarType;

typedef ScrollBarType *ScrollBarPtr;

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
FormObjectKind objectType;
UInt8 reserved;
FormObjectType object;
} FormObjListType;

typedef struct {
WindowType window;
UInt16 formId;
FormAttrType attr;
WinHandle bitsBehindForm;
FormEventHandlerType *handler;
UInt16 focus;
UInt16 defaultButton;
UInt16 helpRscId;
UInt16 menuRscId;
UInt16 numObjects;
FormObjListType *objects;
} FormType;

typedef FormType *FormPtr;


typedef DWord LocalID;
typedef	VoidPtr DmOpenRef;

typedef struct {
UInt8 attributes;
UInt8 uniqueID[3];
} SortRecordInfoType;
typedef SortRecordInfoType * SortRecordInfoPtr;
typedef Int16 DmComparF(void *, void *, Int16 other, SortRecordInfoPtr, SortRecordInfoPtr, MemHandle appInfoH);

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
UInt16 id;
Char command;
UInt8 hidden:1;
UInt8 reserved:7;   
Char *itemStr;
} MenuItemType;

typedef struct {
WinHandle menuWin;
RectangleType bounds;
WinHandle bitsBehind;
RectangleType titleBounds;
Char *title;
UInt16 hidden:1;
UInt16 numItems:15;
MenuItemType *items;
} MenuPullDownType;

typedef MenuPullDownType *MenuPullDownPtr;

typedef struct {
UInt16 visible:1;
UInt16 commandPending:1;
UInt16 insPtEnabled:1;
UInt16 needsRecalc:1;
} MenuBarAttrType;


typedef struct {
WinHandle barWin;
WinHandle bitsBehind;
WinHandle savedActiveWin;
WinHandle bitsBehindStatus;
MenuBarAttrType	attr;
Int16 curMenu;
Int16 curItem;
Int32 commandTick;
Int16 numMenus;
MenuPullDownPtr	menus;
} MenuBarType;

typedef MenuBarType *MenuBarPtr;

typedef struct {
Int32 high;
Int32 low;
} FlpDouble;

typedef struct {
UInt32 sign:1;
Int32 exp:11;
UInt32 manH:20;
UInt32 manL;
} FlpDoubleBits;

typedef union {
double d;
FlpDouble fd;
UInt32 ul[2];
FlpDoubleBits fdb;
} FlpCompDouble;

typedef struct {
Int16 searchStrLen;
UInt16 dbCardNo;	
LocalID	dbID;
UInt16 recordNum;
UInt16 matchPos;
UInt16 matchFieldNum;
UInt32 matchCustom;
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
UInt8 index;
UInt8 r;
UInt8 g;
UInt8 b;
} RGBColorType;

typedef struct {
UInt32 info[8];
} DmSearchStateType;
typedef DmSearchStateType*	DmSearchStatePtr;

typedef struct {
UInt8 hours;
UInt8 minutes;
} TimeType;

typedef enum {
dfMDYWithSlashes,
dfDMYWithSlashes,
dfDMYWithDots,
dfDMYWithDashes,
dfYMDWithSlashes,
dfYMDWithDots,
dfYMDWithDashes,
dfMDYLongWithComma,
dfDMYLong,
dfDMYLongWithDot,
dfDMYLongNoDay,
dfDMYLongWithComma,
dfYMDLongWithDot,
dfYMDLongWithSpace,
dfMYMed,
dfMYMedNoPost
} DateFormatType;

typedef struct {
Int16 second;
Int16 minute;
Int16 hour;
Int16 day;
Int16 month;
Int16 year;
Int16 weekDay;
} DateTimeType;

typedef DateTimeType *DateTimePtr;

enum clipboardFormats { clipboardText, clipboardInk, clipboardBitmap };
typedef enum clipboardFormats ClipboardFormatType;

#define	sysFtrCreator sysFileCSystem
#define	sysFtrNumROMVersion	1

typedef Int16 _comparF (void *, void *, Int32 other);
typedef _comparF * CmpFuncPtr;

#define SYS_TRAP(x) = { 0x4e4f, x }
#define FLOAT_TRAP(x) = { 0x7400 + x, 0x4e4f, sysTrapFlpDispatch }

void EvtGetEvent(EventType *event, Int32 timeout) SYS_TRAP(sysTrapEvtGetEvent);
void EvtGetPen(Int16 *pScreenX, Int16 *pScreenY, Boolean *pPenDown)	SYS_TRAP(sysTrapEvtGetPen);
void EvtAddEventToQueue(const EventType *event) SYS_TRAP(sysTrapEvtAddEventToQueue);

void FrmDeleteForm(FormType *formP) SYS_TRAP(sysTrapFrmDeleteForm);
void FrmDrawForm(FormType *formP) SYS_TRAP(sysTrapFrmDrawForm);
FormPtr FrmGetActiveForm(void) SYS_TRAP(sysTrapFrmGetActiveForm);
void FrmSetActiveForm(FormType *formP) SYS_TRAP(sysTrapFrmSetActiveForm);
Boolean FrmHandleEvent(FormType *formP, EventType *eventP) SYS_TRAP(sysTrapFrmHandleEvent);
void FrmHelp(UInt16 helpMsgId) SYS_TRAP(sysTrapFrmHelp);
void FrmGotoForm(UInt16 formId) SYS_TRAP(sysTrapFrmGotoForm);
Int16 FrmAlert(UInt16 alertId) SYS_TRAP(sysTrapFrmAlert);
Int16 FrmCustomAlert(UInt16 alertId, const char *s1, const char *s2, const char *s3) SYS_TRAP(sysTrapFrmCustomAlert);
Boolean FrmDispatchEvent(EventType *eventP) SYS_TRAP(sysTrapFrmDispatchEvent);
void FrmSetEventHandler(FormType *formP, FormEventHandlerType *handler) SYS_TRAP(sysTrapFrmSetEventHandler);
Int16 FrmGetObjectIndex(const FormType *formP, UInt16 objID)	SYS_TRAP(sysTrapFrmGetObjectIndex);
VoidPtr FrmGetObjectPtr(const FormType *formP, UInt16 objIndex)	SYS_TRAP(sysTrapFrmGetObjectPtr);
Int16 FrmGetObjectId(const FormType *formP, UInt16 objIndex)	SYS_TRAP(sysTrapFrmGetObjectId);
Int16 FrmDoDialog(FormType *formP) SYS_TRAP(sysTrapFrmDoDialog);
Byte FrmGetControlGroupSelection(const FormType *formP, UInt8 groupNum) SYS_TRAP(sysTrapFrmGetControlGroupSelection);
void FrmSetControlGroupSelection(const FormType *formP, UInt8 groupNum, UInt16 controlID) SYS_TRAP(sysTrapFrmSetControlGroupSelection);
void FrmCloseAllForms(void)	SYS_TRAP(sysTrapFrmCloseAllForms);
FormPtr FrmGetFormPtr(UInt16 formId) SYS_TRAP(sysTrapFrmGetFormPtr);
FormPtr FrmGetFirstForm(void) SYS_TRAP(sysTrapFrmGetFirstForm);
void FrmUpdateScrollers(FormType *formP, UInt16 upIndex, UInt16 downIndex, Boolean scrollableUp, Boolean scrollableDown) SYS_TRAP(sysTrapFrmUpdateScrollers);
FormPtr FrmInitForm(UInt16 rscID) SYS_TRAP(sysTrapFrmInitForm);
void FrmEraseForm(FormType *formP) SYS_TRAP(sysTrapFrmEraseForm);
void FrmSetFocus(FormType *formP, UInt16 fieldIndex) SYS_TRAP(sysTrapFrmSetFocus);
UInt16 FrmGetFocus(const FormType *formP) SYS_TRAP(sysTrapFrmGetFocus);
void FrmGetObjectBounds(const FormType *formP, UInt16 objIndex, RectangleType *rP) SYS_TRAP(sysTrapFrmGetObjectBounds);
void FrmPopupForm(UInt16 formId) SYS_TRAP(sysTrapFrmPopupForm);
void FrmCopyLabel(FormType *formP, UInt16 labelID, const char *newLabel) SYS_TRAP(sysTrapFrmCopyLabel);
void FrmReturnToForm(UInt16 formId) SYS_TRAP(sysTrapFrmReturnToForm);
Int16 FrmGetControlValue(const FormType *formP, UInt16 controlID) SYS_TRAP(sysTrapFrmGetControlValue);
void FrmSetControlValue(const FormType *formP, UInt16 controlID, Int16 newValue) SYS_TRAP(sysTrapFrmSetControlValue);

void LstSetListChoices(ListType *listP, char **itemsText, Int16 numItems) SYS_TRAP(sysTrapLstSetListChoices);
Int16 LstGetSelection(const ListType *listP) SYS_TRAP(sysTrapLstGetSelection);
char *LstGetSelectionText(ListType *listP, Int16 itemNum) SYS_TRAP(sysTrapLstGetSelectionText);
void LstEraseList(ListType *listP) SYS_TRAP(sysTrapLstEraseList);
void LstSetSelection(ListType *listP, Int16 itemNum) SYS_TRAP(sysTrapLstSetSelection);

UInt DmNumDatabases(UInt16 cardNo)	SYS_TRAP(sysTrapDmNumDatabases);
LocalID DmGetDatabase(UInt16 cardNo, UInt16 index) SYS_TRAP(sysTrapDmGetDatabase);
DmOpenRef DmOpenDatabaseByTypeCreator(UInt32 type, UInt32 creator, UInt16 mode) SYS_TRAP(sysTrapDmOpenDatabaseByTypeCreator);
Err DmCreateDatabase(UInt16 cardNo, const char *nameP, UInt32 creator, UInt32 type, Boolean resDB) SYS_TRAP(sysTrapDmCreateDatabase);
Err DmWrite(void *recordP, UInt32 offset, const void *srcP, UInt32 bytes) SYS_TRAP(sysTrapDmWrite);						
Err DmStrCopy(void *recordP, UInt32 offset, const char *srcP) SYS_TRAP(sysTrapDmStrCopy);
Err DmSet(void *recordP, UInt32 offset, UInt32 bytes, UInt8 value) SYS_TRAP(sysTrapDmSet);
UInt DmNumResources(DmOpenRef dbP) SYS_TRAP(sysTrapDmNumResources);
Err DmResourceInfo(DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP, LocalID *chunkLocalIDP) SYS_TRAP(sysTrapDmResourceInfo);
MemHandle DmGetRecord(DmOpenRef dbP, UInt16 index) SYS_TRAP(sysTrapDmGetRecord);
Err DmDetachRecord(DmOpenRef dbP, UInt16 index, MemHandle *oldHP) SYS_TRAP(sysTrapDmDetachRecord);
Err DmReleaseRecord(DmOpenRef dbP, UInt16 index, Boolean dirty) SYS_TRAP(sysTrapDmReleaseRecord);
Err	DmRemoveRecord(DmOpenRef dbP, UInt index) SYS_TRAP(sysTrapDmRemoveRecord);
UInt DmNumRecords(DmOpenRef dbP) SYS_TRAP(sysTrapDmNumRecords);
MemHandle DmNewRecord(DmOpenRef dbP, UIntPtr atP, ULong size) SYS_TRAP(sysTrapDmNewRecord);
MemHandle DmQueryRecord(DmOpenRef dbP, UInt index) SYS_TRAP(sysTrapDmQueryRecord);
MemHandle DmResizeRecord(DmOpenRef dbP, UInt index, ULong newSize) SYS_TRAP(sysTrapDmResizeRecord);
MemHandle DmGetResource(ULong type, Int16 id) SYS_TRAP(sysTrapDmGetResource);
MemHandle DmNewResource(DmOpenRef dbP, ULong resType, DmResID resID, ULong size)	SYS_TRAP(sysTrapDmNewResource);
Err DmReleaseResource(MemHandle resourceH) SYS_TRAP(sysTrapDmReleaseResource);
Err DmRemoveResource(DmOpenRef dbP, UInt16 index) SYS_TRAP(sysTrapDmRemoveResource);
MemHandle DmGetResourceIndex(DmOpenRef dbP, UInt16 index) SYS_TRAP(sysTrapDmGetResourceIndex);
Err DmSetResourceInfo(DmOpenRef dbP, UInt16 index, DmResType *resTypeP, DmResID *resIDP) SYS_TRAP(sysTrapDmSetResourceInfo);
Err DmQuickSort(DmOpenRef dbP, DmComparF *compar, Int16 other) SYS_TRAP(sysTrapDmQuickSort);
UInt16 DmFindResourceType(DmOpenRef dbP, DmResType resType, UInt16 typeIndex)	SYS_TRAP(sysTrapDmFindResourceType);
UInt16 DmFindResource(DmOpenRef dbP, DmResType resType, DmResID resID, MemHandle resH) SYS_TRAP(sysTrapDmFindResource);
Err	DmGetNextDatabaseByTypeCreator(Boolean newSearch, DmSearchStatePtr stateInfoP,
			 		UInt32 type, UInt32 creator, Boolean onlyLatestVers, UInt16 *cardNoP, LocalID *dbIDP) SYS_TRAP(sysTrapDmGetNextDatabaseByTypeCreator);
DmOpenRef DmOpenDatabase(UInt16 cardNo, LocalID dbID, UInt16 mode) SYS_TRAP(sysTrapDmOpenDatabase);
Err DmCloseDatabase(DmOpenRef dbP) SYS_TRAP(sysTrapDmCloseDatabase);
LocalID	DmFindDatabase(UInt16 cardNo, const char *nameP) SYS_TRAP(sysTrapDmFindDatabase);
Err DmDatabaseInfo(UInt16 cardNo, LocalID	dbID, char *nameP,
					UInt16 *attributesP, UInt16 *versionP, UInt32 *crDateP,
					UInt32 *	modDateP, UInt32 *bckUpDateP,
					UInt32 *	modNumP, LocalID *appInfoIDP,
					LocalID *sortInfoIDP, UInt32 *typeP,
					UInt32 *creatorP) SYS_TRAP(sysTrapDmDatabaseInfo);
Err DmSetDatabaseInfo(UInt16 cardNo, LocalID	dbID, const char *nameP,
					UInt16 *attributesP, UInt16 *versionP, UInt32 *crDateP,
					UInt32 *	modDateP, UInt32 *bckUpDateP,
					UInt32 *	modNumP, LocalID *appInfoIDP,
					LocalID *sortInfoIDP, UInt32 *typeP,
					UInt32 *creatorP) SYS_TRAP(sysTrapDmSetDatabaseInfo);
Err DmDatabaseSize(UInt16 cardNo, LocalID dbID, UInt32 *numRecordsP,
					UInt32 *totalBytesP, UInt32 *dataBytesP) SYS_TRAP(sysTrapDmDatabaseSize);
Err DmDeleteDatabase(UInt16 cardNo, LocalID dbID) SYS_TRAP(sysTrapDmDeleteDatabase);

MemPtr MemHandleLock(MemHandle h) SYS_TRAP(sysTrapMemHandleLock);							
Err MemHandleUnlock(MemHandle h)	SYS_TRAP(sysTrapMemHandleUnlock);
ULong MemHandleSize(MemHandle h) SYS_TRAP(sysTrapMemHandleSize);
MemHandle MemHandleNew(UInt32 size) SYS_TRAP(sysTrapMemHandleNew);
Err	MemHandleResize(MemHandle h, UInt32 newSize) SYS_TRAP(sysTrapMemHandleResize);
Err MemHandleFree(MemHandle h) SYS_TRAP(sysTrapMemHandleFree);
UInt16 MemHandleLockCount(MemHandle h) SYS_TRAP(sysTrapMemHandleLockCount);
MemPtr MemPtrNew(UInt32 size) SYS_TRAP(sysTrapMemPtrNew);
Err MemPtrFree(MemPtr chunkDataP) SYS_TRAP(sysTrapMemChunkFree);
Err	MemPtrUnlock(MemPtr p) SYS_TRAP(sysTrapMemPtrUnlock);
Err MemMove(void *dstP, const void *sP, Int32 numBytes) SYS_TRAP(sysTrapMemMove);
Err MemSet(void *dstP, Int32 numBytes, UInt8 value) SYS_TRAP(sysTrapMemSet);
							


WinHandle WinCreateOffscreenWindow(Coord width, Coord height, WindowFormatType format, UInt16 *error) SYS_TRAP(sysTrapWinCreateOffscreenWindow);
WinHandle WinSetDrawWindow(WinHandle winHandle) SYS_TRAP(sysTrapWinSetDrawWindow);
void WinDeleteWindow(WinHandle winHandle, Boolean eraseIt) SYS_TRAP(sysTrapWinDeleteWindow);
void WinDrawBitmap(BitmapPtr bitmapP, Coord x, Coord y) SYS_TRAP(sysTrapWinDrawBitmap);
void WinDrawChars(const char *chars, Int16 len, Coord x, Coord y) SYS_TRAP(sysTrapWinDrawChars);
void WinDrawInvertedChars(const char *chars, Int16 len, Coord x, Coord y) SYS_TRAP(sysTrapWinDrawInvertedChars);
void WinEraseLine(Coord x1, Coord y1, Coord x2, Coord y2) SYS_TRAP(sysTrapWinEraseLine);
void WinInvertLine(Coord x1, Coord y1, Coord x2, Coord y2) SYS_TRAP(sysTrapWinInvertLine);
void WinFillLine(Coord x1, Coord y1, Coord x2, Coord y2) SYS_TRAP(sysTrapWinFillLine);
void WinDrawLine(Coord x1, Coord y1, Coord x2, Coord y2) SYS_TRAP(sysTrapWinDrawLine);
void WinDrawGrayLine(Coord x1, Coord y1, Coord x2, Coord y2) SYS_TRAP(sysTrapWinDrawGrayLine);
void WinPaintRectangle(const RectangleType *rP, UInt16 cornerDiam) SYS_TRAP(sysTrapWinPaintRectangle);
void WinDrawRectangle(const RectangleType *rP, UInt16 cornerDiam) SYS_TRAP(sysTrapWinDrawRectangle);
void WinEraseRectangle(const RectangleType *rP, UInt16 cornerDiam) SYS_TRAP(sysTrapWinEraseRectangle);
void WinInvertRectangle(const RectangleType *rP, UInt16 cornerDiam) SYS_TRAP(sysTrapWinInvertRectangle);
void WinFillRectangle(const RectangleType *rP, UInt16 cornerDiam) SYS_TRAP(sysTrapWinFillRectangle);
void WinDrawRectangleFrame(FrameType frame, const RectangleType *rP) SYS_TRAP(sysTrapWinDrawRectangleFrame);
void WinInvertRectangleFrame(FrameType frame, const RectangleType *rP)	SYS_TRAP(sysTrapWinInvertRectangleFrame);
void WinCopyRectangle(WinHandle srcWin, WinHandle dstWin, const RectangleType *srcRect, Coord destX, Coord destY, WinDrawOperation mode) SYS_TRAP(sysTrapWinCopyRectangle);
void WinSetClip(const RectangleType *rP) SYS_TRAP(sysTrapWinSetClip);
void WinResetClip(void)	SYS_TRAP(sysTrapWinResetClip);
void WinScrollRectangle(const RectangleType *rP, WinDirectionType direction, Coord distance, RectangleType *vacatedP) SYS_TRAP(sysTrapWinScrollRectangle);
IndexedColorType WinSetForeColor(IndexedColorType foreColor) SYS_TRAP(sysTrapWinSetForeColor);
IndexedColorType WinSetBackColor(IndexedColorType backColor) SYS_TRAP(sysTrapWinSetBackColor);
Err WinScreenMode(WinScreenModeOperation operation, UInt32 *widthP, UInt32 *heightP, UInt32 *depthP, Boolean *enableColorP) SYS_TRAP(sysTrapScrDisplayMode);
void WinPushDrawState(void) SYS_TRAP(sysTrapWinPushDrawState);
void WinPopDrawState(void) SYS_TRAP(sysTrapWinPopDrawState);
IndexedColorType WinSetTextColor(IndexedColorType textColor) SYS_TRAP(sysTrapWinSetTextColor);
IndexedColorType WinRGBToIndex(const RGBColorType *rgbP) SYS_TRAP(sysTrapWinRGBToIndex);
Err UIColorSetTableEntry(UIColorTableEntries which, const RGBColorType *rgbP) SYS_TRAP(sysTrapUIColorSetTableEntry);
WinHandle WinGetActiveWindow(void) SYS_TRAP(sysTrapWinGetActiveWindow);
void WinSetPattern(CustomPatternType) SYS_TRAP(sysTrapWinSetPattern);
WinHandle WinCreateWindow(RectanglePtr bounds, FrameType frame, Boolean modal, Boolean focusable, WordPtr error) SYS_TRAP(sysTrapWinCreateWindow);

BitmapType *BmpCreate(Coord width, Coord height, UInt8 depth, ColorTableType *colortableP, UInt16 *error) SYS_TRAP(sysTrapBmpCreate);
Err BmpDelete(BitmapType *bitmapP) SYS_TRAP(sysTrapBmpDelete);
void *BmpGetBits(BitmapType *bitmapP) SYS_TRAP(sysTrapBmpGetBits);


void SndPlaySystemSound(SndSysBeepType beepID) SYS_TRAP(sysTrapSndPlaySystemSound);

MenuBarPtr MenuInit(UInt16 resourceId) SYS_TRAP(sysTrapMenuInit);
Boolean MenuHandleEvent(MenuBarType *menuP, EventType *event, UInt16 *error) SYS_TRAP(sysTrapMenuHandleEvent);
void MenuDispose(MenuBarType *menuP) SYS_TRAP(sysTrapMenuDispose);
void MenuEraseStatus(MenuBarType *menuP) SYS_TRAP(sysTrapMenuEraseStatus);
MenuBarPtr MenuGetActiveMenu(void) SYS_TRAP(sysTrapMenuGetActiveMenu);
MenuBarPtr MenuSetActiveMenu(MenuBarType *menuP) SYS_TRAP(sysTrapMenuSetActiveMenu);

CharPtr StrCopy(char *dst, const char *src) SYS_TRAP(sysTrapStrCopy);
CharPtr StrNCopy(char *dst, const char *src, Int16 n) SYS_TRAP(sysTrapStrNCopy);
CharPtr StrCat(char *dst, const char *src) SYS_TRAP(sysTrapStrCat);
CharPtr StrNCat(char *dst, const char *src, Int16 n) SYS_TRAP(sysTrapStrNCat);
UInt StrLen(const char *src) SYS_TRAP(sysTrapStrLen);
Int16 StrCompare(const char* s1, const char* s2) SYS_TRAP(sysTrapStrCompare);
Int16 StrNCompare(const char* s1, const char* s2, DWord n) SYS_TRAP(sysTrapStrNCompare);
CharPtr StrToLower(char *dst, const char *src) SYS_TRAP(sysTrapStrToLower);
CharPtr StrIToA(char *s, Int32 i) SYS_TRAP(sysTrapStrIToA);
CharPtr StrIToH(char *s, UInt32 i) SYS_TRAP(sysTrapStrIToH);
CharPtr StrChr(const char *str, WChar chr) SYS_TRAP(sysTrapStrChr);
CharPtr StrStr(const char *str, const char *token) SYS_TRAP(sysTrapStrStr);
long StrAToI(const char *str) SYS_TRAP(sysTrapStrAToI);
Int16 StrPrintF(char *s, const char *formatStr, ...) SYS_TRAP(sysTrapStrPrintF);							
Int16 StrVPrintF(char *s, const char *formatStr, VoidPtr arg) SYS_TRAP(sysTrapStrVPrintF);

void CtlHideControl(ControlType *controlP) SYS_TRAP(sysTrapCtlHideControl);
void CtlShowControl(ControlType *controlP) SYS_TRAP(sysTrapCtlShowControl);
Int16 CtlGetValue(ControlType *controlP) SYS_TRAP(sysTrapCtlGetValue);
void CtlSetValue(ControlType *controlP, Int16 newValue) SYS_TRAP(sysTrapCtlSetValue);
void CtlSetEnabled(ControlType *controlP, Boolean usable) SYS_TRAP(sysTrapCtlSetEnabled);

void FldGetAttributes(const FieldType *fldP, FieldAttrPtr attrP) SYS_TRAP(sysTrapFldGetAttributes);
void FldSetAttributes(FieldType *fldP, const FieldAttrType *attrP) SYS_TRAP(sysTrapFldSetAttributes);
void FldGrabFocus(FieldType *fldP) SYS_TRAP(sysTrapFldGrabFocus);
void FldReleaseFocus(FieldType *fldP) SYS_TRAP(sysTrapFldReleaseFocus);
MemHandle FldGetTextHandle(FieldType *fldP) SYS_TRAP(sysTrapFldGetTextHandle);
void FldSetText(FieldType *fldP, MemHandle textHandle, UInt16 offset, UInt16 size)	SYS_TRAP(sysTrapFldSetText);
void FldSetTextHandle(FieldType *fldP, MemHandle textHandle) SYS_TRAP(sysTrapFldSetTextHandle);
CharPtr FldGetTextPtr(const FieldType *fldP) SYS_TRAP(sysTrapFldGetTextPtr);
void FldDrawField(FieldType *fldP) SYS_TRAP(sysTrapFldDrawField);
void FldEraseField(FieldType *fldP) SYS_TRAP(sysTrapFldEraseField);
Boolean FldHandleEvent(FieldType *fldP, EventType *eventP) SYS_TRAP(sysTrapFldHandleEvent);
UInt16 FldGetTextLength(const FieldType *fldP) SYS_TRAP(sysTrapFldGetTextLength);
void FldCopy(const FieldType *fldP) SYS_TRAP(sysTrapFldCopy);
void FldCut(FieldType *fldP) SYS_TRAP(sysTrapFldCut);
void FldPaste(FieldType *fldP) SYS_TRAP(sysTrapFldPaste);
void FldUndo(FieldType *fldP) SYS_TRAP(sysTrapFldUndo);
void FldDelete(FieldType *fldP, UInt16 start, UInt16 end) SYS_TRAP(sysTrapFldDelete);
void FldSetUsable(FieldType *fldP, Boolean usable) SYS_TRAP(sysTrapFldSetUsable);
void FldGetSelection(const FieldType *fldP, UInt16 *startPosition, UInt16 *endPosition)	SYS_TRAP(sysTrapFldGetSelection);
void FldSetSelection(FieldType *fldP, UInt16 startPosition, UInt16 endPosition) SYS_TRAP(sysTrapFldSetSelection);

void ClipboardAddItem(const ClipboardFormatType format, const void *ptr, UInt16 length) SYS_TRAP(sysTrapClipboardAddItem);
Err ClipboardAppendItem(const ClipboardFormatType format, const void *ptr, UInt16 length) SYS_TRAP(sysTrapClipboardAppendItem);
MemHandle ClipboardGetItem(const ClipboardFormatType format, UInt16 *length) SYS_TRAP(sysTrapClipboardGetItem);

Int16 PrefGetAppPreferences(UInt32 creator, UInt16 id, void *prefs, UInt16 *prefsSize, Boolean saved) SYS_TRAP(sysTrapPrefGetAppPreferences);
void PrefSetAppPreferences(UInt32 creator, UInt16 id, Int16 version, void *prefs, UInt16 prefsSize, Boolean saved) SYS_TRAP(sysTrapPrefSetAppPreferences);

Err FtrGet(UInt32 creator, UInt16 featureNum, UInt32 *valueP)	SYS_TRAP(sysTrapFtrGet);
Err FtrSet(UInt32 creator, UInt16 featureNum, UInt32 newValue) SYS_TRAP(sysTrapFtrSet);
Err FtrUnregister(UInt32 creator, UInt16 featureNum) SYS_TRAP(sysTrapFtrUnregister);

UInt32 KeyCurrentState(void) SYS_TRAP(sysTrapKeyCurrentState);

Boolean SysHandleEvent(EventPtr eventP)	SYS_TRAP(sysTrapSysHandleEvent);
void SysInsertionSort(void *baseP, Int16 numOfElements, Int16 width, const CmpFuncPtr comparF, const Int32 other) SYS_TRAP(sysTrapSysInsertionSort);
Int16 SysRandom(Int32 newSeed) SYS_TRAP(sysTrapSysRandom);
Err SysTaskDelay(Int32 delay) SYS_TRAP(sysTrapSysTaskDelay);

UInt32 TimGetTicks(void) SYS_TRAP(sysTrapTimGetTicks);
UInt32 TimGetSeconds(void) SYS_TRAP(sysTrapTimGetSeconds);
void TimSecondsToDateTime(UInt32 seconds, DateTimePtr dateTimeP) SYS_TRAP(sysTrapTimSecondsToDateTime);
Boolean SelectTime(TimeType *startTimeP, TimeType *EndTimeP, Boolean untimed, const char *titleP, Int16 startOfDay, Int16 endOfDay, Int16 startOfDisplay) SYS_TRAP(sysTrapSelectTime);
void DateToAscii(UInt8 months, UInt8 days, UInt16 years, DateFormatType dateFormat, char *pString) SYS_TRAP(sysTrapDateToAscii);

Int16 FntSetFont(FontID fontID) SYS_TRAP(sysTrapFntSetFont);
Int16 FntCharsWidth(char *chars, Word len) SYS_TRAP(sysTrapFntCharsWidth);
Int16 FntCharWidth(const char ch) SYS_TRAP(sysTrapFntCharWidth);
Int16 FntCharHeight(void) SYS_TRAP(sysTrapFntCharHeight);
Int16 FntDescenderHeight(void) SYS_TRAP(sysTrapFntDescenderHeight);

Err FlpFToA(FlpDouble a, char* s) FLOAT_TRAP(1);
FlpDouble FlpAToF(char* s) FLOAT_TRAP(2);

void SclSetScrollBar(const ScrollBarPtr bar, Int16 value, const Int16 min, const Int16 max, const Int16 pageSize) SYS_TRAP(sysTrapSclSetScrollBar);

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

Err SysLibLoad(UInt32 libType, UInt32 libCreator, UInt16 *refNumP) SYS_TRAP(sysTrapSysLibLoad);
Err SysLibRemove(UInt16 refNum) SYS_TRAP(sysTrapSysLibRemove);
Err SysLibFind(const char *nameP, UInt16 *refNumP) SYS_TRAP(sysTrapSysLibFind);

Err MathLibOpen(UInt16 refnum, UInt16 version) SYS_TRAP(sysLibTrapOpen);
Err MathLibClose(UInt16 refnum, UInt16 *usecountP) SYS_TRAP(sysLibTrapClose);

Err MathLibPow(UInt16 refnum, double x, double y, double *result) SYS_TRAP(sysLibTrapCustom+24);
Err MathLibSqrt(UInt16 refnum, double x, double *result) SYS_TRAP(sysLibTrapCustom+25);

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


