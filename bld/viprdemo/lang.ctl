# Viperdemo Builder Control file
# ==============================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>

    cdsay src/os2
    bviper -r drawos2.tgt
    # <CPCMD> <DEVDIR>\plusplus\bin\rpp38610.exe wpp386.exe
    wmake -i -h -f drawos2.mk1 <DEVDIR>/viprdemo/src/os2/box.obj
    wmake -i -h -f drawos2.mk1 <DEVDIR>/viprdemo/src/os2/drawroom.obj
    wmake -i -h -f drawos2.mk1 <DEVDIR>/viprdemo/src/os2/furnitu.obj
    # rm -f wpp386.exe

    cdsay ../win
    bviper -r draw16.tgt
    # <CPCMD> <DEVDIR>\plusplus\bin\rppi8610.exe wpp.exe
    wmake -i -h -f draw16.mk1 <DEVDIR>/viprdemo/src/win/box.obj
    wmake -i -h -f draw16.mk1 <DEVDIR>/viprdemo/src/win/drawroom.obj
    wmake -i -h -f draw16.mk1 <DEVDIR>/viprdemo/src/win/furnitu.obj
    # rm -f wpp.exe

    cdsay ../win386
    bviper -r draw.tgt
    # <CPCMD> <DEVDIR>\plusplus\bin\rpp38610.exe wpp386.exe
    wmake -i -h -f draw.mk1 <DEVDIR>/viprdemo/src/win386/box.obj
    wmake -i -h -f draw.mk1 <DEVDIR>/viprdemo/src/win386/drawroom.obj
    wmake -i -h -f draw.mk1 <DEVDIR>/viprdemo/src/win386/furnitu.obj
    # rm -f wpp386.exe

    cdsay ../win32
    bviper -r draw32.tgt
    # <CPCMD> <DEVDIR>\plusplus\bin\rpp38610.exe wpp386.exe
    wmake -i -h -f draw32.mk1 <DEVDIR>/viprdemo/src/win32/box.obj
    wmake -i -h -f draw32.mk1 <DEVDIR>/viprdemo/src/win32/drawroom.obj
    wmake -i -h -f draw32.mk1 <DEVDIR>/viprdemo/src/win32/furnitu.obj
    # rm -f wpp386.exe
    cd <PROJDIR>

[ BLOCK <1> rel2 cprel2 ]
#========================
    cd src
    <CPCMD> *.* <RELROOT>/rel2/samples/ide/
    <CPCMD> fortran/*.* <RELROOT>/rel2/samples/ide/fortran/
    <CPCMD> fortran/win32/*.* <RELROOT>/rel2/samples/ide/fortran/win32/
    <CPCMD> fortran/os2/*.* <RELROOT>/rel2/samples/ide/fortran/os2/
    <CPCMD> fortran/win/*.* <RELROOT>/rel2/samples/ide/fortran/win/
    <CPCMD> fortran/win386/*.* <RELROOT>/rel2/samples/ide/fortran/win386/
    <CPCMD> win32/*.tgt <RELROOT>/rel2/samples/ide/win32/
    <CPCMD> os2/*.tgt <RELROOT>/rel2/samples/ide/os2/
    <CPCMD> win/*.tgt <RELROOT>/rel2/samples/ide/win/
    <CPCMD> win386/*.tgt <RELROOT>/rel2/samples/ide/win386/
    cd ..
  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> threed/os2/os2_3d.dll <RELROOT>/rel2/samples/ide/
    <CPCMD> threed/os2/os2_3d.dll <RELROOT>/rel2/samples/ide/os2/
    <CPCMD> threed/os2/os2_3d.dll   <RELROOT>/rel2/samples/ide/fortran/
    <CPCMD> threed/os2/os2_3d.dll   <RELROOT>/rel2/samples/ide/fortran/os2/
  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> threed/nt/nt_3d.dll  <RELROOT>/rel2/samples/ide/win32/
    <CPCMD> threed/nt/nt_3d.dll     <RELROOT>/rel2/samples/ide/fortran/win32/
  [ IFDEF (os_win "") <2*> ]
    <CPCMD> threed/win/win_3d.dll <RELROOT>/rel2/samples/ide/win/
    <CPCMD> threed/win/win_3d.dll <RELROOT>/rel2/samples/ide/win386/
    <CPCMD> threed/win/win_3d.dll   <RELROOT>/rel2/samples/ide/fortran/win/
    <CPCMD> threed/win/win_3d.dll   <RELROOT>/rel2/samples/ide/fortran/win386/
  [ ENDIF ]
#    <CPCMD> src/os2/box.obj         <RELROOT>/rel2/samples/ide/fortran/os2/
#    <CPCMD> src/os2/drawroom.obj    <RELROOT>/rel2/samples/ide/fortran/os2/
#    <CPCMD> src/os2/furnitu.obj     <RELROOT>/rel2/samples/ide/fortran/os2/
#    <CPCMD> src/win/box.obj         <RELROOT>/rel2/samples/ide/fortran/win/
#    <CPCMD> src/win/drawroom.obj    <RELROOT>/rel2/samples/ide/fortran/win/
#    <CPCMD> src/win/furnitu.obj     <RELROOT>/rel2/samples/ide/fortran/win/
#    <CPCMD> src/win386/box.obj      <RELROOT>/rel2/samples/ide/fortran/win386/
#    <CPCMD> src/win386/drawroom.obj <RELROOT>/rel2/samples/ide/fortran/win386/
#    <CPCMD> src/win386/furnitu.obj  <RELROOT>/rel2/samples/ide/fortran/win386/
#    <CPCMD> src/win32/box.obj       <RELROOT>/rel2/samples/ide/fortran/win32/
#    <CPCMD> src/win32/drawroom.obj  <RELROOT>/rel2/samples/ide/fortran/win32/
#    <CPCMD> src/win32/furnitu.obj   <RELROOT>/rel2/samples/ide/fortran/win32/
    cd ..

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    wmake -i -h -f clean.mif
