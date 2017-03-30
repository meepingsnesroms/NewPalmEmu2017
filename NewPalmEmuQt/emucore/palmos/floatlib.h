#ifndef FLOATLIB
#define FLOATLIB

/************************************************************
 * New Floating point manager selectors
 *************************************************************/

// The order of these #defines *MUST* match the
// corresponding table in NewFloatDispatch.c
#define sysFloatBase10Info			0
#define sysFloatFToA				1
#define sysFloatAToF				2
#define sysFloatCorrectedAdd		3
#define sysFloatCorrectedSub		4
#define sysFloatVersion				5

// used by NewFloatDispatch.c
#define flpMaxFloatSelector		sysFloatVersion


// The order of these #defines *MUST* match the
// corresponding table in NewFloatDispatch.c
#define sysFloatEm_fp_round			0
#define sysFloatEm_fp_get_fpscr		1
#define sysFloatEm_fp_set_fpscr		2

#define sysFloatEm_f_utof			3
#define sysFloatEm_f_itof			4
#define sysFloatEm_f_ulltof			5
#define sysFloatEm_f_lltof			6

#define sysFloatEm_d_utod			7
#define sysFloatEm_d_itod			8
#define sysFloatEm_d_ulltod			9
#define sysFloatEm_d_lltod			10

#define sysFloatEm_f_ftod			11
#define sysFloatEm_d_dtof			12
#define sysFloatEm_f_ftoq			13
#define sysFloatEm_f_qtof			14
#define sysFloatEm_d_dtoq			15
#define sysFloatEm_d_qtod			16

#define sysFloatEm_f_ftou			17
#define sysFloatEm_f_ftoi			18
#define sysFloatEm_f_ftoull			19
#define sysFloatEm_f_ftoll			20

#define sysFloatEm_d_dtou			21
#define sysFloatEm_d_dtoi			22
#define sysFloatEm_d_dtoull			23
#define sysFloatEm_d_dtoll			24

#define sysFloatEm_f_cmp			25
#define sysFloatEm_f_cmpe			26
#define sysFloatEm_f_feq			27
#define sysFloatEm_f_fne			28
#define sysFloatEm_f_flt			29
#define sysFloatEm_f_fle			30
#define sysFloatEm_f_fgt			31
#define sysFloatEm_f_fge			32
#define sysFloatEm_f_fun			33
#define sysFloatEm_f_for			34

#define sysFloatEm_d_cmp			35
#define sysFloatEm_d_cmpe			36
#define sysFloatEm_d_feq			37
#define sysFloatEm_d_fne			38
#define sysFloatEm_d_flt			39
#define sysFloatEm_d_fle			40
#define sysFloatEm_d_fgt			41
#define sysFloatEm_d_fge			42
#define sysFloatEm_d_fun			43
#define sysFloatEm_d_for			44

#define sysFloatEm_f_neg			45
#define sysFloatEm_f_add			46
#define sysFloatEm_f_mul			47
#define sysFloatEm_f_sub			48
#define sysFloatEm_f_div			49

#define sysFloatEm_d_neg			50
#define sysFloatEm_d_add			51
#define sysFloatEm_d_mul			52
#define sysFloatEm_d_sub			53
#define sysFloatEm_d_div			54



/************************************************************************
 * New Floating point manager constants
 ***********************************************************************/

#define flpVersion		0x02008000	// first version of NewFloatMgr (PalmOS 2.0)

/*
 * These constants are passed to and received from the _fp_round routine.
 */

#define flpToNearest	0
#define flpTowardZero	1
#define flpUpward		3
#define flpDownward		2
#define flpModeMask		0x00000030
#define flpModeShift	4

/*
 * These masks define the fpscr bits supported by the sfpe (software floating point emulator).
 * These constants are used with the _fp_get_fpscr and _fp_set_fpscr routines.
 */

#define flpInvalid		0x00008000
#define flpOverflow		0x00004000
#define flpUnderflow	0x00002000
#define flpDivByZero	0x00001000
#define flpInexact		0x00000800

/*
 * These constants are returned by _d_cmp, _d_cmpe, _f_cmp, and _f_cmpe:
 */

#define flpEqual		0
#define flpLess			1
#define flpGreater		2
#define flpUnordered	3


void flpdispatch();//Lib trap
void flpemdispatch();//FPU emu trap

#endif // FLOATLIB

