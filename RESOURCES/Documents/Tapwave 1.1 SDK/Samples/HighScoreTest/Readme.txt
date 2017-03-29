/*
	File:		Readme.txt	

	Description:	HighScoreTest Readme	

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

This example is intended to demonstrate how to correctly use the high score
API.  You can use it to validate that your application is correctly using
the high score API.

From this example you can register and unregister with the high score manager,
add new scores, and view the currently recorded scores.


Using HighScoreTest:

Reg. - 		Calls TwHighScoreRegister with all the values in the form.  (Easy 
		to confuse this with "Get" below)
Unreg. - 	Calls TwHighScoreUnregister with the creatorID and 
		scoreType.  Note that this does not clear any fields in the form
		so you can tap "Reg." again right away.  Tapping "Unreg." 
		effectively clears all score data.
Get - 		Loads high score data for the specified creatorID and
		scoreType.
Details - 	Shows details for the current creatorID and scoreType
Score - 	Generates a new score for the current creatorID and scoreType.  
		The new score is a random number based on the current min and 
		max scores, biased to give a good chance at a new top score.


Build Instructions:

The HighScoreTest code is compiled using Metrowerks Codewarrior v9.3.