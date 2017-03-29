/******************************************************************************
 *
 * Copyright (c) 1999-2002 PalmSource, Inc. All rights reserved.
 *
 * File: PalmOptUserMode.h
 *
 * Release: Palm OS 5 SDK (68K) R2.
 *
 *****************************************************************************/

#include <BuildDefines.h>
#ifdef USER_MODE
#undef USER_MODE
#endif
#define USER_MODE USER_MODE_NORMAL
