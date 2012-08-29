#!/bin/sh
#
# Script to clean a bootstrap build of Open Watcom tools.

# Run builder (if it exists) to clean out most of the files.
if [ ! -f $OWBINDIR/builder ]; then
    echo Cannot find builder - did you run boot.sh?
else
    cd $OWROOT/src
    builder bootclean
    cd $OWROOT
fi

# Nuke the builder and wmake bootstrap directories
cd $OWROOT/src/builder
rm -rf $OWOBJDIR
cd $OWROOT/src/make
rm -rf $OWOBJDIR
# Remove any log files
cd $OWROOT/src
rm -f *.lo?
# Finally delete the builder and wmake executables
cd $OWROOT
rm -f $OWBINDIR/wmake
rm -f $OWBINDIR/builder


