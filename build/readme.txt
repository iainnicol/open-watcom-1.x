 Build System Notes
 ==================

 The Version 2 build system is not all that new. For the most part, it uses
the exact same tools but updated makefiles and build scripts.

 OBJECTIVE: Make the build system portable and flexible, allowing builds on
a variety of platforms using different compilers.

 This is, in itself, a non-trivial task. The major challenge is the number
of differences between tools on various platforms. The differences are
twofold: Firstly the tools used for driving the build process, secondly the
compilers and libraries used.

 There are two major classes of host platforms: UNIX style and DOS style.
The former includes eg. Mac OS X, the latter Windows or OS/2. In general,
UNIX style platforms offer a considerably richer set of tools. On DOS style
platforms, we supply our own UNIX style tools. This includes sed and awk.

 The build system also uses a number of custom Watcom tools, starting with
wmake. The wmake utility was a natural choice, but it is also fairly portable
and has special support for Watcom tools (DLL tools, autodependencies). We
also control the source code, which means no one can spring a surprise on us.

 The build system uses an interesting combination of top-down and bottom-up
approach. The makefiles are built bottom-up, with each output leaf directory
containing a file called 'makefile' which includes a number of other files.
This ensures that wmake can be manually run in specific directories to
quickly rebuild a specific tool or library.

 The overall build system is driven by builder and pmake. Builder is a simple
scripting tool whose main purpose is to conditionally execute external
commands, while pmake can execute a simple command in any number of
subdirectories that match a specific combination of keywords.

 This approach was chosen because the default build includes cross compilation
to a number of platforms. This is different from 99.9% of software projects.

 The subprojects in the source tree could be roughly divided into two classes:
projects that can be built for the host platform and projects that must be
cross compiled. The former class includes the compilers and linker, the latter
includes runtime libraries.

 These two classes of projects have significantly different build requirements.
Projects buildable on host need to be buildable with non-Watcom tools, but
must of course be possible to cross build using Open Watcom tools. Projects
that are intended for cross compilation only need to be only buildable with
Watcom tools, and may rely on many Open Watcom specific features.

 One of the objectives is to support builds even on platforms not supported
by the Open Watcom tools, for example Mac OS X. This requires first building
the Open Watcom tools with a third party compiler (eg. GCC), then continuing
the build using the newly built Watcom tools.

 A somewhat muddled situation occurs when an earlier Open Watcom version is
used for the build. In this case, the we have to very very carefully control
which tools, headers, and libraries are used. For example the C runtime (clib)
always must be built against fresh headers, and the C++ runtime also must
be built using a fresh C++ compiler. For most tools (eg. the C compiler) it
does not matter much which headers and libs we use, as the code needs to be
fairly portable anyway.

 NB: The V2 build will probably use a bootstrap approach in all cases, ie.
first build uptodate tools and then rebuild the cross compiled targets using
these tools. This strategy is very flexible and allows us to add new features
easily - although it can also be somewhat fragile and we have to be careful
not to diverge too far from the last stable release.
