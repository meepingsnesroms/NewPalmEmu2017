CONVERT = txt2pdbdoc
FLAGS = 

HEADERS=OnBoardHeaderV35.pdb \
	OnBoardHeaderV40.pdb \
	OnBoardHeader.pdb

OTHERS=	OnBoardCompatibility.pdb

.PHONY: all
all: headers others

#Special case for header files: use "OnBoardHeader" as name, don't use filename
OnBoardHead%.pdb : OnBoardHead%.h
	$(CONVERT) $(FLAGS) OnBoardHeader.h $< $@

#General rule
%.pdb: %.h
	$(CONVERT) $(FLAGS) $< $< $@

headers: $(HEADERS)

others: $(OTHERS)

.PHONY: clean
clean:
	-rm -f *~ *.pdb

.PHONY: dist-clean
dist-clean: clean