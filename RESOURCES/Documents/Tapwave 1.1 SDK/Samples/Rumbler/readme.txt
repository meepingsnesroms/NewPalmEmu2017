/*
	File:		Readme.txt	

	Description:	Rumbler Readme

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

This example is intended to demonstrate how to use the vibration APIs and how to
incorporate special rumble effects into your game.  After you launch the application
you are presented with two pickers and two buttons.

The upper picker/button combo allows you to issue a vibrate command such as start,
stop, slow, medium, or fast.

The lower picker/button combo allows you to play a special rumble effect.  The
effects include Explosion, Earthquake, Crash, Off-Roading, and Rocket Acceleration.
These effects are preliminary and still need some tweaking.  This sample also
includes some debug code to display the rumble pattern.  This debug code
will be removed in the next SDK.

--------------------------------------------------------------
Build Instructions
--------------------------------------------------------------

The GameStarter code is compiled using Metrowerks Codewarrior 9.3 for Palm OS