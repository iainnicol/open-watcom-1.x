# WRESEDIT Builder Control file
# =============================

set PROJDIR=<CWD>
set PROJNAME=wresedit

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/waccel/wini86/wacc.dll     <RELROOT>/binw/wacc.dll
    <CCCMD> <PROJDIR>/wmenu/wini86/wmenu.dll     <RELROOT>/binw/wmenu.dll
    <CCCMD> <PROJDIR>/wstring/wini86/wstring.dll <RELROOT>/binw/wstring.dll

    <CCCMD> <PROJDIR>/waccel/nt386/wacc.dll      <RELROOT>/binnt/wacc.dll
    <CCCMD> <PROJDIR>/wmenu/nt386/wmenu.dll      <RELROOT>/binnt/wmenu.dll
    <CCCMD> <PROJDIR>/wstring/nt386/wstring.dll  <RELROOT>/binnt/wstring.dll

    <CCCMD> <PROJDIR>/waccel/ntaxp/wacc.dll      <RELROOT>/axpnt/wacc.dll
    <CCCMD> <PROJDIR>/wmenu/ntaxp/wmenu.dll      <RELROOT>/axpnt/wmenu.dll
    <CCCMD> <PROJDIR>/wstring/ntaxp/wstring.dll  <RELROOT>/axpnt/wstring.dll

[ BLOCK . . ]
#============
cdsay <PROJDIR>
