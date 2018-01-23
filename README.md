# Introduction
I'm trying to learn QT and C++. In this project i try to write a usable client for Mopidy on my HTPC, using big pictures, images etc. To talk with mopidy itself websocket implementation is used. Since i'm only learning C++ and QT the code will probably be rewritten many times. 

# Building

## Dependencies
* QT5 toolkit (usually called qt5-base or similiar) 
* qmake

## Make
* Download and unpack the source code
* Switch to the main directory in the root of the unpacked sources
* Create a platform specific makefile with: `qmake -makefile MopidyDisplay.pro`
* Compile with: `make`
