# Default Builder Control File for tools
# ======================================
#
# Build a tool and for boot builds, copy it into the binary directory.
# For a boot clean, also remove the tool from the binary directory.
# For normal builds, copying needs to be done from the .ctl file which
# included this one.
# NB: PROJNAME must be the tool's base name.

[ BLOCK .<PROJNAME> . ]
    echo PROJNAME must be set!

[ BLOCK <1> build rel2 ]
#=======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel2 ]
#=================
    cdsay <PROJDIR>

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    
[ BLOCK <1> boot ]
#=================
    echo **** Building the <PROJNAME> bootstrap
    mkdir <PROJDIR>/<OBJDIR>
    cdsay <PROJDIR>/<OBJDIR>
    wmake -h -f ../bootmake
    <CPCMD> <PROJNAME>.exe <OWBINDIR>/<PROJNAME><CMDEXT>

[ BLOCK <1> bootclean ]
#======================
    echo **** BOOTCLEAN rule
    echo rm -r -f <PROJDIR>/<OBJDIR>
    rm -r -f <PROJDIR>/<OBJDIR>
    echo rm -f <OWBINDIR>/<PROJNAME><CMDEXT>
    rm -f <OWBINDIR>/<PROJNAME><CMDEXT>

[ BLOCK . . ]
#============
