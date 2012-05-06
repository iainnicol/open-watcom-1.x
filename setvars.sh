# Do not use directly; copy and modify as appropriate

export P4PORT=perforce.openwatcom.org:3488
export P4USER=YourName
export P4PASSWD=YourPassword
export P4CLIENT=YourClient

export OWROOT=`cd \`dirname -- $0\` && pwd`

# Change this to point to your existing Open Watcom installation 
# if you bootstrap by host native tools then comment it out
export OWBOOTSTRAP=/usr/bin/watcom

# Change this to the PATH required by GhostScript for PDF creation on used host OS (optional)
export OWGHOSTSCRIPTPATH=/usr/bin

# Set this variable to 1 to get debug build
export OW_DEBUG_BUILD=0

# Set this variable to 1 to get default windowing support in clib
export OW_DEFAULT_WINDOWING=0

# Set this variable to 0 to suppress documentation build
export OW_DOC_BUILD=0

# Documentation related variables
# set appropriate variables to point Windows help compilers which you have installed
# export OW_WIN95HC=hcrtf
# export OW_HHC=hhc

# Adjust to match the host platform
export BOOTSTRAP_OS=linux
export BOOTSTRAP_CPU=386

source $OWROOT/cmnvars.sh

cd %OWROOT%

