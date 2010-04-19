# graphlib Builder Control file
# =============================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> boot ]
#=================
    echo **** Building the <PROJNAME> bootstrap
    mkdir <PROJDIR>/fixtools/<OBJDIR>
    cdsay <PROJDIR>/fixtools/<OBJDIR>
    wmake -h -f ../bootmake
    <CPCMD> objchg.exe  <OWBINDIR>/objchg<CMDEXT>
    <CPCMD> objfind.exe <OWBINDIR>/objfind<CMDEXT>
    <CPCMD> objlist.exe <OWBINDIR>/objlist<CMDEXT>
    <CPCMD> objxdef.exe <OWBINDIR>/objxdef<CMDEXT>
    <CPCMD> objxref.exe <OWBINDIR>/objxref<CMDEXT>

[ BLOCK <1> build rel ]
#======================
    cd <PROJDIR>/pgchart
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel ]
#================
    cdsay <PROJDIR>

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/fix/dosi86/graph.lib    <RELROOT>/lib286/dos/graph.lib
    <CCCMD> <PROJDIR>/fix/dos386/graph.lib    <RELROOT>/lib386/dos/graph.lib
    <CCCMD> <PROJDIR>/fix/os2i86/seginit.obj  <RELROOT>/lib286/os2/graphp.obj
    <CCCMD> <PROJDIR>/fix/qnxi86/graph.lib    <RELROOT>/lib286/qnx/graph.lib
    <CCCMD> <PROJDIR>/fix/qnx386/graph3r.lib  <RELROOT>/lib386/qnx/graph3r.lib
    <CCCMD> <PROJDIR>/fix/qnx386/graph3s.lib  <RELROOT>/lib386/qnx/graph3s.lib

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cd <PROJDIR>/pgchart
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cdsay <PROJDIR>/fix
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK <1> bootclean ]
#======================
    echo **** BOOTCLEAN rule
    echo rm -r -f <PROJDIR>/fixtools/<OBJDIR>
    rm -r -f <PROJDIR>/fixtools/<OBJDIR>
    echo rm -f <OWBINDIR>/objchg<CMDEXT>
    rm -f <OWBINDIR>/objchg<CMDEXT>
    echo rm -f <OWBINDIR>/objfind<CMDEXT>
    rm -f <OWBINDIR>/objfind<CMDEXT>
    echo rm -f <OWBINDIR>/objlist<CMDEXT>
    rm -f <OWBINDIR>/objlist<CMDEXT>
    echo rm -f <OWBINDIR>/objxdef<CMDEXT>
    rm -f <OWBINDIR>/objxdef<CMDEXT>
    echo rm -f <OWBINDIR>/objxref<CMDEXT>
    rm -f <OWBINDIR>/objxref<CMDEXT>

[ BLOCK . . ]
#============

cdsay <PROJDIR>
