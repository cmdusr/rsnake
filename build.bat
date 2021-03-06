@echo off

goto SKIP_DEF

:IS_FILE_LOCKED
echo %1
2>nul (>>%1 (call )) && (EXIT /B 0) || (EXIT /B 1)

:SKIP_DEF

set CC=cl.exe
set CCFLAGS=/D_HAS_EXCEPTIONS=0 /nologo /I..\code /Zi
set LDFLAGS=-incremental:no

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

call :IS_FILE_LOCKED bin/%Target%.exe
set core_locked=%ERRORLEVEL%

call :IS_FILE_LOCKED bin/%Game%.dll
set game_locked=%ERRORLEVEL%

pushd build

if %core_locked% EQU 0 (
	%CC% %CCFLAGS% /Fe%Target% %TargetPath% /link %LDFLAGS% user32.lib shell32.lib gdi32.lib
	move /y %Target%.exe ..\bin
	move /y %Target%.pdb ..\bin
)

rem Always build game
set Game_pdb=%Game%_%random%.pdb
%CC% %CCFLAGS% /Fe%Game% %GamePath% /LD /link %LDFLAGS% /PDB:%Game_pdb% /Export:get_game_api
move /y %Game_pdb% ..\bin

if %game_locked% EQU 0 (
	move /y %game%.dll ..\bin
) else (
	move /y %game%.dll ..\bin\%game%_temp.dll
)

popd

:END
