//
// SCells is a freeware program for HSPascal.
// SCells Version 1.3 - October 26, 2005 - Made by Laurent Duveau
//       Web Site = http://aldweb.free.fr
//       e-Mail   = aldweb@free.fr
//
// SCells is based on the source code of Cells freeware.
// Cells Version 1.6 - September 18, 2002 - Made by Laurent Duveau
//
// SCells was compiled with the great HSPascal compiler
// for Palm OS handheld devices
//       Web Site = http://HSPascal.Fihl.net
//       e-Mail   = Christen@Fihl.net
//
// The original source code of Cells was slightly modified
// for Speedy tests purposes, and the program was renamed
// as SCells for no confusion making.
//


Program SCells;


{$SearchPath Units; Units\UI; Units\System}
{$ApplName SCells,LDsC}
// LDsC is a referenced PalmOS CreatorID


Uses
  Window, Form, Menu, Rect, Event, SysEvent, SystemMgr, FloatMgr, HSUtils,
  TimeMgr, Preferences, Bitmap;


{$R .\CellsRes.ro}

Resource
  MenuRes=(ResMBAR,,
    (ResMPUL,(6,14,85,93),(4,0,35,12),'Game',
      MenuNewGame=(,'G','New Game'),
      MenuLoad1=(,'1','Load #1'),
      MenuLoad2=(,'2','Load #2'),
      MenuLoad3=(,'3','Load #3'),
      MenuSave1=(,'4','Save #1'),
      MenuSave2=(,'5','Save #2'),
      MenuSave3=(,'6','Save #3'),
      MenuSpace1=(,'','-'),
      MenuQuit=(,'X','Exit')),
    (ResMPUL,(42,14,90,82),(40,0,47,12),'Options',
      MenuEditCurrent=(,'C','Edit Current'),
      MenuEditNew=(,'N','Edit New'),
      MenuEndEdit=(,'E','End Edit'),
      MenuSpace2=(,'','-'),
      MenuFilling=(,'F','Filling'),
      MenuSpeed=(,'S','Speed'),
      MenuSize=(,'I','Cell Size'),
      MenuColor=(,'L','Cell Color')),
    (ResMPUL,(85,14,73,49),(88,0,30,12),'Help',
      MenuHelp=(,'H','Help'),
      MenuRules=(,'R','Rules'),
      MenuSpace3=(,'','-'),
      MenuDonate=(,'D','Donate...'),

      MenuAbout=(,'A','About')));


  MainForm=(ResTFRM,1000,(0,0,160,160),0,0,MenuRes, (FormTitle,'SCells'));

  Help1=(ResTalt,,0,0,0,'Cells - Help','Cells is a port of the popular "Game of '+
          'Life" invented in 1970 by John Conway.'#10#10+
          'In an automata universe, cells follow very basic rules to survive, be born '+
          'or die in a turn based simulation.','OK');
  Rule1=(ResTalt,,0,0,0,'Cells - Rules','Survival:'#10'If a cell has 2 or 3 alive cells '+
         'next to it, it will survive. Otherwise, it will die.'#10#10'Birth:'#10+
         'If an empty space is surrounded by 3 cells, it will come up to life.','OK');
  HelpAbout1=(ResTSTR,,'Cells is a sample freeware program compiled with the great '+
              'HSPascal compiler for Palm OS handheld devices.'#10+
              'HSPascal can be found here:'#10'http://HSPascal.Fihl.net'#10#10+
              'The source code of Cells is available for download on my web site.');
  HelpAbout2=(ResTSTR,,'Cells is free to use. However, if you like it, please '+
              'consider making a donation to show your support.'#10+
              'Any amount will be greatly appreciated.'#10#10+
              'To proceed, just connect to:'#10'www.aldweb.com/give.html'#10+
              '(secure PayPal transaction)');
  About1=(ResTalt,,0,HelpAbout1,0,'Cells - About', 'Cells  v1.6'#10+
          #9'September 18, 2002'#10#9'by Laurent Duveau'#10#10+
          'Visit my Web site:'#10#9'www.aldweb.com'#10#10+
          'e-Mail me:'#10#9'info@aldweb.com','OK','Donate...');
  StartNewGame1=(ResTalt,,1,0,1,'Cells - New game','Do you really want to start '+
                 'a new simulation ?','Yes','No');
  HelpSpeed1=(ResTSTR,,'Speed option sets the time that the Palm will wait before '+
              'moving to the next generation of Cells.'#10#10+
              'If set to "Manual", you will have to tick on the screen to move to '+
              'the next generation.');
  Speed1=(ResTalt,,1,HelpSpeed1,0,'Cells - Speed','Current speed is :'#10#9'0 second'+
          #10#10'Choose a new speed :','0 sec','1 sec','2 sec','Manual');
  Speed2=(ResTalt,,1,HelpSpeed1,1,'Cells - Speed','Current speed is :'#10#9'1 second'+
          #10#10'Choose a new speed :','0 sec','1 sec','2 sec','Manual');
  Speed3=(ResTalt,,1,HelpSpeed1,2,'Cells - Speed','Current speed is :'#10#9'2 seconds'+
          #10#10'Choose a new speed :','0 sec','1 sec','2 sec','Manual');
  Speed4=(ResTalt,,1,HelpSpeed1,3,'Cells - Speed','Current speed is :'#10#9'Manual'+
          #10#10'Choose a new speed :','0 sec','1 sec','2 sec','Manual');
  HelpFilling1=(ResTSTR,,'Filling option sets the initial percentage of spaces to be '+
                 'turned into Cells at the beginning of the game.'#10#10+
                 'This setup will be used next time you start a new game.');
  Filling1=(ResTalt,,1,HelpFilling1,0,'Cells - Filling','Current initial filling is :'#10#9'10%'+
            #10#10'Choose a new filling :','10%','15%','20%','25%');
  Filling2=(ResTalt,,1,HelpFilling1,1,'Cells - Filling','Current initial filling is :'#10#9'15%'+
            #10#10'Choose a new filling :','10%','15%','20%','25%');
  Filling3=(ResTalt,,1,HelpFilling1,2,'Cells - Filling','Current initial filling is :'#10#9'20%'+
            #10#10'Choose a new filling :','10%','15%','20%','25%');
  Filling4=(ResTalt,,1,HelpFilling1,3,'Cells - Filling','Current initial filling is :'#10#9'25%'+
            #10#10'Choose a new filling :','10%','15%','20%','25%');
  CellSize1=(ResTalt,,1,0,0,'Cells - Size','Current size of cells is :'#10#9'Small'+
             #10#10'Choose a new size :','Small','Medium','Big');
  CellSize2=(ResTalt,,1,0,1,'Cells - Size','Current size of cells is :'#10#9'Medium'+
             #10#10'Choose a new size :','Small','Medium','Big');
  CellSize3=(ResTalt,,1,0,2,'Cells - Size','Current size of cells is :'#10#9'Big'+
             #10#10'Choose a new size :','Small','Medium','Big');
  CellColor0=(ResTalt,,1,0,0,'Cells - Color','Current color of cells is :'#10#9'Black'+
              #10#10'This color cannot be changed because of your device.','OK');
  CellColor1=(ResTalt,,1,0,0,'Cells - Color','Current color of cells is :'#10#9'Black'+
              #10#10'Choose a new color :','Black','Blue','Green','Red');
  CellColor2=(ResTalt,,1,0,0,'Cells - Color','Current color of cells is :'#10#9'Blue'+
              #10#10'Choose a new color :','Black','Blue','Green','Red');
  CellColor3=(ResTalt,,1,0,0,'Cells - Color','Current color of cells is :'#10#9'Green'+
              #10#10'Choose a new color :','Black','Blue','Green','Red');
  CellColor4=(ResTalt,,1,0,0,'Cells - Color','Current color of cells is :'#10#9'Red'+
              #10#10'Choose a new color :','Black','Blue','Green','Red');
  NoLoad1=(ResTalt,,2,0,0,'Cells - Load Game','No saved game #1 yet.','OK');
  NoLoad2=(ResTalt,,2,0,0,'Cells - Load Game','No saved game #2 yet.','OK');
  NoLoad3=(ResTalt,,2,0,0,'Cells - Load Game','No saved game #3 yet.','OK');
  ReallySave1=(ResTalt,,1,0,1,'Cells - Save Game','Game #1 already contains a saved game. '+
               'Overwrite saved game #1 with current data ?','Yes','No');
  ReallySave2=(ResTalt,,1,0,1,'Cells - Save Game','Game #2 already contains a saved game. '+
               'Overwrite saved game #2 with current data ?','Yes','No');
  ReallySave3=(ResTalt,,1,0,1,'Cells - Save Game','Game #3 already contains a saved game. '+
               'Overwrite saved game #3 with current data ?','Yes','No');
  Saved1=(ResTalt,,0,0,0,'Cells - Save Game','Game #1 saved.','OK');
  Saved2=(ResTalt,,0,0,0,'Cells - Save Game','Game #2 saved.','OK');
  Saved3=(ResTalt,,0,0,0,'Cells - Save Game','Game #3 saved.','OK');
  BadOSVersion=(ResTalt,,2,0,0,'Cells','^1 ^2 ^3','Done');

  ResultWindow=(ResTalt,,0,0,0,'SCells - Timer Results','^1 ^2 ^3','Ok');

  (ResTAIN,1000,'SCells');
  (ResTVER,1000,'1.2');


Const
  CreatorID=$4C445343;      // LDSC
  AppName='SCells';
  MinOSVer=V200;

  CellXmaxSize = 53;
  CellYmaxSize = 48;


Type
  TStatus = record
              Previous : Boolean;
              Current  : Boolean;
            end;
  TCells = Array[0..CellXmaxSize+1,0..CellYmaxSize+1] of TStatus;



Var
  MyMenu: MenuBarPtr;
  WorkRect: RectangleType;
  FormLoad,FormOpen,DoStop,TickDown,Editor,InColor: Boolean;
  DelaySeed,Speed,Filling,CellSize,CellColor,CellXmax,CellYmax: Integer;
  Cells: TCells;
  SavedGame: array[0..3] of Boolean;
  ColorRGB: Array[0..3] of IndexedColorType;

  DlySeed: LongInt;


Procedure StartTimer;
begin
  DlySeed:=TimGetSeconds;
end;

Function StopTimer: LongInt;
begin
  StopTimer:=TimGetSeconds-DlySeed;
end;


Procedure ApplyCellsColor;
Var
  IndexedColor: IndexedColorType;
begin
  if InColor then
    IndexedColor:=WinSetForeColor(ColorRGB[CellColor]);
end;


Procedure InitCurrentCells(StartX,StartY: Integer);
Var
  X,Y: Integer;
begin
  for X:=1 to CellXmaxSize do
    for Y:=1 to CellYmaxSize do
      if (X>=StartX) or (Y>=StartY)
        then Cells[X,Y].Current:=False;
end;


Procedure CalcCellSize;
Var
  X,Y: Integer;
begin
  CellXmax:= 160 div CellSize;
  CellYmax:= 144 div CellSize;
  InitCurrentCells(CellXmax+1,CellYmax+1);
end;


Procedure DrawCell(X,Y: Integer; DrawIt: Boolean);
Var
  Rec: RectangleType;
begin
  With Rec do begin
    topLeft.X := X;
    topLeft.y := Y;
    extent.x  := CellSize-1;
    extent.y  := CellSize-1;
    if DrawIt then
      WinDrawRectangle(Rec,0)
    else
      WinEraseRectangle(Rec,0);
   end;
end;


Procedure DrawGameBoard;
Var
  X,Y: Integer;
begin
  ApplyCellsColor;
  for X:=0 to CellXmax-1 do
    for Y:=0 to CellYmax-1 do
      if Cells[X+1,Y+1].Current<>Cells[X+1,Y+1].Previous then
        if Cells[X+1,Y+1].Current then
          DrawCell(X*CellSize,17+Y*CellSize,True)
        else
          DrawCell(X*CellSize,17+Y*CellSize,False);
end;


Procedure EditCell(X,Y:Integer);
begin
  X:=1+X div CellSize;
  Y:=1+(Y-17) div CellSize;
  Cells[X,Y].Previous:=Cells[X,Y].Current;
  Cells[X,Y].Current:=not(Cells[X,Y].Current);
  DrawGameBoard;
end;


Procedure InitPreviousCells;
Var
  X,Y: Integer;
begin
  for X:=0 to CellXmaxSize+1 do

    for Y:=0 to CellYmaxSize+1 do
      Cells[X,Y].Previous:=False;
end;


Procedure EraseDrawBoard;
begin
  InitPreviousCells;
  WinEraseRectangle(WorkRect, 0);
  DrawGameBoard;
end;


Procedure InitCells;
Var
  X,Y: Integer;
begin
  InitCurrentCells(0,0);
  for X:=1 to CellXmax do
    for Y:=1 to CellYmax do
      if Random(100)<5*(Filling+2) then
        Cells[X,Y].Current:=True
      else
        Cells[X,Y].Current:=False;
  EraseDrawBoard;
end;


Procedure ReallySavePreferences(GameID:Integer);
Var
  N: Integer;
begin
  if GameID=0 then begin
    case Speed of
      0: begin
           Cells[0,0].Previous:=False;
           Cells[0,1].Previous:=False;
         end;
      1: begin
           Cells[0,0].Previous:=True;
           Cells[0,1].Previous:=False;
         end;
      2: begin
           Cells[0,0].Previous:=False;
           Cells[0,1].Previous:=True;
         end;
      3: begin
           Cells[0,0].Previous:=True;
           Cells[0,1].Previous:=True;
         end;
    end;
    case Filling of
      0: begin
           Cells[0,2].Previous:=False;
           Cells[0,3].Previous:=False;
         end;
      1: begin
           Cells[0,2].Previous:=True;
           Cells[0,3].Previous:=False;
         end;
      2: begin
           Cells[0,2].Previous:=False;
           Cells[0,3].Previous:=True;
         end;
      3: begin
           Cells[0,2].Previous:=True;
           Cells[0,3].Previous:=True;
         end;
    end;
    Cells[0,4].Previous:=Editor;
    Cells[0,7].Previous:=SavedGame[1];
    Cells[0,8].Previous:=SavedGame[2];
    Cells[0,9].Previous:=SavedGame[3];
  end;
  case CellSize of
    3: begin
         Cells[0,5].Previous:=False;
         Cells[0,6].Previous:=False;
       end;
    4: begin
         Cells[0,5].Previous:=True;
         Cells[0,6].Previous:=False;
       end;
    5: begin
         Cells[0,5].Previous:=False;
         Cells[0,6].Previous:=True;
       end;
    end;
  case CellColor of
    0: begin
         Cells[0,10].Previous:=False;
         Cells[0,11].Previous:=False;


       end;
    1: begin
         Cells[0,10].Previous:=True;
         Cells[0,11].Previous:=False;
       end;
    2: begin
         Cells[0,10].Previous:=False;
         Cells[0,11].Previous:=True;
       end;
    3: begin
         Cells[0,10].Previous:=True;
         Cells[0,11].Previous:=True;
       end;
    end;
  PrefSetAppPreferences(CreatorID,GameID,0,@Cells,SizeOf(Cells),True);
  SavedGame[GameID]:=True;
  case GameID of
    1: N:=FrmAlert(Saved1);
    2: N:=FrmAlert(Saved2);
    3: N:=FrmAlert(Saved3);
  end;
end;


Procedure SavePreferences(GameID:Integer);
Var
  N: Integer;
begin
  N:=0;
  if SavedGame[GameID] then
    case GameID of
      1: N:=FrmAlert(ReallySave1);
      2: N:=FrmAlert(ReallySave2);
      3: N:=FrmAlert(ReallySave3);
    end;
  if N=0 then
    ReallySavePreferences(GameID);
end;


Procedure LoadPreferences(GameID:Integer);
Var
  Size,N: Integer;
begin
  Size:=SizeOf(Cells);
  N:=PrefGetAppPreferences(CreatorID,GameID,@Cells,Size,True);
  if N<>noPreferenceFound then begin
    if GameID=0 then begin
      Speed:=Byte(Cells[0,0].Previous)+2*Byte(Cells[0,1].Previous);
      Filling:=Byte(Cells[0,2].Previous)+2*Byte(Cells[0,3].Previous);
      Editor:=Cells[0,4].Previous;
      SavedGame[1]:=Cells[0,7].Previous;
      SavedGame[2]:=Cells[0,8].Previous;
      SavedGame[3]:=Cells[0,9].Previous;
    end;
    CellSize:=3+Byte(Cells[0,5].Previous)+2*Byte(Cells[0,6].Previous);
    CellColor:=Byte(Cells[0,10].Previous)+2*Byte(Cells[0,11].Previous);
    CalcCellSize;
    EraseDrawBoard;
  end
  else
    case GameID of
      0: InitCells;
      1: N:=FrmAlert(NoLoad1);
      2: N:=FrmAlert(NoLoad2);
      3: N:=FrmAlert(NoLoad3);
    end;
end;


Procedure InitColors;
Var
  RGB: RGBColorType;
begin
  RGB.R:=0;
  RGB.G:=0;
  RGB.B:=0;
  ColorRGB[0]:=WinRGBToIndex(RGB);
  RGB.R:=0;
  RGB.G:=0;
  RGB.B:=255;
  ColorRGB[1]:=WinRGBToIndex(RGB);
  RGB.R:=51;
  RGB.G:=153;
  RGB.B:=51;
  ColorRGB[2]:=WinRGBToIndex(RGB);
  RGB.R:=255;
  RGB.G:=0;
  RGB.B:=0;
  ColorRGB[3]:=WinRGBToIndex(RGB);
end;


Procedure InitVar;
Var
  WidthP,HeightP,DepthP: UInt32;
  EnableColorP: Boolean;
  Error: Err;
begin
  DelaySeed:=TimGetSeconds;
  FormLoad:=False;
  FormOpen:=False;
  TickDown:=False;
  DoStop:=False;
  Speed:=0;
  Filling:=1;
  SavedGame[0]:=False;
  SavedGame[1]:=False;
  SavedGame[2]:=False;
  SavedGame[3]:=False;
  Editor:=False;
  CellSize:=3;
  CalcCellSize;
  CellColor:=0;
  if VersionSupported(V350) then begin
    Error:=WinScreenMode(winScreenModeGet,WidthP,HeightP,DepthP,EnableColorP);
    InColor:=(DepthP>=8);
    if InColor then
      InitColors;
  end
  else
    InColor:=False;
end;


Function CalcDelay(NbSec:Integer):Boolean;
Var
  Delay: Integer;
begin
  CalcDelay:=False;
  Delay:=TimGetSeconds-DelaySeed;
  if NbSec<=Delay then begin
    DelaySeed:=TimGetSeconds;
    CalcDelay:=True;
  end;
end;


Procedure NextGeneration;
Var
  X,Y: Integer;
  N : Integer;
begin
  for X:=1 to CellXmax do
    for Y:=1 to CellYmax do
      Cells[X,Y].Previous:=Cells[X,Y].Current;
  for X:=1 to CellXmax do
    for Y:=1 to CellYmax do begin
      N:=Byte(Cells[X-1,Y-1].Previous)+Byte(Cells[X,Y-1].Previous)+
         Byte(Cells[X+1,Y-1].Previous)+Byte(Cells[X-1,Y].Previous)+
         Byte(Cells[X+1,Y].Previous)+Byte(Cells[X-1,Y+1].Previous)+
         Byte(Cells[X,Y+1].Previous)+Byte(Cells[X+1,Y+1].Previous);
      Cells[X,Y].Current:=False;
      if Cells[X,Y].Previous then
        if ((N=2) or (N=3)) then
          Cells[X,Y].Current:=True;
      if (not(Cells[X,Y].Previous) and (N=3)) then
        Cells[X,Y].Current:=True;
    end;
  DrawGameBoard;
end;


Function InsideGameBoard(var Event: EventType): Boolean;
begin
  with Event do
    InsideGameBoard:=RctPtInRectangle(ScreenX, ScreenY, WorkRect);
end;


Function HandleEvent(var Event: EventType): Boolean;
Var
  N: Integer;
  PForm: FormPtr;
begin
  HandleEvent:=False;
  with Event do
  case eType of
  penDownEvent:
    if InsideGameBoard(Event) then begin
      TickDown:=True;
      HandleEvent:=True;
    end;
  penUpEvent:
    if TickDown and InsideGameBoard(Event) then begin
      if Editor then
        EditCell(ScreenX,ScreenY)
      else
        if Speed=3 then
          NextGeneration;
      TickDown:=False;
      HandleEvent:=True;
    end;
  frmLoadEvent:
    begin
      PForm:=FrmInitForm(data.frmLoad.FormID);
      FrmSetActiveForm(PForm);
      FrmSetEventHandlerNONE(PForm);  // Needed for PalmOS < v3.3
      FormLoad:=True;
      HandleEvent:=True;
    end;
  frmOpenEvent:
    begin
      FrmDrawForm(FrmGetActiveForm);
      //LoadPreferences(0);
      ApplyCellsColor;
      FormOpen:=True;
      HandleEvent:=True;
    end;
  menuEvent:
    case Data.Menu.ItemID of
      MenuNewGame:     begin
                         N:=FrmAlert(StartNewGame1);
                         if N=0 then InitCells;
                         HandleEvent:=True;
                       end;
      MenuLoad1:       begin
                         LoadPreferences(1);
                         HandleEvent:=True;
                       end;
      MenuLoad2:       begin
                         LoadPreferences(2);
                         HandleEvent:=True;
                       end;
      MenuLoad3:       begin
                         LoadPreferences(3);
                         HandleEvent:=True;
                       end;
      MenuSave1:       begin
                         SavePreferences(1);
                         HandleEvent:=True;
                       end;
      MenuSave2:       begin
                         SavePreferences(2);
                         HandleEvent:=True;
                       end;
      MenuSave3:       begin
                         SavePreferences(3);
                         HandleEvent:=True;
                       end;
      MenuQuit:        begin
                         DoStop:=True;
                         HandleEvent:=True;
                       end;
      MenuEditCurrent: begin
                         Editor:=True;
                         HandleEvent:=True;
                       end;
      MenuEditNew:     begin
                         InitCurrentCells(0,0);
                         EraseDrawBoard;
                         Editor:=True;
                         HandleEvent:=True;
                       end;
      MenuEndEdit:     begin
                         Editor:=False;
                         HandleEvent:=True;
                       end;
      MenuSpeed:       begin
                         case Speed of
                           0 : Speed:=FrmAlert(Speed1);
                           1 : Speed:=FrmAlert(Speed2);
                           2 : Speed:=FrmAlert(Speed3);
                           3 : Speed:=FrmAlert(Speed4);
                         end;
                         HandleEvent:=True;
                       end;
      MenuFilling:     begin
                         case Filling of
                           0 : Filling:=FrmAlert(Filling1);
                           1 : Filling:=FrmAlert(Filling2);
                           2 : Filling:=FrmAlert(Filling3);
                           3 : Filling:=FrmAlert(Filling4);
                         end;
                         HandleEvent:=True;
                       end;
      MenuSize:        begin
                         case CellSize of
                           3: CellSize:=FrmAlert(CellSize1)+3;
                           4: CellSize:=FrmAlert(CellSize2)+3;
                           5: CellSize:=FrmAlert(CellSize3)+3;
                         end;
                         CalcCellSize;
                         EraseDrawBoard;
                         HandleEvent:=True;
                       end;
      MenuColor:       begin
                         if InColor then begin
                           case CellColor of
                             0 : CellColor:=FrmAlert(CellColor1);
                             1 : CellColor:=FrmAlert(CellColor2);
                             2 : CellColor:=FrmAlert(CellColor3);
                             3 : CellColor:=FrmAlert(CellColor4);
                           end;
                           EraseDrawBoard;
                         end
                         else
                           N:=FrmAlert(CellColor0);
                         HandleEvent:=True;
                       end;
      MenuHelp:        begin
                         N:=FrmAlert(Help1);
                         HandleEvent:=True;
                       end;
      MenuRules:       begin
                         N:=FrmAlert(Rule1);
                         HandleEvent:=True;
                       end;
      MenuDonate:      begin
                         FrmHelp(HelpAbout2);
                         HandleEvent:=True;
                       end;
      MenuAbout:       begin
                         N:=FrmAlert(About1);
                         if N=1 then
                           FrmHelp(HelpAbout2);
                         HandleEvent:=True;
                       end;
    end;
  end;
end;


Procedure Main;
Var
  Event: EventType;
  Error: UInt16;
  N: Integer;
  Freeze: Boolean;
begin
  Freeze:=False;
  RctSetRectangle(WorkRect, 0, 16, 160, 144);
  FrmGotoForm(MainForm);
  Repeat
    EvtGetEvent(Event, 5);
    if not SysHandleEvent(Event) then
      if MenuHandleEvent(MyMenu,Event,Error) then
        Freeze:=True
      else
        if not FrmDispatchEvent(Event) then
          if HandleEvent(Event) then
            Freeze:=False
          else
            if (FormLoad and FormOpen) then
              if (Speed<3) and CalcDelay(Speed) and not(Freeze) and not(Editor) then begin
                NextGeneration;
                if (Byte(Cells[1,33].Current)+
                    Byte(Cells[1,34].Current)+
                    Byte(Cells[2,33].Current)+
                    Byte(Cells[2,34].Current)=4) then
                  DoStop:=True;
              end;
  Until DoStop; //or (Event.eType=appStopEvent);
//  SavePreferences(0);
  if FrmGetActiveForm<>nil then begin
    FrmEraseForm(FrmGetActiveForm);
    FrmDeleteForm(FrmGetActiveForm);
  end;
end;


Function Initialize: Boolean;
Var
  N: Integer;
  S: String;
begin
  Initialize:=True;
  if not(VersionSupported(MinOSVer)) then begin
    case MinOSVer of
      V100: S:='1.0';
      V200: S:='2.0';
      V300: S:='3.0';
      V310: S:='3.1';
      V320: S:='3.2';
      V330: S:='3.3';
      V350: S:='3.5';
      V351: S:='3.51';
    end;
    N:=frmCustomAlert(BadOSVersion,'PalmOS version ', S,
                      ' or later is required to run '+AppName+'.');
    Initialize:=False;
  end;
end;


Procedure SpeedBeg;
begin
  InitCurrentCells(0,0);
  Cells[37,40].Current:=True;
  Cells[36,40].Current:=True;
  Cells[34,40].Current:=True;
  Cells[36,39].Current:=True;
  Cells[35,39].Current:=True;
  Cells[34,39].Current:=True;
  Cells[35,38].Current:=True;
  EraseDrawBoard;
end;

Procedure SpeedEnd;
Var
  N: Integer;
begin
  N:=StopTimer;
  N:=frmCustomAlert(ResultWindow,'SCells test lasted ',i2s(N),' seconds.');
end;


begin
  if Initialize then begin
    StartTimer;
    Randomize;
    InitVar;
    SpeedBeg;
    Main;
    SpeedEnd;
  end;
end.
