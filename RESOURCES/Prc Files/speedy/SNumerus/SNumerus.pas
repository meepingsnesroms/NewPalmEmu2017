//
// SNumerus is a freeware program for HSPascal.
// SNumerus Version 1.2 - October 8, 2003 - Made by Laurent Duveau
//       Web Site = http://aldweb.free.fr
//       e-Mail   = aldweb@free.fr
//
// SNumerus is based on the source code of Numerus freeware.
// Numerus Version 1.7 - September 18, 2002 - Made by Laurent Duveau
//
// SNumerus was compiled with the great HSPascal compiler
// for Palm OS handheld devices
//       Web Site = http://HSPascal.Fihl.net
//       e-Mail   = Christen@Fihl.net
//
// The original source code of Numerus was slightly modified
// for Speedy tests purposes, and the program was renamed
// as SNumerus for no confusion making.
//


Program SNumerus;


{$SearchPath Units; Units\UI; Units\System}
{$ApplName SNumerus,LDSN}
// LDSN is a referenced PalmOS CreatorID


Uses
  Window, Form, Menu, Rect, Event, SysEvent, SystemMgr, FloatMgr, HSUtils, Font,
  Preferences, SystemResources, SoundMgr, ClipBoard, TimeMgr;


{$R .\NumerusRes.ro}

Resource
  MenuRes=(ResMBAR,,
    (ResMPUL,(6,14,115,49),(4,0,48,12),'Options',
      MenuMethod=(,'I','Input Method'),
      MenuAlert=(,'L','Input Alert'),
      MenuButt=(,'K','Keyboard Layout'),
      MenuSpace1=(,'','-'),
      MenuQuit=(,'X','Exit')),
    (ResMPUL,(54,14,60,22),(52,0,27,12),'Edit',
      MenuCopy=(,'C','Copy'),
      MenuReset=(,'R','Clear')),
    (ResMPUL,(43,14,115,60),(80,0,31,12),'Help',
      MenuHelp=(,'H','Help'),
      MenuInput=(,'T','Data Input'),
      MenuTips=(,'N','Roman Numerals'),
      MenuSpace2=(,'','-'),
      MenuDonate=(,'D','Donate...'),
      MenuAbout=(,'A','About')));

  MainForm=(ResTFRM,1000,(0,0,160,160),0,0,MenuRes, (FormTitle,'SNumerus'),
    MCButton=(FormButton,,(2,54,20,17),,stdFont,,'MC'),
    MRButton=(FormButton,,(2,75,20,17),,stdFont,,'MR'),
    MPButton=(FormButton,,(2,96,20,17),,stdFont,,'M+'),
    CEButton=(FormButton,,(2,118,20,18),,stdFont,,'CE'),
    CButton=(FormButton,,(2,140,20,18),,stdFont,,'C'),
    NXButton=(FormButton,,(26,54,32,32),,largeBoldFont,,'X'),
    NVButton=(FormButton,,(26,90,32,32),,largeBoldFont,,'V'),
    NIButton=(FormButton,,(26,126,32,32),,largeBoldFont,,'I'),
    NCButton=(FormButton,,(62,54,32,32),,largeBoldFont,,'C'),
    NLButton=(FormButton,,(62,90,32,32),,largeBoldFont,,'L'),
    EQUButton=(FormButton,,(62,126,68,32),,largeFont,,'='),
    NMButton=(FormButton,,(98,54,32,32),,largeBoldFont,,'M'),
    NDButton=(FormButton,,(98,90,32,32),,largeBoldFont,,'D'),
    DIVButton=(FormButton,,(134,54,24,23),,largeFont,,'/'),
    MULButton=(FormButton,,(134,81,24,23),,largeFont,,#215),
    SUBButton=(FormButton,,(134,108,24,23),,largeFont,,#150),
    ADDButton=(FormButton,,(134,135,24,23),,largeFont,,'+'));

  Help1=(ResTalt,,0,0,0,'Numerus - Help','Numerus is a basic standard 4 function '+
         'calculator... that operates in Roman numerals.'#10#10+
         'Numerus accepts numbers in the range {0..99999}','OK');
  Help2=(ResTalt,,0,0,0,'Numerus - Input Methods','There are 2 ways for inputting the '+
         'Roman numerals : either ''additive'' or ''natural''.'#10#10+
         'Click on the Details button to learn more about these two methods.','OK', 'Details');
  Tip1=(ResTalt,,0,0,0,'Numerus - Roman Numerals','I = 1'#9#9#9'V = 5'#10'X = 10'#9#9'L = 50'+
        #10'C = 100'#9#9'D = 500'#10'M = 1000'#10#10'For numbers > 4999 :'#10+
        'N.M means N x 1000'#10'For example :'#10'V.M is 5000','OK');
  HelpAbout1=(ResTSTR,,'Numerus is a sample freeware program compiled with the great '+
              'HSPascal compiler for Palm OS handheld devices.'#10+
              'HSPascal can be found here:'+#10+'http://HSPascal.Fihl.net'#10#10+
              'The source code of Numerus is available for download on my web site.'#10#10+
              'I also want to address here a very special Thank You to Michael Kilby '+
              'who helped me a lot in improving Numerus. Thanks Michael.');
  HelpAbout2=(ResTSTR,,'Numerus is free to use. However, if you like it, please '+
              'consider making a donation to show your support.'#10+
              'Any amount will be greatly appreciated.'#10#10+
              'To proceed, just connect to:'#10'www.aldweb.com/give.html'#10+
              '(secure PayPal transaction)');
  About1=(ResTalt,,0,HelpAbout1,0,'Numerus - About', 'Numerus  v1.7'#10+
          #9'Sept. XVIII, MMII'#10#9'by Laurent Duveau'#10#10+
          'Visit my Web site:'#10#9'www.aldweb.com'#10#10+
          'e-Mail me:'#10#9'info@aldweb.com','OK','Donate...');
  HelpInput1=(ResTSTR,,'Additive method:'#10'Numerus adds the Roman numerals as you input '+
              'them.'#10'For example, if you key in V and then X, Numerus will show XV '+
              '(because V + X = XV).'#10#10'Natural method:'#10'Numerus will check that you '+
              'input a valid number.'#10'For example, if you key in V and then X, Numerus '+
              'will refuse the entry because VX is not a valid Roman number.'#10'Numerus will '+
              'also assist you in your input. For example, if you key in IIII it will replace '+
              'it with the more common IV value.'#10#10'Please, read the documentation that came '+
              'with the program for a full understanding of the rules that Roman numerals follow.');
  Input1=(ResTalt,,1,HelpInput1,0,'Numerus - Data Input','Current data input method '+
          'is:'#10#9'Additive'#10#10'Choose a new method:','Additive','Natural');
  Input2=(ResTalt,,1,HelpInput1,1,'Numerus - Data Input','Current data input method '+
          'is:'#10#9'Natural'#10#10'Choose a new method:','Additive','Natural');
  InputAlert1=(ResTalt,,1,HelpInput1,0,'Numerus - Data Input','In Natural input method, when keying in a wrong entry:'+
               #10'a warning message pops up.'#10#10'Popup a warning window or beep?','Popup warning','Beep');
  InputAlert2=(ResTalt,,1,HelpInput1,1,'Numerus - Data Input','In Natural input method, when keying in a wrong entry:'+
               #10'the device beeps.'#10#10'Popup a warning window or beep?','Popup warning','Beep');
  ButtonLayout1=(ResTalt,,1,,0,'Numerus - Keyboard Layout','Layout #1'#9'Layout #2'#10+
                 '    X  C  M'#9#9'    M  D  C'#10'    V  L  D'#9#9'    L    X  V'#10'    I       ='#9#9+
                 '    I         ='#10#10'Choose a layout:','Layout #1','Layout #2');
  BadInput1=(ResTalt,,2,HelpInput1,0,'Numerus - Entry Error','Last numeral keyed in does '+
          'not give a valid Roman number.'#10'I skipped it.','Done');
  BadOSVersion=(ResTalt,,2,0,0,'Numerus','^1 ^2 ^3','Done');

  ResultWindow=(ResTalt,,0,0,0,'SNumerus - Timer Results','^1 ^2 ^3','Ok');


  (ResTAIN,1000,'SNumerus');
  (ResTVER,1000,'1.2');


Type
  TOper = (cEQU,cADD,cSUB,cMUL,cDIV);
  TAlerte = (aSND,aPOP);
  TMemDraw = (mONE,mTWO);
  TPref = Record
            N1: LongInt;
            N2: LongInt;
            MD: TMemDraw;
            NM: LongInt;
            OP: TOper;
            IP: Integer;
            AL: TAlerte;
            LA: Integer;
          end;


Const
  CreatorID=$4C44534E;      // LDSN
  AppName='SNumerus';
  MinOSVer=V300;

  One = 'I';
  Five = 'V';
  Ten = 'X';
  Fifty = 'L';
  OneHundred = 'C';
  FiveHundred = 'D';
  OneThousand = 'M';
  Void = -1;


Var
  MyMenu: MenuBarPtr;
  WorkRect: RectangleType;
  FormLoad,FormOpen,DoStop: Boolean;
  InputMethod, Layout: Integer;
  NumArab1,NumArab2,NumMem: LongInt;
  MemDraw: TMemDraw;
  Oper: TOper;
  Alerte: TAlerte;
  NumLatin: String;

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


Procedure CReset;
begin
  NumArab1:=0;
  NumArab2:=Void;
  MemDraw:=mONE;
  Oper:=cEQU;
end;


Procedure SavePreferences;
Var
  ToSave: TPref;
begin
  with ToSave do begin
    N1:=NumArab1;
    N2:=NumArab2;
    MD:=MemDraw;
    NM:=NumMem;
    OP:=Oper;
    IP:=InputMethod;
    AL:=Alerte;
    LA:=Layout;
  end;
  PrefSetAppPreferences(CreatorID,0,0,@ToSave,SizeOf(ToSave),True);
end;


Procedure LoadPreferences;
Var
  ToLoad: TPref;
  Size,N: Integer;
begin
  Size:=SizeOf(ToLoad);
  N:=PrefGetAppPreferences(CreatorID,0,@ToLoad,Size,True);
  if N=noPreferenceFound then begin
    CReset;
    NumMem:=0;
    InputMethod:=1;
    Alerte:=aPOP;
    Layout:=0;
  end
  else
    with ToLoad do begin
      NumArab1:=N1;
      NumArab2:=N2;
      MemDraw:=MD;
      NumMem:=NM;
      Oper:=OP;
      InputMethod:=IP;
      Alerte:=AL;
      Layout:=LA;
    end;
end;


Function CalcNumLatin(NumArab: LongInt): String;
Var
  NumLatin: String;
  Procedure AddLatin(LatinChar: String);
  begin
    NumLatin:=LatinChar+NumLatin;
  end;
  Procedure AddRoman(NumAr: LongInt);
  Var
    N1,N2,N3,N4: Integer;
  begin
    N1:= NumAr mod 10;
    Case N1 of
      1: AddLatin(One);
      2: AddLatin(One+One);
      3: AddLatin(One+One+One);
      4: AddLatin(One+Five);
      5: AddLatin(Five);
      6: AddLatin(Five+One);
      7: AddLatin(Five+One+One);
      8: AddLatin(Five+One+One+One);
      9: AddLatin(One+Ten);
    end;
    N2 := NumAr mod 100 - N1;
    Case N2 of
      10: AddLatin(Ten);
      20: AddLatin(Ten+Ten);
      30: AddLatin(Ten+Ten+Ten);
      40: AddLatin(Ten+Fifty);
      50: AddLatin(Fifty);
      60: AddLatin(Fifty+Ten);
      70: AddLatin(Fifty+Ten+Ten);
      80: AddLatin(Fifty+Ten+Ten+Ten);
      90: AddLatin(Ten+OneHundred);
    end;
    N3 := NumAr mod 1000 - N2 - N1;
    Case N3 of
      100: AddLatin(OneHundred);
      200: AddLatin(OneHundred+OneHundred);
      300: AddLatin(OneHundred+OneHundred+OneHundred);
      400: AddLatin(OneHundred+FiveHundred);
      500: AddLatin(FiveHundred);
      600: AddLatin(FiveHundred+OneHundred);
      700: AddLatin(FiveHundred+OneHundred+OneHundred);
      800: AddLatin(FiveHundred+OneHundred+OneHundred+OneHundred);
      900: AddLatin(OneHundred+OneThousand);
    end;
    N4 := NumAr mod 10000 -N3 - N2 - N1;
    Case N4 of
      1000: AddLatin(OneThousand);
      2000: AddLatin(OneThousand+OneThousand);
      3000: AddLatin(OneThousand+OneThousand+OneThousand);
      4000: AddLatin(OneThousand+OneThousand+OneThousand+OneThousand);
    end;
  end;
begin
  NumLatin:='';
  if NumArab>4999 then begin
    AddRoman(NumArab mod 1000);
    AddLatin('.'+OneThousand+'  ');
    AddRoman(NumArab div 1000);
  end
  else AddRoman(NumArab);
  CalcNumLatin:=NumLatin;
end;


Procedure DrawNumbers(MD: TMemDraw);
Var
  NumArab: LongInt;
  UL: UnderlineModeType;
  FID: FontID;
  T: String;
  N: Integer;
  Procedure CleanFrame;
  Var
    Rec: RectangleType;
  begin
    With Rec do begin
      topLeft.X := 6;
      topLeft.y := 22;
      extent.x  := 148;
      extent.y  := 8;
      WinEraseRectangle(Rec,0);
      topLeft.y := 35;
      extent.y  := 12;
      WinEraseRectangle(Rec,0);
    end;
  end;
begin
  MemDraw:=MD;
  case MemDraw of
    mONE: NumArab:=NumArab1;
    mTWO: NumArab:=NumArab2;
  end;
  CleanFrame;
  FID:=FntSetFont(boldFont);  // can be stdFont, boldFont or largeBoldFont
  if NumMem>0 then
    WinDrawChars('m',1,6,19);
  if (NumArab<0) or (NumArab>99999) then begin
    NumLatin:='error';
    N:=FntCharsWidth(NumLatin,Length(NumLatin));
    WinDrawChars(NumLatin,Length(NumLatin),91-N,20);
    SndPlaySystemSound(sndStartUp);
    CReset;
  end
  else begin
    Str(NumArab:6,T);
    N:=FntCharsWidth(T,Length(T));
    WinDrawChars(T,Length(T),91-N,20);
    FID:=FntSetFont(largeBoldFont);
    NumLatin:=CalcNumLatin(NumArab);
    WinDrawChars(NumLatin,Length(NumLatin),6,34);
  end;
end;


Procedure InitCalcDisplay;
  Procedure DrawFrame;
  Var
    Rec: RectangleType;
  begin
    With Rec do begin
    topLeft.X := 3;
    topLeft.y := 19;
    extent.x  := 154;
    extent.y  := 30;
    WinDrawRectangleFrame(dialogFrame,Rec);
    topLeft.y := 32;
    extent.y  := 2;
    WinDrawRectangle(Rec,0);
    end;
  end;
begin
  DrawFrame;
  DrawNumbers(MemDraw);
end;


Procedure PositionOneButton(ButtonID,X,Y: Integer);
Var
  PForm : FormPtr;
begin
  PForm := FrmGetFormPtr(MainForm);
  FrmSetObjectPosition(PForm,FrmGetObjectIndex(PForm,ButtonID),X,Y);
end;


Procedure PositionButtons;
begin
  if Layout=0 then begin
    PositionOneButton(NXButton,26,54);
    PositionOneButton(NCButton,62,54);
    PositionOneButton(NMButton,98,54);
    PositionOneButton(NVButton,26,90);
    PositionOneButton(NLButton,62,90);
    PositionOneButton(NDButton,98,90);
    PositionOneButton(NIButton,26,126);
  end
  else begin
    PositionOneButton(NMButton,26,54);
    PositionOneButton(NDButton,62,54);
    PositionOneButton(NCButton,98,54);
    PositionOneButton(NLButton,26,90);
    PositionOneButton(NXButton,62,90);
    PositionOneButton(NVButton,98,90);
    PositionOneButton(NIButton,26,126);
  end;
  FrmDrawForm(FrmGetActiveForm);
  InitCalcDisplay;
end;


Procedure InitCalc;
begin
  DoStop:=False;
  FormLoad:=False;
  FormOpen:=False;
  NumLatin:='';
end;


Function ReverseOneNumeral(C: Char): Integer;
Var
  N: Integer;
begin
  N:=0;
  case C of
    One:         N:=1;
    Five:        N:=5;
    Ten:         N:=10;
    Fifty:       N:=50;
    OneHundred:  N:=100;
    FiveHundred: N:=500;
    OneThousand: N:=1000;
  end;
  ReverseOneNumeral:=N;
end;


Function ApplySubstractRule(C1,C2: Char): Integer;
begin
  ApplySubstractRule:=ReverseOneNumeral(C2)-2*ReverseOneNumeral(C1);
end;


Function CheckSubstractRule(S: String): Boolean;
begin
  CheckSubstractRule:=(S=One+Five) or (S=One+Ten) or
                      (S=Ten+Fifty) or (S=Ten+OneHundred) or
                      (S=OneHundred+FiveHundred) or (S=OneHundred+OneThousand);
end;


Function CheckValidTriplet(NS1,NS3: Char): Boolean;
begin
  if (ReverseOneNumeral(NS3) mod 10 = 0) then
    CheckValidTriplet:=(ReverseOneNumeral(NS1)>=ReverseOneNumeral(NS3))
  else
    CheckValidTriplet:=(ReverseOneNumeral(NS1)>ReverseOneNumeral(NS3));
end;


Function CheckAddNumeral(N1,N2: LongInt): LongInt;
Var
  NString: String;
  NS1,NS2,NS3: Char;
  AddNumeral: LongInt;
  N: Integer;

begin
  NString:=CalcNumLatin(N1)+CalcNumLatin(N2);
  if Length(NString)>2 then
    NS1:=NString[Length(NString)-2]
  else
    NS1:=' ';
  if Length(NString)>1 then
    NS2:=NString[Length(NString)-1]
  else
    NS2:=' ';
  NS3:=NString[Length(NString)];
  if (NS1=' ') and (NS2=' ') then
    AddNumeral:=N2
  else
    if (NS1=' ') then
      if CheckSubstractRule(NS2+NS3) then
        AddNumeral:=ApplySubstractRule(NS2,NS3)
      else
        if ReverseOneNumeral(NS2)>=ReverseOneNumeral(NS3) then
          AddNumeral:=N2
        else
          AddNumeral:=0
    else
      if CheckSubstractRule(NS1+NS2) then
        if ReverseOneNumeral(NS1)>ReverseOneNumeral(NS3) then
          AddNumeral:=N2
        else
          AddNumeral:=0
      else
        if CheckSubstractRule(NS2+NS3) then
          if CheckValidTriplet(NS1,NS3) then
            AddNumeral:=ApplySubstractRule(NS2,NS3)
          else
            AddNumeral:=0
        else
          if ReverseOneNumeral(NS2)>=ReverseOneNumeral(NS3) then
            AddNumeral:=N2
          else
            AddNumeral:=0;
  if AddNumeral=0 then
    case Alerte of
      aSND: SndPlaySystemSound(sndStartUp);
      aPOP: N:=FrmAlert(BadInput1);
    end;
  CheckAddNumeral:=AddNumeral;
end;


Procedure AddArab2(N: LongInt);
begin
  if NumArab2=Void then
    NumArab2:=0;
  case InputMethod of
    0 : inc(NumArab2,N);
    1 : inc(NumArab2,CheckAddNumeral(NumArab2,N));
  end;
  DrawNumbers(mTWO);
end;


Procedure Calculate(C: TOper);
  Function StrictOperator(Op: TOper): Boolean;
  begin
    if Op=cEQU then
      StrictOperator:=False
    else
      StrictOperator:=True;
  end;
  Procedure CalculateIt;
  Var
    N1,N2: LongInt;
    R1,R2: Real;
  begin
    case Oper of
      cADD: inc(NumArab1,NumArab2);
      cSUB: dec(NumArab1,NumArab2);
      cMUL: begin
              N1:=NumArab1;
              N2:=NumArab2;
              R1:=NumArab1;
              R2:=NumArab2;
              if (N1*N2)=(R1*R2) then
                NumArab1:=NumArab1*NumArab2
              else
                NumArab1:=-1;
            end;
      cDIV: if NumArab2=0 then
              NumArab1:=-1
            else
              NumArab1:=NumArab1 div NumArab2;
      cEQU: if NumArab2>0 then
              NumArab1:=NumArab2;
    end;
    DrawNumbers(mONE);
    Oper:=C;
    NumArab2:=Void;
  end;
begin
  if (NumArab2=Void) and StrictOperator(Oper) then
    if not(StrictOperator(C)) then begin
      NumArab2:=NumArab1;
      CalculateIt;
    end
    else
      Oper:=C
  else
    CalculateIt;
end;


Function HandleEvent(var Event: EventType): Boolean;
var
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
      PositionButtons;
      //the 2 next procedure lines now included in PositionButtons procedure
      //FrmDrawForm(FrmGetActiveForm);
      //InitCalcDisplay;
      FormOpen:=True;
      HandleEvent:=True;
    end;
  ctlSelectEvent:
    case Data.CtlEnter.ControlID of
      MCButton:  begin
                   NumMem:=0;
                   if NumArab2>0 then
                     DrawNumbers(mTWO)
                   else
                     DrawNumbers(mONE);
                   HandleEvent:=True;
                 end;
      MRButton:  begin
                   if Oper=cEQU then begin
                     NumArab1:=NumMem;
                     NumArab2:=Void;
                     DrawNumbers(mONE);
                   end
                   else begin
                     NumArab2:=NumMem;
                     DrawNumbers(mTWO);
                   end;
                   HandleEvent:=True;
                 end;
      MPButton:  begin
                   if NumArab2>0 then begin
                     inc(NumMem,NumArab2);
                     NumArab1:=NumArab2;
                     NumArab2:=Void;
                   end
                   else
                     inc(NumMem,NumArab1);
                   DrawNumbers(mONE);
                   HandleEvent:=True;
                 end;
      CEButton:  begin
                   NumArab2:=0;
                   DrawNumbers(mTWO);
                   NumArab2:=Void;
                   HandleEvent:=True;
                 end;
      CButton:   begin
                   CReset;
                   DrawNumbers(mONE);
                   HandleEvent:=True;
                 end;
      NXButton:  begin
                   AddArab2(10);
                   HandleEvent:=True;
                 end;
      NVButton:  begin
                   AddArab2(5);
                   HandleEvent:=True;
                 end;
      NIButton:  begin
                   AddArab2(1);
                   HandleEvent:=True;
                 end;
      NCButton:  begin
                   AddArab2(100);
                   HandleEvent:=True;
                 end;
      NLButton:  begin
                   AddArab2(50);
                   HandleEvent:=True;
                 end;
      NMButton:  begin
                   AddArab2(1000);
                   HandleEvent:=True;
                 end;
      NDButton:  begin
                   AddArab2(500);
                   HandleEvent:=True;
                 end;
      DIVButton: begin
                   Calculate(cDIV);
                   HandleEvent:=True;
                 end;
      MULButton: begin
                   Calculate(cMUL);
                   HandleEvent:=True;
                 end;
      SUBButton: begin
                   Calculate(cSUB);
                   HandleEvent:=True;
                 end;

      ADDButton: begin
                   Calculate(cADD);
                   HandleEvent:=True;
                 end;
      EQUButton: begin
                   Calculate(cEQU);
                   HandleEvent:=True;
                 end;
    end;
  menuEvent:
    case Data.Menu.ItemID of
      MenuMethod: begin
                    case InputMethod of
                      0: InputMethod:=FrmAlert(Input1);
                      1: InputMethod:=FrmAlert(Input2);
                    end;
                    HandleEvent:=True;
                  end;
      MenuAlert:  begin
                    case Alerte of
                      aPOP: N:=FrmAlert(InputAlert1);
                      aSND: N:=FrmAlert(InputAlert2);
                    end;
                    if N=0 then
                      Alerte:=aPOP
                    else
                      Alerte:=aSND;
                    HandleEvent:=True;
                  end;
      MenuButt:   begin
                    Layout:=FrmAlert(ButtonLayout1);
                    PositionButtons;
                    HandleEvent:=True;
                  end;
      MenuCopy:   begin
                    ClipboardAddItem(clipboardText,NumLatin,Length(NumLatin));
                    HandleEvent:=True;
                  end;
      MenuReset:  begin
                    CReset;
                    NumMem:=0;
                    InitCalcDisplay;
                    HandleEvent:=True;
                  end;
      MenuQuit:   begin
                    DoStop:=True;
                    HandleEvent:=True;
                  end;
      MenuHelp:   begin
                    N:=FrmAlert(Help1);
                    HandleEvent:=True;
                  end;
      MenuInput:  begin
                    N:=FrmAlert(Help2);
                    if N=1 then FrmHelp(HelpInput1);
                    HandleEvent:=True;
                  end;
      MenuTips:   begin
                    N:=FrmAlert(Tip1);
                    HandleEvent:=True;
                  end;
      MenuDonate: begin
                    FrmHelp(HelpAbout2);
                    HandleEvent:=True;
                  end;
      MenuAbout:  begin
                    N:=FrmAlert(About1);
                    if N=1 then
                      FrmHelp(HelpAbout2);
                    HandleEvent:=True;
                  end;
    end;
  end;
end;


Procedure DoCalc;
Var
  N: Integer;
begin
  N:=Rnd(100);
  case N of
    96,97,98,99:  begin
              NumMem:=0;
              if NumArab2>0 then
              DrawNumbers(mTWO)
              else
                DrawNumbers(mONE);
            end;
    91,92,93,94,95:  if Oper=cEQU then begin
              NumArab1:=NumMem;
              DrawNumbers(mONE);
            end
            else begin
              NumArab2:=NumMem;
              DrawNumbers(mTWO);
            end;
    86,87,88,89,90:  begin
              if NumArab2>0 then begin
                inc(NumMem,NumArab2);
                NumArab1:=NumArab2;
                NumArab2:=0;
              end
              else
                inc(NumMem,NumArab1);
              DrawNumbers(mONE);
            end;
    81,82,83,84,85:  begin
              NumArab2:=0;
              DrawNumbers(mTWO);
            end;
    76,77,78,79,80:   begin
              CReset;
              DrawNumbers(mONE);
            end;
    21,22,23,24,25,26,27,28,29,30:  AddArab2(10);
    11,12,13,14,15,16,17,18,19,20:  AddArab2(5);
    1,2,3,4,5,6,7,8,9,10:  AddArab2(1);
    41,42,43,44,45:  AddArab2(100);
    31,32,33,34,35,36,37,38,39,40:  AddArab2(50);
    100:  AddArab2(1000);
    46,47,48,49,50:  AddArab2(500);
    51,52,53,54,55: Calculate(cDIV);
    56,57,58,59,60: Calculate(cMUL);
    61,62,63,64,65: Calculate(cSUB);
    66,67,68,69,70: Calculate(cADD);
    71,72,73,74,75: Calculate(cEQU);
  end;
end;


Procedure Main;
var
  Event: EventType;
  Error: UInt16;
begin
  RctSetRectangle(WorkRect, 0, 16, 160, 128);
  FrmGotoForm(MainForm);
  Repeat
    EvtGetEvent(Event, 5);
    if not SysHandleEvent(Event) then
      if not MenuHandleEvent(MyMenu,Event,Error) then
        if not FrmDispatchEvent(Event) then
          if not HandleEvent(Event) then
            if (FormLoad and FormOpen) then
              if TurnsToPlay>0 then begin
                DoCalc;
                dec(TurnsToPlay);
              end
              else
                DoStop:=True;
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
  TurnsToPlay:=1900;

  CReset;
  NumMem:=0;
  InputMethod:=1;
  Alerte:=aSND;
  Layout:=0;
end;

Procedure SpeedEnd;
Var
  N: LongInt;
begin
  N:=StopTimer;
  N:=frmCustomAlert(ResultWindow,'SNumerus test lasted ',l2s(N),' seconds.');
end;


begin
  if Initialize then begin
//    LoadPreferences;
    StartTimer;
    InitCalc;
    SpeedBeg;
    Main;
    SpeedEnd;
  end;
end.
