.*
.*
.option OSNAME
.*
.np
The "OSNAME" option can be used to set the name of the target
operating system of the executable file generated by the linker.
The format of the "OSNAME" option (short form "OSN") is as follows.
.mbigbox
    OPTION OSNAME='string'
.embigbox
.synote
.mnote string
is any sequence of characters.
.esynote
.np
The information specified by the "OSNAME" option will be displayed in
the
.us creating a ? executable
message.
This is the last line of output produced by the linker, provided the
"QUIET" option is not specified.
Consider the following example.
.millust begin
option osname='SuperOS'
.millust end
.np
The last line of output produced by the linker will be as follows.
.millust begin
creating a SuperOS executable
.millust end
.np
Some executable formats have a stub executable file that is run under
16-bit DOS.
The message displayed by the default stub executable file will be
modified when the "OSNAME" option is used.
The default stub executable displays the following message:
.begnote $break
.note OS/2:
.mono this is an OS/2 executable
.note Win16:
.mono this is a Windows executable
.note Win32:
.mono this is a Windows NT executable
.endnote
.np
If the "OSNAME" option used in the previous example was specified, the
default stub executable would generate the following message.
.millust begin
this is a SuperOS executable
.millust end
