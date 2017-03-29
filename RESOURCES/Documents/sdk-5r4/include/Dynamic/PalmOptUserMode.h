/******************************************************************************
 *
 * Copyright (c) 1999-2004 PalmSource, Inc. All rights reserved.
 *
 * File: PalmOptUserMode.h
 *
 * Release: Palm OS Developer Suite 5 SDK (68K) 4.0
 *
 *****************************************************************************/

#include <BuildDefines.h>
#ifdef USER_MODE
#undef USER_MODE
#endif
#define USER_MODE USER_MODE_NORMAL
