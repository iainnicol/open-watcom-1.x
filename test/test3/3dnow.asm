.586
.k3d
.model small

.data

data1 dq 0
data2 dq 0

.code

FEMMS
PAVGUSB mm1,mm7
PAVGUSB mm1,data1
PAVGUSB mm1,cs:[bx+di+10]
PAVGUSB mm1,cs:[ebx+2*eax+10]
PF2ID mm1,mm7
PF2ID mm1,data1
PF2ID mm1,cs:[bx+di+10]
PF2ID mm1,cs:[ebx+2*eax+10]
PF2IW mm1,mm7
PF2IW mm1,data1
PF2IW mm1,cs:[bx+di+10]
PF2IW mm1,cs:[ebx+2*eax+10]
PFACC mm1,mm7
PFACC mm1,data1
PFACC mm1,cs:[bx+di+10]
PFACC mm1,cs:[ebx+2*eax+10]
PFADD mm1,mm7
PFADD mm1,data1
PFADD mm1,cs:[bx+di+10]
PFADD mm1,cs:[ebx+2*eax+10]
PFCMPEQ mm1,mm7
PFCMPEQ mm1,data1
PFCMPEQ mm1,cs:[bx+di+10]
PFCMPEQ mm1,cs:[ebx+2*eax+10]
PFCMPGE mm1,mm7
PFCMPGE mm1,data1
PFCMPGE mm1,cs:[bx+di+10]
PFCMPGE mm1,cs:[ebx+2*eax+10]
PFCMPGT mm1,mm7
PFCMPGT mm1,data1
PFCMPGT mm1,cs:[bx+di+10]
PFCMPGT mm1,cs:[ebx+2*eax+10]
PFMAX mm1,mm7
PFMAX mm1,data1
PFMAX mm1,cs:[bx+di+10]
PFMAX mm1,cs:[ebx+2*eax+10]
PFMIN mm1,mm7
PFMIN mm1,data1
PFMIN mm1,cs:[bx+di+10]
PFMIN mm1,cs:[ebx+2*eax+10]
PFMUL mm1,mm7
PFMUL mm1,data1
PFMUL mm1,cs:[bx+di+10]
PFMUL mm1,cs:[ebx+2*eax+10]
PFNACC mm1,mm7
PFNACC mm1,data1
PFNACC mm1,cs:[bx+di+10]
PFNACC mm1,cs:[ebx+2*eax+10]
PFPNACC mm1,mm7
PFPNACC mm1,data1
PFPNACC mm1,cs:[bx+di+10]
PFPNACC mm1,cs:[ebx+2*eax+10]
PFRCP mm1,mm7
PFRCP mm1,data1
PFRCP mm1,cs:[bx+di+10]
PFRCP mm1,cs:[ebx+2*eax+10]
PFRCPIT1 mm1,mm7
PFRCPIT1 mm1,data1
PFRCPIT1 mm1,cs:[bx+di+10]
PFRCPIT1 mm1,cs:[ebx+2*eax+10]
PFRCPIT2 mm1,mm7
PFRCPIT2 mm1,data1
PFRCPIT2 mm1,cs:[bx+di+10]
PFRCPIT2 mm1,cs:[ebx+2*eax+10]
PFRSQIT1 mm1,mm7
PFRSQIT1 mm1,data1
PFRSQIT1 mm1,cs:[bx+di+10]
PFRSQIT1 mm1,cs:[ebx+2*eax+10]
PFRSQRT mm1,mm7
PFRSQRT mm1,data1
PFRSQRT mm1,cs:[bx+di+10]
PFRSQRT mm1,cs:[ebx+2*eax+10]
PFSUB mm1,mm7
PFSUB mm1,data1
PFSUB mm1,cs:[bx+di+10]
PFSUB mm1,cs:[ebx+2*eax+10]
PFSUBR mm1,mm7
PFSUBR mm1,data1
PFSUBR mm1,cs:[bx+di+10]
PFSUBR mm1,cs:[ebx+2*eax+10]
PI2FD mm1,mm7
PI2FD mm1,data1
PI2FD mm1,cs:[bx+di+10]
PI2FD mm1,cs:[ebx+2*eax+10]
PI2FW mm1,mm7
PI2FW mm1,data1
PI2FW mm1,cs:[bx+di+10]
PI2FW mm1,cs:[ebx+2*eax+10]
PMULHRW mm1,mm7
PMULHRW mm1,data1
PMULHRW mm1,cs:[bx+di+10]
PMULHRW mm1,cs:[ebx+2*eax+10]
PREFETCH data1
PREFETCH cs:[bx+di+10]
PREFETCH cs:[ebx+2*eax+10]
PREFETCHW data2
PSWAPD mm1,mm7
PSWAPD mm1,data1
PSWAPD mm1,cs:[bx+di+10]
PSWAPD mm1,cs:[ebx+2*eax+10]

end
