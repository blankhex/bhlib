# Determine OS
OS = $(shell uname)
MAKEFILE = gnu

ifeq ($(OS), Darwin)
    MAKEFILE = osx
endif
ifeq ($(OS), windows32)
    MAKEFILE = mingw
endif


# Targets
default:
	$(MAKE) -f Makefile.$(MAKEFILE)

all:
	$(MAKE) -f Makefile.$(MAKEFILE) all

dist:
	$(MAKE) -f Makefile.$(MAKEFILE) dist

clean:
	$(MAKE) -f Makefile.$(MAKEFILE) clean
