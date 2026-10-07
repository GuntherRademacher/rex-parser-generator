@echo off
setlocal enabledelayedexpansion

set "BUILD_DIR=%~dp0build"
set "BUILD_DIR=!BUILD_DIR:%cd%=.!!"

for /f "delims=" %%A in ('where basex') do set "BASEX=%%~dpA.."
for %%A in ("%BASEX%") do set "BASEX=%%~fA"
set CLASSPATH=.;%BASEX%\BaseX.jar;%BASEX%\lib\*
set "BASEX_JVM=-Dorg.basex.catal3og=file:///C:/Users/Gunther/git/rex-parser-generator/docs/sample-grammars/XQuery-40/catalog.xml"

cd "%BUILD_DIR%" || exit /b

set LANGUAGE=%1
if "%1"=="" (set "LANGUAGE=xquery") else (set "LANGUAGE=%1")
if "%2"=="" (set "IMPLEMENTATION=java") else (set "IMPLEMENTATION=%2")
if "%3"=="" (set "VERBOSE=false") else (set "VERBOSE=%3")

java org.basex.BaseX "-blanguage=%LANGUAGE%" "-bimplementation=%IMPLEMENTATION%" "-bverbose=%VERBOSE%" "-broot=..\..\..\..\qt4tests\catalog.xml" ../process-tests.xq || exit /b

exit /b