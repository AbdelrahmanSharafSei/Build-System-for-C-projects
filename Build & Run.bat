@echo off
set folderName=build
 
if not exist "%folderName%" (
    mkdir "%folderName%"
    echo Directory created: %folderName%
) else (
    echo Directory already exists: %folderName%
)

set folderNam=Exe_File
 
if not exist "%folderNam%" (
    mkdir "%folderNam%"
    echo Directory created: %folderNam%
) else (
    echo Directory already exists: %folderNam%
)


g++ -std=c++20 -c FileTrakker.cpp -o "build\FileTrakker.o"
g++ -std=c++20 -c Build.cpp -o "build\Build.o"
g++ -std=c++20 -c main.cpp -o "build\main.o"

g++ "build\FileTrakker.o" "build\Build.o" "build\main.o" -o "Exe_File\Build.exe"

@echo on

CD /D C:\Users\AbdelrahmanSharaf\OneDrive - SEITech Solutions GmbH\Desktop\Build\Exe_File
pause
Build.exe
pause