@echo off
call "D:\Program Files\Microsoft Visual Studio\18\Community\Common7\Tools\VsDevCmd.bat" -arch=amd64
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
cmake -S . -B build --fresh -G "NMake Makefiles" -D CMAKE_BUILD_TYPE=Release -D CMAKE_TOOLCHAIN_FILE="D:/DevTools/vcpkg/scripts/buildsystems/vcpkg.cmake" -D VCPKG_TARGET_TRIPLET="x64-windows"
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%
cmake --build build --config Release
exit /b %ERRORLEVEL%
