# Especificación Técnica del Lenguaje

## Visión General

El lenguaje es un intérprete recursivo descendente que procesa código fuente a través de tres fases:

1. **Análisis Léxico (Lexer)**: Tokenización del código fuente
2. **Análisis Sintáctico (Parser)**: Construcción del Árbol Sintáctico Abstracto (AST)
3. **Interpretación**: Evaluación y ejecución del AST

## Fases de Compilación

### 1. Análisis Léxico (Lexer)

El lexer (`Lexer.h`, `Lexer.cpp`) transforma el código fuente en una secuencia de tokens.

**Tokens Soportados:**
- Literales: números, textos, booleanos
- Identificadores
- Palabras clave: var, si, sino, mientras, para, funcion, retorna, escribir, leer
- Operadores: +, -, *, /, %, ==, !=, <, >, <=, >=, &&, ||, !
- Delimitadores: ( ) { } [ ] , ; : .

**Manejo de Comentarios:**
- Comentarios de línea: `// comentario`
- Comentarios de bloque: `/* comentario */`

### 2. Análisis Sintáctico (Parser)

El parser (`Parser.h`, `Parser.cpp`) implementa un analizador sintáctico recursivo descendente.

**Gramática Simplificada:**

```
programa → declaracion*

declaracion → var_decl
            | funcion_decl
            | si_stmt
            | mientras_stmt
            | para_stmt
            | escribir_stmt
            | leer_stmt
            | retorna_stmt
            | expresion

var_decl → 'var' IDENTIFICADOR '=' expresion ';'?

funcion_decl → 'funcion' IDENTIFICADOR '(' parametros? ')' '{' bloq '}'

si_stmt → 'si' '(' expresion ')' '{' bloque '}' ('sino' '{' bloque '}')?

mientras_stmt → 'mientras' '(' expresion ')' '{' bloque '}'

para_stmt → 'para' '(' IDENTIFICADOR '=' expresion ';' expresion ';' expresion ')' '{' bloque '}'

escribir_stmt → 'escribir' '(' expresion (',' expresion)* ')'

leer_stmt → 'leer' '(' IDENTIFICADOR ')'

retorna_stmt → 'retorna' expresion

bloque → declaracion*

expresion → asignacion

asignacion → IDENTIFICADOR ('=' | '+=' | '-=' | '*=' | '/=') expresion
           | expresion_logica_o

expresion_logica_o → expresion_logica_y ('||' expresion_logica_y)*

expresion_logica_y → igualdad ('&&' igualdad)*

igualdad → comparacion (('==' | '!=') comparacion)*

comparacion → aditiva (('<' | '>' | '<=' | '>=') aditiva)*

aditiva → multiplicativa (('+' | '-') multiplicativa)*

multiplicativa → unaria (('*' | '/' | '%') unaria)*

unaria → ('!' | '-') unaria | primaria

primaria → NUMERO
         | TEXTO
         | 'verdadero' | 'falso'
         | IDENTIFICADOR
         | IDENTIFICADOR '(' argumentos? ')'
         | '(' expresion ')'

argumentos → expresion (',' expresion)*
```

### 3. Árbol Sintáctico Abstracto (AST)

El AST (`AST.h`) define la estructura de los nodos del árbol sintáctico.

**Clases de Nodos:**

**Expresiones:**
- `NodoNumero`: valor numérico
- `NodoTexto`: cadena de texto
- `NodoBool`: valor booleano
- `NodoIdentificador`: referencia a variable
- `NodoOperacionBinaria`: a op b
- `NodoOperacionUnaria`: op a
- `NodoAsignacion`: var = valor
- `NodoLlamadaFuncion`: funcion(args)

**Declaraciones:**
- `NodoVariableNum`: var x = valor
- `NodoDeclaracionFuncion`: funcion nombre(params) { cuerpo }
- `NodoSi`: si (cond) { } [sino { }]
- `NodoMientras`: mientras (cond) { }
- `NodoPara`: para (v=inicio; fin; paso) { }
- `NodoBloque`: secuencia de declaraciones
- `NodoEscribir`: escribir(...)
- `NodoLeer`: leer(var)
- `NodoRetorna`: retorna expr

### 4. Intérprete

El intérprete (`Interprete.h`, `Interprete.cpp`) ejecuta el AST.

**Características:**

**Gestión de Escopo:**
- Cada función tiene su propio escopo
- Los escopos están anidados (closure)
- Las variables se resuelven recursivamente

```cpp
class Escopo {
    std::map<std::string, ValorTipo> variables;
    std::shared_ptr<Escopo> padre;
};
```

**Tipos de Datos:**
- Números: `double` (C++)
- Textos: `std::string` (C++)
- Booleanos: `bool` (C++)
- Representados con: `std::variant<double, std::string, bool>`

**Control de Flujo:**
- `si/sino`: ejecución condicional
- `mientras`: bucle while
- `para`: bucle for
- `retorna`: retorno de función

**Cortocircuito Lógico:**
- Operador `||` (o): si izquierda es verdadera, no evalúa derecha
- Operador `&&` (y): si izquierda es falsa, no evalúa derecha

## Estructura de Directorios

```
Lenguage/
├── main.cpp                    # Punto de entrada
├── README.md                   # Documentación del usuario
├── ESPECIFICACION.md           # Este archivo
├── CMakeLists.txt             # Configuración CMake
├── compilar.bat               # Script compilación Windows
├── compilar.sh                # Script compilación Linux/macOS
├── src/
│   ├── Token.h                # Definición de tokens
│   ├── Lexer.h/cpp            # Analizador léxico
│   ├── Parser.h/cpp           # Analizador sintáctico
│   ├── AST.h                  # Nodos del árbol sintáctico
│   └── Interprete.h/cpp       # Motor de ejecución
└── ejemplos/                  # Programas de ejemplo
    ├── hola.ld
    ├── operaciones.ld
    ├── condicionales.ld
    ├── while.ld
    ├── for.ld
    ├── funciones.ld
    ├── tablas.ld
    ├── logica.ld
    ├── textos.ld
    └── fibonacci.ld
```

## Elementos del Lenguaje

### Palabras Clave

| Palabra | Uso | Ejemplo |
|---------|-----|---------|
| `var` | Declarar variable | `var x = 5;` |
| `si` | Condicional if | `si (x > 0) { }` |
| `sino` | Condicional else | `} sino { }` |
| `mientras` | Bucle while | `mientras (x < 10) { }` |
| `para` | Bucle for | `para (i = 0; i < 10; i++) { }` |
| `funcion` | Declarar función | `funcion suma(a, b) { }` |
| `retorna` | Retornar valor | `retorna x * 2;` |
| `escribir` | Imprimir salida | `escribir("Hola");` |
| `leer` | Leer entrada | `leer(nombre);` |
| `verdadero` | Boolean true | `var ok = verdadero;` |
| `falso` | Boolean false | `var ok = falso;` |

### Operadores

**Precedencia (de mayor a menor):**

1. Primario: `( )`, números, textos, identificadores
2. Unario: `!`, `-`
3. Multiplicativo: `*`, `/`, `%`
4. Aditivo: `+`, `-`
5. Comparación: `<`, `>`, `<=`, `>=`
6. Igualdad: `==`, `!=`
7. Lógico Y: `&&`
8. Lógico O: `||`
9. Asignación: `=`, `+=`, `-=`, `*=`, `/=` (derecha asociativo)

### Reglas de Tipo

- **Conversión automática:** Los tipos se convierten implícitamente según el contexto
  - Número + Texto = Concatenación (resultado: texto)
  - Texto + Número = Concatenación
  - Comparación siempre compara numéricamente
  - Booleano a número: verdadero=1, falso=0
  - Número a booleano: 0=falso, cualquier otro=verdadero

- **Comparación de texto:** `"abc" == "abc"` compara como números (intenta convertir)

## Ejecución

### Modo Archivo
```bash
./lenguaje programa.ld
```

Pasos:
1. Leer archivo → string
2. Lexer.tokenizar() → vector de Token
3. Parser.parsear() → AST (NodoBloque)
4. Interprete.ejecutar(AST) → ejecución

### Modo Interactivo
```bash
./lenguaje
```

Permite escribir línea por línea hasta "salir"

## Errores y Excepciones

El lenguaje maneja errores mediante excepciones C++ `std::runtime_error`:

- "Variable no definida: nombre"
- "Función no definida: nombre"
- "Número incorrecto de argumentos"
- "División por cero"
- "El paso del bucle no puede ser cero"
- "Se esperaba token esperado en línea X"

## Optimizaciones

El intérprete es simple y directo:
- No usa compilación JIT
- No optimiza código
- Ejecuta el AST directamente
- Evaluación perezosa en expresiones lógicas

## Limitaciones Actuales

1. **Memory:** Gestión de memoria automática (RAII C++)
2. **Recursión:** Limitada por stack (típicamente ~1000 marcos)
3. **Números:** Usa `double` (límites de precisión)
4. **Strings:** Sin operaciones avanzadas (no hay métodos de string)
5. **Scope:** Todas las funciones comparten scope global
6. **Entrada:** `leer()` intenta convertir a número, sino guarda como texto

## Extensiones Sugeridas

1. **Arrays:** `var arr = [1, 2, 3];` `escribir(arr[0]);`
2. **For-Each:** `para (item en coleccion) { }`
3. **Try-Catch:** Manejo de excepciones
4. **Imports:** Múltiples archivos
5. **Clases:** OOP básico
6. **Métodos string:** `.length`, `.substring()`, etc.
7. **Función integrada:** `sqrt()`, `potencia()`, `aleatorio()`
8. **Estructuras:** `struct`, `class`

## Referencias Técnicas

- **Lenguaje:** C++17
- **Patrón de Diseño:** Visitor (evaluador), Builder (parser)
- **Gestión de Memoria:** shared_ptr para AST nodos
- **Tipo Variante:** std::variant para valores heterogéneos
