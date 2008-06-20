# Master Languages Builder Control File
# =====================================

# Validate the environment
[ BLOCK .<OWROOT> . ]
#====================
    error OWROOT must be set!

[ BLOCK .<OBJDIR> . ]
#====================
    error OBJDIR must be set!

[ BLOCK .<BLD_HOST> . ]
====================
    error BLD_HOST not set - use updated builder!

# Set default output directory
[ BLOCK .<RELROOT> . ]
#=====================
    set RELROOT=<OWROOT>/rel

[ BLOCK . . ]
#============

# Default to bld.log
set LOGFNAME=bld
set LOGEXT=log
set CPCMD=acopy
set CCCMD=accopy

# Set up directories
set SRCDIR=<OWROOT>/src

[ BLOCK .<1> . ]
#===============
    # default rule
    set 1=build

[ BLOCK .<1> .. ]
#================
    # default rule
    set 1=build

[ BLOCK <1> cprel ]
#==================
    echo **** CPREL rule
    set LOGFNAME=cprel
    # with 'cprel', we want to force the copy to occur
    set CPCMD=copy
    set CCCMD=ccopy

[ BLOCK <1> build ]
#==================
    echo **** BUILD rule
    set LOGFNAME=bld

[ BLOCK <1> rel ]
#================
    echo **** REL rule
    set LOGFNAME=bld

[ BLOCK <1> clean ]
#==================
    echo **** CLEAN rule
    set LOGFNAME=clean

[ BLOCK <1> install ]
#==================
    set LOGFNAME=install

[ BLOCK <1> boot ]
#==================
    set LOGFNAME=boot

[ BLOCK <1> pass1 ]
#==================
    echo **** REL rule
    set LOGFNAME=pass1
    set 1=rel

[ BLOCK <1> pass2 ]
#==================
    echo **** REL rule
    set LOGFNAME=pass2
    set 1=rel

# Configure executable extension: DOS, OS/2 and Windows use .exe, others nothing

[ BLOCK <BUILD_PLATFORM> nt386 ntaxp os2386 dos386 ]
#===================================================
    set CMDEXT=.exe

[ BLOCK . . ]
