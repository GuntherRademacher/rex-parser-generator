@echo off

:: builds rex.exe with Microsoft C/C++ 19.41.34123
:: from Visual Studio 2019 Version 16.11: Version 19.29.30136
:: download link: "https://visualstudio.microsoft.com/de/downloads/
:: for x86, call e.g. "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"

call %~dp0fragments\check-version.bat "cl" " x86" "Microsoft C/C++ Optimizing Compiler for x86"
if errorlevel 1 exit /b
call %~dp0fragments\build-windows.bat obj rem "cl /nologo /c /EHsc /O2 /Fo:" "cl /nologo /MT /Fe:"