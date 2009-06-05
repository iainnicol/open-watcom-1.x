# clib Builder Control file
# =========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel ]
#======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

[ BLOCK <1> rel ]
#================
    cdsay <PROJDIR>

[ BLOCK <1> rel cprel acprel ]
#=============================
    <CCCMD> library/msdos.086/mc/clibc.lib                  <RELROOT>/lib286/dos/
    <CCCMD> library/msdos.086/mh/clibh.lib                  <RELROOT>/lib286/dos/
    <CCCMD> library/msdos.086/ml/clibl.lib                  <RELROOT>/lib286/dos/
    <CCCMD> library/msdos.086/ml_ov/clibol.lib              <RELROOT>/lib286/dos/
    <CCCMD> library/msdos.086/mm/clibm.lib                  <RELROOT>/lib286/dos/
    <CCCMD> library/msdos.086/mm_ov/clibom.lib              <RELROOT>/lib286/dos/
    <CCCMD> library/msdos.086/ms/clibs.lib                  <RELROOT>/lib286/dos/
    <CCCMD> startup/library/msdos.086/ml/d16msels.obj       <RELROOT>/lib286/dos/
    <CCCMD> startup/library/msdos.086/ml/dos16m.obj         <RELROOT>/lib286/dos/
    <CCCMD> startup/library/msdos.086/ms/binmode.obj        <RELROOT>/lib286/dos/
    <CCCMD> startup/library/msdos.086/ms/commode.obj        <RELROOT>/lib286/dos/
    <CCCMD> startup/library/msdos.086/ms/cstrtiny.obj       <RELROOT>/lib286/dos/cstart_t.obj

    <CCCMD> library/msdos.386/ms_r/clib3r.lib               <RELROOT>/lib386/dos/
    <CCCMD> library/msdos.386/ms_s/clib3s.lib               <RELROOT>/lib386/dos/
    <CCCMD> startup/library/msdos.386/ms_r/binmode.obj      <RELROOT>/lib386/dos/
    <CCCMD> startup/library/msdos.386/ms_r/commode.obj      <RELROOT>/lib386/dos/
    <CCCMD> startup/library/msdos.386/ms_r/cstrtx32.obj     <RELROOT>/lib386/dos/cstrtx3r.obj
    <CCCMD> startup/library/msdos.386/ms_r/dllstart.obj     <RELROOT>/lib386/dos/dllstrtr.obj
    <CCCMD> startup/library/msdos.386/ms_s/cstrtx32.obj     <RELROOT>/lib386/dos/cstrtx3s.obj
    <CCCMD> startup/library/msdos.386/ms_s/adsstart.obj     <RELROOT>/lib386/dos/
    <CCCMD> startup/library/msdos.386/ms_s/adiestrt.obj     <RELROOT>/lib386/dos/
    <CCCMD> startup/library/msdos.386/ms_s/adifstrt.obj     <RELROOT>/lib386/dos/
    <CCCMD> startup/library/msdos.386/ms_s/dllstart.obj     <RELROOT>/lib386/dos/dllstrts.obj

    <CCCMD> library/msdos.286/mc/clibc.lib                  <RELROOT>/lib286/os2/dospmc.lib
    <CCCMD> library/msdos.286/mh/clibh.lib                  <RELROOT>/lib286/os2/dospmh.lib
    <CCCMD> library/msdos.286/ml/clibl.lib                  <RELROOT>/lib286/os2/dospml.lib
    <CCCMD> library/msdos.286/mm/clibm.lib                  <RELROOT>/lib286/os2/dospmm.lib
    <CCCMD> library/msdos.286/ms/clibs.lib                  <RELROOT>/lib286/os2/dospms.lib

    <CCCMD> library/os2.286/mc/clibc.lib                    <RELROOT>/lib286/os2/
    <CCCMD> library/os2.286/mh/clibh.lib                    <RELROOT>/lib286/os2/
    <CCCMD> library/os2.286/ml/clibl.lib                    <RELROOT>/lib286/os2/
    <CCCMD> library/os2.286/ml_dll/clibdll.lib              <RELROOT>/lib286/os2/
    <CCCMD> library/os2.286/ml_mt/clibmtl.lib               <RELROOT>/lib286/os2/
    <CCCMD> library/os2.286/mm/clibm.lib                    <RELROOT>/lib286/os2/
    <CCCMD> library/os2.286/ms/clibs.lib                    <RELROOT>/lib286/os2/
    <CCCMD> startup/library/os2.286/ms/binmode.obj          <RELROOT>/lib286/os2/
    <CCCMD> startup/library/os2.286/ms/commode.obj          <RELROOT>/lib286/os2/

    <CCCMD> library/os2.386/mf_r/clib3r.lib                 <RELROOT>/lib386/os2/
    <CCCMD> library/os2.386/mf_s/clib3s.lib                 <RELROOT>/lib386/os2/
    <CCCMD> library/os2.386/mf_rd/clib3rd.lib               <RELROOT>/lib386/os2/
    <CCCMD> startup/library/os2.386/mf_r/binmode.obj        <RELROOT>/lib386/os2/
    <CCCMD> startup/library/os2.386/mf_r/commode.obj        <RELROOT>/lib386/os2/

    <CCCMD> library/windows.086/mc/clibc.lib                <RELROOT>/lib286/win/
    <CCCMD> library/windows.086/ml/clibl.lib                <RELROOT>/lib286/win/
    <CCCMD> library/windows.086/mm/clibm.lib                <RELROOT>/lib286/win/
    <CCCMD> library/windows.086/ms/clibs.lib                <RELROOT>/lib286/win/
    <CCCMD> startup/library/windows.086/ml/libentry.obj     <RELROOT>/lib286/win/
    <CCCMD> startup/library/windows.086/ms/binmode.obj      <RELROOT>/lib286/win/
    <CCCMD> startup/library/windows.086/ms/commode.obj      <RELROOT>/lib286/win/

    <CCCMD> library/windows.386/mf_r/clib3r.lib             <RELROOT>/lib386/win/
    <CCCMD> library/windows.386/mf_s/clib3s.lib             <RELROOT>/lib386/win/
    <CCCMD> startup/library/windows.386/mf_r/binmode.obj    <RELROOT>/lib386/win/
    <CCCMD> startup/library/windows.386/mf_r/commode.obj    <RELROOT>/lib386/win/

    <CCCMD> library/winnt.386/mf_r/clib3r.lib               <RELROOT>/lib386/nt/
    <CCCMD> library/winnt.386/mf_s/clib3s.lib               <RELROOT>/lib386/nt/
    <CCCMD> library/winnt.386/mf_rd/clib3rd.lib             <RELROOT>/lib386/nt/

    <CCCMD> startup/library/winnt.386/mf_r/binmode.obj      <RELROOT>/lib386/nt/
    <CCCMD> startup/library/winnt.386/mf_r/commode.obj      <RELROOT>/lib386/nt/

    <CCCMD> library/linux.386/mf_r/clib3r.lib               <RELROOT>/lib386/linux/
    <CCCMD> library/linux.386/mf_s/clib3s.lib               <RELROOT>/lib386/linux/

    <CCCMD> startup/library/linux.386/mf_r/commode.obj      <RELROOT>/lib386/linux/

    <CCCMD> library/nw_libc.386/ms_s/clib3s.lib             <RELROOT>/lib386/netware/
    <CCCMD> library/nw_libcl.386/ms_s/clib3s.lib            <RELROOT>/lib386/netware/libc3sl.lib
    <CCCMD> library/nw_clib.386/ms_s/clib3s.lib             <RELROOT>/lib386/netware/clib3s.lib
    <CCCMD> library/nw_clibl.386/ms_s/clib3s.lib            <RELROOT>/lib386/netware/clib3sl.lib
    <CCCMD> library/nw_libc.386/ms_sd/clib3s.lib            <RELROOT>/lib386/netware/libc3sd.lib
    <CCCMD> library/nw_libcl.386/ms_sd/clib3s.lib           <RELROOT>/lib386/netware/libc3sld.lib
    <CCCMD> library/nw_clib.386/ms_sd/clib3s.lib            <RELROOT>/lib386/netware/clib3sd.lib
    <CCCMD> library/nw_clibl.386/ms_sd/clib3s.lib           <RELROOT>/lib386/netware/clib3sld.lib
#
# Note binmode applies to both LIBC and CLIB libraries but only needs to be built once from the
# fat CLIB source code.
#
    <CCCMD> startup/library/nw_clib.386/ms_s/binmode.obj    <RELROOT>/lib386/netware/
    <CCCMD> startup/library/nw_clib.386/ms_sd/binmode.obj   <RELROOT>/lib386/netware/binmoded.obj

    <CCCMD> library/qnx.286/mc/clibc.lib                    <RELROOT>/lib286/qnx/
    <CCCMD> library/qnx.286/mh/clibh.lib                    <RELROOT>/lib286/qnx/
    <CCCMD> library/qnx.286/ml/clibl.lib                    <RELROOT>/lib286/qnx/
    <CCCMD> library/qnx.286/ml_sh/clibl.lib                 <RELROOT>/lib286/qnx/clibshar.lib
    <CCCMD> library/qnx.286/mm/clibm.lib                    <RELROOT>/lib286/qnx/
    <CCCMD> library/qnx.286/ms/clibs.lib                    <RELROOT>/lib286/qnx/
    <CCCMD> startup/library/qnx.286/ms/commode.obj          <RELROOT>/lib286/qnx/

    <CCCMD> library/qnx.386/ms_r/clib3r.lib                 <RELROOT>/lib386/qnx/
    <CCCMD> library/qnx.386/ms_s/clib3s.lib                 <RELROOT>/lib386/qnx/
    <CCCMD> startup/library/qnx.386/ms_r/commode.obj        <RELROOT>/lib386/qnx/

# Libraries not built by default

    <CCCMD> library/winnt.axp/_s/clib.lib                   <RELROOT>/libaxp/nt/
    <CCCMD> startup/library/winnt.axp/_s/binmode.obj        <RELROOT>/libaxp/nt/
    <CCCMD> startup/library/winnt.axp/_s/commode.obj        <RELROOT>/libaxp/nt/

    <CCCMD> library/osi.386/ms_r/clib3r.lib                 <RELROOT>/lib386/osi/

    <CCCMD> library/linux.mps/_s/clib.lib                   <RELROOT>/libmps/linux/

[ BLOCK <1> test ]
#=================
    cdsay qa
    pmake -d clibqa -h

[ BLOCK <1> clean ]
#==================
# ALIASGEN_CLEAN takes care of no longer trying to !include the not existing
# file objs.mif in projects clib/alias and mathlib/alias
    set ALIASGEN_CLEAN=1
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK . . ]
#============
cdsay <PROJDIR>
