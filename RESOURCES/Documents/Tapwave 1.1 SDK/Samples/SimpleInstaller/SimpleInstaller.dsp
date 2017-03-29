# Microsoft Developer Studio Project File - Name="SimpleInstaller" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SimpleInstaller - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SimpleInstaller.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SimpleInstaller.mak" CFG="SimpleInstaller - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SimpleInstaller - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SimpleInstaller - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "Perforce Project"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SimpleInstaller - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "SimpleInstaller___Win32_Release"
# PROP BASE Intermediate_Dir "SimpleInstaller___Win32_Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gz /Zp4 /W4 /O1 /D "NDEBUG" /D "_APP" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FD /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /Gz /Zp4 /W4 /O1 /D "NDEBUG" /D "_APP" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FD /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o".\Release\SimpleInstaller.bsc"
# ADD BSC32 /nologo /o".\Release\SimpleInstaller.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /pdb:".\Release\SimpleInstaller.pdb" /map:".\Release\SimpleInstaller.map" /machine:I386 /out:".\Release\SimpleInstaller.exe"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /pdb:".\Release\SimpleInstaller.pdb" /map:".\Release\SimpleInstaller.map" /machine:I386 /out:".\Release\SimpleInstaller.exe"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "SimpleInstaller - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "SimpleInstaller___Win32_Debug"
# PROP BASE Intermediate_Dir "SimpleInstaller___Win32_Debug"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /Gz /Zp4 /W4 /Zi /Od /Gf /Gy /D "_DEBUG" /D "_APP" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT BASE CPP /YX
# ADD CPP /nologo /Gz /Zp4 /W4 /Zi /Od /Gf /Gy /D "_DEBUG" /D "_APP" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /FR /FD /GZ /c
# SUBTRACT CPP /YX
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo /o".\Debug\SimpleInstaller.bsc"
# ADD BSC32 /nologo /o".\Debug\SimpleInstaller.bsc"
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /incremental:no /pdb:".\Debug\SimpleInstaller.pdb" /map:".\Debug\SimpleInstaller.map" /debug /machine:I386 /out:".\Debug\SimpleInstaller.exe" /pdbtype:sept
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 /nologo /subsystem:windows /incremental:no /pdb:".\Debug\SimpleInstaller.pdb" /map:".\Debug\SimpleInstaller.map" /debug /machine:I386 /out:".\Debug\SimpleInstaller.exe" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "SimpleInstaller - Win32 Release"
# Name "SimpleInstaller - Win32 Debug"
# Begin Group "Sources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Install.cpp
# End Source File
# Begin Source File

SOURCE=.\Message.cpp
# End Source File
# Begin Source File

SOURCE=.\Select.cpp
# End Source File
# Begin Source File

SOURCE=.\SimpleInstaller.cpp
# End Source File
# End Group
# Begin Group "Headers"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SimpleInstaller.hpp
# End Source File
# End Group
# Begin Group "Resources"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\SimpleInstaller.rc
# End Source File
# End Group
# Begin Source File

SOURCE=.\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\SimpleInstaller.ini
# End Source File
# End Target
# End Project
