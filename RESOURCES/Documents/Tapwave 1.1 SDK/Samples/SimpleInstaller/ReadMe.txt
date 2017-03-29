/*
	File:				

	Description:	SimpleInstaller Readme

	Author:		

	Copyright:	Copyright © 2003-4 by Tapwave, Inc.

	Disclaimer:	IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
			use is subject to and governed by terms and conditions of the Software Development 
			Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
			into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
			to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
			You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
			or visiting Tapwave at http://www.tapwave.com/developers/.
				
*/

This is a sample project illustrating the use of the Desktop Support API -- including 
the Tapwave extension for installing Palm OS applications and their data files to 
the handheld.  It represents a real-life application scenario where an application 
needs to be installed onto a device along with one or more data files.  See the
"High Performance Games" document for more information about why you may want to 
include an installer with your application.

This sample shows how to install an application onto the device along with two 
sample files.  The sample files are installed onto a media expansion card.

The following contains a brief description of the basic topics covered by this 
example:

1) Generic installer functionality
2) Use of the InstAide.DLL and UserData.DLL functions to enumerate registered 
   Hotsync users: UmGetUserCount(), UmGetUserID(), UmGetUserName()
3) Use of InstAide.dll to obtain the list of available slots on particular 
   user’s device account and presenting it to the user: UmSlotGetCount(), UmSlotGetInfo()
4) Use of the InstAide.dll functions for installing files to RAM and media slot 
   by directory: PltInstallFile(), PlmSlotInstallFileToDir(), PlmSlotInstallFile()

--------------------------------------------------------------
File Descriptions
--------------------------------------------------------------

Below is a list of the project files with short descriptions:

SimpleInstaller.dsw, SimpleInstaller.dsp
Visual Studio 6 workspace and project files. Use the .dsw file to open the project. 

SimpleInstaller.cpp
Main program file, defines the program entry point WinMain()

Select.cpp
Exports the top-level Select() function called by WinMain() in SimpleInstaller.cpp.
Implements the installation preference collection screen where the user enters data 
necessary for the installation completion.
 
Install.cpp
Exports the top-level Install() function called by WinMain() in SimpleInstaller.cpp.
Perform the actual installation (or installation scheduling) of the desired files to 
the handheld by using the data in the installation project file and the data collected 
by Select().
 
Message.cpp
Exports the top-level LastMessage() function called by WinMain() in SimpleInstaller.cpp.
Displays a typical "Done" dialog with instructions for installation completion or reports 
the error possibly returned by Install().
 
SimpleInstaller.rc, SimpleInstaller.rc.hpp
Project resource file and automatically created header. 

SimpleInstaller.ini
The installer application's project file, that is, the file that contains the information 
what to install and where. Do not confuse with the source code project file; this is used 
by the program we create to avoid hard coding file names and make it more flexible.  The
ini file must have the same name as the executable file.  See the sample .ini file for
more information about the format of the file.

SimpleInstaller.sln, SimpleInstaller.vcprj
Visual Studio.NET 2003 solution and project files. Use the .sln file to open the project. 

--------------------------------------------------------------
Notes
--------------------------------------------------------------

There are a lot of comments in the source files for this project; you will surely want 
to look at those for some extra notes and details.
  
Note that while the sample illustrates the basics of creating an installer for your Palm OS 
application, it does not have enough functionality for a robust installer. One important 
component it misses is the ability to compact all project and installer files into one 
single redistributable package appropriate for distribution; the good news is there are many 
available solutions to that problem, starting with any popular compressing utility such as 
WinZIP® or StuffIt Expander®.
 
This installer does not undo (rollback) the already scheduled installation files in case one 
of them fails to register for installation. This is something to watch for in your installations as 
it may result in negative user experience.
 
One very common reason for install failure is the availability of files with same name already scheduled 
for installation; you may want to handle this specific error code returned by the install functions and 
ignore it, or, better yet, make sure there are no pending installations before yours; it is a good idea 
to ask the user to synchronize once before they run an installation.

--------------------------------------------------------------
Build Instructions
--------------------------------------------------------------

The project is written in C for Microsoft® Visual Studio. Project files are included for Visual Studio 6 
and Visual Studio 2003. Users of Visual Studio 2002 or other compilers will have to import or manually 
create the necessary files for the build.

Users of VS 6 should open the SimpleProject.dsw file and run build.
Users of VS.NET 2003 should open the SimpleProject.sln file and run build.

The executable file needs to have the installation project INI file in the same directory where it runs 
from; all Palm files should be defined and available relative to that directory.

Another important thing to mention is that the program uses DELAY LOAD for the Hotsync DLLs; if you are 
importing .dsw project into VS.NET 2002 you will need to explicitly specify the DELAY LOAD DLLs. You can 
copy the neccessary lines from the .vcprj file.

--------------------------------------------------------------
Version 1.1.0.0 Updates
--------------------------------------------------------------

The SimpleInstaller.exe now has a version resource, which has been updated to 1.1.0.0 to
distinguish it from the first version which had no version resource.  A suggested scheme for
maintaining the version is: the first two digits are Tapwave-maintained and represent major
architecture revisions and minor functionality upgrades, respectively.  The third number represents
bug fix releases by Tapwave.  The fourth number should be developer-maintained to differentiate 
developer-modified versions from the standard Tapwave-released source base.

The principal differences between 1.1.0.0 and 1.0 are:

- Tolerance of different Path, DesktopPath and HotSyncPath registry keys (a weird condition
that some users have - caused 'Hotsync not found' messages).
- Some internal cleanup - use of constants, uses debug libraries in debug builds
- Sort the list of users
- Has a scrollbar in the user list - now handles more than 6 users
- Improved and extra error messages
- Better library version checking



