.686
.xmm3
.model small

.code

addsubpd xmm1,xmm7
addsubps xmm1,xmm7
fisttp dword ptr dataq
fisttp dword ptr cs:[bx+di+10]
fisttp dword ptr cs:[ebx+2*eax+10]
fisttp qword ptr dataq
fisttp qword ptr cs:[bx+di+10]
fisttp qword ptr cs:[ebx+2*eax+10]
fisttp word ptr dataq
fisttp word ptr cs:[bx+di+10]
fisttp word ptr cs:[ebx+2*eax+10]
haddpd xmm1,xmm7
haddps xmm1,xmm7
hsubpd xmm1,xmm7
hsubps xmm1,xmm7
lddqu xmm1,datao
lddqu xmm1,cs:[bx+di+10]
lddqu xmm1,cs:[ebx+2*eax+10]
monitor
movddup xmm1,xmm7
movddup xmm1,datao
movddup xmm1,cs:[bx+di+10]
movddup xmm1,cs:[ebx+2*eax+10]
movshdup xmm1,xmm7
movshdup xmm1,datao
movshdup xmm1,cs:[bx+di+10]
movshdup xmm1,cs:[ebx+2*eax+10]
movsldup xmm1,xmm7
movsldup xmm1,datao
movsldup xmm1,cs:[bx+di+10]
movsldup xmm1,cs:[ebx+2*eax+10]
mwait

.data

datao label oword
dataq dq 0,0

end
