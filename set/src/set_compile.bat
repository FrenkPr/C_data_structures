@REM @echo off

mkdir "../bin"

clang.exe -o ../bin/set.exe ^
    -Xlinker /subsystem:console ^
    set.c