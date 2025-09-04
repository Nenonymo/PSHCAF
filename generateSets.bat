@echo off
setlocal enabledelayedexpansion

:: Define the array
set arg[0]= 0.0000
set arg[1]= 0.0010
set arg[2]= 0.0017
set arg[3]= 0.0030
set arg[4]= 0.0044
set arg[5]= 0.0065
set arg[6]= 0.0095
set arg[7]= 0.0138
set arg[8]= 0.0201
set arg[9]= 0.0292
set arg[10]= 0.0425
set arg[11]= 0.0619
set arg[12]= 0.0901
set arg[13]= 0.1311
set arg[14]= 0.1908
set arg[15]= 0.2772
set arg[16]= 0.4026
set arg[17]= 0.5848
set arg[18]= 0.8496
set arg[19]= 1.0000

:: Loop through array indices
for /L %%i in (0,1,19) do (
    set "variance=!arg[%%i]!"
    echo Running gen set with variance !variance! and seed %%i
    bin\taskGenerator.exe 2000 %%i !variance! 200 > tasks\%%i.txt
)

endlocal
