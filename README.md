# LenguajeLd — Lenguaje de programación en Español (Intérprete en C++)

## Español (ES)

Un lenguaje de programación educativo con palabras clave en español y un intérprete implementado en C++ (lexer, parser y ejecutor). Ideal para aprender conceptos de análisis léxico/sintáctico y para escribir programas sencillos usando sintaxis totalmente en español.

### Estado
Funcional: intérprete CLI y una versión IDE básica incluida. Ejemplos incluidos en /ejemplos. Proyecto en desarrollo — mejoras planeadas (arrays, módulos, excepciones).

### Características principales
- Sintaxis y palabras clave en español (ej.: `var`, `si`, `sino`, `mientras`, `para`, `funcion`, `retorna`, `escribir`, `leer`).
- Tipos básicos: números (enteros y decimales), textos (strings), booleanos.
- Operadores aritméticos, comparadores y lógicos.
- Declaración de variables, funciones con parámetros y retorno.
- Control de flujo: condicionales y bucles.
- Modo interactivo (REPL) y ejecución de archivos.
- Ejemplos listos en `ejemplos/`.

### Estructura del proyecto
```
/ (repo root)
├── CMakeLists.txt           # configuración de build (genera 2 ejecutables)
├── main.cpp                 # intérprete CLI (ejecuta archivos o REPL)
├── ide_main.cpp             # ejecutable para la IDE web básica
├── src/                     # código fuente del lenguaje
│   ├── Lexer.h
│   ├── Lexer.cpp
│   ├── Parser.h
│   ├── Parser.cpp
│   ├── AST.h
│   ├── Interprete.h
│   └── Interprete.cpp
├── ejemplos/                # programas de ejemplo (.ld)
├── compilar.sh / compilar.bat# scripts de compilación rápidos
├── README.md
├── INSTALACION.md
├── ESPECIFICACION.md
├── PROYECTO_FINAL.md
└── LICENSE
```

Cómo encajan las piezas:
- `main.cpp` implementa el flujo principal: leer archivo o entrar en REPL → tokenizar con `Lexer` → parsear con `Parser` → ejecutar AST con `Interprete`.
- `ide_main.cpp` y `src/ServidorHTTP.*` conforman una versión de IDE/servicio web (construido como ejecutable separado por CMake).

### Compilación (rápida)
Recomendado: CMake
```bash
git clone https://github.com/Luiscrespo-bot/G-.git
cd G-
mkdir build
cd build
cmake ..
cmake --build .
```

Esto creará al menos dos ejecutables:
- `lenguaje` (intérprete CLI)
- `lenguaje_ide` (IDE web, si tu sistema cumple dependencias)

Compilación manual (g++):
```bash
g++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje
```

Uso:
- Ejecutar un archivo: `./lenguaje ejemplos/hola.ld`
- REPL: `./lenguaje` (escribe "salir" para terminar)

Consulta `ESPECIFICACION.md` para la gramática completa y ejemplos detallados.

### Limitaciones conocidas
- Sin arrays/listas ni diccionarios aún.
- Manejo de scope y recursión limitado.
- No hay soporte para múltiples archivos o módulos.
- No hay suite de pruebas automatizada (por ahora).

### Extensiones planeadas
- Arrays y colecciones.
- Diccionarios / mapas.
- Manejo de excepciones (try/catch).
- Módulos/imports y soporte para múltiples archivos.
- Más funciones estándar (math, string utilities).

### Contribuir
1. Abre un issue para discutir cambios grandes.
2. Crea un fork y una rama con tu PR.
3. Incluye ejemplos y pasos para reproducir/compilar tus cambios.

---

## English (EN)

LenguajeLd — Programming language in Spanish (Interpreter in C++)

An educational programming language with Spanish keywords and an interpreter implemented in C++ (lexer, parser, and executor). Great for learning lexical/syntactic analysis and writing simple programs using Spanish-only syntax.

### Status
Working: CLI interpreter and a basic IDE version included. Examples in `/ejemplos`. Project is in development — planned improvements (arrays, modules, exceptions).

### Key features
- Keywords in Spanish (e.g., `var`, `si`, `sino`, `mientras`, `para`, `funcion`, `retorna`, `escribir`, `leer`).
- Basic types: numbers (integers and floats), texts (strings), booleans.
- Arithmetic, comparison and logical operators.
- Variable declaration, functions with parameters and return values.
- Control flow: conditionals and loops.
- Interactive mode (REPL) and file execution.
- Examples included in `ejemplos/`.

### Project layout
```
/ (repo root)
├── CMakeLists.txt
├── main.cpp
├── ide_main.cpp
├── src/
│   ├── Lexer.h, Lexer.cpp
│   ├── Parser.h, Parser.cpp
│   ├── AST.h
│   └── Interprete.*
├── ejemplos/
├── compilar.sh / compilar.bat
└── LICENSE
```

How it fits together:
- `main.cpp` is the main flow: read file or REPL → tokenize with `Lexer` → parse with `Parser` → execute AST with `Interprete`.
- `ide_main.cpp` and `src/ServidorHTTP.*` implement a simple IDE/web service (built as a separate executable in CMake).

### Build (quick)
Recommended: CMake
```bash
git clone https://github.com/Luiscrespo-bot/G-.git
cd G-
mkdir build
cd build
cmake ..
cmake --build .
```

Manual g++ build:
```bash
g++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje
```

### Usage
- Run a file: `./lenguaje ejemplos/hola.ld`
- REPL: `./lenguaje` (type `salir` to exit)

See `ESPECIFICACION.md` for full grammar and detailed examples.

### Known limitations
- No arrays/lists or dictionaries yet.
- Limited scope and deep recursion support.
- No multi-file/module support.
- No automated test suite yet.

### Planned extensions
- Arrays and collections.
- Dictionaries / maps.
- Exception handling (try/catch).
- Modules/imports and multi-file support.
- More standard library functions.

### Contributing
1. Open an issue to discuss large changes.
2. Fork and open a PR with your branch.
3. Include examples and reproduction steps.
