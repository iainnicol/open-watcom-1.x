proj_name = wmake_regress_cmds

!include cproj.mif
!include deftarg.mif
!include defrule.mif

targets = mkerr.exe envarg.exe ifeq.exe

!ifdef __UNIX__
targets += rem
additional_cleanup = rem
!endif

all: $(targets) .SYMBOLIC
	@%null
	
mkerr.exe: mkerr.c
        $(host_cl) $(host_cl_opts) $<

envarg.exe: envarg.c
        $(host_cl) $(host_cl_opts) $<

ifeq.exe: ifeq.c
        $(host_cl) $(host_cl_opts) $<

rem: rem.c
        $(host_cl) $(host_cl_opts) $<
