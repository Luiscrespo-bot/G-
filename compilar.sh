#!/bin/bash

# Script de compilación para Linux/macOS

echo "Compilando intérprete del lenguaje..."

g++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje

if [ $? -eq 0 ]; then
    echo "Compilación exitosa"
    echo "Ejecutable creado: lenguaje"
else
    echo "Error durante la compilación"
    exit 1
fi
