/*
	File:			random.h	

	Description:	Random number generator header file.

	Author:		

	Copyright:		Copyright © 2003 by Tapwave, Inc.

	Disclaimer:		IMPORTANT:  This Tapwave software is provided by Tapwave, Inc. ("Tapwave").  Your 
					use is subject to and governed by terms and conditions of the Software Development 
					Kit Agreement ("SDK Agreement") between you and Tapwave.  If you have not entered 
					into Tapwave’s standard SDK Agreement with Tapwave, you have no right or license 
					to use, reproduce, modify, distribute or otherwise exploit this Tapwave software.  
					You may obtain a copy of Tapwave’s standard SDK Agreement by calling 650-960-1817
					or visiting Tapwave at http://www.tapwave.com/developers/. 

	Change History (most recent first):
				
*/

// The API to these functions is C based.
#ifdef __cplusplus
extern "C"
{
#endif

uint32
random_number_get_seed(void);
void
random_number_set_seed(uint32 number);
uint16
random_number(int16 range)
;


#ifdef __cplusplus
}
#endif
