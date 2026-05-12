# Lenguaje de Programación en Español

## Descripción

Este proyecto implementa un lenguaje de programación simple con sintaxis completamente en español, incluyendo su propio intérprete escrito en C++. El lenguaje soporta variables, tipos básicos, operaciones aritméticas, control de flujo, y funciones.

## Características

- **Sintaxis en Español**: Todas las palabras clave están en español
- **Tipos de Datos Soportados**:
  - Números (decimales e enteros)
  - Texto (cadenas de caracteres)
  - Booleanos (verdadero/falso)
- **Características**:
  - Variables con declaração `var`
  - Operaciones aritméticas: `+`, `-`, `*`, `/`, `%`
  - Comparadores: `==`, `!=`, `<`, `>`, `<=`, `>=`
  - Operadores lógicos: `&&`, `||`, `!`
  - Control condicional: `si`, `sino`
  - Bucles: `mientras`, `para`
  - Funciones con parámetros y retorno
  - Entrada/Salida: `escribir`, `leer`

## Estructura del Proyecto

```
Lenguage/
├── src/
│   ├── Token.h              # Definición de tokens
│   ├── Lexer.h              # Analizador léxico
│   ├── Lexer.cpp
│   ├── Parser.h             # Analizador sintáctico
│   ├── Parser.cpp
│   ├── AST.h                # Árbol sintáctico abstracto
│   ├── Interprete.h         # Intérprete
│   └── Interprete.cpp
├── ejemplos/                # Ejemplos de programas
│   ├── hola.ld
│   ├── operaciones.ld
│   ├── condicionales.ld
│   ├── while.ld
│   ├── for.ld
│   ├── funciones.ld
│   ├── tablas.ld
│   ├── logica.ld
│   ├── textos.ld
│   └── fibonacci.ld
├── main.cpp                 # Programa principal
├── CMakeLists.txt          # Configuración CMake
└── README.md               # Este archivo
```

## Compilación

### Con CMake (Recomendado)

```bash
cd Lenguage
mkdir build
cd build
cmake ..
cmake --build .
```

### Compilación manual (g++)

```bash
g++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje
```

### Compilación manual (Visual Studio)

```bash
cl /std:c++latest src\Lexer.cpp src\Parser.cpp src\Interprete.cpp main.cpp
```

## Uso

### Ejecutar un archivo
```bash
./lenguaje ejemplos/hola.ld
```

### Modo interactivo
```bash
./lenguaje
```

## Guía de Sintaxis

### Variables

```
var nombre = valor;
```

Ejemplos:
```
var x = 10;
var mensaje = "Hola";
var esVerdad = verdadero;
```

### Operaciones Aritméticas

```
var a = 10;
var b = 3;
var suma = a + b;           // 13
var resta = a - b;          // 7
var multiplicacion = a * b; // 30
var division = a / b;       // 3.33
var modulo = a % b;         // 1
```

### Comparaciones y Lógica

```
si (x > 5 && y < 10) {
    escribir("Condición cumplida");
}

si (a == b || c != d) {
    escribir("Una de las condiciones es verdadera");
}
```

### Control Condicional

#### Si/Sino
```
si (condicion) {
    // código si verdadero
} sino {
    // código si falso
}
```

Ejemplo:
```
var edad = 18;
si (edad >= 18) {
    escribir("Eres mayor de edad");
} sino {
    escribir("Eres menor de edad");
}
```

### Bucles

#### Bucle Mientras
```
mientras (condicion) {
    // código que se repite
}
```

Ejemplo:
```
var contador = 0;
mientras (contador < 5) {
    escribir(contador);
    contador = contador + 1;
}
```

#### Bucle Para
```
para (variable = inicio; fin; paso) {
    // código que se repite
}
```

Ejemplo:
```
para (i = 1; i <= 10; i = i + 1) {
    escribir(i);
}
```

### Funciones

#### Declaración
```
funcion nombre(parametro1, parametro2) {
    // código de la función
}
```

#### Con retorno
```
funcion cuadrado(x) {
    retorna x * x;
}

var resultado = cuadrado(5);  // resultado = 25
```

Ejemplo completo:
```
funcion sumar(a, b) {
    retorna a + b;
}

var resultado = sumar(3, 4);
escribir("La suma es:", resultado);
```

### Entrada/Salida

#### Escribir (Salida)
```
escribir("texto");
escribir(variable);
escribir("múltiples", "argumentos", 123);
```

Ejemplo:
```
var nombre = "Juan";
var edad = 25;
escribir("Nombre:", nombre);
escribir("Edad:", edad);
```

#### Leer (Entrada)
```
leer(variable_nombre);
```

Ejemplo:
```
escribir("¿Cuál es tu nombre?");
leer(nombre);
escribir("Hola,", nombre);
```

### Concatenación de Textos

```
var a = "Hola";
var b = "Mundo";
var resultado = a + " " + b;  // "Hola Mundo"
```

### Comentarios

Comentarios de línea única:
```
// Este es un comentario
var x = 5;  // Esto también es un comentario
```

Comentarios de múltiples líneas:
```
/* Esto es un comentario
   que abarca
   varias líneas */
```

## Tipos de Datos

### Números
- Soportan enteros y decimales
- Operaciones: `+`, `-`, `*`, `/`, `%`

### Textos (Strings)
- Encerrados en comillas simples o dobles
- Concatenación con `+`
- Secuencias de escape: `\n` (salto de línea), `\t` (tabulación)

### Booleanos
- Valores: `verdadero`, `falso`
- Usados en condicionales
- Resultado de comparaciones

## Operadores

### Aritméticos
- `+` Suma
- `-` Resta
- `*` Multiplicación
- `/` División
- `%` Módulo (residuo)

### Comparadores
- `==` Igual
- `!=` No igual
- `<` Menor
- `>` Mayor
- `<=` Menor o igual
- `>=` Mayor o igual

### Lógicos
- `&&` Y (AND)
- `||` O (OR)
- `!` NO (NOT)

### Asignación
- `=` Asignación
- `+=` Suma y asigna
- `-=` Resta y asigna
- `*=` Multiplica y asigna
- `/=` Divide y asigna

## Ejemplos de Programas

### 1. Hola Mundo
```
escribir("¡Hola, Mundo!");
```

### 2. Tabla de Multiplicar
```
funcion tabla(numero) {
    para (i = 1; i <= 10; i = i + 1) {
        var resultado = numero * i;
        escribir(numero, "x", i, "=", resultado);
    }
}

tabla(5);
```

### 3. Números de Fibonacci
```
funcion fibonacci(n) {
    si (n <= 1) {
        retorna n;
    }
    retorna fibonacci(n - 1) + fibonacci(n - 2);
}

para (i = 0; i < 10; i = i + 1) {
    escribir(fibonacci(i));
}
```

### 4. Verificar si es par o impar
```
funcion es_par(numero) {
    si (numero % 2 == 0) {
        retorna verdadero;
    }
    retorna falso;
}

var num = 7;
si (es_par(num)) {
    escribir(num, "es par");
} sino {
    escribir(num, "es impar");
}
```

## Limitaciones Conocidas

- No soporta arrays/listas
- No soporta estructuras de datos complejas
- No soporta recursión profunda (limitada por el stack)
- No soporta múltiples archivos
- No soporta scope global vs local específico (todas las funciones comparten scope global)

## Extensiones Futuras

- Arrays y listas
- Diccionarios/mapas
- Excepciones con try/catch
- Módulos e importación
- Clases y programación orientada a objetos
- Más funciones integradas (sqrt, abs, etc.)

## Problemas Comunes

### Error: "Variable no definida"
Asegúrate de declarar la variable con `var` antes de usarla.

### Error: "División por cero"
Verifica que no estés intentando dividir entre cero.

### El bucle `para` no se ejecuta
Verifica que el paso no sea cero y que la condición sea correcta.

### Las funciones no retornan valor
Usa `retorna` para devolver un valor de una función.

## Autor
Luis Fernando Crespo Soliz 
 Intérprete creado en C++ con lexer, parser e intérprete personalizado.

## Licencia

Libre para usar y modificar.
