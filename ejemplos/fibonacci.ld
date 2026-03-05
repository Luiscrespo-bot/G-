// Ejemplo 10: Números de Fibonacci

funcion fibonacci(n) {
    si (n <= 1) {
        retorna n;
    }
    retorna fibonacci(n - 1) + fibonacci(n - 2);
}

escribir("Series de Fibonacci (primeros 10 números):");
para (i = 0; i < 10; i = i + 1) {
    var fib = fibonacci(i);
    escribir(fib);
}
