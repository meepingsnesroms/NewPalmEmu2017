/*! \file 
 * X-Forge Core <br>
 * Copyright 2000-2003 Fathammer Ltd
 * 
 * \brief ARM assembler fixed point multiplication functions.
 * 
 * $Id: XFcAsmFixedMul.h,v 1.7 2003/08/12 13:33:47 lars Exp $
 * $Date: 2003/08/12 13:33:47 $
 * $Revision: 1.7 $
 */
#ifndef XFC_FIXEDMUL_H_INCLUDED
#define XFC_FIXEDMUL_H_INCLUDED

//! Multiplies a fixed point value with a fixed point value.
extern "C" int xfcAsmFixedMul(int a, int b, int shift);
//! Multiplies a fixed point value with a fixed point value. This function will always be for 16.16 fixed point values.
extern "C" int xfcAsmFixedMul16x16(int a, int b);
//! Multiplies a fixed point value with a fixed point value. This function will always be for 10.22 fixed point values.
extern "C" int xfcAsmFixedMul10x22(int a, int b);

#endif // !XFC_FIXEDMUL_H_INCLUDED
