/*! file			gauge.c

	Description:	Display data on the screen in a bar graph presentation.

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

#include <TapWave.h>
#include "gauge.h"
#include "utils.h"

/*! \brief Open a gauge for data adding and drawing.

\see GaugeAdd
\see GaugeDraw
\see GaugeClose
*/
// There is info we could add, like max data value, max height, tick count
GaugeFIFOType * 
GaugeOpen(int screen_width)
{
	GaugeFIFOType * info;
	
	info = (GaugeFIFOType *) MemPtrNew(sizeof(*info));
	info->start = 0;
	info->end = 0;
	info->used = false;
	info->screen_width = screen_width;

    return info;
}


/*! \brief Add data to a gauge.

The oldest data is discarded if the gauge is full.

\see GaugeOpen
\see GaugeDraw
\see GaugeClose
*/
void
GaugeAdd(GaugeFIFOType * info, int value)
{
	info->data[info->end] = value;
	info->used = true;
	
	info->end++;
	if (info->end >= GAUGE_DATA_MAX)
		info->end = 0;
	
	if (info->start == info->end)
	{
		info->start++;
		if (info->start >= GAUGE_DATA_MAX)
			info->start = 0;
	}
}


/*! \brief Draw data added to a gauge.

The data is drawn as a horizontal bar graph rising vertically.

\see GaugeOpen
\see GaugeAdd
\see GaugeClose
*/
void
GaugeDraw(GaugeFIFOType * info, TwGfxSurfaceType* aDestSurface, 
	TwGfxPackedRGBType aColor,
	int left, int top)
{
	static TwGfxPointType points[GAUGE_DATA_MAX * 2];
	int count;
	int end_point;
	int i;
	int x;
	char text[16];
	Err err;


	if (info->used)
	{
		if (info->start < info->end)
		{
			count = info->end - info->start;
			
			// Centering is cool, but I think it's hard
			// to read.
			x = info->screen_width - (info->screen_width - GAUGE_DATA_MAX) / 2 - count + left;
			
			end_point = 0;
			for (i = info->start; i < info->end; i++)
			{
				points[end_point].x = x;
				points[end_point].y = top;
				end_point++;
				points[end_point].x = x;
				points[end_point].y = top - info->data[i];
				end_point++;

                x++;
			}
		}
		else
		{
			count = (GAUGE_DATA_MAX - info->start) + (info->end - 0);
			x = info->screen_width - (info->screen_width - GAUGE_DATA_MAX) / 2 - count + left;
			
			end_point = 0;
			for (i = info->start; i < GAUGE_DATA_MAX; i++)
			{
				points[end_point].x = x;
				points[end_point].y = top;
				end_point++;
				points[end_point].x = x;
				points[end_point].y = top - info->data[i];
				end_point++;

                x++;
			}
			
			for (i = 0; i < info->end; i++)
			{
				points[end_point].x = x;
				points[end_point].y = top;
				end_point++;
				points[end_point].x = x;
				points[end_point].y = top - info->data[i];
				end_point++;

                x++;
			}
		}
		
		err = TwGfxDrawLineSegments(aDestSurface, points,
			end_point, aColor);
		
		// Draw the last number too.
		if (info->end > 0)
			StrIToA(text, info->data[info->end - 1]);
		else
			StrIToA(text, info->data[GAUGE_DATA_MAX - 1]);
		if (err != errNone)
		{
			StrIToA(text, end_point);
			StrCat(text, "err");
		}
		FontDrawChars(text, StrLen(text), 
            aDestSurface, left + info->screen_width - 40, top - FontGetLineHeight());
	}
}


void
GaugeClose(GaugeFIFOType * info)
{
	MemPtrFree(info);
}


