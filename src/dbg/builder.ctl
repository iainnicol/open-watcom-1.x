# Debugger Front End Control file
# ===============================

set PROJDIR=<CWD>
set PROJNAME=wd

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dbg/*.dbg               <RELROOT>/binw/
    <CCCMD> <PROJDIR>/ssl/*.prs               <RELROOT>/binw/

    <CCCMD> <PROJDIR>/rfx/dosi86/rfx.exe      <RELROOT>/binw/rfx.exe
    <CCCMD> <PROJDIR>/dsx/dos386/wv.exe       <RELROOT>/binw/wd.exe
    <CCCMD> <PROJDIR>/dsx/dos386/wv.sym       <RELROOT>/binw/wd.sym

    <CCCMD> <PROJDIR>/win/wini86/wv.exe       <RELROOT>/binw/wdc.exe
    <CCCMD> <PROJDIR>/win/wini86/wv.sym       <RELROOT>/binw/wdc.sym
    <CCCMD> <PROJDIR>/win/wini86.gui/wv.exe   <RELROOT>/binw/wdw.exe
    <CCCMD> <PROJDIR>/win/wini86.gui/wv.sym   <RELROOT>/binw/wdw.sym

    <CCCMD> <PROJDIR>/rfx/os2386/rfx.exe      <RELROOT>/binp/rfx.exe
    <CCCMD> <PROJDIR>/os2/os2386/wv.exe       <RELROOT>/binp/wd.exe
    <CCCMD> <PROJDIR>/os2/os2386/wv.sym       <RELROOT>/binp/wd.sym
    <CCCMD> <PROJDIR>/os2/os2386.gui/wv.exe   <RELROOT>/binp/wdw.exe
    <CCCMD> <PROJDIR>/os2/os2386.gui/wv.sym   <RELROOT>/binp/wdw.sym
#   <CCCMD> <PROJDIR>/os2/os2i86/wv.exe       <RELROOT>/binp/wd16.exe
#   <CCCMD> <PROJDIR>/os2/os2i86.gui/wv.exe   <RELROOT>/binp/wdw16.exe

    <CCCMD> <PROJDIR>/win/nt386/wv.exe        <RELROOT>/binnt/wd.exe
    <CCCMD> <PROJDIR>/win/nt386/wv.sym        <RELROOT>/binnt/wd.sym
    <CCCMD> <PROJDIR>/win/nt386.gui/wv.exe    <RELROOT>/binnt/wdw.exe
    <CCCMD> <PROJDIR>/win/nt386.gui/wv.sym    <RELROOT>/binnt/wdw.sym

    <CCCMD> <PROJDIR>/linux/linux386/wv.exe   <RELROOT>/binl/wd
    <CCCMD> <PROJDIR>/linux/linux386/wv.sym   <RELROOT>/binl/wd.sym
    <CCCMD> <PROJDIR>/dbg/*.dbg               <RELROOT>/binl/
    <CCCMD> <PROJDIR>/ssl/*.prs               <RELROOT>/binl/

    <CCCMD> <PROJDIR>/win/ntaxp/wv.exe        <RELROOT>/axpnt/wd.exe
    <CCCMD> <PROJDIR>/win/ntaxp/wv.sym        <RELROOT>/axpnt/wd.sym
    <CCCMD> <PROJDIR>/win/ntaxp.gui/wv.exe    <RELROOT>/axpnt/wdw.exe
    <CCCMD> <PROJDIR>/win/ntaxp.gui/wv.sym    <RELROOT>/axpnt/wdw.sym

    <CCCMD> <PROJDIR>/qnx/qnx386/wv.qnx       <RELROOT>/qnx/binq/wd
    <CCCMD> <PROJDIR>/qnx/qnx386/wv.sym       <RELROOT>/qnx/sym/wd.sym
    <CCCMD> <PROJDIR>/dbg/*.dbg               <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/ssl/*.prs               <RELROOT>/qnx/watcom/wd/

[ BLOCK . . ]
#============
cdsay <PROJDIR>
