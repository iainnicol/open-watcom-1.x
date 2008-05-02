# vi Builder Control file
# =======================

set PROJDIR=<CWD>
set PROJNAME=vi

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> build rel ]
#======================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h bind=1

[ BLOCK . . ]

[ INCLUDE <OWROOT>/build/deftool.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CPCMD> <PROJDIR>/dat/v*.cmd                <RELROOT>/binp/
    <CPCMD> <PROJDIR>/dat/v*.bat                <RELROOT>/binw/
    <CPCMD> <PROJDIR>/dat/*.vi                  <RELROOT>/eddat/
    <CPCMD> <PROJDIR>/dat/*.cfg                 <RELROOT>/eddat/
    <CPCMD> <PROJDIR>/dat/*.dat                 <RELROOT>/eddat/
    <CPCMD> <PROJDIR>/dat/*.ini                 <RELROOT>/eddat/
    <CPCMD> <PROJDIR>/dat/bindvi.*              <RELROOT>/eddat/
    <CPCMD> <PROJDIR>/doc/*.hlp                 <RELROOT>/eddat/

    <CCCMD> <PROJDIR>/dos386/vi.exe             <RELROOT>/binw/vi.exe
    <CCCMD> <PROJDIR>/ctags/dos386/ctags.exe    <RELROOT>/binw/ctags.exe
    <CCCMD> <PROJDIR>/bind/dosi86/edbind.exe    <RELROOT>/binw/edbind.exe

    <CCCMD> <PROJDIR>/wini86/vi.exe             <RELROOT>/binw/viw.exe
    <CCCMD> <PROJDIR>/win386/vi.exe             <RELROOT>/binw/viwp.exe

    <CCCMD> <PROJDIR>/nt386/vi.exe              <RELROOT>/binnt/vi.exe
    <CCCMD> <PROJDIR>/nt386.win/vi.exe          <RELROOT>/binnt/viw.exe
    <CCCMD> <PROJDIR>/ctags/nt386/ctags.exe     <RELROOT>/binnt/ctags.exe
    <CCCMD> <PROJDIR>/bind/nt386/edbind.exe     <RELROOT>/binnt/edbind.exe

    <CCCMD> <PROJDIR>/ntaxp/vi.exe              <RELROOT>/axpnt/vi.exe
    <CCCMD> <PROJDIR>/ntaxp.win/vi.exe          <RELROOT>/axpnt/viw.exe
    <CCCMD> <PROJDIR>/ctags/ntaxp/ctags.exe     <RELROOT>/axpnt/ctags.exe
    <CCCMD> <PROJDIR>/bind/ntaxp/edbind.exe     <RELROOT>/axpnt/edbind.exe

    <CCCMD> <PROJDIR>/os2386/vi.exe             <RELROOT>/binp/vi.exe
    <CCCMD> <PROJDIR>/ctags/os2386/ctags.exe    <RELROOT>/binp/ctags.exe
    <CCCMD> <PROJDIR>/bind/os2386/edbind.exe    <RELROOT>/binp/edbind.exe

    <CCCMD> <PROJDIR>/qnxi86/vi.exe             <RELROOT>/qnx/binq/vi

    <CCCMD> <PROJDIR>/linux386/vi.exe           <RELROOT>/binl/vi
    <CCCMD> <PROJDIR>/linux386/vi.sym           <RELROOT>/binl/vi.sym
    <CCCMD> <PROJDIR>/ctags/linux386/ctags.exe  <RELROOT>/binl/ctags
    <CCCMD> <PROJDIR>/bind/linux386/edbind.exe  <RELROOT>/binl/edbind

[ BLOCK . . ]
#============
cdsay <PROJDIR>
