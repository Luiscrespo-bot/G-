#include "Lexer.h"
#include <cctype>
#include <iostream>

Lexer::Lexer(const std::string& codigo)
    : codigo(codigo), posicion(0), linea(1), columna(1) {}

char Lexer::caracter_actual() {
    if (posicion >= codigo.length()) {
        return '\0';
    }
    return codigo[posicion];
}

char Lexer::siguiente_caracter() {
    if (posicion + 1 >= codigo.length()) {
        return '\0';
    }
    return codigo[posicion + 1];
}

void Lexer::avanzar() {
    if (posicion < codigo.length()) {
        if (codigo[posicion] == '\n') {
            linea++;
            columna = 1;
        } else {
            columna++;
        }
        posicion++;
    }
}

void Lexer::pasar_espacios_en_blanco() {
    while (caracter_actual() != '\0' && std::isspace(caracter_actual())) {
        if (caracter_actual() == '\n') {
            // Podemos usar saltos de línea como separadores importantes
        }
        avanzar();
    }
}

void Lexer::pasar_comentario() {
    if (caracter_actual() == '/' && siguiente_caracter() == '/') {
        while (caracter_actual() != '\0' && caracter_actual() != '\n') {
            avanzar();
        }
    } else if (caracter_actual() == '/' && siguiente_caracter() == '*') {
        avanzar(); // /
        avanzar(); // *
        while (caracter_actual() != '\0') {
            if (caracter_actual() == '*' && siguiente_caracter() == '/') {
                avanzar();
                avanzar();
                break;
            }
            avanzar();
        }
    }
}

bool Lexer::es_digito(char c) {
    return std::isdigit(c);
}

bool Lexer::es_letra(char c) {
    return std::isalpha(c) || c == '_';
}

bool Lexer::es_espacio_en_blanco(char c) {
    return std::isspace(c);
}

Token Lexer::leer_numero() {
    int linea_inicio = linea;
    int columna_inicio = columna;
    std::string numero;
    
    while (es_digito(caracter_actual()) || caracter_actual() == '.') {
        numero += caracter_actual();
        avanzar();
    }
    
    return Token(TokenType::NUMERO, numero, linea_inicio, columna_inicio);
}

Token Lexer::leer_texto() {
    int linea_inicio = linea;
    int columna_inicio = columna;
    char delimitador = caracter_actual();
    avanzar(); // pasar comilla inicial
    std::string texto;
    
    while (caracter_actual() != '\0' && caracter_actual() != delimitador) {
        if (caracter_actual() == '\\') {
            avanzar();
            switch (caracter_actual()) {
                case 'n': texto += '\n'; break;
                case 't': texto += '\t'; break;
                case 'r': texto += '\r'; break;
                case '\\': texto += '\\'; break;
                case '"': texto += '"'; break;
                case '\'': texto += '\''; break;
                default: texto += caracter_actual();
            }
            avanzar();
        } else {
            texto += caracter_actual();
            avanzar();
        }
    }
    
    if (caracter_actual() == delimitador) {
        avanzar(); // pasar comilla final
    }
    
    return Token(TokenType::TEXTO, texto, linea_inicio, columna_inicio);
}

TokenType Lexer::obtener_tipo_palabra_clave(const std::string& palabra) {
    if (palabra == "var") return TokenType::VAR;
    if (palabra == "si") return TokenType::SI;
    if (palabra == "sino") return TokenType::SINO;
    if (palabra == "mientras") return TokenType::MIENTRAS;
    if (palabra == "para") return TokenType::PARA;
    if (palabra == "funcion") return TokenType::FUNCION;
    if (palabra == "retorna") return TokenType::RETORNA;
    if (palabra == "escribir") return TokenType::ESCRIBIR;
    if (palabra == "leer") return TokenType::LEER;
    if (palabra == "verdadero") return TokenType::VERDADERO;
    if (palabra == "falso") return TokenType::FALSO;
    return TokenType::IDENTIFICADOR;
}

Token Lexer::leer_identificador_o_palabra_clave() {
    int linea_inicio = linea;
    int columna_inicio = columna;
    std::string palabra;
    
    while (es_letra(caracter_actual()) || es_digito(caracter_actual())) {
        palabra += caracter_actual();
        avanzar();
    }
    
    TokenType tipo = obtener_tipo_palabra_clave(palabra);
    return Token(tipo, palabra, linea_inicio, columna_inicio);
}

Token Lexer::leer_operador_o_delimitador() {
    int linea_inicio = linea;
    int columna_inicio = columna;
    char c = caracter_actual();
    avanzar();
    
    switch (c) {
        case '+':
            if (caracter_actual() == '=') {
                avanzar();
                return Token(TokenType::MAS_IGUAL, "+=", linea_inicio, columna_inicio);
            }
            return Token(TokenType::MAS, "+", linea_inicio, columna_inicio);
        case '-':
            if (caracter_actual() == '=') {
                avanzar();
                return Token(TokenType::MENOS_IGUAL, "-=", linea_inicio, columna_inicio);
            }
            return Token(TokenType::MENOS, "-", linea_inicio, columna_inicio);
        case '*':
            if (caracter_actual() == '=') {
                avanzar();
                return Token(TokenType::MULTIPLICAR_IGUAL, "*=", linea_inicio, columna_inicio);
            }
            return Token(TokenType::MULTIPLICAR, "*", linea_inicio, columna_inicio);
        case '/':
            if (caracter_actual() == '=') {
                avanzar();
                return Token(TokenType::DIVIDIR_IGUAL, "/=", linea_inicio, columna_inicio);
            }
            return Token(TokenType::DIVIDIR, "/", linea_inicio, columna_inicio);
        case '%':
            return Token(TokenType::MODULO, "%", linea_inicio, columna_inicio);
        case '=':
            if (caracter_actual() == '=') {
                avanzar();
                return Token(TokenType::COMPARACION, "==", linea_inicio, columna_inicio);
            }
            return Token(TokenType::IGUAL, "=", linea_inicio, columna_inicio);
        case '!':
            if (caracter_actual() == '=') {
                avanzar();
                return Token(TokenType::NO_IGUAL, "!=", linea_inicio, columna_inicio);
            }
            return Token(TokenType::NO, "!", linea_inicio, columna_inicio);
        case '<':
            if (caracter_actual() == '=') {
                avanzar();
                return Token(TokenType::MENOR_IGUAL, "<=", linea_inicio, columna_inicio);
            }
            return Token(TokenType::MENOR, "<", linea_inicio, columna_inicio);
        case '>':
            if (caracter_actual() == '=') {
                avanzar();
                return Token(TokenType::MAYOR_IGUAL, ">=", linea_inicio, columna_inicio);
            }
            return Token(TokenType::MAYOR, ">", linea_inicio, columna_inicio);
        case '&':
            if (caracter_actual() == '&') {
                avanzar();
                return Token(TokenType::Y, "&&", linea_inicio, columna_inicio);
            }
            break;
        case '|':
            if (caracter_actual() == '|') {
                avanzar();
                return Token(TokenType::O, "||", linea_inicio, columna_inicio);
            }
            break;
        case '(':
            return Token(TokenType::PARENTESIS_IZQUIERDO, "(", linea_inicio, columna_inicio);
        case ')':
            return Token(TokenType::PARENTESIS_DERECHO, ")", linea_inicio, columna_inicio);
        case '{':
            return Token(TokenType::LLAVE_IZQUIERDA, "{", linea_inicio, columna_inicio);
        case '}':
            return Token(TokenType::LLAVE_DERECHA, "}", linea_inicio, columna_inicio);
        case '[':
            return Token(TokenType::CORCHETE_IZQUIERDO, "[", linea_inicio, columna_inicio);
        case ']':
            return Token(TokenType::CORCHETE_DERECHO, "]", linea_inicio, columna_inicio);
        case ',':
            return Token(TokenType::COMA, ",", linea_inicio, columna_inicio);
        case ';':
            return Token(TokenType::PUNTO_Y_COMA, ";", linea_inicio, columna_inicio);
        case ':':
            return Token(TokenType::DOS_PUNTOS, ":", linea_inicio, columna_inicio);
        case '.':
            return Token(TokenType::PUNTO, ".", linea_inicio, columna_inicio);
    }
    
    return Token(TokenType::ERROR, std::string(1, c), linea_inicio, columna_inicio);
}

Token Lexer::siguiente_token() {
    pasar_espacios_en_blanco();
    
    // Verificar comentarios
    while ((caracter_actual() == '/' && 
            (siguiente_caracter() == '/' || siguiente_caracter() == '*'))) {
        pasar_comentario();
        pasar_espacios_en_blanco();
    }
    
    if (caracter_actual() == '\0') {
        return Token(TokenType::FIN_ARCHIVO, "", linea, columna);
    }
    
    // Números
    if (es_digito(caracter_actual())) {
        return leer_numero();
    }
    
    // Textos
    if (caracter_actual() == '"' || caracter_actual() == '\'') {
        return leer_texto();
    }
    
    // Identificadores y palabras clave
    if (es_letra(caracter_actual())) {
        return leer_identificador_o_palabra_clave();
    }
    
    // Operadores y delimitadores
    return leer_operador_o_delimitador();
}

std::vector<Token> Lexer::tokenizar() {
    std::vector<Token> tokens;
    Token token = siguiente_token();
    
    while (token.tipo != TokenType::FIN_ARCHIVO) {
        tokens.push_back(token);
        token = siguiente_token();
    }
    
    tokens.push_back(token); // Agregar FIN_ARCHIVO
    return tokens;
}
