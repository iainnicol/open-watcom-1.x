.586
.mmx
.model small

.data

dataq dq 0
datad dd 0
dataw dw 0

.code

EMMS
MOVD datad,mm7
MOVD mm1,datad
MOVD mm3,ebx
MOVD ebx,mm7
MOVQ dataq,mm1
MOVQ mm1,mm7
MOVQ mm1,dataq
PACKSSDW mm1,mm7
PACKSSDW mm1,dataq
PACKSSWB mm1,mm7
PACKSSWB mm1,dataq
PACKUSWB mm1,mm7
PACKUSWB mm1,dataq
PADDB mm1,mm7
PADDB mm1,dataq
PADDD mm1,mm7
PADDD mm1,dataq
PADDSB mm1,mm7
PADDSB mm1,dataq
PADDSW mm1,mm7
PADDSW mm1,dataq
PADDUSB mm1,mm7
PADDUSB mm1,dataq
PADDUSW mm1,mm7
PADDUSW mm1,dataq
PADDW mm1,mm7
PADDW mm1,dataq
PAND mm1,mm7
PAND mm1,dataq
PANDN mm1,mm7
PANDN mm1,dataq
PCMPEQB mm1,mm7
PCMPEQB mm1,dataq
PCMPEQD mm1,mm7
PCMPEQD mm1,dataq
PCMPEQW mm1,mm7
PCMPEQW mm1,dataq
PCMPGTB mm1,mm7
PCMPGTB mm1,dataq
PCMPGTD mm1,mm7
PCMPGTD mm1,dataq
PCMPGTW mm1,mm7
PCMPGTW mm1,dataq
PMADDWD mm1,mm7
PMADDWD mm1,dataq
;PMULHUW mm1,mm7
;PMULHUW mm1,dataq
PMULHW mm1,mm7
PMULHW mm1,dataq
PMULLW mm1,mm7
PMULLW mm1,dataq
POR mm1,mm7
POR mm1,dataq
PSLLD mm7,255
PSLLD mm1,mm7
PSLLD mm1,dataq
PSLLQ mm7,255
PSLLQ mm1,mm7
PSLLQ mm1,dataq
PSLLW mm7,255
PSLLW mm1,mm7
PSLLW mm1,dataq
PSRAD mm7,255
PSRAD mm1,mm7
PSRAD mm1,dataq
PSRAW mm7,255
PSRAW mm1,mm7
PSRAW mm1,dataq
PSRLD mm7,255
PSRLD mm1,mm7
PSRLD mm1,dataq
PSRLQ mm7,255
PSRLQ mm1,mm7
PSRLQ mm1,dataq
PSRLW mm7,255
PSRLW mm1,mm7
PSRLW mm1,dataq
PSUBB mm1,mm7
PSUBB mm1,dataq
PSUBD mm1,mm7
PSUBD mm1,dataq
PSUBSB mm1,mm7
PSUBSB mm1,dataq
PSUBSW mm1,mm7
PSUBSW mm1,dataq
PSUBUSB mm1,mm7
PSUBUSB mm1,dataq
PSUBUSW mm1,mm7
PSUBUSW mm1,dataq
PSUBW mm1,mm7
PSUBW mm1,dataq
PUNPCKHBW mm1,mm7
PUNPCKHBW mm1,dataq
PUNPCKHDQ mm1,mm7
PUNPCKHDQ mm1,dataq
PUNPCKHWD mm1,mm7
PUNPCKHWD mm1,dataq
PUNPCKLBW mm1,mm7
PUNPCKLBW mm1,dataq
PUNPCKLDQ mm1,mm7
PUNPCKLDQ mm1,dataq
PUNPCKLWD mm1,mm7
PUNPCKLWD mm1,dataq
PXOR mm1,mm7
PXOR mm1,dataq

end
