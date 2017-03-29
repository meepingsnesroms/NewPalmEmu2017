/*
	File:		Readme.txt	

	Description:	GameStarter Readme

	Author:		

	Copyright:	Copyright © 2003 by Tapwave, Inc.

	Disclaimer:	IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
			use is subject to and governed by terms and conditions of the Software Development 
			Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
			into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
			to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
			You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
			or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

This example is intended to provide a good starting point for creating a
high performance game for the Tapwave platform.  GameStarter is a Tapwave Native 
Application which uses the Tapwave APIs.  See the "High Performance Games" 
document for more information.

GameStarter demonstrates the following:

1) Setting up/Tearing down a Tapwave Native Application properly.
2) Loading/Saving application preferences.
3) Loading a graphic into a TwGfx surface and displaying that surface.
   
This sample also demonstrates the difference between using 
twGfxLocationAcceleratorMemoryNoBackingStore and twGfxLocationAcceleratorMemory 
by toggling the USE_BACKING_STORE define.

Specifying twGfxLocationAcceleratorMemory means that your surface data will be
copied into main memory when the device goes to sleep and copied back into
your surface when the device wakes.  This is necessary due to a bug in the
Zodiac graphics chip.  You'll normally want to specify this location, however
if your surfaces use a lot of VRAM, it may not be possible for the OS to copy
them into main memory.  If this is the case then you'll need to use the
twGfxLocationAcceleratorMemoryNoBackingStore location option instead.

Specifying twGfxLocationAcceleratorMemoryNoBackingStore means that you will need
to manually re-load your surfaces when the device wakes from sleep.  To do this
you should register for the sysNotifyEarlyWakeupEvent notification and re-load
your surfaces as appropriate.

This sample shows how to use both options depending on whether USE_BACKING_STORE
is defined.  If it is defined then the surfaces are created using the
twGfxLocationAcceleratorMemory location.  If it is not defined, then they are
created using twGfxLocationAcceleratorMemoryNoBackingStore and additional code is
compiled showing how to re-load them during the early wake-up event.

--------------------------------------------------------------
Build Instructions
--------------------------------------------------------------

The GameStarter code is compiled using Metrowerks Codewarrior 9.3 for the
Tapwave Native Application and Visual C++ 6.0 for the Palm Simulator.

To build the Tapwave Native Application, open the GameStarter.mcp file and build.  
The MCP project file has two targets: one is the ARM target which compiles the
ARM code, the other is the Application target which compiles the 68k code.
Building the Application target will cause the ARM target to be built
since the ARM target is a dependency.

To build the DLL, open the GameStarter.dsw file and build.