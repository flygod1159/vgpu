@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
cmake -B ".\build\win64" -S "." -G "Visual Studio 16 2019" -A x64 -DCMAKE_INSTALL_PREFIX="Sdk"
cd ..\..\
pause