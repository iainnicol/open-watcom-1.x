@echo off
rem do some sanity checks here before we start creating gobs of directories
if .%relroot%. == .. goto error
if .%defrel%. == .. goto error
md %relroot%\%defrel%
md %relroot%\%defrel%\n98bw
md %relroot%\%defrel%\binnt
md %relroot%\%defrel%\binp
md %relroot%\%defrel%\binw
md %relroot%\%defrel%\eddat
md %relroot%\%defrel%\h
md %relroot%\%defrel%\qnx
md %relroot%\%defrel%\qnx\binq
md %relroot%\%defrel%\qnx\binq\wd
md %relroot%\%defrel%\qnx\sym
md %relroot%\%defrel%\qnx\sym\wd
md %relroot%\%defrel%\qnx\tix
md %relroot%\%defrel%\qnx\watcom
md %relroot%\%defrel%\qnx\watcom\wd
md %relroot%\%defrel%\h\win
md %relroot%\%defrel%\h\nt
md %relroot%\%defrel%\h\nt\GL
md %relroot%\%defrel%\h\os2
md %relroot%\%defrel%\h\os2\arpa
md %relroot%\%defrel%\h\os2\machine
md %relroot%\%defrel%\h\os2\net
md %relroot%\%defrel%\h\os2\netinet
md %relroot%\%defrel%\h\os2\protocol
md %relroot%\%defrel%\h\os2\sys
md %relroot%\%defrel%\h\os2\GL
md %relroot%\%defrel%\h\os21x
md %relroot%\%defrel%\qh
md %relroot%\%defrel%\qh\sys
md %relroot%\%defrel%\lh
md %relroot%\%defrel%\lh\sys
md %relroot%\%defrel%\lib286
md %relroot%\%defrel%\lib386
md %relroot%\%defrel%\nlm
md %relroot%\%defrel%\samples
md %relroot%\%defrel%\src
md %relroot%\%defrel%\binnt\rtdll
md %relroot%\%defrel%\binp\dll
md %relroot%\%defrel%\binp\help
md %relroot%\%defrel%\h\sys
md %relroot%\%defrel%\lib286\dos
md %relroot%\%defrel%\lib286\os2
md %relroot%\%defrel%\lib286\win
md %relroot%\%defrel%\lib286\qnx
md %relroot%\%defrel%\lib386\dos
md %relroot%\%defrel%\lib386\netware
md %relroot%\%defrel%\lib386\nt
md %relroot%\%defrel%\lib386\os2
md %relroot%\%defrel%\lib386\win
md %relroot%\%defrel%\lib386\qnx
md %relroot%\%defrel%\lib386\linux
md %relroot%\%defrel%\libaxp
md %relroot%\%defrel%\libaxp\nt
md %relroot%\%defrel%\samples\clibexam
md %relroot%\%defrel%\samples\cplbexam
md %relroot%\%defrel%\samples\dll
md %relroot%\%defrel%\samples\goodies
md %relroot%\%defrel%\samples\ide
md %relroot%\%defrel%\samples\win
md %relroot%\%defrel%\samples\clibexam\kanji
md %relroot%\%defrel%\samples\clibexam\test
md %relroot%\%defrel%\samples\cplbexam\complex
md %relroot%\%defrel%\samples\cplbexam\contain
md %relroot%\%defrel%\samples\cplbexam\fstream
md %relroot%\%defrel%\samples\cplbexam\ios
md %relroot%\%defrel%\samples\cplbexam\iostream
md %relroot%\%defrel%\samples\cplbexam\string
md %relroot%\%defrel%\samples\cplbexam\strstrea
md %relroot%\%defrel%\samples\cplbexam\complex\friend
md %relroot%\%defrel%\samples\cplbexam\complex\pubfun
md %relroot%\%defrel%\samples\cplbexam\complex\relfun
md %relroot%\%defrel%\samples\cplbexam\complex\relop
md %relroot%\%defrel%\samples\cplbexam\fstream\fstream
md %relroot%\%defrel%\samples\cplbexam\fstream\ifstream
md %relroot%\%defrel%\samples\cplbexam\fstream\ofstream
md %relroot%\%defrel%\samples\cplbexam\iostream\iostream
md %relroot%\%defrel%\samples\cplbexam\iostream\istream
md %relroot%\%defrel%\samples\cplbexam\iostream\ostream
md %relroot%\%defrel%\samples\cplbexam\string\friend
md %relroot%\%defrel%\samples\cplbexam\string\pubfun
md %relroot%\%defrel%\samples\cplbexam\strstrea\istrstre
md %relroot%\%defrel%\samples\cplbexam\strstrea\ostrstre
md %relroot%\%defrel%\samples\cplbexam\strstrea\strstre
md %relroot%\%defrel%\samples\ide\os2
md %relroot%\%defrel%\samples\ide\win
md %relroot%\%defrel%\samples\ide\win32
md %relroot%\%defrel%\samples\ide\win386
md %relroot%\%defrel%\samples\ide\fortran
md %relroot%\%defrel%\samples\ide\fortran\os2
md %relroot%\%defrel%\samples\ide\fortran\win
md %relroot%\%defrel%\samples\ide\fortran\win32
md %relroot%\%defrel%\samples\ide\fortran\win386
md %relroot%\%defrel%\samples\win\alarm
md %relroot%\%defrel%\samples\win\datactl
md %relroot%\%defrel%\samples\win\edit
md %relroot%\%defrel%\samples\win\generic
md %relroot%\%defrel%\samples\win\helpex
md %relroot%\%defrel%\samples\win\iconview
md %relroot%\%defrel%\samples\win\life
md %relroot%\%defrel%\samples\win\shootgal
md %relroot%\%defrel%\samples\win\watzee
md %relroot%\%defrel%\samples\win\generic\win16
md %relroot%\%defrel%\samples\win\generic\win32
md %relroot%\%defrel%\samples\win\generic\win386
md %relroot%\%defrel%\samples\win\helpex\win16
md %relroot%\%defrel%\samples\win\helpex\win32
md %relroot%\%defrel%\samples\win\helpex\win386
md %relroot%\%defrel%\samples\win\iconview\win16
md %relroot%\%defrel%\samples\win\iconview\win32
md %relroot%\%defrel%\samples\win\iconview\win386
md %relroot%\%defrel%\samples\win\life\win16
md %relroot%\%defrel%\samples\win\life\win32
md %relroot%\%defrel%\samples\win\life\win386
md %relroot%\%defrel%\samples\win\shootgal\win16
md %relroot%\%defrel%\samples\win\shootgal\win32
md %relroot%\%defrel%\samples\win\shootgal\win386
md %relroot%\%defrel%\samples\win\watzee\win16
md %relroot%\%defrel%\samples\win\watzee\win32
md %relroot%\%defrel%\samples\win\watzee\win386
md %relroot%\%defrel%\samples\fortran
md %relroot%\%defrel%\samples\fortran\os2
md %relroot%\%defrel%\samples\fortran\os2\dll
md %relroot%\%defrel%\samples\fortran\os2\rexx
md %relroot%\%defrel%\samples\fortran\win32
md %relroot%\%defrel%\samples\fortran\win
md %relroot%\%defrel%\samples\win\alarm\win16
md %relroot%\%defrel%\samples\win\alarm\win32
md %relroot%\%defrel%\samples\win\alarm\win386
md %relroot%\%defrel%\samples\win\datactl\win386
md %relroot%\%defrel%\samples\fortran\win32\dll
md %relroot%\%defrel%\samples\fortran\win\dll
md %relroot%\%defrel%\samples\win\datactl\win16
md %relroot%\%defrel%\samples\win\datactl\win32
md %relroot%\%defrel%\samples\win\edit\win16
md %relroot%\%defrel%\samples\win\edit\win32
md %relroot%\%defrel%\samples\win\edit\win386
md %relroot%\%defrel%\src\cpplib
md %relroot%\%defrel%\src\editdll
md %relroot%\%defrel%\src\editdll\nt
md %relroot%\%defrel%\src\editdll\nt\cw
md %relroot%\%defrel%\src\editdll\nt\viw
md %relroot%\%defrel%\src\editdll\os2
md %relroot%\%defrel%\src\editdll\win
md %relroot%\%defrel%\src\editdll\win\cw
md %relroot%\%defrel%\src\editdll\win\viw
md %relroot%\%defrel%\src\inc
md %relroot%\%defrel%\src\os2
md %relroot%\%defrel%\src\startup
md %relroot%\%defrel%\src\cpplib\contain
md %relroot%\%defrel%\src\os2\pdd
md %relroot%\%defrel%\src\startup\386
md %relroot%\%defrel%\src\startup\ads
md %relroot%\%defrel%\src\startup\dos
md %relroot%\%defrel%\src\startup\os2
md %relroot%\%defrel%\src\startup\win
md %relroot%\%defrel%\src\fortran
md %relroot%\%defrel%\src\fortran\dos
md %relroot%\%defrel%\src\fortran\win
md %relroot%\%defrel%\src\fortran\ads
md %relroot%\%defrel%\src\fortran\os2
md %relroot%\%defrel%\src\fortran\ads\rel12
goto end
:error
@echo The relroot and defrel environment variables need to be set!
:end
