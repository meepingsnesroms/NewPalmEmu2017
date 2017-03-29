#
#  Makefile
#
#  T.Harbaum@tu-bs.de - http://www.ibr.cs.tu-bs.de/~harbaum/pilot
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#

APPNAME = ArgonV
ICONTEXT = "Argon V"
APPID = ArgV

SRCS = argonv.c video.c

# Tool locations
CC = m68k-palmos-gcc -palmos3.5
BUILDPRC = build-prc
PILRC = pilrc
OBJRES = m68k-palmos-obj-res

# File names
RESFILE = $(APPNAME).rcp
PRC = ../$(APPNAME).prc
OBJS = $(SRCS:.c=.o)

# Compile options
DEFINES = -DASM -DGAMEPAD
CSFLAGS = -O2 -S $(DEFINES) $(INCLUDES)
# CFLAGS = -O2 -fomit-frame-pointer $(DEFINES) $(INCLUDES)
CFLAGS = -O2 -g $(DEFINES) $(INCLUDES)

# Makefile targets

all: 
	cd graphics; make
	make $(PRC)

.S.o:
	$(CC) $(TARGETFLAGS) -c $<

.c.s:
	$(CC) $(CSFLAGS) $<

sin: sin.c
	gcc -o sin sin.c -lm

csin0000.bin: sin
	./sin > csin0000.bin

one2four: one2four.c
	gcc -o one2four one2four.c

conv0000.bin: one2four
	./one2four > conv0000.bin

$(PRC): code.stamp bin.stamp graphics.h conv0000.bin csin0000.bin levl0000.lev
	ln -sf levl0000.lev levl0000.bin
	ln -sf font0000.fnt font0000.bin
	$(BUILDPRC) $@ $(ICONTEXT) $(APPID) *.grc *.bin

code.stamp: $(APPNAME)
	$(OBJRES) $(APPNAME)
	touch code.stamp

bin.stamp: $(RESFILE)
	$(PILRC) $(RESFILE)
	touch bin.stamp

$(APPNAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $@

clean::
	rm -rf *.[oa] $(APPNAME) *.bin *.stamp *.grc *~
	rm -rf one2four sin
	cd graphics; make clean

dist:	all
	make clean
	rm -f ../../$(APPNAME).zip
	cd ../..; zip -r $(APPNAME).zip argonv

www::
	make dist
	cp ../../$(APPNAME).zip /usr/home/harbaum/WWW/pilot/argonv

disk::
	make dist
	mcopy -o ../../$(APPNAME).zip a:

level::
	cd graphics; make edit_level

install::
	make all
	pilot-xfer -p /dev/palmv -i $(PRC)

xdebug::
	xxgdb -db_name m68k-palmos-gdb ArgonV
