# wcl Builder Control file
# ========================

set PROJDIR=<CWD>
set PROJNAME=owcc

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> boot build rel ]
#===========================
    echo wsplice -k Pspecs <OWROOT>/src/link/specs.sp specs.owc
    wsplice -k Pspecs <OWROOT>/src/link/specs.sp specs.owc

[ BLOCK <1> build rel ]
#======================
    pmake -d buildwcl <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> boot ]
#=================
    <CPCMD> specs.owc <OWBINDIR>/specs.owc

[ BLOCK . . ]
#============

[ INCLUDE <OWROOT>/build/deftool.ctl ]


[ BLOCK <1> rel cprel acprel ]
#=============================

    <CPCMD> <PROJDIR>/specs.owc                 <RELROOT>/binw/specs.owc
    
    <CCCMD> <PROJDIR>/dosi86.i86/wcl.exe        <RELROOT>/binw/wcl.exe
    <CCCMD> <PROJDIR>/dosi86.386/wcl386.exe     <RELROOT>/binw/wcl386.exe
    <CCCMD> <PROJDIR>/dosi86.axp/wclaxp.exe     <RELROOT>/binw/wclaxp.exe
    <CCCMD> <PROJDIR>/dosi86.ppc/wclppc.exe     <RELROOT>/binw/wclppc.exe

    <CCCMD> <PROJDIR>/nt386/owcc.exe            <RELROOT>/binnt/owcc.exe
    <CCCMD> <PROJDIR>/nt386.i86/wcl.exe         <RELROOT>/binnt/wcl.exe
    <CCCMD> <PROJDIR>/nt386.386/wcl386.exe      <RELROOT>/binnt/wcl386.exe
    <CCCMD> <PROJDIR>/nt386.axp/wclaxp.exe      <RELROOT>/binnt/wclaxp.exe
    <CCCMD> <PROJDIR>/nt386.ppc/wclppc.exe      <RELROOT>/binnt/wclppc.exe
    <CCCMD> <PROJDIR>/nt386.mps/wclmps.exe      <RELROOT>/binnt/wclmps.exe

    <CCCMD> <PROJDIR>/os2386/owcc.exe           <RELROOT>/binp/owcc.exe
    <CCCMD> <PROJDIR>/os2386.i86/wcl.exe        <RELROOT>/binp/wcl.exe
    <CCCMD> <PROJDIR>/os2386.386/wcl386.exe     <RELROOT>/binp/wcl386.exe
    <CCCMD> <PROJDIR>/os2386.axp/wclaxp.exe     <RELROOT>/binp/wclaxp.exe
    <CCCMD> <PROJDIR>/os2386.ppc/wclppc.exe     <RELROOT>/binp/wclppc.exe
    <CCCMD> <PROJDIR>/os2386.mps/wclmps.exe     <RELROOT>/binp/wclmps.exe

    <CCCMD> <PROJDIR>/linux386/owcc.exe         <RELROOT>/binl/owcc
    <CCCMD> <PROJDIR>/linux386.i86/wcl.exe      <RELROOT>/binl/wcl
    <CCCMD> <PROJDIR>/linux386.i86/wcl.sym      <RELROOT>/binl/wcl.sym
    <CCCMD> <PROJDIR>/linux386.386/wcl386.exe   <RELROOT>/binl/wcl386
    <CCCMD> <PROJDIR>/linux386.386/wcl386.sym   <RELROOT>/binl/wcl386.sym
    <CCCMD> <PROJDIR>/linux386.axp/wclaxp.exe   <RELROOT>/binl/wclaxp
    <CCCMD> <PROJDIR>/linux386.mps/wclmps.exe   <RELROOT>/binl/wclmps

    <CCCMD> <PROJDIR>/ntaxp.i86/wcl.exe         <RELROOT>/axpnt/wcl.exe
    <CCCMD> <PROJDIR>/ntaxp.386/wcl386.exe      <RELROOT>/axpnt/wcl386.exe
    <CCCMD> <PROJDIR>/ntaxp.axp/wclaxp.exe      <RELROOT>/axpnt/wclaxp.exe

[ BLOCK <1> clean ]
#==================
    rm  -f specs.owc
    pmake -d buildwcl <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK <1> bootclean ]
#======================
    echo rm -f <OWBINDIR>/specs.owc
    rm -f <OWBINDIR>/specs.owc

[ BLOCK . . ]
#============
cdsay <PROJDIR>
