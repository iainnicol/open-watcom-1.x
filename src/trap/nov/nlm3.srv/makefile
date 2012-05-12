#pmake: build serv remote os_nov cpu_386 nov x86

host_os  = nov
host_cpu = 386

!ifndef nlm_ver
nlm_ver = 3
!endif
os    = nlm
srv   = nov
cpu   = x86
which = SERVER
type  = remote_link

extra_objs = novnlm.obj

!include $(trap_dir)/lcl/nlm/trap.mif
!include $(trap_dir)/master.mif
