.chap Introduction

This document serves as an introduction and a guide for developers of
the Open Watcom compilers and tools. It is not particularly useful for
the users (who are also developers) of Open Watcom compilers &mdash
they are encouraged to read the User's Guide, Programmer's Guide,
C Language Reference and other user oriented books.
.np
It should not be assumed that this book is in anyway final or the
ultimate reference. Readers are encouraged to add, change and modify it
to better reflect evolution of the Open Watcom project.

.section History
.*
.np
.ix 'history'
.ix 'WATFOR'
The history of the Open Watcom project is rather long, in terms of
Interned years it would probably span millennia. The origins can be
traced back to 1965. That summer a team of undergraduate students
at the University of Waterloo develped a FORTRAN compiler (called
WATFOR) that ran on the University's IBM 7040 systems. The compiler
was soon ported to IBM 360 and later to the famous DEC PDP-11.
.np
.ix 'WATFOR-77'
In early 1980's a brand new version of the compiler was created
that supported the FORTRAN 77 language. It ran on two platforms,
the IBM 370 and the emerging IBM PC. The PC version of WATFOR-77
was finished in 1985 and in the same year support for Japanese was
added. In 1986, WATFOR-77 was ported to the QNX operating system.
.np
In parallel to the FORTRAN compilers Watcom developed optimizing
C compilers. When the first PC version (Watcom C 6.0) was introduced
in 1987, it immediately attracted attention by producing faster code
than other compilers available at that time.
.np
In 1988 work started on an advanced highly optimizing code generator
that supported both the C language and FORTRAN and was portable across
multiple platforms. Generation of tight code, availability on multiple
platforms (DOS, Windows, OS/2 and Windows NT in one package) and the
ability to cross-compile made Watcom C and C++ compilers quite popular
in mid-1990s. Around 1994-1996, nearly all DOS games were developed
with Watcom C.
.np
Watcom International, Inc. had other successful products besides its
highly acclaimed compilers. VX-REXX was a popular GUI RAD tool for
OS/2 and Watcom SQL was a cross-platform "embeddable" SQL database.
.np
In 1996 Watcom International, Inc. was acquired by PowerSoft, the maker
of Power++, PowerDesigner and other GUI RAD tools for the Windows
platform. PowerSoft used Watcom compiler technology as a back-end for
their GUI tools.
.np
But the Watcom compilers did not spend very long time in the custodianship
of PowerSoft because in 1997, PowerSoft was acquired by Sybase, Inc.,
a major database vendor. Sybase was primarily interested in database
oriented RAD tools and also in Watcom SQL which was enhanced and turned
into Sybase SQL Anywhere.
.np
Sybase continued to sell Watcom C/C++ and FORTRAN compilers version 11 but
it was obvious that Sybase couldn't compete with Microsoft. Sybase decided
to end-of-life the Watcom compilers effective 2000.
.np
But that's not the end of the story. Many customers did not want to give
up the Watcom compilers because there was no suitable replacement in many
areas. One of these customers was Kendall Bennett of SciTech Software, Inc.
SciTech entered into negotiations with Sybase and in an unprecedented move,
Sybase agreed upon open sourcing the Watcom compilers and tools. One of
the reasons why this was possible at all was the fact that Watcom had very
little reliance on third-party tools and developed practically everything
in-house, from YACC to IDE.
.np
The process of opening the source was longer than originally anticipated
(all software related projects tend to work out this way for some
inexplicable reason) but in the first half of 2002, the source was finally
made available under the Sybase Open Watcom Public License version 1.0.


.section Guided Tour
.*
.np
This section is a guided tour of the Open Watcom source tree, presenting
an overview of its structure and highlighting some of the more memorable
sights.
.np
The Open Watcom directory structure mostly mirrors the layout used by
the Watcom/Sybase build server but attempts to clean it up, straighten
out and unify. The original build process partially relied on fixed
pathnames and fixed locations in relation to the root of the build drive
(which was more or less fixed at D:). Most of the dependencies have been
removed and the rest should be eradicated soon.
.np
The root of the Open Watcom directory tree can be in the root of
any drive (if your OS uses drive letters) or in any directory, for
instance
.id e:\openwatcom.
.np
The main subdirectories in the Open Watcom root are the following:
.begnote
.note bat
currently contains mostly useless batch files and several useful ones.
One extremely important file lives here:
.us makeinit.
This file controls the operation of wmake and is the key to understanding
of the build process. Since wmake looks for
.us makeinit
along the
.id PATH,
the
us bat
directory must be placed at or near the start of your
.id PATH
environment variable.
.note bin, binp
contains miscellaneous binaries used in the build process.
.note bld
is
.us the
directory where it's at. It contains all the Open Watcom source code. It is
so important (and huge) that it deserves its own section.
.note docs
contains source files for the Open Watcom documentation as well as binaries
needed to translate the sources into PostScript, HTML or various online
help formats. The source files of this document are stored under this directory.
For more information please refer the the chapter entitled Documentation
later in this manual.
.note rel2
is the "release" directory is where the binaries and other files produced
as a result of the build process end up. The structure of this directory
mirrors the
.us WATCOM
directory of a typical Open Watcom installation.
.endnote


.section The bld directory
.*
.np
.ix 'bld'
Following is a brief description of all subdirectories of bld. Each subdirectory
roughly corresponds to one "project". There's a lot of projects!
.begnote
.note as
the Alpha AXP and PowerPC assembler. The x86 assembler lives separately.
.note aui
user interface library employed by the debugger.
.note bdiff
binary diff and patch utilities.
.note bin
some projects place built binaries here, particularly the debugger related ones.
.note brinfo
part of the C++ source browser.
.note browser
the GUI C++ source browser.
.note build
directory holding build related files such as binaries used internally during
build process and several master make include files. Important!
.note builder
builder tool controlled by those
.us lang.ctl
files that are all over the place.
.note cc
the C compiler front end.
.note cfloat
utility function for conversion between various floating point binary formats.
.note cg
Open Watcom code generators, the heart of the compilers. These are shared by
all languages (C, C++, FORTRAN). Currently supported targets are 16-bit and
32-bit x86 as well as Alpha AXP.
.note clib
the C runtime library. Pretty big project in itself.
.note cmdedit
command line editing utilities, pretty much obsolete.
.note comp_cfg
compiler configuration header files for various targets.
.note cpp
a simple C style preprocessor.
.note cvpack
the CV pack utility (for CodeView style debugging information).
.note diff
Open Watcom version of the popular utility.
.note dig
files used by debugger.
.note dip
Debug Information Processors, used by debugger.
.note dmpobj
a simple OMF dump utility.
.note dwarf
library for reading and writing DWARF style debugging information.
.note editdll
bridges between the IDE and external editors.
.note emu
80387 emulator library.
.note emu86
8087 emulator library.
.note f77
FORTRAN 77 compiler front end, runtime library and samples. All the
FORTRAN stuff is crowded in there.
.note fe_misc
miscellaneous compiler front-end stuff.
.note fmedit
form edit library, part of the SDK tools.
.note graphlib
Open Watcom graphics library for DOS.
.note gui
GUI library.
.note hdr
source files of header files distributed with the compilers.
.note help
character mode help viewer (WHELP).
.note idebatch
batch processor for the IDE.
.note lib_misc
shared library.
.note mad
Machine Architecture Definition used by debufgger.
.note mathlib
the math library.
.note misc
stuff that didn't fit anywhere else.
.note mstools
Microsoft clone tools, front ends for compilers and utilities.
.note ndisasm
the "new" disassembler.
.note nwlib
the "new" librarian.
.note online
place for finished online help files and associated header files.
.note orl
Object Reader Library, reads OMF, COFF and ELF object files.
.note owl
Object Writer Library, brother of the above.
.note pgchart
presentation graphics and chart library for DOS.
.note plusplus
another huge directory containing all C++ stuff. Compiler, runtime
libraries, all that.
.note plustest
C++ regression test utilities.
.note pmake
parallel make, tool used in the build process to roughly control
what gets built.
.note posix
a bunch of POSIX utilites like cp, rm and so on.
.note rtdll
C runtime DLLs.
.note sdk
SDK tools like resource editor, resource compiler or dialog editor.
.note src
sample source code distributed with the compiler.
.note sweep
a simple utility that walks subdirectories and performs specified
action in each.
.note techinfo
ancient system information utility.
.note trap
trap files (both local and remote), the heart of the debugger containing
platform specific debugging code.
.note trmem
memory tracker library (good for plugging memory leaks).
.note ui
user interface library.
.note vi
Open Watcom vi editor, clone of the (not so) popular Unix editor.
.note viper
the Open Watcom IDE.
.note viprdemo
IDE demo program.
.note w32loadr
loaders for OS independent (OSI) binaries.
.note wasm
the x86 assembler.
.note watcom
contains internal headers and libraries shared by many projects.
.note wclass
an Open Watcom C++ class library.
.note wdisasm
disassembler supporting a variety of object formats and instruction
sets.
.note whpcvt
Watcom Help Converter used for producing online documentation.
.note wic
utility for converting include files between various languages.
.note win386
the Windows 386 extender.
.note wl
the Open Watcom linker.
.note wmake
the make utility.
.note womp
Watcom Object Module Processor, primarily for conversion between
debug info formats.
.note wpack
simple file compression/decompression utility.
.note wpi
macros and helper functions for facilitating development of Windows
and OS/2 GUI programs from single source code.
.note wprof
the Open Watcom profiler.
.note wsample
the execution sampler, companion tool to the profiler.
.note wsplice
splice utility for text file processing.
.note wstrip
strip utility for detaching or attaching debug information and/or
resources.
.note wstub
stub program for DOS/4GW.
.note wtouch
a touch utility.
.note wv
the debugger (used to be called WVIDEO, hence the name).
.note yacc
Watcom's version of YACC used for building compilers/assemblers.
.endnote
.np
As you can see, there's a lot of stuff! Some of these projects
contain specific documentation pertaining to them. For the most
part, the best documentation is the source code.
