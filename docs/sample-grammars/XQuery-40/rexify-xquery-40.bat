@echo off
setlocal enabledelayedexpansion

set "BUILD_DIR=%~dp0build"
set "BUILD_DIR=!BUILD_DIR:%cd%=.!!"

echo ...creating build directory: %BUILD_DIR%
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%" || exit /b
cd "%BUILD_DIR%" || exit /b

echo ...fetching EBNF grammar
if not exist Parser.ebnf curl --silent -O https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/java/de/bottlecaps/railroad/core/Parser.ebnf || exit /b

echo ...generating EBNF parser
rex -q -xquery -tree Parser.ebnf || exit /b

echo ...RExifying XQuery 4.0 grammar
call basex -smethod=text ../%~n0.xq > XQuery-40.ebnf || exit /b

echo ...running LALR(2) construction on XQuery 4.0 grammar
rex -lalr 2 XQuery-40.ebnf || exit /b

echo ...done