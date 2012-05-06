#!/bin/sh
#
# *****************************************************************
# cmnvars.sh - common environment variables
# *****************************************************************
# NOTE: All script files to set the environment must call this script
#       file at the end.

# Set the version numbers
export BLD_VER=20
export BLD_VER_STR=2.0

# Save default path information variables
if [ -z "$OWDEFPATH" ]; then
    export OWDEFPATH=$PATH:
    export OWDEFINCLUDE=$INCLUDE
    export OWDEFWATCOM=$WATCOM
fi

# Subdirectory to be used for bootstrapping
export OWOBJDIR=bootstrp

# Subdirectory to be used for bootstrapping binaries
export OWBINDIR=$OWROOT/build/bin

# Set environment variables
export PATH=$OWBINDIR:$OWROOT/build:$OWDEFPATH
export INCLUDE=$OWDEFINCLUDE
export WATCOM=$OWDEFWATCOM

echo Open Watcom build environment
