// Ejemplo 6: Funciones

funcion saludar(nombre) {
    escribir("¡Hola,", nombre, "!");
}

saludar("Juan");
saludar("María");
saludar("Carlos");

// Función que retorna un valor
funcion cuadrado(x) {
    retorna x * x;
}

var resultado = cuadrado(5);
escribir("El cuadrado de 5 es:", resultado);

var resultado2 = cuadrado(10);
escribir("El cuadrado de 10 es:", resultado2);
