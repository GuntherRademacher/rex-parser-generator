@echo off
setlocal enabledelayedexpansion

set "BUILD_DIR=%~dp0build"
set "BUILD_DIR=!BUILD_DIR:%cd%=.!!"

echo ...creating build directory: %BUILD_DIR%
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%" || exit /b
cd "%BUILD_DIR%" || exit /b

call :rexify https://qt4cg.org/specifications/xquery-40/xquery-40.html XQuery-40.ebnf || exit /b
call :rexify https://qt4cg.org/specifications/xquery-40/xpath-40.html XPath-40.ebnf || exit /b
echo ...done

exit /b

:rexify
set "INPUT=%1"
set "OUTPUT=%2"

echo ...RExifying %INPUT% into %OUTPUT%
call basex -bspecification-url="%INPUT%" -smethod=text ../%~n0.xq > "%OUTPUT%" || exit /b

echo ...running LALR(2) construction on %OUTPUT%
rex -lalr 2 %OUTPUT% || exit /b

exit /b