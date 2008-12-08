.*
.*
.if &e'&dohelp eq 0 .do begin
.section Introduction
.do end
.*
.np
.ix '&stripcmdup'
.ix 'strip utility'
The &stripname may be used to manipulate information that is appended
to the end of an executable file.
The information can be either one of two things:
.autopoint
.point
Symbolic debugging information
.point
Resource information
.endpoint
.np
This information can be added or removed from the executable file.
Symbolic debugging information is placed at the end of an executable
file by the &lnkname or the &stripname..
Resource information is placed at the end of an executable by a
resource compiler or the &stripname..
.np
.ix 'removing debug information'
.ix 'debug information ' 'removal'
.ix 'executable files ' 'reducing size'
Once a program has been debugged, the &stripname allows you to remove
the debugging information from the executable file so that you do not
have to remove the debugging directives from the linker directive file
and link your program again.
Removal of the debugging information reduces the size of the
executable image.
.np
All executable files generated by the &lnkname can be specified as
input to the &stripname..
.if '&target' ne 'QNX' .do begin
Note that for executable files created for Novell's NetWare
operating system, debugging information created using the "NOVELL"
option in the "DEBUG" directive cannot be removed from the executable
file.
You must remove the "DEBUG" directive from the directive file and
re-link your application.
.np
The &stripname currently runs under the following operating systems.
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
.do end