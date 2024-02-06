@echo off
set folderName=build
 
if not exist "%folderName%" 
(
    mkdir "%folderName%"
    echo Directory created: %folderName%
) 
else 
(
    echo Directory already exists: %folderName%
)
 

set folderNam=Exe_File
 
if not exist "%folderNam%" 
(
    mkdir "%folderNam%"
    echo Directory created: %folderNam%
) 
else 
(
    echo Directory already exists: %folderNam%
)

g++ -std=c++17 -c Build.cpp -o "build\Build.o"
g++ -std=c++17 -c main.cpp -o "build\main.o"
g++ "build\Build.o" "build\main.o" -o "Exe_File\Build.exe"