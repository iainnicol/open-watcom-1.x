# DIP Builder Control file
# ========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
#=======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
  [ IFDEF (os_dos "") <2*> ]
        <CPCMD> <DEVDIR>/dip/dwarf/dos386/dwarf.dip         <RELROOT>/rel2/binw/
#        <CPCMD> <DEVDIR>/dip/dwarf/dos386/dwarf.sym         <RELROOT>/rel2/binw/dwarf.dsy
        <CPCMD> <DEVDIR>/dip/codeview/dos386/codeview.dip   <RELROOT>/rel2/binw/
#        <CPCMD> <DEVDIR>/dip/codeview/dos386/codeview.sym   <RELROOT>/rel2/binw/codeview.dsy
        <CPCMD> <DEVDIR>/dip/export/dos386/export.dip       <RELROOT>/rel2/binw/
#        <CPCMD> <DEVDIR>/dip/export/dos386/export.sym       <RELROOT>/rel2/binw/export.dsy
        <CPCMD> <DEVDIR>/dip/watcom/dos386/watcom.dip       <RELROOT>/rel2/binw/
#        <CPCMD> <DEVDIR>/dip/watcom/dos386/watcom.sym       <RELROOT>/rel2/binw/watcom.dsy

  [ IFDEF (os_win "") <2*> ]
        <CPCMD> <DEVDIR>/dip/dwarf/wini86/dwarf.dll         <RELROOT>/rel2/binw/
#        <CPCMD> <DEVDIR>/dip/dwarf/wini86/dwarf.sym         <RELROOT>/rel2/binw/
        <CPCMD> <DEVDIR>/dip/codeview/wini86/codeview.dll   <RELROOT>/rel2/binw/
#        <CPCMD> <DEVDIR>/dip/codeview/wini86/codeview.sym   <RELROOT>/rel2/binw/
        <CPCMD> <DEVDIR>/dip/export/wini86/export.dll       <RELROOT>/rel2/binw/
#        <CPCMD> <DEVDIR>/dip/export/wini86/export.sym       <RELROOT>/rel2/binw/
        <CPCMD> <DEVDIR>/dip/watcom/wini86/watcom.dll       <RELROOT>/rel2/binw/
#        <CPCMD> <DEVDIR>/dip/watcom/wini86/watcom.sym       <RELROOT>/rel2/binw/

  [ IFDEF (os_os2 "") <2*> ]
#        <CPCMD> <DEVDIR>/dip/dwarf/os2i86/dwarf.dll         <RELROOT>/rel2/binp/dll/
#        <CPCMD> <DEVDIR>/dip/dwarf/os2i86/dwarf.sym         <RELROOT>/rel2/binp/dll/
#        <CPCMD> <DEVDIR>/dip/codeview/os2i86/codeview.dll   <RELROOT>/rel2/binp/dll/
#        <CPCMD> <DEVDIR>/dip/codeview/os2i86/codeview.sym   <RELROOT>/rel2/binp/dll/
#        <CPCMD> <DEVDIR>/dip/export/os2i86/export.dll       <RELROOT>/rel2/binp/dll/
#        <CPCMD> <DEVDIR>/dip/export/os2i86/export.sym       <RELROOT>/rel2/binp/dll/
#        <CPCMD> <DEVDIR>/dip/watcom/os2i86/watcom.dll       <RELROOT>/rel2/binp/dll/
#        <CPCMD> <DEVDIR>/dip/watcom/os2i86/watcom.sym       <RELROOT>/rel2/binp/dll/
        <CPCMD> <DEVDIR>/dip/dwarf/os2386/dwarf.d32         <RELROOT>/rel2/binp/
        <CPCMD> <DEVDIR>/dip/dwarf/os2386/dwarf.sym         <RELROOT>/rel2/binp/
        <CPCMD> <DEVDIR>/dip/codeview/os2386/codeview.d32   <RELROOT>/rel2/binp/
        <CPCMD> <DEVDIR>/dip/codeview/os2386/codeview.sym   <RELROOT>/rel2/binp/
        <CPCMD> <DEVDIR>/dip/export/os2386/export.d32       <RELROOT>/rel2/binp/
        <CPCMD> <DEVDIR>/dip/export/os2386/export.sym       <RELROOT>/rel2/binp/
        <CPCMD> <DEVDIR>/dip/watcom/os2386/watcom.d32       <RELROOT>/rel2/binp/
        <CPCMD> <DEVDIR>/dip/watcom/os2386/watcom.sym       <RELROOT>/rel2/binp/

  [ IFDEF (os_nt "") <2*> ]
        <CPCMD> <DEVDIR>/dip/dwarf/nt386/dwarf.dll          <RELROOT>/rel2/binnt/
        <CPCMD> <DEVDIR>/dip/dwarf/nt386/dwarf.sym          <RELROOT>/rel2/binnt/
        <CPCMD> <DEVDIR>/dip/codeview/nt386/codeview.dll    <RELROOT>/rel2/binnt/
        <CPCMD> <DEVDIR>/dip/codeview/nt386/codeview.sym    <RELROOT>/rel2/binnt/
        <CPCMD> <DEVDIR>/dip/export/nt386/export.dll        <RELROOT>/rel2/binnt/
        <CPCMD> <DEVDIR>/dip/export/nt386/export.sym        <RELROOT>/rel2/binnt/
        <CPCMD> <DEVDIR>/dip/watcom/nt386/watcom.dll        <RELROOT>/rel2/binnt/
        <CPCMD> <DEVDIR>/dip/watcom/nt386/watcom.sym        <RELROOT>/rel2/binnt/

  [ IFDEF (os_linux "") <2*> ]
        <CPCMD> <DEVDIR>/dip/dwarf/linux386/dwarf.dip       <RELROOT>/rel2/binl/
        <CPCMD> <DEVDIR>/dip/dwarf/linux386/dwarf.sym       <RELROOT>/rel2/binl/
        <CPCMD> <DEVDIR>/dip/watcom/linux386/watcom.dip     <RELROOT>/rel2/binl/
        <CPCMD> <DEVDIR>/dip/watcom/linux386/watcom.sym     <RELROOT>/rel2/binl/
        <CPCMD> <DEVDIR>/dip/codeview/linux386/codeview.dip <RELROOT>/rel2/binl/
        <CPCMD> <DEVDIR>/dip/codeview/linux386/codeview.sym <RELROOT>/rel2/binl/
        <CPCMD> <DEVDIR>/dip/export/linux386/export.dip     <RELROOT>/rel2/binl/
        <CPCMD> <DEVDIR>/dip/export/linux386/export.sym     <RELROOT>/rel2/binl/

  [ IFDEF axp <2*> ]
#        <CPCMD> <DEVDIR>/dip/dwarf/ntaxp/dwarf.dll          <RELROOT>/rel2/axpnt/
#        <CPCMD> <DEVDIR>/dip/dwarf/ntaxp/dwarf.sym          <RELROOT>/rel2/axpnt/
#        <CPCMD> <DEVDIR>/dip/codeview/ntaxp/codeview.dll    <RELROOT>/rel2/axpnt/
#        <CPCMD> <DEVDIR>/dip/codeview/ntaxp/codeview.sym    <RELROOT>/rel2/axpnt/
#        <CPCMD> <DEVDIR>/dip/export/ntaxp/export.dll        <RELROOT>/rel2/axpnt/
#        <CPCMD> <DEVDIR>/dip/export/ntaxp/export.sym        <RELROOT>/rel2/axpnt/
#        <CPCMD> <DEVDIR>/dip/watcom/ntaxp/watcom.dll        <RELROOT>/rel2/axpnt/
#        <CPCMD> <DEVDIR>/dip/watcom/ntaxp/watcom.sym        <RELROOT>/rel2/axpnt/

  [ IFDEF os_qnx <2*> ]
#        <CPCMD> <DEVDIR>/dip/dwarf/qnx386/dwarf.dip         <RELROOT>/rel2/qnx/watcom/wd/
#        <CPCMD> <DEVDIR>/dip/dwarf/qnx386/dwarf.sym         <RELROOT>/rel2/qnx/sym/
#        <CPCMD> <DEVDIR>/dip/codeview/qnx386/codeview.dip   <RELROOT>/rel2/qnx/watcom/wd/
#        <CPCMD> <DEVDIR>/dip/codeview/qnx386/codeview.sym   <RELROOT>/rel2/qnx/sym/
#        <CPCMD> <DEVDIR>/dip/export/qnx386/export.dip       <RELROOT>/rel2/qnx/watcom/wd/
#        <CPCMD> <DEVDIR>/dip/export/qnx386/export.sym       <RELROOT>/rel2/qnx/sym/
#        <CPCMD> <DEVDIR>/dip/watcom/qnx386/watcom.dip       <RELROOT>/rel2/qnx/watcom/wd/
#        <CPCMD> <DEVDIR>/dip/watcom/qnx386/watcom.sym       <RELROOT>/rel2/qnx/sym/

[ BLOCK <1> clean ]
#==================
    pmake -d all <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cdsay <PROJDIR>

