# Copyright (C) 2006 International Business Machines and others.
# All Rights Reserved.
# This file is distributed under the Common Public License.

## $Id$

AUTOMAKE_OPTIONS = foreign

########################################################################
#                          Subdirectories                              #
########################################################################

SUBDIRS = src

# We don't want to compile the test subdirectory, unless the test target is
# specified.  But we need to list it as subdirectory to make sure that it is
# included in the tarball

if ALWAYS_FALSE
  SUBDIRS += test/BAC
endif

########################################################################
#             Additional files to be included in tarball               #
########################################################################

# Here we need include all files that are not mentioned in other Makefiles

EXTRA_DIST =
EXTRA_DIST += doc/flow-lpfathom.fig
EXTRA_DIST += doc/man.pdf
EXTRA_DIST += doc/man.tex
EXTRA_DIST += doc/man-getting-started.tex
EXTRA_DIST += doc/sample.tex
EXTRA_DIST += doc/flow2.eps
EXTRA_DIST += doc/flow2.fig
EXTRA_DIST += doc/flow3.eps
EXTRA_DIST += doc/flow3.fig
EXTRA_DIST += doc/flow4.eps
EXTRA_DIST += doc/flow4.fig
EXTRA_DIST += doc/biblio.bib
EXTRA_DIST += doc/biblio.tex
EXTRA_DIST += doc/flow-init.eps
EXTRA_DIST += doc/flow-init.fig
EXTRA_DIST += doc/flow-steady.fig
EXTRA_DIST += doc/man-cg.tex
EXTRA_DIST += doc/man.ps
EXTRA_DIST += doc/man-mcp.tex
EXTRA_DIST += doc/man-lp.tex
EXTRA_DIST += doc/man-param.tex
EXTRA_DIST += doc/man-mkc.tex
EXTRA_DIST += doc/bcp.eps
EXTRA_DIST += doc/man-tm.tex
EXTRA_DIST += doc/flow-lploop.eps
EXTRA_DIST += doc/flow-lploop.fig
EXTRA_DIST += doc/flow.eps
EXTRA_DIST += doc/flow.fig
EXTRA_DIST += doc/man-intro.tex
EXTRA_DIST += doc/man-develop.tex

########################################################################
#                           Extra Targets                              #
########################################################################

TESTS = BAC
EXAMPLES = BAC

test: all
	for t in $(TESTS); do \
		(cd test/$$t; $(MAKE) test); \
	done

unitTest: test

clean-local:
	for t in $(TESTS); do \
		(if test -r test/$$t/Makefile; then cd test/$$t; $(MAKE) clean; fi); \
	done
	for t in $(EXAMPLES); do \
		for f in `find examples/$$t -name "*.o"`; do \
			rm -f $$f; \
		done; \
	done

distclean-local:
	for t in $(TESTS); do \
		(if test -r test/$$t/Makefile; then cd test/$$t; $(MAKE) distclean; fi); \
		(if test -r test/$$t/testfiles.txt; then cd test/$$t; rm `cat testfiles.txt`; fi); \
	done

.PHONY: test unitTest

########################################################################
#                  Installation of the addlibs file                    #
########################################################################

pkgconfiglibdir = $(libdir)/pkgconfig
pkgconfiglib_DATA = bcp.pc

addlibsdir = $(DESTDIR)$(datadir)/coin/doc/Bcp

install-data-hook:
	@$(mkdir_p) "$(addlibsdir)"
if COIN_HAS_PKGCONFIG
	PKG_CONFIG_PATH=@COIN_PKG_CONFIG_PATH@ \
	$(PKG_CONFIG) --libs bcp > $(addlibsdir)/bcp_addlibs.txt
else
if COIN_CXX_IS_CL
	echo "-libpath:`$(CYGPATH_W) @abs_lib_dir@` libBcp.lib @BCPLIB_LIBS_INSTALLED@" > $(addlibsdir)/bcp_addlibs.txt
else
	echo -L@abs_lib_dir@ -lBcp @BCPLIB_LIBS_INSTALLED@ > $(addlibsdir)/bcp_addlibs.txt
endif
endif

uninstall-hook:
	rm -f $(addlibsdir)/bcp_addlibs.txt

########################################################################
#                         Maintainer Stuff                             #
########################################################################

# Files that are generated and should be cleaned with make distclean
DISTCLEANFILES =

include BuildTools/Makemain.inc
