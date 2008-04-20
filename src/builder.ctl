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
[ INCLUDE <SRCDIR>/cc/boot386.ctl ]
[ INCLUDE <SRCDIR>/cc/booti86.ctl ]
# Build RISC assemblers
[ INCLUDE <SRCDIR>/owl/builder.ctl ]
[ INCLUDE <SRCDIR>/re2c/builder.ctl ]
[ INCLUDE <SRCDIR>/as/builder.ctl ]

# Now do our vi editor
[ INCLUDE <SRCDIR>/ncurses/builder.ctl ]
[ INCLUDE <SRCDIR>/ui/builder.ctl ]
[ INCLUDE <SRCDIR>/vi/builder.ctl ]
# Build miscellaneous utilities
[ INCLUDE <SRCDIR>/disasm/builder.ctl ]
[ INCLUDE <SRCDIR>/dump/builder.ctl ]
[ INCLUDE <SRCDIR>/dmpobj/builder.ctl ]
[ INCLUDE <SRCDIR>/orl/test/builder.ctl ]
[ INCLUDE <SRCDIR>/dwarf/util/builder.ctl ]

[ BLOCK . . ]
#============
cdsay .
