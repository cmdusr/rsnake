@echo off

set CC=cl.exe
set CCFLAGS=/D_HAS_EXCEPTIONS=0 /nologo /I..\code /Zi
set LDFLAGS=-incremental:no user32.lib shell32.lib gdi32.lib

set Target=rgame
set TargetPath=..\code\unity\windows_unity.cpp

set Game=game
set GamePath=..\code\unity\rsnake_unity.cpp

rem Search for CC
for %%X in (%CC%) do (set FOUND=%%~$PATH:X)
if not defined FOUND (
	echo Error: Cannot find cl.exe. Setup your devlopment environment to include cl.exe
	echo This can be done by using vcvarsall.bat if running from a console
	goto END
)

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

%CC% %CCFLAGS% /Fe%Game%   %GamePath%   /LD /link %LDFLAGS% /PDB:%Game%_%random%.pdb /Export:get_game_api
%CC% %CCFLAGS% /Fe%Target% %TargetPath%     /link %LDFLAGS% user32.lib shell32.lib gdi32.lib

move /y *.pdb ..\bin
move /y *.exe ..\bin

if EXIST ..\bin\%game%.dll (
	 move /y %game%.dll ..\bin\%game%_temp.dll
) else (
	move /y %game%.dll ..\bin
)

popd

:END
