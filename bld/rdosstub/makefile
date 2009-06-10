#pmake: build os_dos os_win cpu_i86 cpu_386

host_os  = dos
host_cpu = i86

memory_model_i86 = s

!include cproj.mif
!include defrule.mif
!include deftarg.mif

all : rdosstub.exe

!ifeq release 1
extra_c_flags = -oaxs
!endif

rdosstub.exe : rdosstub.obj
        $(linker) $(lflags) file $[@
