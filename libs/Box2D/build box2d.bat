@echo off
setlocal enabledelayedexpansion

set SRC=src
set INC=include

echo Compiling Box2D...
pushd %SRC%
for /r %%f in (*.c) do (
    gcc -std=c17 -O2 -I..\%INC% -I. -c "%%f" -o "%%~nf.o"
)
popd

echo Collecting object files...
set OBJLIST=
for %%f in (%SRC%\*.o) do set OBJLIST=!OBJLIST! "%%f"

echo Archiving into libbox2d.a...
ar rcs libbox2d.a !OBJLIST!

echo Cleaning up...
del %SRC%\*.o

echo Done.
endlocal

pause