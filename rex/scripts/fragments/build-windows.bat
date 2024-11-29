@echo off

setlocal EnableDelayedExpansion

set "OBJECT_EXTENSION=%~1"
set      "LOG_COMMAND=%~2"
set  "COMPILE_COMMAND=%~3"
set     "LINK_COMMAND=%~4"

cd /d %~dp0..\..
rd /s /q build 2>nul

set EXECUTABLE=build\bin\rex.exe
set OBJECTS=
for /r src %%c in (*.cpp) do (
  call :compile %%c
)

mkdir build\bin 2>nul
echo on
%LINK_COMMAND%%EXECUTABLE% %OBJECTS%
@echo off
if errorlevel 1 exit /b
echo/
echo Successfully built executable %EXECUTABLE%
exit /b

:compile
set FILE=%1
set FILE=!FILE:%CD%\src\=.\!
set FOLDER=!FILE:\%~nx1=!
set CPP=%FOLDER%\%~nx1
set OBJ=build\obj\%FOLDER%\%~n1.%OBJECT_EXTENSION%
set OBJECTS=%OBJECTS% %OBJ%

mkdir build\obj\%FOLDER% 2>nul
%LOG_COMMAND% %FILE:.\=%
%COMPILE_COMMAND%%OBJ% src\%CPP%
