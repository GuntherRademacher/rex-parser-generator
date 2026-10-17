@echo off
setlocal EnableExtensions EnableDelayedExpansion

set "SCRIPT_DIR=%~dp0"
set "BUILD_DIR=%SCRIPT_DIR%build"
set "CACHE=%BUILD_DIR%\cache"
set "REXIFY=%SCRIPT_DIR%rexify-xquery-40.bat"
set "DASHBOARD_QUERY=%SCRIPT_DIR%qt4cg-dashboard-prs.xq"
set "DASHBOARD=https://qt4cg.org/dashboard/"
set "PR_LIST=%BUILD_DIR%\qt4cg-dashboard-prs.txt"
set "LOG_FILE=%BUILD_DIR%\rexify-xquery-40-all.log"
set "SUCCESS_LIST=%BUILD_DIR%\rexify-xquery-40-all-success.txt"
set "FAILURE_LIST=%BUILD_DIR%\rexify-xquery-40-all-failure.txt"
set "FINAL_STATUS=0"

for /f "delims=" %%A in ('where basex') do set "BASEX=%%~dpA.."
if not defined BASEX (
  echo ERROR: basex was not found on PATH
  exit /b 1
)
for %%A in ("%BASEX%") do set "BASEX=%%~fA"
set "CLASSPATH=.;%BASEX%\BaseX.jar;%BASEX%\lib\*"

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%" || exit /b 1

type nul > "%LOG_FILE%"
type nul > "%SUCCESS_LIST%"
type nul > "%FAILURE_LIST%"
call :log ============================================================
call :log rexify-xquery-40-all started at %DATE% %TIME%
call :log Dashboard: %DASHBOARD%
call :log Log file: %LOG_FILE%
call :log ============================================================

call :fetch_prs
if errorlevel 1 (
  call :log ERROR: failed to fetch PR list from %DASHBOARD%
  exit /b 1
)

set "ANY_PR="

for /f "usebackq delims=" %%P in ("%PR_LIST%") do (
  set "ANY_PR=1"
  call :run_one "%%P"
)

if not defined ANY_PR (
  call :log ERROR: no pull requests found on %DASHBOARD%
  exit /b 1
)

call :run_one

call :log ============================================================
call :summary
if "%FINAL_STATUS%"=="0" goto :all_succeeded
call :log rexify-xquery-40-all finished with failures at %DATE% %TIME%
exit /b %FINAL_STATUS%

:all_succeeded
call :log rexify-xquery-40-all finished successfully at %DATE% %TIME%
exit /b 0

:fetch_prs
java org.basex.BaseX -bdashboard-url="%DASHBOARD%" -smethod=text "%DASHBOARD_QUERY%" > "%PR_LIST%"
set "FETCH_STATUS=%ERRORLEVEL%"

if not "%FETCH_STATUS%"=="0" exit /b %FETCH_STATUS%

call :log Pull requests to process:
for /f "usebackq delims=" %%P in ("%PR_LIST%") do call :log   %%P
exit /b 0

:run_one
set "SPEC_PATH=%~1"
if "%SPEC_PATH%"=="" (
  set "LABEL=master"
) else (
  set "LABEL=%SPEC_PATH%"
)

call :log ============================================================
call :log Beginning !LABEL! at %DATE% %TIME%
call :clear_cache
if errorlevel 1 (
  call :log Skipping !LABEL! because %CACHE% could not be cleared.
  call :record_failure "!LABEL!" 1
  exit /b 0
)

set "RUNNER=%TEMP%\rexify-xquery-40-%RANDOM%-%RANDOM%.cmd"
> "%RUNNER%" echo @echo off
>>"%RUNNER%" echo cd /d "%SCRIPT_DIR%"
if "%SPEC_PATH%"=="" (
  >>"%RUNNER%" echo call "%REXIFY%" 2^>^&1
) else (
  >>"%RUNNER%" echo call "%REXIFY%" "%SPEC_PATH%" 2^>^&1
)

powershell -NoProfile -ExecutionPolicy Bypass -Command "$LASTEXITCODE = 0; & '%RUNNER%' | ForEach-Object { $_; Add-Content -LiteralPath '%LOG_FILE%' -Encoding UTF8 -Value $_ }; if ($LASTEXITCODE -eq $null) { exit 1 } else { exit $LASTEXITCODE }"
set "STATUS=%ERRORLEVEL%"
del "%RUNNER%" >nul 2>nul

if "%STATUS%"=="0" (
  call :log Finished !LABEL! successfully at %DATE% %TIME%
  call :record_success "!LABEL!"
) else (
  call :log Finished !LABEL! with exit code %STATUS% at %DATE% %TIME%
  call :record_failure "!LABEL!" %STATUS%
)
exit /b 0

:record_success
>>"%SUCCESS_LIST%" echo %~1
exit /b 0

:record_failure
>>"%FAILURE_LIST%" echo %~1 exit %~2
if "%FINAL_STATUS%"=="0" set "FINAL_STATUS=%~2"
exit /b 0

:summary
call :count_lines "%SUCCESS_LIST%" SUCCESS_COUNT
call :count_lines "%FAILURE_LIST%" FAILURE_COUNT
call :log Summary: %SUCCESS_COUNT% succeeded, %FAILURE_COUNT% failed.
if not "%SUCCESS_COUNT%"=="0" (
  call :log Successful runs:
  for /f "usebackq delims=" %%S in ("%SUCCESS_LIST%") do call :log   %%S
)
if not "%FAILURE_COUNT%"=="0" (
  call :log Failed runs:
  for /f "usebackq delims=" %%F in ("%FAILURE_LIST%") do call :log   %%F
)
exit /b 0

:count_lines
set "COUNT=0"
for /f "usebackq delims=" %%L in ("%~1") do set /a COUNT+=1
set "%~2=%COUNT%"
exit /b 0

:clear_cache
if exist "%CACHE%" (
  call :log Clearing %CACHE%
  rmdir /s /q "%CACHE%"
  if errorlevel 1 (
    call :log ERROR: failed to delete %CACHE%
    exit /b 1
  )
)
exit /b 0

:log
set "LOG_LINE=%*"
echo(!LOG_LINE!
>>"%LOG_FILE%" echo(!LOG_LINE!
exit /b 0
