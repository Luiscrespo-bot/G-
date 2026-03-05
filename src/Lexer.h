#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <vector>
#include <string>
#include <memory>

class Lexer {
private:
    std::string codigo;
    size_t posicion;
    int linea;
    int columna;
    
    char caracter_actual();
    char siguiente_caracter();
    void avanzar();
    void pasar_espacios_en_blanco();
    void pasar_comentario();
    
    Token leer_numero();
    Token leer_texto();
    Token leer_identificador_o_palabra_clave();
    Token leer_operador_o_delimitador();
    
    bool es_digito(char c);
    bool es_letra(char c);
    bool es_espacio_en_blanco(char c);
    
    TokenType obtener_tipo_palabra_clave(const std::string& palabra);
    
public:
    Lexer(const std::string& codigo);
    std::vector<Token> tokenizar();
    Token siguiente_token();
};

#endif // LEXER_H
