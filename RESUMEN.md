# Resumen del Proyecto - Lenguaje de Programación en Español

## 📋 Descripción

Se ha creado un **lenguaje de programación completo con sintaxis en español** junto con su propio intérprete implementado en C++. El proyecto incluye:

- ✅ Lexer (analizador léxico) para tokenización
- ✅ Parser (analizador sintáctico) con precedencia de operadores
- ✅ AST (Árbol Sintáctico Abstracto)
- ✅ Intérprete completo con evaluación de AST
- ✅ Soporte para variables, funciones, control de flujo
- ✅ 10 ejemplos de programas demostrados
- ✅ Documentación completa

---

## 📁 Estructura de Archivos

### Archivos Principales del Intérprete

| Archivo | Descripción |
|---------|-------------|
| **main.cpp** | Programa principal (REPL interactivo + ejecución de archivos) |
| **src/Token.h** | Definición de tipos de tokens |
| **src/Lexer.h/.cpp** | Analizador léxico (tokenización) |
| **src/Parser.h/.cpp** | Analizador sintáctico (construcción de AST) |
| **src/AST.h** | Nodos del árbol sintáctico abstracto |
| **src/Interprete.h/.cpp** | Intérprete (ejecución del AST) |

### Archivos de Configuración y Compilación

| Archivo | Descripción |
|---------|-------------|
| **CMakeLists.txt** | Configuración CMake para compilación |
| **compilar.bat** | Script de compilación para Windows |
| **compilar.sh** | Script de compilación para Linux/macOS |

### Ejemplos de Programas

| Archivo | Tema |
|---------|------|
| **ejemplos/hola.ld** | Hola Mundo |
| **ejemplos/operaciones.ld** | Operaciones aritméticas |
| **ejemplos/condicionales.ld** | Estructura if/else |
| **ejemplos/while.ld** | Bucles while |
| **ejemplos/for.ld** | Bucles for |
| **ejemplos/funciones.ld** | Declaración y uso de funciones |
| **ejemplos/tablas.ld** | Tablas de multiplicar |
| **ejemplos/logica.ld** | Operadores lógicos |
| **ejemplos/textos.ld** | Concatenación de strings |
| **ejemplos/fibonacci.ld** | Recursión - números de Fibonacci |

### Documentación

| Archivo | Contenido |
|---------|----------|
| **README.md** | Guía de usuario completa |
| **ESPECIFICACION.md** | Especificación técnica detallada |
| **INSTALACION.md** | Instrucciones de instalación de compiladores |
| **RESUMEN.md** | Este archivo |

---

## 🎯 Características del Lenguaje

### Palabras Clave
```
var, si, sino, mientras, para, funcion, retorna, escribir, leer
verdadero, falso
```

### Tipos de Datos
- Números (enteros y decimales)
- Textos (cadenas)
- Booleanos (verdadero/falso)

### Operadores Soportados

**Aritméticos:** `+` `-` `*` `/` `%`
**Comparadores:** `==` `!=` `<` `>` `<=` `>=`
**Lógicos:** `&&` `||` `!`
**Asignación:** `=` `+=` `-=` `*=` `/=`

### Características del Lenguaje

✅ **Variables dinámicas**
✅ **Tipos implícitos**
✅ **Funciones con parámetros y retorno**
✅ **Control de flujo (if/else, while, for)**
✅ **Entrada/Salida (escribir, leer)**
✅ **Operadores lógicos con cortocircuito**
✅ **Concatenación de strings**
✅ **Comentarios (// y /* */)**
✅ **Recursión**

---

## 💻 Compilación y Uso

### Compilación Rápida

**Windows (con g++ instalado):**
```bash
cd c:\Users\lfcre\OneDrive\Desktop\Lenguage
.\compilar.bat
```

**Linux/macOS:**
```bash
cd ~/Lenguage
chmod +x compilar.sh
./compilar.sh
```

### Ejecución

**Ejecutar un archivo:**
```bash
./lenguaje ejemplos/hola.ld
```

**Modo interactivo:**
```bash
./lenguaje
```

---

## 📚 Ejemplos de Código

### Hola Mundo
```
escribir("¡Hola, Mundo!");
```

### Variables y Operaciones
```
var x = 10;
var y = 20;
var resultado = x + y;
escribir("Resultado:", resultado);
```

### Condicionales
```
var edad = 18;
si (edad >= 18) {
    escribir("Mayor de edad");
} sino {
    escribir("Menor de edad");
}
```

### Bucles
```
para (i = 1; i <= 5; i = i + 1) {
    escribir("Número:", i);
}
```

### Funciones
```
funcion saludar(nombre) {
    escribir("¡Hola,", nombre, "!");
}

saludar("Juan");
saludar("María");
```

### Recursión
```
funcion factorial(n) {
    si (n <= 1) {
        retorna 1;
    }
    retorna n * factorial(n - 1);
}

escribir("Factorial de 5:", factorial(5));
```

---

## 🔧 Componentes Técnicos

### 1. Lexer (Análisis Léxico)
- Tokeniza el código fuente
- Reconoce palabras clave, operadores, literales
- Maneja comentarios
- Reporta errores de léxico

### 2. Parser (Análisis Sintáctico)
- Implementa análisis recursivo descendente
- Respeta precedencia de operadores
- Construye el AST
- Reporta errores de sintaxis

### 3. AST (Árbol Sintáctico Abstracto)
- Representa la estructura del programa
- Nodos para expresiones y declaraciones
- Tipos: Número, Texto, Bool, Identificador, etc.

### 4. Intérprete
- Ejecuta el AST
- Gestiona escopos y variables
- Maneja funciones con cierres (closures)
- Ejecuta control de flujo
- Implementa evaluación perezosa (lazy evaluation)

---

## 📊 Estadísticas del Proyecto

- **Líneas de código C++:** ~1000+ líneas (sin ejemplos)
- **Archivos fuente:** 6 archivos (.h y .cpp)
- **Ejemplos:** 10 programas demostrados
- **Palabras clave:** 11
- **Operadores:** 20+
- **Tipos de tokens:** 40+

---

## 🚀 Cómo Comenzar

1. **Instalar compilador C++** (ver INSTALACION.md)
2. **Compilar el proyecto:**
   ```bash
   g++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje
   ```
3. **Ejecutar un ejemplo:**
   ```bash
   ./lenguaje ejemplos/hola.ld
   ```
4. **Explorar los ejemplos** en la carpeta `ejemplos/`
5. **Crear tu propio programa** (extensión `.ld`)

---

## 🛠️ Tecnologías Utilizadas

- **Lenguaje:** C++17
- **Patrones de Diseño:** Visitor, Builder
- **Conceptos:** Interpretación de lenguajes, AST, Parsing
- **Librerías:** STL únicamente (std::vector, std::map, std::string, std::variant)

---

## 📖 Documentación Disponible

1. **README.md** - Manual de usuario con guía de sintaxis
2. **ESPECIFICACION.md** - Especificación técnica completa
3. **INSTALACION.md** - Cómo instalar compiladores
4. **Comentarios en código** - Explicaciones en archivos fuente

---

## 🎓 Concepto Educativo

Este proyecto demuestra:
- ✅ Cómo diseñar un lenguaje de programación
- ✅ Implementación de análisis léxico
- ✅ Implementación de análisis sintáctico
- ✅ Construcción de AST
- ✅ Interpretación de código
- ✅ Gestión de escopo y variables
- ✅ Implementación de funciones y cierres

---

## 📝 Nota Final

El lenguaje está completamente funcional y puede ejecutar programas complejos incluyendo recursión, funciones anidadas, bucles y condicionales. Es una excelente base para aprender sobre construcción de intérpretes o para ser extendido con nuevas características.

**¡El intérprete está listo para usar!**
