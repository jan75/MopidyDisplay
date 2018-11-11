# Introduction
I'm trying to learn QT and C++. In this project i try to write a usable client for Mopidy on my HTPC, using big pictures, images etc. To talk with mopidy itself websocket implementation is used. Since i'm only learning C++ and QT the code will probably be rewritten many times. 

# Building

## Dependencies
* QT5 toolkit (usually called qt5-base or similiar) 
* QT5 websockets
* qmake

## Make
* Download and unpack the source code
* Switch to the main directory in the root of the unpacked sources
* Create a platform specific makefile with: `qmake -makefile MopidyDisplay.pro`
* Compile with: `make`

## Generating documentation
Documentation is built using Doxygen and Sphinx. First doxygen generates xml files of the annotated classes, then Sphinx (using the "Breathe" plugin) generates documentation using RTF files with the ".. doxygenclass:: <class>" directive (among others). 

I created three makefiles to first generate doxygen, then sphinx docs. Run the makefile in the *doc* folder with the chosen target (e.g. "make html"). 

Requirements: 
* [Sphinx](http://www.sphinx-doc.org/en/master/)
* [Sphinx Read The Docs theme](https://sphinx-rtd-theme.readthedocs.io/en/latest/)
* [Doxygen](http://www.doxygen.org/)
* [Breathe](https://breathe.readthedocs.io/en/latest/)

Append the path where the breathe binary resides to the Sphinx config (*doc/sphinx/source/conf.py*, sys.path.append()). 

## Platforms
Builds tested on Linux (GCC, Clang) and Windows (MinGW)
