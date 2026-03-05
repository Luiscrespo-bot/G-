# Instrucciones de Instalación del Compilador

## Para Windows

### Opción 1: MinGW (Recomendado para g++)

1. **Descargar MinGW:**
   - Ve a https://www.mingw-w64.org/
   - Descarga "x86_64-w64-mingw32" (para Windows 64-bit)

2. **Instalar MinGW:**
   - Ejecuta el instalador
   - Selecciona el directorio de instalación (ej: `C:\MinGW64`)
   - Luego agrega el bin al PATH:
     - Presiona Win + R
     - Escribe: `sysdm.cpl`
     - Ve a "Variables de entorno"
     - Agrega `C:\MinGW64\bin` al PATH

3. **Verificar instalación:**
   ```bash
   g++ --version
   ```

### Opción 2: CMake + Ninja + Visual Studio Build Tools

1. **Instalar Visual Studio Build Tools:**
   - Descarga desde: https://visualstudio.microsoft.com/visual-cpp-build-tools/
   - Instala "MSVC v143" y "Windows SDK"

2. **Instalar CMake:**
   - Descarga desde: https://cmake.org/download/
   - Ejecuta el instalador

3. **Compilar con CMake:**
   ```bash
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```

### Opción 3: Usar WSL (Windows Subsystem for Linux)

1. **Instalar WSL2:**
   ```powershell
   wsl --install
   ```

2. **En WSL (Ubuntu):**
   ```bash
   sudo apt update
   sudo apt install build-essential
   ```

3. **Compilar:**
   ```bash
   cd /mnt/c/Users/lfcre/OneDrive/Desktop/Lenguage
   g++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje
   ```

## Para Linux

```bash
# Debian/Ubuntu
sudo apt update
sudo apt install build-essential

# Fedora/RHEL
sudo dnf install gcc-c++ make

# Arch
sudo pacman -S gcc
```

## Para macOS

```bash
# Con Homebrew
brew install gcc

# O usar clang (instalado por defecto)
clang++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje
```

## Compilación después de instalar

### Con g++ (después de instalar MinGW en Windows)

```bash
cd c:\Users\lfcre\OneDrive\Desktop\Lenguage
g++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje.exe
```

### Con clang (macOS)

```bash
clang++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje
```

### Con CMake (Multiplataforma)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

## Verificar la compilación

Después de compilar exitosamente, prueba con un ejemplo:

```bash
./lenguaje ejemplos/hola.ld
```

Debería mostrar:
```
¡Hola, Mundo!
```

Si ves esto, ¡todo funciona correctamente!
