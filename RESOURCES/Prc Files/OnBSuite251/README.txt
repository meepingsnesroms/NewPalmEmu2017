These are release notes for the OnBoard Suite.  These tools are free software 
under the GNU General Public License.  The OnBoard Suite homepage (where you 
can always get the latest downloads) can be found at:

	http://onboardc.sourceforge.net/

This page points to the user's forum on Yahoo:

	http://groups.yahoo.com/group/onboardc

and the developer's pages on SourceForge

	http://sourceforge.net/projects/onboardc

You can learn more about the GNU Public License from:

	http://www.fsf.org/licenses/gpl.html	

-------------------------------------------
Release 2.4.2

The files in this release are:

	OnBSuite242_src.tgz
	OnBSuite242_src.zip
		o source tree
		o ExampleProjects
		o Documentation
		o OnBoardHeaderV40.pdb
		o README.txt
		o COPYING.txt
		o SrcEdit_KeyboardSupport.txt

	OnBSuite242.tgz
	OnBSuite242.zip
		o OnBoardC.prc, OnBoard.prc, SrcEdit.prc
		o ExampleProjects
		o Documentation
		o OnBoardHeaderV40.pdb
		o README.txt
		o COPYING.txt
		o SrcEdit_KeyboardSupport.txt

These files build with the PRC toolkit using Gnu C Compiler version
2.95.3-kgpd.

The changes in this release are:
    
    OnBoardC
	849435	OnBC: .proj and .rsrc files need backup bit (and generated prc)
	825817	OnBC: Macro problem with double datatype
	866957	WeirdAssembly Error w/ extern func ptrs
    OnBoard
	874893	OnBA: Bad code generated from systrap bug
	xxxxxx	OnBA: First draft of a User's Guide for OnBA
	876013	Only add debug function names when requested
	876009	OnBA: Generate better code for 0 displacement
    SrcEdit
		BUG: Cursor doesn't blink when positioned at the page far right
		BUG: Tap @ X>160 (in short DOCs with very few lines)
		BUG: Long Line BUG
		BUG: More double cursor problems
	692889	(S011) SrcEdit: HiRes mode (including Font Hack support)
	846728	(S016) SrcEdit: External Keyboard Support
		(N.B. See SrcEdit_KeyboardSupport.txt for more info)
	949425	High-Resolution fonts suport
	684392	SrcEdit (HiRes): right half  of screen ignores taps
	684384	SrcEdit (HiRes): drag select off bottom of screen bug
	634524	(S037,S034) SrcEdit crashes on Open Dialog
	910455	SrcEdit: Support the Sony Jog-Dial for scrolling
	861914	SrcEdit: crash on 'save as' using existing filename bug
	847959	(S062) SrcEdit: saveAs screen bug
	621840	(S032) SrcEdit: document categories resetting bug
	624273	(S033) SrcEdit: does not reset grafitti state bug
	846288	(S058) SrcEdit: Popup Tools Menu
	892131	SrcEdit: double cursors
	906652	SrcEdit: Support for Alphasmart Dana Screen size
	899043	SrcEdit: quote auto complete
	895637	SrcEdit: grey out left & right arrows
	891109	SrcEdit: Select All
	874196	SrcEdit: New button on open form
	870770	SrcEdit (Tungsten T3)
	869072	SrcEdit: let the Beeping follow SysPrefs
	864525	SrcEdit: Scrolling is buggy with 5-way key
	863546	Screen redraw bug
	847961	(S061) SrcEdit: Add Tab/Spaces option
	846707	(S055) SrcEdit: File info and attributes
	846293	(S046) SrcEdit: pick highlight mode based on file extension
	846292	(S051) SrcEdit: Use hard buttons to scroll
	846291	(S053) Comment-out selected region
	792166	SrcEdit (treo): alt key does not
	789951	SrdEdit: //* comment bug
	786055	(S013) SrcEdit: Replace
	769745	SrcEdit (Treo 180): ListType key not interpretted properly
	618591	(S030) SrcEdit 'too large file error'
    Documentation
	846867	(D002) Cookbook: checkboxes
    Sherpa
	(None)

	Possibly a few other minor bug fixes

Special Thanks go to John Wilund for all his work on SrcEdit, and to
everyone else who contributed.
Also to Wade for his inspiring work as an admin over the past several years, 
and his help in getting this release done.

-------------------------------------------
From Release 2.2 (We're gonna keep this one for awhile)

  IMPORTANT NOTE TO EXISTING USERS:  We've made some changes to
  OnBoardHeader.h.  Not only does the default version now support OS4.0
  but we've also removed some data types that are incompatible with the
  PRC tools.  If you've got a pre-existing product you need to either:
  
	1) include "OnBoardCompatability.h" (included in the
	   OnBoardC/Samples directory) and, possibly, "MathLib.h", or
	2) replace OnBoardHeader.h with OnBoardHeader35.h (also in
	   the Samples directory).
  
  Note that if you use the skeleton to make a new program, you'll need the
  new OnBoardHeader.h (it's v40).  Our goal, with this change, was to make
  it easier to port OnBoardC programs to the PRC tools and vice versa.
  Thanks for you understanding.

--
