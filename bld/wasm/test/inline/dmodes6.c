int     x;
#pragma aux pinit0=".486p"
#pragma aux p01 = "mov dx,word ptr [bx]"
r01() { p01(); }
#pragma aux p02 = "mov dx,word ptr [si]"
r02() { p02(); }
#pragma aux p04 = "mov dx,word ptr [di]"
r04() { p04(); }
#pragma aux p06 = "mov dx,word ptr +0H[bp]"
r06() { p06(); }
#pragma aux p08 = "mov dx,word ptr [bx+si]"
r08() { p08(); }
#pragma aux p10 = "mov dx,word ptr [bx+di]"
r10() { p10(); }
#pragma aux p12 = "mov dx,word ptr [bp+si]"
r12() { p12(); }
#pragma aux p14 = "mov dx,word ptr [bp+di]"
r14() { p14(); }
#pragma aux p16 = "mov dx,word ptr -0fH[bx]"
r16() { p16(); }
#pragma aux p18 = "mov dx,word ptr -0fH[si]"
r18() { p18(); }
#pragma aux p20 = "mov dx,word ptr -0fH[di]"
r20() { p20(); }
#pragma aux p22 = "mov dx,word ptr -0fH[bp]"
r22() { p22(); }
#pragma aux p24 = "mov dx,word ptr -0fH[bx+si]"
r24() { p24(); }
#pragma aux p26 = "mov dx,word ptr -0fH[bx+di]"
r26() { p26(); }
#pragma aux p28 = "mov dx,word ptr -0fH[bp+si]"
r28() { p28(); }
#pragma aux p30 = "mov dx,word ptr -0fH[bp+di]"
r30() { p30(); }
#pragma aux p32 = "mov edx,dword ptr [bx]"
r32() { p32(); }
#pragma aux p34 = "mov edx,dword ptr [si]"
r34() { p34(); }
#pragma aux p36 = "mov edx,dword ptr [di]"
r36() { p36(); }
#pragma aux p38 = "mov edx,dword ptr +0H[bp]"
r38() { p38(); }
#pragma aux p40 = "mov edx,dword ptr [bx+si]"
r40() { p40(); }
#pragma aux p42 = "mov edx,dword ptr [bx+di]"
r42() { p42(); }
#pragma aux p44 = "mov edx,dword ptr [bp+si]"
r44() { p44(); }
#pragma aux p46 = "mov edx,dword ptr [bp+di]"
r46() { p46(); }
#pragma aux p48 = "mov edx,dword ptr -0fH[bx]"
r48() { p48(); }
#pragma aux p50 = "mov edx,dword ptr -0fH[si]"
r50() { p50(); }
#pragma aux p52 = "mov edx,dword ptr -0fH[di]"
r52() { p52(); }
#pragma aux p54 = "mov edx,dword ptr -0fH[bp]"
r54() { p54(); }
#pragma aux p56 = "mov edx,dword ptr -0fH[bx+si]"
r56() { p56(); }
#pragma aux p58 = "mov edx,dword ptr -0fH[bx+di]"
r58() { p58(); }
#pragma aux p60 = "mov edx,dword ptr -0fH[bp+si]"
r60() { p60(); }
#pragma aux p62 = "mov edx,dword ptr -0fH[bp+di]"
r62() { p62(); }
