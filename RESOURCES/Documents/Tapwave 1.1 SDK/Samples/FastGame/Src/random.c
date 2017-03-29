/*
	File:			random.c

	Description:	Use our own random number generator for performance reasons.  It's statically linked so it is
					quickly accessed.  We pick a quick but useful enough method for number generation.  The method 
					produces the same string when given the same seed, which is important for repeatability for testing.

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


#include "host.h"
#include "random.h"



static uint32 RandomNumberSeed;


/***********************************************************************
 *
 * FUNCTION:     RandomNumberGetSeed
 *
 * DESCRIPTION:  Return the seed.
 *
 * PARAMETERS:   nothing
 *
 * RETURNED:     the seed
 *
 ***********************************************************************/

uint32
random_number_get_seed(void)
{
    return RandomNumberSeed;
}


/***********************************************************************
 *
 * FUNCTION:     RandomNumberSetSeed
 *
 * DESCRIPTION:  Set the seed.
 *
 * PARAMETERS:   number - number to use as the seed.
 *
 * RETURNED:     nothing
 *
 ***********************************************************************/

void
random_number_set_seed(uint32 number)
{
    RandomNumberSeed = number;
}


/***********************************************************************
 *
 * FUNCTION:     RandomNumber
 *
 * DESCRIPTION:  Return a number from 0 to range - 1.
 *
 * PARAMETERS:   range - range to pick a number from.
 *
 * RETURNED:     a number from 0 to range - 1
 *
 ***********************************************************************/
#define	randomMax		0xFFFF  // Max value returned

uint16
random_number(int16 range)
{
    uint32 result;

//   assert(range >= 0);

    // Generate the new seed
    RandomNumberSeed *= 2147001325;
    RandomNumberSeed += 715136305;

    // Return the random number
    result = RandomNumberSeed >> 16;

    // Make the result in proportion to the range requested.
    result = (result * range) / ((uint32) randomMax + 1);

    return (uint16) result;
}
