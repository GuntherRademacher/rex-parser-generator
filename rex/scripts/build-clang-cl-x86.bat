@echo off

:: builds rex.exe with clang version 19.1.3 from LLVM 19.1.3 plus Microsoft C/C++ 19.41.34123
:: download link: https://github.com/llvm/llvm-project/releases
:: download link: https://visualstudio.microsoft.com/de/downloads
:: for x86, call e.g. "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars32.bat"

call %~dp0fragments\check-version.bat "clang-cl --version" "clang version" Clang
if errorlevel 1 exit /b
call %~dp0fragments\check-version.bat "cl" " x86" "Clang with Microsoft C/C++ Optimizing Compiler for x86"
if errorlevel 1 exit /b
call %~dp0fragments\build-windows.bat obj echo "clang-cl -m32 -c -EHsc -O2  -Wno-deprecated-declarations -Fo" "clang-cl -MT -Fe"