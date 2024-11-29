@echo off

:: regenerate REx-generated REx source files

setlocal

cd %~dp0..\..\src

for /f "delims=" %%A in ('findstr /m /s /c:"// This file was generated " *') do (
  echo %%~nxA 
  pushd %%~dpA 
  rex -remake %%~nxA 
  popd
)