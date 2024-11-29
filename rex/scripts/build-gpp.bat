@echo off

:: builds rex.exe with g++ 6, 8, 9, 10, 12, 14

call %~dp0fragments\check-version.bat "g++ --version" "g++" "g++"
if errorlevel 1 exit /b
call %~dp0fragments\build-windows.bat o echo "g++ -std=gnu++17 -O3 -Wall -c -o " "g++ -static -o "