//
// SMatches is a freeware program for HSPascal.
// SMatches Version 1.2 - October 8, 2003 - Made by Laurent Duveau
//       Web Site = http://aldweb.free.fr
//       e-Mail   = aldweb@free.fr
//
// SMatches is based on the source code of Matches freeware.
// Matches Version Version 2.0 - October 24, 2002 - Made by Laurent Duveau
//
// SMatches was compiled with the great HSPascal compiler
// for Palm OS handheld devices
//       Web Site = http://HSPascal.Fihl.net
//       e-Mail   = Christen@Fihl.net
//
// The original source code of Matches was slightly modified
// for Speedy tests purposes, and the program was renamed
// as SMatches for no confusion making.
//


Program SMatches;


{$SearchPath Units; Units\UI; Units\System}
{$ApplName SMatches,LDSM}
// LDSM is a referenced PalmOS CreatorID


Uses
  Window, Form, Menu, Rect, Event, SysEvent, SystemMgr, FloatMgr, HSUtils,
  TimeMgr, Preferences, SystemResources, Bitmap;


{$R .\MatchesRes.ro}

Resource
  MenuRes=(ResMBAR,,
    (ResMPUL,(6,14,90,38),(4,0,35,12),'Game',
      MenuNewGame=(,'N','New Game'),
      MenuSpeed=(,'S','Game Speed'),
      MenuSpace1=(,'','-'),
      MenuQuit=(,'X','Exit')),
    (ResMPUL,(42,14,73,49),(40,0,30,12),'Help',
      MenuRules=(,'R','Rules'),
      MenuTips=(,'T','Tips'),
      MenuSpace2=(,'','-'),
      MenuDonate=(,'D','Donate...'),
      MenuAbout=(,'A','About')));

  MainForm=(ResTFRM,1000,(0,0,160,160),0,0,MenuRes, (FormTitle,'SMatches'),
    Main1Button=(FormButton,,(16,145,36,12),,,,'1'),
    Main2Button=(FormButton,,(60,145,36,12),,,,'2'),
    Main3Button=(FormButton,,(104,145,36,12),,,,'3'));

  Rule1=(ResTalt,,0,0,0,'Matches - Rules','Matches is a silly little game in '+
         'which each of the two players (computer and you) removes one after '+
         'the other from one to three matches.'+#10+'The player who remains with '+
         'the last match looses the game.','OK');
  Tip1=(ResTalt,,0,0,0,'Matches - Tips','There is a way to win every time. Try to '+
        'figure out what rule you should follow to make sure you win against the '+
        'computer player...','OK');
  HelpAbout1=(ResTSTR,,'Matches is a sample freeware program compiled with the great '+
              'HSPascal compiler for Palm OS handheld devices.'#10+
              'HSPascal can be found here:'#10'http://HSPascal.Fihl.net'#10#10+
              'The source code of Matches is available for download on my web site.');
  HelpAbout2=(ResTSTR,,'Matches is free to use. However, if you like it, please '+
              'consider making a donation to show your support.'#10+
              'Any amount will be greatly appreciated.'#10#10+
              'To proceed, just connect to:'#10'www.aldweb.com/give.html'#10+
              '(secure PayPal transaction)');
  About1=(ResTalt,,0,HelpAbout1,0,'Matches - About', 'Matches  v2.0'#10+
          #9'October 24, 2002'#10#9'by Laurent Duveau'#10#10+
          'Visit my Web site:'#10#9'www.aldweb.com'#10#10+
          'e-Mail me:'#10#9'info@aldweb.com','OK','Donate...');
  StartNewGame1=(ResTalt,,1,0,1,'Matches - New Game','Do you really want to start '+
                 'a new game ?','Yes','No');
  First1=(ResTalt,,1,0,0,'Matches - First Player','^1 ^2 ^3','Computer','You');
  ComputerWin1=(ResTalt,,2,0,0,'Matches - Winner','Sorry, I win !','OK');
  PlayerWin1=(ResTalt,,2,0,0,'Matches - Winner','Good job, YOU win.','OK');
  StartNewGame2=(ResTalt,,1,0,1,'Matches - New Game','Do you wish to play again ?','Yes','No');
  HelpSpeed1=(ResTSTR,,'Game Speed option sets the animation displaying speed.');
  Speed1=(ResTalt,,1,HelpSpeed1,0,'Matches - Game Speed','Current speed is :'#10#9'Fast'+
          #10#10'Choose a new speed :','Fast','Average','Slow');
  Speed2=(ResTalt,,1,HelpSpeed1,1,'Matches - Game Speed','Current speed is :'#10#9'Average'+
          #10#10'Choose a new speed :','Fast','Average','Slow');
  Speed3=(ResTalt,,1,HelpSpeed1,2,'Matches - Game Speed','Current speed is :'#10#9'Slow'+
          #10#10'Choose a new speed :','Fast','Average','Slow');
  BadOSVersion=(ResTalt,,2,0,0,'Matches','^1 ^2 ^3','Done');

  ResultWindow=(ResTalt,,0,0,0,'SMatches - Timer Results','^1 ^2 ^3','Ok');

  (ResTAIN,1000,'SMatches');
  (ResTVER,1000,'1.2');


Type
  TPref = Record
            NB: Integer;
            GS: Integer;


          end;


Const
  CreatorID=$4C44534D;      // LDSM
  AppName='SMatches';
  MinOSVer=V200;

  Nobody=0;
  Computer=1;
  Human=2;
  RemoveHowMany='Remove how many matches ?';
  Me='I remove ';
  You='You remove ';
  OneMatch=' match';
  MoreMatches=' matches';
  Left=' left';
  FiveSpaces='     ';
  TenSpaces=FiveSpaces+FiveSpaces;
  SixtySpaces=TenSpaces+TenSpaces+TenSpaces+TenSpaces+TenSpaces+TenSpaces;
  StartMatches1='There are ';
  StartMatches2=' matches on the board.';
  StartMatches3='Please choose who will start first to remove matches:';


Var
  NbOfMatches,FirstPlayer,GameSpeed: Integer;
  MyMenu: MenuBarPtr;
  WorkRect: RectangleType;
  FormLoad,FormOpen,FirstLaunch,DoStop,InColor: Boolean;
  PlayerIcon: Array[1..58] of String[28];
  MatchIcon: Array[1..23] of String[7];
  ColorRGB: Array[0..7] of IndexedColorType;

  DlySeed: LongInt;
  RndSeed : Real;
  TurnsToPlay: Integer;


Procedure StartTimer;
begin
  DlySeed:=TimGetSeconds;
end;

Function StopTimer: LongInt;
begin
  StopTimer:=TimGetSeconds-DlySeed;
end;

Function Rnd(Rdm: Integer): Integer;
begin
  RndSeed:=221*RndSeed+0.2113;
  RndSeed:=RndSeed-Trunc(RndSeed);
  Rnd:=Trunc(Rdm*RndSeed);
end;


Procedure DrawOneDot(X,Y: Integer; C: Char);
Var
  IndexedColor: IndexedColorType;
begin
  if InColor then begin
    IndexedColor:=WinSetForeColor(ColorRGB[s2i(C)]);
    WinDrawLine(X,Y,X,Y);
   end
   else
     if C in ['1','4','6'] then
       WinDrawLine(X,Y,X,Y);
end;


Procedure EraseLogo(X,Y,W,H: Integer);
Var
  Rec: RectangleType;
begin
  With Rec do begin
    topLeft.X := X;
    topLeft.y := Y;
    extent.x  := W;
    extent.y  := H;
    WinEraseRectangle(Rec,0);
  end;
end;


Procedure DrawPlayerIcon(WhoPlays: Integer);
Const
  Xi=2;
  Yi=110;
Var
  I,J: Integer;
  S : String;
begin
  Eraselogo(Xi,Yi,29,29);
  for J:=0 to 28 do begin
    S:=PlayerIcon[29*(WhoPlays-1)+J+1];
    for I:=0 to 28 do
      DrawOneDot(Xi+I,Yi+J,S[I+1]);
  end;
end;


Procedure DrawMatchIcon(ShowIt: Boolean; X,Y: Integer);
Var
  I,J: Integer;
  S: String;
begin
  if ShowIt=True then
    for J:=0 to 22 do begin
      S:=MatchIcon[J+1];
      for I:=0 to 6 do
        DrawOneDot(X+I,Y+J,S[I+1]);
    end
    else Eraselogo(X,Y,7,23);
end;


Procedure DrawMatches;
Var
  N,X,Y: Integer;
begin
  for N := 0 to 29 do begin
    Y:=N div 10;
    X:=N-10*Y;
    Y:=26*Y+20;
    X:=12*X+20;
    if N<NbOfMatches then
      DrawMatchIcon(True,X,Y)
    else
      DrawMatchIcon(False,X,Y);
  end;
end;


Procedure DrawTextLine(LineNumber: Integer; ToPrint: String);
begin
  case LineNumber of
    1: WinDrawChars(ToPrint,Length(ToPrint),50,115);
    2: WinDrawChars(ToPrint,Length(ToPrint),35,125);
  end;
end;


Procedure DrawGameBoard(NbOfRemoved,WhoRemoved: Integer);
Var
  S: String;
  N: Integer;
begin
  if NbOfRemoved>0 then begin
    Str(NbOfRemoved:1,S);
    case WhoRemoved of
      Computer: S:=Me+S;
      Human:    S:=You+S;
    end;
    if NbOfRemoved=1 then
      S:=S+OneMatch
    else
      S:=S+MoreMatches;
    S:=FiveSpaces+S+SixtySpaces;
    DrawTextLine(2,S);
    NbOfMatches:=NbOfMatches-NbOfRemoved;
    DrawMatches;
    N:=SysTaskDelay(GameSpeed*SysTicksPerSecond div 4);
  end
  else
    DrawMatches;
  Str(NbOfMatches:2,S);
  if NbOfMatches=1 then
    S:=S+OneMatch+Left+SixtySpaces
  else
    S:=S+MoreMatches+Left+SixtySpaces;
  DrawTextLine(1,S);
  case WhoRemoved of
    Nobody:   begin
                DrawTextLine(2,SixtySpaces);
                Eraselogo(2,110,29,29);
              end;
    Computer: if NbOfRemoved=0 then begin
                DrawTextLine(2,SixtySpaces);
                DrawPlayerIcon(Computer);
              end
              else begin
                DrawTextLine(2,RemoveHowMany);
                DrawPlayerIcon(Human);
              end;
    Human:    if NbOfRemoved=0 then begin
                DrawTextLine(2,RemoveHowMany);
                DrawPlayerIcon(Human);
              end
              else begin
                DrawTextLine(2,SixtySpaces);
                DrawPlayerIcon(Computer);
              end;
  end;
end;


Procedure ComputerPlayerPlays;
Var
  N: Integer;
  S: String;
  M: Integer;
begin
  // "magic" test is (NbOfMatches-1)/4=int((NbOfMatches-1)/4)
  // or in a more elegant way (NbOfMatches-1) mod 4=0
  if (NbOfMatches-1) mod 4=0 then
    repeat
      N:=Rnd(3)+1;
    until N<NbOfMatches
  else
  // "magic" formula is  NbOfMatches-(4*Trunc(NbOfMatches/4-0.5)+1);
  // or in a much smarter way (NbOfMatches-1) mod 4
    N:=(NbOfMatches-1) mod 4;
  DrawGameBoard(N,Computer);
  if NbOfMatches=1 then begin
//    N:=FrmAlert(ComputerWin1);
    NbOfMatches:=0;
  end;
end;


Procedure HumanPlayerPlays(NbOfRemoved: Integer);
Var
  N: Integer;
begin
  if NbOfRemoved<NbOfMatches then begin
    DrawGameBoard(NbOfRemoved,Human);
    if NbOfMatches=1 then begin
//      N:=FrmAlert(PlayerWin1);
      NbOfMatches:=0;
    end
    else
      ComputerPlayerPlays;
  end;
end;


Procedure InitGame;
Var
  Init: Boolean;
  S: String;
begin
  Init:=True;
//  if NbOfMatches>0 then
//    Init:=FrmAlert(StartNewGame1)<>1;
  if Init then begin
    NbOfMatches:=Rnd(29)+2;
    WinEraseRectangle(WorkRect,0);
    DrawGameBoard(0,Nobody);
//    Str(NbOfMatches:2,S);
//    S:=StartMatches1+S+StartMatches2;
//    if frmCustomAlert(First1,S,#10#10,StartMatches3)=0 then begin
//      DrawGameBoard(0,Computer);
//      ComputerPlayerPlays;
//    end
//    else
//      DrawGameBoard(0,Human);
    ComputerPlayerPlays;
  end;
end;


Procedure SavePreferences;
var
  GamePref: TPref;
begin
  with GamePref do begin
    NB:=NbofMatches;
    GS:=GameSpeed;
  end;
  PrefSetAppPreferences(CreatorID,0,0,@GamePref,SizeOf(GamePref),True);
end;


Procedure LoadPreferences;
Var
  Size,N: Integer;
  GamePref: TPref;
begin
  Size:=SizeOf(GamePref);
  N:=PrefGetAppPreferences(CreatorID,0,@GamePref,Size,True);
  if N=noPreferenceFound then begin
    NbOfMatches:=0;
    GameSpeed:=2;
  end
  else
    with GamePref do begin
      NbofMatches:=NB;
      GameSpeed:=GS;
    end;
end;


Procedure InitColors;
Var
  RGB: RGBColorType;
begin
  // White
  RGB.R:=255;
  RGB.G:=255;
  RGB.B:=255;
  ColorRGB[0]:=WinRGBToIndex(RGB);
  // Black
  RGB.R:=0;
  RGB.G:=0;
  RGB.B:=0;
  ColorRGB[1]:=WinRGBToIndex(RGB);
  // Match lighter color
  RGB.R:=255;
  RGB.G:=255;
  RGB.B:=102;
  ColorRGB[2]:=WinRGBToIndex(RGB);
  // Match stick color
  RGB.R:=204;
  RGB.G:=153;
  RGB.B:=51;
  ColorRGB[3]:=WinRGBToIndex(RGB);
  // Human Hair color
  RGB.R:=128;
  RGB.G:=64;
  RGB.B:=64;
  ColorRGB[4]:=WinRGBToIndex(RGB);
  // Human Skin color
  RGB.R:=255;
  RGB.G:=128;
  RGB.B:=128;
  ColorRGB[5]:=WinRGBToIndex(RGB);
  // Palm Screen color
  RGB.R:=123;
  RGB.G:=140;
  RGB.B:=90;
  ColorRGB[6]:=WinRGBToIndex(RGB);
  // Palm Border color
  RGB.R:=85;
  RGB.G:=85;
  RGB.B:=85;
  ColorRGB[7]:=WinRGBToIndex(RGB);
end;


Procedure InitVar;
Var
  WidthP,HeightP,DepthP: UInt32;
  EnableColorP: Boolean;
  Error: Err;
begin
  DoStop:=False;
//  LoadPreferences;
  FormLoad:=False;
  FormOpen:=False;
  FirstLaunch:=True;
  if VersionSupported(V350) then begin
    Error:=WinScreenMode(winScreenModeGet,WidthP,HeightP,DepthP,EnableColorP);
    InColor:=(DepthP>=8);
    if InColor then
      InitColors;
  end
  else
    InColor:=False;
  // Here under is a way of managing tiles without using Palm Resources
  // The resulting displaying is very slow but I keep it this way for educational purposes
  PlayerIcon[1]:='0000077777777777777770000000';      // Palm player
  PlayerIcon[2]:='0000711111111111111111000000';
  PlayerIcon[3]:='0000710000000000000000100000';
  PlayerIcon[4]:='0000710011111111111100100000';
  PlayerIcon[5]:='0000710166666666666610100000';
  PlayerIcon[6]:='0000710166666666666610100000';
  PlayerIcon[7]:='0000710166666666666610100000';
  PlayerIcon[8]:='0000710166666666666610100000';
  PlayerIcon[9]:='0000710166666666666610100000';
  PlayerIcon[10]:='0000710166666666666610100000';
  PlayerIcon[11]:='0000710166666666666610100000';
  PlayerIcon[12]:='0000710166666666666610100000';
  PlayerIcon[13]:='0000710166666666666610100000';
  PlayerIcon[14]:='0000710166666666666610100000';
  PlayerIcon[15]:='0000710166666666666610100000';
  PlayerIcon[16]:='0000710166666666666610100000';
  PlayerIcon[17]:='0000710166666666666610100000';
  PlayerIcon[18]:='0000710106060606060610100000';
  PlayerIcon[19]:='0000710160606060606010100000';
  PlayerIcon[20]:='0000710106060606060610100000';
  PlayerIcon[21]:='0000710160606060606010100000';
  PlayerIcon[22]:='0000710011111111111110100000';
  PlayerIcon[23]:='0000710000000000000000100000';
  PlayerIcon[24]:='0000710000000110000000100000';
  PlayerIcon[25]:='0000710110110110110110100000';
  PlayerIcon[26]:='0000710110110110110110100000';
  PlayerIcon[27]:='0000710000000110000000100000';
  PlayerIcon[28]:='0000010000000000000000100000';
  PlayerIcon[29]:='0000001111111111111111100000';
  PlayerIcon[30]:='0000000000011111111000000000';     // Human player
  PlayerIcon[31]:='0000000011144444444110000000';
  PlayerIcon[32]:='0000000144444444444141100000';
  PlayerIcon[33]:='00000014444444444441444100000';
  PlayerIcon[34]:='00000144444444444441444410000';
  PlayerIcon[35]:='00000144444444444441444410000';
  PlayerIcon[36]:='00001444444444444441444441000';
  PlayerIcon[37]:='00001444444444444415144441000';
  PlayerIcon[38]:='00014444444444444155144444100';
  PlayerIcon[39]:='00014444444444411555514444100';
  PlayerIcon[40]:='00144444444441155555551144410';
  PlayerIcon[41]:='00144444441115555555555514410';
  PlayerIcon[42]:='01444411115555555555555551410';
  PlayerIcon[43]:='14441155555555555555555555110';
  PlayerIcon[44]:='14115551155555555555511555510';
  PlayerIcon[45]:='11555510015555555555100155511';
  PlayerIcon[46]:='15555511115555115555111155551';
  PlayerIcon[47]:='15555511115551111555111155551';
  PlayerIcon[48]:='15555551155511111155511555551';
  PlayerIcon[49]:='15555555555511111155555555551';
  PlayerIcon[50]:='11555555555551111555555555511';
  PlayerIcon[51]:='01155555115555115555115555110';
  PlayerIcon[52]:='00115555111555555551115551100';
  PlayerIcon[53]:='00011555511155555511155511000';
  PlayerIcon[54]:='00001155551111111111555110000';
  PlayerIcon[55]:='00000115555111111115551100000';
  PlayerIcon[56]:='00000011555555555555511000000';
  PlayerIcon[57]:='00000001155555555555110000000';
  PlayerIcon[58]:='00000000111111111111100000000';
  MatchIcon[1]:='0011100';
  MatchIcon[2]:='0122210';
  MatchIcon[3]:='1222221';
  MatchIcon[4]:='1222221';
  MatchIcon[5]:='0122210';
  MatchIcon[6]:='0111110';
  MatchIcon[7]:='0131310';
  MatchIcon[8]:='0131310';
  MatchIcon[9]:='0131310';
  MatchIcon[10]:='0131310';
  MatchIcon[11]:='0131310';
  MatchIcon[12]:='0131310';
  MatchIcon[13]:='0131310';
  MatchIcon[14]:='0131310';
  MatchIcon[15]:='0131310';
  MatchIcon[16]:='0131310';
  MatchIcon[17]:='0131310';
  MatchIcon[18]:='0131310';
  MatchIcon[19]:='0131310';
  MatchIcon[20]:='0131310';
  MatchIcon[21]:='0131310';
  MatchIcon[22]:='0011100';
  MatchIcon[23]:='0001000';
end;


Function HandleEvent(var Event: EventType): Boolean;
Var
  N: Integer;
  PForm: FormPtr;
begin
  HandleEvent:=False;
  with Event do
  case eType of
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
      if NbOfMatches>0 then
        DrawGameBoard(0,Human);
      FormOpen:=True;
      HandleEvent:=True;
    end;
  ctlSelectEvent:
    case Data.CtlEnter.ControlID of
      Main1Button: begin
                     HumanPlayerPlays(1);
                     HandleEvent:=True;
                   end;
      Main2Button: begin
                     HumanPlayerPlays(2);
                     HandleEvent:=True;
                   end;
      Main3Button: begin
                     HumanPlayerPlays(3);
                     HandleEvent:=True;
                   end;
    end;
  menuEvent:
    case Data.Menu.ItemID of
      MenuNewGame: begin
                     InitGame;
                     HandleEvent:=True;
                   end;
      MenuSpeed:   begin
                     case GameSpeed of
                       1 : GameSpeed:=FrmAlert(Speed1)+1;
                       2 : GameSpeed:=FrmAlert(Speed2)+1;
                       3 : GameSpeed:=FrmAlert(Speed3)+1;
                     end;
                     HandleEvent:=True;
                   end;
      MenuQuit:    begin
                     DoStop:=True;
                     HandleEvent:=True;
                   end;
      MenuRules:   begin
                     N:=FrmAlert(Rule1);
                     HandleEvent:=True;
                   end;
      MenuTips:    begin
                     N:=FrmAlert(Tip1);
                     HandleEvent:=True;
                   end;
      MenuDonate:  begin
                     FrmHelp(HelpAbout2);
                     HandleEvent:=True;
                   end;
      MenuAbout:   begin
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
begin
  RctSetRectangle(WorkRect,0,16,160,128);
  FrmGotoForm(MainForm);
  Repeat
    EvtGetEvent(Event, 5);
    if not SysHandleEvent(Event) then
      if not MenuHandleEvent(MyMenu,Event,Error) then
        if not FrmDispatchEvent(Event) then
          if not HandleEvent(Event) then
            if (FormLoad and FormOpen) then
              if (NbOfMatches=0) then
                if not FirstLaunch then
                  if TurnsToPlay>0 then begin
                    InitGame;
                    dec(TurnsToPlay);
                  end
                  else
                    DoStop:=True
                else begin
                  InitGame;
                  FirstLaunch:=False;
                end
              else begin
                repeat
                  N:=Rnd(3)+1;
                until N<NbOfMatches;
                HumanPlayerPlays(N);
              end;
  Until DoStop; // or (Event.eType=appStopEvent);
//  SavePreferences;
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
  RndSeed:=0.1234;
  TurnsToPlay:=9;

  NbOfMatches:=0;
  GameSpeed:=2;
end;

Procedure SpeedEnd;
Var
  N: LongInt;
begin
  N:=StopTimer;
  N:=frmCustomAlert(ResultWindow,'SMatches test lasted ',l2s(N),' seconds.');
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
