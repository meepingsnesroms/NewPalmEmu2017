@echo off
echo.
echo first, let's make the cfl
echo.
..\bin\makecfl cfl hello.ini
echo.
echo then we'll compile our example
echo.
cl /I..\include hello.cpp zlib.lib ../src/CFL.cpp ../src/CFLDirectoryEntry.cpp ../src/CFLLibrary.cpp ../src/CFLMaker.cpp ../src/CFLResource.cpp ../src/CFLResourceFilter.cpp ../src/CFL_delta16.cpp ../src/CFL_delta32.cpp ../src/CFL_delta8.cpp ../src/CFL_none.cpp ../src/CFL_zlib.cpp
rem if zlib is at /zlib/, add /I/zlib/ /zlib/zlib.lib to above
echo.
echo and run it
echo.
hello
echo.
echo cleanup
del *.obj