########################################################################
#
#	File:			EmUtils.pm
#
#	Purpose:		High-level utilities for scripting the Palm OS
#					Emulator
#
#	Description:	This file contains the following useful utilities:
#
#					Wait
#						Wait for a signal from the Emulator.
#
#					TapPen
#						Tap the pen at the given x,y location.
#
#					TapButton
#						Tap the pen on the button with the given name.
#
#					ClipperGoToURL
#						Launches the web clipping application with a given URL.
#
########################################################################

package EmUtils;

use strict;
use vars qw(@ISA @EXPORT);

use EmFunctions;	# EvtEnqueuePenPoint, etc.
use HostControl;	# HostSignalWait, HostSignalResume, etc.

use Exporter;
@ISA = qw(Exporter);
@EXPORT = qw(
	Wait
	Resume
	TapPen TapPenSync
	TapButton TapButtonSync
	EnterKey EnterKeySync
	ClipperGoToURL

);


########################################################################
#
#	FUNCTION:		Wait
#
#	DESCRIPTION:	Wait for a signal from the Palm OS Emulator.
#
#	PARAMETERS:		timeout in milliseconds.
#
#	RETURNED:		List containing the HostSignalResume error code
#					and the number of the signalled event.
#
########################################################################

sub Wait
{
	my $timeout = $_[0];
	if (not defined $timeout)
	{
		$timeout = 0x7fffffff;
	}

	my ($err, $signal) = HostSignalWait ($timeout);
	die "Didn't hear back from Poser, stopped" if ($err != 0);

	($err, $signal);
}


########################################################################
#
#	FUNCTION:		Resume
#
#	DESCRIPTION:	Resume the Palm OS Emulator after it paused itself
#					after sending a signal.
#
#	PARAMETERS:		none.
#
#	RETURNED:		Nothing.
#
########################################################################

sub Resume
{
	HostSignalResume ();
}


########################################################################
#
#	FUNCTION:		TapPen
#
#	DESCRIPTION:	Simulate a tap at the given location, then wait for
#					the next null event.
#
#	PARAMETERS:		x, y coordinates.
#
#	RETURNED:		Nothing.
#
########################################################################

sub TapPen
{
	my ($err, $point) = PenScreenToRaw ({x => $_[0], y => $_[1]});
		
	EvtEnqueuePenPoint ($point);
	EvtEnqueuePenPoint ({x => -1, y => -1});
}

sub TapPenSync
{
	Wait ();
	TapPen (@_);
	Resume ();
}


########################################################################
#
#	FUNCTION:		TapButton
#
#	DESCRIPTION:	Simulate a tap on the named button, then wait for
#					the next null event.
#
#	PARAMETERS:		Name of the button to tap on.
#
#	RETURNED:		Nothing.
#
########################################################################

sub TapButton
{
	my ($button_name) = @_;
	my($ii);

	my ($form) = FrmGetActiveForm();
	my ($num_objects) = FrmGetNumberOfObjects($form);

	for $ii (0..$num_objects - 1)
	{
		my ($object_type) = FrmGetObjectType($form, $ii);

		if ($object_type == EmFunctions::frmControlObj)
		{
			my ($obj_ptr) = FrmGetObjectPtr ($form, $ii);
			my ($address, $label) = CtlGetLabel($obj_ptr);

			if ($label eq $button_name)
			{
				my (%bounds) = FrmGetObjectBounds($form, $ii);

				my ($x, $y) = (	$bounds{left} + $bounds{width} / 2,
								$bounds{top} + $bounds{height} / 2);

				($x, $y) = WinWindowToDisplayPt ($x, $y);

				TapPen ($x, $y);

				last;	# break out of the for loop.
			}
		}
	}
}

sub TapButtonSync
{
	Wait ();
	TapButton (@_);
	Resume ();
}

########################################################################
#
#	FUNCTION:		EnterKey
#
#	DESCRIPTION:	Enter a key, then wait for the next null event.
#
#	PARAMETERS:		WChar asciiChar, UInt16 keycode, UInt16 modifiers
#
#	RETURNED:		Nothing.
#
########################################################################

sub EnterKey
{
	EvtEnqueueKey($_[0], $_[1], $_[2]);
}

sub EnterKeySync
{
	Wait ();
	EnterKey (@_);
	Resume ();
}

########################################################################
#
#	FUNCTION:		ClipperGoToURL
#
# 	AUTHOR:	 		Flash Sheridan, based on C code by David Fedor
#
#	DESCRIPTION:	Launches Clipper to view the given URL.
#
#	PARAMETERS:		URL string
#
#	RETURNS:		An OS error code; zero means no error.
#
########################################################################

sub ClipperGoToURL 
{
	my $url = $_[0] . "\0";
	my $sysAppLaunchCmdGoToURL = 54;
	my($ClipperID);
	$ClipperID = DmFindDatabase (0, "Clipper") if not $ClipperID;
	die "Clipper not found" unless $ClipperID;	

	my $cmdPB = MemPtrNew (length ($url));
	EmRPC::WriteBlock ($cmdPB, $url);
	MemPtrSetOwner($cmdPB, 0);
	SysUIAppSwitch (0, $ClipperID, $sysAppLaunchCmdGoToURL, $cmdPB);		
}

1;
