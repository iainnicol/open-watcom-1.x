# DIP Builder Control file
# ========================

set PROJDIR=<CWD>
set PROJNAME=dip

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
        <CCCMD> <PROJDIR>/dwarf/dos386/dwarf.dip         <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/dwarf/dos386/dwarf.sym         <RELROOT>/binw/dwarf.dsy
        <CCCMD> <PROJDIR>/codeview/dos386/codeview.dip   <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/codeview/dos386/codeview.sym   <RELROOT>/binw/codeview.dsy
        <CCCMD> <PROJDIR>/export/dos386/export.dip       <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/export/dos386/export.sym       <RELROOT>/binw/export.dsy
        <CCCMD> <PROJDIR>/watcom/dos386/watcom.dip       <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/watcom/dos386/watcom.sym       <RELROOT>/binw/watcom.dsy
        <CCCMD> <PROJDIR>/mapsym/dos386/mapsym.dip       <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/mapsym/dos386/mapsym.sym       <RELROOT>/binw/watcom.dsy

        <CCCMD> <PROJDIR>/dwarf/wini86/dwarf.dll         <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/dwarf/wini86/dwarf.sym         <RELROOT>/binw/
        <CCCMD> <PROJDIR>/codeview/wini86/codeview.dll   <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/codeview/wini86/codeview.sym   <RELROOT>/binw/
        <CCCMD> <PROJDIR>/export/wini86/export.dll       <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/export/wini86/export.sym       <RELROOT>/binw/
        <CCCMD> <PROJDIR>/watcom/wini86/watcom.dll       <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/watcom/wini86/watcom.sym       <RELROOT>/binw/
        <CCCMD> <PROJDIR>/mapsym/wini86/mapsym.dll       <RELROOT>/binw/
#        <CCCMD> <PROJDIR>/mapsym/wini86/mapsym.sym       <RELROOT>/binw/

#        <CCCMD> <PROJDIR>/dwarf/os2i86/dwarf.dll         <RELROOT>/binp/dll/
#        <CCCMD> <PROJDIR>/dwarf/os2i86/dwarf.sym         <RELROOT>/binp/dll/
#        <CCCMD> <PROJDIR>/codeview/os2i86/codeview.dll   <RELROOT>/binp/dll/
#        <CCCMD> <PROJDIR>/codeview/os2i86/codeview.sym   <RELROOT>/binp/dll/
#        <CCCMD> <PROJDIR>/export/os2i86/export.dll       <RELROOT>/binp/dll/
#        <CCCMD> <PROJDIR>/export/os2i86/export.sym       <RELROOT>/binp/dll/
#        <CCCMD> <PROJDIR>/watcom/os2i86/watcom.dll       <RELROOT>/binp/dll/
#        <CCCMD> <PROJDIR>/watcom/os2i86/watcom.sym       <RELROOT>/binp/dll/
        <CCCMD> <PROJDIR>/dwarf/os2386/dwarf.d32         <RELROOT>/binp/
        <CCCMD> <PROJDIR>/dwarf/os2386/dwarf.sym         <RELROOT>/binp/
        <CCCMD> <PROJDIR>/codeview/os2386/codeview.d32   <RELROOT>/binp/
        <CCCMD> <PROJDIR>/codeview/os2386/codeview.sym   <RELROOT>/binp/
        <CCCMD> <PROJDIR>/export/os2386/export.d32       <RELROOT>/binp/
        <CCCMD> <PROJDIR>/export/os2386/export.sym       <RELROOT>/binp/
        <CCCMD> <PROJDIR>/watcom/os2386/watcom.d32       <RELROOT>/binp/
        <CCCMD> <PROJDIR>/watcom/os2386/watcom.sym       <RELROOT>/binp/
        <CCCMD> <PROJDIR>/mapsym/os2386/mapsym.d32       <RELROOT>/binp/
        <CCCMD> <PROJDIR>/mapsym/os2386/mapsym.sym       <RELROOT>/binp/
        <CCCMD> <PROJDIR>/hllcv/os2386/hllcv.d32         <RELROOT>/binp/
        <CCCMD> <PROJDIR>/hllcv/os2386/hllcv.sym         <RELROOT>/binp/

        <CCCMD> <PROJDIR>/dwarf/nt386/dwarf.dll          <RELROOT>/binnt/
        <CCCMD> <PROJDIR>/dwarf/nt386/dwarf.sym          <RELROOT>/binnt/
        <CCCMD> <PROJDIR>/codeview/nt386/codeview.dll    <RELROOT>/binnt/
        <CCCMD> <PROJDIR>/codeview/nt386/codeview.sym    <RELROOT>/binnt/
        <CCCMD> <PROJDIR>/export/nt386/export.dll        <RELROOT>/binnt/
        <CCCMD> <PROJDIR>/export/nt386/export.sym        <RELROOT>/binnt/
        <CCCMD> <PROJDIR>/watcom/nt386/watcom.dll        <RELROOT>/binnt/
        <CCCMD> <PROJDIR>/watcom/nt386/watcom.sym        <RELROOT>/binnt/
        <CCCMD> <PROJDIR>/mapsym/nt386/mapsym.dll        <RELROOT>/binnt/
        <CCCMD> <PROJDIR>/mapsym/nt386/mapsym.sym        <RELROOT>/binnt/

        <CCCMD> <PROJDIR>/dwarf/linux386/dwarf.dip       <RELROOT>/binl/
        <CCCMD> <PROJDIR>/dwarf/linux386/dwarf.sym       <RELROOT>/binl/
        <CCCMD> <PROJDIR>/watcom/linux386/watcom.dip     <RELROOT>/binl/
        <CCCMD> <PROJDIR>/watcom/linux386/watcom.sym     <RELROOT>/binl/
        <CCCMD> <PROJDIR>/codeview/linux386/codeview.dip <RELROOT>/binl/
        <CCCMD> <PROJDIR>/codeview/linux386/codeview.sym <RELROOT>/binl/
        <CCCMD> <PROJDIR>/export/linux386/export.dip     <RELROOT>/binl/
        <CCCMD> <PROJDIR>/export/linux386/export.sym     <RELROOT>/binl/
        <CCCMD> <PROJDIR>/mapsym/linux386/mapsym.dip     <RELROOT>/binl/
        <CCCMD> <PROJDIR>/mapsym/linux386/mapsym.sym     <RELROOT>/binl/

        <CCCMD> <PROJDIR>/dwarf/ntaxp/dwarf.dll          <RELROOT>/axpnt/
        <CCCMD> <PROJDIR>/dwarf/ntaxp/dwarf.sym          <RELROOT>/axpnt/
        <CCCMD> <PROJDIR>/codeview/ntaxp/codeview.dll    <RELROOT>/axpnt/
        <CCCMD> <PROJDIR>/codeview/ntaxp/codeview.sym    <RELROOT>/axpnt/
        <CCCMD> <PROJDIR>/export/ntaxp/export.dll        <RELROOT>/axpnt/
        <CCCMD> <PROJDIR>/export/ntaxp/export.sym        <RELROOT>/axpnt/
        <CCCMD> <PROJDIR>/watcom/ntaxp/watcom.dll        <RELROOT>/axpnt/
        <CCCMD> <PROJDIR>/watcom/ntaxp/watcom.sym        <RELROOT>/axpnt/
        <CCCMD> <PROJDIR>/mapsym/ntaxp/mapsym.dll        <RELROOT>/axpnt/
        <CCCMD> <PROJDIR>/mapsym/ntaxp/mapsym.sym        <RELROOT>/axpnt/

#        <CCCMD> <PROJDIR>/dwarf/qnx386/dwarf.dip         <RELROOT>/qnx/watcom/wd/
#        <CCCMD> <PROJDIR>/dwarf/qnx386/dwarf.sym         <RELROOT>/qnx/sym/
#        <CCCMD> <PROJDIR>/codeview/qnx386/codeview.dip   <RELROOT>/qnx/watcom/wd/
#        <CCCMD> <PROJDIR>/codeview/qnx386/codeview.sym   <RELROOT>/qnx/sym/
#        <CCCMD> <PROJDIR>/export/qnx386/export.dip       <RELROOT>/qnx/watcom/wd/
#        <CCCMD> <PROJDIR>/export/qnx386/export.sym       <RELROOT>/qnx/sym/
#        <CCCMD> <PROJDIR>/watcom/qnx386/watcom.dip       <RELROOT>/qnx/watcom/wd/
#        <CCCMD> <PROJDIR>/watcom/qnx386/watcom.sym       <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============
cdsay <PROJDIR>
