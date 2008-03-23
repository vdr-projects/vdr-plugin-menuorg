#
# vdr-menuorg - A plugin for the Linux Video Disk Recorder
#
# $Id$
#

# The official name of this plugin.
# This name will be used in the '-P...' option of VDR to load the plugin.
#
PLUGIN = menuorg

SVNROOT ?= svn+e-tobi://e-tobi.net/menuorg

### The version number of this plugin (taken from the main source file):

VERSION = $(shell grep 'static const char VERSION\[\] =' src/Version.h | \
  awk '{ print $$6 }' | sed -e 's/[";]//g')

### The C++ compiler and options:

CXX      ?= g++
CXXFLAGS ?= -fPIC -O2 -Wall -Woverloaded-virtual

### The directory environment:

DVBDIR = ../../../../DVB
VDRDIR = ../../..
LIBDIR = ../../lib
TMPDIR = /tmp

### Allow user defined options to overwrite defaults:

-include $(VDRDIR)/Make.config

### The version number of VDR's plugin API (taken from VDR's "config.h"):

APIVERSION = $(shell sed -ne '/define APIVERSION/s/^.*"\(.*\)".*$$/\1/p' \
  $(VDRDIR)/config.h)

### The name of the distribution archive:

ARCHIVE = $(PLUGIN)-$(VERSION)
PACKAGE = vdr-$(ARCHIVE)

### Includes, Libs and Defines (add further entries here):

INCLUDES += -I. -I$(VDRDIR)/include -I$(DVBDIR)/include
INCLUDES +=  `pkg-config libxml++-2.6 --cflags`
INCLUDES +=  `pkg-config glibmm-2.4 --cflags`

LIBS +=  `pkg-config libxml++-2.6 --libs`
LIBS +=  `pkg-config glibmm-2.4 --libs`

DEFINES += -D_GNU_SOURCE -DPLUGIN_NAME_I18N='"$(PLUGIN)"'

### The source files (add further files here):

-include sources.mk

### The object files

OBJS := $(addsuffix .o,$(basename ${SRCS}))

### Implicit rules:

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $(DEFINES)  $(INCLUDES) $< -o $@

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $(DEFINES)  $(INCLUDES) $< -o $@

# Dependencies:

MAKEDEP = $(CXX) -MM
BUILD_DEPFILE = .dependencies

$(BUILD_DEPFILE): Makefile
	@$(MAKEDEP) $(DEFINES) $(INCLUDES) $(SRCS) \
	  | sed "s/.*: \([^ ]*\/\).*/\1\0/" > $@

-include $(BUILD_DEPFILE)

### Internationalization (I18N):

PODIR     = po
LOCALEDIR = $(VDRDIR)/locale
I18Npo    = $(wildcard $(PODIR)/*.po)
I18Nmsgs  = $(addprefix $(LOCALEDIR)/, $(addsuffix /LC_MESSAGES/vdr-$(PLUGIN).mo, $(notdir $(foreach file, $(I18Npo), $(basename $(file))))))
I18Npot   = $(PODIR)/$(PLUGIN).pot

%.mo: %.po
	msgfmt -c -o $@ $<

%.po: $(I18Npot)
	msgmerge -U --no-wrap --no-location --backup=none -q $@ $<
	@touch $@

$(I18Npot): $(SRCS) $(SRCS_TESTABLE)
	xgettext -C -cTRANSLATORS --no-wrap --no-location -k -ktr -ktrNOOP --msgid-bugs-address='<vdr@e-tobi.net>' -o $@ $^

$(I18Nmsgs): $(LOCALEDIR)/%/LC_MESSAGES/vdr-$(PLUGIN).mo: $(PODIR)/%.mo
	@mkdir -p $(dir $@)
	mv $< $@

update-po: $(I18Npo)

.PHONY: i18n
i18n: $(I18Nmsgs)

### Targets:

all: libvdr-$(PLUGIN).so i18n

libvdr-$(PLUGIN).so: $(OBJS)
	$(CXX) $(CXXFLAGS) -shared $(OBJS) -L. $(LIBS) -o $@
	@cp $@ $(LIBDIR)/$@.$(APIVERSION)

dist: clean
	@-rm -rf $(TMPDIR)/$(ARCHIVE)
	@mkdir $(TMPDIR)/$(ARCHIVE)
	@cp -a * $(TMPDIR)/$(ARCHIVE)
	tar czf $(PACKAGE).tar.gz -C $(TMPDIR) --exclude debian --exclude CVS \
	  --exclude .svn --exclude tools --exclude .cproject --exclude .project \
	  $(ARCHIVE)
	@-rm -rf $(TMPDIR)/$(ARCHIVE)
	@echo Distribution package created as $(PACKAGE).tar.gz

clean:
	@-rm -f $(BUILD_DEPFILE) *.so* *.tar.gz core* *~
	@-find . -name \*.\o -exec rm -f {} \; 
