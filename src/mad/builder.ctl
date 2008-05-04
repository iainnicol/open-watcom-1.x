# MAD Builder Control file
# ========================

set PROJDIR=<CWD>
set PROJNAME=mad

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
# x86
    <CCCMD> <PROJDIR>/x86/dos386/madx86.mad   <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/axp/dos386/madaxp.mad   <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/ppc/dos386/madppc.mad   <RELROOT>/binw/

    <CCCMD> <PROJDIR>/x86/wini86/madx86.dll   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/axp/wini86/madaxp.dll   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/ppc/wini86/madppc.dll   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/mips/wini86/madmips.dll <RELROOT>/binw/

#    <CCCMD> <PROJDIR>/x86/os2i86/madx86.dll   <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/axp/os2i86/madaxp.dll   <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/ppc/os2i86/madppc.dll   <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/x86/os2386/madx86.d32   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/x86/os2386/madx86.sym   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/axp/os2386/madaxp.d32   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/axp/os2386/madaxp.sym   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/ppc/os2386/madppc.d32   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/ppc/os2386/madppc.sym   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/mips/os2386/madmips.d32 <RELROOT>/binp/
    <CCCMD> <PROJDIR>/mips/os2386/madmips.sym <RELROOT>/binp/

    <CCCMD> <PROJDIR>/x86/nt386/madx86.dll    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/x86/nt386/madx86.sym    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/axp/nt386/madaxp.dll    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/axp/nt386/madaxp.sym    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/ppc/nt386/madppc.dll    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/ppc/nt386/madppc.sym    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/mips/nt386/madmips.dll  <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/mips/nt386/madmips.sym  <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/x86/ntaxp/madx86.dll    <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/axp/ntaxp/madaxp.dll    <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/ppc/ntaxp/madppc.dll    <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/mips/ntaxp/madmips.dll  <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/x86/qnx386/madx86.mad   <RELROOT>/qnx/watcom/wd/
#    <CCCMD> <PROJDIR>/axp/qnx386/madaxp.mad   <RELROOT>/qnx/watcom/wd/
#    <CCCMD> <PROJDIR>/ppc/qnx386/madppc.mad   <RELROOT>/qnx/watcom/wd/

    <CCCMD> <PROJDIR>/x86/linux386/madx86.mad    <RELROOT>/binl/
    <CCCMD> <PROJDIR>/x86/linux386/madx86.sym    <RELROOT>/binl/
    <CCCMD> <PROJDIR>/axp/linux386/madaxp.mad    <RELROOT>/binl/
    <CCCMD> <PROJDIR>/axp/linux386/madaxp.sym    <RELROOT>/binl/
    <CCCMD> <PROJDIR>/ppc/linux386/madppc.mad    <RELROOT>/binl/
    <CCCMD> <PROJDIR>/ppc/linux386/madppc.sym    <RELROOT>/binl/
    <CCCMD> <PROJDIR>/mips/linux386/madmips.mad  <RELROOT>/binl/
    <CCCMD> <PROJDIR>/mips/linux386/madmips.sym  <RELROOT>/binl/

[ BLOCK . . ]
#============
cdsay <PROJDIR>
