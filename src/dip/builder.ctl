# DIP Builder Control file
# ========================

set PROJDIR=<CWD>

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

[ INCLUDE dwarf/builder.ctl ]
[ INCLUDE codeview/builder.ctl ]
[ INCLUDE watcom/builder.ctl ]
[ INCLUDE export/builder.ctl ]
[ INCLUDE mapsym/builder.ctl ]
