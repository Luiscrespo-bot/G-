#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "AST.h"
#include <vector>
#include <memory>

class Parser {
private:
    std::vector<Token> tokens;
    size_t posicion;
    
    const Token& token_actual();
    const Token& siguiente_token();
    void avanzar();
    bool coincidir(TokenType tipo);
    bool coincidir_multiple(const std::vector<TokenType>& tipos);
    Token consumir(TokenType tipo, const std::string& mensaje);
    
    // Análisis de expresiones
    ExprPtr expresion();
    ExprPtr expresion_logica_o();
    ExprPtr expresion_logica_y();
    ExprPtr expresion_igualdad();
    ExprPtr expresion_comparacion();
    ExprPtr expresion_aditiva();
    ExprPtr expresion_multiplicativa();
    ExprPtr expresion_unaria();
    ExprPtr expresion_primaria();
    
    // Análisis de declaraciones
    DeclPtr declaracion();
    DeclPtr declaracion_variable();
    DeclPtr declaracion_funcion();
    DeclPtr declaracion_si();
    DeclPtr declaracion_mientras();
    DeclPtr declaracion_para();
    DeclPtr declaracion_escribir();
    DeclPtr declaracion_leer();
    DeclPtr declaracion_retorna();
    DeclPtr expresion_como_declaracion();
    
    // Análisis de bloques
    std::shared_ptr<NodoBloque> bloque();
    
public:
    Parser(const std::vector<Token>& tokens);
    std::shared_ptr<NodoBloque> parsear();
};

#endif // PARSER_H
