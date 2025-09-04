@echo off
setlocal enabledelayedexpansion

:: Loop ranges
set "E_MIN=0"
set "E_MAX=6"   :: inclusive -> 7 values
set "I_MIN=0"
set "I_MAX=19"  :: inclusive -> 20 values

:: Derived totals
set /a "E_COUNT=E_MAX-E_MIN+1"
set /a "I_COUNT=I_MAX-I_MIN+1"
set /a "TOTAL=E_COUNT*I_COUNT"

:: Make sure results folder exists
if not exist "results" mkdir "results"

for /L %%e in (%E_MIN%,1,%E_MAX%) do (
    for /L %%i in (%I_MIN%,1,%I_MAX%) do (
        :: How many completed so far (1-based)
        set /a "COMPLETED=(%%e-%E_MIN%)*%I_COUNT% + (%%i-%I_MIN%) + 1"
        :: Integer percentage
        set /a "PCT=COMPLETED*100/TOTAL"

        echo Running e=%%e, i=%%i  --  !PCT!%% complete

        bin\benchmark.exe tasks\%%i.txt 6 %%e 0111110 > results\%%e_%%i.txt
    )

    :: Sleep for 1 minute between outer-loop batches
    timeout /t 60 /nobreak > nul
)

endlocal
`
