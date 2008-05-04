# Debugger Trap Files Control file
# ================================

set PROJDIR=<CWD>
set PROJNAME=trap

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK <1> rel cprel ]
#======================
    <CCCMD> <PROJDIR>/lcl/dos/dosr/dos.std/std.trp              <RELROOT>/binw/
    <CCCMD> <PROJDIR>/lcl/dos/dosx/rsi/dos.trp/rsi.trp          <RELROOT>/binw/
    <CCCMD> <PROJDIR>/lcl/dos/dosx/rsi/dos.srv/rsihelp.exp      <RELROOT>/binw/
    <CCCMD> <PROJDIR>/lcl/dos/dosx/pls/dos.trp/pls.trp          <RELROOT>/binw/
    <CCCMD> <PROJDIR>/lcl/dos/dosx/pls/dos.srv/plshelp.exp      <RELROOT>/binw/
    <CCCMD> <PROJDIR>/lcl/dos/dosx/pls/dosped.srv/pedhelp.exp   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/lcl/dos/dosx/cw/dos.trp/cw.trp            <RELROOT>/binw/
    <CCCMD> <PROJDIR>/lcl/dos/dosx/cw/dos.srv/cwhelp.exe        <RELROOT>/binw/
    <CCCMD> <PROJDIR>/net/dos.trp/net.trp                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/net/dos.srv/netserv.exe                   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nmp/dos.trp/nmp.trp                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nmp/dos.srv/nmpserv.exe                   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nov/dos.trp/nov.trp                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nov/dos.srv/novserv.exe                   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/par/dos.trp/par.trp                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/par/dos.srv/parserv.exe                   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/ser/dos.trp/ser.trp                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/ser/dos.srv/serserv.exe                   <RELROOT>/binw/
#    <CCCMD> <PROJDIR>/tcp/dos.trp/tcp.trp                      <RELROOT>/binw/
    <CCCMD> <PROJDIR>/tcp/dos.srv/tcpserv.exe                   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/vdm/dos.srv/vdmserv.exe                   <RELROOT>/binw/
    <CCCMD> <PROJDIR>/win/dos.trp/win.trp                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/win/dos.srv/winserv.exe                   <RELROOT>/binw/

    <CCCMD> <PROJDIR>/lcl/os2v2/std/std.d32                     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/net/os2v2.trp/net.d32                     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/net/os2v2.srv/netserv.exe                 <RELROOT>/binp/
    <CCCMD> <PROJDIR>/nmp/os2v2.trp/nmp.d32                     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/nmp/os2v2.srv/nmpserv.exe                 <RELROOT>/binp/
    <CCCMD> <PROJDIR>/par/os2v2.trp/par.d32                     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/par/os2v2.srv/parserv.exe                 <RELROOT>/binp/
    <CCCMD> <PROJDIR>/ser/os2v2.trp/ser.d32                     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/ser/os2v2.srv/serserv.exe                 <RELROOT>/binp/
    <CCCMD> <PROJDIR>/tcp/os2v2.trp/tcp.d32                     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/tcp/os2v2.srv/tcpserv.exe                 <RELROOT>/binp/
    <CCCMD> <PROJDIR>/vdm/os2v2.trp/vdm.d32                     <RELROOT>/binp/
    <CCCMD> <PROJDIR>/lcl/os2v2/wvpmhelp/wdpmhook.dll           <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/lcl/os2v2/wvpmhelp/wdpmhelp.exe           <RELROOT>/binp/
    <CCCMD> <PROJDIR>/lcl/os2v2/splice/wdsplice.dll             <RELROOT>/binp/dll/
    <CCCMD> <PROJDIR>/nmp/nmpbind/nmpbind.exe                   <RELROOT>/binp/
    <CCCMD> <PROJDIR>/par/os2v2.pio/wdio.dll                    <RELROOT>/binp/dll/
#os2
#    <CCCMD> <PROJDIR>/nov/os2.trp/nov.dll                      <RELROOT>/binp/dll/
#    <CCCMD> <PROJDIR>/nov/os2.srv/novserv1.exe                 <RELROOT>/binp/
#    <CCCMD> <DEVDIR>/bin/binp/dll/???.dll                          <RELROOT>/binp/dll/
#    <CCCMD> <DEVDIR>/bin/binp/dll/std??.dll                        <RELROOT>/binp/dll/
#    <CCCMD> <DEVDIR>/bin/binp/dll/???serv.exe                      <RELROOT>/binp/dll/
#    <CCCMD> <DEVDIR>/bin/binp/???serv1.exe                         <RELROOT>/binp/

    <CCCMD> <PROJDIR>/lcl/win/std/std.dll                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/net/win.trp/net.dll                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/net/win.srv/netservw.exe                  <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nmp/win.trp/nmp.dll                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nmp/win.srv/nmpservw.exe                  <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nov/win.trp/nov.dll                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/nov/win.srv/novservw.exe                  <RELROOT>/binw/
    <CCCMD> <PROJDIR>/par/win.trp/par.dll                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/par/win.srv/parservw.exe                  <RELROOT>/binw/
    <CCCMD> <PROJDIR>/tcp/win.trp/tcp.dll                       <RELROOT>/binw/
    <CCCMD> <PROJDIR>/tcp/win.srv/tcpservw.exe                  <RELROOT>/binw/
    <CCCMD> <PROJDIR>/vdm/win.srv/vdmservw.exe                  <RELROOT>/binw/
    <CCCMD> <PROJDIR>/lcl/win/int32/wint32.dll                  <RELROOT>/binw/

    <CCCMD> <PROJDIR>/lcl/nt/std/std.dll                        <RELROOT>/binnt/
#    <CCCMD> <PROJDIR>/nmp/nt.trp/nmp.dll                       <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nov/nt.trp/nov.dll                        <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/nov/nt.srv/novserv.exe                    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/par/nt.trp/par.dll                        <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/par/nt.srv/parserv.exe                    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/ser/nt.trp/ser.dll                        <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/ser/nt.srv/serserv.exe                    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/tcp/nt.trp/tcp.dll                        <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/tcp/nt.srv/tcpserv.exe                    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/vdm/nt.trp/vdm.dll                        <RELROOT>/binnt/
# NT parallel port device driver and installer
    <CCCMD> <PROJDIR>/par/ntsupp/dbgport.sys                    <RELROOT>/binnt/
    <CCCMD> <PROJDIR>/par/ntsupp/dbginst.exe                    <RELROOT>/binnt/

    <CCCMD> <PROJDIR>/lcl/nt/stdaxp/std.dll                     <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/nov/ntaxp.trp/nov.dll                     <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/nov/ntaxp.srv/novserv.exe                 <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/tcp/ntaxp.trp/tcp.dll                     <RELROOT>/axpnt/
    <CCCMD> <PROJDIR>/tcp/ntaxp.srv/tcpserv.exe                 <RELROOT>/axpnt/

    <CCCMD> <PROJDIR>/nov/nlm3.srv/novserv3.nlm                 <RELROOT>/nlm/
    <CCCMD> <PROJDIR>/nov/nlm4.srv/novserv4.nlm                 <RELROOT>/nlm/
    <CCCMD> <PROJDIR>/par/nlm3.srv/parserv3.nlm                 <RELROOT>/nlm/
    <CCCMD> <PROJDIR>/par/nlm4.srv/parserv4.nlm                 <RELROOT>/nlm/
    <CCCMD> <PROJDIR>/ser/nlm3.srv/serserv3.nlm                 <RELROOT>/nlm/
    <CCCMD> <PROJDIR>/ser/nlm4.srv/serserv4.nlm                 <RELROOT>/nlm/

    <CCCMD> <PROJDIR>/lcl/qnx/pmd/pmd.trp                       <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/lcl/qnx/std/std.trp                       <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/par/qnx.trp/par.trp                       <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/par/qnx.srv/parserv.qnx                   <RELROOT>/qnx/binq/parserv
    <CCCMD> <PROJDIR>/ser/qnx.trp/ser.trp                       <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/ser/qnx.srv/serserv.qnx                   <RELROOT>/qnx/binq/serserv
    <CCCMD> <PROJDIR>/tcp/qnx.trp/tcp.trp                       <RELROOT>/qnx/watcom/wd/
    <CCCMD> <PROJDIR>/tcp/qnx.srv/tcpserv.qnx                   <RELROOT>/qnx/binq/tcpserv

    <CCCMD> <PROJDIR>/lcl/linux/std/std.trp                     <RELROOT>/binl/
    <CCCMD> <PROJDIR>/par/linux.trp/par.trp                     <RELROOT>/binl/
    <CCCMD> <PROJDIR>/par/linux.srv/parserv.elf                 <RELROOT>/binl/parserv
    <CCCMD> <PROJDIR>/tcp/linux.trp/tcp.trp                     <RELROOT>/binl/
    <CCCMD> <PROJDIR>/tcp/linux.srv/tcpserv.elf                 <RELROOT>/binl/tcpserv

[ BLOCK . . ]
#============
cdsay <PROJDIR>
