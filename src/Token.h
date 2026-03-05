#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    // Literales
    NUMERO,
    TEXTO,
    VERDADERO,
    FALSO,
    
    // Identificadores y palabras clave
    IDENTIFICADOR,
    VAR,
    SI,
    SINO,
    MIENTRAS,
    PARA,
    FUNCION,
    RETORNA,
    ESCRIBIR,
    LEER,
    
    // Operadores
    MAS,
    MENOS,
    MULTIPLICAR,
    DIVIDIR,
    MODULO,
    IGUAL,
    MENOS_IGUAL,
    MAS_IGUAL,
    MULTIPLICAR_IGUAL,
    DIVIDIR_IGUAL,
    
    // Comparadores
    COMPARACION,        // ==
    NO_IGUAL,           // !=
    MENOR,              // <
    MAYOR,              // >
    MENOR_IGUAL,        // <=
    MAYOR_IGUAL,        // >=
    
    // Lógicos
    Y,                  // &&
    O,                  // ||
    NO,                 // !
    
    // Delimitadores
    PARENTESIS_IZQUIERDO,
    PARENTESIS_DERECHO,
    LLAVE_IZQUIERDA,
    LLAVE_DERECHA,
    CORCHETE_IZQUIERDO,
    CORCHETE_DERECHO,
    COMA,
    PUNTO_Y_COMA,
    DOS_PUNTOS,
    PUNTO,
    
    // Especiales
    SALTO_LINEA,
    FIN_ARCHIVO,
    ERROR
};

struct Token {
    TokenType tipo;
    std::string valor;
    int linea;
    int columna;
    
    Token(TokenType t, const std::string& v, int l, int c)
        : tipo(t), valor(v), linea(l), columna(c) {}
};

#endif // TOKEN_H
