.CONTINUE
.IGNORE

cmd_file = test_tmp.cmd

objs = &
387 &
a &
alias &
anon &
b &
backquot &
beep &
bigext &
bug &
bunk &
c &
cmps &
comm &
current &
data &
dosinite &
do_ax &
dup &
empty &
error &
f &
farjmp &
fcom &
five &
float &
foo &
g &
getenv &
hello &
ifs &
include &
ins &
irp &
jmpext &
jmpfword &
jmpsize &
jmptst &
kyb &
l2 &
l3 &
labelbug &
lods &
maaak &
macro &
macroloc &
macrotst &
mainnew &
mangle &
masmsuks &
masmtest &
movs &
new &
newbug &
newmif &
offset &
org &
orgage &
outs &
passtest &
proc &
proc3 &
pub &
pub2 &
pubdef &
q &
qnxstrt &
quote &
scas &
segoff &
shell &
size &
sizebug &
sizebug2 &
stos &
strmang &
struct &
structjn &
tmp &
tn &
wincall &
word &
x &
xx

dev_objs = &
alignorg &
anthony &
bar &
dos16m &
dosstart &
fubar &
jmp &
loader2 &
main &
newproc &
notcomm &
t2 &
test

asm_flags_x = -c

!ifndef asm
asm=wasm -q -zld
!endif 

count=1

all : $(cmd_file) $(objs) $(dev_objs)
	@call $(cmd_file)

$(cmd_file) : .SYMBOLIC
!ifndef asm
asm=wasm
!endif 
	@%create $(cmd_file)
	@%write $(cmd_file) @echo off
	@%write $(cmd_file) @echo %1.asm ======================================================
	@%write $(cmd_file) @$(asm) %1.asm -q >null
	@%write $(cmd_file) @if not exist %1.err goto next1
	@%write $(cmd_file) @if not exist %1.chk goto next2
        @%write $(cmd_file) @bdiff -b %1.err %1.chk
	@%write $(cmd_file) goto next1
	@%write $(cmd_file) :next2
	@%write $(cmd_file) type %1.err
	@%write $(cmd_file) :next1
	@for %x in ($(objs)) do @call $(cmd_file) %x

debug : .SYMBOLIC
	@%create $(cmd_file)
	@%write $(cmd_file) @echo off

$(objs) : .SYMBOLIC
	@%append $(cmd_file) @echo $^@.asm ======================================================
	@%append $(cmd_file) @$(asm) $(asm_flags_$^@) $^@.asm >$^@.tmp 2>&1
	@%append $(cmd_file) @if not exist $^@.chk goto next$^@a
        @%append $(cmd_file) @diff -b $^@.tmp $^@.chk
	@%append $(cmd_file) goto next$^@c
	@%append $(cmd_file) :next$^@a
	@%append $(cmd_file) type $^@.tmp
	@%append $(cmd_file) :next$^@c
	@%append $(cmd_file) @if not exist $^@.obj goto next$^@d
	@%append $(cmd_file) @wdis -l=$^@.dis -a $^@.obj
	@%append $(cmd_file) @if not exist $^@.esm goto next$^@b
        @%append $(cmd_file) @diff -b $^@.dis $^@.esm
	@%append $(cmd_file) :next$^@b
	@%append $(cmd_file) @dmpobj -q -l -rec=FIXUPP $^@.obj
	@%append $(cmd_file) @if not exist $^@.emp goto next$^@d
        @%append $(cmd_file) @diff -b $^@.lst $^@.emp
	@%append $(cmd_file) :next$^@d

$(dev_objs) : .SYMBOLIC
	@%append $(cmd_file) @echo .
	@%append $(cmd_file) @echo ==============================================================
	@%append $(cmd_file) @echo DEVELOPMENT - $^@.asm 
	@%append $(cmd_file) @echo ==============================================================
	@%append $(cmd_file) @echo .
	@%append $(cmd_file) @$(asm) $(asm_flags_$^@) $^@.asm >$^@.tmp 2>&1
	@%append $(cmd_file) @if not exist $^@.chk goto next$^@a
        @%append $(cmd_file) @diff -b $^@.tmp $^@.chk
	@%append $(cmd_file) goto next$^@c
	@%append $(cmd_file) :next$^@a
	@%append $(cmd_file) type $^@.tmp
	@%append $(cmd_file) :next$^@c
	@%append $(cmd_file) @if not exist $^@.obj goto next$^@d
	@%append $(cmd_file) @wdis -l=$^@.dis -a $^@.obj
	@%append $(cmd_file) @if not exist $^@.esm goto next$^@b
        @%append $(cmd_file) @diff -b $^@.dis $^@.esm
	@%append $(cmd_file) :next$^@b
	@%append $(cmd_file) @dmpobj -q -l -rec=FIXUPP $^@.obj
	@%append $(cmd_file) @if not exist $^@.emp goto next$^@d
        @%append $(cmd_file) @diff -b $^@.lst $^@.emp
	@%append $(cmd_file) :next$^@d

clean : .SYMBOLIC
	rm -f *.obj *.err *.dis *.lst *.tmp test_tmp.cmd mem.trk
