/*
	File:				

	Description:	TwMpTNA Readme

	Author:		

	Copyright:	Copyright © 2004 by Tapwave, Inc.

	Disclaimer:	IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
			use is subject to and governed by terms and conditions of the Software Development 
			Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
			into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
			to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
			You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
			or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

This example is intended to show how to create a Tapwave Native
Application and use the Tapwave TwMp APIs. TwMpTNA is a Tapwave Native
Application which uses the Tapwave APIs. A Tapwave Native Application
means it has a 68K stub that calls the game in ARM mode. A core set of
PalmOS APIs have been made available for use in the ARM mode, plus the
Tapwave APIs. The main exception are UI APIs, which most games are not
expected to need.  

The TwMpTNA sample application demonstrates how to take advantage of the
TwMp multiplayer game startup methods to start a two player game over
bluetooth.  For an example of how to use TwMp for more players please
examine the TwMpTest sample.  The UI and graphics methods in this game
are primitive and it is recommended that you look to other samples for
help in that area.  This TNA Application is unlike others in that there
is some code of consequence to examine in the 68K stub.  The code to 
replace default invitation dialog has to be in the 68K stub.  

To run the app make sure TwMpTNA is present on the device or an SD card inserted
into a device.  On the game host, start the application and select the other player.
once the game is established the two devices will alternate counting from 0.  
Pressing any key will bring up a dialog to either host or leave the game depending
on what is appropriate.  

--------------------------------------------------------------
Build Instructions
--------------------------------------------------------------

The code is compiled using Metrowerks CodeWarrior v9.3 for Palm for
the Tapwave Native Application and Visual Studio for the Palm
Simulator.

To build the Tapwave Native Application, open the TwMpTNA.mcp file and
make. The mcp project files has two targets. One is the ARMlet target,
which compiles the ARM code. The whole game is in this target. The
other target is the Application. This has the 68K code to launch the
ARMlet. Making this target also makes the ARMlet target, because it
includes the ARMlet target and is dependent on it. The Zing.prc
should be copied to the \Palm\Launcher folder of an SD card and then
run on the device.

This sample uses bluetooth, which cannot be simulated.  So no simulater
project file is provided.  
