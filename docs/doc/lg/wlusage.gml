.*
.*
.chap *refid=wlusage The &lnkname
.*
.np
The &lnkname is a linkage editor (linker) that takes object and
library files as input and produces executable files as output.
.ix 'OMF'
The following object module and library formats are supported by the
&lnkname..
.begbull
.bull
.ix 'Intel OMF'
The standard Intel Object Module Format (OMF).
.bull
.ix 'Microsoft OMF'
Microsoft's extensions to the standard Intel OMF.
.bull
.ix 'Phar Lap OMF-386'
Phar Lap's Easy OMF-386 object module format for linking 386
applications.
.bull
.ix 'COFF'
The COFF object module format.
.bull
.ix 'ELF'
The ELF object module format.
.bull
.ix 'OMF library'
The OMF library format.
.bull
.ix 'AR-format'
The AR (Microsoft compatible) object library format.
.endbull
.np
.ix 'executable formats'
The &lnkname is capable of producing a number of executable file
formats.
The following lists these executable file formats.
.begbull
.bull
DOS executable files
.bull
ELF executable files
.bull
executable files that run under FlashTek's DOS extender
.bull
executable files that run under Phar Lap's 386|DOS-Extender
.bull
executable files that run under Tenberry Software's DOS/4G and DOS/4GW
DOS extenders
.bull
NetWare Loadable Modules (NLMs) that run under Novell's NetWare
operating system
.bull
OS/2 executable files including Dynamic Link Libraries
.bull
QNX executable files
.bull
16-bit Windows (Win16) executable files including Dynamic Link Libraries
.bull
32-bit Windows (Win32) executable files including Dynamic Link Libraries
.endbull
.np
.ix 'host operating system'
In addition to being able to generate the above executable file
formats, the &lnkname also runs under a variety of operating systems.
Currently, the &lnkname runs under the following operating systems.
.begbull
.bull
DOS
.bull
OS/2
.bull
QNX
.bull
Windows NT/2000/XP
.bull
Windows 95/98/Me
.endbull
.if '&target' eq 'QNX' .do begin
.im tutqnx
.do end
.el .do begin
.np
.ix 'host'
.ix 'host operating system'
.ix 'operating system' 'host'
We refer to the operating system upon which you run the &lnkname as
the "host".
.np
The chapter entitled :HDREF refid='tutchap'. summarizes each of the
executable file formats that can be generated by the linker.
The chapter entitled :HDREF refid='genchap'. describes all of the
linker directives and options.
The remaining chapters describe aspects of each of the executable
file formats.
.do end
