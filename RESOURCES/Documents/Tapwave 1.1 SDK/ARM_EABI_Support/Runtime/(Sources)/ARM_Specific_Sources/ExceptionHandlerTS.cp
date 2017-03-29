/* Metrowerks ARM Runtime Support Library 
 * Copyright � 1995-2003 Metrowerks Corporation. All rights reserved. 
 * 
 * $Date: 2003/04/03 00:43:58 $ 
 * $Revision: 1.4 $ 
 */ 

/*
 *	ExceptionHandlerTS.cp	-	Target-specific C++ Exception Handler support
 *
 *	THEORY OF OPERATION
 *
 *	Here we define all functions which implement the target-specific aspects of
 *	the standard C++ Exception Handler.
 *
 *	See UnwindInfo.h for precise details on the stack frame format.
 *
 */

#include "NMWException.h"
#include "ExceptionHandler.h"
#include "UnwindInfo.h"

 
/*	
 *	__PopStackFrame(context, info)
 *
 *	Restore any registers saved in the current frame, as indicated by the
 *	UnwindInfo stored in 'info->exception_record', and pop the frame.
 *
 *	We don't actually modify the runtime stack; we simply restore the values of
 *	all registers saved in the current function to their value in the function's
 *	caller, IN THE LOCAL COPY OF THE REGISTER VALUES STORED IN 'context'. When we
 *	finally transfer control to a catch-block, we'll copy these values into the
 *	actual machine registers.
 *
 *	We return the return address in the caller--the place where the function whose
 *	frame we are popping would have returned to--so that the caller can use it to
 *	find the corresponding exception table.
 *
 *	We cannot correctly set 'context->FP' to the new frame's frame pointer because
 *	we don't yet have the exception table, which tells us whether the frame used
 *	a separate frame pointer or whether 'context->FP' == 'context->SP'.
 *
 */

char *__PopStackFrame(ThrowContext *context, ExceptionInfo *info)
{
	unsigned long frame_size, flushback_area_size, *GPRs;
	int i;
	
		/*	get the size of the frame	*/

	frame_size = context->target.frame_size;
	flushback_area_size = context->target.has_flushback ? 16 : 0;
	
		/*	restore the saved nonvolatile GPRs and get the new return address	*/
	
	GPRs = (unsigned long *) (context->FP + frame_size - flushback_area_size);
	for (i = 15; i >= 0; i--) {
		if (context->target.saved_GPRs & (1 << i))
			context->target.GPR[i] = *--GPRs;
	}
		
		/*	remove the frame from the stack	*/
	
	context->SP = context->FP + frame_size;
		
		/*	return the new return address	*/
	
	return((char *) context->target.GPR[14]);
}


/*
 *	__SetupFrameInfo(context, info)
 *
 *	Decode the UnwindInfo pointed at by 'info->exception_record'. Using this
 *	and the information contained in 'context', setup any information needed to
 *	address local variables in the current frame. This information is only used
 *	by __LocalVariable() defined below.
 *
 *	Typically this involves setting 'context->FP' to 'context->SP' for functions
 *	which do not have a separate frame pointer, or to whichever general-purpose
 *	register is used as a frame pointer for functions which do require a separate
 *	frame pointer.
 *
 *	On most RISC machines, locals can be addressed via SP unless the function
 *	calls alloca() or contains a catch-block or exception-specification, in which
 *	case a separate frame pointer is used because SP may float while the function
 *	is executing.
 *
 *	It is convenient to retain the decoded UnwindInfo in the target-specific portion
 *	of the ThrowContext so it can be reused by __PopStackFrame() and other routines.
 *
 */

extern void __SetupFrameInfo(ThrowContext *context, ExceptionInfo *info)
{
	char *p = info->exception_record;
	char flags = *p++;

		/*	decode the UnwindInfo for the current function	*/
	
	context->target.has_frame_ptr = flags & UNWIND_FRAME_IS_DYNAMIC;
	context->target.has_flushback = flags & UNWIND_FRAME_HAS_FLUSHBACK;
	context->target.is_Thumb = flags & UNWIND_FRAME_IS_THUMB;

	context->target.saved_GPRs  = ((unsigned char) *p++) << 4; /*r4-r11*/
	context->target.saved_GPRs |= (1 << 14); /*LR*/

	p = __DecodeUnsignedNumber(p, &context->target.frame_size);

	if (flags & UNWIND_FRAME_IS_DYNAMIC)
		p = __DecodeUnsignedNumber(p, &context->target.argument_size);
	
		/*	setup the frame pointer for addressing locals in the current function	*/
	
	if (flags & UNWIND_FRAME_IS_DYNAMIC) {
		if (flags & UNWIND_FRAME_IS_THUMB)
			context->FP = (char *) context->target.GPR[7];	//	r7  (v4) is used as the frame pointer
		else /* frame is ARM */
			context->FP = (char *) context->target.GPR[11];	//	r11 (v8) is used as the frame pointer
	}
	else
		context->FP = context->SP;							//	r13 (SP) is used as the frame pointer
}


/*
 *	__FindExceptionTable(info, retaddr)
 *
 *	Find the Exception Table Index that (possibly) contains 'retaddr'.
 *	The start and end of the index are stored in 'info->exception_table_start'
 *	and 'info->exception_table_end'.
 *
 *	If there is any target-specific ExceptionInfo it must be initialized here
 *	as well, e.g. base address of code/data sections.
 *
 *	For most targets there is only one exception table, usually accessed via
 *	globals generated by the linker, e.g. __exception_table_start__ and
 *	__exception_table_end__, so we just fill in those addresses and return TRUE.
 *
 *	If the target supports multiple fragments or overlays or for some other reason
 *	has more than one exception table index for a single program, we can use
 *	'retaddr' to find the appropriate index. If 'retaddr' doesn't correspond to
 *	any known exception table index then we must return FALSE.
 *
 *	Note that at this point 'retaddr' is an absolute return address, since we
 *	don't know until this routine finishes what it may be relative to.
 *
 */

int __FindExceptionTable(ExceptionInfo *info, char *retaddr)
{
	extern __declspec(exceptlist) ExceptionTableIndex __exception_table_start__[];
	extern __declspec(exceptlist) ExceptionTableIndex __exception_table_end__[];
	
	info->exception_table_start = __exception_table_start__;
	info->exception_table_end = __exception_table_end__;
	
	return(1);
}


/*
 *	__SkipUnwindInfo(exceptionrecord)
 *
 *	Given a pointer to an Exception Record, skip past the target-specific UnwindInfo
 *	to point at the Range Table. If the UnwindInfo is fixed-length we can implement
 *	this as a simple macro or inline function, but most targets will have variable-length
 *	UnwindInfo.
 *
 */

char *__SkipUnwindInfo(char *p)
{
	char flags = *p++;	/*	flag byte	*/;
	unsigned long dummy;
	
	p += 1;										/*	skip saved regs v1-v8	*/
	p = __DecodeUnsignedNumber(p, &dummy);		/*	skip frame size	*/
	if (flags & UNWIND_FRAME_IS_DYNAMIC)
		p = __DecodeUnsignedNumber(p, &dummy);	/*	skip argument size	*/

	return(p);
}


/*
 *	__TransferControl(info, context, address)
 *
 *	Transfer control back to the program at 'address'. This will always be either
 *	a catch-block or a call to __unexpected() supporting an exception specification.
 *
 *	'address' is of the same form as returned by __AdjustReturnAddress(), i.e.
 *	it is absolute if the exception table index contains absolute addresses, and
 *	relative if it contains relative addresses.
 *
 *	Using the information stored in the ThrowContext we restore all registers, and
 *	restore the stack pointer to its value in the function which called __throw()
 *	(discarding the exception-handling frames but leaving the thrower's frame intact)
 *
 *	Then we fixup the stack frame as needed (e.g. filling in any back-links, guaranteeing
 *	enough space for outgoing arguments, etc) and jump to the target address.
 *
 */

asm void __TransferControl(register ThrowContext *context, register ExceptionInfo *info, register char *address)
{
#ifndef __thumb // ARM version

		//	restore the nonvolatile GPRs of the catcher
		ldr		v1,[context,#ThrowContext.target.GPR+16]	//	GPR[4]
		ldr		v2,[context,#ThrowContext.target.GPR+20]	//	GPR[5]
		ldr		v3,[context,#ThrowContext.target.GPR+24]	//	GPR[6]
		ldr		v4,[context,#ThrowContext.target.GPR+28]	//	GPR[7]
		ldr		v5,[context,#ThrowContext.target.GPR+32]	//	GPR[8]
		ldr		v6,[context,#ThrowContext.target.GPR+36]	//	GPR[9]
		ldr		v7,[context,#ThrowContext.target.GPR+40]	//	GPR[10]
		ldr		v8,[context,#ThrowContext.target.GPR+44]	//	GPR[11]

		//	restore SP to stack top at throw: discards exception-handling frames
		//	but not exception temporaries!
		ldr		sp,[context,#ThrowContext.target.throwSP]
		
		//	add enough space to the frame to accomodate any outgoing arguments
		//	used by the catcher; this is needed because the thrower may not
		//	have as large an argument area as the catcher, and we don't want the
		//	catcher to overwrite locals in the thrower (i.e. the exception object
		//	being thrown) if it makes any calls from the catch-block.
		ldr		ip,[context,#ThrowContext.target.argument_size]
		sub		sp,sp,ip

		//	transfer control to the catch-block
		mov		pc,address

#else // Thumb version

		//	restore the nonvolatile GPRs of the catcher
		ldr		v1,[context,#ThrowContext.target.GPR+16]	//	GPR[4]
		ldr		v2,[context,#ThrowContext.target.GPR+20]	//	GPR[5]
		ldr		v3,[context,#ThrowContext.target.GPR+24]	//	GPR[6]
		ldr		v4,[context,#ThrowContext.target.GPR+28]	//	GPR[7]
		ldr		a4,[context,#ThrowContext.target.GPR+32]	//	GPR[8]
		mov		v5,a4
		ldr		a4,[context,#ThrowContext.target.GPR+36]	//	GPR[9]
		mov		v6,a4
		ldr		a4,[context,#ThrowContext.target.GPR+40]	//	GPR[10]
		mov		v7,a4
		ldr		a4,[context,#ThrowContext.target.GPR+44]	//	GPR[11]
		mov		v8,a4

		//	restore SP to stack top at throw: discards exception-handling frames
		//	but not exception temporaries!
		ldr		a4,[context,#ThrowContext.target.throwSP]
		mov		sp,a4
		
		//	add enough space to the frame to accomodate any outgoing arguments
		//	used by the catcher; this is needed because the thrower may not
		//	have as large an argument area as the catcher, and we don't want the
		//	catcher to overwrite locals in the thrower (i.e. the exception object
		//	being thrown) if it makes any calls from the catch-block.
		ldr		a4,[context,#ThrowContext.target.argument_size]
		neg		a4,a4
		add		sp,a4

		//	transfer control to the catch-block
		mov		pc,address

#endif
}


/*
 *	__throw(throwtype, location, dtor)
 *
 *	Throw an exception object at 'location' of type 'throwtype'. After catch-handling
 *	is complete, the object will be destroyed by calling destructor 'dtor'.
 *
 *	We capture the necessary target-independent (e.g. stack pointer in the thrower,
 *	return address into the thrower) and target-specific (e.g. the values of nonvolatile
 *	registers from the thrower) context information, and remember the throw-type,
 *	exception-object and its destructor, and then jump to the target-independent
 *	throw handler.
 *
 */
 
asm void __throw(register char *throwtype, register void *location, register void *dtor)
{
#ifndef __thumb // ARM version

		//	capture the stack pointer of the thrower, which we will
		//	need when we transfer control back to the catcher
		mov		ip,sp

		//	allocate space for a local ThrowContext
		sub		sp,sp,#sizeof(ThrowContext)

		//	capture the nonvolatile GPRs of the thrower
		str		v1,[sp,#ThrowContext.target.GPR+16]	//	GPR[4]
		str		v2,[sp,#ThrowContext.target.GPR+20]	//	GPR[5]
		str		v3,[sp,#ThrowContext.target.GPR+24]	//	GPR[6]
		str		v4,[sp,#ThrowContext.target.GPR+28]	//	GPR[7]
		str		v5,[sp,#ThrowContext.target.GPR+32]	//	GPR[8]
		str		v6,[sp,#ThrowContext.target.GPR+36]	//	GPR[9]
		str		v7,[sp,#ThrowContext.target.GPR+40]	//	GPR[10]
		str		v8,[sp,#ThrowContext.target.GPR+44]	//	GPR[11]

		//	throwcontext.SP = throwcontext.throwSP = <stack pointer of caller>;
		str		ip,[sp,#ThrowContext.SP]
		str		ip,[sp,#ThrowContext.target.throwSP]

		//	throwcontext.returnaddr = <return address into caller>;
		str		lr,[sp,#ThrowContext.returnaddr]

		//	remember the throw-type, location, and dtor
		str		throwtype,[sp,#ThrowContext.throwtype]
		str		location,[sp,#ThrowContext.location]
		str		dtor,[sp,#ThrowContext.dtor]

		//	call __ThrowHandler(&throwcontext)
		mov		a1,sp
		b		__ThrowHandler
		//	we will never return to here!

#else // Thumb version

		//	capture the stack pointer of the thrower, which we will
		//	need when we transfer control back to the catcher
		mov		ip,sp

		//	allocate space for a local ThrowContext
		mov		a4,#sizeof(ThrowContext)
		neg		a4,a4
		add		sp,a4

		//	capture the nonvolatile GPRs of the thrower
		str		v1,[sp,#ThrowContext.target.GPR+16]	//	GPR[4]
		str		v2,[sp,#ThrowContext.target.GPR+20]	//	GPR[5]
		str		v3,[sp,#ThrowContext.target.GPR+24]	//	GPR[6]
		str		v4,[sp,#ThrowContext.target.GPR+28]	//	GPR[7]
		mov		a4,v5
		str		a4,[sp,#ThrowContext.target.GPR+32]	//	GPR[8]
		mov		a4,v6
		str		a4,[sp,#ThrowContext.target.GPR+36]	//	GPR[9]
		mov		a4,v7
		str		a4,[sp,#ThrowContext.target.GPR+40]	//	GPR[10]
		mov		a4,v8
		str		a4,[sp,#ThrowContext.target.GPR+44]	//	GPR[11]

		//	throwcontext.SP = throwcontext.throwSP = <stack pointer of caller>;
		mov		a4,ip
		str		a4,[sp,#ThrowContext.SP]
		str		a4,[sp,#ThrowContext.target.throwSP]

		//	throwcontext.returnaddr = <return address into caller>;
		mov		a4,lr
		str		a4,[sp,#ThrowContext.returnaddr]

		//	remember the throw-type, location, and dtor
		str		throwtype,[sp,#ThrowContext.throwtype]
		str		location,[sp,#ThrowContext.location]
		str		dtor,[sp,#ThrowContext.dtor]

		//	call __ThrowHandler(&throwcontext)
		mov		a1,sp
		bl		__ThrowHandler
		//	we will never return to here!

#endif
}


/*
 *	__rethrow()
 *
 *	Rethrow the current exception. This is equivalent to __throw(0,0,0).
 *
 */
 
asm void __rethrow(void)
{
#ifndef __thumb // ARM version

		//	capture the stack pointer of the thrower, which we will
		//	need when we transfer control back to the catcher
		mov		ip,sp

		//	allocate space for a local ThrowContext
		sub		sp,sp,#sizeof(ThrowContext)

		//	capture the nonvolatile GPRs of the thrower
		str		v1,[sp,#ThrowContext.target.GPR+16]	//	GPR[4]
		str		v2,[sp,#ThrowContext.target.GPR+20]	//	GPR[5]
		str		v3,[sp,#ThrowContext.target.GPR+24]	//	GPR[6]
		str		v4,[sp,#ThrowContext.target.GPR+28]	//	GPR[7]
		str		v5,[sp,#ThrowContext.target.GPR+32]	//	GPR[8]
		str		v6,[sp,#ThrowContext.target.GPR+36]	//	GPR[9]
		str		v7,[sp,#ThrowContext.target.GPR+40]	//	GPR[10]
		str		v8,[sp,#ThrowContext.target.GPR+44]	//	GPR[11]

		//	throwcontext.SP = throwcontext.throwSP = <stack pointer of caller>;
		str		ip,[sp,#ThrowContext.SP]
		str		ip,[sp,#ThrowContext.target.throwSP]

		//	throwcontext.returnaddr = <return address into caller>;
		str		lr,[sp,#ThrowContext.returnaddr]

		//	clear the throw-type, location, and dtor
		mov		ip,#0
		str		ip,[sp,#ThrowContext.throwtype]
		str		ip,[sp,#ThrowContext.location]
		str		ip,[sp,#ThrowContext.dtor]

		//	call __ThrowHandler(&throwcontext)
		mov		a1,sp
		b		__ThrowHandler
		//	we will never return to here!

#else // Thumb version

		//	capture the stack pointer of the thrower, which we will
		//	need when we transfer control back to the catcher
		mov		a1,sp

		//	allocate space for a local ThrowContext
		mov		a2,#sizeof(ThrowContext)
		neg		a2,a2
		add		sp,a2

		//	capture the nonvolatile GPRs of the thrower
		str		v1,[sp,#ThrowContext.target.GPR+16]	//	GPR[4]
		str		v2,[sp,#ThrowContext.target.GPR+20]	//	GPR[5]
		str		v3,[sp,#ThrowContext.target.GPR+24]	//	GPR[6]
		str		v4,[sp,#ThrowContext.target.GPR+28]	//	GPR[7]
		mov		a2,v5
		str		a2,[sp,#ThrowContext.target.GPR+32]	//	GPR[8]
		mov		a2,v6
		str		a2,[sp,#ThrowContext.target.GPR+36]	//	GPR[9]
		mov		a2,v7
		str		a2,[sp,#ThrowContext.target.GPR+40]	//	GPR[10]
		mov		a2,v8
		str		a2,[sp,#ThrowContext.target.GPR+44]	//	GPR[11]

		//	throwcontext.SP = throwcontext.throwSP = <stack pointer of caller>;
		str		a1,[sp,#ThrowContext.SP]
		str		a1,[sp,#ThrowContext.target.throwSP]

		//	throwcontext.returnaddr = <return address into caller>;
		mov		a1,lr
		str		a1,[sp,#ThrowContext.returnaddr]

		//	clear the throw-type, location, and dtor
		mov		a1,#0
		str		a1,[sp,#ThrowContext.throwtype]
		str		a1,[sp,#ThrowContext.location]
		str		a1,[sp,#ThrowContext.dtor]

		//	call __ThrowHandler(&throwcontext)
		mov		a1,sp
		bl		__ThrowHandler
		//	we will never return to here!

#endif
}
