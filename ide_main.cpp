#include "src/Lexer.h"
#include "src/Parser.h"
#include "src/Interprete.h"
#include "src/ServidorHTTP.h"
#include <iostream>
#include <sstream>
#include <memory>

// Buffer para capturar salida
class CapturaConsola {
private:
    std::ostringstream buffer;
    std::streambuf* sb_original;
    
public:
    CapturaConsola() {
        sb_original = std::cout.rdbuf(buffer.rdbuf());
    }
    
    ~CapturaConsola() {
        std::cout.rdbuf(sb_original);
    }
    
    std::string obtener_salida() {
        return buffer.str();
    }
};

std::string ejecutar_codigo(const std::string& codigo) {
    try {
        // Capturar salida
        CapturaConsola captura;
        
        // Analizar y ejecutar
        Lexer lexer(codigo);
        auto tokens = lexer.tokenizar();
        
        Parser parser(tokens);
        auto ast = parser.parsear();
        
        Interprete interprete;
        interprete.ejecutar(ast);
        
        return captura.obtener_salida();
    } catch (const std::exception& e) {
        return std::string(e.what());
    }
}

int main(int argc, char* argv[]) {
    int puerto = 8080;
    
    if (argc > 1) {
        puerto = std::atoi(argv[1]);
    }
    
    ServidorHTTP servidor(puerto);
    
    // Establecer controlador para ejecutar código
    servidor.establecer_controlador_ejecutar(ejecutar_codigo);
    
    if (!servidor.iniciar()) {
        std::cerr << "Error al iniciar el servidor" << std::endl;
        return 1;
    }
    
    std::cout << "\n╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║     IDE - Lenguaje de Programación       ║" << std::endl;
    std::cout << "║            Escrito en Español            ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝\n" << std::endl;
    
    std::cout << "✅ Servidor iniciado en: http://127.0.0.1:" << puerto << std::endl;
    std::cout << "📝 Presiona Ctrl+C para detener\n" << std::endl;
    
    servidor.aceptar_conexiones();
    
    return 0;
}
