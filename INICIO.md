# 🚀 Guía Rápida de Inicio

## ¿Qué es esto?

Un **lenguaje de programación completo escrito en español** con su propio intérprete en C++.

Tienes **dos opciones**:
1. **IDE Web** (más fácil) - Interfaz gráfica en el navegador
2. **Intérprete CLI** (tradicional) - Ejecutar desde línea de comandos

## ⚡ OPCIÓN 1: IDE Web (RECOMENDADO)

### En 3 pasos:

```bash
# 1. Compilar
.\compilar_ide.bat        # Windows
./compilar_ide.sh         # Linux/macOS

# 2. Ejecutar
lenguaje_ide.exe          # Windows
./lenguaje_ide            # Linux/macOS

# 3. Abrir en navegador
http://127.0.0.1:8080
```

¡Listo! Escribe código y presiona Ctrl+Enter

✨ **Ventajas de la IDE:**
- No necesita línea de comandos
- Interfaz visual moderna
- Ejemplos incorporados
- Sin necesidad de guardar archivos

---

## ⚡ OPCIÓN 2: Intérprete CLI

### Paso 1: Instalar Compilador C++

**Windows:**
- Descarga MinGW-w64 desde https://www.mingw-w64.org/

**macOS:**
```bash
brew install gcc
```

**Linux (Ubuntu/Debian):**
```bash
sudo apt install build-essential
```

### Paso 2: Compilar

```bash
g++ -std=c++17 src/Lexer.cpp src/Parser.cpp src/Interprete.cpp main.cpp -o lenguaje
```

### Paso 3: Ejecutar tu primer programa

```bash
./lenguaje ejemplos/hola.ld
```

Resultado:
```
¡Hola, Mundo!
```

---

## 📝 Ejemplo Básico

### Con IDE Web:

Copia esto en el editor:
```
var nombre = "Juan";
var edad = 25;
escribir("Hola,", nombre);
escribir("Edad:", edad);
```

Presiona **Ctrl+Enter**

### Con Intérprete:

Crea archivo `programa.ld`:
```
var nombre = "Juan";
var edad = 25;
escribir("Hola,", nombre);
escribir("Edad:", edad);
```

Ejecuta:
```bash
./lenguaje programa.ld
```

---

## 🎯 Palabras Clave Principales

| Palabra | Uso |
|---------|-----|
| `var` | Crear variable |
| `si` / `sino` | If / else |
| `mientras` | While |
| `para` | For |
| `funcion` | Crear función |
| `retorna` | Return |
| `escribir` | Print |
| `leer` | Input |

## 💡 Ejemplos Rápidos

### Condicional
```
si (10 > 5) {
    escribir("Diez es mayor que cinco");
}
```

### Bucle
```
para (i = 1; i <= 5; i = i + 1) {
    escribir("Número:", i);
}
```

### Función
```
funcion doble(x) {
    retorna x * 2;
}

escribir(doble(5));
```

---

## 📂 Estructura del Proyecto

```
Lenguage/
├── IDE Web (nuevo)
│   ├── ide_main.cpp        ← Programa de la IDE
│   ├── compilar_ide.bat    ← Compilar en Windows
│   ├── compilar_ide.sh     ← Compilar en Linux/macOS
│   ├── IDE.md              ← Doc completa de IDE
│   └── IDE_RAPIDO.md       ← Guía rápida de IDE
│
├── Intérprete CLI
│   ├── main.cpp            ← Programa principal
│   ├── compilar.bat        ← Compilar en Windows
│   ├── compilar.sh         ← Compilar en Linux/macOS
│   └── src/                ← Código del intérprete
│
└── Documentación
    ├── README.md
    ├── ESPECIFICACION.md
    └── INSTALACION.md
```

---

## 🔍 Ver Ejemplos

### Con IDE Web:
Selecciona en "Cargar Ejemplo..."

### Con Intérprete:
```bash
./lenguaje ejemplos/hola.ld
./lenguaje ejemplos/operaciones.ld
./lenguaje ejemplos/funciones.ld
./lenguaje ejemplos/fibonacci.ld
```

---

## 🐛 Solución de Problemas

### IDE no abre
1. Verifica que el servidor está corriendo
2. Intenta `http://localhost:8080` en lugar de `127.0.0.1`

### Compilador no encontrado
Revisa **INSTALACION.md**

### Error de sintaxis
Revisa **README.md** para la sintaxis correcta

---

## 📖 Documentación

- **INICIO.md** (este) - Guía de 5 minutos
- **IDE_RAPIDO.md** - Guía rápida de IDE
- **IDE.md** - Documentación completa de IDE
- **README.md** - Manual de sintaxis del lenguaje
- **ESPECIFICACION.md** - Detalles técnicos
- **INSTALACION.md** - Instalar compiladores

---

## 🎓 Próximos Pasos

1. **IDE Web** - Copia/pega un ejemplo y experimenta
2. **CLI** - Crea tu primer archivo `.ld`
3. **Aprende** - Lee los ejemplos en la carpeta `ejemplos/`
4. **Crea** - Escribe tus propios programas

---

## 🎉 ¡Felicidades!

Ya tienes todo lo que necesitas para programar en español.

**Elige tu preferencia:**
- 👨‍💻 **Fácil**: IDE Web 
- 🖥️ **Clásico**: Intérprete CLI
