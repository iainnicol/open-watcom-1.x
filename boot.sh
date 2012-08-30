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

# On Solaris, support boostrapping with both gcc and Sun Studio
if [ `uname` = "SunOS" ]; then
    unset OW_SUNSTUDIO # In case user switched compilers
    echo "Bootstrapping on Solaris"
    if [ -x /opt/sfw/bin/gcc -o -x /usr/sfw/bin/gcc -o -x /usr/bin/gcc ]; then
            echo "Using GCC compiler"
    else
        # No gcc, look for cc
        if [ -x /usr/bin/cc ]; then
            echo "Using Sun Studio compiler"
            OW_SUNSTUDIO=1
            export OW_SUNSTUDIO
        else
            # No Sun Studio either, bail
            echo "No compiler found!"
            exit 20
        fi
    fi 
fi

# First build 'wmake', unless it already exists
if [ ! -x $OWBINDIR/wmake ]; then
    cd $OWROOT/src/make
    if [ ! -d $OWOBJDIR ]; then mkdir $OWOBJDIR; fi
    cd $OWOBJDIR
    make -f ../posmake
    if [ $? -ne 0 ]; then
        echo "Failed to build wmake!"
        exit 30
    fi
fi

# Build the 'builder' tool
cd $OWROOT/src/builder
if [ ! -d $OWOBJDIR ]; then mkdir $OWOBJDIR; fi
cd $OWOBJDIR
$OWBINDIR/wmake -h -f ../bootmake builder.exe
if [ $? -ne 0 ]; then
    echo "Failed to build builder!"
    exit 31
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
