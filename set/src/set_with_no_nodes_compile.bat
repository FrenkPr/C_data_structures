@REM @echo off

mkdir "../bin"

clang.exe -o ../bin/set_with_no_nodes.exe ^
    -Xlinker /subsystem:console ^
    set_with_no_nodes.c