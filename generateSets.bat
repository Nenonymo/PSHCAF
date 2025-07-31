@echo off
setlocal enabledelayedexpansion

:: Define the array
set arg[0]=0.0
set arg[1]=0.010
set arg[2]=0.018
set arg[3]=0.031
set arg[4]=0.056
set arg[5]=0.100
set arg[6]=0.180
set arg[7]=0.310
set arg[8]=0.560
set arg[9]=1.000

:: Loop through array indices
for /L %%i in (0,1,9) do (
    set "variance=!arg[%%i]!"
    echo Running gen set with variance !variance! and seed %%i
    bin\taskGenerator.exe 3000 %%i !variance! 300 > tasks\%%i.txt
)

endlocal
