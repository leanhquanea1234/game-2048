@echo off
setlocal enabledelayedexpansion

@REM cd to project root
cd /d "%~dp0.."

if exist "build" (
    echo Build directory already exits
    cd "build"
) else (
    mkdir "build"
    cd "build"
)

echo Configuring MSVC build...
cmake .. -G "Visual Studio 17 2022" -T host=x64 -A x64

echo Building project...
cmake --build . --config Release

echo Starting game...
start bin\Release\Game2048.exe

endlocal