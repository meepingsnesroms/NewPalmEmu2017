#!/usr/bin/perl -w
########################################################################
#
#	File:			SkipStartup.pl
#
#	Purpose:		Skip the NTFull_enUS.rom startup application.
#
#	Description:	Run this script to skip past the application that
#					automatically starts when cold-booting a Palm 
#					NTFull_enUS.rom, or NTFull_jpJP.rom.  
#					It generates the appropriate
#					pen events to "tap past" the initial forms.
#
########################################################################

use EmRPC;			# EmRPC::OpenConnection, CloseConnection
use EmFunctions;
use EmUtils;		# TapPenSync, TapButtonSync


EmRPC::OpenConnection("localhost:2000#Console");

	TapPenSync (10*2, 10*2);			# First tap in pen calibration screen
	TapPenSync ((160-10)*2, (160-10)*2);		# Second tap in pen calibration screen
	TapPenSync (80*2, 60*2);			# Confirmation tap in pen calibration screen

#	Uncomment the following lines to Skip past a NTFull_EFIGS.rom
	TapPenSync (15*2, 155*2);			# Tap OK button
	TapPenSync (25*2, 145*2);			# Tap Yes button
	TapPenSync (65*2, 150*2);			# Tap Next button
	TapPenSync (105*2, 150*2);			# Tap Done button

EmRPC::CloseConnection();
