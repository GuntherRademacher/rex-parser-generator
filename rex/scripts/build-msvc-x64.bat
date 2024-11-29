@echo off

:: builds rex.exe with Microsoft C/C++ 19.41.34123
:: download link: "https://visualstudio.microsoft.com/de/downloads/
:: for x64, call e.g. "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"

call %~dp0fragments\check-version.bat "cl" " x64" "Microsoft C/C++ Optimizing Compiler for x64"
if errorlevel 1 exit /b
call %~dp0fragments\build-windows.bat obj rem "cl /nologo /c /EHsc /O2 /Fo:" "cl /nologo /MT /Fe:"