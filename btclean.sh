#!/bin/sh
#
# Script to clean a bootstrap build of Open Watcom tools.

if [ -f setvars ]; then
    source setvars
else
    source setvars.sh
fi
if [ ! -f $OWBINDIR/builder ]; then
    echo Cannot find builder - did you run boot.sh?
else
    cd src
    builder bootclean
    rm -rf make/$OBJDIR
    rm -f $OWBINDIR/wmake $OWBINDIR/builder
fi
