#!/bin/bash

# Script de compilación de la IDE para Linux/macOS

echo "Compilando IDE del lenguaje..."

g++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp src/ServidorHTTP.cpp ide_main.cpp -pthread -o lenguaje_ide

if [ $? -eq 0 ]; then
    echo "✅ Compilación exitosa"
    echo "🚀 IDE creada: lenguaje_ide"
    echo "   Ejecuta: ./lenguaje_ide"
else
    echo "❌ Error durante la compilación"
    exit 1
fi
