########################################################################
#
#	File:			HostControl.pm
#
#	Purpose:		Perl wrappers for Palm OS Emulator HostControl 
#					functions.
#
#	Description:	This file contains Perl equivalents of Palm OS
#					Emulator Host Control functions, like HostGetHostID,
#					HostGetHostVersion, HostProfileStart etc...
#
#					In general, functions follow the calling
#					conventions in the SDK headers.  However, there
#					are exceptions.  See the comments before each
#					subroutine for details.
#
########################################################################

package HostControl;

use EmRPC qw(DoRPC);
use EmSysTraps;

use strict;
use vars qw(@ISA @EXPORT);

use Exporter;
@ISA = qw(Exporter);

@EXPORT = qw(

	HostGetHostVersion HostGetHostID HostGetHostPlatform 
	HostIsSelectorImplemented HostGestalt HostIsCallingTrap
	
	HostProfileInit HostProfileStart HostProfileStop HostProfileDump 
	HostProfileCleanup HostProfileDetailFn
	
	HostErrNo HostFClose HostFEOF HostFError HostFFlush HostFGetC 
	HostFGetPos HostFGetS HostFOpen HostFPrintF HostFPutC HostFPutS 
	HostFRead HostRemove HostRename HostFReopen HostFScanF HostFSeek 
	HostFSetPos HostFTell HostFWrite HostTmpFile HostTmpNam HostGetEnv

	HostMalloc HostRealloc HostFree

	HostGremlinIsRunning HostGremlinNumber HostGremlinCounter 
	HostGremlinLimit HostGremlinNew
	
	HostImportFile HostExportFile

	HostGetPreference HostSetPreference

	HostLogFile HostSetLogFileSize

	HostSessionCreate HostSessionOpen HostSessionClose HostSessionQuit 
	HostSignalSend HostSignalWait HostSignalResume

	HostTraceInit HostTraceClose HostTraceOutputT HostTraceOutputTL 
	HostTraceOutputVT HostTraceOutputVTL HostTraceOutputB

);

#// HostControl.h functions.

# Host information selectors
use constant hostSelectorGetHostVersion			=> 0x0100;
use constant hostSelectorGetHostID				=> 0x0101;
use constant hostSelectorGetHostPlatform		=> 0x0102;
use constant hostSelectorIsSelectorImplemented	=> 0x0103;
use constant hostSelectorGestalt				=> 0x0104;
use constant hostSelectorIsCallingTrap			=> 0x0105;

# Profiler Selectors
use constant hostSelectorProfileInit			=> 0x0200;
use constant hostSelectorProfileStart			=> 0x0201;
use constant hostSelectorProfileStop			=> 0x0202;
use constant hostSelectorProfileDump			=> 0x0203;
use constant hostSelectorProfileCleanup			=> 0x0204;
use constant hostSelectorProfileDetailFn		=> 0x0205;

# Std C Library wrapper selectors

use constant hostSelectorErrNo					=> 0x0300;

use constant hostSelectorFClose					=> 0x0301;
use constant hostSelectorFEOF					=> 0x0302;
use constant hostSelectorFError					=> 0x0303;
use constant hostSelectorFFlush					=> 0x0304;
use constant hostSelectorFGetC					=> 0x0305;
use constant hostSelectorFGetPos				=> 0x0306;
use constant hostSelectorFGetS					=> 0x0307;
use constant hostSelectorFOpen					=> 0x0308;
use constant hostSelectorFPrintF				=> 0x0309;		# Floating point not yet supported in Poser
use constant hostSelectorFPutC					=> 0x030A;
use constant hostSelectorFPutS					=> 0x030B;
use constant hostSelectorFRead					=> 0x030C;
use constant hostSelectorRemove					=> 0x030D;		# Not yet implemented in Poser
use constant hostSelectorRename					=> 0x030E;		# Not yet implemented in Poser
use constant hostSelectorFReopen				=> 0x030F;		# Not yet implemented in Poser
use constant hostSelectorFScanF					=> 0x0310;		# Not yet implemented in Poser
use constant hostSelectorFSeek					=> 0x0311;
use constant hostSelectorFSetPos				=> 0x0312;
use constant hostSelectorFTell					=> 0x0313;
use constant hostSelectorFWrite					=> 0x0314;
use constant hostSelectorTmpFile				=> 0x0315;
use constant hostSelectorTmpNam					=> 0x0316;		# Not yet implemented in Poser
use constant hostSelectorGetEnv					=> 0x0317;

use constant hostSelectorMalloc					=> 0x0318;		# Not yet implemented in Poser
use constant hostSelectorRealloc				=> 0x0319;		# Not yet implemented in Poser
use constant hostSelectorFree					=> 0x031A;		# Not yet implemented in Poser

# Gremlin Selectors
use constant hostSelectorGremlinIsRunning		=> 0x0400;
use constant hostSelectorGremlinNumber			=> 0x0401;
use constant hostSelectorGremlinCounter			=> 0x0402;
use constant hostSelectorGremlinLimit			=> 0x0403;
use constant hostSelectorGremlinNew				=> 0x0404;

# Database Selectors
use constant hostSelectorImportFile				=> 0x0500;
use constant hostSelectorExportFile				=> 0x0501;

# Preference Selectors
use constant hostSelectorGetPreference			=> 0x0600;
use constant hostSelectorSetPreference			=> 0x0601;

# Logging Selectors
use constant hostSelectorLogFile				=> 0x0700;
use constant hostSelectorSetLogFileSize			=> 0x0701;

# RPC Selectors
use constant hostSelectorSessionCreate			=> 0x0800;		# Not yet implemented in Poser
use constant hostSelectorSessionOpen			=> 0x0801;		# Not yet implemented in Poser
use constant hostSelectorSessionClose			=> 0x0802;
use constant hostSelectorSessionQuit			=> 0x0803;
use constant hostSelectorSignalSend				=> 0x0804;
use constant hostSelectorSignalWait				=> 0x0805;
use constant hostSelectorSignalResume			=> 0x0806;

# External tracing tool support
use constant hostSelectorTraceInit				=> 0x0900;
use constant hostSelectorTraceClose				=> 0x0901;
use constant hostSelectorTraceOutputT			=> 0x0902;
use constant hostSelectorTraceOutputTL			=> 0x0903;
use constant hostSelectorTraceOutputVT			=> 0x0904;
use constant hostSelectorTraceOutputVTL			=> 0x0905;
use constant hostSelectorTraceOutputB			=> 0x0906;

use constant hostSelectorLastTrapNumber			=> 0x0907;


#/* ==================================================================== */
#/* Host environment-related calls										 */
#/* ==================================================================== */

########################################################################
#
#	FUNCTION:		HostGetHostVersion
#
#	DESCRIPTION:	Get the version number of the host (Palm OS Emulator).
#
#	PARAMETERS:		None
#
#	RETURNS:		Version number of Poser in Palm OS version format.
#
########################################################################

sub HostGetHostVersion
{
	# long HostGetHostVersion(void)

	my ($return, $format) = ("int32", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGetHostVersion, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostGetHostID
#
#	DESCRIPTION:	Get the ID of the debugging host.
#
#	PARAMETERS:		None
#
#	RETURNS:		hostIDPalmOS, hostIDPalmOSEmulator, hostIDPalmOSSimulator 
#					etc...
#
########################################################################

sub HostGetHostID
{
	# HostID HostGetHostID(void)

	my ($return, $format) = ("int32", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGetHostID, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostGetHostPlatform
#
#	DESCRIPTION:	Get the host platform ID.
#					hostPlatformPalmOS, hostPlatformWindows, 
#					hostPlatformMacintosh, hostPlatformUnix etc...
#
#	PARAMETERS:		None
#
#	RETURNS:		hostPlatformPalmOS, hostPlatformWindows, 
#					hostPlatformMacintosh, hostPlatformUnix etc...
#
########################################################################

sub HostGetHostPlatform
{
	# HostPlatform HostGetHostPlatform(void)

	my ($return, $format) = ("int32", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGetHostPlatform, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostIsSelectorImplemented
#
#	DESCRIPTION:	Determines if the particular selector is implemented.
#
#	PARAMETERS:		None
#
#	RETURNS:		True or False.
#
########################################################################

sub HostIsSelectorImplemented
{
	# HostBool HostIsSelectorImplemented(long selector)

	my ($return, $format) = ("int32", "int16 int32");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorIsSelectorImplemented, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostGestalt
#
#	DESCRIPTION:	Return queries about the Runtime environment.
#
#	PARAMETERS:		None
#
#	RETURNS:		Runtime environment info.
#
########################################################################

sub HostGestalt
{
	# HostErr HostGestalt(long gestSel, long* response)

	my ($return, $format) = ("HostErr", "int16 int32 rptr");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGestalt, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostIsCallingTrap
#
#	DESCRIPTION:	Determines if the Palm OS Emulator is currently
#					calling a trap.  True if so, false if not.
#
#	PARAMETERS:		None
#
#	RETURNS:		True if trap is being called, false if not.
#
########################################################################

sub HostIsCallingTrap
{
	# HostBool HostIsCallingTrap(void)

	my ($return, $format) = ("int32", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorIsCallingTrap, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


#/* ==================================================================== */
#/* Profiling-related calls												 */
#/* ==================================================================== */


########################################################################
#
#	FUNCTION:		HostProfileInit
#
#	DESCRIPTION:	Initializes and enables profiling in debugging host.
#
#	PARAMETERS:		None
#
#	RETURNS:		Returns zero if successful, non-zero otherwise.
#
########################################################################

sub HostProfileInit
{
	# HostErr HostProfileInit(long maxCalls, long maxDepth)

	my ($return, $format) = ("HostErr", "int16 int32 int32");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorProfileInit, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostProfileDetailFn
#
#	DESCRIPTION:	Profiles the function that contains the specified 
#					address.
#
#	PARAMETERS:		None
#
#	RETURNS:		Returns zero if successful, non-zero otherwise.
#
########################################################################

sub HostProfileDetailFn
{
	# HostErr HostProfileDetailFn(void* addr, HostBool logDetails)

	my ($return, $format) = ("HostErr", "int16 rptr int32");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorProfileDetailFn, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostProfileStart
#
#	DESCRIPTION:	Turns Profiling on.
#
#	PARAMETERS:		None
#
#	RETURNS:		Returns zero if successful, non-zero otherwise.
#
########################################################################

sub HostProfileStart
{
	# HostErr HostProfileStart(void)

	my ($return, $format) = ("HostErr", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorProfileStart, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostProfileStop
#
#	DESCRIPTION:	Initializes and enables profiling in debugging host.
#
#	PARAMETERS:		None
#
#	RETURNS:		Returns zero if successful, non-zero otherwise.
#
########################################################################

sub HostProfileStop
{
	# HostErr HostProfileStop(void)

	my ($return, $format) = ("HostErr", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorProfileStop, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostProfileDump
#
#	DESCRIPTION:	Writes the current profiling information to the 
#					named file.
#
#	PARAMETERS:		None
#
#	RETURNS:		Returns zero if successful, non-zero otherwise.
#
########################################################################

sub HostProfileDump
{
	# HostErr HostProfileDump(const char* filename)

	my ($return, $format) = ("HostErr", "int16 string");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorProfileDump, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostProfileCleanup
#
#	DESCRIPTION:	Initializes and enables profiling in debugging host.
#
#	PARAMETERS:		None
#
#	RETURNS:		Returns zero if successful, non-zero otherwise.
#
########################################################################

sub HostProfileCleanup
{
	# HostErr HostProfileCleanup(void)

	my ($return, $format) = ("HostErr", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorProfileCleanup, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


#/* ==================================================================== */
#/* Std C Library-related calls											 */
#/* 	ADD LATER!!!													 */
#/* ==================================================================== */


#/* ==================================================================== */
#/* Gremlin-related calls												 */
#/* ==================================================================== */


########################################################################
#
#	FUNCTION:		HostGremlinIsRunning
#
#	DESCRIPTION:	Determines if Gremlin is currently running.
#
#	PARAMETERS:		None
#
#	RETURNS:		True if a gremlin is currently running, False otherwise.
#
########################################################################

sub HostGremlinIsRunning
{
	# HostBool HostGremlinIsRunning(void)

	my ($return, $format) = ("int32", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGremlinIsRunning, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostGremlinNumber
#
#	DESCRIPTION:	Retrieves the number of the currently running gremlin.
#
#	PARAMETERS:		None
#
#	RETURNS:		The number of the current gremlin.
#					Only valid if a gremlin is currently executing.
#
########################################################################

sub HostGremlinNumber
{
	# long HostGremlinNumber(void)

	my ($return, $format) = ("int32", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGremlinNumber, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostGremlinCounter
#
#	DESCRIPTION:	Returns the current event counter of the currently 
#					running gremlin.
#
#	PARAMETERS:		None
#
#	RETURNS:		Current event counter.  
#					Only valid if a gremlin is currently executing.
#
########################################################################

sub HostGremlinCounter
{
	# long HostGremlinCounter(void)

	my ($return, $format) = ("int32", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGremlinCounter, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostGremlinLimit
#
#	DESCRIPTION:	Retrieves the limit value of the currently running gremlin.
#
#	PARAMETERS:		None
#
#	RETURNS:		Limit value of the currently running gremlin.
#					Only valid if a gremlin is currently executing.
#
########################################################################

sub HostGremlinLimit
{
	# long HostGremlinLimit(void)

	my ($return, $format) = ("int32", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGremlinLimit, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostGremlinNew
#
#	DESCRIPTION:	Start a new Gremlin Horde.
#
#	PARAMETERS:		Starting Gremlin number.
#					Ending Gremlin number.
#					Frequency (in terms of Gremlin events) at which
#						states are automatically saved.
#					Switching depth (number of events generated before
#						switching to a different Gremlin).
#					Max depth (maximum number of events generated
#						for each Gremlin).
#					List of application names on which to run Gremlins.
#
#	RETURNS:		Error code.
#
########################################################################

sub HostGremlinNew
{
	# HostErr HostGremlinNew(const HostGremlinInfo*)

	my($start, $stop, $save_freq, $switch_depth, $max_depth, @apps) = @_;

	my ($app_string) = join (",", @apps);

	my ($struct) = pack("NNNNN", $start, $stop, $save_freq, $switch_depth, $max_depth) . $app_string;

	my ($return, $format) = ("HostErr", "int16 block");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGremlinNew, $struct);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


#/* ==================================================================== */
#/* Import/export-related calls											 */
#/* ==================================================================== */


########################################################################
#
#	FUNCTION:	HostImportFile
#
#	DESCRIPTION:	Path to file on desktop
#			Card to import file to.
#
#	PARAMETERS:	None
#
#	RETURNS:	Error code.
#
########################################################################

sub HostImportFile
{
	# HostErr HostImportFile(const char* fileName, long cardNum)

	my ($return, $format) = ("HostErr", "int16 string int32");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorImportFile, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:	HostExportFile
#
#	DESCRIPTION:	Export a db from Emulator to the host.
#
#	PARAMETERS:	None
#
#	RETURNS:	Error code.
#
########################################################################

sub HostExportFile
{
	# HostErr HostExportFile(const char* fileName, long cardNum, const char* dbName)

	my ($return, $format) = ("HostErr", "int16 string int32 string");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorExportFile, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


#/* ==================================================================== */
#/* Logging-related calls												 */
#/* ==================================================================== */


########################################################################
#
#	FUNCTION:	HostSetPreference
#
#	DESCRIPTION:	Set a preference.
#
#	PARAMETERS:	prefName, The name of the preference whose value you
#                          are setting.
#               prefValue, The new value of the preference.
#	
#	RETURNS:	Nothing.
#
########################################################################

sub HostSetPreference
{
	# void HostSetPreference(const char*, const char*)

	my ($return, $format) = ("void", "int16 string string");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorSetPreference, @_);
	#//EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:	HostGetPreference
#
#	DESCRIPTION:	Export a db from Emulator to the host.
#
#	PARAMETERS:	prefName, The name of the preference whose value you
#                  want to retrieve.
#
#	RETURNS:	Error code.
#
########################################################################
	
sub HostGetPreference
{
	# HostBool HostGetPreference(const char*, char*)

	my ($return, $format) = ("int32", "int16 string string");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorGetPreference, $_[0], "");
	($D0,	prefName	=> $params[1],
			prefValue	=> $params[2]);
}




########################################################################
#
#	FUNCTION:		HostSetLogFileSize
#
#	DESCRIPTION:	Determines the size of the log file the Palm OS 
#					Emulator is using.  By default the Palm OS Emulator
#					Uses a 1 MB log file to record the last 1 MB of 
#					Log Data information.
#
#	PARAMETERS:		Size, The new size for the logging file in bytes.
#
#	RETURNS:		None.
#
#
########################################################################

sub HostSetLogFileSize
{
	# void HostSetLogFileSize(long)

	my ($return, $format) = ("int16", "int16 int32");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorSetLogFileSize, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


#/* ==================================================================== */
#/* RPC-related calls													 */
#/* ==================================================================== */


########################################################################
#
#	FUNCTION:		HostSessionCreate
#
#	DESCRIPTION:	Create a new session.
#
#	PARAMETERS:		Name of device to emulate.  Choices are: "Pilot",
#						"PalmPilot", "Palm III", "Palm IIIx",
#						"Palm V", "Palm VII".
#					RAM size (in K) to emulate.
#					Path to ROM to use.
#
#	RETURNS:		Error code.
#
########################################################################

sub HostSessionCreate
{
	# HostErr HostSessionCreate(const char* device, long ramSize, const char* romPath)

	my ($return, $format) = ("HostErr", "int16 string int32 string");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorSessionCreate, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostSessionOpen
#
#	DESCRIPTION:	Open a previously create session file.
#
#	PARAMETERS:		Path to session file to open.
#
#	RETURNS:		Error code.
#
########################################################################

sub HostSessionOpen
{
	# HostErr HostSessionOpen(const char* psfFileName)

	my ($return, $format) = ("HostErr",  "int16 string");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorSessionOpen, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostSessionClose
#
#	DESCRIPTION:	Close the current session, optionally saving it.
#
#	PARAMETERS:		Name of session file to create. Can be null.
#
#	RETURNS:		Error code.
#
########################################################################

sub HostSessionClose
{
	# HostErr HostSessionClose(const char* saveFileName)

	my ($return, $format) = ("HostErr", "int16 string");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorSessionClose, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostSessionQuit
#
#	DESCRIPTION:	Ask Palm OS Emulator to quit.
#
#	PARAMETERS:		None
#
#	RETURNS:		Error code.
#
########################################################################

sub HostSessionQuit
{
	# HostErr HostSessionQuit(void)

	my ($return, $format) = ("HostErr", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorSessionQuit, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostSignalSend
#
#	DESCRIPTION:	Sends a signal to any script that has host signal 
#					wait calls pending.
#
#	PARAMETERS:		signalNumber, The signal you want to wait for.
#
#	RETURNS:		List containing the error code and the numeric
#					signal value returned from the Emulator.
#
########################################################################

sub HostSignalSend
{
	# HostErr HostSignalSend(HostSignal signalNumber)

	my ($return, $format) = ("HostErr", "int16 int32*");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorSignalSend, $_[0], 0);

	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}


########################################################################
#
#	FUNCTION:		HostSignalWait
#
#	DESCRIPTION:	Wait for a signal from the Palm OS Emulator.
#
#	PARAMETERS:		timeout (in milliseconds)
#
#	RETURNS:		List containing the error code and the numeric
#					signal value returned from the Emulator.
#
########################################################################

sub HostSignalWait
{
	# HostErr HostSignalWait(long timeout, HostSignal* signalNumber)
	
	my ($return, $format) = ("HostErr", "int16 int32 rptr");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorSignalWait, $_[0], 0);

	($D0, $params[2]);	# 0 = selector, 1 = timeout, 2 = signal number
}


########################################################################
#
#	FUNCTION:		HostSignalResume
#
#	DESCRIPTION:	Tell the Emulator to resume after it has sent us
#					a signal.
#
#	PARAMETERS:		None
#
#	RETURNS:		Error code.
#
########################################################################

sub HostSignalResume
{
	# HostErr HostSignalResume(void)

	my ($return, $format) = ("HostErr", "int16");
	my ($D0, $A0, @params) = EmRPC::DoRPC (EmSysTraps::sysTrapHostControl, $format,
						hostSelectorSignalResume, @_);
	EmRPC::ReturnValue ($return, $D0, $A0, @params);
}
