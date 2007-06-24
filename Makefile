ROOTDIR = $(PWD)

include makefiles/platforms.mk

ZLIBDIR = zlibrary
APPDIRS = fbreader GeometricCalculator SampleApplications/0 SampleApplications/1 SampleApplications/2

all:
	@echo Target all: $(ZLIBDIR) $(APPDIRS)
	@echo ROOTDIR: $(ROOTDIR)
	@echo PWDs: real $(shell pwd) vs variable $(PWD)
	@for dir in $(ZLIBDIR) $(APPDIRS); do \
		echo CHECKING: $$dir; \
		if [ -d $$dir ]; then \
			cd $$dir; \
			if ! $(MAKE); then \
				exit 1; \
			fi; \
			cd $(ROOTDIR); \
		else \
			echo Could not open $$dir; \
		fi; \
	done;

install: all do_install

do_install:
	@for dir in $(ZLIBDIR) $(APPDIRS); do \
		if [ -d $$dir ]; then \
			cd $$dir; make $@; cd $(ROOTDIR); \
		fi; \
	done

packages: all
	@for dir in $(ZLIBDIR) $(APPDIRS); do \
		if [ -d $$dir ]; then \
			cd $$dir; make package; cd $(ROOTDIR); \
		fi; \
	done

clean:
	@for dir in $(ZLIBDIR) $(APPDIRS); do \
		if [ -d $$dir ]; then \
			cd $$dir; make $@; cd $(ROOTDIR); \
		fi; \
	done

distclean: clean
	rm -vf *.tgz *.ipk *.deb *.prc *.exe *.log

archives: clean
