# Default Builder Control File for libraries
# ==========================================
#
# Build libraries in place, do not copy any files around.

[ BLOCK .<PROJNAME> . ]
    error PROJNAME must be set!

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
    mkdir <PROJDIR>/<BOOTSUBDIR><OBJDIR>
    cdsay <PROJDIR>/<BOOTSUBDIR><OBJDIR>
    wmake -h -f ../bootmake

[ BLOCK <1> bootclean ]
#======================
    echo **** BOOTCLEAN rule
    echo rm -r -f <PROJDIR>/<BOOTSUBDIR><OBJDIR>
    rm -r -f <PROJDIR>/<BOOTSUBDIR><OBJDIR>

[ BLOCK . . ]
#============
    set BOOTSUBDIR=
