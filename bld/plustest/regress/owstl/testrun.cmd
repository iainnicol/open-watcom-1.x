pushd
wmake -h global
wmake -h
wmake -h global
wmake -h test1=
wmake -h global
wmake -h test2=
wmake -h global
wmake -h test3=
wmake -h global
wmake -h test4=
wmake -h global
wmake -h test5=
if [%extra_arch%] == [] goto no_extra
wmake -h global
wmake -h arch=%extra_arch%
wmake -h global
wmake -h test1= arch=%extra_arch%
wmake -h global
wmake -h test2= arch=%extra_arch%
wmake -h global
wmake -h test3= arch=%extra_arch%
wmake -h global
wmake -h test4= arch=%extra_arch%
wmake -h global
wmake -h test5= arch=%extra_arch%
:no_extra
wmake -h global
popd
