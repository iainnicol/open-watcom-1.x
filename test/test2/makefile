.CONTINUE
.IGNORE

cmd_file = test_tmp.cmd

objs = &
a &
adc &
arithop &
asmbug &
asmbug1 &
b &
bar &
bitwise &
bunk &
c &
dasm &
dup &
enter &
fadd &
foo &
fubar &
help &
imul &
j2 &
jmp &
jnk &
label &
new &
old1 &
ptrtest &
reljmp &
reljmp16 &
scal &
struct &
stupid &
t &
t01 &
t03 &
t06 &
t07 &
t08 &
t09 &
t10 &
t13 &
t14 &
t15 &
t16 &
t17 &
t18 &
t19 &
t20 &
t21 &
t23 &
t24 &
t25 &
t26 &
t27 &
t28 &
t29 &
t30 &
t31 &
t32 &
t33 &
t34 &
t35 &
t36 &
t37 &
t38 &
t39 &
t51 &
test &
timer

dev_objs = &
data &
jmptst &
old2 &
set386 &
setjmp &
t02 &
t04 &
t05 &
t11 &
t12 &
t22 &
tmp

!ifndef asm
asm=wasm -q -zld
!endif

all : $(cmd_file) $(objs) $(dev_objs)
	@call $(cmd_file)

$(cmd_file) : .SYMBOLIC
!ifndef asm
asm=wasm
!endif
	@%create $(cmd_file)
	@%write $(cmd_file) @echo off
	@%write $(cmd_file) @echo %1.asm ======================================================
	@%write $(cmd_file) @$(asm) %1.asm -q
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
