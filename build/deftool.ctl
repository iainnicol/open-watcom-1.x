# Default Builder Control File for tools
# ======================================
#
# Build a tool and for boot builds, copy it into the binary directory.
# For a boot clean, also remove the tool from the binary directory.
# For normal builds, copying needs to be done from the .ctl file which
# included this one.
# NB: PROJNAME must be the tool's base name.

cdsay <PROJDIR>

[ BLOCK .<PROJNAME> . ]
    error PROJNAME must be set!

[ BLOCK <1> build rel ]
#======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    
[ BLOCK <1> boot ]
#=================
    mkdir <PROJDIR>/<OWOBJDIR>
    cdsay <PROJDIR>/<OWOBJDIR>
    <BWMAKE> -h -f ../bootmake
    <CPCMD> <PROJNAME>.exe <OWBINDIR>/<PROJNAME><CMDEXT>

[ BLOCK <1> bootclean ]
#======================
    echo rm -r -f <PROJDIR>/<OWOBJDIR>
    rm -r -f <PROJDIR>/<OWOBJDIR>
    echo rm -f <OWBINDIR>/<PROJNAME><CMDEXT>
    rm -f <OWBINDIR>/<PROJNAME><CMDEXT>

[ BLOCK . . ]
#============
