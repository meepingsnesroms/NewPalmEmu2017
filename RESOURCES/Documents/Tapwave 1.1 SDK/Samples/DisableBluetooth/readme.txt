/*
	File:		Readme.txt	

	Description:	DisableBluetooth Readme

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

This example demonstrates how to properly detect whether Bluetooth 
is on and disable it.  It also shows how to intercept the bluetooth 
keys to keep bluetooth from being turned on.  

The important functions to examine are TurnOffBluetooth and AppEventLoop.  

------------------------------------------------------------
Build Instructions
------------------------------------------------------------

The code is compiled using Metrowerks CodeWarrior v9.3 for Palm OS.