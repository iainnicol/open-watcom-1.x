# wasm Builder Control file
# =========================

set PROJDIR=<CWD>
set PROJNAME=wasm

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> dos386/wasm.exe     <RELROOT>/binw/wasm.exe
    <CCCMD> dos386/wasm.sym     <RELROOT>/binw/wasm.sym
    <CCCMD> dosi86/wasm.exe     <RELROOT>/binw/wasmr.exe
    <CCCMD> dosi86/wasm.sym     <RELROOT>/binw/wasmr.sym
    <CCCMD> os2386/wasm.exe     <RELROOT>/binp/wasm.exe
    <CCCMD> os2386/wasm.sym     <RELROOT>/binp/wasm.sym
    <CCCMD> nt386/wasm.exe      <RELROOT>/binnt/wasm.exe
    <CCCMD> nt386/wasm.sym      <RELROOT>/binnt/wasm.sym
    <CCCMD> linux386/wasm.exe   <RELROOT>/binl/wasm
    <CCCMD> linux386/wasm.sym   <RELROOT>/binl/wasm.sym
    <CCCMD> ntaxp/wasm.exe      <RELROOT>/axpnt/wasm.exe
    <CCCMD> ntaxp/wasm.sym      <RELROOT>/axpnt/wasm.sym
    <CCCMD> qnx386/wasm.exe     <RELROOT>/qnx/binq/wasm
    <CCCMD> qnx386/wasm.sym     <RELROOT>/qnx/sym/

[ BLOCK . . ]
#============

cdsay <PROJDIR>
