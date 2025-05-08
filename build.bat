@echo off
rem Clean the cache and the build folder
if exist build (
    rd /s /q build
)

rem Create the build folder
mkdir build
cd build

rem Run cmake to configure the project using Ninja (or other generator)
cmake -G "MinGW Makefiles" ..  rem Change to your desired generator

rem Build the project in Release mode
cmake --build . --config Release

rem Inform the user that the build is complete
echo Build complete! Output is in the build\x64\Release folder.

start AutoClickerTracker.exe

pause
