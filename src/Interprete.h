#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "AST.h"
#include <map>
#include <string>
#include <functional>
#include <iostream>

class Escopo {
public:
    std::map<std::string, ValorTipo> variables;
    std::shared_ptr<Escopo> padre;
    
    Escopo(std::shared_ptr<Escopo> p = nullptr) : padre(p) {}
    
    bool existe_variable(const std::string& nombre) {
        auto it = variables.find(nombre);
        if (it != variables.end()) {
            return true;
        }
        if (padre) {
            return padre->existe_variable(nombre);
        }
        return false;
    }
    
    ValorTipo obtener_variable(const std::string& nombre) {
        auto it = variables.find(nombre);
        if (it != variables.end()) {
            return it->second;
        }
        if (padre) {
            return padre->obtener_variable(nombre);
        }
        throw std::runtime_error("Variable no definida: " + nombre);
    }
    
    void asignar_variable(const std::string& nombre, const ValorTipo& valor) {
        auto it = variables.find(nombre);
        if (it != variables.end()) {
            it->second = valor;
            return;
        }
        if (padre) {
            padre->asignar_variable(nombre, valor);
            return;
        }
        variables[nombre] = valor;
    }
    
    void definir_variable(const std::string& nombre, const ValorTipo& valor) {
        variables[nombre] = valor;
    }
};

struct Funcion {
    std::vector<std::string> parametros;
    std::shared_ptr<NodoBloque> cuerpo;
    std::shared_ptr<Escopo> escopo_cierre;
};

class Interprete {
private:
    std::shared_ptr<Escopo> escopo_global;
    std::shared_ptr<Escopo> escopo_actual;
    std::map<std::string, Funcion> funciones;
    
    // Para el control de flujo
    bool retornando = false;
    ValorTipo valor_retorno;
    
    // Evaluación de expresiones
    ValorTipo evaluar_expresion(const ExprPtr& expr);
    ValorTipo evaluar_numero(const std::shared_ptr<NodoNumero>& nodo);
    ValorTipo evaluar_texto(const std::shared_ptr<NodoTexto>& nodo);
    ValorTipo evaluar_bool(const std::shared_ptr<NodoBool>& nodo);
    ValorTipo evaluar_identificador(const std::shared_ptr<NodoIdentificador>& nodo);
    ValorTipo evaluar_operacion_binaria(const std::shared_ptr<NodoOperacionBinaria>& nodo);
    ValorTipo evaluar_operacion_unaria(const std::shared_ptr<NodoOperacionUnaria>& nodo);
    ValorTipo evaluar_asignacion(const std::shared_ptr<NodoAsignacion>& nodo);
    ValorTipo evaluar_llamada_funcion(const std::shared_ptr<NodoLlamadaFuncion>& nodo);
    
    // Ejecución de declaraciones
    void ejecutar_declaracion(const DeclPtr& decl);
    void ejecutar_variable_num(const std::shared_ptr<NodoVariableNum>& nodo);
    void ejecutar_declaracion_funcion(const std::shared_ptr<NodoDeclaracionFuncion>& nodo);
    void ejecutar_si(const std::shared_ptr<NodoSi>& nodo);
    void ejecutar_mientras(const std::shared_ptr<NodoMientras>& nodo);
    void ejecutar_para(const std::shared_ptr<NodoPara>& nodo);
    void ejecutar_escribir(const std::shared_ptr<NodoEscribir>& nodo);
    void ejecutar_leer(const std::shared_ptr<NodoLeer>& nodo);
    void ejecutar_retorna(const std::shared_ptr<NodoRetorna>& nodo);
    void ejecutar_bloque(const std::shared_ptr<NodoBloque>& nodo,
                        std::shared_ptr<Escopo> escopo = nullptr);
    
    // Utilidades
    bool es_verdadero(const ValorTipo& valor);
    std::string valor_a_texto(const ValorTipo& valor);
    double obtener_numero(const ValorTipo& valor);
    std::string obtener_texto(const ValorTipo& valor);
    bool obtener_bool(const ValorTipo& valor);
    
public:
    Interprete();
    void ejecutar(const std::shared_ptr<NodoBloque>& programa);
};

#endif // INTERPRETER_H
