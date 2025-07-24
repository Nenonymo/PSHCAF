@echo off
setlocal enabledelayedexpansion

:: Outer loop from 0 to 6
for /L %%e in (0,1,6) do (
    :: Inner loop from 0 to 9
    for /L %%i in (0,1,9) do (
        echo Running %%i of %%e
        bin\benchmark.exe tasks\%%i.txt 6 %%e 010101 > results\%%e_%%i.txt
    )

    :: Sleep for 1 minutes (60 seconds)
    timeout /t 60 /nobreak > nul
)

endlocal
