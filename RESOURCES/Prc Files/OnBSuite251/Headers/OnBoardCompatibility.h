/* 
* OnBoardCompatability.h
*
* To be included when backward compatability is needed 
* To be used together with "OnBoardHeaderV40.h.pdb" 
*
* Copyright (c) 1994-2000 Palm, Inc. or its subsidiaries.
* All rights reserved.
* 
*/


typedef unsigned char Byte; 
typedef int Word; 
typedef int SWord; 
typedef long SDWord; 
typedef long DWord; 
typedef short Short; 
typedef long Long; 
typedef char *CharPtr; 
typedef unsigned int UInt; 
typedef UInt *UIntPtr; 
typedef unsigned long ULong; 
typedef ULong *ULongPtr; 
typedef int Int; 
typedef Int *IntPtr; 
typedef Word *WordPtr; 
typedef DWord *DWordPtr; 
typedef MemPtr VoidPtr; 
typedef MemHandle VoidHand; 
typedef MemHandle Handle; 
typedef char *Ptr;


#define ScrDisplayMode WinScreenMode


/* Math Lib APIs
Only Uncomment if MathLib.h is not included.
Err MathLibOpen(UInt16 refnum, UInt16 version) SYS_TRAP(sysLibTrapOpen); 
Err MathLibClose(UInt16 refnum, UInt16 *usecountP) SYS_TRAP(sysLibTrapClose); 


Err MathLibPow(UInt16 refnum, double x, double y, double *result) SYS_TRAP(sysLibTrapCustom+24); 
Err MathLibSqrt(UInt16 refnum, double x, double *result) SYS_TRAP(sysLibTrapCustom+25); 
*/


