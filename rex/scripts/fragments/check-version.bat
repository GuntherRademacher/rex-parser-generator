@echo off

:: check that command %1 returns output containing %2, identifying product %3

setlocal

set         "VERSION_COMMAND=%~1"
set "EXPECTED_VERSION_STRING=%~2"
set        "EXPECTED_VERSION=%~3"

if errorlevel 1 exit/b %errorlevel%
for /f "tokens=*" %%i in ('%VERSION_COMMAND% 2^>^&1') do (
    echo %%i | findstr /c:"%EXPECTED_VERSION_STRING%" >nul
    if not errorlevel 1 (
        exit/b 0
    )
)

echo This script is for %EXPECTED_VERSION%, but that could not be identified. Received this from command "%VERSION_COMMAND%"
echo/ 
%VERSION_COMMAND%
exit /b 1
