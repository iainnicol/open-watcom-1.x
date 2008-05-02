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
    <CCCMD> library/msdos.086/mc/clibc.lib                  <RELROOT>/lib286/dos/clibc.lib
    <CCCMD> library/msdos.086/mh/clibh.lib                  <RELROOT>/lib286/dos/clibh.lib
    <CCCMD> library/msdos.086/ml/clibl.lib                  <RELROOT>/lib286/dos/clibl.lib
    <CCCMD> library/msdos.086/ml_ov/clibl.lib               <RELROOT>/lib286/dos/clibol.lib
    <CCCMD> library/msdos.086/mm/clibm.lib                  <RELROOT>/lib286/dos/clibm.lib
    <CCCMD> library/msdos.086/mm_ov/clibm.lib               <RELROOT>/lib286/dos/clibom.lib
    <CCCMD> library/msdos.086/ms/clibs.lib                  <RELROOT>/lib286/dos/clibs.lib
    <CCCMD> startup/library/msdos.086/ml/d16msels.obj       <RELROOT>/lib286/dos/d16msels.obj
    <CCCMD> startup/library/msdos.086/ml/dos16m.obj         <RELROOT>/lib286/dos/dos16m.obj
    <CCCMD> startup/library/msdos.086/ms/binmode.obj        <RELROOT>/lib286/dos/binmode.obj
    <CCCMD> startup/library/msdos.086/ms/commode.obj        <RELROOT>/lib286/dos/commode.obj
    <CCCMD> startup/library/msdos.086/ms/cstrtiny.obj       <RELROOT>/lib286/dos/cstart_t.obj

    <CCCMD> library/msdos.386/ms_r/clib3r.lib               <RELROOT>/lib386/dos/clib3r.lib
    <CCCMD> library/msdos.386/ms_s/clib3s.lib               <RELROOT>/lib386/dos/clib3s.lib
    <CCCMD> startup/library/msdos.386/ms_r/binmode.obj      <RELROOT>/lib386/dos/binmode.obj
    <CCCMD> startup/library/msdos.386/ms_r/commode.obj      <RELROOT>/lib386/dos/commode.obj
    <CCCMD> startup/library/msdos.386/ms_r/cstrtx32.obj     <RELROOT>/lib386/dos/cstrtx3r.obj
    <CCCMD> startup/library/msdos.386/ms_r/dllstart.obj     <RELROOT>/lib386/dos/dllstrtr.obj
    <CCCMD> startup/library/msdos.386/ms_s/cstrtx32.obj     <RELROOT>/lib386/dos/cstrtx3s.obj
    <CCCMD> startup/library/msdos.386/ms_s/adsstart.obj     <RELROOT>/lib386/dos/adsstart.obj
    <CCCMD> startup/library/msdos.386/ms_s/adiestrt.obj     <RELROOT>/lib386/dos/adiestrt.obj
    <CCCMD> startup/library/msdos.386/ms_s/adifstrt.obj     <RELROOT>/lib386/dos/adifstrt.obj
    <CCCMD> startup/library/msdos.386/ms_s/dllstart.obj     <RELROOT>/lib386/dos/dllstrts.obj

    <CCCMD> library/msdos.286/mc/clibc.lib                  <RELROOT>/lib286/os2/dospmc.lib
    <CCCMD> library/msdos.286/mh/clibh.lib                  <RELROOT>/lib286/os2/dospmh.lib
    <CCCMD> library/msdos.286/ml/clibl.lib                  <RELROOT>/lib286/os2/dospml.lib
    <CCCMD> library/msdos.286/mm/clibm.lib                  <RELROOT>/lib286/os2/dospmm.lib
    <CCCMD> library/msdos.286/ms/clibs.lib                  <RELROOT>/lib286/os2/dospms.lib

    <CCCMD> library/os2.286/mc/clibc.lib                    <RELROOT>/lib286/os2/clibc.lib
    <CCCMD> library/os2.286/mh/clibh.lib                    <RELROOT>/lib286/os2/clibh.lib
    <CCCMD> library/os2.286/ml/clibl.lib                    <RELROOT>/lib286/os2/clibl.lib
    <CCCMD> library/os2.286/ml_dll/clibl.lib                <RELROOT>/lib286/os2/clibdll.lib
    <CCCMD> library/os2.286/ml_mt/clibl.lib                 <RELROOT>/lib286/os2/clibmtl.lib
    <CCCMD> library/os2.286/mm/clibm.lib                    <RELROOT>/lib286/os2/clibm.lib
    <CCCMD> library/os2.286/ms/clibs.lib                    <RELROOT>/lib286/os2/clibs.lib
    <CCCMD> startup/library/os2.286/ms/binmode.obj          <RELROOT>/lib286/os2/binmode.obj
    <CCCMD> startup/library/os2.286/ms/commode.obj          <RELROOT>/lib286/os2/commode.obj

    <CCCMD> library/os2.386/mf_r/clib3r.lib                 <RELROOT>/lib386/os2/clib3r.lib
    <CCCMD> library/os2.386/mf_s/clib3s.lib                 <RELROOT>/lib386/os2/clib3s.lib
    <CCCMD> library/os2.386/mf_rd/clib3r.lib                <RELROOT>/lib386/os2/clib3rd.lib
    <CCCMD> startup/library/os2.386/mf_r/binmode.obj        <RELROOT>/lib386/os2/binmode.obj
    <CCCMD> startup/library/os2.386/mf_r/commode.obj        <RELROOT>/lib386/os2/commode.obj

    <CCCMD> library/windows.086/mc/clibc.lib                <RELROOT>/lib286/win/clibc.lib
    <CCCMD> library/windows.086/ml/clibl.lib                <RELROOT>/lib286/win/clibl.lib
    <CCCMD> library/windows.086/mm/clibm.lib                <RELROOT>/lib286/win/clibm.lib
    <CCCMD> library/windows.086/ms/clibs.lib                <RELROOT>/lib286/win/clibs.lib
    <CCCMD> startup/library/windows.086/ml/libentry.obj     <RELROOT>/lib286/win/libentry.obj
    <CCCMD> startup/library/windows.086/ms/binmode.obj      <RELROOT>/lib286/win/binmode.obj
    <CCCMD> startup/library/windows.086/ms/commode.obj      <RELROOT>/lib286/win/commode.obj

    <CCCMD> library/windows.386/mf_r/clib3r.lib             <RELROOT>/lib386/win/clib3r.lib
    <CCCMD> library/windows.386/mf_s/clib3s.lib             <RELROOT>/lib386/win/clib3s.lib
    <CCCMD> startup/library/windows.386/mf_r/binmode.obj    <RELROOT>/lib386/win/binmode.obj
    <CCCMD> startup/library/windows.386/mf_r/commode.obj    <RELROOT>/lib386/win/commode.obj

    <CCCMD> library/winnt.386/mf_r/clib3r.lib               <RELROOT>/lib386/nt/clib3r.lib
    <CCCMD> library/winnt.386/mf_s/clib3s.lib               <RELROOT>/lib386/nt/clib3s.lib
    <CCCMD> library/winnt.386/mf_rd/clib3r.lib              <RELROOT>/lib386/nt/clib3rd.lib

    <CCCMD> startup/library/winnt.386/mf_r/binmode.obj      <RELROOT>/lib386/nt/binmode.obj
    <CCCMD> startup/library/winnt.386/mf_r/commode.obj      <RELROOT>/lib386/nt/commode.obj

    <CCCMD> library/linux.386/mf_r/clib3r.lib               <RELROOT>/lib386/linux/clib3r.lib
    <CCCMD> library/linux.386/mf_s/clib3s.lib               <RELROOT>/lib386/linux/clib3s.lib

    <CCCMD> startup/library/linux.386/mf_r/commode.obj      <RELROOT>/lib386/linux/commode.obj

    <CCCMD> library/nw_libc.386/ms_s/clib3s.lib             <RELROOT>/lib386/netware/libc3s.lib
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
    <CCCMD> startup/library/nw_clib.386/ms_s/binmode.obj    <RELROOT>/lib386/netware/binmode.obj
    <CCCMD> startup/library/nw_clib.386/ms_sd/binmode.obj   <RELROOT>/lib386/netware/binmoded.obj

    <CCCMD> library/qnx.286/mc/clibc.lib                    <RELROOT>/lib286/qnx/clibc.lib
    <CCCMD> library/qnx.286/mh/clibh.lib                    <RELROOT>/lib286/qnx/clibh.lib
    <CCCMD> library/qnx.286/ml/clibl.lib                    <RELROOT>/lib286/qnx/clibl.lib
    <CCCMD> library/qnx.286/ml_sh/clibl.lib                 <RELROOT>/lib286/qnx/clibshar.lib
    <CCCMD> library/qnx.286/mm/clibm.lib                    <RELROOT>/lib286/qnx/clibm.lib
    <CCCMD> library/qnx.286/ms/clibs.lib                    <RELROOT>/lib286/qnx/clibs.lib
    <CCCMD> startup/library/qnx.286/ms/commode.obj          <RELROOT>/lib286/qnx/commode.obj

    <CCCMD> library/qnx.386/ms_r/clib3r.lib                 <RELROOT>/lib386/qnx/clib3r.lib
    <CCCMD> library/qnx.386/ms_s/clib3s.lib                 <RELROOT>/lib386/qnx/clib3s.lib
    <CCCMD> startup/library/qnx.386/ms_r/commode.obj        <RELROOT>/lib386/qnx/commode.obj

# Libraries not built by default

    <CCCMD> library/winnt.axp/_s/clib.lib                   <RELROOT>/libaxp/nt/clib.lib
    <CCCMD> startup/library/winnt.axp/_s/binmode.obj        <RELROOT>/libaxp/nt/binmode.obj
    <CCCMD> startup/library/winnt.axp/_s/commode.obj        <RELROOT>/libaxp/nt/commode.obj

    <CCCMD> library/osi.386/ms_r/clib3r.lib                 <RELROOT>/lib386/osi/clib3r.lib

    <CCCMD> library/linux.mps/_s/clib.lib                   <RELROOT>/libmps/linux/clib.lib

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
