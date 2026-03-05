#include "src/Lexer.h"
#include "src/Parser.h"
#include "src/Interprete.h"
#include <iostream>
#include <fstream>
#include <sstream>

std::string leer_archivo(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + ruta);
    }
    
    std::stringstream buffer;
    buffer << archivo.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    try {
        std::string codigo;
        
        if (argc > 1) {
            // Ejecutar archivo
            codigo = leer_archivo(argv[1]);
        } else {
            // Modo interactivo
            std::cout << "===========================================\n";
            std::cout << "  Intérprete del Lenguaje de Programación\n";
            std::cout << "  Escrito en Español\n";
            std::cout << "===========================================\n\n";
            std::cout << "Escribe 'salir' para terminar.\n\n";
            
            std::string linea;
            std::string programa;
            
            while (true) {
                std::cout << "> ";
                if (!std::getline(std::cin, linea)) {
                    break;
                }
                
                if (linea == "salir") {
                    break;
                }
                
                programa += linea + "\n";
                
                // Intentar ejecutar si parece completo
                if (linea.find("}") != std::string::npos) {
                    try {
                        Lexer lexer(programa);
                        auto tokens = lexer.tokenizar();
                        
                        Parser parser(tokens);
                        auto ast = parser.parsear();
                        
                        Interprete interprete;
                        interprete.ejecutar(ast);
                        
                        programa.clear();
                    } catch (const std::exception& e) {
                        std::cerr << "Error: " << e.what() << std::endl;
                    }
                }
            }
            
            return 0;
        }
        
        // Procesar archivo
        Lexer lexer(codigo);
        auto tokens = lexer.tokenizar();
        
        Parser parser(tokens);
        auto ast = parser.parsear();
        
        Interprete interprete;
        interprete.ejecutar(ast);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
