# cfe Builder Control file
# ==========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/bat/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel2 ]
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h
    cd <PROJDIR>

[ BLOCK <1> rel2 cprel2 acprel2 ]
#================================
#dos stuff
    <CPCMD> dos386/wcc386c.exe <RELROOT>/rel2/binw/wcc386.exe
    <CPCMD> dos386/wcc386c.sym <RELROOT>/rel2/binw/wcc386.sym
    <CPCMD> dos386/wcc38601.int <RELROOT>/rel2/binw/wcc38601.int
    <CPCMD> dosi86/wcci86c.exe <RELROOT>/rel2/binw/wcc.exe
    <CPCMD> dosi86/wcci86c.sym <RELROOT>/rel2/binw/wcc.sym
    <CPCMD> dosi86/wcci8601.int <RELROOT>/rel2/binw/wcci8601.int
#    <CPCMD> dos386/wccaxpe.exe <RELROOT>/rel2/binnt/wccaxp.exe
#    <CPCMD> dosi86/wccaxpe.exe <RELROOT>/rel2/binnt/wccaxp.exe
#    <CPCMD> osippc/wccppcc.exe <RELROOT>/rel2/binw/wccppc.exe
#    <CPCMD> osiaxp/wccaxpc.exe <RELROOT>/rel2/binw/wccaxp.exe

#osi stuff
#    <CPCMD> osi386/wcc386c.exe <RELROOT>/rel2/binw/wcc386.exe
#    <CPCMD> osi386/wcc386c.sym <RELROOT>/rel2/binw/wcc386.sym
#    <CPCMD> osi386/wcc38601.int <RELROOT>/rel2/binw/wcc38601.int
#    <CPCMD> osii86/wcci86c.exe <RELROOT>/rel2/binw/wcc.exe
#    <CPCMD> osii86/wcci86c.sym <RELROOT>/rel2/binw/wcc.sym
#    <CPCMD> osii86/wcci8601.int <RELROOT>/rel2/binw/wcci8601.int

#AXP target
    <CPCMD> ntaxp/wccaxpe.exe <RELROOT>/rel2/binnt/wccaxp.exe
    <CPCMD> ntaxp/wccaxpe.sym <RELROOT>/rel2/binnt/wccaxp.sym
    <CPCMD> ntaxp/wccdaxpe.dll <RELROOT>/rel2/binnt/wccdaxp.dll
    <CPCMD> ntaxp/wccdaxpe.sym <RELROOT>/rel2/binnt/wccdaxp.sym

    <CPCMD> os2axp/wccaxpe.exe <RELROOT>/rel2/binp/wccaxp.exe
    <CPCMD> os2axp/wccaxpe.sym <RELROOT>/rel2/binp/wccaxp.sym
    <CPCMD> os2axp/wccdaxpe.dll <RELROOT>/rel2/binp/dll/wccdaxp.dll
    <CPCMD> os2axp/wccdaxpe.sym <RELROOT>/rel2/binp/dll/wccdaxp.sym

#NT stuff
    <CPCMD> nt386/wcc386e.exe <RELROOT>/rel2/binnt/wcc386.exe
    <CPCMD> nt386/wcc386e.sym <RELROOT>/rel2/binnt/wcc386.sym
    <CPCMD> nt386/wccd386e.dll <RELROOT>/rel2/binnt/wccd386.dll
    <CPCMD> nt386/wccd386e.sym <RELROOT>/rel2/binnt/wccd386.sym
    <CPCMD> nt386/wcc38601.int <RELROOT>/rel2/binnt/wcc38601.int
    <CPCMD> nti86/wcci86e.exe <RELROOT>/rel2/binnt/wcc.exe
    <CPCMD> nti86/wcci86e.sym <RELROOT>/rel2/binnt/wcc.sym
    <CPCMD> nti86/wccdi86e.dll <RELROOT>/rel2/binnt/wccd.dll
    <CPCMD> nti86/wccdi86e.sym <RELROOT>/rel2/binnt/wccd.sym
    <CPCMD> nti86/wcci8601.int <RELROOT>/rel2/binnt/wcci8601.int

#OS/2 stuff
    <CPCMD> os2386/wcc386e.exe <RELROOT>/rel2/binp/wcc386.exe
    <CPCMD> os2386/wcc386e.sym <RELROOT>/rel2/binp/wcc386.sym
    <CPCMD> os2386/wccd386e.dll <RELROOT>/rel2/binp/dll/wccd386.dll
    <CPCMD> os2386/wccd386e.sym <RELROOT>/rel2/binp/dll/wccd386.sym
    <CPCMD> os2386/wcc38601.int <RELROOT>/rel2/binp/dll/wcc38601.int

    <CPCMD> os2i86/wcci86e.exe <RELROOT>/rel2/binp/wcc.exe
    <CPCMD> os2i86/wcci86e.sym <RELROOT>/rel2/binp/wcc.sym
    <CPCMD> os2i86/wccdi86e.dll <RELROOT>/rel2/binp/dll/wccd.dll
    <CPCMD> os2i86/wccdi86e.sym <RELROOT>/rel2/binp/dll/wccd.sym
    <CPCMD> os2i86/wcci8601.int <RELROOT>/rel2/binp/dll/wcci8601.int

#QNX stuff
#    <CPCMD> qnxi86/wcci86c.qnx <RELROOT>/rel2/qnx/binq/wcc.
#    <CPCMD> qnxi86/wcci86c.sym <RELROOT>/rel2/qnx/sym/wcc.sym
#    <CPCMD> qnx386/wcc386c.qnx <RELROOT>/rel2/qnx/binq/wcc386.
#    <CPCMD> qnx386/wcc386c.sym <RELROOT>/rel2/qnx/sym/wcc.sym

#AXP NT host
#    <CPCMD> ntaxp.axp/wccaxpc.exe <RELROOT>/rel2/axpnt/wccaxp.exe
#    <CPCMD> ntaxp.axp/wccaxpc.exe <RELROOT>/rel2/axpnt/wccaxp.sym
#    <CPCMD> ntaxp.386/wcc386c.exe <RELROOT>/rel2/axpnt/wcc386.exe
#    <CPCMD> ntaxp.i86/wcci86c.exe <RELROOT>/rel2/axpnt/wcc.exe
#    <CPCMD> ntaxp.axp/wccaxpe.exe <RELROOT>/rel2/axpnt/wccaxp.exe
#    <CPCMD> ntaxp.axp/wccdaxpe.dll <RELROOT>/rel2/axpnt/wccdaxp.dll
#    <CPCMD> ntppc/wccppcc.exe <RELROOT>/rel2/binnt/wccppc.exe

[ BLOCK <1> clean ]
#==================
    pmake -d all <2> <3> <4> <5> <6> <7> <8> <9> -h clean
