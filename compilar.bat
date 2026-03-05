@echo off
REM Script de compilación para Windows usando g++

echo Compilando intérprete del lenguaje...
g++ -std=c++17 src\Lexer.cpp src\Parser.cpp src\Interprete.cpp main.cpp -o lenguaje.exe

if errorlevel 1 (
    echo Error durante la compilación
    exit /b 1
) else (
    echo Compilación exitosa
    echo Ejecutable creado: lenguaje.exe
)
