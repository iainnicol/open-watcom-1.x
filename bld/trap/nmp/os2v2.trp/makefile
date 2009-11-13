#pmake: build trap remote os_os2 cpu_i86 cpu_386 nmp x86
host_CPU = 386
host_OS = os2

os  = os2v2
srv = nmp
cpu = x86
which = TRAP
type  = remote_link

>>>> ORIGINAL makefile#1
extra_objs = $(remote_objs) nmpos22.obj
extra_libs = $(%os2tkroot)\lib\os2386.lib
==== THEIRS makefile#6
extra_objs = nmpos22.obj
==== YOURS makefile
extra_objs = $(remote_objs) nmpos22.obj
<<<<
extra_libs = $(os2386)

!include $(trap_dir)/master.mif
