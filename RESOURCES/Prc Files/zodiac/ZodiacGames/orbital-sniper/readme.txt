Orbital Sniper / Zodiac
-----------------------
Version 1.0
Copyright 2002 - 2004 Jari Komppa
http://iki.fi/sol



This is a game for the Tapwave Zodiac handheld console.

 

This software is provided 'as-is', without any express or implied
warranty.    In no event will the authors be held liable for any damages
arising from the use of this software.


-- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< --


Welcome to utopia.

The year is 2174, and you have been ordered to function as an
orbital sniper. In your world there's just three kinds of people:
VIPs, dissidents and normal citizens. VIPs run the world: they must
not come to harm. Dissidents must die. If a commoner or two gets
wasted in progress, it'll count against you when your post ends.

You were a normal citizen only moments ago. If you manage to prove
yourself and keep VIPs safe in your area, they might make you
a VIP. Or do poorly enough and they might decide that you're the
enemy.

On screen, VIPs are designated blue, threats are designated red
and the normal folk are white.


-- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< --


You control the target with the analog joystick (or stylus); 
use blue and green buttons to zoom. Different zoom modes are 
useful for different things. Zoom full out to see the whole 
situation at a glance (with all that useless clutter removed), 
or zoom full in for better aiming. Several levels of zoom in 
between give different information.

Red button fires your gun (which is based on some new physics laws
that we haven't invented yet, as the target is destroyed instantly).
The gun reloads for three seconds, so make sure you hit.

A typical game round lasts for a couple of minutes. It starts out easy,
but gets rather nasty later on.

Comments etc can be tossed my way; my current email address
is jari.komppa@kolumbus.fi, but you can find me at
http://iki.fi/sol even if that changes.


-- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< --


Version 1.0
First public, signed release.
- Fixed "device does not go to sleep after being idle for a while" while not in-game.
- Audio latency is a bit better now.
- Added slight vibration effect when you shoot.

Version 1.0b
Unsigned test version. Based on Orbital Sniper 1.20. Most major differences:
- Screen size (was hardcoded to 640x480; now hardcoded to 480x320 =)
- HUD rearranged so that the text doesn't obscure view
- Controls are (obviously) different
- Game slowed down a bit to make it a bit more sane without a mouse.


-- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< --


Orbital Sniper was my entry to the Ludum Dare 48h game design contest
in 2002. Version 1.0 of the zodiac version is a fairly direct port of
the version that I wrote during those 48 hours. The original time log
follows:


-- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< --


Build log

----
Saturday
----

4am 
contest begins

10am 
I manage to drag myself out of bed, with a great idea of a game if it has a 'gravity' theme, and
find that it's 'guardian'. Ponder upon several ideas, take a walk.

11am 
Start drawing a city map. Set up SDL. Find out that SDL doesn't have a stretch blit. Decide
to write my own. First version done, I'm hungry.

12.30am 
Start cooking pancakes.

12.40am 
Get the great idea to keep a log

1:30pm
Damn, cooking these pancakes takes a long time.

2:00pm
Armed with a batch of pancakes, strawberry jam and prototype zoomer, I start working on mouse control.

2:10pm
Mental note: buy dronningholm jam next time.

3:34pm
Mouse control implemented + clippings & unreal dither implemented in zoomer

3:52pm
fixed some bugs in unreal dither reading outside image, added crosshairs & wobble

4:21pm
Working on writer, found that SDL's SDL_MUSTLOCK macro doesn't work.

4:39pm
Blitting from one 8bit surface, changing palette, blitting again doesn't work. Have to make
several copies of font..

5:15pm
Split source base into several source files.

6:13pm
Made prototype sprite stuff

6:32pm
drew AI waypoint map

7:00pm
did tracing code for AI waypoints

7:31pm
posted first screenshot in ludum dare

7:42pm
designed AI data structure; time to cook something.. omelet, ham, potatoes.

8:21pm
Done eating finally, going to mix some drink and then I'll work on AI behaviors.

9:53pm
Pedestrian AI is somewhat finished

10:02pm
Did a simple shooting animation

10:59pm
Drew logo screen

12:05am 
Created the game end screen

----
Sunday
----

1:10am
Did preliminary VIP and bad guy spawns, fixed a bug in clipper with a kludge
(too tired to think, really). Only real thing left before calling this
a game are the VIP and bad guys' AI:s. I'm calling it a day.

9:29am
About 18 hours to go, I manage to drag my self up the bed again. I was wrong
when I whined about the competition hours.. these are just about optimal for
me. 

10:52am
Made different zoom levels more sensible & made it so that camera wobble 
doesn't affect HUD stuff -> now there's a point in zooming extremely
out (find VIPs and threats fast) and extremely in (actually hit someone)

10:59am
Added mouse wheel support (for zoom)

11:03am
Breakfast.

12:19pm
VIP and bad guys AIs done. Tweaked the target and spawn times a bit.

12:38pm
Added different game over reasons, fixed couple bugs. The game is now
playable, about 23 hours after the first lines of code. Time to start
cooking again..

2:23pm
Made enough pasta sauce for a family of 4. Oh dear. Dug up my old and 
amazingly crappy microphone, downloaded goldwave and recorded some sounds.

3:46pm
Added sound. Next up is alpha blended, scaling sprite routines. Joy.

4:05pm
Avoiding the abovementioned task, added some stats to the game over screen.

4:12pm
Took a shower.

5:31pm
Sprites plugged in

5:52pm
Added screen border indicators. Time to try a release build for the first
time.

6:10pm
Mixed some more drink, loaded the laundry machine and put it on, played
around a bit with the target display.

6:58pm
Added target information screens

7:39pm
Hunting a mystery bug.. only occurs in release mode.

7:50pm
Hm. Using release mode + fullscreen crashed the system so totally that I 
lost the contents of the main cpp file at least. I have no idea how
much had happened after my last backup. I at least lost sound and all the
tweaking I did to the game settings. ARGH!

8:09pm
Since the game didn't crash anymore, I just have to hope that the crash
was caused by the audio system. Oh dear. Which I'll now start to recode.

8:35pm
Audio re-implemented

8:43pm
Managed to get it to crash in fullscreen again, but not in windowed mode,
and SDL happily just kills off the application without letting me debug
if we're in fullscreen. Joy.

9:08pm
Made the fullscren mode also a software surface, doesn't seem to crash
anymore. Probably a rare overflow somewhere. =(

9:14pm
Changed sprite drawing so that it'll draw slightly outside the screen -
clipping is performed per pixel but who cares, we have CPU power..
The clipping was done earlier, so that's not the cause of the bug.

9:21pm
ARGH! crashed again.

9:32pm
Managed to crash in windowed mode: AIs were trying to use wrong waypoints
in some obscure case.

9:52pm
Ran physics loop at 10x speed for several minutes in fullscreen release mode
and nothing crashed, so I'd guess the AI stuff is fixed now. I'm fairly
confident (fingers crossed) that that was it. Next up: packaging &
documentation.

10:15pm
Finished, now I'll just zip it up and toss it away..
    
-- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< -- 8< --
