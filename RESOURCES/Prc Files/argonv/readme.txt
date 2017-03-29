Argon V - blast your way home  (c) 1999 - 2002 by Till Harbaum
--------------------------------------------------------------
palm@harbaum.org            - http://www.harbaum.org/till/palm

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

WHAT IS ARGON V?
Argon V is the first game for the palm to make use of the
16 shades of grey the new palm models can display. Argon V
is a action shooter with vertical multilayer scrolling. You
objective is to shoot everything that moves.

SYSTEM REQUIREMENTS
Argon V requires a palm computing device capable of displaying
16 shades of grey simultaneously. Currently the Palm IIIx,
Palm IIIe, Palm V, Palm Vx and the Handspring Visor do support
this. Furthermore, the device needs a screen with high refresh
capabilities to avoid smearing and streaking effects. 
Unfortunately most Palm IIIx displays have been verified to
be unable to display fast moving sprites and backgrounds.

INSTALLATION
Install Argon V on your Palm Pilot by hotsynching ArgonV.prc
onto your Palm.

HISTORY
Version 1.0  - initial release
Version 1.01 - gamepad support, changed default key mapping,
	       slower but Palm IIIc and Visor compatible
               video driver
Version 1.02 - small updates of the video driver for 
	       Palm OS 3.5 and up
Version 1.03 - another video driver fix, this time for the
	       palm tungsten

FURTHER DEVELOPMENT
Argon V is a work in progess. To further develop this game into
the best palm game ever, your help is needed. Without your
help version 1.02 will be the last version released.

You will have noticed, that Argon V lacks several features
and needs the inclusion of more and different enemies, sounds,
music, a nice title screen, more weapons and other extras,
more complex background images ...

Let's prove, that there is another way for game development
on the palm than shareware!

GRAPHICS
You don't need to be a programmer to participate. Just take 
your favorite paint program and draw new background images
(imag*.gif) or sprites (sprt*.gif). Take a look at the
existing images for the required image format (left half is 
always image data, right half is transparency map). Please
use only the predefined shades of grey displayed as in the 
grey bar in all images and sprites.

New background images can then be transferred into gif images
with correct gif transparency using ImageMagick and afterwards
be included into the level editor argoned. Under Linux
a simple 'make level' will do all this automatically.
Windows will probably need some changes to the Makefile
or new batch files (see the WINDOWS section).

SOUND
Argon V currently has no sound at all. If you have some
cool sound routines or free midi tunes for the palm,
they are very welcome. Please don't send me midi tunes
that are not verified to work with the palm sound routines.
WAV files, MP3 and whatever else won't work either.
Complete sound routines are preferred :-)

NEW ENEMIES, NEW WAVE TYPE, NEW GAME PLAY
This involves major code changes/extensions. You'll have
to be a programmer to participate in this. Ideas for
new game elements are welcome, but if you implement
you ideas into the game yourself, they are much more 
likely to become part of the official Argon V. 

A VERSION FOR OLD PALMS
The current version of Argon V does not support machines
with less than 16 shades (4 bits) of grey. A version for the 
old palms would require images reduced to four shades of grey
(2 bits, black, white and two greys, see empty4.gif for the 
shades available). If all necessary images are available in
four shades of grey, the image conversion tools (grey.c
and bmp2bin.c) need to be changed to support 2 bits per
pixel, too. And the video driver for the palm (video.c) needs 
to be translated into a new version for images with four
shades of grey.

DEVELOPMENT TOOLS
Argon V was developed on a Linux machine using free development
tools only. To compile the current version of Argon V you'll
need:

- gcc (compiler for the host)
- prc-tools (compiler and tools for the palm)
- pilrc (palm ressource compiler)
- ImageMagick (image conversion utilities)
- Tcl/Tk (script language with GUI support)

LINUX
The recent linux distributions include ImageMagick and Tcl/Tk. 
Links to the necessary prc-tools and pilrc are available at 
http://www.harbaum.org/till/palm

WINDOWS
Windows versions of the prc-tools and pilrc are available at
www.palmgear.com, Tcl/Tk, a gcc for the host and other
development tools needed are in the cygwin package
available at www.cygnus.com. Binaries of ImageMagick
for all kinds of OS's are available at
http://www.wizards.dupont.com/cristy/ImageMagick.html

A complete compile of Argon V under Windows hasn't been
tested yet, but will probably need some changes in the
Makefiles. Any feedback is very welcome, please try not
to break the Linux Makefiles when adding Windows support.

CODEWARRIOR
Argon V has been developed using gcc. A port to codewarrior
hasn't been done, but should be possible without major
problems. If you port Argon V to this platform please try
not to break the unix development branch.
