@echo off

set CC=cl.exe
set CCFLAGS=/D_HAS_EXCEPTIONS=0 /nologo /I..\code
set LDFLAGS=-incremental:no user32.lib shell32.lib gdi32.lib

set Target=rgame
set TargetPath=..\code\unity\windows_unity.cpp

if not exist code (
	echo Error: Invalid directory. Must be run from the root directory
	goto END
)

if NOT EXIST bin (
	mkdir bin
)

if NOT EXIST build (
	mkdir build
)

pushd build

%CC% %CCFLAGS% /Fe%Target%.exe /Zi /Fd%Target%.pdb %TargetPath% /link %LDFLAGS%

move /y *.exe ..\bin
move /y *.pdb ..\bin

popd

:END
