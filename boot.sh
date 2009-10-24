#!/bin/sh
#
# Script to build a subset of the Open Watcom tools
# using the host platform's native C/C++ compiler tools.
#
# Expects POSIX tools.

if [ -f setvars ]; then
    source setvars
    echo setvars found
else
    source setvars.sh
    echo setvars not found, running setvars.sh
fi
mkdir src/make/$OBJDIR
cd src/make/$OBJDIR
make -f ../posmake
mkdir ../../builder/$OBJDIR
cd ../../builder/$OBJDIR
wmake -h -f ../bootmake builder.exe
cd ../..
builder boot && builder build
