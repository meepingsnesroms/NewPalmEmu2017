# Microsoft Developer Studio Project File - Name="MultiPlayerExample" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=MultiPlayerExample - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MultiPlayerExample.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MultiPlayerExample.mak" CFG="MultiPlayerExample - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MultiPlayerExample - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "MultiPlayerExample - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MultiPlayerExample - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\..\..\xforge\include" /I "..\..\..\include" /D "NDEBUG" /D "XFC_PLATFORM_DESKTOPWINDOWS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "NDEBUG"
# ADD RSC /l 0x40b /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 xfcore.lib xfutil.lib kernel32.lib user32.lib gdi32.lib shell32.lib winmm.lib wsock32.lib zlib.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBC.lib" /libpath:"..\..\..\..\..\xforge\lib\windows"

!ELSEIF  "$(CFG)" == "MultiPlayerExample - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\..\xforge\include" /I "..\..\..\include" /D "XFC_DEBUG" /D "_DEBUG" /D "XFC_PLATFORM_DESKTOPWINDOWS" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40b /d "_DEBUG"
# ADD RSC /l 0x40b /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 xfcored.lib xfutild.lib kernel32.lib user32.lib gdi32.lib shell32.lib winmm.lib wsock32.lib zlib.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCD.lib" /pdbtype:sept /libpath:"..\..\..\..\..\xforge\lib\windows"

!ENDIF 

# Begin Target

# Name "MultiPlayerExample - Win32 Release"
# Name "MultiPlayerExample - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\source\ConnectingScreen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\GameScreen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\MainMenuScreen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\MultiPlayerExample.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\MultiPlayerHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\Screen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\source\UIImageFactory.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\include\AppStates.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\ClientListEntry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\ClientStateEntry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\ConnectingScreen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\GameScreen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\GameState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\MainMenuScreen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\MultiPlayerExample.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\MultiPlayerHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Packets.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Screen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\UIImageFactory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\Widget.h
# End Source File
# End Group
# End Target
# End Project
