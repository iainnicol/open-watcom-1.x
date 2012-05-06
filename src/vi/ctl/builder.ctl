# parsectl Builder Control file
# =============================

set PROJDIR=<CWD>
set PROJNAME=parsectl

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> boot ]
#=================
    <CPCMD> <PROJDIR>/<OWOBJDIR>/parsectl.exe <OWBINDIR>/parsectl<CMDEXT> 
    <CPCMD> <PROJDIR>/<OWOBJDIR>/parsedyn.exe <OWBINDIR>/parsedyn<CMDEXT> 
    
[ BLOCK <1> bootclean ]
#======================
    rm -f <OWBINDIR>/parsectl<CMDEXT> 
    rm -f <OWBINDIR>/parsedyn<CMDEXT> 

[ BLOCK <1> rel cprel ]
#======================
    # Currently not built by default

[ BLOCK . . ]
#============
cdsay <PROJDIR>
