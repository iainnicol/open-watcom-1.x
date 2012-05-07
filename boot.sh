#!/bin/sh
#
# Script to build the Open Watcom tools
# using the host platform's native C/C++ compiler or OW tools.
#
# Expects POSIX or OW tools.

if [ -n "$OWBOOTSTRAP" ]; then
    export WATCOM=$OWBOOTSTRAP
    export PATH=$OWBOOTSTRAP_PATH
    export INCLUDE=$OWBOOTSTRAP_INCLUDE
fi
cd $OWROOT/src/make
mkdir $OWOBJDIR
cd $OWOBJDIR
if [ -n "$OWBOOTSTRAP" ]; then
    wmake -h -f ../wmake
else
    make -f ../posmake
fi
cd $OWROOT/src/builder
mkdir $OWOBJDIR
cd $OWOBJDIR
$OWBINDIR/wmake -h -f ../bootmake builder.exe
cd $OWROOT/src
builder boot 
RC=$?
if [ -n "$OWBOOTSTRAP" ]; then
    export WATCOM=$OWDEFWATCOM
    export PATH=$OWBINDIR:$OWROOT/build:$OWDEFPATH
    export INCLUDE=$OWDEFINCLUDE
fi
if [ $RC -eq 0 ]; then
    builder build
    RC=$?
fi
cd $OWROOT
exit $RC
