#!/usr/bin/perl
########################################################################
#
#	File:			PoserRPC.pl
#
#	Purpose:		Scrap file for testing Poser's RPC mechanism
#
#	Description:	This file contains a hodgepodge of scripts and
#					commands used to test out parts of Poser's RPC.
#					Don't take anything in this file too seriously;
#					it's provided only for completeness' sake.
#
########################################################################

use EmRPC;			# EmRPC::OpenConnection, CloseConnection
use EmFunctions;
use EmUtils;		# Wait, TapPen, TapButton

use constant hostSignalReserved			=> 0;
use constant hostSignalIdle				=> 1;
use constant hostSignalQuit				=> 2;
use constant hostSignalSessionStarted	=> 3;
use constant hostSignalSessionStopped	=> 4;

EmRPC::OpenConnection("localhost:2000#Console");

if (1)
{
	my ($err, $result) = HwrDisplayAttributes (0, hwrDispType, "xxxx");
	print "hwrDispType", ($err ? ": err = $err" : (" = ", $result)), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispRev, "xx");
	print "hwrDispRev", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispVers, "xx");
	print "hwrDispVers", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispAllDepths, "xx");
	print "hwrDispAllDepths", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispMaxDepth, "xx");
	print "hwrDispMaxDepth", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispBootDepth, "xx");
	print "hwrDispBootDepth", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispMaxGrays, "xx");
	print "hwrDispMaxGrays", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispHorizontal, "xx");
	print "hwrDispHorizontal", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispVertical, "xx");
	print "hwrDispVertical", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispVRAMBaseAddr, "xxxx");
	print "hwrDispVRAMBaseAddr", ($err ? ": err = $err" : (" = ", unpack ("N", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispVRAMSize, "xxxx");
	print "hwrDispVRAMSize", ($err ? ": err = $err" : (" = ", unpack ("N", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispColor, "xx");
	print "hwrDispColor", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispName, pack ("x32"));
	print "hwrDispName", ($err ? ": err = $err" : (" = ", $result)), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispBaseAddr, "xxxx");
	print "hwrDispBaseAddr", ($err ? ": err = $err" : (" = ", unpack ("N", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispDepth, "xx");
	print "hwrDispDepth", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispWidth, "xx");
	print "hwrDispWidth", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispHeight, "xx");
	print "hwrDispHeight", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispRowBytes, "xx");
	print "hwrDispRowBytes", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispBacklight, "x");
	print "hwrDispBacklight", ($err ? ": err = $err" : (" = ", unpack ("c", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispBrightness, "x");
	print "hwrDispBrightness", ($err ? ": err = $err" : (" = ", unpack ("c", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispContrast, "x");
	print "hwrDispContrast", ($err ? ": err = $err" : (" = ", unpack ("c", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispDbgIndicator, "xx");
	print "hwrDispDbgIndicator", ($err ? ": err = $err" : (" = ", unpack ("n", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispEndAddr, "xxxx");
	print "hwrDispEndAddr", ($err ? ": err = $err" : (" = ", unpack ("N", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispBufferMask, "xxxx");
	print "hwrDispBufferMask", ($err ? ": err = $err" : (" = ", unpack ("N", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispResolutionX, "xxxx");
	print "hwrDispResolutionX", ($err ? ": err = $err" : (" = ", unpack ("N", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispResolutionY, "xxxx");
	print "hwrDispResolutionY", ($err ? ": err = $err" : (" = ", unpack ("N", $result))), "\n";

	my ($err, $result) = HwrDisplayAttributes (0, hwrDispMemAccessOK, "x");
	print "hwrDispMemAccessOK", ($err ? ": err = $err" : (" = ", unpack ("c", $result))), "\n";
}

if (0)
{
	TapButtonSync("OK");
}

if (0)
{
	Wait();
	$err = HostSessionClose ("");	# Don't save
	die "$err" if $err;
	$err = HostSessionQuit ();
	die "$err" if $err;
}


if (0)
{
	my ($err, $signal);

	########################################################################
	print "Waiting for idle\n";

	do {
		($err, $signal) = HostSignalWait (0x7fffffff);
		if ($err)
		{
			HostSignalResume ();
			die "Error $err while waiting for hostSignalIdle";
		}
	} while ($signal != hostSignalIdle);

	########################################################################
	print "Closing session\n";

	$err = HostSessionClose ("");	# Don't save

	########################################################################
	print "Waiting for session to close\n";

	do {
		($err, $signal) = HostSignalWait (0x7fffffff);
		if ($err)
		{
			HostSignalResume ();
			die "Error $err while waiting for hostSignalSessionStopped";
		}
	} while ($signal != hostSignalSessionStopped);

	########################################################################
	print "Creating session\n";

	$err = HostSessionCreate ("PalmIII", 1024, "C:\\ROMs\\spp\\rom30dbg.rom");

	########################################################################
	print "Waiting for session to start\n";

	do {
		($err, $signal) = HostSignalWait (0x7fffffff);
		if ($err)
		{
			HostSignalResume ();
			die "Error $err while waiting for hostSignalSessionStarted";
		}
	} while ($signal != hostSignalSessionStarted);

	########################################################################
	print "Closing session\n";

	$err = HostSessionClose ("");	# Don't save

	########################################################################
	print "Waiting for session to close\n";

	do {
		($err, $signal) = HostSignalWait (0x7fffffff);
		if ($err)
		{
			HostSignalResume ();
			die "Error $err while waiting for hostSignalSessionStopped";
		}
	} while ($signal != hostSignalSessionStopped);

	########################################################################

	HostSignalResume ();
	print "Done!\n";
}

if (0)
{
	$addr = MemPtrNew (100);
	printf ("0x%08X\n", $addr);
	EmRPC::WriteBlock ($addr, "1234567890");
	$str = EmRPC::ReadBlock ($addr, 10);
	print $str, "\n";
	MemPtrFree ($addr);
}

if (0)
{
	TapPen (100, 100);
}

if (0)
{
	$vers = HostGetHostVersion ();
	printf ("HostGetHostVersion() = 0x%08X\n", $vers);
}

if (0)
{
	$num = DmNumDatabases (0);
	print "DmNumDatabases(0) = ", $num, "\n";

	$localID = DmFindDatabase (0, "MemoDB");
	printf ("DmFindDatabase(0, \"MemoDB\") = 0x%08X\n", $localID);

	($err, %results) = DmDatabaseInfo (0, $localID);
	printf ("DmDatabaseInfo(0, 0x%08X) = 0x%08X\n", $localID, $err);
	print ("results: \n");
	print ("\tname = ", $results{name}, "\n");
	print ("\tattributes = ", $results{attributes}, "\n");
	print ("\tversion = ", $results{version}, "\n");
	print ("\tcrDate = ", $results{crDate}, "\n");
	print ("\tmodDate = ", $results{modDate}, "\n");
	print ("\tbckUpDate = ", $results{bckUpDate}, "\n");
	print ("\tmodNum = ", $results{modNum}, "\n");
	print ("\tappInfoID = ", $results{appInfoID}, "\n");
	print ("\tsortInfoID = ", $results{sortInfoID}, "\n");
	print ("\ttype = ", $results{type}, "\n");
	print ("\tcreator = ", $results{creator}, "\n");
}

if (0)
{
	$block = EmRPC::ReadBlock (0, 256);
	EmRPC::PrintString ($block);
}

if (0)
{
	my ($form) = FrmGetActiveForm();
	my ($num_objects) = FrmGetNumberOfObjects($form);

	for $ii (0..$num_objects - 1)
	{
		my ($line) = "$ii. ";
		my ($object_type) = FrmGetObjectType($form, $ii);

		my ($type) = ("frmFieldObj", "frmControlObj", "frmListObj", "frmTableObj",
					  "frmBitmapObj", "frmLineObj", "frmFrameObj", "frmRectangleObj",
					  "frmLabelObj", "frmTitleObj", "frmPopupObj", "frmGraffitiStateObj",
					  "frmGadgetObj", "frmScrollBarObj")[$object_type];

		$line .= " $type";

		if ($object_type == frmControlObj)
		{
			my ($obj_ptr) = FrmGetObjectPtr ($form, $ii);
			my ($address, $label) = CtlGetLabel($obj_ptr);
			$line .= " \"$label\"";
		}
		elsif ($object_type == frmLabelObj)
		{
			my ($label_id) = FrmGetObjectId ($form, $ii);
			my ($address, $label) = FrmGetLabel($form, $label_id);
			$line .= " \"$label\"";
		}
		elsif ($object_type == frmTitleObj)
		{
			my ($address, $title) = FrmGetTitle($form,);
			$line .= " \"$title\"";
		}
		else
		{
			$line .= " <no label>";
		}

		my (%bounds) = FrmGetObjectBounds($form, $ii);
		$line .= " ($bounds{left}, $bounds{top}, $bounds{right}, $bounds{bottom})";

		print "$line\n";
	}
}

if (0)
{
	$err = HostSessionClose ("");
	printf ("HostSessionClose() = 0x%08X\n", $err);

	$err = HostSessionQuit ();
	printf ("HostSessionQuit() = 0x%08X\n", $err);
}

if (0)
{
	HostGremlinNew (0, 3, 0, -1, 10000, "Memo Pad") == 0 || die "HostGremlinNew failed, stopped";
}

EmRPC::CloseConnection();



