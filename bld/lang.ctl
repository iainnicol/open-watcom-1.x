# --------------------------------------------------------------------

[ INCLUDE <LANG_BLD>/master.ctl ]
[ LOG <DEVDIR>/<LOGFNAME>.<LOGEXT> ]

set FULLBUILD=1

cdsay .

echo Languages Build: <1> <2> <3>

[ BLOCK <BUILDMODE> bootstrap ]
#================================
echo Bootstrapping compiler using GNU tools...
[ INCLUDE <DEVDIR>/langlnx.ctl ]

[ BLOCK . . ]
#
#        First of all build prerequisite utilities used in the build
#
[ INCLUDE <DEVDIR>/builder/lang.ctl ]
[ INCLUDE <DEVDIR>/pmake/lang.ctl ]
[ INCLUDE <DEVDIR>/cc/wcl/prereq.ctl ]
[ INCLUDE <DEVDIR>/yacc/lang.ctl ]
[ INCLUDE <DEVDIR>/re2c/lang.ctl ]
[ INCLUDE <DEVDIR>/whpcvt/lang.ctl ]
[ INCLUDE <DEVDIR>/helpcomp/lang.ctl ]
[ INCLUDE <DEVDIR>/bmp2eps/lang.ctl ]
[ INCLUDE <DEVDIR>/ssl/lang.ctl ]
[ INCLUDE <DEVDIR>/wstub/lang.ctl ]
[ INCLUDE <DEVDIR>/vi/prereq.ctl ]
#        Prebuild new WLIB for build process
[ INCLUDE <DEVDIR>/nwlib/prereq.ctl ]
[ INCLUDE <DEVDIR>/posix/prereq.ctl ]
#
#        Prebuild newest WASM version for build process
[ INCLUDE <DEVDIR>/wasm/prereq.ctl ]
#
#        Before building anything for real, create up-to-date header files
#
[ INCLUDE <DEVDIR>/hdr/lang.ctl ]
#        Same for OS/2 and Win32 headers/import libs
[ INCLUDE <DEVDIR>/os2api/lang.ctl ]
[ INCLUDE <DEVDIR>/w32api/lang.ctl ]
#        Same for Win16 headers/import libs
[ INCLUDE <DEVDIR>/w16api/lang.ctl ]
#
#        Next step, build libraries used by various projects
#
#        RC builds resource file libraries for everybody
[ INCLUDE <DEVDIR>/fmedit/lang.ctl ]
#        BWPI needs to be done before BSDK
[ INCLUDE <DEVDIR>/wpi/lang.ctl ]
#        BSDK must be done after BDISASM ?
[ INCLUDE <DEVDIR>/sdk/lang.ctl ]
#        Librarys for different Programs as next
[ INCLUDE <DEVDIR>/aui/lang.ctl ]
#        BWPI must be done before BSDK and hui, dui and lui
[ INCLUDE <DEVDIR>/gui/lang.ctl ]
[ INCLUDE <DEVDIR>/wclass/lang.ctl ]
[ INCLUDE <DEVDIR>/ncurses/lang.ctl ]
#        UI can be deferred until VI is to be built. W.Briscoe 2004-11-25
[ INCLUDE <DEVDIR>/ui/lang.ctl ]
#        OWL/ORL must be done early so that clients are up-to-date
[ INCLUDE <DEVDIR>/owl/lang.ctl ]
#        BAS must be done after BOWL but before BCFE
[ INCLUDE <DEVDIR>/as/lang.ctl ]
[ INCLUDE <DEVDIR>/orl/lang.ctl ]
#        BDWARF must be done early so that DWARF library users are up-to-date
[ INCLUDE <DEVDIR>/dwarf/lang.ctl ]
#
#        Now build Open Watcom libraries
#
#        emu libraries must be made before C libraries
[ INCLUDE <DEVDIR>/emu/lang.ctl ]
[ INCLUDE <DEVDIR>/emu86/lang.ctl ]
#        C libraries must be made after linker
[ INCLUDE <DEVDIR>/lib_misc/lang.ctl ]
[ INCLUDE <DEVDIR>/clib/lang.ctl ]
[ INCLUDE <DEVDIR>/mathlib/lang.ctl ]
[ INCLUDE <DEVDIR>/cfloat/lang.ctl ]
[ INCLUDE <DEVDIR>/win386/lang.ctl ]
#        src must be made after the C library
[ INCLUDE <DEVDIR>/src/lang.ctl ]
#        graphics library must be made after C library
[ INCLUDE <DEVDIR>/graphlib/lang.ctl ]
[ INCLUDE <DEVDIR>/nwlib/lang.ctl ]
#        BRCSDLL must be before BVI and BVIPER
[ INCLUDE <DEVDIR>/rcsdll/lang.ctl ]
#
#       Then build the compilers
#
#       BW32LDR must be done before EXE's that use the loader
[ INCLUDE <DEVDIR>/w32loadr/lang.ctl ]
#
#        Starting with the code generators
#
#        BWOMP must be done before BWASM and F77, now it is not necessary
#[ INCLUDE <DEVDIR>/womp/lang.ctl ]
#        BWASM must be done early so that inline assembler users are up-to-date
#        now it is not necessary, it can be anywhere
[ INCLUDE <DEVDIR>/wasm/lang.ctl ]
[ INCLUDE <DEVDIR>/cg/lang.ctl ]
#        c front ends must be built after code generator
[ INCLUDE <DEVDIR>/cc/lang.ctl ]
[ INCLUDE <DEVDIR>/cc/wcl/lang.ctl ]
[ INCLUDE <DEVDIR>/plusplus/lang.ctl ]
[ INCLUDE <DEVDIR>/fe_misc/lang.ctl ]
#        FORTRAN 77 compilers must be built after code generators
#        flib & flib286 get built with f77
[ INCLUDE <DEVDIR>/f77/lang.ctl ]
[ INCLUDE <DEVDIR>/f77/samples/lang.ctl ]
[ INCLUDE <DEVDIR>/wl/lang.ctl ]
#
#        Now we can build the C++ libraries - must be done after C library
#        as well as after the C++ compilers
#
[ INCLUDE <DEVDIR>/plusplus/cpplib/lang.ctl ]
#        rtdll must be made after all other libraries
[ INCLUDE <DEVDIR>/rtdll/lang.ctl ]
#
#        Now let's build the utilities and other stuff
#
[ INCLUDE <DEVDIR>/vi/lang.ctl ]
[ INCLUDE <DEVDIR>/wdisasm/lang.ctl ]
[ INCLUDE <DEVDIR>/ndisasm/lang.ctl ]
[ INCLUDE <DEVDIR>/bdiff/lang.ctl ]
[ INCLUDE <DEVDIR>/misc/lang.ctl ]
[ INCLUDE <DEVDIR>/techinfo/lang.ctl ]
[ INCLUDE <DEVDIR>/help/lang.ctl ]
[ INCLUDE <DEVDIR>/cmdedit/lang.ctl ]
[ INCLUDE <DEVDIR>/brinfo/lang.ctl ]
[ INCLUDE <DEVDIR>/trap/lang.ctl ]
[ INCLUDE <DEVDIR>/dip/lang.ctl ]
[ INCLUDE <DEVDIR>/mad/lang.ctl ]
[ INCLUDE <DEVDIR>/wv/lang.ctl ]
[ INCLUDE <DEVDIR>/wsample/lang.ctl ]
[ INCLUDE <DEVDIR>/wprof/lang.ctl ]
[ INCLUDE <DEVDIR>/wmake/lang.ctl ]
[ INCLUDE <DEVDIR>/wtouch/lang.ctl ]
[ INCLUDE <DEVDIR>/wstrip/lang.ctl ]
[ INCLUDE <DEVDIR>/editdll/lang.ctl ]
[ INCLUDE <DEVDIR>/browser/lang.ctl ]
[ INCLUDE <DEVDIR>/idebatch/lang.ctl ]
[ INCLUDE <DEVDIR>/viper/lang.ctl ]
[ INCLUDE <DEVDIR>/viper/bviper/lang.ctl ]
[ INCLUDE <DEVDIR>/mstools/lang.ctl ]
[ INCLUDE <DEVDIR>/viprdemo/lang.ctl ]
[ INCLUDE <DEVDIR>/online/lang.ctl ]
[ INCLUDE <DEVDIR>/posix/lang.ctl ]
[ INCLUDE <DEVDIR>/cpp/lang.ctl ]
[ INCLUDE <DEVDIR>/pgchart/lang.ctl ]
[ INCLUDE <DEVDIR>/dig/lang.ctl ]
[ INCLUDE <DEVDIR>/uiforms/lang.ctl ]
[ INCLUDE <DEVDIR>/watcom/lang.ctl ]
[ INCLUDE <DEVDIR>/pbide/lang.ctl ]
[ INCLUDE <DEVDIR>/trmem/lang.ctl ]
#[ INCLUDE <DEVDIR>/version/lang.ctl ]
[ INCLUDE <DEVDIR>/dmpobj/lang.ctl ]
[ INCLUDE <DEVDIR>/wpack/lang.ctl ]
[ INCLUDE <DEVDIR>/cvpack/lang.ctl ]
[ INCLUDE <DEVDIR>/wic/lang.ctl ]
[ INCLUDE <DEVDIR>/redist/lang.ctl ]
[ INCLUDE <DOC_ROOT>/lang.ctl ]

# deal with the project which contains this file last --- the BAT directory
# BATDIR Builder Control file
# ===========================
[ INCLUDE <LANG_BLD>/wproj.ctl ]

# Do CDSAY to see end time
cdsay .

