# Master Open Watcom Builder Control file
# =======================================

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ BLOCK <1> boot bootclean ]
#===========================
# NB: The ordering of the following inclusions is significant!
# At the beginning, we only have wmake and builder/pmake
# Start with the ORL and librarian - boot build has no other dependencies
[ INCLUDE <SRCDIR>/orl/builder.ctl ]
[ INCLUDE <SRCDIR>/lib/builder.ctl ]
# Build our version of yacc
[ INCLUDE <SRCDIR>/yacc/builder.ctl ]
# Next build wres and the resource compiler
[ INCLUDE <SRCDIR>/wres/builder.ctl ]
[ INCLUDE <SRCDIR>/rc/rc/builder.ctl ]
# Build wstrip and wsplice
[ INCLUDE <SRCDIR>/builder/builder.ctl ]
[ INCLUDE <SRCDIR>/strip/builder.ctl ]
# Continue with the linker
[ INCLUDE <SRCDIR>/dwarf/builder.ctl ]
[ INCLUDE <SRCDIR>/link/builder.ctl ]
# Now we also have everything to build wasm and owcc
[ INCLUDE <SRCDIR>/wasm/builder.ctl ]
[ INCLUDE <SRCDIR>/cl/builder.ctl ]
# Build the 16-bit and 32-bit x86 compilers
[ INCLUDE <SRCDIR>/cfloat/builder.ctl ]
[ INCLUDE <SRCDIR>/cg/intel/386/builder.ctl ]
[ INCLUDE <SRCDIR>/cg/intel/i86/builder.ctl ]
[ INCLUDE <SRCDIR>/cc/386/builder.ctl ]
[ INCLUDE <SRCDIR>/cc/i86/builder.ctl ]
[ INCLUDE <SRCDIR>/plusplus/boot386.ctl ]
[ INCLUDE <SRCDIR>/plusplus/booti86.ctl ]
# Build RISC assemblers
[ INCLUDE <SRCDIR>/owl/builder.ctl ]
[ INCLUDE <SRCDIR>/re2c/builder.ctl ]
[ INCLUDE <SRCDIR>/as/builder.ctl ]

# The following tools are not required during build
# Build our vi editor and the libs it requires
[ INCLUDE <SRCDIR>/ncurses/builder.ctl ]
[ INCLUDE <SRCDIR>/ui/builder.ctl ]
[ INCLUDE <SRCDIR>/vi/builder.ctl ]
# Build miscellaneous utilities
[ INCLUDE <SRCDIR>/disasm/builder.ctl ]
[ INCLUDE <SRCDIR>/dump/builder.ctl ]
[ INCLUDE <SRCDIR>/dmpobj/builder.ctl ]
[ INCLUDE <SRCDIR>/orl/test/builder.ctl ]
[ INCLUDE <SRCDIR>/dwarf/util/builder.ctl ]
[ INCLUDE <SRCDIR>/hlpview/builder.ctl ]

[ BLOCK <1> build rel clean ]
#============================
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
[ INCLUDE <SRCDIR>/rtdll/builder.ctl ]
# Now we have enough to start cross building everything else

# Start with the libs used by various tools
[ INCLUDE <SRCDIR>/orl/builder.ctl ]
[ INCLUDE <SRCDIR>/owl/builder.ctl ]
[ INCLUDE <SRCDIR>/dwarf/builder.ctl ]
[ INCLUDE <SRCDIR>/cfloat/builder.ctl ]
# Continue with the assemblers/librarian/linker
[ INCLUDE <SRCDIR>/wasm/builder.ctl ]
[ INCLUDE <SRCDIR>/as/builder.ctl ]
[ INCLUDE <SRCDIR>/lib/builder.ctl ]
[ INCLUDE <SRCDIR>/link/builder.ctl ]
# On to the compilers
# Continue with SDK tools
[ INCLUDE <SRCDIR>/sdk/builder.ctl ]

[ BLOCK . . ]
#============
cdsay .
