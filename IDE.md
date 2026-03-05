# 🖥️ IDE Web - Lenguaje de Programación en Español

## ¿Qué es?

Una interfaz web moderna y fácil de usar para escribir y ejecutar código en el lenguaje de programación en español. ¡Sin necesidad de compilar archivos!

## ✨ Características

- ✅ **Editor de código** - Sintaxis clara y fácil de leer
- ✅ **Ejecución instantánea** - Presiona Ctrl+Enter o haz clic en "Ejecutar"
- ✅ **Ejemplos incorporados** - 5 ejemplos para aprender rápidamente
- ✅ **Interfaz moderna** - Diseño limpio y responsivo
- ✅ **Salida en tiempo real** - Ve los resultados inmediatamente
- ✅ **Sin instalación** - Solo necesitas un navegador web

## 🚀 Iniciar la IDE

### Paso 1: Compilar la IDE

**Windows:**
```bash
.\compilar_ide.bat
```

**Linux/macOS:**
```bash
chmod +x compilar_ide.sh
./compilar_ide.sh
```

### Paso 2: Ejecutar el servidor

**Windows:**
```bash
lenguaje_ide.exe
```

**Linux/macOS:**
```bash
./lenguaje_ide
```

Verás:
```
Servidor iniciado en: http://127.0.0.1:8080
📝 Presiona Ctrl+C para detener
```

### Paso 3: Abrir en navegador

Abre tu navegador y ve a:
```
http://127.0.0.1:8080
```

¡Ya puedes escribir código!

## 📖 Cómo Usar

### Escribir Código

1. Haz clic en el área de texto de "Editor de Código"
2. Escribe tu código en español
3. Presiona **Ctrl+Enter** o haz clic en el botón **"▶ Ejecutar"**

### Ejemplos Rápidos

La IDE viene con 5 ejemplos:
- **Hola Mundo** - Comienza aquí
- **Operaciones** - Aritméticas básicas
- **Condicionales** - Si/Sino
- **Bucle FOR** - Bucles
- **Funciones** - Crear funciones

Selecciona uno en el desplegable "Cargar Ejemplo..."

## 🎯 Ejemplo Completo

```
var nombre = "Juan";
var edad = 25;

si (edad >= 18) {
    escribir(nombre, "es mayor de edad");
} sino {
    escribir(nombre, "es menor de edad");
}

para (i = 1; i <= 5; i = i + 1) {
    escribir("Número:", i);
}
```

Resultado:
```
Juan es mayor de edad
Número: 1
Número: 2
Número: 3
Número: 4
Número: 5
```

## ⌨️ Atajos de Teclado

| Atajo | Acción |
|-------|--------|
| **Ctrl+Enter** | Ejecutar código |
| **Tab** | Indentación |
| **Ctrl+A** | Seleccionar todo |

## 🔧 Opciones Avanzadas

### Cambiar el Puerto

Por defecto, la IDE usa el puerto 8080. Para cambiar:

```bash
lenguaje_ide 3000
```

Luego abre: `http://127.0.0.1:3000`

### Puertos Comunes

- 8080 (defecto)
- 3000 (desarrollo)
- 5000 (Flask)
- 8000 (Django)

## 🐛 Solución de Problemas

### "No se puede conectar al servidor"

1. Verifica que el servidor está corriendo
2. Verifica que usas el puerto correcto
3. Intenta `http://localhost:8080` en lugar de `127.0.0.1`

### "Puerto ya está en uso"

```bash
lenguaje_ide 8081
```

### IDE se ve roto (sin estilos)

1. Recarga la página (F5)
2. Limpia el caché del navegador (Ctrl+Shift+Delete)

## 📝 Características Principales

### Resaltado de Código

Los ejemplos muestran la sintaxis correcta:

```
var x = 10;          // Variable
si (x > 5) { }       // Condicional
para (i = 0; i < 10; i = i + 1) { }  // Bucle
funcion suma(a, b) { retorna a + b; } // Función
escribir(x);         // Salida
```

### Manejo de Errores

Si hay un error, se muestra en rojo:

```
Error: Variable no definida: variable_inexistente
```

### Salida Formateada

La salida se muestra en una consola estilo terminal.

## 🎨 Personalización

### Tamaños de Pantalla

La IDE es **responsive**:
- **Escritorio** - Editor y salida lado a lado
- **Tablet** - Editor arriba, salida abajo
- **Móvil** - Stack vertical

## 📚 Integración con Ejemplos

Todos los ejemplos de la carpeta `ejemplos/` están disponibles:

- `hola.ld` ➜ Hola Mundo
- `operaciones.ld` ➜ Operaciones
- `condicionales.ld` ➜ Condicionales
- `for.ld` ➜ Bucle FOR
- `funciones.ld` ➜ Funciones

Selecciona uno en "Cargar Ejemplo..."

## 🔒 Seguridad

La IDE:
- ✅ Ejecuta código de forma aislada
- ✅ No almacena datos personales
- ✅ Solo para uso local

## 🌐 Compatibilidad de Navegadores

| Navegador | Compatible |
|-----------|-----------|
| Chrome | ✅ Sí |
| Firefox | ✅ Sí |
| Safari | ✅ Sí |
| Edge | ✅ Sí |
| IE11 | ⚠️ Parcial |

## 💻 Requisitos

- **Servidor:** C++ con soporte para C++17
- **Cliente:** Navegador moderno con JavaScript
- **RAM:** Mínimo 50 MB
- **Red:** Solo necesita localhost

## 🚀 Primeros Pasos (Video)

1. Compilar IDE
2. Ejecutar servidor
3. Abrir navegador
4. Escribir código
5. Presionar Ctrl+Enter

## 📊 Estadísticas

- **Interfaz web:** ~500 líneas HTML/CSS/JS
- **Servidor HTTP:** ~400 líneas C++
- **Tamaño total:** ~900 líneas
- **Tiempo de respuesta:** <100ms

## 🎓 Aprende Escribiendo

La mejor forma de aprender es escribiendo código:

1. Abre la IDE
2. Modifica los ejemplos
3. Experimenta con nuevas características
4. Crea tus propios programas

## 💡 Consejos

- **Comienza simple** - Hola Mundo primero
- **Lee ejemplos** - Aprende de los disponibles
- **Experimenta** - Cambia y prueba cosas
- **Guarda tu código** - Copia/pega en un archivo `.ld`

## 🔗 Información Útil

- **Puerto defecto:** 8080
- **URL local:** http://127.0.0.1:8080
- **Para detener:** Ctrl+C en la consola

## 📞 Soporte

Si hay problemas:
1. Revisa los errores en la consola del navegador (F12)
2. Verifica que el servidor está corriendo
3. Intenta refrescar la página (F5)
4. Intenta otro puerto: `lenguaje_ide 8000`

---

**¡Disfruta programando en español!** 🎉
