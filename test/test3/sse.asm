.686
.xmm
.model small

.data

datao label oword
dataq dq 0
datad dd 0
dataw dw 0

.code

ADDPS xmm1, xmm6
ADDPS xmm1, datao
ADDPS xmm1, cs:[bx+di+10]
ADDPS xmm1, cs:[ebx+2*eax+10]
ADDSS xmm1, xmm6	
ADDSS xmm1,datad
ADDSS xmm1,cs:[bx+di+10]
ADDSS xmm1,cs:[ebx+2*eax+10]
ANDNPS xmm1, xmm6
ANDNPS xmm1, datao
ANDNPS xmm1, cs:[bx+di+10]
ANDNPS xmm1, cs:[ebx+2*eax+10]
ANDPS xmm1, xmm6
ANDPS xmm1, datao
ANDPS xmm1, cs:[bx+di+10]
ANDPS xmm1, cs:[ebx+2*eax+10]
CMPPS xmm1, xmm6,255
CMPPS xmm1, dataq,255
CMPPS xmm1, cs:[bx+di+10],255
CMPPS xmm1, cs:[ebx+2*eax+10],255
CMPSS xmm1, xmm6,255
CMPSS xmm1, dataq,255
CMPSS xmm1, cs:[bx+di+10],255
CMPSS xmm1, cs:[ebx+2*eax+10],255
COMISS xmm1, xmm6
COMISS xmm1, datao
COMISS xmm1, cs:[bx+di+10]
COMISS xmm1, cs:[ebx+2*eax+10]
CVTPI2PS xmm1, mm5
CVTPI2PS xmm1, dataq
CVTPI2PS xmm1, cs:[bx+di+10]
CVTPI2PS xmm1, cs:[ebx+2*eax+10]
CVTPS2PI mm2, xmm6
CVTPS2PI mm2, dataq
CVTPS2PI mm2, cs:[bx+di+10]
CVTPS2PI mm2, cs:[ebx+2*eax+10]
CVTSI2SS XMM1,datad
CVTSI2SS XMM1,cs:[bx+di+10]
CVTSI2SS XMM1,cs:[ebx+2*eax+10]
CVTSI2SS XMM1,ebx
CVTSS2SI ebx, xmm4
CVTSS2SI ebx, datad
CVTSS2SI ebx, cs:[bx+di+10]
CVTSS2SI ebx, cs:[ebx+2*eax+10]
CVTTPS2PI mm2, xmm6
CVTTPS2PI mm2, dataq
CVTTPS2PI mm2, cs:[bx+di+10]
CVTTPS2PI mm2, cs:[ebx+2*eax+10]
CVTTSS2SI ebx, xmm4
CVTTSS2SI ebx, datad
CVTTSS2SI ebx, cs:[bx+di+10]
CVTTSS2SI ebx, cs:[ebx+2*eax+10]
DIVPS xmm1, xmm6
DIVPS xmm1, dataq
DIVPS xmm1, cs:[bx+di+10]
DIVPS xmm1, cs:[ebx+2*eax+10]
DIVSS xmm1, xmm6
DIVSS xmm1, dataq
DIVSS xmm1, cs:[bx+di+10]
DIVSS xmm1, cs:[ebx+2*eax+10]
FXRSTOR dataq
FXRSTOR cs:[bx+di+10]
FXRSTOR cs:[ebx+2*eax+10]
FXSAVE dataq
FXSAVE cs:[bx+di+10]
FXSAVE cs:[ebx+2*eax+10]
LDMXCSR datad
LDMXCSR cs:[bx+di+10]
LDMXCSR cs:[ebx+2*eax+10]
MASKMOVQ mm1,mm3
MAXPS xmm1, xmm6
MAXPS xmm1, dataq
MAXPS xmm1, cs:[bx+di+10]
MAXPS xmm1, cs:[ebx+2*eax+10]
MAXSS xmm1, xmm6
MAXSS xmm1, dataq
MAXSS xmm1, cs:[bx+di+10]
MAXSS xmm1, cs:[ebx+2*eax+10]
MINPS xmm1, xmm6
MINPS xmm1, dataq
MINPS xmm1, cs:[bx+di+10]
MINPS xmm1, cs:[ebx+2*eax+10]
MINSS xmm1, xmm6
MINSS xmm1, dataq
MINSS xmm1, cs:[bx+di+10]
MINSS xmm1, cs:[ebx+2*eax+10]
MOVAPS dataq,xmm7
MOVAPS cs:[bx+di+10],xmm7
MOVAPS cs:[ebx+2*eax+10],xmm7
MOVAPS xmm1, xmm6
MOVAPS xmm1, dataq
MOVAPS xmm1, cs:[bx+di+10]
MOVAPS xmm1, cs:[ebx+2*eax+10]
MOVHLPS xmm7,xmm1
MOVHPS dataq,xmm7
MOVHPS cs:[bx+di+10],xmm7
MOVHPS cs:[ebx+2*eax+10],xmm7
MOVHPS xmm1,dataq
MOVHPS xmm1,cs:[bx+di+10]
MOVHPS xmm1,cs:[ebx+2*eax+10]
MOVLHPS xmm1,xmm7
MOVLPS dataq,xmm7
MOVLPS cs:[bx+di+10],xmm7
MOVLPS cs:[ebx+2*eax+10],xmm7
MOVLPS xmm7,dataq
MOVLPS xmm7,cs:[bx+di+10]
MOVLPS xmm7,cs:[ebx+2*eax+10]
MOVMSKPS ebx,xmm7
MOVNTPS dataq,xmm7
MOVNTPS cs:[bx+di+10],xmm7
MOVNTPS cs:[ebx+2*eax+10],xmm7
MOVNTQ dataq,mm3
MOVNTQ cs:[bx+di+10],mm3
MOVNTQ cs:[ebx+2*eax+10],mm3
MOVSS dataq,xmm7
MOVSS cs:[bx+di+10],xmm7
MOVSS cs:[ebx+2*eax+10],xmm7
MOVSS xmm1, xmm6
MOVSS xmm1, dataq
MOVSS xmm1, cs:[bx+di+10]
MOVSS xmm1, cs:[ebx+2*eax+10]
MOVUPS dataq,xmm7
MOVUPS cs:[bx+di+10],xmm7
MOVUPS cs:[ebx+2*eax+10],xmm7
MOVUPS xmm1, xmm6
MOVUPS xmm1, dataq
MOVUPS xmm1, cs:[bx+di+10]
MOVUPS xmm1, cs:[ebx+2*eax+10]
MULPS xmm1, xmm6
MULPS xmm1, dataq
MULPS xmm1, cs:[bx+di+10]
MULPS xmm1, cs:[ebx+2*eax+10]
MULSS xmm1, xmm6
MULSS xmm1, dataq
MULSS xmm1, cs:[bx+di+10]
MULSS xmm1, cs:[ebx+2*eax+10]
ORPS xmm1, xmm6
ORPS xmm1, dataq
ORPS xmm1, cs:[bx+di+10]
ORPS xmm1, cs:[ebx+2*eax+10]
PAVGB mm2, mm5
PAVGB mm2, dataq
PAVGB mm2, cs:[bx+di+10]
PAVGB mm2, cs:[ebx+2*eax+10]
PAVGW mm2, mm5
PAVGW mm2, dataq
PAVGW mm2, cs:[bx+di+10]
PAVGW mm2, cs:[ebx+2*eax+10]
PEXTRW ebx,mm3,255
PEXTRW ebx,xmm3,255
PINSRW mm1,dataw,255
PINSRW mm1,cs:[bx+di+10],255
PINSRW mm1,cs:[ebx+2*eax+10],255
PINSRW mm3,ebx,255
PINSRW xmm1,dataw,255
PINSRW xmm1,cs:[bx+di+10],255
PINSRW xmm1,cs:[ebx+2*eax+10],255
PINSRW xmm3,ebx,255
PMAXSW mm2, mm5
PMAXSW mm2, dataq
PMAXSW mm2, cs:[bx+di+10]
PMAXSW mm2, cs:[ebx+2*eax+10]
PMAXUB mm2, mm5
PMAXUB mm2, dataq
PMAXUB mm2, cs:[bx+di+10]
PMAXUB mm2, cs:[ebx+2*eax+10]
PMINSW mm2, mm5
PMINSW mm2, dataq
PMINSW mm2, cs:[bx+di+10]
PMINSW mm2, cs:[ebx+2*eax+10]
PMINUB mm2, mm5
PMINUB mm2, dataq
PMINUB mm2, cs:[bx+di+10]
PMINUB mm2, cs:[ebx+2*eax+10]
PMOVMSKB ebx,mm1
PMULHUW mm1, mm6
PMULHUW mm1, dataq
PMULHUW mm1, cs:[bx+di+10]
PMULHUW mm1, cs:[ebx+2*eax+10]
PREFETCHNTA dataq
PREFETCHNTA cs:[bx+di+10]
PREFETCHNTA cs:[ebx+2*eax+10]
PREFETCHT0 dataq
PREFETCHT0 cs:[bx+di+10]
PREFETCHT0 cs:[ebx+2*eax+10]
PREFETCHT1 dataq
PREFETCHT1 cs:[bx+di+10]
PREFETCHT1 cs:[ebx+2*eax+10]
PREFETCHT2 dataq
PREFETCHT2 cs:[bx+di+10]
PREFETCHT2 cs:[ebx+2*eax+10]
PSADBW mm2, mm5
PSADBW mm2, dataq
PSADBW mm2, cs:[bx+di+10]
PSADBW mm2, cs:[ebx+2*eax+10]
PSHUFW mm2, mm5,255
PSHUFW mm2, dataq,255
PSHUFW mm2, cs:[bx+di+10],255
PSHUFW mm2, cs:[ebx+2*eax+10],255
RCPPS xmm1, xmm6
RCPPS xmm1, dataq
RCPPS xmm1, cs:[bx+di+10]
RCPPS xmm1, cs:[ebx+2*eax+10]
RCPSS xmm1, xmm6
RCPSS xmm1, dataq
RCPSS xmm1, cs:[bx+di+10]
RCPSS xmm1, cs:[ebx+2*eax+10]
RSQRTPS xmm1, xmm6
RSQRTPS xmm1, dataq
RSQRTPS xmm1, cs:[bx+di+10]
RSQRTPS xmm1, cs:[ebx+2*eax+10]
RSQRTSS xmm1, xmm6
RSQRTSS xmm1, dataq
RSQRTSS xmm1, cs:[bx+di+10]
RSQRTSS xmm1, cs:[ebx+2*eax+10]
SFENCE
SHUFPS xmm1, xmm6,255
SHUFPS xmm1, dataq,255
SHUFPS xmm1, cs:[bx+di+10],255
SHUFPS xmm1, cs:[ebx+2*eax+10],255
SQRTPS xmm1, xmm6
SQRTPS xmm1, dataq
SQRTPS xmm1, cs:[bx+di+10]
SQRTPS xmm1, cs:[ebx+2*eax+10]
SQRTSS xmm1, xmm6
SQRTSS xmm1, dataq
SQRTSS xmm1, cs:[bx+di+10]
SQRTSS xmm1, cs:[ebx+2*eax+10]
STMXCSR datad
STMXCSR cs:[bx+di+10]
STMXCSR cs:[ebx+2*eax+10]
SUBPS xmm1, xmm6
SUBPS xmm1, dataq
SUBPS xmm1, cs:[bx+di+10]
SUBPS xmm1, cs:[ebx+2*eax+10]
SUBSS xmm1, xmm6
SUBSS xmm1, dataq
SUBSS xmm1, cs:[bx+di+10]
SUBSS xmm1, cs:[ebx+2*eax+10]
UCOMISS xmm1, xmm6
UCOMISS xmm1, datao
UCOMISS xmm1, cs:[bx+di+10]
UCOMISS xmm1, cs:[ebx+2*eax+10]
UNPCKHPS xmm1, xmm6
UNPCKHPS xmm1, dataq
UNPCKHPS xmm1, cs:[bx+di+10]
UNPCKHPS xmm1, cs:[ebx+2*eax+10]
UNPCKLPS xmm1, xmm6
UNPCKLPS xmm1, dataq
UNPCKLPS xmm1, cs:[bx+di+10]
UNPCKLPS xmm1, cs:[ebx+2*eax+10]
XORPS xmm1, xmm6
XORPS xmm1, dataq
XORPS xmm1, cs:[bx+di+10]
XORPS xmm1, cs:[ebx+2*eax+10]

end
