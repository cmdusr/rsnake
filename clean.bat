@echo off

echo Cleaning dirs...

if EXIST "bin" (
	rd /s /q bin
)

if EXIST "build" (
	rd /s /q build
)

echo Clean complete.
