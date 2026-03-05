#include "Interprete.h"
#include <iostream>
#include <cmath>
#include <sstream>
#include <iomanip>

Interprete::Interprete() {
    escopo_global = std::make_shared<Escopo>();
    escopo_actual = escopo_global;
}

ValorTipo Interprete::evaluar_numero(const std::shared_ptr<NodoNumero>& nodo) {
    return static_cast<double>(nodo->valor);
}

ValorTipo Interprete::evaluar_texto(const std::shared_ptr<NodoTexto>& nodo) {
    return nodo->valor;
}

ValorTipo Interprete::evaluar_bool(const std::shared_ptr<NodoBool>& nodo) {
    return nodo->valor;
}

ValorTipo Interprete::evaluar_identificador(const std::shared_ptr<NodoIdentificador>& nodo) {
    return escopo_actual->obtener_variable(nodo->nombre);
}

bool Interprete::es_verdadero(const ValorTipo& valor) {
    if (std::holds_alternative<bool>(valor)) {
        return std::get<bool>(valor);
    }
    if (std::holds_alternative<double>(valor)) {
        return std::get<double>(valor) != 0.0;
    }
    if (std::holds_alternative<std::string>(valor)) {
        return !std::get<std::string>(valor).empty();
    }
    return false;
}

std::string Interprete::valor_a_texto(const ValorTipo& valor) {
    if (std::holds_alternative<double>(valor)) {
        double d = std::get<double>(valor);
        // Si es un número entero, mostrar sin decimales
        if (d == std::floor(d)) {
            return std::to_string(static_cast<long long>(d));
        }
        std::ostringstream oss;
        oss << d;
        return oss.str();
    }
    if (std::holds_alternative<std::string>(valor)) {
        return std::get<std::string>(valor);
    }
    if (std::holds_alternative<bool>(valor)) {
        return std::get<bool>(valor) ? "verdadero" : "falso";
    }
    return "";
}

double Interprete::obtener_numero(const ValorTipo& valor) {
    if (std::holds_alternative<double>(valor)) {
        return std::get<double>(valor);
    }
    if (std::holds_alternative<bool>(valor)) {
        return std::get<bool>(valor) ? 1.0 : 0.0;
    }
    if (std::holds_alternative<std::string>(valor)) {
        try {
            return std::stod(std::get<std::string>(valor));
        } catch (...) {
            return 0.0;
        }
    }
    return 0.0;
}

std::string Interprete::obtener_texto(const ValorTipo& valor) {
    return valor_a_texto(valor);
}

bool Interprete::obtener_bool(const ValorTipo& valor) {
    return es_verdadero(valor);
}

ValorTipo Interprete::evaluar_operacion_binaria(const std::shared_ptr<NodoOperacionBinaria>& nodo) {
    // Operadores lógicos con cortocircuito
    if (nodo->operador == "||") {
        auto izq = evaluar_expresion(nodo->izquierda);
        if (es_verdadero(izq)) {
            return true;
        }
        auto der = evaluar_expresion(nodo->derecha);
        return es_verdadero(der);
    }
    
    if (nodo->operador == "&&") {
        auto izq = evaluar_expresion(nodo->izquierda);
        if (!es_verdadero(izq)) {
            return false;
        }
        auto der = evaluar_expresion(nodo->derecha);
        return es_verdadero(der);
    }
    
    auto izq = evaluar_expresion(nodo->izquierda);
    auto der = evaluar_expresion(nodo->derecha);
    
    // Operaciones aritméticas
    if (nodo->operador == "+") {
        // Concatenación de textos o suma numérica
        if (std::holds_alternative<std::string>(izq) || 
            std::holds_alternative<std::string>(der)) {
            return valor_a_texto(izq) + valor_a_texto(der);
        }
        return obtener_numero(izq) + obtener_numero(der);
    }
    
    if (nodo->operador == "-") {
        return obtener_numero(izq) - obtener_numero(der);
    }
    
    if (nodo->operador == "*") {
        return obtener_numero(izq) * obtener_numero(der);
    }
    
    if (nodo->operador == "/") {
        double divisor = obtener_numero(der);
        if (divisor == 0.0) {
            throw std::runtime_error("División por cero");
        }
        return obtener_numero(izq) / divisor;
    }
    
    if (nodo->operador == "%") {
        long long a = static_cast<long long>(obtener_numero(izq));
        long long b = static_cast<long long>(obtener_numero(der));
        if (b == 0) {
            throw std::runtime_error("Módulo por cero");
        }
        return static_cast<double>(a % b);
    }
    
    // Comparaciones
    if (nodo->operador == "==") {
        return valor_a_texto(izq) == valor_a_texto(der);
    }
    
    if (nodo->operador == "!=") {
        return valor_a_texto(izq) != valor_a_texto(der);
    }
    
    if (nodo->operador == "<") {
        return obtener_numero(izq) < obtener_numero(der);
    }
    
    if (nodo->operador == "<=") {
        return obtener_numero(izq) <= obtener_numero(der);
    }
    
    if (nodo->operador == ">") {
        return obtener_numero(izq) > obtener_numero(der);
    }
    
    if (nodo->operador == ">=") {
        return obtener_numero(izq) >= obtener_numero(der);
    }
    
    throw std::runtime_error("Operador binario no reconocido: " + nodo->operador);
}

ValorTipo Interprete::evaluar_operacion_unaria(const std::shared_ptr<NodoOperacionUnaria>& nodo) {
    auto operando = evaluar_expresion(nodo->operando);
    
    if (nodo->operador == "!") {
        return !es_verdadero(operando);
    }
    
    if (nodo->operador == "-") {
        return -obtener_numero(operando);
    }
    
    throw std::runtime_error("Operador unario no reconocido: " + nodo->operador);
}

ValorTipo Interprete::evaluar_asignacion(const std::shared_ptr<NodoAsignacion>& nodo) {
    auto valor = evaluar_expresion(nodo->valor);
    escopo_actual->asignar_variable(nodo->nombre, valor);
    return valor;
}

ValorTipo Interprete::evaluar_llamada_funcion(const std::shared_ptr<NodoLlamadaFuncion>& nodo) {
    auto it = funciones.find(nodo->nombre);
    if (it == funciones.end()) {
        throw std::runtime_error("Función no definida: " + nodo->nombre);
    }
    
    const Funcion& func = it->second;
    
    if (nodo->argumentos.size() != func.parametros.size()) {
        throw std::runtime_error("Número incorrecto de argumentos para " + nodo->nombre);
    }
    
    // Crear nuevo escopo para la función
    auto escopo_funcion = std::make_shared<Escopo>(func.escopo_cierre);
    
    // Asignar argumentos a parámetros
    for (size_t i = 0; i < nodo->argumentos.size(); ++i) {
        auto valor = evaluar_expresion(nodo->argumentos[i]);
        escopo_funcion->definir_variable(func.parametros[i], valor);
    }
    
    // Ejecutar cuerpo
    auto escopo_anterior = escopo_actual;
    escopo_actual = escopo_funcion;
    retornando = false;
    
    ejecutar_bloque(func.cuerpo, escopo_funcion);
    
    auto resultado = retornando ? valor_retorno : ValorTipo(0.0);
    retornando = false;
    
    escopo_actual = escopo_anterior;
    
    return resultado;
}

ValorTipo Interprete::evaluar_expresion(const ExprPtr& expr) {
    if (auto nodo = std::dynamic_pointer_cast<NodoNumero>(expr)) {
        return evaluar_numero(nodo);
    }
    if (auto nodo = std::dynamic_pointer_cast<NodoTexto>(expr)) {
        return evaluar_texto(nodo);
    }
    if (auto nodo = std::dynamic_pointer_cast<NodoBool>(expr)) {
        return evaluar_bool(nodo);
    }
    if (auto nodo = std::dynamic_pointer_cast<NodoIdentificador>(expr)) {
        return evaluar_identificador(nodo);
    }
    if (auto nodo = std::dynamic_pointer_cast<NodoOperacionBinaria>(expr)) {
        return evaluar_operacion_binaria(nodo);
    }
    if (auto nodo = std::dynamic_pointer_cast<NodoOperacionUnaria>(expr)) {
        return evaluar_operacion_unaria(nodo);
    }
    if (auto nodo = std::dynamic_pointer_cast<NodoAsignacion>(expr)) {
        return evaluar_asignacion(nodo);
    }
    if (auto nodo = std::dynamic_pointer_cast<NodoLlamadaFuncion>(expr)) {
        return evaluar_llamada_funcion(nodo);
    }
    
    throw std::runtime_error("Tipo de expresión no soportado");
}

void Interprete::ejecutar_variable_num(const std::shared_ptr<NodoVariableNum>& nodo) {
    auto valor = evaluar_expresion(nodo->valor);
    escopo_actual->definir_variable(nodo->nombre, valor);
}

void Interprete::ejecutar_declaracion_funcion(const std::shared_ptr<NodoDeclaracionFuncion>& nodo) {
    Funcion func;
    func.parametros = nodo->parametros;
    func.cuerpo = nodo->cuerpo;
    func.escopo_cierre = escopo_actual;
    
    funciones[nodo->nombre] = func;
}

void Interprete::ejecutar_si(const std::shared_ptr<NodoSi>& nodo) {
    auto condicion = evaluar_expresion(nodo->condicion);
    
    if (es_verdadero(condicion)) {
        ejecutar_bloque(nodo->rama_verdadera);
    } else if (nodo->rama_falsa) {
        ejecutar_bloque(nodo->rama_falsa);
    }
}

void Interprete::ejecutar_mientras(const std::shared_ptr<NodoMientras>& nodo) {
    while (es_verdadero(evaluar_expresion(nodo->condicion))) {
        ejecutar_bloque(nodo->cuerpo);
        if (retornando) break;
    }
}

void Interprete::ejecutar_para(const std::shared_ptr<NodoPara>& nodo) {
    auto valor_inicio = obtener_numero(evaluar_expresion(nodo->inicio));
    auto valor_fin = obtener_numero(evaluar_expresion(nodo->fin));
    auto valor_paso = obtener_numero(evaluar_expresion(nodo->paso));
    
    if (valor_paso == 0.0) {
        throw std::runtime_error("El paso del bucle 'para' no puede ser cero");
    }
    
    for (double i = valor_inicio; 
         (valor_paso > 0 ? i <= valor_fin : i >= valor_fin); 
         i += valor_paso) {
        escopo_actual->asignar_variable(nodo->variable, i);
        ejecutar_bloque(nodo->cuerpo);
        if (retornando) break;
    }
}

void Interprete::ejecutar_escribir(const std::shared_ptr<NodoEscribir>& nodo) {
    for (size_t i = 0; i < nodo->expresiones.size(); ++i) {
        auto valor = evaluar_expresion(nodo->expresiones[i]);
        std::cout << valor_a_texto(valor);
        if (i < nodo->expresiones.size() - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

void Interprete::ejecutar_leer(const std::shared_ptr<NodoLeer>& nodo) {
    std::string entrada;
    std::getline(std::cin, entrada);
    
    // Intentar convertir a número
    try {
        double numero = std::stod(entrada);
        escopo_actual->asignar_variable(nodo->variable, numero);
    } catch (...) {
        // Si no es un número, guardar como texto
        escopo_actual->asignar_variable(nodo->variable, entrada);
    }
}

void Interprete::ejecutar_retorna(const std::shared_ptr<NodoRetorna>& nodo) {
    valor_retorno = evaluar_expresion(nodo->valor);
    retornando = true;
}

void Interprete::ejecutar_bloque(const std::shared_ptr<NodoBloque>& nodo,
                                 std::shared_ptr<Escopo> escopo) {
    if (!escopo) {
        escopo = std::make_shared<Escopo>(escopo_actual);
    }
    
    auto escopo_anterior = escopo_actual;
    escopo_actual = escopo;
    
    for (const auto& decl : nodo->declaraciones) {
        ejecutar_declaracion(decl);
        if (retornando) break;
    }
    
    escopo_actual = escopo_anterior;
}

void Interprete::ejecutar_declaracion(const DeclPtr& decl) {
    if (auto nodo = std::dynamic_pointer_cast<NodoVariableNum>(decl)) {
        ejecutar_variable_num(nodo);
    } else if (auto nodo = std::dynamic_pointer_cast<NodoDeclaracionFuncion>(decl)) {
        ejecutar_declaracion_funcion(nodo);
    } else if (auto nodo = std::dynamic_pointer_cast<NodoSi>(decl)) {
        ejecutar_si(nodo);
    } else if (auto nodo = std::dynamic_pointer_cast<NodoMientras>(decl)) {
        ejecutar_mientras(nodo);
    } else if (auto nodo = std::dynamic_pointer_cast<NodoPara>(decl)) {
        ejecutar_para(nodo);
    } else if (auto nodo = std::dynamic_pointer_cast<NodoEscribir>(decl)) {
        ejecutar_escribir(nodo);
    } else if (auto nodo = std::dynamic_pointer_cast<NodoLeer>(decl)) {
        ejecutar_leer(nodo);
    } else if (auto nodo = std::dynamic_pointer_cast<NodoRetorna>(decl)) {
        ejecutar_retorna(nodo);
    }
}

void Interprete::ejecutar(const std::shared_ptr<NodoBloque>& programa) {
    ejecutar_bloque(programa, escopo_global);
}
