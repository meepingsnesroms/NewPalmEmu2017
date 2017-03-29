/*
	File:		Readme.txt	

	Description:	CodeCompress Readme

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

The Tapwave platform supports uncompressing a compressed code resource at runtime. This 
example is provided to demonstrate how to create a Tapwave Native Application with a 
compressed ARM code resource.  The advantage of this method is that it allows developers 
to create smaller PRCs -- we recommend using this method if your ARMC code resource is 
larger than 64kb.

This example requires gzip to compress the ARM code resource.  You can obtain gzip at
http://www.gzip.org/.  After downloading, be sure to update your "Path" environment
variable appropriately.

------------------------------------------------------------
Build Instructions
------------------------------------------------------------

The CodeCompress code is compiled using Metrowerks Codewarrior 9.3.

To build the Tapwave Native Application, open the GameStarter.mcp file and build.  
The MCP project file has two targets: one is the ARM target which compiles the
ARM code, the other is the 68K target which compiles the 68k code.
Building the Application target will cause the ARM target to be built
since the ARM target is a dependency.

After the ARM target is built, the "BatchRunner" PostLinker will execute the
armz.bat file.  This batch file compresses the ARMC code resource into an ARMZ
resource.  The ARMZ resource is then included in your project rather than the
ARMC code resource.  To accomplish this, the CodeCompress ARM settings have 
two changes from a normal uncompressed project:

1) The "Target Settings" have been changed so that the PostLinker is
"BatchRunner PostLinker".
2) The "Linker Settings" have been modified to include the "armz.bat"
batch file.

Note that you might need to build the "Application" target twice due to a bug
in the CodeWarrior compiler.

------------------------------------------------------------
KNOWN PROBLEMS
------------------------------------------------------------

There is a bug in the CodeWarrior BatchRunner PostLinker such that the armz.bat file
will not excecute correctly when the SDK is installed in the correct location.  You'll 
need to copy this sample to the top level of your hard drive and compile it from there.