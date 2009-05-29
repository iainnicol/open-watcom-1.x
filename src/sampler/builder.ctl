# Execution Sampler Builder Control file
# ======================================

set PROJDIR=<CWD>
set PROJNAME=wsample

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dosi86/wsample.exe      <RELROOT>/binw/wsample.exe
    <CCCMD> <PROJDIR>/rsii86/wsamprsi.exe     <RELROOT>/binw/wsamprsi.exe
    <CCCMD> <PROJDIR>/pls386/wsamppls.exp     <RELROOT>/binw/wsamppls.exp
    <CCCMD> <PROJDIR>/wini86/wsamplew.exe     <RELROOT>/binw/wsamplew.exe
#    <CCCMD> <PROJDIR>/os2i86/wsampos2.exe     <RELROOT>/binp/wsampos2.exe
    <CCCMD> <PROJDIR>/os2386/wsmpos22.exe     <RELROOT>/binp/wsample.exe
    <CCCMD> <PROJDIR>/nt386/wsmpnt.exe        <RELROOT>/binnt/wsample.exe
    <CCCMD> <PROJDIR>/linux386/wsample.exe    <RELROOT>/binl/wsample
    <CCCMD> <PROJDIR>/ntaxp/wsmpaxp.exe       <RELROOT>/axpnt/wsample.exe
    <CCCMD> <PROJDIR>/nlm/wsample.nlm         <RELROOT>/nlm/wsample.nlm

[ BLOCK . . ]
#============
cdsay <PROJDIR>
