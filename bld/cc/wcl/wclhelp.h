/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:  Usage help for wcl.
*
****************************************************************************/


#ifdef WCLAXP
E("Usage:  wclaxp [options] file(s)")
J("Usage:  wclaxp [options] file(s)")
#elif defined(WCL386)
E("Usage:  wcl386 [options] file(s)")
J("Usage:  wcl386 [options] file(s)")
#else
E("Usage:  wcl [options] file(s)")
J("Usage:  wcl [options] file(s)")
#endif
#ifndef __UNIX__
E("Options:  ( /option is also accepted )")
J("Options:  ( /option is also accepted )")
#endif
E("-c    compile only, no link")
J("-c    compile only, no link")
E("-cc   treat source files as C code")
J("-cc   treat source files as C code")
E("-cc++ treat source files as C++ code")
J("-cc++ treat source files as C++ code")
#ifdef WCLAXP
E("-y    ignore the WCLAXP environment variable")
J("-y    ignore the WCLAXP environment variable")
#elif defined(WCL386)
E("-y    ignore the WCL386 environment variable")
J("-y    ignore the WCL386 environment variable")
#else
E("-y    ignore the WCL environment variable")
J("-y    ignore the WCL environment variable")
#endif
#ifdef WCL386
E("[Processor options]")
J("[Processor options]")
E("-3r 386 register calling conventions")
J("-3r 386 register calling conventions")
E("-3s 386 stack calling conventions")
J("-3s 386 stack calling conventions")
E("-4r 486 register calling conventions")
J("-4r 486 register calling conventions")
E("-4s 486 stack calling conventions")
J("-4s 486 stack calling conventions")
E("-5r Pentium register calling conv.")
J("-5r Pentium register calling conv.")
E("-5s Pentium stack calling conventions")
J("-5s Pentium stack calling conventions")
E("-6r Pentium Pro register call conven.")
J("-6r Pentium Pro register call conven.")
E("-6s Pentium Pro stack call conven.")
J("-6s Pentium Pro stack call conven.")
#elif defined(WCLI86)
E("[Processor options]")
J("[Processor options]")
E("-0 generate code for 8086 or higher")
J("-0 generate code for 8086 or higher")
E("-1 generate code for 186 or higher")
J("-1 generate code for 186 or higher")
E("-2 generate code for 286 or higher")
J("-2 generate code for 286 or higher")
E("-3 generate code for 386 or higher")
J("-3 generate code for 386 or higher")
E("-4 generate code optimized for 486")
J("-4 generate code optimized for 486")
E("-5 generate code optimized for Pentium")
J("-5 generate code optimized for Pentium")
E("-6 generate code opt. for Pentium Pro")
J("-6 generate code opt. for Pentium Pro")
#endif
#if defined(WCLI86) || defined(WCL386)
E("[Floating-point processor options]")
J("[Floating-point processor options]")
E("-fpc calls to floating-point library")
J("-fpc calls to floating-point library")
E("-fpd enable Pentium FDIV check")
J("-fpd enable Pentium FDIV check")
E("-fpi   inline 80x87 with emulation")
J("-fpi   inline 80x87 with emulation")
E("-fpi87 inline 80x87")
J("-fpi87 inline 80x87")
E("-fpr use old floating-point conventions")
J("-fpr use old floating-point conventions")
E("-fp2 generate 287 floating-point code")
J("-fp2 generate 287 floating-point code")
E("-fp3 generate 387 floating-point code")
J("-fp3 generate 387 floating-point code")
E("-fp5 optimize f-p for Pentium")
J("-fp5 optimize f-p for Pentium")
E("-fp6 optimize f-p for Pentium Pro")
J("-fp6 optimize f-p for Pentium Pro")
#endif
E("[Compiler options]")
J("[Compiler options]")
E("-db generate browsing information")
J("-db generate browsing information")
E("-e=<n> set error limit number")
J("-e=<n> set error limit number")
E("-ee call epilogue hook routine")
J("-ee call epilogue hook routine")
E("-ef full paths in messages")
J("-ef full paths in messages")
E("-ei force enums to be type int")
J("-ei force enums to be type int")
E("-em minimum base type for enum is int")
J("-em minimum base type for enum is int")
E("-en emit routine names in the code")
J("-en emit routine names in the code")
E("-ep[=<n>] call prologue hook routine")
J("-ep[=<n>] call prologue hook routine")
E("-eq do not display error messages")
J("-eq do not display error messages")
#ifdef WCL386
E("-et P5 profiling")
J("-et P5 profiling")
E("-ez generate PharLap EZ-OMF object")
J("-ez generate PharLap EZ-OMF object")
#endif
E("-fh=<file> pre-compiled headers")
J("-fh=<file> pre-compiled headers")
E("-fhq[=<file>] fh without warnings")
J("-fhq[=<file>] fh without warnings")
E("-fhr  (C++) only read PCH")
J("-fhr  (C++) only read PCH")
E("-fhw  (C++) only write PCH")
J("-fhw  (C++) only write PCH")
E("-fhwe (C++) don't count PCH warnings")
J("-fhwe (C++) don't count PCH warnings")
E("-fi=<file> force include of file")
J("-fi=<file> force include of file")
E("-fo=<file> set object file name")
J("-fo=<file> set object file name")
E("-fr=<file> set error file name")
J("-fr=<file> set error file name")
E("-ft (C++) check for 8.3 file names")
J("-ft (C++) check for 8.3 file names")
E("-fx (C++) no check for 8.3 file names")
J("-fx (C++) no check for 8.3 file names")
#if defined(WCLI86) || defined(WCL386)
E("-g=<codegroup> set code group name")
J("-g=<codegroup> set code group name")
#endif
E("-hc codeview debug format")
J("-hc codeview debug format")
E("-hd dwarf debug format")
J("-hd dwarf debug format")
E("-hw watcom debug format")
J("-hw watcom debug format")
E("-j  change char default to signed")
J("-j  change char default to signed")
#ifdef WCL386
E("-m{f,s,m,c,l}  memory model")
J("-m{f,s,m,c,l}  memory model")
#elif defined(WCLP16)
E("-m{t,s,m,c,l,h,p}  memory model")
J("-m{t,s,m,c,l,h,p}  memory model")
#elif defined(WCLI86)
E("-m{t,s,m,c,l,h}  memory model")
J("-m{t,s,m,c,l,h}  memory model")
#endif
#if defined(WCLI86) || defined(WCL386)
E("-nc=<name>  set CODE class name")
J("-nc=<name>  set CODE class name")
E("-nd=<name>  set data segment name")
J("-nd=<name>  set data segment name")
E("-nm=<module_name> set module name")
J("-nm=<module_name> set module name")
E("-nt=<name>  set text segment name")
J("-nt=<name>  set text segment name")
E("-r  save/restore segregs across calls")
J("-r  save/restore segregs across calls")
#endif
E("-ri promote function args/rets to int")
J("-ri promote function args/rets to int")
E("-s  remove stack overflow checks")
J("-s  remove stack overflow checks")
#if defined(WCLI86) || defined(WCL386)
E("-sg generate calls to grow the stack")
J("-sg generate calls to grow the stack")
E("-st touch stack through SS first")
J("-st touch stack through SS first")
#endif
E("-v  output func declarations to .def")
J("-v  output func declarations to .def")
E("-vcap VC++ compat: alloca in arg lists")
J("-vcap VC++ compat: alloca in arg lists")
E("-w=<n>  set warning level number")
J("-w=<n>  set warning level number")
E("-wcd=<n> disable warning message <n>")
J("-wcd=<n> disable warning message <n>")
E("-wce=<n> enable warning message <n>")
J("-wce=<n> enable warning message <n>")
E("-we treat all warnings as errors")
J("-we treat all warnings as errors")
E("-wx (C++) set warning level to max")
J("-wx (C++) set warning level to max")
#if defined(WCLI86)
E("-wo diagnose problems in overlaid code")
J("-wo diagnose problems in overlaid code")
#endif
E("-xr (C++) enable RTTI")
J("-xr (C++) enable RTTI")
E("-z{a,e} disable/enable extensions")
J("-z{a,e} disable/enable extensions")
E("-zc place strings in CODE segment")
J("-zc place strings in CODE segment")
#if defined(WCLI86) || defined(WCL386)
E("-zd{f,p} DS floats vs DS pegged to DGROUP")
J("-zd{f,p} DS floats vs DS pegged to DGROUP")
#ifdef WCL386
E("-zdl load DS directly from DGROUP")
J("-zdl load DS directly from DGROUP")
#endif
E("-zf{f,p} FS floats vs FS pegged to seg")
J("-zf{f,p} FS floats vs FS pegged to seg")
E("-zg{f,p} GS floats vs GS pegged to seg")
J("-zg{f,p} GS floats vs GS pegged to seg")
#endif
E("-zg function prototype using base type")
J("-zg function prototype using base type")
E("-zk{0,0u,1,2,3,l} double-byte support")
J("-zk{0,0u,1,2,3,l} double-byte support")
E("-zku=<codepage> UNICODE support")
J("-zku=<codepage> UNICODE support")
E("-zl  remove default library information")
J("-zl  remove default library information")
E("-zld remove file dependency information")
J("-zld remove file dependency information")
E("-zm  place functions in separate segments")
J("-zm  place functions in separate segments")
E("-zmf (C++) zm with near calls allowed")
J("-zmf (C++) zm with near calls allowed")
// obosolete #ifdef WCL386
// obosolete E("-zo (C++) O/S-based exception handling")
// obosolete J("-zo (C++) O/S-based exception handling")
// obosolete #endif
E("-zp{1,2,4,8,16} struct packing align.")
J("-zp{1,2,4,8,16} struct packing align.")
E("-zpw warning when padding a struct")
J("-zpw warning when padding a struct")
E("-zq operate quietly")
J("-zq operate quietly")
E("-zs check syntax only")
J("-zs check syntax only")
E("-zt<n> set data threshold")
J("-zt<n> set data threshold")
#if defined(WCLI86) || defined(WCL386)
E("-zu SS != DGROUP")
J("-zu SS != DGROUP")
#endif
E("-zv (C++) enable virt. fun. removal opt")
J("-zv (C++) enable virt. fun. removal opt")
#ifdef WCL386
E("-zw  generate code for MS Windows")
J("-zw  generate code for MS Windows")
#endif
#ifdef WCLI86
E("-zW  zw with efficient entry sequences")
J("-zW  zw with efficient entry sequences")
E("-zws -zw with smart callbacks")
J("-zws -zw with smart callbacks")
E("-zWs -zW with smart callbacks")
J("-zWs -zW with smart callbacks")
#endif
#ifdef WCL386
E("-zz remove @size from __stdcall func.")
J("-zz remove @size from __stdcall func.")
#endif
E("[Debugging options]")
J("[Debugging options]")
E("-d0 no debugging information" )
J("-d0 no debugging information" )
E("-d1{+} line number debugging info.")
J("-d1{+} line number debugging info.")
E("-d2 full symbolic debugging info.")
J("-d2 full symbolic debugging info.")
E("-d2i (C++) d2 + inlines as COMDATs")
J("-d2i (C++) d2 + inlines as COMDATs")
E("-d2s (C++) d2 + inlines as statics")
J("-d2s (C++) d2 + inlines as statics")
E("-d2t (C++) d2 but without type names")
J("-d2t (C++) d2 but without type names")
E("-d3 debug info with unref'd type names")
J("-d3 debug info with unref'd type names")
E("-d3i (C++) d3 + inlines as COMDATs")
J("-d3i (C++) d3 + inlines as COMDATs")
E("-d3s (C++) d3 + inlines as statics")
J("-d3s (C++) d3 + inlines as statics")
E("[Optimization options]")
J("[Optimization options]")
E("-oa relax alias checking")
J("-oa relax alias checking")
#if defined(WCLI86) || defined(WCL386)
E("-ob branch prediction")
J("-ob branch prediction")
E("-oc disable call/ret optimization")
J("-oc disable call/ret optimization")
#endif
E("-od disable optimizations")
J("-od disable optimizations")
E("-oe[=num] expand functions inline")
J("-oe[=num] expand functions inline")
#if defined(WCLI86) || defined(WCL386)
E("-of[+] generate traceable stack frames")
J("-of[+] generate traceable stack frames")
#endif
E("-oh enable repeated optimizations")
J("-oh enable repeated optimizations")
E("-oi inline intrinsic functions")
J("-oi inline intrinsic functions")
E("-oi+ (C++) oi with max inlining depth")
J("-oi+ (C++) oi with max inlining depth")
E("-ok control flow entry/exit seq.")
J("-ok control flow entry/exit seq.")
E("-ol perform loop optimizations")
J("-ol perform loop optimizations")
E("-ol+ ol with loop unrolling")
J("-ol+ ol with loop unrolling")
#if defined(WCLI86) || defined(WCL386)
E("-om generate inline math functions")
J("-om generate inline math functions")
#endif
E("-on numerically unstable floating-point")
J("-on numerically unstable floating-point")
E("-oo continue compile when low on memory")
J("-oo continue compile when low on memory")
#if defined(WCLI86) || defined(WCL386)
E("-op improve floating-point consistency")
J("-op improve floating-point consistency")
#endif
E("-or re-order instructions to avoid stalls")
J("-or re-order instructions to avoid stalls")
E("-os optimize for space")
J("-os optimize for space")
E("-ot optimize for time")
J("-ot optimize for time")
E("-ou ensure unique addresses for functions")
J("-ou ensure unique addresses for functions")
#if defined(WCLAXP)
E("-ox maximum optimization (-oilr -s)")
J("-ox maximum optimization (-oilr -s)")
#elif defined(WCLI86) || defined(WCL386)
E("-ox maximum optimization (-obmiler -s)")
J("-ox maximum optimization (-obmiler -s)")
#endif
E("[C++ exception handling options]")
E("-xd  no exception handling")
J("-xd  no exception handling")
E("-xds no exception handling: space")
J("-xds no exception handling: space")
E("-xdt no exception handling")
J("-xdt no exception handling")
E("-xs  exception handling: balanced")
J("-xs  exception handling: balanced")
E("-xss exception handling: space")
J("-xss exception handling: space")
E("-xst exception handling: time")
J("-xst exception handling: time")
E("[Preprocessor options]")
J("[Preprocessor options]")
E("-d<name>[=text] define a macro")
J("-d<name>[=text] define a macro")
E("-d+ extend syntax of -d option")
J("-d+ extend syntax of -d option")
E("-fo=<filename> set object file name")
J("-fo=<filename> set object file name")
E("-i=<directory>  include directory")
J("-i=<directory>  include directory")
E("-t=<n> (C++) # of spaces in tab stop")
J("-t=<n> (C++) # of spaces in tab stop")
E("-tp=<name> (C) set #pragma on( <name>")
J("-tp=<name> (C) set #pragma on( <name>")
E("-u<name>  undefine macro name")
J("-u<name>  undefine macro name")
E("-p{c,l,w=<n>} preprocess source file")
E("   c     -> preserve comments")
E("   l     -> insert #line directives")
E("   w=<n> -> wrap output at column n")
J("-p{c,l,w=<n>} preprocess source file")
J("   c     -> preserve comments")
J("   l     -> insert #line directives")
J("   w=<n> -> wrap output at column n")
E("[Linker options]")
J("[Linker options]")
E("-bd  build Dynamic link library")
J("-bd  build Dynamic link library")
E("-bm  build Multi-thread application")
J("-bm  build Multi-thread application")
E("-br  build with dll run-time library")
J("-br  build with dll run-time library")
E("-bw  build default Windowing app.")
J("-bw  build default Windowing app.")
E("-bt=<os> build target OS.")
J("-bt=<os> build target OS.")
E("-fd[=<directive_file>] directive file")
J("-fd[=<directive_file>] directive file")
E("-fe=<executable> name executable file")
J("-fe=<executable> name executable file")
E("-fm[=<map_file>]  generate map file")
J("-fm[=<map_file>]  generate map file")
E("-k<stack_size> set stack size")
J("-k<stack_size> set stack size")
#ifdef WCLI86
E("-lp create an OS/2 protected-mode pgm")
J("-lp create an OS/2 protected-mode pgm")
E("-lr create a DOS real-mode program")
J("-lr create a DOS real-mode program")
#endif
E("-l=<system> link for the specified system")
J("-l=<system> link for the specified system")
E("-x  make names case sensitive")
J("-x  make names case sensitive")
E("@<directive_file> include file")
J("@<directive_file> include file")
E("-\"<linker directives>\"")
J("-\"<linker directives>\"")
