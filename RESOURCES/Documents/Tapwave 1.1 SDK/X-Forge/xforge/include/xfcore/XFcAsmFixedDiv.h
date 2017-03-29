/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief ARM assembler fixed division functions.
 * 
 * $Id: XFcAsmFixedDiv.h,v 1.8 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.8 $
 */

#ifndef XFC_FIXEDDIV_H_INCLUDED
#define XFC_FIXEDDIV_H_INCLUDED

//! Divides fixed point value with a fixed point value.
extern "C" int xfcAsmFixedDiv(int a, int b);
//! Divides fixed point value with a fixed point value. This function will always be for 16.16 fixed point values.
extern "C" int xfcAsmFixedDiv16x16(int a, int b);
//! Divides fixed point value with a fixed point value. This function will always be for 11.21 fixed point values.
extern "C" int xfcAsmFixedDiv11x21(int a, int b);
//! Divides fixed point value with a fixed point value. This function will always be for 10.22 fixed point values.
extern "C" int xfcAsmFixedDiv10x22(int a, int b);

#endif // !XFC_FIXEDDIV_H_INCLUDED
