@REM @echo off

mkdir "../bin"

clang.exe -o ../bin/doubly_linked_list.exe ^
    -Xlinker /subsystem:console ^
    *.c