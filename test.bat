@echo off
REM PREBARING BUILD
IF NOT EXIST build mkdir build
pushd build
IF NOT EXIST win32 mkdir win32
IF NOT EXIST win32_release mkdir win32_release

REM BUILD SETTINGS
set CommonFlags=/W3 /MD /nologo /std:c++14 /wd"4200" /Zc:__cplusplus /EHa
set CommonIncludes=/I../inc /I../src /I../test
set CommonSourceFiles=../test/test.cpp
set CommonLinks=/link /incremental:NO /libpath:../lib shlwapi.lib 
set BuildDir=win32
set Release=false
set Debug=false

REM BUILDING
IF [%~1] == [-r] (
    set BuildDir=win32_release
    set Release=true

    IF [%~2] == [-d] (
        set Debug=true
    )
)

IF [%~1] == [-d] (
    set Debug=true
)

IF [%Release%] == [true] (
    @echo on
    cl %CommonFlags% %CommonIncludes% /Fe%BuildDir%/ /Fo%BuildDir%/ /O2 /Ot %CommonSourceFiles% %CommonLinks%
    @echo off
) ELSE (
    @echo on
    cl %CommonFlags% %CommonIncludes% /DRETEX_DEBUG /DEBUG:FULL /Zi /Fe%BuildDir%/ /Fo%BuildDir%/ /Fd%BuildDir%/ /Fa%BuildDir%/ /Fm%BuildDir%/ /Fp%BuildDir%/ /FR%BuildDir%/ %CommonSourceFiles% %CommonLinks%
    @echo off
)
@echo off
pushd %BuildDir%
set Release=
set BuildDir=
IF [%Debug%] == [true] (
    devenv test.exe
) ELSE (
    test.exe
)
popd
popd