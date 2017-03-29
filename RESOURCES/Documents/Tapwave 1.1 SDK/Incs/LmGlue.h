/******************************************************************************
 *
 * Copyright (c) 2000-2002 PalmSource, Inc. All rights reserved.
 *
 * File: LmGlue.h
 *
 * Release: Palm OS 5 SDK (68K) R2.
 *
 * Description:
 *		Public header providing access to Locale Manager routines (independent of
 *		Palm OS version).
 *
 *****************************************************************************/

#ifndef	__LMGLUE_H__
#define	__LMGLUE_H__

#include <LocaleMgr.h>

/***********************************************************************
 * Locale Manager glue routines
 **********************************************************************/

#ifdef __cplusplus
	extern "C" {
#endif

/* Return the number of known locales (maximum locale index + 1).
*/
UInt16
LmGlueGetNumLocales(void);

/* Convert <iLocale> to <oLocaleIndex> by locating it within the set of known
locales.
*/
Err
LmGlueLocaleToIndex(	const
							LmLocaleType*	iLocale,
							UInt16*			oLocaleIndex);

/* Return in <oValue> the setting identified by <iChoice> which is appropriate for
the locale identified by <iLocaleIndex>.  Return lmErrSettingDataOverflow if the
data for <iChoice> occupies more than <iValueSize> bytes.  Display a non-fatal
error if <iValueSize> is larger than the data for a fixed-size setting.
*/
Err
LmGlueGetLocaleSetting(	UInt16			iLocaleIndex,
							LmLocaleSettingChoice iChoice,
							void*				oValue,
							UInt16			iValueSize);

#ifdef __cplusplus
	}
#endif

#endif
