SUBDIRS = Boxes \
	  CaseHack \
	  HelloWorld \
	  OnBoardTest \
	  Skeleton

.PHONY: all
all: subdirs

.PHONY: subdirs $(SUBDIRS)
subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) $(TARGET) -C $@

.PHONY: clean
clean: TARGET=clean
clean: subdirs
	-rm -f *~

.PHONY: dist-clean
dist-clean: clean
	-rm -rf