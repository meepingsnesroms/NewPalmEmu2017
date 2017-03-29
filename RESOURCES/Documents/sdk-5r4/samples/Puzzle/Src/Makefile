###############################################################################
#
# Copyright (c) 2000 Palm, Inc. or its subsidiaries.
# All rights reserved.
#
# File: Makefile
#
# Release: 
#
###############################################################################

CC = m68k-palmos-gcc
CFLAGS = -O2 -Wall

# This Makefile would be a little tidier if we put .rcp files in the same
# directory as the source code.
R = ../Rsc

Puzzle.prc: PuzzleApp tver0001.bin tFRM03e8.bin Talt03e9.bin
	build-prc Puzzle.prc "Puzzle" puzl PuzzleApp *.bin

PuzzleApp: PuzzleApp.o
PuzzleApp.o: PuzzleApp.c PuzzleRsc.h

tver0001.bin: $(R)/PuzzleApp.rcp \
              $(R)/PuzzleLarge.pbitm $(R)/PuzzleSmall.pbitm \
	      PuzzleRsc.h
	pilrc -I $(R) $(R)/PuzzleApp.rcp

tFRM03e8.bin: $(R)/PuzzleMain.rcp PuzzleRsc.h
	pilrc -I $(R) $(R)/PuzzleMain.rcp

Talt03e9.bin: $(R)/PuzzleMisc.rcp PuzzleRsc.h
	pilrc -I $(R) $(R)/PuzzleMisc.rcp

clean:
	rm -f PuzzleApp *.o *.bin
