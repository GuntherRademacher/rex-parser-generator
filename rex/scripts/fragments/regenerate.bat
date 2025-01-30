@echo off

:: regenerate REx-generated REx source files

setlocal

if not exist "%1" (
  echo Usage: %~n0 FOLDER
  echo/
  echo Regenerates REx-generated source files in FOLDER and its subdirectories.
  exit/b 1
)

cd %1

for /f "delims=" %%A in ('findstr /m /s /c:" This file was generated on " *') do (
  echo %%~nxA 
  pushd %%~dpA 
  rex -remake %%~nxA 
  popd
)