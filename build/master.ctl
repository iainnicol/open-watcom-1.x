# Master Languages Builder Control File
# =====================================

# Validate the environment
[ BLOCK .<OWROOT> . ]
#====================
    error OWROOT must be set!

[ BLOCK .<OWOBJDIR> . ]
#======================
    error OWOBJDIR must be set!

[ BLOCK .<BLD_HOST> . ]
====================
    error BLD_HOST not set - use updated builder!

# Set default output directory
[ BLOCK .<RELROOT> . ]
#=====================
    set RELROOT=<OWROOT>/rel

[ BLOCK . . ]
#============

# Default to build.log
set LOGFNAME=build
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
    set LOGFNAME=cprel
    echo **** CPREL rule
    # with 'cprel', we want to force the copy to occur
    set CPCMD=copy
    set CCCMD=ccopy

[ BLOCK <1> build ]
#==================
    set LOGFNAME=build
    echo **** BUILD rule

[ BLOCK <1> rel ]
#================
    set LOGFNAME=build
    echo **** REL rule

[ BLOCK <1> clean ]
#==================
    set LOGFNAME=clean
    echo **** CLEAN rule

[ BLOCK <1> install ]
#====================
    set LOGFNAME=install

[ BLOCK <1> boot ]
#=================
    set LOGFNAME=boot
    echo **** Building the <PROJNAME> bootstrap

[ BLOCK <1> boot1 ]
#==================
    set LOGFNAME=boot1
    echo **** Building the <PROJNAME> bootstrap
    set 1=boot

[ BLOCK <1> boot2 ]
#==================
    set LOGFNAME=boot2
    echo **** Building the <PROJNAME> bootstrap
    set 1=boot

[ BLOCK <1> bootclean ]
#======================
    set LOGFNAME=btclean
    echo **** BOOTCLEAN rule

[ BLOCK <1> pass1 ]
#==================
    set LOGFNAME=pass1
    echo **** REL rule
    set 1=rel

[ BLOCK <1> pass2 ]
#==================
    set LOGFNAME=pass2
    echo **** REL rule
    set 1=rel

[ BLOCK <1> test ]
#==================
    set LOGFNAME=test
    echo **** TEST rule

[ BLOCK <1> testclean ]
#======================
    set LOGFNAME=tstclean
    echo **** TESTCLEAN rule

# Configure extensions: For executables, DOS, OS/2 and Windows use .exe, others
# nothing. For dynamic libraries, DOS, OS/2 and Windows use .dll, UNIX uses .so.

[ BLOCK <BLD_HOST> NT OS2 DOS ]
#==============================
    set CMDEXT=.exe
    set DYLEXT=.dll
    set BWMAKE=<OWBINDIR>\wmake

[ BLOCK <BLD_HOST> UNIX ]
#========================
    set CMDEXT=
    set DYLEXT=.so
    set BWMAKE=<OWBINDIR>/wmake

[ BLOCK . . ]
#============
