#include "Parser.h"
#include <iostream>
#include <stdexcept>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens), posicion(0) {}

const Token& Parser::token_actual() {
    if (posicion >= tokens.size()) {
        return tokens.back();
    }
    return tokens[posicion];
}

const Token& Parser::siguiente_token() {
    if (posicion + 1 >= tokens.size()) {
        return tokens.back();
    }
    return tokens[posicion + 1];
}

void Parser::avanzar() {
    if (posicion < tokens.size()) {
        posicion++;
    }
}

bool Parser::coincidir(TokenType tipo) {
    if (token_actual().tipo == tipo) {
        avanzar();
        return true;
    }
    return false;
}

bool Parser::coincidir_multiple(const std::vector<TokenType>& tipos) {
    for (TokenType tipo : tipos) {
        if (token_actual().tipo == tipo) {
            avanzar();
            return true;
        }
    }
    return false;
}

Token Parser::consumir(TokenType tipo, const std::string& mensaje) {
    if (token_actual().tipo != tipo) {
        throw std::runtime_error(mensaje + " en línea " + 
                                 std::to_string(token_actual().linea));
    }
    Token token = token_actual();
    avanzar();
    return token;
}

// Análisis de expresiones con precedencia
ExprPtr Parser::expresion() {
    return expresion_logica_o();
}

ExprPtr Parser::expresion_logica_o() {
    auto izq = expresion_logica_y();
    
    while (coincidir(TokenType::O)) {
        izq = std::make_shared<NodoOperacionBinaria>(izq, "||", expresion_logica_y());
    }
    
    return izq;
}

ExprPtr Parser::expresion_logica_y() {
    auto izq = expresion_igualdad();
    
    while (coincidir(TokenType::Y)) {
        izq = std::make_shared<NodoOperacionBinaria>(izq, "&&", expresion_igualdad());
    }
    
    return izq;
}

ExprPtr Parser::expresion_igualdad() {
    auto izq = expresion_comparacion();
    
    while (true) {
        if (coincidir(TokenType::COMPARACION)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, "==", expresion_comparacion());
        } else if (coincidir(TokenType::NO_IGUAL)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, "!=", expresion_comparacion());
        } else {
            break;
        }
    }
    
    return izq;
}

ExprPtr Parser::expresion_comparacion() {
    auto izq = expresion_aditiva();
    
    while (true) {
        if (coincidir(TokenType::MENOR)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, "<", expresion_aditiva());
        } else if (coincidir(TokenType::MENOR_IGUAL)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, "<=", expresion_aditiva());
        } else if (coincidir(TokenType::MAYOR)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, ">", expresion_aditiva());
        } else if (coincidir(TokenType::MAYOR_IGUAL)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, ">=", expresion_aditiva());
        } else {
            break;
        }
    }
    
    return izq;
}

ExprPtr Parser::expresion_aditiva() {
    auto izq = expresion_multiplicativa();
    
    while (true) {
        if (coincidir(TokenType::MAS)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, "+", expresion_multiplicativa());
        } else if (coincidir(TokenType::MENOS)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, "-", expresion_multiplicativa());
        } else {
            break;
        }
    }
    
    return izq;
}

ExprPtr Parser::expresion_multiplicativa() {
    auto izq = expresion_unaria();
    
    while (true) {
        if (coincidir(TokenType::MULTIPLICAR)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, "*", expresion_unaria());
        } else if (coincidir(TokenType::DIVIDIR)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, "/", expresion_unaria());
        } else if (coincidir(TokenType::MODULO)) {
            izq = std::make_shared<NodoOperacionBinaria>(izq, "%", expresion_unaria());
        } else {
            break;
        }
    }
    
    return izq;
}

ExprPtr Parser::expresion_unaria() {
    if (coincidir(TokenType::NO)) {
        return std::make_shared<NodoOperacionUnaria>("!", expresion_unaria());
    }
    if (coincidir(TokenType::MENOS)) {
        return std::make_shared<NodoOperacionUnaria>("-", expresion_unaria());
    }
    
    return expresion_primaria();
}

ExprPtr Parser::expresion_primaria() {
    // Números
    if (token_actual().tipo == TokenType::NUMERO) {
        Token num = token_actual();
        avanzar();
        return std::make_shared<NodoNumero>(std::stod(num.valor));
    }
    
    // Textos
    if (token_actual().tipo == TokenType::TEXTO) {
        Token texto = token_actual();
        avanzar();
        return std::make_shared<NodoTexto>(texto.valor);
    }
    
    // Booleanos
    if (token_actual().tipo == TokenType::VERDADERO) {
        avanzar();
        return std::make_shared<NodoBool>(true);
    }
    if (token_actual().tipo == TokenType::FALSO) {
        avanzar();
        return std::make_shared<NodoBool>(false);
    }
    
    // Identificadores y asignaciones
    if (token_actual().tipo == TokenType::IDENTIFICADOR) {
        Token ident = token_actual();
        avanzar();
        
        // Asignaciones
        if (coincidir(TokenType::IGUAL)) {
            auto valor = expresion();
            return std::make_shared<NodoAsignacion>(ident.valor, valor);
        }
        
        // Asignaciones compuestas
        if (coincidir(TokenType::MAS_IGUAL)) {
            auto valor = expresion();
            auto operacion = std::make_shared<NodoOperacionBinaria>(
                std::make_shared<NodoIdentificador>(ident.valor), "+", valor);
            return std::make_shared<NodoAsignacion>(ident.valor, operacion);
        }
        if (coincidir(TokenType::MENOS_IGUAL)) {
            auto valor = expresion();
            auto operacion = std::make_shared<NodoOperacionBinaria>(
                std::make_shared<NodoIdentificador>(ident.valor), "-", valor);
            return std::make_shared<NodoAsignacion>(ident.valor, operacion);
        }
        if (coincidir(TokenType::MULTIPLICAR_IGUAL)) {
            auto valor = expresion();
            auto operacion = std::make_shared<NodoOperacionBinaria>(
                std::make_shared<NodoIdentificador>(ident.valor), "*", valor);
            return std::make_shared<NodoAsignacion>(ident.valor, operacion);
        }
        if (coincidir(TokenType::DIVIDIR_IGUAL)) {
            auto valor = expresion();
            auto operacion = std::make_shared<NodoOperacionBinaria>(
                std::make_shared<NodoIdentificador>(ident.valor), "/", valor);
            return std::make_shared<NodoAsignacion>(ident.valor, operacion);
        }
        
        // Llamada a función
        if (token_actual().tipo == TokenType::PARENTESIS_IZQUIERDO) {
            avanzar();
            std::vector<ExprPtr> argumentos;
            
            if (token_actual().tipo != TokenType::PARENTESIS_DERECHO) {
                do {
                    argumentos.push_back(expresion());
                } while (coincidir(TokenType::COMA));
            }
            
            consumir(TokenType::PARENTESIS_DERECHO, "Se esperaba ')'");
            return std::make_shared<NodoLlamadaFuncion>(ident.valor, argumentos);
        }
        
        // Solo identificador
        return std::make_shared<NodoIdentificador>(ident.valor);
    }
    
    // Expresión entre paréntesis
    if (coincidir(TokenType::PARENTESIS_IZQUIERDO)) {
        auto expr = expresion();
        consumir(TokenType::PARENTESIS_DERECHO, "Se esperaba ')'");
        return expr;
    }
    
    throw std::runtime_error("Se esperaba una expresión válida en línea " + 
                            std::to_string(token_actual().linea));
}

// Análisis de declaraciones
DeclPtr Parser::declaracion() {
    // Palabras clave de control
    if (token_actual().tipo == TokenType::SI) {
        return declaracion_si();
    }
    if (token_actual().tipo == TokenType::MIENTRAS) {
        return declaracion_mientras();
    }
    if (token_actual().tipo == TokenType::PARA) {
        return declaracion_para();
    }
    if (token_actual().tipo == TokenType::VAR) {
        return declaracion_variable();
    }
    if (token_actual().tipo == TokenType::FUNCION) {
        return declaracion_funcion();
    }
    if (token_actual().tipo == TokenType::ESCRIBIR) {
        return declaracion_escribir();
    }
    if (token_actual().tipo == TokenType::LEER) {
        return declaracion_leer();
    }
    if (token_actual().tipo == TokenType::RETORNA) {
        return declaracion_retorna();
    }
    
    // Expresión como declaración
    return expresion_como_declaracion();
}

DeclPtr Parser::declaracion_variable() {
    consumir(TokenType::VAR, "Se esperaba 'var'");
    Token nombre = consumir(TokenType::IDENTIFICADOR, "Se esperaba un nombre de variable");
    
    consumir(TokenType::IGUAL, "Se esperaba '=' después del nombre de variable");
    auto valor = expresion();
    
    if (coincidir(TokenType::PUNTO_Y_COMA)) {}
    
    return std::make_shared<NodoVariableNum>(nombre.valor, valor);
}

DeclPtr Parser::declaracion_funcion() {
    consumir(TokenType::FUNCION, "Se esperaba 'funcion'");
    Token nombre = consumir(TokenType::IDENTIFICADOR, "Se esperaba un nombre de función");
    
    consumir(TokenType::PARENTESIS_IZQUIERDO, "Se esperaba '('");
    
    std::vector<std::string> parametros;
    if (token_actual().tipo != TokenType::PARENTESIS_DERECHO) {
        do {
            Token param = consumir(TokenType::IDENTIFICADOR, "Se esperaba un nombre de parámetro");
            parametros.push_back(param.valor);
        } while (coincidir(TokenType::COMA));
    }
    
    consumir(TokenType::PARENTESIS_DERECHO, "Se esperaba ')'");
    consumir(TokenType::LLAVE_IZQUIERDA, "Se esperaba '{'");
    
    auto cuerpo = bloque();
    
    consumir(TokenType::LLAVE_DERECHA, "Se esperaba '}'");
    
    return std::make_shared<NodoDeclaracionFuncion>(nombre.valor, parametros, cuerpo);
}

DeclPtr Parser::declaracion_si() {
    consumir(TokenType::SI, "Se esperaba 'si'");
    consumir(TokenType::PARENTESIS_IZQUIERDO, "Se esperaba '('");
    auto condicion = expresion();
    consumir(TokenType::PARENTESIS_DERECHO, "Se esperaba ')'");
    
    consumir(TokenType::LLAVE_IZQUIERDA, "Se esperaba '{'");
    auto rama_verdadera = bloque();
    consumir(TokenType::LLAVE_DERECHA, "Se esperaba '}'");
    
    std::shared_ptr<NodoBloque> rama_falsa = nullptr;
    if (coincidir(TokenType::SINO)) {
        consumir(TokenType::LLAVE_IZQUIERDA, "Se esperaba '{'");
        rama_falsa = bloque();
        consumir(TokenType::LLAVE_DERECHA, "Se esperaba '}'");
    }
    
    return std::make_shared<NodoSi>(condicion, rama_verdadera, rama_falsa);
}

DeclPtr Parser::declaracion_mientras() {
    consumir(TokenType::MIENTRAS, "Se esperaba 'mientras'");
    consumir(TokenType::PARENTESIS_IZQUIERDO, "Se esperaba '('");
    auto condicion = expresion();
    consumir(TokenType::PARENTESIS_DERECHO, "Se esperaba ')'");
    
    consumir(TokenType::LLAVE_IZQUIERDA, "Se esperaba '{'");
    auto cuerpo = bloque();
    consumir(TokenType::LLAVE_DERECHA, "Se esperaba '}'");
    
    return std::make_shared<NodoMientras>(condicion, cuerpo);
}

DeclPtr Parser::declaracion_para() {
    consumir(TokenType::PARA, "Se esperaba 'para'");
    consumir(TokenType::PARENTESIS_IZQUIERDO, "Se esperaba '('");
    
    Token variable = consumir(TokenType::IDENTIFICADOR, "Se esperaba un nombre de variable");
    consumir(TokenType::IGUAL, "Se esperaba '='");
    auto inicio = expresion();
    
    consumir(TokenType::PUNTO_Y_COMA, "Se esperaba ';'");
    auto fin = expresion();
    
    consumir(TokenType::PUNTO_Y_COMA, "Se esperaba ';'");
    auto paso = expresion();
    
    consumir(TokenType::PARENTESIS_DERECHO, "Se esperaba ')'");
    
    consumir(TokenType::LLAVE_IZQUIERDA, "Se esperaba '{'");
    auto cuerpo = bloque();
    consumir(TokenType::LLAVE_DERECHA, "Se esperaba '}'");
    
    return std::make_shared<NodoPara>(variable.valor, inicio, fin, paso, cuerpo);
}

DeclPtr Parser::declaracion_escribir() {
    consumir(TokenType::ESCRIBIR, "Se esperaba 'escribir'");
    
    std::vector<ExprPtr> expresiones;
    
    if (coincidir(TokenType::PARENTESIS_IZQUIERDO)) {
        if (token_actual().tipo != TokenType::PARENTESIS_DERECHO) {
            do {
                expresiones.push_back(expresion());
            } while (coincidir(TokenType::COMA));
        }
        consumir(TokenType::PARENTESIS_DERECHO, "Se esperaba ')'");
    }
    
    if (coincidir(TokenType::PUNTO_Y_COMA)) {}
    
    return std::make_shared<NodoEscribir>(expresiones);
}

DeclPtr Parser::declaracion_leer() {
    consumir(TokenType::LEER, "Se esperaba 'leer'");
    
    consumir(TokenType::PARENTESIS_IZQUIERDO, "Se esperaba '('");
    Token variable = consumir(TokenType::IDENTIFICADOR, "Se esperaba un nombre de variable");
    consumir(TokenType::PARENTESIS_DERECHO, "Se esperaba ')'");
    
    if (coincidir(TokenType::PUNTO_Y_COMA)) {}
    
    return std::make_shared<NodoLeer>(variable.valor);
}

DeclPtr Parser::declaracion_retorna() {
    consumir(TokenType::RETORNA, "Se esperaba 'retorna'");
    auto valor = expresion();
    
    if (coincidir(TokenType::PUNTO_Y_COMA)) {}
    
    return std::make_shared<NodoRetorna>(valor);
}

DeclPtr Parser::expresion_como_declaracion() {
    auto expr = expresion();
    
    if (coincidir(TokenType::PUNTO_Y_COMA)) {}
    
    // Convertir expresión a una "declaración" envuelta
    // Por ahora solo retornamos expresiones válidas
    auto decl = std::make_shared<NodoDeclaracion>();
    return decl;
}

std::shared_ptr<NodoBloque> Parser::bloque() {
    auto bloque = std::make_shared<NodoBloque>();
    
    while (token_actual().tipo != TokenType::LLAVE_DERECHA &&
           token_actual().tipo != TokenType::FIN_ARCHIVO) {
        bloque->agregar_declaracion(declaracion());
    }
    
    return bloque;
}

std::shared_ptr<NodoBloque> Parser::parsear() {
    auto bloque = std::make_shared<NodoBloque>();
    
    while (token_actual().tipo != TokenType::FIN_ARCHIVO) {
        bloque->agregar_declaracion(declaracion());
    }
    
    return bloque;
}
