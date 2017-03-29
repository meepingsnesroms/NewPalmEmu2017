ARML = PNOLet
CPMD = CPMDemo
BTLT = BtLibTest
BTPICONET = BtPiconet
WHITEBOARD = WhiteBoard
HARD = HardBall
PUZZ = Puzzle
MINE = MineHunt
SUBH = SubHunt
TICT = TicTacToe
MEMO = memo
TODO = todo
SUBDIRS = $(ARML) $(CPMD) $(BTLT) $(HARD) $(PUZZ) $(MINE) $(SUBH) \
	$(BTPICONET) $(WHITEBOARD) $(TICT) \
	$(MEMO) $(TODO)
# Default Target
all:
	for i in $(SUBDIRS) ; do \
	(cd $$i ; make ) ; \
	done
	
	
	
clean:
	rm -f *~
	for i in $(SUBDIRS) ; do \
	( cd $$i ; make clean) ; \
	done
	 
