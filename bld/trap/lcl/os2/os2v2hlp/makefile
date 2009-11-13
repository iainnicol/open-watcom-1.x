#pmake: os_os2 lcl cpu_386 support
#
# Create OS2V2HLP.EXE
#
host_CPU = 386
host_OS = os2

!include cproj.mif
!include deftarg.mif
!include defrule.mif

w : .symbolic os2v2hlp.exe
        @%null

.asm : ../asm

os2v2hlp.exe : os2v2hlp.obj
        $(linker) system os2v2 lx op dosseg, map name $^@ f os2v2hlp.obj &
                imp DOS32WRITE DOSCALLS.282,DOS32DEBUG DOSCALLS.317
>>>> ORIGINAL makefile#1
os2v2hlp.obj: ..\asm\os2v2hlp.asm
        $(wasm) -zq -3r ..\asm\os2v2hlp
==== THEIRS makefile#9
==== YOURS makefile
os2v2hlp.obj: ../asm/os2v2hlp.asm
        $(as) -3r $[@
