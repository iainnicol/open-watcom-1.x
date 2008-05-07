# VIPER Builder Control file
# ==========================

set PROJDIR=<CWD>
set PROJNAME=IDE

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CPCMD> viper.doc            <RELROOT>/ide.doc
    <CPCMD> viper/ide.cfg        <RELROOT>/binw/ide.cfg
    <CPCMD> viper/idedos.cfg     <RELROOT>/binw/idedos.cfg
    <CPCMD> viper/idedos32.cfg   <RELROOT>/binw/idedos32.cfg
    <CPCMD> viper/idewin.cfg     <RELROOT>/binw/idewin.cfg
    <CPCMD> viper/ideos2.cfg     <RELROOT>/binw/ideos2.cfg
    <CPCMD> viper/ideos232.cfg   <RELROOT>/binw/ideos232.cfg
    <CPCMD> viper/idew32.cfg     <RELROOT>/binw/idew32.cfg
    <CPCMD> viper/idew386.cfg    <RELROOT>/binw/idew386.cfg
    <CPCMD> viper/idenlm.cfg     <RELROOT>/binw/idenlm.cfg
    <CPCMD> viper/ideaxp.cfg     <RELROOT>/binw/ideaxp.cfg
    <CPCMD> viper/idelnx.cfg     <RELROOT>/binw/idelnx.cfg

    <CPCMD> viper/ideunix.cfg    <RELROOT>/binl/ide.cfg
    <CPCMD> viper/idedos.cfg     <RELROOT>/binl/idedos.cfg
    <CPCMD> viper/idedos32.cfg   <RELROOT>/binl/idedos32.cfg
    <CPCMD> viper/idewin.cfg     <RELROOT>/binl/idewin.cfg
    <CPCMD> viper/ideos2.cfg     <RELROOT>/binl/ideos2.cfg
    <CPCMD> viper/ideos232.cfg   <RELROOT>/binl/ideos232.cfg
    <CPCMD> viper/idew32.cfg     <RELROOT>/binl/idew32.cfg
    <CPCMD> viper/idew386.cfg    <RELROOT>/binl/idew386.cfg
    <CPCMD> viper/idenlm.cfg     <RELROOT>/binl/idenlm.cfg
    <CPCMD> viper/ideaxp.cfg     <RELROOT>/binl/ideaxp.cfg
    <CPCMD> viper/idelnx.cfg     <RELROOT>/binl/idelnx.cfg

    <CCCMD> viper/wini86/ide.exe <RELROOT>/binw/ide.exe
    <CCCMD> viper/win/idex.cfg   <RELROOT>/binw/idex.cfg
    <CCCMD> viper/win/wsrv.pif   <RELROOT>/binw/wsrv.pif
    <CCCMD> viper/win/wd.pif     <RELROOT>/binw/wd.pif

    <CCCMD> viper/os2386/ide.exe <RELROOT>/binp/ide.exe
    <CCCMD> viper/os2/idex.cfg   <RELROOT>/binp/idex.cfg

    <CCCMD> viper/nt386/ide.exe  <RELROOT>/binnt/ide.exe
    <CCCMD> viper/nt/idex.cfg    <RELROOT>/binnt/idex.cfg

    <CCCMD> viper/ntaxp/ide.exe  <RELROOT>/axpnt/ide.exe
    <CCCMD> viper/axp/idex.cfg   <RELROOT>/axpnt/idex.cfg

[ BLOCK . . ]
#============
cdsay <PROJDIR>
