#
# vdr-menuorg - A plugin for the Linux Video Disk Recorder
# Copyright (C) 2007 Thomas Creutz, Tobias Grimm
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
# $Id:$
#
#

# The official name of this plugin.
# This name will be used in the '-P...' option of VDR to load the plugin.
#
PLUGIN = menuorg

SVNROPOOT ?= svn+e-tobi://e-tobi.net/menuorg

### The version number of this plugin (taken from the main source file):

VERSION = $(shell grep 'static const char VERSION\[\] =' src/version.h | \
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

LIBS +=  `pkg-config libxml++-2.6 --libs`

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
	@$(MAKEDEP) $(DEFINES) $(INCLUDES) $(SRCS) $(SRCS_TESTABLE) \
	  | sed "s/.*: \([^ ]*\/\).*/\1\0/" > $@

$(TESTS_DEPFILE): Makefile $(SRCS_TESTPARTS)
	@$(MAKEDEP) $(DEFINES) $(INCLUDES) $(SRCS_TESTABLE) $(SRCS_TESTONLY) \
          $(SRCS_TESTPARTS) | sed "s/.*: \([^ ]*\/\).*/\1\0/" > $@

-include $(BUILD_DEPFILE)

### Targets:

all: libvdr-$(PLUGIN).so

libvdr-$(PLUGIN).so: $(OBJS)
	$(CXX) $(CXXFLAGS) -shared $(OBJS) -L. $(LIBS) -o $@
	@cp $@ $(LIBDIR)/$@.$(APIVERSION)

dist: clean
	@-rm -rf $(TMPDIR)/$(ARCHIVE)
	@mkdir $(TMPDIR)/$(ARCHIVE)
	@cp -a * $(TMPDIR)/$(ARCHIVE)
	@tar czf $(PACKAGE).tar.gz -C $(TMPDIR) --exclude debian --exclude CVS \
	  --exclude .svn --exclude tools $(ARCHIVE)
	@-rm -rf $(TMPDIR)/$(ARCHIVE)
	@echo Distribution package created as $(PACKAGE).tar.gz
        
release: dist
	@svn cp -m"release $(VERSION)" $(SVNROOT)/trunk $(SVNROOT)/tags/$(VERSION)

clean:
	@-rm -f $(BUILD_DEPFILE) $(TESTS_DEPFILE) *.so* *.tar.gz core* *~
	@-find . -name \*.\o -exec rm -f {} \; 
