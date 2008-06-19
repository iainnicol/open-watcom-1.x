# w32api Builder Control file
# ===========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel ]
#======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h

[ BLOCK <1> rel cprel]
#=====================
    <CPCMD> nt/*.h                        <RELROOT>/h/nt/
    <CPCMD> nt/GL/*.h                     <RELROOT>/h/nt/GL/
    <CPCMD> nt/ddk/*.h                    <RELROOT>/h/nt/ddk/
    <CPCMD> nt/directx/*.h                <RELROOT>/h/nt/directx/

    <CPCMD> nt386/*.lib                   <RELROOT>/lib386/nt/
    <CPCMD> nt386/ddk/*.lib               <RELROOT>/lib386/nt/ddk/
    <CPCMD> nt386/directx/*.lib           <RELROOT>/lib386/nt/directx/

#    <CPCMD> ntaxp/*.lib                   <RELROOT>/libaxp/nt/

[ BLOCK <1> clean ]
#==================
    pmake -d all <2> <3> <4> <5> <6> <7> <8> <9> -h clean

[ BLOCK . . ]
#============
cdsay <PROJDIR>
