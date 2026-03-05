#ifndef SERVIDOR_HTTP_H
#define SERVIDOR_HTTP_H

#include <string>
#include <memory>
#include <functional>
#include <thread>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    #define SOCKET_ERROR_VAL SOCKET_ERROR
    typedef int socklen_t;
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define SOCKET_ERROR_VAL -1
    #define closesocket close
    typedef int SOCKET;
    #define INVALID_SOCKET -1
#endif

class ServidorHTTP {
private:
    SOCKET socket_escucha;
    int puerto;
    bool ejecutando;
    
    std::function<std::string(const std::string&)> controlador_ejecutar;
    
public:
    ServidorHTTP(int p);
    ~ServidorHTTP();
    
    bool iniciar();
    void detener();
    void establecer_controlador_ejecutar(std::function<std::string(const std::string&)> handler);
    void aceptar_conexiones();
    
private:
    std::string procesar_solicitud(const std::string& solicitud);
    std::string generar_respuesta_html();
    std::string generar_json_respuesta(const std::string& resultado, bool exito);
};

#endif // SERVIDOR_HTTP_H
