int     x;
#pragma aux pinit0=".486p"
#pragma aux p01 = "mov edx,dword ptr x[eax+eax]"
r01() { p01(); }
#pragma aux p02 = "mov edx,dword ptr x[eax+ebx]"
r02() { p02(); }
#pragma aux p04 = "mov edx,dword ptr x[eax+ecx]"
r04() { p04(); }
#pragma aux p06 = "mov edx,dword ptr x[eax+edx]"
r06() { p06(); }
#pragma aux p08 = "mov edx,dword ptr x[eax+esi]"
r08() { p08(); }
#pragma aux p10 = "mov edx,dword ptr x[eax+edi]"
r10() { p10(); }
#pragma aux p12 = "mov edx,dword ptr x[eax+ebp]"
r12() { p12(); }
#pragma aux p14 = "mov edx,dword ptr x[edx+eax]"
r14() { p14(); }
#pragma aux p16 = "mov edx,dword ptr x[edx+ebx]"
r16() { p16(); }
#pragma aux p18 = "mov edx,dword ptr x[edx+ecx]"
r18() { p18(); }
#pragma aux p20 = "mov edx,dword ptr x[edx+edx]"
r20() { p20(); }
#pragma aux p22 = "mov edx,dword ptr x[edx+esi]"
r22() { p22(); }
#pragma aux p24 = "mov edx,dword ptr x[edx+edi]"
r24() { p24(); }
#pragma aux p26 = "mov edx,dword ptr x[edx+ebp]"
r26() { p26(); }
#pragma aux p28 = "mov edx,dword ptr x[ebx+eax]"
r28() { p28(); }
#pragma aux p30 = "mov edx,dword ptr x[ebx+ebx]"
r30() { p30(); }
#pragma aux p32 = "mov edx,dword ptr x[ebx+ecx]"
r32() { p32(); }
#pragma aux p34 = "mov edx,dword ptr x[ebx+edx]"
r34() { p34(); }
#pragma aux p36 = "mov edx,dword ptr x[ebx+esi]"
r36() { p36(); }
#pragma aux p38 = "mov edx,dword ptr x[ebx+edi]"
r38() { p38(); }
#pragma aux p40 = "mov edx,dword ptr x[ebx+ebp]"
r40() { p40(); }
#pragma aux p42 = "mov edx,dword ptr x[ecx+eax]"
r42() { p42(); }
#pragma aux p44 = "mov edx,dword ptr x[ecx+ebx]"
r44() { p44(); }
#pragma aux p46 = "mov edx,dword ptr x[ecx+ecx]"
r46() { p46(); }
#pragma aux p48 = "mov edx,dword ptr x[ecx+edx]"
r48() { p48(); }
#pragma aux p50 = "mov edx,dword ptr x[ecx+esi]"
r50() { p50(); }
#pragma aux p52 = "mov edx,dword ptr x[ecx+edi]"
r52() { p52(); }
#pragma aux p54 = "mov edx,dword ptr x[ecx+ebp]"
r54() { p54(); }
#pragma aux p56 = "mov edx,dword ptr x[esi+eax]"
r56() { p56(); }
#pragma aux p58 = "mov edx,dword ptr x[esi+ebx]"
r58() { p58(); }
#pragma aux p60 = "mov edx,dword ptr x[esi+ecx]"
r60() { p60(); }
#pragma aux p62 = "mov edx,dword ptr x[esi+edx]"
r62() { p62(); }
#pragma aux p64 = "mov edx,dword ptr x[esi+esi]"
r64() { p64(); }
#pragma aux p66 = "mov edx,dword ptr x[esi+edi]"
r66() { p66(); }
#pragma aux p68 = "mov edx,dword ptr x[esi+ebp]"
r68() { p68(); }
#pragma aux p70 = "mov edx,dword ptr x[edi+eax]"
r70() { p70(); }
#pragma aux p72 = "mov edx,dword ptr x[edi+ebx]"
r72() { p72(); }
#pragma aux p74 = "mov edx,dword ptr x[edi+ecx]"
r74() { p74(); }
#pragma aux p76 = "mov edx,dword ptr x[edi+edx]"
r76() { p76(); }
#pragma aux p78 = "mov edx,dword ptr x[edi+esi]"
r78() { p78(); }
#pragma aux p80 = "mov edx,dword ptr x[edi+edi]"
r80() { p80(); }
#pragma aux p82 = "mov edx,dword ptr x[edi+ebp]"
r82() { p82(); }
#pragma aux p84 = "mov edx,dword ptr x[esp+eax]"
r84() { p84(); }
#pragma aux p86 = "mov edx,dword ptr x[esp+ebx]"
r86() { p86(); }
#pragma aux p88 = "mov edx,dword ptr x[esp+ecx]"
r88() { p88(); }
#pragma aux p090 = "mov edx,dword ptr x[esp+edx]"
r090() { p090(); }
#pragma aux p092 = "mov edx,dword ptr x[esp+esi]"
r092() { p092(); }
#pragma aux p094 = "mov edx,dword ptr x[esp+edi]"
r094() { p094(); }
#pragma aux p096 = "mov edx,dword ptr x[esp+ebp]"
r096() { p096(); }
#pragma aux p098 = "mov edx,dword ptr x[ebp+eax]"
r098() { p098(); }
#pragma aux p100 = "mov edx,dword ptr x[ebp+ebx]"
r100() { p100(); }
#pragma aux p102 = "mov edx,dword ptr x[ebp+ecx]"
r102() { p102(); }
#pragma aux p104 = "mov edx,dword ptr x[ebp+edx]"
r104() { p104(); }
#pragma aux p106 = "mov edx,dword ptr x[ebp+esi]"
r106() { p106(); }
#pragma aux p108 = "mov edx,dword ptr x[ebp+edi]"
r108() { p108(); }
#pragma aux p110 = "mov edx,dword ptr x[ebp+ebp]"
r110() { p110(); }
