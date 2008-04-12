# WRES Builder Control file
# =========================

set PROJDIR=<CWD>
set PROJNAME=wres

[ INCLUDE <OWROOT>/build/master.ctl ]
[ LOG <LOGFNAME>.<LOGEXT> ]

cdsay .

set BOOTCOPY=

[ INCLUDE <OWROOT>/build/defrule.ctl ]

[ BLOCK . . ]
#============

cdsay <PROJDIR>
