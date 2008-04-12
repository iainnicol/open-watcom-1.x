# wdis Builder Control file
# =========================

set PROJDIR=<CWD>
set PROJNAME=wdis

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <PROJDIR>/dos386/wdis.exe   <RELROOT>/binw/
    <CPCMD> <PROJDIR>/dos386/wdis.sym   <RELROOT>/binw/

  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <PROJDIR>/os2386/wdis.exe   <RELROOT>/binp/
    <CPCMD> <PROJDIR>/os2386/wdis.sym   <RELROOT>/binp/

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <PROJDIR>/nt386/wdis.exe    <RELROOT>/binnt/
    <CPCMD> <PROJDIR>/nt386/wdis.sym    <RELROOT>/binnt/

  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <PROJDIR>/ntaxp/wdis.exe    <RELROOT>/axpnt/
    <CPCMD> <PROJDIR>/ntaxp/wdis.sym    <RELROOT>/axpnt/

  [ IFDEF (os_qnx) <2*> ]
    <CPCMD> <PROJDIR>/qnx386/wdis.exe   <RELROOT>/qnx/binq/wdis
    <CPCMD> <PROJDIR>/qnx386/wdis.sym   <RELROOT>/qnx/sym/

  [ IFDEF (os_linux "") <2*> ]
    <CPCMD> <PROJDIR>/linux386/wdis.exe <RELROOT>/binl/wdis
    <CPCMD> <PROJDIR>/linux386/wdis.sym <RELROOT>/binl/

[ BLOCK . . ]
#============

cdsay <PROJDIR>
