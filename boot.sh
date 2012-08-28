#!/bin/sh
#
# Script to build the Open Watcom tools
# using the host platform's native C/C++ compiler.
#
# Expects POSIX tools.

# Check the environment
if [ -z "$OWROOT" ]; then
    echo "The OWROOT environment variable must be set!"
    exit 1
fi
if [ -z "$OWOBJDIR" ]; then
    echo "The OWOBJDIR environment variable must be set!"
    exit 2
fi
if [ -z "$OWBINDIR" ]; then
    echo "The OWBINDIR environment variable must be set!"
    exit 2
fi

# Basic sanity checks on directories
if [ ! -d $OWROOT/src/make ]; then
    echo "The \$OWROOT/src/make directory does not exist?!"
    exit 10
fi
if [ ! -d $OWROOT/src/builder ]; then
    echo "The \$OWROOT/src/builder directory does not exist?!"
    exit 11
fi
if [ ! -d $OWBINDIR ]; then
    echo "The \$OWBINDIR directory does not exist?!"
    exit 12
fi

# First build 'wmake', unless it already exists
if [ ! -x $OWBINDIR/wmake ]; then
    cd $OWROOT/src/make
    if [ ! -d $OWOBJDIR ]; then mkdir $OWOBJDIR; fi
    cd $OWOBJDIR
    make -f ../posmake
    if [ $? -ne 0 ]; then
        echo "Failed to build wmake!"
        exit 20
    fi
fi

# Build the 'builder' tool
cd $OWROOT/src/builder
if [ ! -d $OWOBJDIR ]; then mkdir $OWOBJDIR; fi
cd $OWOBJDIR
$OWBINDIR/wmake -h -f ../bootmake builder.exe
if [ $? -ne 0 ]; then
    echo "Failed to build builder!"
    exit 30
fi

# Use 'builder' to build bootstrap tools
cd $OWROOT/src
builder boot
RC=$?

if [ $RC -eq 0 ]; then
    builder build
    RC=$?
fi

cd $OWROOT
exit $RC
