Noiz2sa  readme_e.txt
ported to TapWave Zodiac by Andrew Kearns (support@pocketdimension.com)
based on the version by Kenta Cho
for Windows98/2000/XP
ver. 0.51
(C) Kenta Cho

Abstract shootem up game, 'Noiz2sa'.


- How to install.

Unpack noiz2sa_zodiac.zip
hotsync Noiz2sa.prc to your device or SD card
Make the directory "Palm/Programs/Noiz2sa and
copy all the folders to a SD card.  You must keep the 
folder and file structure intact.

MOD Music can be added to the sound directory.
The files must have an .MOD, .XM, .IT extension, and not all
MOD files are supported although most work fine.  Memory is
the big consideration as MODs can be large.

There is a limit of 64 mods in the directory.  I advise putting
only one in the directory and testing it while first putting them
on.

Pressing the function button on the title screen starts a random
mod playing.  The filename is shown in the left box.


- How to play.

Select the stage by a keyboard or a joystick.

 - Movement  Joystick
 - Fire      Green       
 - Slowdown  Yellow      
 - Pause     Function

Press a fire key to start the game.

Control your ship and avoid the barrage.
A ship is not destroyed even if it contacts an enemy main body.
A ship becomes slow while holding the slowdown key.

A green star is the bonus item.
A score of the item(displayed at the left-up corner) increases 
if you get items continuously.

When all ships are destroyed, the game is over.
The ship extends 200,000 and every 500,000 points.


- Add your original barrage patterns.

You can add your own barrage patterns to Noiz2sa.
In the 'noiz2sa' directory, there are 3 directories named
'zako', 'middle' and 'boss'.
In these directories, the barrage pattern files are placed.

The barrage pattern files are written by BulletML.
About BulletML, see the page:

BulletML
http://www.asahi-net.or.jp/~cs8k-cyu/bulletml/index_e.html

A 'zako' directory is for the small enemies.
A 'middle' directory is for the middle class enemies.
A 'boss' directory is for the boss type enemies.

You should adjust the difficulty of the barrage
by using a $rank variable properly.
A $rank variable is used to control the difficulty
of each scene in Noiz2sa.


- Comments

If you have any comments, please mail to cs8k-cyu@asahi-net.or.jp.


- Acknowledgement

libBulletML is used to parse BulletML files.
 libBulletML
 http://user.ecc.u-tokyo.ac.jp/~s31552/wp/libbulletml/


Note:  SDL is not used for the Zodiac version
 
Simple DirectMedia Layer is used for the display handling. 
 Simple DirectMedia Layer
 http://www.libsdl.org/


-- License

License
-------

Copyright 2002 Kenta Cho. All rights reserved. 

Redistribution and use in source and binary forms, 
with or without modification, are permitted provided that 
the following conditions are met: 

 1. Redistributions of source code must retain the above copyright notice, 
    this list of conditions and the following disclaimer. 

 2. Redistributions in binary form must reproduce the above copyright notice, 
    this list of conditions and the following disclaimer in the documentation 
    and/or other materials provided with the distribution. 

THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, 
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL 
THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
