@echo off
setlocal enabledelayedexpansion

rem Dateien vorbereiten
if exist acceptable-keywords.txt del acceptable-keywords.txt
if exist unacceptable-keywords.txt del unacceptable-keywords.txt

for /f "usebackq delims=" %%K in ("keywords.txt") do (
    set "keyword=%%K"

    rem Statusanzeige
    echo Verarbeite: !keyword!

    rem Ersetze KEYWORD-HERE durch das aktuelle Schlüsselwort und schreibe nach XQuery-40-test.ebnf
    sed "s/KEYWORD-HERE/!keyword!/g" XQuery-40-kh.ebnf > XQuery-40-test.ebnf

    rem rex ausführen
    rex -lalr 2 XQuery-40-test.ebnf 2>&1 >nul
    if errorlevel 1 (
        echo !keyword! >> unacceptable-keywords.txt
    ) else (
        echo !keyword! >> acceptable-keywords.txt
    )
)

echo Alle Schlüsselwörter wurden verarbeitet.
