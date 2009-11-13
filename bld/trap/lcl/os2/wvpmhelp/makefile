#pmake: os_os2 lcl cpu_386 support
#
# Create WDPMHELP.EXE, WDPMHOOK.DLL
#

host_os  = os2
host_cpu = i86

!include cproj.mif
!include deftarg.mif

proj_name = wvpmhelp

!include cproj.mif
!include deftarg.mif
!include defrule.mif
w d : wdpmhook.dll wdpmhelp.exe .SYMBOLIC
        @%null

tmplnk = tmp.lnk
wdpmhook.dll: pmhook.obj loadstd.obj
    @%write  $^&.lnk name $^@ sys os2 dll initglobal
    @%append $^&.lnk debug all op symfile
    @%append $^&.lnk option dosseg,quiet
    @%append $^&.lnk option map
    @%append $^&.lnk file loadstd.obj,pmhook.obj
    @%append $^&.lnk library os2.lib
    @%append $^&.lnk export SENDMSGHOOKPROC.1,SETHMQDEBUGEE.2
    @%append $^&.lnk segment class 'DATA' shared
    @%append $^&.lnk segment class 'BSS' shared
    $(linker) @$^&.lnk

>>>> ORIGINAL makefile#1
$(bdir)\dll\wdpmhook.dll: pmhook.obj loadstd.obj
    @%write  $(tmplnk) name $(bdir)\dll\wdpmhook.dll sys os2 dll initglobal
    @%append $(tmplnk) debug all op symfile
    @%append $(tmplnk) option dosseg,quiet
    @%append $(tmplnk) option map
    @%append $(tmplnk) file loadstd,pmhook
    @%append $(tmplnk) library $(watcom_dir)\lib\os2.lib
    @%append $(tmplnk) export SendMsgHookProc.1,SetHmqDebugee.2
    @%append $(tmplnk) segment class 'DATA' shared
    @%append $(tmplnk) segment class 'BSS' shared
    $(linker) @$(tmplnk)
==== THEIRS makefile#11
wdpmhelp.exe: _err.gh pmhelp.res pmhelp.obj
    @%write  $^&.lnk name $^@ system os2 pm
    @%append $^&.lnk debug all op symfile
    @%append $^&.lnk file pmhelp.obj
    @%append $^&.lnk library clibl.lib
    @%append $^&.lnk library os2.lib
    @%append $^&.lnk option alignment=16
    @%append $^&.lnk option nodefaultlibs,quiet
    @%append $^&.lnk option modname=wdpmhelp
    @%append $^&.lnk option description 'OS/2 Presentation Manager Sample'
    @%append $^&.lnk option manyautodata
    @%append $^&.lnk option stack=4096
    @%append $^&.lnk option heapsize=1024
    @%append $^&.lnk option protmode
    $(linker) @$^&.lnk
    $(rc) pmhelp.res wdpmhelp.exe
==== YOURS makefile
wdpmhook.dll: pmhook.obj loadstd.obj
    @%write  $(tmplnk) name $^@ sys os2 dll initglobal
    @%append $(tmplnk) debug all op symfile
    @%append $(tmplnk) option dosseg,quiet
    @%append $(tmplnk) option map
    @%append $(tmplnk) file loadstd,pmhook
    @%append $(tmplnk) library os2.lib
    @%append $(tmplnk) export SENDMSGHOOKPROC.1,SETHMQDEBUGEE.2
    @%append $(tmplnk) segment class 'DATA' shared
    @%append $(tmplnk) segment class 'BSS' shared
    $(linker) @$(tmplnk)
<<<<

wdpmhelp.exe: pmhelp.lbj pmhelp.res
    @%write  $(tmplnk) name $^@ system os2 pm
    @%append $(tmplnk) library os2.lib
    $(lang_root)\binp\rc pmhelp.res wdpmhelp.exe
.c: ../c
.asm: ../asm

>>>> ORIGINAL makefile#1
.c: ..\c
==== THEIRS makefile#11
extra_c_flags = -s -zu -fpc
==== YOURS makefile
.c: ../c
<<<<

>>>> ORIGINAL makefile#1
.c.obj:
        $(comp286) $[* -bt=os2 -zq-fpc-d1-oais-s-w3-mc-zu-i$(watcom_dir)\h;$(watcom_dir)\os21x_h;$(watcom_dir)\os220_h;$(trap_dir)\h
==== THEIRS makefile#11
extra_c_flags_pmhook = -mc -oais
extra_c_flags_pmhelp = -ml
==== YOURS makefile
.c.obj:
        $(comp286) $[* -bt=os2 -zq-fpc-d1-oais-s-w3-mc-zu-i"$(watcom_dir)/h;$(lang_root)/h/os21x;$(lang_root)/h/os2;$(trap_dir)/h"
<<<<

>>>> ORIGINAL makefile#1
.c.lbj
        $(comp286) $[* -bt=os2 -zq-fpc-d1-ml-zu-w3-s-i$(watcom_dir)\os21x_h;$(trap_dir)\h -fo=.lbj
==== THEIRS makefile#11
inc_dirs = -i"$(watcom_dir)/h;$(lang_root)/h/os21x;$(lang_root)/h/os2;$(trap_dir)/h"
==== YOURS makefile
.c.lbj
        $(comp286) $[* -bt=os2 -zq-fpc-d1-ml-zu-w3-s-i"$(lang_root)/h/os21x;$(trap_dir)/h" -fo=.lbj
<<<<

>>>> ORIGINAL makefile#1
.asm: ..\asm
==== THEIRS makefile#11
extra_a_flags = -2 -bt=os2 -fo=.obj -mc
==== YOURS makefile
.asm: ../asm
<<<<

        $(as) -2 -bt=os2 $[*
pmhelp.res: ../h/pmhelp.rc ../h/wdpmhelp.h
    $(rc) $(rc_flags) $(inc_path) $[@ -fo=$@

>>>> ORIGINAL makefile#1
pmlock.obj : pmlock.c ..\h\wdpmhelp.h
==== THEIRS makefile#11
./mkstr.exe: $(trap_dir)/c/mkstr.c $(trap_dir)/h/trap.msg
    $(bld_cl) $(wcl_util_opts) -I"$(trap_dir)/h" $[@
==== YOURS makefile
pmlock.obj : pmlock.c ../h/wdpmhelp.h
<<<<

>>>> ORIGINAL makefile#1
#.rc.res:
#       @set oinc=$(%include)
#       set include=$(watcom_dir)\os220_h;$(%include)
#       set opath=$(%path)
#       set path=$(%toolkit)\os2bin
#        $(%toolkit)\os2bin\rc -r $*.rc
#       set path=$(%opath)
#       @set include=$(%oinc)

==== THEIRS makefile#11
_err.gh : ./mkstr.exe
    $[@ $^@

==== YOURS makefile
pmhelp.res: ../h/pmhelp.rc ../h/wdpmhelp.h
<<<<
>>>> ORIGINAL makefile#1
        @set include=$(watcom_dir)\os21x_h;..\h;$(%include)
        @set opath=$(%path)
        @set path=$(os2_tools_root)
        $(os2_tools_root)\rc -r pmhelp.rc
        @set path=$(%opath)
        @set include=$(%oinc)
==== THEIRS makefile#11
==== YOURS makefile
        @set include=$(lang_root)/h/os21x;../h;$(%include)
        @set opath=$(%path)
        @set path=$(lang_root)\binp
        $(lang_root)\binp\rc -r ..\h\pmhelp.rc .\pmhelp.res
        @set path=$(%opath)
        @set include=$(%oinc)
