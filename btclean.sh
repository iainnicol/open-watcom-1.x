#!/bin/sh
#
# Script to clean a bootstrap build of Open Watcom tools.

if [ ! -f $OWBINDIR/builder ]; then
    echo Cannot find builder - did you run boot.sh?
else
    cd $OWROOT/src
    builder clean
    builder bootclean
    cd $OWROOT
fi
cd $OWROOT/src/builder
rm -rf $OBJDIR
cd $OWROOT/src/make
rm -rf $OBJDIR
cd $OWROOT
rm -f $OWBINDIR/wmake
rm -f $OWBINDIR/builder

