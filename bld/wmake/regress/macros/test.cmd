@echo off
echo # ===========================
echo # Start Macro Test
echo # ===========================

if .%2 == . goto usage

echo # ---------------------------
echo #   Macro Test 1
echo # ---------------------------

rm tmp.out
%1 -ms -h -f MACRO01 > tmp.out 2>&1
diff -b MACRO01.CMP tmp.out
if errorlevel 1 goto err1
    @echo # MACRO01 successful
    goto test2
:err1
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #1 unsuccessful!!! | tee -a %2

:test2

echo # ---------------------------
echo #   Macro Test 2A
echo # ---------------------------

rm tmp.out
%1 -h -f MACRO02 > tmp.out 2>&1
diff -b MACRO02A.CMP tmp.out
if errorlevel 1 goto err2a
    @echo # MACRO02A successful
    goto test2b
:err2a
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #2A unsuccessful!!! | tee -a %2

:test2b
echo # ---------------------------
echo #   Macro Test 2B
echo # ---------------------------

rm tmp.out
%1 -h -ms -f MACRO02 > tmp.out 2>&1
diff -b MACRO02B.CMP tmp.out
if errorlevel 1 goto err2b
    @echo # MACRO02B successful
    goto test3
:err2b
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #2B unsuccessful!!! | tee -a %2

:test3

echo # ---------------------------
echo #   Macro Test 3A
echo # ---------------------------
REM set TRMEM_CODE=3
rm tmp.out
%1 -h -f MACRO03 > tmp.out 2>&1
diff -b MACRO03A.CMP tmp.out
if errorlevel 1 goto err3a
    @echo # MACRO03A successful
    goto test3b
:err3a
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #3A unsuccessful!!! | tee -a %2

:test3b
REM set TRMEM_CODE=1
echo # ---------------------------
echo #   Macro Test 3B
echo # ---------------------------

rm tmp.out
%1 -h -ms -f MACRO03 > tmp.out 2>&1
diff -b MACRO03B.CMP tmp.out
if errorlevel 1 goto err3b
    @echo # MACRO03B successful
    goto test4
:err3b
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #3B unsuccessful!!! | tee -a %2

:test4

echo # ---------------------------
echo #   Macro Test 4A
echo # ---------------------------

rm tmp.out
%1 -h -f MACRO04 > tmp.out 2>&1
diff -b MACRO04A.CMP tmp.out
if errorlevel 1 goto err4a
    @echo # MACRO04A successful
    goto test4b
:err4a
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #4A unsuccessful!!! | tee -a %2

:test4b
echo # ---------------------------
echo #   Macro Test 4B
echo # ---------------------------

rm tmp.out
%1 -h -ms -f MACRO04 > tmp.out 2>&1
diff -b MACRO04B.CMP tmp.out
if errorlevel 1 goto err4b
    @echo # MACRO0r4B successful
    goto test5
:err4b
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #4B unsuccessful!!! | tee -a %2

:test5

echo # ---------------------------
echo #   Macro Test 5
echo # ---------------------------

wtouch hello.boo hello.tmp hello.c
rm tmp.out
%1 -h -ms -f MACRO05 > tmp.out 2>&1
diff -b MACRO05.CMP tmp.out
if errorlevel 1 goto err5
    @echo # MACRO05 successful
    goto test6
:err5
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #5 unsuccessful!!! | tee -a %2

:test6
rm hello.boo hello.tmp hello.c

echo # ---------------------------
echo #   Macro Test 6
echo # ---------------------------

wtouch hello.obj hello2.obj
wtouch hello.c  hello2.c
rm tmp.out
%1 -h -ms -f MACRO06 -a > tmp.out 2>&1
diff -b MACRO06.CMP tmp.out
if errorlevel 1 goto err6
    @echo # MACRO06 successful
    goto test7
:err6
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #6 unsuccessful!!! | tee -a %2

:test7

echo # ---------------------------
echo #   Macro Test 7
echo # ---------------------------

wtouch hello.obj hello2.obj
wtouch hello.c  hello2.c
%1 -h -ms -m -f MACRO07 -a cc=bwcl386 > tmp.out 2>&1
diff -b MACRO07.CMP tmp.out
if errorlevel 1 goto err7
    @echo # MACRO07 successful
    goto test8
:err7
    @echo ## MACRO ## >> %2
    @echo Error: MACRO #7 unsuccessful!!! | tee -a %2

:test8

rm hello.obj hello2.obj hello.boo hello.tmp hello.c hello2.c 
goto done
:usage
echo usage: %0 prgname errorfile
:done
rm tmp.out
