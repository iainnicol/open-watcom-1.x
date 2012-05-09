# omftools Builder Control file
# =============================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> boot ]
#=================
    mkdir <PROJDIR>/<OWOBJDIR>
    cdsay <PROJDIR>/<OWOBJDIR>
    wmake -h -f ../bootmake
    <CPCMD> objchg.exe  <OWBINDIR>/objchg<CMDEXT>
    <CPCMD> objfind.exe <OWBINDIR>/objfind<CMDEXT>
    <CPCMD> objlist.exe <OWBINDIR>/objlist<CMDEXT>
    <CPCMD> objxdef.exe <OWBINDIR>/objxdef<CMDEXT>
    <CPCMD> objxref.exe <OWBINDIR>/objxref<CMDEXT>
				    
[ BLOCK <1> rel ]
#================
    cdsay <PROJDIR>

[ BLOCK <1> bootclean ]
#======================
    echo rm -r -f <PROJDIR>/<OWOBJDIR>
    rm -r -f <PROJDIR>/<OWOBJDIR>
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
