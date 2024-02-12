@echo off
set folderNam=Exe_File
if not exist "%folderNam%" (
    echo there no EXE to be run please rebuild source code
    pause
) else (
    CD /D C:\Users\AbdelrahmanSharaf\OneDrive - SEITech Solutions GmbH\Desktop\Build\Exe_File
    Build.exe
    pause
)