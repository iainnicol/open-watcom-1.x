'*****************************************************************
' OWCONFIG.VBS - automatically generate batch file to set
' environment variables
'*****************************************************************

WScript.StdOut.WriteLine "Open Watcom Build Configurator"

' Initialize boolean variables for command line switches to the default values.
ShowUsage = False
DebugBuild = False
DefaultWindowing = False
Documentation = True
OutFileName = "myvars.cmd"

' Parse the command line.
For i = 0 To WScript.Arguments.Count - 1
    Select Case WScript.Arguments(i)
    Case "-d", "/d"
        DebugBuild = True
    Case "-w", "/w"
        DefaultWindowing = True
    Case "-n", "/n"
        Documentation = False
    Case Else
        If Left(WScript.Arguments(i), 1) = "-" Or Left(WScript.Arguments(i), 1) = "/" Then
            ShowUsage = True
        Else
            OutFileName = WScript.Arguments(i)
        End If
    End Select
Next

' If there was an invalid command line option, print the usage message.
If ShowUsage Then
    WScript.StdOut.WriteLine "Usage: owconfig [options] [filename] [options]"
    WScript.StdOut.WriteLine "Options:"
    WScript.StdOut.WriteLine "            ( /option is also accepted )"
    WScript.StdOut.WriteLine "-d            debug build"
    WScript.StdOut.WriteLine "-n            suppress documentation build"
    WScript.StdOut.WriteLine "-w            default windowing support in clib"
    WScript.StdOut.WriteLine
Else
    ' Otherwise, do the work.
    ' Check for each needed tool in the path.
    WScript.StdOut.Write "Checking for Open Watcom... "
    OpenWatcomPath = FindFile("wcc386.exe")
    WScript.StdOut.WriteLine OpenWatcomPath
    If Len(OpenWatcomPath) = 0 Then
        WScript.StdOut.WriteLine "You must place the binnt folder of your Open Watcom installation in"
        WScript.StdOut.WriteLine "the PATH environment variable before running owconfig."
        WScript.Quit 1
    End If
    WScript.StdOut.Write "Checking for hcrtf... "
    HcrtfPath = FindFile("hcrtf.exe")
    WScript.StdOut.WriteLine HcrtfPath
    WScript.StdOut.Write "Checking for ipfc... "
    IpfcPath = FindFile("ipfc.exe")
    WScript.StdOut.WriteLine IpfcPath
    
    ' Output a batch file to set the environment.
    Set FSO = CreateObject("Scripting.FileSystemObject")
    Set WshShell = CreateObject("WScript.Shell")
    Set OutFile = FSO.CreateTextFile(OutFileName)
    OutFile.WriteLine "@echo off"
    OutFile.WriteLine "REM *****************************************************************"
    OutFile.WriteLine "REM " + UCase(OutFileName) + " - Windows NT version"
    OutFile.WriteLine "REM *****************************************************************"
    OutFile.WriteLine "REM NOTE: This batch file was automatically generated by owconfig."
    OutFile.WriteLine "REM       DO NOT EDIT!"
    OutFile.WriteLine
    OutFile.WriteLine "set OWROOT=" + WshShell.CurrentDirectory
    OutFile.WriteLine "set WATCOM=" + Left(OpenWatcomPath, InStrRev(OpenWatcomPath, "\") - 1)
    OutFile.WriteLine
    OutFile.WriteLine "REM Set this variable to 1 to get debug build"
    If DebugBuild Then
        OutFile.WriteLine "set DEBUG_BUILD=1"
    Else
        OutFile.WriteLine "set DEBUG_BUILD=0"
    End If
    OutFile.WriteLine
    OutFile.WriteLine "REM Set this variable to 1 to get default windowing support in clib"
    If DefaultWindowing Then
        OutFile.WriteLine "set DEFAULT_WINDOWING=1"
    Else
        OutFile.WriteLine "set DEFAULT_WINDOWING=0"
    End If
    OutFile.WriteLine
    OutFile.WriteLine "REM Set this variable to 0 to suppress documentation build"
    If Documentation Then
        OutFile.WriteLine "set DOC_BUILD=1"
    Else
        OutFile.WriteLine "set DOC_BUILD=0"
    End If
    OutFile.WriteLine
    OutFile.WriteLine "REM Documentation related variables"
    OutFile.WriteLine "set WIN95HC=" + HcrtfPath
    OutFile.WriteLine "set OS2HC=" + IpfcPath
    OutFile.WriteLine
    OutFile.WriteLine "REM Set up default path information variable"
    OutFile.WriteLine "if ""%DEFPATH%"" == """" set DEFPATH=%PATH%"
    OutFile.WriteLine
    OutFile.WriteLine "REM Subdirectory to be used for bootstrapping"
    OutFile.WriteLine "set OBJDIR=bootstrp"
    OutFile.WriteLine
    OutFile.WriteLine "REM Subdirectory to be used for building prerequisite utilities"
    OutFile.WriteLine "set PREOBJDIR=prebuild"
    OutFile.WriteLine
    OutFile.WriteLine "REM Set the version numbers"
    OutFile.WriteLine "call version.bat"
    OutFile.WriteLine
    OutFile.WriteLine "REM Stuff for the Open Watcom build environment"
    OutFile.WriteLine "set BUILD_PLATFORM=nt386"
    OutFile.WriteLine "set BUILDER_CTL=lang.ctl"
    OutFile.WriteLine "set DEVDIR=%OWROOT%\bld"
    OutFile.WriteLine "set OWBINDIR=%DEVDIR%\build\binnt"
    OutFile.WriteLine "set DISTROOT=%OWROOT%\distrib"
    OutFile.WriteLine "set RELROOT=%OWROOT%"
    OutFile.WriteLine "set DWATCOM=%WATCOM%"
    OutFile.WriteLine "set DOC_ROOT=%OWROOT%\docs"
    OutFile.WriteLine "set INCLUDE=%WATCOM%\h;%WATCOM%\h\nt;%DEVDIR%\watcom\h"
    OutFile.WriteLine "set LIB=%OWROOT%\bld\watcom\lib"
    OutFile.WriteLine "set EDPATH=%WATCOM%\eddat"
    OutFile.WriteLine "set PATH=%OWROOT%\bin;%OWBINDIR%;%OWROOT%\bat;%WATCOM%\binnt;%WATCOM%\binw;%WATCOM%\binp;%DOC_ROOT%\cmds;%DEFPATH%"
    OutFile.WriteLine
    OutFile.WriteLine "echo Open Watcom Compiler Build Environment"
    OutFile.WriteLine
    OutFile.WriteLine "REM OS specifics"
    OutFile.WriteLine "cd %DEVDIR%"
    OutFile.WriteLine "set DOS4G=quiet"
    OutFile.WriteLine
    OutFile.WriteLine "REM Set up right COMSPEC for non-standard COMSPEC setting on NT-based systems"
    OutFile.WriteLine "if ""%OS%"" == ""Windows_NT"" set COMSPEC=%WINDIR%\system32\cmd.exe"
    OutFile.WriteLine "set COPYCMD=/y"
    OutFile.Close
End If

Function FindFile(FileName)
'**************************
    Set FSO = CreateObject("Scripting.FileSystemObject")
    Set WshShell = CreateObject("WScript.Shell")
    PathDirs = Split(WshShell.ExpandEnvironmentStrings("%PATH%"), ";")
    For Each Dir In PathDirs
        If Right(Dir, 1) = "\" Then
            Dir = Left(Dir, Len(Dir) - 1)
        End If
        If FSO.FileExists(Dir + "\" + FileName) Then
            FindFile = Dir
            Exit Function
        End If
    Next
    FindFile = ""
End Function

