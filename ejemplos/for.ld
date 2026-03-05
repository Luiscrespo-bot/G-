// Ejemplo 5: Bucles (para)

escribir("Bucle para del 1 al 5:");

para (i = 1; i <= 5; i = i + 1) {
    escribir("Número:", i);
}

escribir("---");

// Calcular factorial
var numero = 5;
var factorial = 1;

para (j = 1; j <= numero; j = j + 1) {
    factorial = factorial * j;
}

escribir("Factorial de", numero, "es:", factorial);
