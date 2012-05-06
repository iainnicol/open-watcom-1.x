# Resource Compiler Builder Control file
# ======================================

set PROJDIR=<CWD>
set PROJNAME=wrc

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CPCMD> <PROJDIR>/*.uni                  <RELROOT>/binw/
    <CPCMD> <PROJDIR>/*.uni                  <RELROOT>/binl/

#    <CPCMD> <PROJDIR>/osi386/wrce.exe        <RELROOT>/binw/wrc.exe
    <CCCMD> <PROJDIR>/dos386/wrce.exe        <RELROOT>/binw/wrc.exe
    <CCCMD> <PROJDIR>/os2386/wrce.exe        <RELROOT>/binp/wrc.exe
    <CCCMD> <PROJDIR>/os2386.dll/wrce.dll    <RELROOT>/binp/dll/wrc.dll
    <CCCMD> <PROJDIR>/nt386/wrce.exe         <RELROOT>/binnt/wrc.exe
    <CCCMD> <PROJDIR>/nt386.dll/wrce.dll     <RELROOT>/binnt/wrc.dll
    <CCCMD> <PROJDIR>/nt386rt.dll/wrce.dll   <RELROOT>/binnt/rtdll/wrc.dll
    <CCCMD> <PROJDIR>/ntaxp/wrce.exe         <RELROOT>/axpnt/wrc.exe
    <CCCMD> <PROJDIR>/linux386/wrce.exe      <RELROOT>/binl/wrc
    <CCCMD> <PROJDIR>/linux386/wrce.sym      <RELROOT>/binl/wrc.sym

[ BLOCK <1> boot ]
#=================
    <CPCMD> <PROJDIR>/<OWOBJDIR>/wrce.exe <OWBINDIR>/wrc<CMDEXT>
    <CPCMD> <PROJDIR>/kanji.uni <OWBINDIR>/

[ BLOCK <1> bootclean ]
#======================
    rm -f <OWBINDIR>/wrc<CMDEXT>
    rm -f <OWBINDIR>/kanji.uni

[ BLOCK . . ]
#============
cdsay <PROJDIR>
