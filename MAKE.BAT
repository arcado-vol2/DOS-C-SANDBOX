@echo off
wcc main.c
if errorlevel 1 goto error
wlink file main.obj
if errorlevel 1 goto error
echo ---------------------------
echo.
echo.


main.exe

:error
