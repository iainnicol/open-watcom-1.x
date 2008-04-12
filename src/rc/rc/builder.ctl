# RC Builder Control file
# =======================

set PROJDIR=<CWD>
set PROJNAME=wrc

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

set BOOTCOPY=<CPCMD> wrce.exe <OWBINDIR>/wrc<CMDEXT>
set BOOTCLEAN=rm -f <OWBINDIR>/wrc<CMDEXT>

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel2 cprel2 ]
#========================
  <CPCMD> <PROJDIR>/*.uni                    <RELROOT>/binw/
  <CPCMD> <PROJDIR>/*.uni                    <RELROOT>/binl/

  [ IFDEF (os_osi) <2*> ]
#    <CPCMD> <PROJDIR>/osi386/wrce.exe        <RELROOT>/binw/wrc.exe

  [ IFDEF (os_dos "") <2*> ]
    <CPCMD> <PROJDIR>/dos386/wrce.exe        <RELROOT>/binw/wrc.exe

  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> <PROJDIR>/os2386/wrce.exe        <RELROOT>/binp/wrc.exe
    <CPCMD> <PROJDIR>/os2386.dll/wrce.dll    <RELROOT>/binp/dll/wrc.dll

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> <PROJDIR>/nt386/wrce.exe         <RELROOT>/binnt/wrc.exe
    <CPCMD> <PROJDIR>/nt386.dll/wrce.dll     <RELROOT>/binnt/wrc.dll
    <CPCMD> <PROJDIR>/nt386rt.dll/wrce.dll   <RELROOT>/binnt/rtdll/wrc.dll

  [ IFDEF (cpu_axp) <2*> ]
    <CPCMD> <PROJDIR>/ntaxp/wrce.exe         <RELROOT>/axpnt/wrc.exe

  [ IFDEF (os_linux "") <2*> ]
    <CPCMD> <PROJDIR>/linux386/wrce.exe      <RELROOT>/binl/wrc
    <CPCMD> <PROJDIR>/linux386/wrce.sym      <RELROOT>/binl/wrc.sym

    <CPCMD> wrce.exe <OWBINDIR>/wrc
    <CPCMD> wrce.exe <OWBINDIR>/bwrc
    cdsay <PROJDIR>

[ BLOCK . . ]
#============

cdsay <PROJDIR>
