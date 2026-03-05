#ifndef AST_H
#define AST_H

#include <string>
#include <vector>
#include <memory>
#include <variant>

// Forward declarations
class Nodo;
class NodoExpresion;
class NodoDeclaracion;
class NodoVariableNum;
class NodoVariableTexto;
class NodoNumero;
class NodoTexto;
class NodoBool;
class NodoIdentificador;
class NodoOperacionBinaria;
class NodoOperacionUnaria;
class NodoAsignacion;
class NodoSi;
class NodoMientras;
class NodoPara;
class NodoBloque;
class NodoLlamadaFuncion;
class NodoDeclaracionFuncion;
class NodoRetorna;
class NodoEscribir;
class NodoLeer;

using NodoPtr = std::shared_ptr<Nodo>;
using ExprPtr = std::shared_ptr<NodoExpresion>;
using DeclPtr = std::shared_ptr<NodoDeclaracion>;

// Tipo de valor durante la ejecución
using ValorTipo = std::variant<double, std::string, bool>;

// Clase base
class Nodo {
public:
    virtual ~Nodo() = default;
};

// Expresiones
class NodoExpresion : public Nodo {
public:
    virtual ~NodoExpresion() = default;
};

class NodoNumero : public NodoExpresion {
public:
    double valor;
    NodoNumero(double v) : valor(v) {}
};

class NodoTexto : public NodoExpresion {
public:
    std::string valor;
    NodoTexto(const std::string& v) : valor(v) {}
};

class NodoBool : public NodoExpresion {
public:
    bool valor;
    NodoBool(bool v) : valor(v) {}
};

class NodoIdentificador : public NodoExpresion {
public:
    std::string nombre;
    NodoIdentificador(const std::string& n) : nombre(n) {}
};

class NodoOperacionBinaria : public NodoExpresion {
public:
    ExprPtr izquierda;
    std::string operador;
    ExprPtr derecha;
    
    NodoOperacionBinaria(ExprPtr izq, const std::string& op, ExprPtr der)
        : izquierda(izq), operador(op), derecha(der) {}
};

class NodoOperacionUnaria : public NodoExpresion {
public:
    std::string operador;
    ExprPtr operando;
    
    NodoOperacionUnaria(const std::string& op, ExprPtr operando)
        : operador(op), operando(operando) {}
};

class NodoAsignacion : public NodoExpresion {
public:
    std::string nombre;
    ExprPtr valor;
    
    NodoAsignacion(const std::string& n, ExprPtr v)
        : nombre(n), valor(v) {}
};

class NodoLlamadaFuncion : public NodoExpresion {
public:
    std::string nombre;
    std::vector<ExprPtr> argumentos;
    
    NodoLlamadaFuncion(const std::string& n, const std::vector<ExprPtr>& args)
        : nombre(n), argumentos(args) {}
};

// Declaraciones
class NodoDeclaracion : public Nodo {
public:
    virtual ~NodoDeclaracion() = default;
};

class NodoVariableNum : public NodoDeclaracion {
public:
    std::string nombre;
    ExprPtr valor;
    
    NodoVariableNum(const std::string& n, ExprPtr v)
        : nombre(n), valor(v) {}
};

class NodoVariableTexto : public NodoDeclaracion {
public:
    std::string nombre;
    ExprPtr valor;
    
    NodoVariableTexto(const std::string& n, ExprPtr v)
        : nombre(n), valor(v) {}
};

class NodoDeclaracionFuncion : public NodoDeclaracion {
public:
    std::string nombre;
    std::vector<std::string> parametros;
    std::shared_ptr<NodoBloque> cuerpo;
    
    NodoDeclaracionFuncion(const std::string& n, const std::vector<std::string>& params,
                          std::shared_ptr<NodoBloque> c)
        : nombre(n), parametros(params), cuerpo(c) {}
};

class NodoSi : public NodoDeclaracion {
public:
    ExprPtr condicion;
    std::shared_ptr<NodoBloque> rama_verdadera;
    std::shared_ptr<NodoBloque> rama_falsa;
    
    NodoSi(ExprPtr cond, std::shared_ptr<NodoBloque> rama_v, 
           std::shared_ptr<NodoBloque> rama_f = nullptr)
        : condicion(cond), rama_verdadera(rama_v), rama_falsa(rama_f) {}
};

class NodoMientras : public NodoDeclaracion {
public:
    ExprPtr condicion;
    std::shared_ptr<NodoBloque> cuerpo;
    
    NodoMientras(ExprPtr cond, std::shared_ptr<NodoBloque> c)
        : condicion(cond), cuerpo(c) {}
};

class NodoPara : public NodoDeclaracion {
public:
    std::string variable;
    ExprPtr inicio;
    ExprPtr fin;
    ExprPtr paso;
    std::shared_ptr<NodoBloque> cuerpo;
    
    NodoPara(const std::string& var, ExprPtr ini, ExprPtr f, ExprPtr p,
             std::shared_ptr<NodoBloque> c)
        : variable(var), inicio(ini), fin(f), paso(p), cuerpo(c) {}
};

class NodoBloque : public Nodo {
public:
    std::vector<DeclPtr> declaraciones;
    
    void agregar_declaracion(DeclPtr decl) {
        declaraciones.push_back(decl);
    }
};

class NodoEscribir : public NodoDeclaracion {
public:
    std::vector<ExprPtr> expresiones;
    
    NodoEscribir(const std::vector<ExprPtr>& exprs)
        : expresiones(exprs) {}
};

class NodoLeer : public NodoDeclaracion {
public:
    std::string variable;
    
    NodoLeer(const std::string& var) : variable(var) {}
};

class NodoRetorna : public NodoDeclaracion {
public:
    ExprPtr valor;
    
    NodoRetorna(ExprPtr v) : valor(v) {}
};

#endif // AST_H
