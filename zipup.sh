#! /bin/sh
RELEASE=1.1.0
LABEL=open_watcom_$RELEASE
PREFIX=open_watcom_$RELEASE
P4OPT=-f
P4PORT=-pp4.scitechsoft.com:3488
ARCHIVES=/archives
cd $ARCHIVES
rm -f *.bz2

#############################################################################
# Archive all Open Watcom source files
rm -rf $ACHIVES/ow_src
p4 $P4PORT -uanonymous -Panonymous -cOPENWATCOM_SRC sync $P4OPT @$LABEL
cd $ARCHIVES/ow_src
tar -cv * | bzip2 -9 > ../$PREFIX-src.tar.bz2

cd ~/ow

