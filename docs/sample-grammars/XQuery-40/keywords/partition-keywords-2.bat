@echo off
setlocal enabledelayedexpansion

rem Ergebnisdateien bereinigen
if exist ambiguous-keywords.txt del ambiguous-keywords.txt
if exist other-unacceptable-keywords.txt del other-unacceptable-keywords.txt

for /f "usebackq delims=" %%K in ("unacceptable-keywords.txt") do (
    rem Keyword einlesen
    set "keyword=%%K"
    rem Trimmen
    for /l %%A in (1,1,100) do if "!keyword:~-1!"==" " set "keyword=!keyword:~0,-1!"

    rem Statusmeldung
    echo Teste mit Parser: "!keyword!"

    rem (1) KEYWORD-HERE ersetzen
    sed "s/KEYWORD-HERE/!keyword!/g" XQuery-40-kh.ebnf > XQuery-40-test.ebnf

    rem (2) Parser generieren
    rex -glalr 1 -javascript -main XQuery-40-test.ebnf
    if errorlevel 1 (
        echo Fehler bei Parser-Generierung für !keyword!
        echo ------------------------------
    ) else (
        rem (3) Ausgabe analysieren via grep
        node XQuery-40-test.js "{element !keyword! {} }"  2>&1| grep -qi ambigu
        if !errorlevel! equ 0 (
            echo !keyword! >> ambiguous-keywords.txt
            echo → !keyword! wurde als **ambiguous** erkannt.
        ) else (
            echo !keyword! >> other-unacceptable-keywords.txt
            echo → !keyword! ist **nicht-ambiguous**, aber weiterhin nicht akzeptabel.
        )
        echo ------------------------------
 rem       pause
    )
)

echo Analyse abgeschlossen.
