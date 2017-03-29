/* Metrowerks Standard Library
 * Copyright © 1995-2003 Metrowerks Corporation.  All rights reserved.
 *
 * $Date: 2003/08/11 21:34:17 $
 * $Revision: 1.44.2.6 $
 */

#ifndef _MSL_C_VERSION_H
#define _MSL_C_VERSION_H

/*
 * The __MSL__ identifier is a hex value tracking a more or less
 * decimal identity - that is, for builds 10 - 16, we will use a
 * decimal appearing number.
 *
 * The __MSL__ identifier is broken up into three parts:  the major
 * Pro version number, a zero (for backwards compatibility with older
 * version of the __MSL__ identifier), and the minor Pro version number.  
 *
 * The major Pro version number takes the first five positions, the
 * zero is in the sixth position, and the minor version number is in
 * the final two positions; therefore: 0x000008001 means the major Pro
 * release name is Pro 8, and the minor version is 1.
 *
 * The identifier is monotonically increasing for each build.
 */

#define __MSL__ 0x00009000


#endif /* _MSL_C_VERSION_H */

/* Change record:
 * JWW 010912 Created new file for tracking the MSL version number
 */