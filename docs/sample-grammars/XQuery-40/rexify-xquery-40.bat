@echo off
setlocal

set "BUILD_DIR=%~dp0build"
set "CACHE=%BUILD_DIR%\cache"
set "CATALOG=%CACHE%\catalog.xml"
for /f "delims=" %%A in ('where basex') do set "BASEX=%%~dpA.."
for %%A in ("%BASEX%") do set "BASEX=%%~fA"
set "CLASSPATH=.;%BASEX%\BaseX.jar;%BASEX%\lib\*"
set "BASEX_JVM=-Dorg.basex.catalog=file:///%CATALOG:\=/%"

if not "%~1"=="" (set "SPEC_PATH_SEGMENT=%~1") else (set "SPEC_PATH_SEGMENT=specifications")
set "XQUERY_SPEC=https://qt4cg.org/%SPEC_PATH_SEGMENT%/xquery-40/xquery-40.html"
set "XPATH_SPEC=https://qt4cg.org/%SPEC_PATH_SEGMENT%/xquery-40/xpath-40.html"

if not exist "%BUILD_DIR%" (echo ...creating build directory: %BUILD_DIR% & mkdir "%BUILD_DIR%" || exit /b )
if not exist "%CACHE%" (echo ...creating cache directory: %CACHE% & mkdir %CACHE% || exit /b )

cd %CACHE% || exit/b

echo ^<?xml version="1.0"?^>>catalog.xml
echo ^<catalog xmlns="urn:oasis:names:tc:entity:xmlns:xml:catalog"^>>>catalog.xml
echo   ^<uri name="unify-grammar.xq" uri="file:///%CD:\=/%/../../unify-grammar.xq"/^>>>catalog.xml

call :download xquery-40.html          %XQUERY_SPEC% || exit/b
call :download xpath-40.html           %XPATH_SPEC% || exit/b
call :download xml.html                https://www.w3.org/TR/REC-xml/ || exit/b
call :download xml-names.html          https://www.w3.org/TR/REC-xml-names/ || exit/b
call :download xquery-update-30.html   https://www.w3.org/TR/xquery-update-30/ || exit/b
call :download xpath-full-text-30.html https://www.w3.org/TR/xpath-full-text-30/ || exit/b

call :download cst-to-ast.xq            https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/cst-to-ast.xq || exit/b
call :download ast-to-ebnf.xq           https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ast-to-ebnf.xq || exit/b
call :download html-to-ebnf.xq          https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/html-to-ebnf.xq || exit/b
call :download ebnf-parser.xquery       https://raw.githubusercontent.com/GuntherRademacher/rr/refs/heads/basex/src/main/resources/de/bottlecaps/railroad/xq/ebnf-parser.xquery || exit/b

echo ^</catalog^>>>catalog.xml

cd "%BUILD_DIR%" || exit /b

call :rexify %XQUERY_SPEC% XQuery-40.ebnf                         -lalr 2 false false false || exit /b
call :rexify %XQUERY_SPEC% XQuery-Full-Text-Update-40.ebnf        -lalr 2 true  true  false || exit /b
call :rexify %XQUERY_SPEC% XQuery-Full-Text-Update-BaseX-40.ebnf -glalr 1 true  true  true  || exit /b
call :rexify %XPATH_SPEC%  XPath-40.ebnf                          -lalr 1 false false false || exit /b
call :rexify %XPATH_SPEC%  XPath-Full-Text-40.ebnf                -lalr 2 false true  false || exit /b
echo ...done

exit /b

:download
if not exist "%1" (echo ...downloading %1 & curl -fsS -o %1 %2) else (echo ...%1 is already present in cache) || exit/b
set "URI=%~dpnx1"
echo   ^<uri name="%1" uri="file:///%URI:\=/%"/^>>>catalog.xml
echo   ^<uri name="%2" uri="file:///%URI:\=/%"/^>>>catalog.xml
exit/b

:rexify
set "HTML=%1"
set "EBNF=%2"
set "ALGORITHM=%3"
set "LOOKAHEAD=%4"
set "WITH_UPDATE=%5"
set "WITH_FULL_TEXT=%6"
set "WITH_BASEX=%7"
set "NAME=%~n2"
set "CLASS=%NAME:-=_%"

echo ...RExifying %HTML% into %EBNF%
java %BASEX_JVM% org.basex.BaseX -bwith-update="%WITH_UPDATE%" -bwith-full-text="%WITH_FULL_TEXT%" -bwith-basex="%WITH_BASEX%" -bspecification-url="%HTML%" -smethod=text ../%~n0.xq > "%EBNF%" || exit /b

echo ...generating parser for %EBNF% in XQuery
rex %ALGORITHM% %LOOKAHEAD% -xquery -name de/bottlecaps/rex/%NAME% %EBNF% || exit /b
echo ...generating parser for %EBNF% in Java
rex %ALGORITHM% %LOOKAHEAD% -java -basex -name de.bottlecaps.rex.%CLASS% %EBNF% || exit /b
echo ...compiling %CLASS%
javac -d . %CLASS%.java

exit /b