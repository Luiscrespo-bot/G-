# LenguajeLd — Programming language in Spanish (Interpreter in C++)

An educational programming language with Spanish keywords and an interpreter implemented in C++ (lexer, parser, and executor). Great for learning lexical/syntactic analysis and writing simple programs using Spanish-only syntax.

## Status
Working: CLI interpreter and a basic IDE version included. Examples in `/ejemplos`. Project is in development — planned improvements (arrays, modules, exceptions).

## Key features
- Keywords in Spanish (e.g., `var`, `si`, `sino`, `mientras`, `para`, `funcion`, `retorna`, `escribir`, `leer`).
- Basic types: numbers (integers and floats), texts (strings), booleans.
- Arithmetic, comparison and logical operators.
- Variable declaration, functions with parameters and return values.
- Control flow: conditionals and loops.
- Interactive mode (REPL) and file execution.
- Examples included in `ejemplos/`.

## Project layout
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

## Build (quick)
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

## Usage
- Run a file: `./lenguaje ejemplos/hola.ld`
- REPL: `./lenguaje` (type `salir` to exit)

See `ESPECIFICACION.md` for full grammar and detailed examples.

## Known limitations
- No arrays/lists or dictionaries yet.
- Limited scope and deep recursion support.
- No multi-file/module support.
- No automated test suite yet.

## Planned extensions
- Arrays and collections.
- Dictionaries / maps.
- Exception handling (try/catch).
- Modules/imports and multi-file support.
- More standard library functions.

## Contributing
1. Open an issue to discuss large changes.
2. Fork and open a PR with your branch.
3. Include examples and reproduction steps.
