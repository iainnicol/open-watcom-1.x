# Master Open Watcom Builder Control file
# =======================================

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

echo Build host: <BLD_HOST>

cdsay .

[ BLOCK <1> boot bootclean ]
#===========================
# Build Open Watcom tools using the host platform's native compiler.
#
# NB: The ordering of the following inclusions is significant!
# At the beginning, we only have wmake and builder/pmake
# Start with the ORL and librarian - boot build has no other dependencies
[ INCLUDE <SRCDIR>/orl/builder.ctl ]
[ INCLUDE <SRCDIR>/lib/builder.ctl ]
# Build our version of yacc
[ INCLUDE <SRCDIR>/yacc/builder.ctl ]
# If necessary, build POSIX tools (awk, sed, cp, ...)
[ IFDEF <BLD_HOST> OS2 NT DOS ]
[ INCLUDE <SRCDIR>/posix/builder.ctl ]
[ INCLUDE <SRCDIR>/awk/builder.ctl ]
[ ENDIF ]
# Build wsplice and genverrc
[ INCLUDE <SRCDIR>/builder/builder.ctl ]
# Next build wres and the resource compiler
[ INCLUDE <SRCDIR>/wres/builder.ctl ]
[ INCLUDE <SRCDIR>/rc/rc/builder.ctl ]
# Build wstrip
[ INCLUDE <SRCDIR>/strip/builder.ctl ]
# Continue with the linker
[ INCLUDE <SRCDIR>/dwarf/dw/builder.ctl ]
[ INCLUDE <SRCDIR>/link/builder.ctl ]
[ INCLUDE <SRCDIR>/link/exe2bin/builder.ctl ]
# Now we also have everything to build wasm and owcc
[ INCLUDE <SRCDIR>/wasm/builder.ctl ]
[ INCLUDE <SRCDIR>/cl/builder.ctl ]
# Build the 16-bit and 32-bit x86 compilers
[ INCLUDE <SRCDIR>/cfloat/builder.ctl ]
[ INCLUDE <SRCDIR>/cg/intel/386/builder.ctl ]
[ INCLUDE <SRCDIR>/cg/intel/i86/builder.ctl ]
[ INCLUDE <SRCDIR>/cc/386/builder.ctl ]
[ INCLUDE <SRCDIR>/cc/i86/builder.ctl ]
[ INCLUDE <SRCDIR>/plusplus/386/builder.ctl ]
[ INCLUDE <SRCDIR>/plusplus/i86/builder.ctl ]
# Build RISC assemblers
[ INCLUDE <SRCDIR>/owl/builder.ctl ]
[ INCLUDE <SRCDIR>/re2c/builder.ctl ]
[ INCLUDE <SRCDIR>/as/builder.ctl ]
# Now miscellaneous utilities required during build
[ INCLUDE <SRCDIR>/omftools/builder.ctl ]
[ INCLUDE <SRCDIR>/ssl/builder.ctl ]
[ INCLUDE <SRCDIR>/win386/wbind/builder.ctl ]
[ INCLUDE <SRCDIR>/causeway/cwc/builder.ctl ]
[ INCLUDE <SRCDIR>/parsedlg/builder.ctl ]
[ INCLUDE <SRCDIR>/vi/ctl/builder.ctl ]
[ INCLUDE <SRCDIR>/vi/bind/builder.ctl ]

# The following tools are not required during build
[ INCLUDE <SRCDIR>/disasm/builder.ctl ]
[ INCLUDE <SRCDIR>/dump/builder.ctl ]
[ INCLUDE <SRCDIR>/dmpobj/builder.ctl ]
[ INCLUDE <SRCDIR>/orl/test/builder.ctl ]
[ INCLUDE <SRCDIR>/dwarf/util/builder.ctl ]
# Debugger/profiler libraries
[ INCLUDE <SRCDIR>/dip/builder.ctl ]
[ INCLUDE <SRCDIR>/mad/builder.ctl ]

[ IFDEF <BLD_HOST> UNIX ]
#========================
# Build UNIX specific utilities using native tools.
# 
# Build our vi editor and the libs it requires
[ INCLUDE <SRCDIR>/ncurses/builder.ctl ]
[ INCLUDE <SRCDIR>/ui/unix/builder.ctl ]
[ INCLUDE <SRCDIR>/vi/builder.ctl ]
[ INCLUDE <SRCDIR>/hlpview/builder.ctl ]
# Build gui/aui lib and the profiler
[ INCLUDE <SRCDIR>/gui/ui/builder.ctl ]
[ INCLUDE <SRCDIR>/aui/builder.ctl ]
[ INCLUDE <SRCDIR>/profiler/builder.ctl ]
[ ENDIF ]

[ BLOCK <1> build rel clean ]
#============================
# Build all of Open Watcom using freshly built tools.
#
# NB: Again, the order is significant.
# At the beginning, assume to have compilers/assemblers/librarian/linker
# running on the host platform, but not necessarily anything else.
# Start with language and API headers
[ INCLUDE <SRCDIR>/hdr/builder.ctl ]
[ INCLUDE <SRCDIR>/os2api/builder.ctl ]
[ INCLUDE <SRCDIR>/w16api/builder.ctl ]
[ INCLUDE <SRCDIR>/w32api/builder.ctl ]
# Continue with runtime libraries.
[ INCLUDE <SRCDIR>/emu87/builder.ctl ]
[ INCLUDE <SRCDIR>/emu387/builder.ctl ]
[ INCLUDE <SRCDIR>/mathlib/builder.ctl ]
[ INCLUDE <SRCDIR>/clib/builder.ctl ]
[ INCLUDE <SRCDIR>/cpplib/builder.ctl ]
[ INCLUDE <SRCDIR>/rtdll/builder.ctl ]
[ INCLUDE <SRCDIR>/win386/builder.ctl ]
[ INCLUDE <SRCDIR>/graphlib/builder.ctl ]
# Now we have enough to start cross building everything else

# Start with the libs used by various tools
[ INCLUDE <SRCDIR>/wres/builder.ctl ]
[ INCLUDE <SRCDIR>/orl/builder.ctl ]
[ INCLUDE <SRCDIR>/owl/builder.ctl ]
[ INCLUDE <SRCDIR>/dwarf/builder.ctl ]
[ INCLUDE <SRCDIR>/cfloat/builder.ctl ]
# Continue with the assemblers/librarian/linker/make
[ INCLUDE <SRCDIR>/wasm/builder.ctl ]
[ INCLUDE <SRCDIR>/as/builder.ctl ]
[ INCLUDE <SRCDIR>/lib/builder.ctl ]
[ INCLUDE <SRCDIR>/link/builder.ctl ]
[ INCLUDE <SRCDIR>/make/builder.ctl ]
# On to the compilers
[ INCLUDE <SRCDIR>/cg/intel/386/builder.ctl ]
[ INCLUDE <SRCDIR>/cg/intel/i86/builder.ctl ]
[ INCLUDE <SRCDIR>/cg/risc/axp/builder.ctl ]
[ INCLUDE <SRCDIR>/cg/risc/ppc/builder.ctl ]
[ INCLUDE <SRCDIR>/cg/risc/mps/builder.ctl ]
[ INCLUDE <SRCDIR>/cc/builder.ctl ]
[ INCLUDE <SRCDIR>/plusplus/builder.ctl ]
# Libraries which the SDK tools use
[ INCLUDE <SRCDIR>/wpi/builder.ctl ]
[ INCLUDE <SRCDIR>/commonui/builder.ctl ]
# Continue with SDK tools
[ INCLUDE <SRCDIR>/sdk/builder.ctl ]
[ INCLUDE <SRCDIR>/rc/rc/builder.ctl ]
[ INCLUDE <SRCDIR>/rc/builder.ctl ]
# Now miscellaneous command line tools
[ INCLUDE <SRCDIR>/rc/builder.ctl ]
[ INCLUDE <SRCDIR>/disasm/builder.ctl ]
[ INCLUDE <SRCDIR>/dump/builder.ctl ]
[ INCLUDE <SRCDIR>/dmpobj/builder.ctl ]
[ INCLUDE <SRCDIR>/cl/builder.ctl ]
[ INCLUDE <SRCDIR>/strip/builder.ctl ]
# User interface libs
[ INCLUDE <SRCDIR>/ncurses/builder.ctl ]
[ INCLUDE <SRCDIR>/ui/builder.ctl ]
[ INCLUDE <SRCDIR>/gui/builder.ctl ]
[ INCLUDE <SRCDIR>/aui/builder.ctl ]
# The vi(w) editor
[ INCLUDE <SRCDIR>/rcsdll/builder.ctl ]
[ INCLUDE <SRCDIR>/vi/builder.ctl ]
# Build the debugger and sampler
[ INCLUDE <SRCDIR>/dip/builder.ctl ]
[ INCLUDE <SRCDIR>/mad/builder.ctl ]
[ INCLUDE <SRCDIR>/dbg/builder.ctl ]
[ INCLUDE <SRCDIR>/trap/builder.ctl ]
[ INCLUDE <SRCDIR>/sampler/builder.ctl ]
# Other GUI tools
[ INCLUDE <SRCDIR>/profiler/builder.ctl ]
[ INCLUDE <SRCDIR>/wclass/builder.ctl ]
# IDE currently disabled due to wgml dependency
# [ INCLUDE <SRCDIR>/ide/builder.ctl ]

[ BLOCK . . ]
#============
cdsay .
