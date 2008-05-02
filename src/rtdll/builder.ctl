# Builder Control file
# ==========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel ]
#======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel ]
#================
    cdsay <PROJDIR>

[ BLOCK <1> rel cprel acprel ]
#=============================
    <CCCMD> clib/os2.386/mf_r/clb*.lib          <RELROOT>/lib386/os2/
    <CCCMD> clib/os2.386/mf_r/clb*.dll          <RELROOT>/binp/dll/
    <CCCMD> clib/os2.386/mf_r/clb*.sym          <RELROOT>/binp/dll/
    <CCCMD> clib/os2.386/mf_rd/clb*.lib         <RELROOT>/lib386/os2/
    <CCCMD> clib/os2.386/mf_rd/clb*.dll         <RELROOT>/binp/dll/
    <CCCMD> clib/os2.386/mf_s/clb*.lib          <RELROOT>/lib386/os2/
    <CCCMD> clib/os2.386/mf_s/clb*.dll          <RELROOT>/binp/dll/
    <CCCMD> clib/os2.386/mf_s/clb*.sym          <RELROOT>/binp/dll/

    <CCCMD> mathlib/os2.386/mf_r/mt*.lib        <RELROOT>/lib386/os2/
    <CCCMD> mathlib/os2.386/mf_r/mt*.dll        <RELROOT>/binp/dll/
    <CCCMD> mathlib/os2.386/mf_r/mt*.sym        <RELROOT>/binp/dll/
    <CCCMD> mathlib/os2.386/mf_rd/mt*.lib       <RELROOT>/lib386/os2/
    <CCCMD> mathlib/os2.386/mf_rd/mt*.dll       <RELROOT>/binp/dll/
    <CCCMD> mathlib/os2.386/mf_s/mt*.lib        <RELROOT>/lib386/os2/
    <CCCMD> mathlib/os2.386/mf_s/mt*.dll        <RELROOT>/binp/dll/
    <CCCMD> mathlib/os2.386/mf_s/mt*.sym        <RELROOT>/binp/dll/

    <CCCMD> mathlib/os2.387/mf_r/mt*.lib        <RELROOT>/lib386/os2/
    <CCCMD> mathlib/os2.387/mf_r/mt*.dll        <RELROOT>/binp/dll/
    <CCCMD> mathlib/os2.387/mf_r/mt*.sym        <RELROOT>/binp/dll/
    <CCCMD> mathlib/os2.387/mf_rd/mt*.lib       <RELROOT>/lib386/os2/
    <CCCMD> mathlib/os2.387/mf_rd/mt*.dll       <RELROOT>/binp/dll/
    <CCCMD> mathlib/os2.387/mf_s/mt*.lib        <RELROOT>/lib386/os2/
    <CCCMD> mathlib/os2.387/mf_s/mt*.dll        <RELROOT>/binp/dll/
    <CCCMD> mathlib/os2.387/mf_s/mt*.sym        <RELROOT>/binp/dll/

    <CCCMD> cpplib/os2.386/mf_r/plb*.lib        <RELROOT>/lib386/os2/
    <CCCMD> cpplib/os2.386/mf_r/plbrdll.lib     <RELROOT>/lib386/os2/plbrdllx.lib
    <CCCMD> cpplib/os2.386/mf_r/plb*.dll        <RELROOT>/binp/dll/
    <CCCMD> cpplib/os2.386/mf_r/plb*.sym        <RELROOT>/binp/dll/
    <CCCMD> cpplib/os2.386/mf_rd/plb*.lib       <RELROOT>/lib386/os2/
    <CCCMD> cpplib/os2.386/mf_rd/plbrdlld.lib   <RELROOT>/lib386/os2/plbrdlxd.lib
    <CCCMD> cpplib/os2.386/mf_rd/plb*.dll       <RELROOT>/binp/dll/
    <CCCMD> cpplib/os2.386/mf_s/plb*.lib        <RELROOT>/lib386/os2/
    <CCCMD> cpplib/os2.386/mf_s/plbsdll.lib     <RELROOT>/lib386/os2/plbsdllx.lib
    <CCCMD> cpplib/os2.386/mf_s/plb*.dll        <RELROOT>/binp/dll/
    <CCCMD> cpplib/os2.386/mf_s/plb*.sym        <RELROOT>/binp/dll/

#    <CCCMD> wrtlib/os2.386/mf_r/wr*.lib         <RELROOT>/lib386/os2/
#    <CCCMD> wrtlib/os2.386/mf_r/wr*.dll         <RELROOT>/binp/dll/
#    <CCCMD> wrtlib/os2.386/mf_r/wr*.sym         <RELROOT>/binp/dll/
#    <CCCMD> wrtlib/os2.386/mf_s/wr*.lib         <RELROOT>/lib386/os2/
#    <CCCMD> wrtlib/os2.386/mf_s/wr*.dll         <RELROOT>/binp/dll/
#    <CCCMD> wrtlib/os2.386/mf_s/wr*.sym         <RELROOT>/binp/dll/

    <CCCMD> clib/winnt.386/mf_r/clb*.lib        <RELROOT>/lib386/nt/
    <CCCMD> clib/winnt.386/mf_r/clb*.dll        <RELROOT>/binnt/
    <CCCMD> clib/winnt.386/mf_r/clb*.sym        <RELROOT>/binnt/
    <CCCMD> clib/winnt.386/mf_rd/clb*.lib       <RELROOT>/lib386/nt/
    <CCCMD> clib/winnt.386/mf_rd/clb*.dll       <RELROOT>/binnt/
    <CCCMD> clib/winnt.386/mf_rp/clb*.lib       <RELROOT>/lib386/nt/
    <CCCMD> clib/winnt.386/mf_rp/clb*.dll       <RELROOT>/binnt/
    <CCCMD> clib/winnt.386/mf_s/clb*.lib        <RELROOT>/lib386/nt/
    <CCCMD> clib/winnt.386/mf_s/clb*.dll        <RELROOT>/binnt/
    <CCCMD> clib/winnt.386/mf_s/clb*.sym        <RELROOT>/binnt/

    <CCCMD> mathlib/winnt.386/mf_r/mt*.lib      <RELROOT>/lib386/nt/
    <CCCMD> mathlib/winnt.386/mf_r/mt*.dll      <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.386/mf_r/mt*.sym      <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.386/mf_rd/mt*.lib     <RELROOT>/lib386/nt/
    <CCCMD> mathlib/winnt.386/mf_rd/mt*.dll     <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.386/mf_rp/mt*.lib     <RELROOT>/lib386/nt/
    <CCCMD> mathlib/winnt.386/mf_rp/mt*.dll     <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.386/mf_s/mt*.lib      <RELROOT>/lib386/nt/
    <CCCMD> mathlib/winnt.386/mf_s/mt*.dll      <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.386/mf_s/mt*.sym      <RELROOT>/binnt/

    <CCCMD> mathlib/winnt.387/mf_r/mt*.lib      <RELROOT>/lib386/nt/
    <CCCMD> mathlib/winnt.387/mf_r/mt*.dll      <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.387/mf_r/mt*.sym      <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.387/mf_rd/mt*.lib     <RELROOT>/lib386/nt/
    <CCCMD> mathlib/winnt.387/mf_rd/mt*.dll     <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.387/mf_rp/mt*.lib     <RELROOT>/lib386/nt/
    <CCCMD> mathlib/winnt.387/mf_rp/mt*.dll     <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.387/mf_s/mt*.lib      <RELROOT>/lib386/nt/
    <CCCMD> mathlib/winnt.387/mf_s/mt*.dll      <RELROOT>/binnt/
    <CCCMD> mathlib/winnt.387/mf_s/mt*.sym      <RELROOT>/binnt/

    <CCCMD> cpplib/winnt.386/mf_r/plb*.lib      <RELROOT>/lib386/nt/
    <CCCMD> cpplib/winnt.386/mf_r/plbrdll.lib   <RELROOT>/lib386/nt/plbrdllx.lib
    <CCCMD> cpplib/winnt.386/mf_r/plb*.dll      <RELROOT>/binnt/
    <CCCMD> cpplib/winnt.386/mf_r/plb*.sym      <RELROOT>/binnt/
    <CCCMD> cpplib/winnt.386/mf_rd/plb*.lib     <RELROOT>/lib386/nt/
    <CCCMD> cpplib/winnt.386/mf_rd/plbrdlld.lib <RELROOT>/lib386/nt/plbrdlxd.lib
    <CCCMD> cpplib/winnt.386/mf_rd/plb*.dll     <RELROOT>/binnt/
    <CCCMD> cpplib/winnt.386/mf_rp/plb*.lib     <RELROOT>/lib386/nt/
    <CCCMD> cpplib/winnt.386/mf_rp/plb*.dll     <RELROOT>/binnt/
    <CCCMD> cpplib/winnt.386/mf_s/plb*.lib      <RELROOT>/lib386/nt/
    <CCCMD> cpplib/winnt.386/mf_s/plbsdll.lib   <RELROOT>/lib386/nt/plbsdllx.lib
    <CCCMD> cpplib/winnt.386/mf_s/plb*.dll      <RELROOT>/binnt/
    <CCCMD> cpplib/winnt.386/mf_s/plb*.sym      <RELROOT>/binnt/

#    <CCCMD> wrtlib/winnt.386/mf_r/wr*.lib       <RELROOT>/lib386/nt/
#    <CCCMD> wrtlib/winnt.386/mf_r/wr*.dll       <RELROOT>/binnt/
#    <CCCMD> wrtlib/winnt.386/mf_r/wr*.sym       <RELROOT>/binnt/
#    <CCCMD> wrtlib/winnt.386/mf_s/wr*.lib       <RELROOT>/lib386/nt/
#    <CCCMD> wrtlib/winnt.386/mf_s/wr*.dll       <RELROOT>/binnt/
#    <CCCMD> wrtlib/winnt.386/mf_s/wr*.sym       <RELROOT>/binnt/

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK . . ]
#============
cdsay <PROJDIR>
