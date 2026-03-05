// Ejemplo Completo: Demostra todas las características del lenguaje

// ============================================
// FUNCIONES ÚTILES
// ============================================

funcion es_par(numero) {
    retorna numero % 2 == 0;
}

funcion es_primo(n) {
    si (n < 2) {
        retorna falso;
    }
    
    para (i = 2; i * i <= n; i = i + 1) {
        si (n % i == 0) {
            retorna falso;
        }
    }
    retorna verdadero;
}

funcion suma_hasta(n) {
    var suma = 0;
    para (i = 1; i <= n; i = i + 1) {
        suma = suma + i;
    }
    retorna suma;
}

funcion potencia(base, exponente) {
    si (exponente == 0) {
        retorna 1;
    }
    
    var resultado = 1;
    para (i = 1; i <= exponente; i = i + 1) {
        resultado = resultado * base;
    }
    retorna resultado;
}

// ============================================
// PROGRAMA PRINCIPAL
// ============================================

escribir("=====================================");
escribir("Demostración del Lenguaje en Español");
escribir("=====================================");
escribir("");

// --- SECCIÓN 1: Variables y Operaciones ---
escribir("--- 1. Variables y Operaciones ---");
var a = 15;
var b = 8;
var c = a + b;
escribir("a =", a, ", b =", b);
escribir("a + b =", c);
escribir("a - b =", a - b);
escribir("a * b =", a * b);
escribir("a / b =", a / b);
escribir("a % b =", a % b);
escribir("");

// --- SECCIÓN 2: Condicionales ---
escribir("--- 2. Condicionales (Si/Sino) ---");
si (c > 20) {
    escribir("c es mayor que 20");
} sino {
    escribir("c no es mayor que 20");
}

var numero = 42;
si (es_par(numero)) {
    escribir(numero, "es par");
} sino {
    escribir(numero, "es impar");
}
escribir("");

// --- SECCIÓN 3: Bucles Mientras ---
escribir("--- 3. Bucles Mientras ---");
escribir("Contando del 1 al 5:");
var contador = 1;
mientras (contador <= 5) {
    escribir("  Contador:", contador);
    contador = contador + 1;
}
escribir("");

// --- SECCIÓN 4: Bucles Para ---
escribir("--- 4. Bucles Para ---");
escribir("Números pares del 1 al 10:");
para (i = 1; i <= 10; i = i + 1) {
    si (es_par(i)) {
        escribir("  ", i);
    }
}
escribir("");

// --- SECCIÓN 5: Funciones ---
escribir("--- 5. Llamadas a Funciones ---");
var num1 = 15;
escribir("¿Es", num1, "primo?", es_primo(num1));

var num2 = 17;
escribir("¿Es", num2, "primo?", es_primo(num2));
escribir("");

// --- SECCIÓN 6: Suma Acumulativa ---
escribir("--- 6. Suma Acumulativa ---");
var limite = 10;
var resultado = suma_hasta(limite);
escribir("La suma de 1 a", limite, "es:", resultado);
escribir("");

// --- SECCIÓN 7: Potencias ---
escribir("--- 7. Potencias ---");
para (i = 1; i <= 4; i = i + 1) {
    var pot = potencia(2, i);
    escribir("2 elevado a", i, "=", pot);
}
escribir("");

// --- SECCIÓN 8: Operadores Lógicos ---
escribir("--- 8. Operadores Lógicos ---");
var x = 10;
var y = 20;

si (x > 5 && y > 15) {
    escribir("x > 5 AND y > 15: verdadero");
}

si (x < 5 || y < 15) {
    escribir("x < 5 OR y < 15: verdadero");
} sino {
    escribir("Ambas condiciones son falsas");
}

var condicion = verdadero;
si (!condicion) {
    escribir("Condición es falsa");
} sino {
    escribir("NOT verdadero = falso");
}
escribir("");

// --- SECCIÓN 9: Función Factorial ---
escribir("--- 9. Función Factorial ---");
funcion factorial(n) {
    si (n <= 1) {
        retorna 1;
    }
    retorna n * factorial(n - 1);
}

para (i = 1; i <= 5; i = i + 1) {
    var fact = factorial(i);
    escribir(i, "! =", fact);
}
escribir("");

// --- SECCIÓN 10: Strings y Concatenación ---
escribir("--- 10. Strings y Concatenación ---");
var nombre = "Carlos";
var apellido = "García";
var nombre_completo = nombre + " " + apellido;
escribir("Nombre completo:", nombre_completo);

var edad = 28;
var presentacion = "Hola, soy " + nombre + " y tengo " + edad + " años";
escribir(presentacion);
escribir("");

// --- SECCIÓN 11: Tabla de Multiplicar ---
escribir("--- 11. Tabla de Multiplicar (7) ---");
var tabla_numero = 7;
para (i = 1; i <= 10; i = i + 1) {
    var resultado_tabla = tabla_numero * i;
    escribir(tabla_numero, "x", i, "=", resultado_tabla);
}
escribir("");

// === FIN ===
escribir("=====================================");
escribir("¡Fin de la Demostración!");
escribir("=====================================");
