# Minimal makefile for Sphinx documentation
#

# You can set these variables from the command line.
SPHINXOPTS    =
SPHINXBUILD   = sphinx-build
SOURCEDIR     = source
BUILDDIR      = build

DOXYGENCONF 	= './doxygen/doxygen.conf'

help: 
	@$(SPHINXBUILD) -M help "$(SOURCEDIR)" "$(BUILDDIR)" $(SPHINXOPTS) $(0)

.PHONY: help Makefile

%: Makefile
	$(MAKE) -C doxygen -f Makefile doxygen
	#doxygen $(DOXYGENCONF)
	$(MAKE) -C sphinx -f Makefile $@
	#$(MAKE) -f Makefile html
