@echo off
setlocal

set "BUILD_DIR=%~dp0build"
set "CACHE=%BUILD_DIR%\cache"
set "CATALOG=%CACHE%\catalog.xml"
for /f "delims=" %%A in ('where basex') do set "BASEX=%%~dpA.."
for %%A in ("%BASEX%") do set "BASEX=%%~fA"
set "CLASSPATH=.;%BASEX%\BaseX.jar;%BASEX%\lib\*"
set "BASEX_JVM=-Dorg.basex.catalog=file:///%CATALOG:\=/%"

if not exist "%BUILD_DIR%" (echo ...creating build directory: %BUILD_DIR% & mkdir "%BUILD_DIR%" || exit /b )
if not exist "%CACHE%" (echo ...creating cache directory: %CACHE% & mkdir %CACHE% || exit /b )

cd %CACHE% || exit/b
echo ^<?xml version="1.0"?^>>catalog.xml
echo ^<catalog xmlns="urn:oasis:names:tc:entity:xmlns:xml:catalog"^>>>catalog.xml
call :download  xquery-40.html     https://qt4cg.org/specifications/xquery-40/xquery-40.html || exit/b
call :download  xpath-40.html      https://qt4cg.org/specifications/xquery-40/xpath-40.html || exit/b
call :download  xml.html           https://www.w3.org/TR/REC-xml/ || exit/b
call :download  xml-names.html     https://www.w3.org/TR/REC-xml-names/ || exit/b
call :download  cst-to-ast.xq      https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/cst-to-ast.xq || exit/b
call :download  ast-to-ebnf.xq     https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ast-to-ebnf.xq || exit/b
call :download  html-to-ebnf.xq    https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/html-to-ebnf.xq || exit/b
call :download  ebnf-parser.xquery https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ebnf-parser.xquery || exit/b
echo ^</catalog^>>>catalog.xml

cd "%BUILD_DIR%" || exit /b

call :rexify https://qt4cg.org/specifications/xquery-40/xquery-40.html XQuery-40.ebnf || exit /b
call :rexify https://qt4cg.org/specifications/xquery-40/xpath-40.html XPath-40.ebnf || exit /b
echo ...done

exit /b

:download
if not exist "%1" (echo ...downloading %1 & curl -sS -o %1 %2) else (echo ...%1 is already present in cache) || exit/b
set "URI=%~dpnx1"
echo   ^<uri name="%1" uri="file:///%URI:\=/%"/^>>>catalog.xml
echo   ^<uri name="%2" uri="file:///%URI:\=/%"/^>>>catalog.xml
exit/b

:rexify
set "HTML=%1"
set "EBNF=%2"
set "NAME=%~n2"
set "CLASS=%NAME:-=_%"

echo ...RExifying %HTML% into %EBNF%
java %BASEX_JVM% org.basex.BaseX -bspecification-url="%HTML%" -smethod=text ../%~n0.xq > "%EBNF%" || exit /b

echo ...generating parser for %EBNF% in XQuery
rex -lalr 2 -xquery -name de/bottlecaps/rex/%NAME% %EBNF% || exit /b
echo ...generating parser for %EBNF% in Java
rex -lalr 2 -java -basex -name de.bottlecaps.rex.%CLASS% %EBNF% || exit /b
echo ...compiling %CLASS%
javac -d . %CLASS%.java

exit /b