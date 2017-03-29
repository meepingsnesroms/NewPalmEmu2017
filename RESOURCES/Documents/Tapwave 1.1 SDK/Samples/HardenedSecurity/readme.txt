/*
	File:		Readme.txt	

	Description:	HardenedSecurity Readme

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

This example is intended to provide a starting poing for protecting an application
using the Tapwave Digital Right's Management APIs.

You should not simply copy-and-paste the code from this sample into your application.
Doing so will make it easy for a hacker to write a tool that searches for particular code
patterns and removes them.  Instead, this read-me describes the techniques to use
and the sample provides one example of how to use those techniques.

First of all, an application should make an effort to validate that the Tapwave DRM system
is working correctly.
1) Validate the Tapwave ROM using the SystemKey by reading the system key directly from
   the EEPROM.  You can read this key using the TwSecurity API however a hacked ROM
   could easily supply a different key.
2) Check to make sure the TwSecurity function pointers are pointing to the correct place
   in ROM.
3) Confirm that the Tapwave Copy Protection is validating things that are valid and
   rejecting things that are invalid.

Secondly, the application should make an effort to validate itself by using the
Tapwave DRM system.  These checks should be distributed throughout the application to
make it more difficult to hack.
1) Validate the application signature with your own key (if you sign your application
   using your own private key).
2) Validate that the public key stored in the application hasn't been tampered with
   by using various checksums, hashes, or direct checks (with multiple whole or
   partial copies).
3) Call TwValidateApp at many places in the application.

This sample includes a build flag called SECURE_BUILD which turns on and off the TwSecurity
checks.  If this flag is false, then you can simply compile and debug the sample provided
that you have a developer access PRC for the Simulator or device.  If this flag is true, then 
the sample requires an application signature and is a bit more complicated.  Use the following 
steps in the latter case:
1) Build the sample.
2) Sign your testing resources with your private key (if you sign your application using
   a private key).  The testing resources should be something useful such as a bitmap
   or form resource.
3) Sign the sample with the Tapwave Signing Server.
4) Sign the application's signature with your own private key and store the result in a
   non-validated resource (either using a skip list or by setting the MSB of the resource
   type to 1).

This sample demonstrates how to test the following:
1) TwSecurity is validating correctly.
2) The Tapwave ROM is signed using the EEPROM system key.
3) The public application key hasn't been tampered with.
4) The application signature is using a valid application key.
5) Calls to TwVerifyApplication work correctly.
6) The TwSecurity pointer is correct and pointing to the correct place
   in Tal.prc.

Note that implementing 3 and 4 might seem complicated, but are very powerful as they
validate the current application signature which validates everything else.

WARNING!  Do not simply copy-and-paste this sample code into your application. Understand
the mechanism used and write your own code.  This will make it a lot harder to break
copy protection in your application.

--------------------------------------------------------------
Build Instructions
--------------------------------------------------------------

The VerifySignature code is compiled using Metrowerks Codewarrior v8 for Palm OS.