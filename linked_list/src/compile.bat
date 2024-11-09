@REM @echo off

mkdir "../bin"

clang.exe -o ../bin/linked_list.exe ^
    -Xlinker /subsystem:console ^
    *.c