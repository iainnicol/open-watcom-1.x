#!/bin/sh
#
# Script to build a subset of the Open Watcom tools
# using the host platform's native C/C++ compiler tools.

if [ -f setvars ]; then
    . setvars
else
    . setvars.sh
fi
cd src/make
$MAKE -f gnumake
mkdir ../builder/$OBJDIR
cd ../builder/$OBJDIR
wmake -h -f ../bootmake builder.exe
cd ../..
builder -s boot 
