/* Metrowerks ARM Runtime Support Library 
 * Copyright © 1995-2002 Metrowerks Corporation. All rights reserved. 
 * 
 * $Date: 2003/07/01 17:42:38 $ 
 * $Revision: 1.4 $ 
 */ 


/*
 *	startup.c	-	entry-point for ARM programs
 *
 */

#include <string.h>
#include <stdlib.h>

static char *argv[] = { 0 };
extern char __SP_INIT[];
extern void __call_static_initializers(void);
extern int main(int, char **);

extern void _fp_init(void);

static void zero_fill_bss(void)
{
	extern char __START_BSS[];
	extern char __END_BSS[];
	
	memset(__START_BSS, 0, (__END_BSS - __START_BSS));
}

#ifdef __thumb // Thumb version
static void thumb_startup(void);
asm void thumb_startup(void)
{
	
		//	setup the stack before we attempt anything else
		lda		r0,__SP_INIT
		mov		sp,r0
		sub		sp,#4
		mov		r0,#0
		mvn		r0,r0
		str		r0,[sp,#0]
		add		sp,#4
	
		//	zero-fill the .bss section
		bl		zero_fill_bss
		
		//	call C++ static initializers
		bl		__call_static_initializers
		
		//      initialize the floating-point library
		bl      _fp_init
	
		//	call main(argc, &argv)
		mov		a1,#0
		lda		a2,argv
		bl		main
		
		//	exit the program
		mov		a1,#0
		bl		exit
		
		//	should never get here
@1:		b		@1
}
#endif

#pragma thumb off
void __startup(void);
asm void __startup(void)
{
#ifndef __thumb // ARM version

		//	setup the stack before we attempt anything else
		lda		sp,__SP_INIT
		mvn		r0,#0
		str		r0,[sp,#-4]!
	
		//	zero-fill the .bss section
		bl		zero_fill_bss
		
		//	call C++ static initializers
		bl		__call_static_initializers
		
		//      initialize the floating-point library
		bl      _fp_init
	
		//	call main(argc, &argv)
		mov		a1,#0
		lda		a2,argv
		bl		main
		
		//	exit the program
		mov		a1,#0
		bl		exit
		
		//	should never get here
@1:		b		@1

#else // Thumb version

		//	we cannot start in Thumb mode, so call thumb_startup
		//	via interworking branch
		lda		r0,thumb_startup
		bx 		r0

#endif
}
#pragma thumb reset 

