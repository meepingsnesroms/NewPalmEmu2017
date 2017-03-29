#!/usr/bin/perl -w
########################################################################
#
#	File:			FormSpy.pl
#
#	Purpose:		Examine the current active form.
#
#	Description:	This script gets the current active form, iterates
#					over its contents, and prints out information on
#					all of the form objects.  For each object, it prints
#
#					* The object's index number (starting from zero)
#					* The object's type (frmTitleObj, etc.)
#					* Text associated with the object (only for title,
#					  label, and control objects)
#					* The object's bounds
#
########################################################################

use EmRPC;			# EmRPC::OpenConnection, CloseConnection
use EmFunctions;

EmRPC::OpenConnection("localhost:2000#Console");

	#=====================================================================
	# Get the current form and the number objects on that form.
	#=====================================================================

	my ($form) = FrmGetActiveForm();
	my ($num_objects) = FrmGetNumberOfObjects($form);

	#=====================================================================
	# Iterate over all the objects on the form.
	#=====================================================================

	for $ii (0..$num_objects - 1)
	{
		#=====================================================================
		# Start generating the line to print.  Start with the object's index.
		#=====================================================================

		my ($line) = "$ii. ";

		#=====================================================================
		# Add the object's type (frmTitleObj, etc.) to the line.
		#=====================================================================

		my ($object_type) = FrmGetObjectType($form, $ii);

		my ($type) = ("frmFieldObj", "frmControlObj", "frmListObj", "frmTableObj",
					  "frmBitmapObj", "frmLineObj", "frmFrameObj", "frmRectangleObj",
					  "frmLabelObj", "frmTitleObj", "frmPopupObj", "frmGraffitiStateObj",
					  "frmGadgetObj", "frmScrollBarObj")[$object_type];

		$line .= " $type";

		#=====================================================================
		# If the object is a frmControlObj, frmLabelObj, or frmTitleObj,
		# get the text associated with the object and add it to our line.
		#=====================================================================

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

		#=====================================================================
		# Add the object's bounds to the line.
		#=====================================================================

		my (%bounds) = FrmGetObjectBounds($form, $ii);
		$line .= " ($bounds{left}, $bounds{top}, $bounds{right}, $bounds{bottom})";

		#=====================================================================
		# Print out the result.
		#=====================================================================

		print "$line\n";
	}

EmRPC::CloseConnection();
