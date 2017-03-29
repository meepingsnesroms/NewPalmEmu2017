/*
	File:		CompatibleGame Readme		

	Description:	

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


This example is intended to show what is needed to get a game 
running on a TapWave device as quickly as possible.  It hopefully
provides a lot of ideas, and may even be suitable as a starting
base.  This example is meant to be as compatible as possible with
other Palm OS devices, including using standard Palm OS drawing
functions.

In the model used, graphics are composed in a frame buffer in 
general RAM using either the Palm API or custom code.  
The results are then copied to the screen bufferlocated in the 
graphics chip.  Note that the graphics are composed of a series
of different colored blocks (representing shallow and deep water).

The game cycle timing is kept using the machine tick mechanism
(100 per second).

Sound is not shown.

The vibrator is not shown.

Game saving is not shown.

Game high score reporting is not shown.

Wireless connections are not shown.

The code is compiled using Metrowerks CodeWarrior v8 for Palm OS.

Note that this sample is not meant to show optimized or high 
performance graphics.