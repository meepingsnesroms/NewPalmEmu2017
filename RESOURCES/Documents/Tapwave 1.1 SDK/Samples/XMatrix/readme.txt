/*
	File:				

	Description:	XMatrix Readme

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

This example is intended to show how to create a Tapwave Native Application 
and use the Tapwave Gfx APIs. XMatrix is a Tapwave Native Application which 
uses the Tapwave APIs. A Tapwave Native Application means it has a 68K stub 
that calls the game in ARM mode. A core  set of PalmOS APIs have been made 
available for use in the ARM mode, plus the Tapwave APIs. The main exception 
are UI APIs, which most games are not expected to need.

In the model used in XMatrix, graphics are composed in a frame buffer in
the dynamic heap using the TwGfx APIs. The results are then copied to
the screen buffer located in the graphics chip.


Build Instructions

The code is compiled using Metrowerks CodeWarrior v9.3 for Palm for the
Tapwave Native Application and Visual Studio for the Palm Simulator.

To build the Tapwave Native Application, open the Xmatrix.mcp file and make. The mcp
project files has two targets. One is the ARMlet target, which compiles
the ARM code. The whole game is in this target. The other target is
the Application. This has the 68K code to launch the ARMlet. Making this
target also makes the ARMlet target, because it includes the ARMlet
target and is dependent on it. The XMatrix.prc should be copied to the
\Palm\Launcher folder of an SD card and then run on the device.

To build the DLL, open the XMatrix.dsw file and make. Copy the resulting 
XMatrix.dll the PalmSim folder. Add the dll to the Visual Studio's PalmSim's 
project setting's Debug tab to enable source level debugging of the dll.
Finally copy the prc to somewhere like \PalmSim\Autoload and then run PalmSim. 
Obviously the dll will need to be rebuilt and copied whenever game code changes 
are made. The prc will need to be rebuilt and copied whenever resources or 68K 
code changes.