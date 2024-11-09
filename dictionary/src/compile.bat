@REM @echo off

mkdir "../bin"

clang.exe -o ../bin/dict.exe ^
    -Xlinker /subsystem:console ^
    *.c