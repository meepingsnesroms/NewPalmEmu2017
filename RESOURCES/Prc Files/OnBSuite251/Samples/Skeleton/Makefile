CONVERT = txt2pdbdoc
FLAGS = 

OBJS = 	skeleton_c.pdb \
	skeleton2_c.pdb

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