.686
.xmm
.model small

.data

datao label oword
dataq dq 0
datad dd 0
dataw dw 0

.code

ADDSUBPD xmm1,xmm7
ADDSUBPS xmm1,xmm7
FISTTP datad
FISTTP dword ptr cs:[bx+di+10]
FISTTP dword ptr cs:[ebx+2*eax+10]
FISTTP dataq
FISTTP qword ptr cs:[bx+di+10]
FISTTP qword ptr cs:[ebx+2*eax+10]
FISTTP dataw
FISTTP word ptr cs:[bx+di+10]
FISTTP word ptr cs:[ebx+2*eax+10]
HADDPD xmm1,xmm7
HADDPS xmm1,xmm7
HSUBPD xmm1,xmm7
HSUBPS xmm1,xmm7
LDDQU xmm1,datao
LDDQU xmm1,cs:[bx+di+10]
LDDQU xmm1,cs:[ebx+2*eax+10]
MONITOR
MOVDDUP xmm1,xmm7
MOVDDUP xmm1,datao
MOVDDUP xmm1,cs:[bx+di+10]
MOVDDUP xmm1,cs:[ebx+2*eax+10]
MOVSHDUP xmm1,xmm7
MOVSHDUP xmm1,datao
MOVSHDUP xmm1,cs:[bx+di+10]
MOVSHDUP xmm1,cs:[ebx+2*eax+10]
MOVSLDUP xmm1,xmm7
MOVSLDUP xmm1,datao
MOVSLDUP xmm1,cs:[bx+di+10]
MOVSLDUP xmm1,cs:[ebx+2*eax+10]
MWAIT

end
