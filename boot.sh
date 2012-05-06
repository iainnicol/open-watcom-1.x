#!/bin/sh
#
# Script to build the Open Watcom tools
# using the host platform's native C/C++ compiler or OW tools.
#
# Expects POSIX or OW tools.

if [ -n "$OWBOOTSTRAP" ]; then
    export PATH=$OWBOOTSTRAP/binl:$PATH
    export INCLUDE=$OWBOOTSTRAP/lh
    export WATCOM=$OWBOOTSTRAP
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
rc = builder boot 
if [ -n "$OWBOOTSTRAP" ]; then
    export PATH=$OWBINDIR:$OWROOT/build:$OWDEFPATH
    export INCLUDE=$OWDEFINCLUDE
    export WATCOM=$OWDEFWATCOM
fi
if [ $rc eq 0 ]; then
    rc = builder build
fi
cd $OWROOT
return $rc
