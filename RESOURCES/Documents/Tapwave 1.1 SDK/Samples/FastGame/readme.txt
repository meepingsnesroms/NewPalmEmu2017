/*
	File:				

	Description:	FastGame Readme

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


This example is intended to show what is needed to get a game running on
a TapWave device as quickly as possible. FastGame is a Tapwave Native Application 
which uses the Tapwave APIs. A Tapwave Native Application means it has a 68K 
stub that calls the game in ARM mode. A core set of PalmOS APIs have been made 
available for use in the ARM mode, plus the Tapwave APIs. The main exception are 
UI APIs, which most games are not expected to need.

FastGame is similar to the CompatibleGame model, except it is faster. It is faster
principally because it's using the TwGfx calls for hardware accellerated
graphics, but also because it's a Tapwave Native Application.

-------------------------------------------------------------
Game Engine
-------------------------------------------------------------

In the model used in FastGame, graphics are composed in a frame buffer in
the dynamic heap using the TwGfx APIs. The results are then copied to
the screen buffer located in the graphics chip.  Note that the graphics are 
composed of a series of different colored blocks (representing shallow and 
deep water).

The game cycle timing is kept using the machine tick mechanism (1000 per
second). This is managed by the application.

You'll notice that two gauges are provided for performance analysis.

The top gauge shows frames per second in a numeric and graphical representation.  
The frames decline over time because more time is spent drawing the graphical 
representation of the gauge.

The bottom gauge shows the number of milliseconds per frame.  It currently uses 
TimGetTicks which has a granularity of 10ms.

Note that sound, vibration, saving game state, high score reporting, and wireless
connectivity are not shown in this sample.

-------------------------------------------------------------
Build Instructions
-------------------------------------------------------------

The code is compiled using Metrowerks CodeWarrior v9.3 for Palm for the
Tapwave Native Application and Visual Studio for the Palm Simulator.

To build the Tapwave Native Application, open the FastGame.mcp file and 
make. The mcp project files has two targets. One is the ARM target, which compiles
the ARM code. The whole game is in this target. The other target is
the Application. This has the 68K code to launch the ARM code. Making this
target also makes the ARM target, because it includes the ARM 
target and is dependent on it. The FastGame.prc should be copied to the
\Palm\Launcher folder of an SD card and then run on the device.

To build the DLL, open the FastGame.dsw file and make. Copy the resulting 
FastGame.dll the PalmSim folder. Add the dll to the Visual Studio's PalmSim's 
project setting's Debug tab to enable source level debugging of the dll. Lastly,
HostPalm68K.c currently embeds the dll name. Update this if the app name
changes. Finally copy the prc to somewhere like \PalmSim\Autoload and
then run PalmSim. Obviously the dll will need to be rebuilt and copied
whenever game code changes are made. The prc will need to be rebuilt and
copied whenever resources or 68K code changes.

-------------------------------------------------------------
Future Work
-------------------------------------------------------------

The game menu is not working. It needs fonts. The Palm OS WinPaintChars
could be used, but a more flexible model using custom fonts is tried. It
works except the font image is larger than 64KB so Pilrc rejects it and
then fails the link step. Zlib is partially added to support gzip
compression, but it's not working. For now the fonts, zlib, and gzip
parts are not used and should be ignored.
