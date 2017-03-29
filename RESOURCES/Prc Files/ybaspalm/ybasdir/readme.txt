HotPaw(tm) Basic for the PalmOS Computing Platform

HotPaw Basic is a full-featured and easy-to-use scripting language
which allows you to create and execute small Basic programs directly
on your Palm handheld organizer/computer.

The BASIC language has been around for 3 decades; it's continued
popularity is due to its simplicity and ease of learning.  HotPaw
brings this language to the palm of your hand and enables you to
better use your Palm handheld as a true personal computer.

HotPaw Basic has many features including:
  - over 75 functions and 30 commands built-in;
  - execution of Basic programs contained in your MemoPad;
  - simple built-in dialogs for displaying results and prompting for
    input parameters;
  - custom form creation with user definable buttons, fields and
    checkboxes;
  - access to several standard database formats (HanDBase, MiniCalc,
    JFile and List) instead of a proprietary format; can also
    access data and run programs contained in pedit32 and Doc files.
  - sound, morse code and graphics drawing commands (including COLOR
    support for filled circles, pie charts, triangles, and bitmaps);
  - programmable ToDo, Datebook appointment and alarm creation;
  - serial port, infrared port and internet socket access;
  - support for all keywords in the ANSI/ISO Minimal BASIC programming
    language standard, as well as many MSBasic(tm) functions and
    statements;
  - support for double precision floating point arithmetic and for
    the MathLib transcendental function library;

HotPaw Basic comes with several example programs, as well as a small
application which allows you to start a Basic program directly from
the Application Launcher (or even a button press).

Please see the HotPaw Basic Quick Reference (quickref.txt) for details
on the features, commands and functions contained in HotPaw Basic 

The manpage.txt document contains a unix man page description of
the Basic language (but without the PalmOS special functions).

The latest versions of HotPaw Basic documentation can be found at:

  <http://www.hotpaw.com/rhn/hotpaw/cbpb-readme.txt>  
  

***
Installation:

  Install the usual way, using the 3Com/Palm Install and HotSync
  utilities on a Windows or MacOS based PC, or using the linux
  pilot-xfer utility on a computer running linux or unix.
  
Installing HotPaw Basic programs:

  Basic programs are text files or memos containing statements in the
  Basic language.  The HotPaw Basic application can run Basic programs
  whose text is contained in memos of the built-in Palm MemoPad.
  
  If you have a HotPaw compatible Basic program on your desktop PC,
  you can copy and paste the Basic program text into the Desktop
  MemoPad application and HotSync.  On a linux system, you can use
  the pilot-link install-memo utility to copy a short text file into
  your Palm MemoPad.
  
  There are also HotPaw Basic applets.  When installed the icons of
  these applets will appear in the Palm launcher; these applets can be
  started the standard way be tapping on the application icon.
  HotPaw Basic must be installed for these applets to function.
    
Getting Started:

  Try entering a short Basic program into your Palm MemoPad.
  Start a new memo (any category).

  Any memo starting with the '#' character and ending with the
  4 characters ".bas" in the first line will be recognized as a
  Basic program in the HotPaw Basic Show Programs selection screen.
  
  Here's an example first line:
  
# My_Example_1.bas

  Here's a short test program that will ask you to guess a number:
  
    # guess_a_number.bas
    x = 0
    # set the variable "secret" to a number between 1 and 5
    secret = 1 + rnd(5)
    while (x <> secret)
      input "Guess a number between 1 and 5", x
    wend
    display x; " is correct!"
    end
    
  Switch to the Basic application.  If there is not a border around
  a list of programs, use the menubar to select "Show Programs".
  If you can't see your new program, check the name to make sure it
  starts with a # and ends with .bas on the first line.
  
  Select your program and hit the "Exec" button to execute it.
  
  If you use the Hackmaster extension utility, then try using the
  SwitchHack extension to switch back and forth between Basic to
  the MemoPad application when writing and testing your Basic
  programs.
  
  The "Show ScratchPad" is for small calculations that do not require
  any loops or subroutines.  Just enter a list of equations and a
  print statement for the result, then the statements you wish
  executed, and hit the "Exec" button.
  
  Other example HotPaw Basic programs are in the yb_tutorial.txt file.
  
  
***
Important Notes and Limitations regarding this version:

  - Please see the LICENSE included in this document for important
    terms and limitations.  If you do not agree with the license
    you are not authorized to use the HotPaw Basic application.
    
  - PalmOS 3.0 or later (Palm III, Palm Vx, etc.) is REQUIRED.
  
  - The MathLib.prc (1.0 or 1.1) library is required.  See:
      <http://www.probe.net/~rhuebner/mathlib.html>  or
      <ftp://ftp.rahul.net/pub/rhn/mathlib11.zip>
  
  - The use of the SwitchHack extension for switching between the
    MemoPad and the HotPaw Basic interpreter is highly recommended.
   
  - This application is still being tested to find and remove bugs
    in the application and errors in the documentation.  Please be
    sure to make backup copies of all your important data prior to
    installing and using this application.
    
  - The documentation is still very very preliminary, is subject to
    change without notice, and may not completely or accurately
    describe the current version of HotPaw Basic.
    
    * New improved documentation is currently under development *

  - The database name of this version of HotPaw Basic, "yBasic",
    may change to "Basic" in future versions.
    
The latest version of this documentation can be found at:

  <http://www.hotpaw.com/rhn/hotpaw/cbpb-readme.txt>  
  

***
FAQ:

  Q: How do I share my Basic programs?
  
  A: Because HotPaw Basic programs are contained in MemoPad
     memo's as plain text, one can HotSync them to the desktop
     and email (or post on the web) the contents of these memo's
     as text files.
  
  Q: Can HotPaw Basic compile stand-alone prc applications?
  
  A: No.  A compiler is a completely different, much bigger,
     and far more complex application. 
     
     There are already a several compilers for Palm handhelds,
     among them Quartus Forth for on-board compilation, and
     Metrowerks Codewarrior for Palm for a complete Mac/Win
     hosted IDE.
     
     HotPaw Basic is designed for people who want to be able
     to see and modify programs and scripts directly on their
     Palm handheld.
     
  Q: What's the difference between HotPaw Basic and cbasPad?
  
  A: cbasPad classic was written as a spare evening hobby in 1996
     for Palm Pilot 1000's and 5000's running PalmOS 1.0 with only
     128k/512k of memory.  Some of the arithmetic and math routines
     built into PalmOS 1.0, which cbasPad classic depends upon, are
     neither reliable nor accurate.  Also, because of its design for
     the single segment restriction of PalmOS 1.0, cbasPad classic
     is no longer expandable.  In spite of its limitations,
     cbasPad classic will remain free for non-commercial and
     non-mission-critical use on old PalmOS 1.0 and 2.0 devices.
     
     HotPaw Basic was written to take advantage of Palm 3.x and
     has double the feature set and a much more accurate math
     calculation capability.

  Q: Where are the other FAQs?
  
  A:  There are several PalmPilot related FAQ's on the Web. 
      Try these URL's:
	<http://www.nicholson.com/rhn/palmfaq.txt>
  	<http://www.palmpilotfaq.com/>


***********************************************************************
Latest Revision notes :
***********************************************************************

Please see the Quick Reference notes for information about these new
features.

-- HotPaw yBasic Version 1.4.7b0    --	(2010May02)

    Changed registration requirement
    
-- HotPaw yBasic Version 1.4.6b0    --	(2006Jun18)

    Added ^ key alternative (u hat and i hat).
    Allow uppercase BASIC keywords.

-- HotPaw yBasic Version 1.4.5b4    --	(2006Feb20)

    Added delete line to the console mode.
    Fixed 5-way input$() on Treo 650 and similar models.

-- HotPaw yBasic Version 1.4.5    --	(2005Feb20)

    Added fn space$() and fn ltrim$()
    Improved navigation on Treo devices.
    Improved fn solve1() equation solver convergence.
    Fixed input form focus problem on Treo 650.
    Fixed a bug in the db.len function.

-- HotPaw yBasic Version 1.4.4    --	(2004Oct19)
    Fixed a problem with VFS write.
    Fixed syntax error problem when opening serial/IR port.
    Fixed def fn array parameter bug.
    Fixed console input echo.
    Added VFS save & load commands to console mode.
    Added an old-fashioned text console mode.
    Added some Alphasmart Dana widescreen support.
    Added fn qkeyboard() to bring up on screen Keyboard.
-- HotPaw yBasic Version 1.4.1    --	(2004Feb19)
    Added new ITU Morse code character for @
    Added fn todocatname()
    Internal bug fixes for future OS compatibility.
-- HotPaw yBasic Version 1.4.0    --	(2003Dec26)
    Added beta test memo editor command.
    Added beta test simple equation solver function.
    Added cbasPad5 native ARM Basic interpreter support.
    Added floating point ARM endianess byte swap function.
    Updated Bluetooth and IRComm client serial I/O support.
    Updated Edit button operation for Tungsten T3.
    Fixed get$ of long clipboard strings.
    Fixed the text color when drawing OS 5 tiny fonts.
    Fixed a bug in format$().
    Fixed a bug in international string comparisons.
    Fixed a bug in custom About Box support.
    Removed outdated Symbol bar scan support.
    Removed outdated iNetLib support.
-- HotPaw yBasic Version 1.3.9    --	(2003Jul10)
    Fixed a bug in chaining to programs in Doc files. (1.3.9b2)
    Added fn pos(n) for file/memo position.
    Added Beta Test Bluetooth Exchange Manager support (OS 5).
    Added Beta Test IRComm and Bluetooth client serial I/O.
    Fixed a bug in chaining from applets.
    Fixed serial IR mode on some OS 4.1 models (Zire/m150)
-- HotPaw yBasic Version 1.3.8    --	(2003Feb16)
    Added autoscaling parametric plot command.
    Added OS 5 tiny fonts for use with "print at" command.
    Added fn assign2var().
    Added fn val() for International format number conversion.
    Added support for calling native (OS 5+) armlets.
    Added an error message for Memo full.
    Added Beta support for writing to uncompressed Doc files.
    Allow a return character to close input dialog.
    Fixed bug in chaining to Basic programs in Doc files.
-- HotPaw yBasic Version 1.3.7    --	(2002Nov24)
    Added 2d and 3d autoscaling fn plot() commands.
    Added peditPro to pedit32 support.
    Added fn byteswap32().
    Fixed problems with JFile and HanDBase record creation.
    Fixed an if-elseif nesting bug.
    Tested on Tungsten T for OS 5 compatibility.
-- HotPaw yBasic Version 1.3.6    --	(2002Sep24)
    Added customizable About... dialog for your programs.
    Enabled multiline dynamic form fields.
-- HotPaw yBasic beta Version 1.3.5b9  --	(2002Sep19)
    Added fn mean(), fn variance(), and fn stdev()
    Added scrollbars to the program selection form.
    Improved commands for reading vfs and Doc files.
-- HotPaw yBasic beta Version 1.3.5b8  --	(2002Sep15)
    Added matrix invert command.
    Added fn setformkey()
    Fixed a bug in eval()
-- HotPaw yBasic beta Version 1.3.5b5  --	(2002Sep11)
    Fixed a problem with forms under OS 3.5
-- HotPaw yBasic beta Version 1.3.5b4  --	(2002Sep09)
    Added def fn(), tab(), and the option base statement 
    to complete the support of all ANSI Minimal Basic keywords.
    Added assigment operator: x += 1
    Added support for changing fields in dynamic forms.
    Added a command to change checkbox status in dynamic forms.
    Added fn formindex() to get field and checkbox numbers.
    Added the get$("clipboard") function.
    Added a few missing morse code characters.
    Fixed a bug in infrared (IR) string exchanges.
    Fixed one problem with using MIDI (31250) baud rates.
-- HotPaw yBasic beta Version 1.3.5b0  --	(2002Aug29)
    Added the MAT statement for matrix arithmetic.
    Updated support for HanDBase version 3
    Included a bcmd to set the time using fn settime(t).
-- HotPaw yBasic beta Version 1.3.4b8  --	(2002Aug17)
    Fixed a problem with using serial ports under OS 3.5
    Changed morse code timing slightly.
    Added fn sinh(), fn cosh(), fn asinh(), fn acosh()
-- HotPaw yBasic beta Version 1.3.4b6  --	(2002July20)
    Fixed a problem with fn fv(), the future value function.
-- HotPaw yBasic beta Version 1.3.4b4  --	(2002June29)
    Added capability to #include VFS text files.
    Changed val("xyz") from returning NaN to returning 0 .
    Tested for readiness under PalmOS 5.1 Simulator.
    Fixed a problem with using serial ports under OS 3.1.
    Fixed a problem using forms under OS 3.5.
    Fixed a problem with executing an empty selection.
    
-- (see revision history on the website for older revision notes).
	<http://www.hotpaw.com/rhn/hotpaw/versions.txt>  


**********************************************************************
Credits
**********************************************************************
  
  HotPaw Basic ("the Software") is Copyright (c) 1999,2000,2001 by
  Ronald H Nicholson, Jr.,  All Rights Reserved.

  cbasPad and HotPaw Basic are loosely based on the CalTech version
  of Chipmunk Basic 1.0, written by D Gillespie.
  
  Portions of HotPaw Basic contain code which is copyrighted by
  Palm Computing, Inc.

**********************************************************************
LICENSE
**********************************************************************

  LICENSE

  TITLE

  HotPaw Basic ("the Software") is Copyright (c) 1999,2001 by
  Ronald H Nicholson, Jr.,  All Rights Reserved.
  
  Title, ownership rights, and intellectual property rights in the
  Software shall remain with Ronald H Nicholson, Jr.  The Software
  is protected by the copyright laws and treaties of the United
  States of America.

  TERMS

  Ronald H. Nicholson, Jr. grants you the right to use this copy
  of the Software if you agree to the following license terms:
  
  You may use the Software without a license key and in Trial or
  Demo mode for educational or non-commercial purposes.
  
  You may transfer or copy a license key or license key database
  for the Software only if required in the normal use of one PalmOS
  handheld unit.  You may also make one copy of the Software license
  key if required for backup purposes.  You are required to keep
  all HotPaw license keys confidential.  You may not loan, rent,
  transfer or assign the license key to another user except with
  (a) the permission of HotPaw and (b) as a permanent transfer of
  the Software and the license key.
  
  You may not reverse engineer, decompile, or disassemble the
  Software.  
  
  Commercial distribution of the Software is not allowed without
  the express permission of the copyright holder.  Contact HotPaw
  for details about obtaining a license.
  
  Usage of the Software is also subject to the following limitations
  and disclaimers.

  WARRANTY AND DISCLAIMER

  The Software is distributed in the hope that it might be useful,
  but WITHOUT ANY WARRANTY OF ANY KIND; not even the implied
  warranties of MERCHANTABILITY, fitness for ANY particular purpose,
  or for non-infringement of any intellectual property rights.
  
  LIMITATION OF LIABILITY

  UNDER NO CIRCUMSTANCES AND UNDER NO LEGAL THEORY, TORT, CONTRACT,
  OR OTHERWISE, SHALL HOTPAW, RONALD NICHOLSON, OR ITS SUPPLIERS OR
  RESELLERS BE LIABLE TO YOU OR ANY OTHER PERSON FOR ANY INDIRECT,
  SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES OF ANY CHARACTER
  INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF GOODWILL, WORK
  STOPPAGE, COMPUTER FAILURE OR MALFUNCTION, OR ANY AND ALL OTHER
  COMMERCIAL DAMAGES OR LOSSES. IN NO EVENT WILL HOTPAW BE LIABLE
  FOR ANY DAMAGES IN EXCESS OF THE AMOUNT HOTPAW RECEIVED FROM YOU
  FOR A LICENSE TO THIS SOFTWARE, EVEN IF HOTPAW OR RONALD NICHOLSON
  SHALL HAVE BEEN INFORMED OF THE POSSIBILITY OF SUCH DAMAGES, OR
  FOR ANY CLAIM BY ANY OTHER PARTY. THIS LIMITATION OF LIABILITY
  SHALL NOT APPLY TO LIABILITY FOR DEATH OR PERSONAL INJURY TO THE
  EXTENT APPLICABLE LAW PROHIBITS SUCH LIMITATION. FURTHERMORE,
  SOME JURISDICTIONS DO NOT ALLOW THE EXCLUSION OR LIMITATION OF
  INCIDENTAL OR CONSEQUENTIAL DAMAGES, SO THIS LIMITATION AND
  EXCLUSION MAY NOT APPLY TO YOU.
  
  IN THE EVENT THIS SOFTWARE INFRINGES UPON ANY OTHER PARTY'S
  INTELLECTUAL PROPERTY RIGHTS, THE LICENSOR'S ENTIRE LIABILITY
  AND YOUR EXCLUSIVE REMEDY SHALL BE, AT THE LICENSOR'S CHOICE,
  EITHER (A) RETURN OF THE PRICE PAID TO THE LICENSOR AND ITS
  AUTHORISED DISTRIBUTORS OR (B) REPLACEMENT OF THE SOFTWARE WITH
  NON-INFRINGING SOFTWARE.

  LIMITATION OF HIGH RISK ACTIVITIES

  The Software is not fault-tolerant and is not designed,
  manufactured or intended for use or resale as on-line control
  equipment in hazardous environments requiring fail-safe
  performance, such as in the operation of nuclear facilities,
  aircraft navigation or communication systems, air traffic control,
  direct life support machines, or weapons systems, in which the
  failure of the Software could lead directly to death, personal
  injury, or severe physical or environmental damage ("High Risk
  Activities").  Ronald Nicholson, HotPaw, and its suppliers
  SPECIFICALLY disclaim ANY express or implied warranty of fitness
  for High Risk Activities.
  
  This license is governed by the laws of the United States and
  the State of California.  If, for any reason, a court of
  competent jurisdiction finds any provision, or portion thereof,
  of this license to be unenforceable, the remainder of this
  license shall continue in full force and effect.
  
  AGREEMENT

  If you do not agree to the terms of this LICENSE, you are not
  authorized to use the Software.
  
   
***
This documentation is preliminary and subject to change at any
time without notice.
--
Palm, PalmOS and HotSync are trademarks of Palm Computing.
HotPaw and cbasPad are trademarks of the HotPaw company.

Copyright 2005,2010 HotPaw Productions & Ronald H. Nicholson, Jr.
***

