@echo off
REM Script de compilación de la IDE para Windows

echo Compilando IDE del lenguaje...

g++ -std=c++17 src\Lexer.cpp src\Parser.cpp src\Interprete.cpp src\ServidorHTTP.cpp ide_main.cpp -pthread -o lenguaje_ide.exe

if errorlevel 1 (
    echo ❌ Error durante la compilación
    exit /b 1
) else (
    echo ✅ Compilación exitosa
    echo ✅ IDE creada: lenguaje_ide.exe
    echo.
    echo 🚀 Para iniciar la IDE, ejecuta:
    echo    lenguaje_ide.exe
    echo.
    echo 📝 Luego abre en tu navegador:
    echo    http://127.0.0.1:8080
)
