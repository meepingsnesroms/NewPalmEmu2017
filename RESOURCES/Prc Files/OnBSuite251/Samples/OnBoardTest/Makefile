CONVERT = txt2pdbdoc
FLAGS = 

OBJS = 	OnBoardTest_c.pdb

.PHONY: all
all: $(OBJS)

%_h.pdb: %.h
%_c.pdb: %.c
	$(CONVERT) $(FLAGS) $< $< $@

.PHONY: clean
clean:
	-rm -f *~ *.pdb

.PHONY: dist-clean
dist-clean: clean