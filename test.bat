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
set UseClang=false

REM BUILDING
REM find a better way to parse arguments
IF [%~1] == [-r] (
    set BuildDir=win32_release
    set Release=true

    IF [%~2] == [-d] (
        set Debug=true

        IF [%~3] == [-c] (
            set UseClang=true
        )
    )

    IF [%~2] == [-c] (
        set UseClang=true
    )
)

IF [%~1] == [-d] (
    set Debug=true

    IF [%~2] == [-c] (
        set UseClang=true
    )
)

IF [%~1] == [-c] (
    set UseClang=true
)

IF [%UseClang%] == [true] (
    IF [%Release%] == [true] (
        @echo on
        clang-cl %CommonFlags% %CommonIncludes% /Fe%BuildDir%/ /Fo%BuildDir%/ /O2 /Ot %CommonSourceFiles% %CommonLinks%
        @echo off
    ) ELSE (
        @echo on
        clang-cl %CommonFlags% %CommonIncludes% /Zi /Fe%BuildDir%/ /Fo%BuildDir%/ /Fd%BuildDir%/ /Fa%BuildDir%/ %CommonSourceFiles% %CommonLinks%
        @echo off
    )
) ELSE (
    IF [%Release%] == [true] (
        @echo on
        cl %CommonFlags% %CommonIncludes% /Fe%BuildDir%/ /Fo%BuildDir%/ /O2 /Ot %CommonSourceFiles% %CommonLinks%
        @echo off
    ) ELSE (
        @echo on
        cl %CommonFlags% %CommonIncludes% /DEBUG:FULL /Zi /Fe%BuildDir%/ /Fo%BuildDir%/ /Fd%BuildDir%/ /Fa%BuildDir%/ /Fm%BuildDir%/ /Fp%BuildDir%/ /FR%BuildDir%/ %CommonSourceFiles% %CommonLinks%
        @echo off
    )
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