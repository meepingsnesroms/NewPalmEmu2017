/******************************************************************************
 *
 * Copyright (c) 1995-2002 PalmSource, Inc. All rights reserved.
 *
 * File: HardBallLevels.h
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 * Description:
 *	  These are the commonly modified game parameters. 
 *
 *****************************************************************************/

static Int16 BrickScores[brickTypeCount] = {0, 5, 10, 20, 0, 0, 0};


#define levelCount		15
#define BE	empty
#define B1	brick1
#define B2	brick2
#define B3	brick3
#define BU	unbreakable
#define BB	ballBrick
#define BS	sidePaddleBrick



static LevelType levelInfo[levelCount] = 
	{
		// Level 0
		{
			"Portcullis",
			{BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 B2, BE, BE, B2, BE, BE, B2, BE, BE,
			 B2, B2, BE, B2, B2, BE, B2, B2, BE,
			 B1, B2, B2, B1, B2, B2, B1, B2, B2,
			 B1, B1, B2, B1, B1, B2, B1, B1, B2,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 BE, B1, B1, BE, B1, B1, BE, B1, B1,
			 BE, BE, B1, BE, BE, B1, BE, BE, B1,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE}
		},
		// Diamonds - Level 1
		{
			"Diamonds",
			{B3, B3, BE, BE, B1, BE, BE, B3, B3,
			 B3, BE, BE, B1, B1, B1, BE, BE, B3,
			 BE, BE, B1, B1, B1, B1, B1, BE, BE,
			 BE, BE, B2, B1, B1, B1, B2, BE, BE,
			 BE, B2, B2, B2, B1, B2, B2, B2, BE,
			 B2, B2, B2, B2, B2, B2, B2, B2, B2,
			 B1, B2, B2, B2, B1, B2, B2, B2, B1,
			 B1, B1, B2, B1, B1, B1, B2, B1, B1,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 B1, B1, BE, B1, B1, B1, BE, B1, B1,
			 B1, BE, BE, BE, B1, BE, BE, BE, B1}
		},
		// Metro - Level 2
		{
			"Metro",
			{BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, B2, B2, B2, BE, BE, BE,
			 BE, BE, B3, B3, B2, B2, BE, BE, BE,
			 BE, BE, B3, B3, B2, B2, BE, BE, BE,
			 BE, B1, B3, BU, B2, B2, B1, B1, BE,
			 BE, B1, B3, BU, B2, B2, B1, B1, BE,
			 BE, B1, B3, BU, B2, B2, B1, B1, BE,
			 BE, B1, B1, B2, B2, B2, B1, B1, BE,
			 BE, B1, B1, B2, B2, B2, B1, B1, BE,
			 BE, B1, B1, B1, B1, B1, B1, B1, BE,
			 BE, B1, B1, B1, B1, B1, B1, B1, BE}
		},
		// Trouble Slide - Level 3
		{
			"Trouble",
			{BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 B2, B2, B2, B2, B2, B2, B1, B1, B1,
			 B3, B2, B2, B2, B2, B1, B1, B1, B1,
			 B3, B3, B2, B2, BU, B1, B1, B1, B1,
			 B3, B3, B3, BU, B1, B1, B1, B1, B1,
			 B3, B3, BU, B1, B1, B1, B1, B1, B1,
			 B3, BU, B1, B1, B1, B1, B1, B1, B1,
			 BU, B1, B1, B1, B1, B1, B1, B1, B1,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE}
		},
		// Egyptian - Level 4
		{
			"Desert Visions",
			{BE, BE, B3, BE, BE, BE, BE, B1, BE,
			 BE, BE, B3, BE, BE, BE, BE, B1, B1,
			 BE, B3, B3, B3, BE, B2, BE, B1, B1,
			 BE, B3, B3, B3, BE, B2, BE, BE, B1,
			 B3, B3, B3, B3, B2, B2, B2, BE, BE,
			 B3, B3, B3, B3, B2, B2, B2, B1, BE,
			 B3, B3, B3, B2, B2, B2, B2, B1, BE,
			 B3, B3, B3, B2, B2, B2, B1, B1, B1,
			 B2, B2, B2, B2, B2, B2, B1, B1, B1,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE}
		},
		// Double Trouble - Level 5
		{
			"Double Trouble",
			{BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 B2, B2, B2, B2, BU, BB, B3, B3, B3,
			 B2, B2, B2, B2, B2, BU, B3, B3, B3,
			 B2, B2, B2, B2, BB, B2, BU, B3, B3,
			 B2, B2, B2, B2, BU, B1, B1, BU, B3,
			 B2, B2, B2, BU, B1, B1, B1, B1, B3,
			 B2, B2, BU, B1, B1, B1, B1, B1, B1,
			 B2, BU, B1, B1, B1, B1, B1, B1, B1,
			 B2, B1, B1, B1, B1, B1, B1, B1, B1,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE}
		},
		// High V - Level 6
		{
			"High V",
			{BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, B2, B2, B2, BE, B2, B2, B2, BE,
			 B2, B2, BU, B3, B3, B3, BU, B2, B2,
			 B2, B1, B1, BU, B3, BU, B1, B1, B2,
			 B1, B1, B1, B1, BU, B1, B1, B1, B1,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 B1, B1, B1, B1, BB, B1, B1, B1, B1,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE}
		},
		// Mayan - Level 7
		{
			"Mayan",
			{BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 B2, B2, B2, BU, BB, BU, B2, B2, B2,
			 B2, B2, B2, B1, B1, B1, B2, B2, B2,
			 B2, B2, B1, B1, B1, B1, B1, B2, B2,
			 B2, B1, B1, B1, B1, B1, B1, B1, B2,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 B1, B1, B1, B1, BB, B1, B1, B1, B1,
			 B1, B1, B1, BE, BE, BE, B1, B1, B1,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE}
		},
		// Face It - Level 8
		{
			"Face It",
			{BE, BE, B3, B3, B3, B3, B3, BE, BE,
			 BE, B2, B3, B3, B3, B3, B3, B2, BE,
			 B2, B2, B1, B3, B3, B3, B1, B2, B2,
			 B2, B1, BB, B1, B3, B1, BB, B1, B2,
			 B2, B1, BU, B1, B2, B1, BU, B1, B2,
			 B2, B2, B1, B2, B2, B2, B1, B2, B2,
			 B2, B2, B2, B2, B2, B2, B2, B2, B2,
			 BE, B2, B2, B2, B2, B2, B2, B2, BE,
			 BE, B2, B2, B2, BS, B2, B2, B2, BE,
			 BE, BE, B1, B2, B2, B2, B1, BE, BE,
			 BE, BE, BE, B1, B1, B1, BE, BE, BE}
		},
		// Grand X - Level 9
		{
			"Grand X",
			{BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BE, BS, BE, BE, BE, BE,
			 B1, BB, BE, B2, B2, B2, BE, BB, B1,
			 B1, BE, BU, B3, B3, B3, BU, BE, B1,
			 BE, B2, B3, BU, B3, BU, B3, B2, BE,
			 B2, B2, B3, B3, BU, B3, B3, B2, B2,
			 BE, B2, B3, BU, B3, BU, B3, B2, BE,
			 B1, BE, BU, B3, B3, B3, BU, BE, B1,
			 B1, B1, BE, B2, B2, B2, BE, B1, B1,
			 B1, B1, B1, BE, B2, BE, B1, B1, B1,
			 B1, B1, B1, B1, BE, B1, B1, B1, B1}
		},
		// Shockwave - Level 10
		{
			"Shockwave",
			{BE, BE, B3, B3, B3, B3, B3, BE, BE,
			 BE, B3, B3, B3, B3, B3, B3, B3, BE,
			 B3, B3, B1, B1, BU, B1, B1, B3, B3,
			 B3, B1, BU, B1, BS, B1, BU, B1, B3,
			 B1, B1, B1, B2, BB, B2, B1, B1, B1,
			 B1, B2, B2, B2, BB, B2, B2, B2, B1,
			 B2, B2, BB, B1, B1, B1, BB, B2, B2,
			 B2, B1, B1, B1, B1, B1, B1, B1, B2,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE}
		},
		// Alleyways - Level 11
		{
			"Alleyways",
			{BE, BE, B3, BE, B3, BE, B3, BE, BE,
			 B3, BE, B3, BE, B3, BE, B3, BE, B3,
			 B3, BE, B3, BE, BB, BE, B3, BE, B3,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 B2, BE, B2, BE, B2, BE, B2, BE, B2,
			 B2, BE, B2, BE, B2, BE, B2, BE, B2,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 B1, BE, B1, BE, BB, BE, B1, BE, B1,
			 B1, BE, B1, BE, B1, BE, B1, BE, B1,
			 B1, BE, BU, BE, BU, BE, BU, BE, B1,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE}
		},
		// Level 12
		{
			"Bo Bo Cha Cha",
			{BE, BE, B3, B3, BB, B3, B3, BE, BE,
			 BE, B3, B2, BE, BE, BE, B2, B3, BE,
			 B3, B2, B1, BE, BE, BE, B1, B2, B3,
			 B2, B1, B3, BE, BE, BE, B3, B1, B2,
			 B1, B3, B2, B3, BE, B3, B2, B3, B1,
			 B3, B2, B1, B2, BS, B2, B1, B2, B3,
			 B2, B1, B1, B1, BB, B1, B1, B1, B2,
			 B1, B1, B1, B1, BB, B1, B1, B1, B1,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 B1, B1, B1, B1, B1, B1, B1, B1, B1,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE}
		},
		// HardBall - Level 13
		{
			"HardBall",
			{BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BE, BE, BE, BE, BE, BE,
			 BE, BE, BE, BB, B2, BB, BE, BE, BE,
			 BE, BE, BU, B2, B2, B2, BU, BE, BE,
			 BE, BU, B2, B2, B2, B2, B2, BU, BE,
			 BE, BU, B2, B2, B2, B2, B2, BU, BE,
			 BE, BU, B2, B2, B2, B2, B2, BU, BE,
			 BE, BE, BU, B2, B2, B2, BU, BE, BE,
			 BE, BE, BE, BU, BU, BU, BE, BE, BE,
			 B3, B3, B3, B3, B3, B3, B3, B3, B3,
			 B3, B3, B3, B3, B3, B3, B3, B3, B3}
		},
		// Rocket - Level 14
		{
			"Rocket",
			{BE, BB, BE, BE, BE, BE, BE, BE, BE,
			 BB, B2, BB, BE, BE, BE, B3, B3, B3,
			 B1, B2, B1, B2, B2, B2, B3, B1, B3,
			 B1, B1, B1, BE, BE, BE, B1, B3, B1,
			 B1, B1, B1, BE, BE, BE, B3, B1, B3,
			 B1, B1, B1, BE, BE, BE, B1, B3, B1,
			 B1, B1, B1, B2, B2, B2, B3, B1, B3,
			 B1, BB, B1, BE, BE, BE, B1, B3, B1,
			 B1, BB, B1, BE, BE, BE, B3, B1, B3,
			 B1, BB, B1, BE, BE, BE, B1, B3, B1,
			 B1, BS, B1, BE, BE, BE, B3, B3, B3}
		}
	};
