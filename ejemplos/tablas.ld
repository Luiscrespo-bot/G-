// Ejemplo 7: Programa más complejo - Tablas de multiplicar

funcion tabla_multiplicar(numero, limite) {
    escribir("--- Tabla del", numero, "---");
    para (i = 1; i <= limite; i = i + 1) {
        var resultado = numero * i;
        escribir(numero, "x", i, "=", resultado);
    }
    escribir("");
}

tabla_multiplicar(3, 10);
tabla_multiplicar(7, 10);
tabla_multiplicar(12, 10);
