@REM @echo off

clang.exe -o bin/dict.exe ^
    -Xlinker /subsystem:console ^
    *.c