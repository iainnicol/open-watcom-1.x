# wlink Builder Control file
# ==========================

set PROJDIR=<CWD>
set PROJNAME=wlink

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> boot ]
#=================
    <CPCMD> <OBJDIR>/wl.exe <OWBINDIR>/wlink<CMDEXT>

[ BLOCK <1> bootclean ]
#======================
    echo rm -f <OWBINDIR>/wlink<CMDEXT>
    rm -f <OWBINDIR>/wlink<CMDEXT>

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/dos386/wl.exe                     <RELROOT>/binw/wlink.exe
    <CCCMD> <PROJDIR>/dos386/wl.sym                     <RELROOT>/binw/wlink.sym
    <CCCMD> <PROJDIR>/ms2wlink/dosi86/ms2wlink.exe      <RELROOT>/binw/ms2wlink.exe
    <CCCMD> <PROJDIR>/fcenable/dosi86/fcenable.exe      <RELROOT>/binw/fcenable.exe
    <CCCMD> <PROJDIR>/exe2bin/dosi86/exe2bin.exe        <RELROOT>/binw/exe2bin.exe
    <CCCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binw/wlsystem.lnk
    <CCCMD> <PROJDIR>/wlbin.lnk                         <RELROOT>/binw/wlink.lnk
    <CCCMD> <PROJDIR>/ovlldr/dosi86/wovl.lib            <RELROOT>/lib286/dos/wovl.lib
#    <CCCMD> <PROJDIR>/ovlldr/dosi86/wmovl.lib           <RELROOT>/lib286/dos/wmovl.lib

    <CCCMD> <PROJDIR>/os2386.dll/wl.exe                 <RELROOT>/binp/wlink.exe
    <CCCMD> <PROJDIR>/os2386.dll/wl.sym                 <RELROOT>/binp/wlink.sym
    <CCCMD> <PROJDIR>/os2386.dll/wld.dll                <RELROOT>/binp/dll/wlinkd.dll
    <CCCMD> <PROJDIR>/os2386.dll/wld.sym                <RELROOT>/binp/dll/wlinkd.sym
    <CCCMD> <PROJDIR>/ms2wlink/os2i86/ms2wlink.exe      <RELROOT>/binp/ms2wlink.exe
    <CCCMD> <PROJDIR>/fcenable/os2i86/fcenable.exe      <RELROOT>/binp/fcenable.exe
    <CCCMD> <PROJDIR>/exe2bin/os2386/exe2bin.exe        <RELROOT>/binp/exe2bin.exe
    <CCCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binw/wlsystem.lnk
    <CCCMD> <PROJDIR>/wlbinp.lnk                        <RELROOT>/binp/wlink.lnk

    <CCCMD> <PROJDIR>/nt386.dll/wl.exe                  <RELROOT>/binnt/wlink.exe
    <CCCMD> <PROJDIR>/nt386.dll/wl.sym                  <RELROOT>/binnt/wlink.sym
    <CCCMD> <PROJDIR>/nt386.dll/wld.dll                 <RELROOT>/binnt/wlinkd.dll
    <CCCMD> <PROJDIR>/nt386.dll/wld.sym                 <RELROOT>/binnt/wlinkd.sym
    <CCCMD> <PROJDIR>/nt386.rtd/wl.exe                  <RELROOT>/binnt/rtdll/wlink.exe
    <CCCMD> <PROJDIR>/nt386.rtd/wld.dll                 <RELROOT>/binnt/rtdll/wlinkd.dll
    <CCCMD> <PROJDIR>/ms2wlink/nt386/ms2wlink.exe       <RELROOT>/binnt/ms2wlink.exe
    <CCCMD> <PROJDIR>/fcenable/nt386/fcenable.exe       <RELROOT>/binnt/fcenable.exe
    <CCCMD> <PROJDIR>/exe2bin/nt386/exe2bin.exe         <RELROOT>/binnt/exe2bin.exe
    <CCCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binw/wlsystem.lnk
    <CCCMD> <PROJDIR>/wlbinnt.lnk                       <RELROOT>/binnt/wlink.lnk

    <CCCMD> <PROJDIR>/linux386/wl.exe                   <RELROOT>/binl/wlink
    <CCCMD> <PROJDIR>/linux386/wl.sym                   <RELROOT>/binl/wlink.sym
    <CCCMD> <PROJDIR>/ms2wlink/linux386/ms2wlink.exe    <RELROOT>/binl/ms2wlink
    <CCCMD> <PROJDIR>/fcenable/linux386/fcenable.exe    <RELROOT>/binl/fcenable
    <CCCMD> <PROJDIR>/exe2bin/linux386/exe2bin.exe      <RELROOT>/binl/exe2bin
    <CCCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binl/wlsystem.lnk
    <CCCMD> <PROJDIR>/wlbinl.lnk                        <RELROOT>/binl/wlink.lnk

    <CCCMD> <PROJDIR>/ntaxp.dll/wl.exe                  <RELROOT>/axpnt/wlink.exe
    <CCCMD> <PROJDIR>/ntaxp.dll/wld.dll                 <RELROOT>/axpnt/wlinkd.dll
    <CCCMD> <PROJDIR>/exe2bin/ntaxp/exe2bin.exe         <RELROOT>/axpnt/exe2bin.exe
    <CCCMD> <PROJDIR>/wlsystem.lnk                      <RELROOT>/binw/wlsystem.lnk
    <CCCMD> <PROJDIR>/wlaxpnt.lnk                       <RELROOT>/axpnt/wlink.lnk

    <CCCMD> <PROJDIR>/qnx386/wl.exe                     <RELROOT>/qnx/binq/wlink
    <CCCMD> <PROJDIR>/qnx386/wl.sym                     <RELROOT>/qnx/sym/wlink.sym
    <CCCMD> <PROJDIR>/qnx.lnk                           <RELROOT>/qnx/etc/wlink.lnk

[ BLOCK . . ]
#============
cdsay <PROJDIR>
