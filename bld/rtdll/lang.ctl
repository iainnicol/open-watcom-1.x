# Builder Control file
# ==========================

set PROJDIR=<CWD>

[ INCLUDE <LANG_BLD>/master.ctl ]
[ INCLUDE <LANG_BLD>/wproj.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

[ BLOCK <1> build rel2 ]
#=======================
    pmake -d build dynamic .not <2> <3> <4> <5> <6> <7> <8> <9> -h
    cdsay <PROJDIR>


[ BLOCK <1> rel2 cprel2 acprel2 ]
#================================
  [ IFDEF (os_os2 "") <2*> ]
    <CPCMD> clib/os2.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/os2/clbrdll.lib
    <CPCMD> clib/os2.386/ms_r/clbr*.dll <RELROOT>/rel2/binp/dll/
    <CPCMD> clib/os2.386/ms_r/clbr*.sym <RELROOT>/rel2/binp/dll/
    <CPCMD> clib/os2.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/os2/clbsdll.lib
    <CPCMD> clib/os2.386/ms_s/clbs*.dll <RELROOT>/rel2/binp/dll/
    <CPCMD> clib/os2.386/ms_s/clbs*.sym <RELROOT>/rel2/binp/dll/

    <CPCMD> mathlib/os2.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/os2/mthrdll.lib
    <CPCMD> mathlib/os2.386/ms_r/mthr*.dll <RELROOT>/rel2/binp/dll/
    <CPCMD> mathlib/os2.386/ms_r/mthr*.sym <RELROOT>/rel2/binp/dll/
    <CPCMD> mathlib/os2.387/ms_r/clib.lib <RELROOT>/rel2/lib386/os2/mt7rdll.lib
    <CPCMD> mathlib/os2.387/ms_r/mt7r*.dll <RELROOT>/rel2/binp/dll/
    <CPCMD> mathlib/os2.387/ms_r/mt7r*.sym <RELROOT>/rel2/binp/dll/
    <CPCMD> mathlib/os2.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/os2/mthsdll.lib
    <CPCMD> mathlib/os2.386/ms_s/mths*.dll <RELROOT>/rel2/binp/dll/
    <CPCMD> mathlib/os2.386/ms_s/mths*.sym <RELROOT>/rel2/binp/dll/
    <CPCMD> mathlib/os2.387/ms_s/clib.lib <RELROOT>/rel2/lib386/os2/mt7sdll.lib
    <CPCMD> mathlib/os2.387/ms_s/mt7s*.dll <RELROOT>/rel2/binp/dll/
    <CPCMD> mathlib/os2.387/ms_s/mt7s*.sym <RELROOT>/rel2/binp/dll/

    <CPCMD> cpplib/os2.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/os2/plbrdll.lib
    <CPCMD> cpplib/os2.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/os2/plbrdllx.lib
    <CPCMD> cpplib/os2.386/ms_r/plbr*.dll <RELROOT>/rel2/binp/dll/
    <CPCMD> cpplib/os2.386/ms_r/plbr*.sym <RELROOT>/rel2/binp/dll/
    <CPCMD> cpplib/os2.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/os2/plbsdll.lib
    <CPCMD> cpplib/os2.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/os2/plbsdllx.lib
    <CPCMD> cpplib/os2.386/ms_s/plbs*.dll <RELROOT>/rel2/binp/dll/
    <CPCMD> cpplib/os2.386/ms_s/plbs*.sym <RELROOT>/rel2/binp/dll/

    #<CPCMD> wrtlib/os2.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/os2/wrtrdll.lib
    #<CPCMD> wrtlib/os2.386/ms_r/wrtr*.dll <RELROOT>/rel2/binp/dll/
    #<CPCMD> wrtlib/os2.386/ms_r/wrtr*.sym <RELROOT>/rel2/binp/dll/
    #<CPCMD> wrtlib/os2.387/ms_r/clib3r.lib <RELROOT>/rel2/lib386/os2/wr7rdll.lib
    #<CPCMD> wrtlib/os2.387/ms_r/wr7r*.dll <RELROOT>/rel2/binp/dll/
    #<CPCMD> wrtlib/os2.387/ms_r/wr7r*.sym <RELROOT>/rel2/binp/dll/
    #<CPCMD> wrtlib/os2.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/os2/wrtsdll.lib
    #<CPCMD> wrtlib/os2.386/ms_s/wrts*.dll <RELROOT>/rel2/binp/dll/
    #<CPCMD> wrtlib/os2.386/ms_s/wrts*.sym <RELROOT>/rel2/binp/dll/
    #<CPCMD> wrtlib/os2.387/ms_s/clib3s.lib <RELROOT>/rel2/lib386/os2/wr7sdll.lib
    #<CPCMD> wrtlib/os2.387/ms_s/wr7s*.dll <RELROOT>/rel2/binp/dll/
    #<CPCMD> wrtlib/os2.387/ms_s/wr7s*.sym <RELROOT>/rel2/binp/dll/

  [ IFDEF (os_nt "") <2*> ]
    <CPCMD> clib/winnt.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/nt/clbrdll.lib
    <CPCMD> clib/winnt.386/ms_r/clbr*.dll <RELROOT>/rel2/binnt/
    <CPCMD> clib/winnt.386/ms_r/clbr*.sym <RELROOT>/rel2/binnt/
    <CPCMD> clib/winnt.386/ms_rp/clib3r.lib <RELROOT>/rel2/lib386/nt/clbrpdll.lib
    <CPCMD> clib/winnt.386/ms_rp/clbrp*.dll <RELROOT>/rel2/binnt/
    <CPCMD> clib/winnt.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/nt/clbsdll.lib
    <CPCMD> clib/winnt.386/ms_s/clbs*.dll <RELROOT>/rel2/binnt/
    <CPCMD> clib/winnt.386/ms_s/clbs*.sym <RELROOT>/rel2/binnt/

    <CPCMD> mathlib/winnt.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/nt/mthrdll.lib
    <CPCMD> mathlib/winnt.386/ms_r/mthr*.dll <RELROOT>/rel2/binnt/
    <CPCMD> mathlib/winnt.386/ms_r/mthr*.sym <RELROOT>/rel2/binnt/
    <CPCMD> mathlib/winnt.387/ms_r/clib.lib <RELROOT>/rel2/lib386/nt/mt7rdll.lib
    <CPCMD> mathlib/winnt.387/ms_r/mt7r*.dll <RELROOT>/rel2/binnt/
    <CPCMD> mathlib/winnt.387/ms_r/mt7r*.sym <RELROOT>/rel2/binnt/
    <CPCMD> mathlib/winnt.386/ms_rp/clib3r.lib <RELROOT>/rel2/lib386/nt/mthrpdll.lib
    <CPCMD> mathlib/winnt.386/ms_rp/mthrp*.dll <RELROOT>/rel2/binnt/
    <CPCMD> mathlib/winnt.387/ms_rp/clib.lib <RELROOT>/rel2/lib386/nt/mt7rpdll.lib
    <CPCMD> mathlib/winnt.387/ms_rp/mt7rp*.dll <RELROOT>/rel2/binnt/
    <CPCMD> mathlib/winnt.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/nt/mthsdll.lib
    <CPCMD> mathlib/winnt.386/ms_s/mths*.dll <RELROOT>/rel2/binnt/
    <CPCMD> mathlib/winnt.386/ms_s/mths*.sym <RELROOT>/rel2/binnt/
    <CPCMD> mathlib/winnt.387/ms_s/clib.lib <RELROOT>/rel2/lib386/nt/mt7sdll.lib
    <CPCMD> mathlib/winnt.387/ms_s/mt7s*.dll <RELROOT>/rel2/binnt/
    <CPCMD> mathlib/winnt.387/ms_s/mt7s*.sym <RELROOT>/rel2/binnt/

    <CPCMD> cpplib/winnt.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/nt/plbrdll.lib
    <CPCMD> cpplib/winnt.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/nt/plbrdllx.lib
    <CPCMD> cpplib/winnt.386/ms_r/plbr*.dll <RELROOT>/rel2/binnt/
    <CPCMD> cpplib/winnt.386/ms_r/plbr*.sym <RELROOT>/rel2/binnt/
    <CPCMD> cpplib/winnt.386/ms_rp/clib3r.lib <RELROOT>/rel2/lib386/nt/plbrpdll.lib
    <CPCMD> cpplib/winnt.386/ms_rp/plbrp*.dll <RELROOT>/rel2/binnt/
    <CPCMD> cpplib/winnt.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/nt/plbsdll.lib
    <CPCMD> cpplib/winnt.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/nt/plbsdllx.lib
    <CPCMD> cpplib/winnt.386/ms_s/plbs*.dll <RELROOT>/rel2/binnt/
    <CPCMD> cpplib/winnt.386/ms_s/plbs*.sym <RELROOT>/rel2/binnt/

    #<CPCMD> wrtlib/winnt.386/ms_r/clib3r.lib <RELROOT>/rel2/lib386/nt/wrtrdll.lib
    #<CPCMD> wrtlib/winnt.386/ms_r/wrtr*.dll <RELROOT>/rel2/binnt/
    #<CPCMD> wrtlib/winnt.386/ms_r/wrtr*.sym <RELROOT>/rel2/binnt/
    #<CPCMD> wrtlib/winnt.387/ms_r/clib3r.lib <RELROOT>/rel2/lib386/nt/wr7rdll.lib
    #<CPCMD> wrtlib/winnt.387/ms_r/wr7r*.dll <RELROOT>/rel2/binnt/
    #<CPCMD> wrtlib/winnt.387/ms_r/wr7r*.sym <RELROOT>/rel2/binnt/
    #<CPCMD> wrtlib/winnt.386/ms_s/clib3s.lib <RELROOT>/rel2/lib386/nt/wrtsdll.lib
    #<CPCMD> wrtlib/winnt.386/ms_s/wrts*.dll <RELROOT>/rel2/binnt/
    #<CPCMD> wrtlib/winnt.386/ms_s/wrts*.sym <RELROOT>/rel2/binnt/
    #<CPCMD> wrtlib/winnt.387/ms_s/clib3s.lib <RELROOT>/rel2/lib386/nt/wr7sdll.lib
    #<CPCMD> wrtlib/winnt.387/ms_s/wr7s*.dll <RELROOT>/rel2/binnt/
    #<CPCMD> wrtlib/winnt.387/ms_s/wr7s*.sym <RELROOT>/rel2/binnt/

[ BLOCK <1> clean ]
#==================
    pmake -d build <2> <3> <4> <5> <6> <7> <8> <9> -h clean
    cdsay <PROJDIR>
