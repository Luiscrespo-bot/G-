# 📑 Índice de Archivos del Proyecto

## 📂 Estructura del Proyecto

```
Lenguage/
│
├── 📄 INICIO.md                    ← COMIENZA AQUÍ (guía rápida)
├── 📄 IDE_RAPIDO.md                ← Guía rápida de IDE web
├── 📄 README.md                    ← Documentación del lenguaje
├── 📄 ESPECIFICACION.md            ← Especificación técnica
├── 📄 INSTALACION.md               ← Instalar compiladores
├── 📄 IDE.md                       ← Documentación completa de IDE
├── 📄 RESUMEN.md                   ← Resumen del proyecto
│
├── 🔧 Compilación - Intérprete CLI
│   ├── compilar.bat                ← Script para Windows
│   └── compilar.sh                 ← Script para Linux/macOS
│
├── 🔧 Compilación - IDE Web
│   ├── compilar_ide.bat            ← Script para Windows (NUEVO)
│   └── compilar_ide.sh             ← Script para Linux/macOS (NUEVO)
│
├── 💻 Programas Principales
│   ├── main.cpp                    ← Intérprete CLI
│   └── ide_main.cpp                ← IDE Web (NUEVO)
│
├── CMakeLists.txt                  ← Configuración CMake
│
├── 📁 src/                         ← Código fuente del intérprete
│   ├── Token.h
│   ├── Lexer.h/.cpp
│   ├── Parser.h/.cpp
│   ├── AST.h
│   ├── Interprete.h/.cpp
│   └── ServidorHTTP.h/.cpp        ← Servidor HTTP (NUEVO)
│
└── 📁 ejemplos/                    ← Programas de ejemplo
    ├── hola.ld
    ├── operaciones.ld
    ├── condicionales.ld
    ├── while.ld
    ├── for.ld
    ├── funciones.ld
    ├── tablas.ld
    ├── logica.ld
    ├── textos.ld
    ├── fibonacci.ld
    └── completo.ld
```

## 📖 Dónde Empezar

### Para Usuarios Nuevos

**Opción A (RECOMENDADO): IDE Web**
1. Lee **IDE_RAPIDO.md** (2 minutos)
2. Compila con `compilar_ide.bat/sh`
3. Ejecuta `lenguaje_ide`
4. Abre navegador en `http://127.0.0.1:8080`
5. ¡A programar!

**Opción B: Intérprete CLI**
1. Lee **INICIO.md** (5 minutos)
2. Lee **INSTALACION.md** (instala compilador)
3. Compila con `compilar.bat/sh`
4. Ejecuta `./lenguaje programa.ld`

### Para Desarrolladores

1. Lee **ESPECIFICACION.md** para entender la arquitectura
2. Explora **src/** para ver la implementación
3. Para IDE: revisa **src/ServidorHTTP.cpp**
4. Lee **ide_main.cpp** para integración

### Para Educadores

1. **INICIO.md** - Introducción rápida
2. **README.md** - Guía de sintaxis
3. **ejemplos/** - Aprende escribiendo código
4. **ESPECIFICACION.md** - Conceptos avanzados

---

## 📝 Descripción de Archivos Clave

### 🆕 IDE Web (NUEVO)

**IDE.md** (~5 KB)
- Documentación completa de la IDE web
- Cómo compilar y ejecutar
- Características detalladas
- Solución de problemas

**IDE_RAPIDO.md** (~1 KB)
- Guía de 3 pasos
- Comandos esenciales
- Atajos de teclado

**ide_main.cpp** (~50 líneas)
- Programa principal de la IDE
- Integración servidor + intérprete
- Captura de salida

**src/ServidorHTTP.h/.cpp** (~700 líneas)
- Servidor HTTP simple
- Interfaz HTML/CSS/JS incorporada
- Procesamiento de solicitudes JSON
- Ejecución aislada de código

---

### Documentación Original

**INICIO.md** (actualizado)
- Ahora incluye IDE como opción primaria
- Guía rápida de 5 minutos
- Dos caminos: IDE o CLI

**README.md**
- Características del lenguaje
- Sintaxis completa
- Ejemplos por tópico
- Limitaciones conocidas

**ESPECIFICACION.md**
- Detalles técnicos
- Fases de compilación
- Gramática formal
- Implementación

**INSTALACION.md**
- Instrucciones para Windows, macOS, Linux
- Múltiples opciones de compiladores
- Verificación

**RESUMEN.md**
- Perfil del proyecto
- Estadísticas
- Tecnologías usadas

---

### Código Fuente (src/)

**Token.h** (1.4 KB)
- Enumeración de tipos
- Estructura Token

**Lexer (h/cpp)** (10 KB)
- Análisis léxico
- Tokenización

**Parser (h/cpp)** (16 KB)
- Análisis sintáctico
- Construcción AST

**AST.h** (5 KB)
- Definición de nodos
- Expresiones y declaraciones

**Interprete (h/cpp)** (16 KB)
- Ejecución del AST
- Gestión de variables
- Control de flujo

**ServidorHTTP (h/cpp)** (13 KB) 🆕
- Servidor HTTP
- Interfaz web
- Procesamiento de código

---

## 🚀 Pasos Rápidos

### IDE Web (RECOMENDADO)

```bash
# 1. Compilar
compilar_ide.bat           # Windows
./compilar_ide.sh          # Linux/macOS

# 2. Ejecutar
lenguaje_ide.exe           # Windows
./lenguaje_ide             # Linux/macOS

# 3. Abrir navegador
http://127.0.0.1:8080
```

### Intérprete CLI

```bash
# 1. Compilar
compilar.bat               # Windows
./compilar.sh              # Linux/macOS

# 2. Ejecutar
lenguaje archivo.ld        # Ejecutar archivo
lenguaje                   # Modo interactivo
```

---

## ✅ Lista de Verificación

**Nuevo en esta versión:**
- ✅ IDE Web completa
- ✅ Servidor HTTP integrado
- ✅ Interfaz HTML/CSS/JavaScript
- ✅ Ejemplos incorporados
- ✅ Documentación de IDE
- ✅ Scripts de compilación de IDE

**Características existentes:**
- ✅ Documentación completa
- ✅ Código fuente bien comentado
- ✅ 11 ejemplos funcionales
- ✅ Especificación técnica
- ✅ Guía de inicio rápido

---

## 📊 Estadísticas Actualizadas

### Archivos
- **Total:** 35 (agregamos IDE web)
- **Documentación:** 8 archivos
- **Código fuente:** 9 archivos (+ ServidorHTTP)
- **Ejemplos:** 11 programas
- **Configuración:** 4 archivos

### Líneas de Código
- **Total C++:** ~2,600 líneas (agregamos servidor)
- **ServidorHTTP:** ~400 líneas
- **IDE:** ~50 líneas (main)
- **Total proyecto:** ~135 KB

---

## 🎯 Elección: IDE vs CLI

| Aspecto | IDE Web | CLI |
|---------|---------|-----|
| **Facilidad** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ |
| **Visual** | ⭐⭐⭐⭐⭐ | ⭐ |
| **Rápido** | ⭐⭐⭐⭐⭐ | ⭐⭐ |
| **Control** | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| **Moderno** | ⭐⭐⭐⭐⭐ | ⭐⭐ |

**Recomendado:** IDE Web para principiantes, CLI para desarrollo

---

**¡El proyecto ahora tiene IDE web integrada!** 🎉
