#include "ServidorHTTP.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cstring>

#ifdef _WIN32
#else
    #include <signal.h>
#endif

ServidorHTTP::ServidorHTTP(int p)
    : socket_escucha(INVALID_SOCKET), puerto(p), ejecutando(false) {
    #ifdef _WIN32
    WSADATA wsa_data;
    WSAStartup(MAKEWORD(2, 2), &wsa_data);
    #endif
}

ServidorHTTP::~ServidorHTTP() {
    detener();
}

bool ServidorHTTP::iniciar() {
    socket_escucha = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_escucha == INVALID_SOCKET) {
        return false;
    }
    
    sockaddr_in direccion;
    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(puerto);
    direccion.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if (bind(socket_escucha, (sockaddr*)&direccion, sizeof(direccion)) == SOCKET_ERROR_VAL) {
        closesocket(socket_escucha);
        return false;
    }
    
    if (listen(socket_escucha, SOMAXCONN) == SOCKET_ERROR_VAL) {
        closesocket(socket_escucha);
        return false;
    }
    
    ejecutando = true;
    std::cout << "Servidor HTTP iniciado en http://127.0.0.1:" << puerto << std::endl;
    return true;
}

void ServidorHTTP::detener() {
    ejecutando = false;
    if (socket_escucha != INVALID_SOCKET) {
        closesocket(socket_escucha);
        socket_escucha = INVALID_SOCKET;
    }
}

void ServidorHTTP::establecer_controlador_ejecutar(std::function<std::string(const std::string&)> handler) {
    controlador_ejecutar = handler;
}

std::string ServidorHTTP::generar_respuesta_html() {
    const char* html = R"(<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>IDE - Lenguaje en Español</title>
    <style>
        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
        }
        
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            min-height: 100vh;
            display: flex;
            flex-direction: column;
        }
        
        header {
            background-color: rgba(0, 0, 0, 0.3);
            color: white;
            padding: 20px;
            text-align: center;
            box-shadow: 0 2px 10px rgba(0, 0, 0, 0.2);
        }
        
        header h1 {
            font-size: 28px;
            margin-bottom: 5px;
        }
        
        header p {
            font-size: 14px;
            opacity: 0.9;
        }
        
        .container {
            display: flex;
            flex: 1;
            max-width: 1400px;
            width: 100%;
            margin: 20px auto;
            gap: 20px;
            padding: 0 20px;
        }
        
        .editor-section {
            flex: 1;
            display: flex;
            flex-direction: column;
            background: white;
            border-radius: 8px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.2);
            overflow: hidden;
        }
        
        .editor-header {
            background-color: #2c3e50;
            color: white;
            padding: 15px 20px;
            font-weight: bold;
            font-size: 16px;
        }
        
        textarea {
            flex: 1;
            border: none;
            padding: 20px;
            font-family: 'Courier New', monospace;
            font-size: 14px;
            resize: none;
            outline: none;
            background-color: #f8f9fa;
        }
        
        .editor-footer {
            display: flex;
            gap: 10px;
            padding: 15px 20px;
            background-color: #ecf0f1;
            border-top: 1px solid #bdc3c7;
        }
        
        button {
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            font-size: 14px;
            font-weight: bold;
            cursor: pointer;
            transition: all 0.3s ease;
        }
        
        .btn-ejecutar {
            background-color: #27ae60;
            color: white;
            flex: 1;
            font-size: 16px;
        }
        
        .btn-ejecutar:hover {
            background-color: #229954;
            transform: translateY(-2px);
            box-shadow: 0 4px 12px rgba(39, 174, 96, 0.4);
        }
        
        .btn-ejecutar:active {
            transform: translateY(0);
        }
        
        .btn-limpiar {
            background-color: #e74c3c;
            color: white;
        }
        
        .btn-limpiar:hover {
            background-color: #c0392b;
        }
        
        .btn-ejemplo {
            background-color: #3498db;
            color: white;
        }
        
        .btn-ejemplo:hover {
            background-color: #2980b9;
        }
        
        .output-section {
            flex: 1;
            display: flex;
            flex-direction: column;
            background: white;
            border-radius: 8px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.2);
            overflow: hidden;
        }
        
        .output-header {
            background-color: #2c3e50;
            color: white;
            padding: 15px 20px;
            font-weight: bold;
            font-size: 16px;
        }
        
        #salida {
            flex: 1;
            padding: 20px;
            font-family: 'Courier New', monospace;
            font-size: 14px;
            overflow-y: auto;
            background-color: #1e1e1e;
            color: #00ff00;
            white-space: pre-wrap;
            word-wrap: break-word;
        }
        
        .error {
            color: #ff6b6b;
        }
        
        .exito {
            color: #51cf66;
        }
        
        .cargando {
            text-align: center;
            padding: 20px;
            color: #3498db;
        }
        
        .spinner {
            display: inline-block;
            width: 20px;
            height: 20px;
            border: 3px solid rgba(52, 152, 219, 0.3);
            border-radius: 50%;
            border-top-color: #3498db;
            animation: spin 1s ease-in-out infinite;
        }
        
        @keyframes spin {
            to { transform: rotate(360deg); }
        }
        
        .ejemplos {
            display: flex;
            gap: 10px;
            flex-wrap: wrap;
        }
        
        select {
            padding: 8px 15px;
            border: 1px solid #bdc3c7;
            border-radius: 4px;
            font-size: 14px;
            background-color: white;
            cursor: pointer;
        }
        
        @media (max-width: 1024px) {
            .container {
                flex-direction: column;
            }
            
            .editor-section, .output-section {
                min-height: 400px;
            }
        }
        
        footer {
            text-align: center;
            color: white;
            padding: 15px;
            font-size: 12px;
            background-color: rgba(0, 0, 0, 0.2);
        }
    </style>
</head>
<body>
    <header>
        <h1>🚀 IDE - Lenguaje en Español</h1>
        <p>Escribe código en español y ejecútalo directamente</p>
    </header>
    
    <div class="container">
        <div class="editor-section">
            <div class="editor-header">📝 Editor de Código</div>
            <textarea id="codigo" placeholder="Escribe tu código aquí...

var x = 10;
escribir(&quot;Hola&quot;, x);"></textarea>
            <div class="editor-footer">
                <button class="btn-ejecutar" onclick="ejecutar()">▶ Ejecutar (Ctrl+Enter)</button>
                <button class="btn-limpiar" onclick="limpiar()">🗑 Limpiar</button>
                <select onchange="cargarEjemplo(this.value)">
                    <option value="">📚 Cargar Ejemplo...</option>
                    <option value="hola">Hola Mundo</option>
                    <option value="operaciones">Operaciones</option>
                    <option value="condicionales">Condicionales</option>
                    <option value="bucle">Bucle FOR</option>
                    <option value="funciones">Funciones</option>
                </select>
            </div>
        </div>
        
        <div class="output-section">
            <div class="output-header">📊 Salida</div>
            <div id="salida">Escribe código y presiona 'Ejecutar'...</div>
        </div>
    </div>
    
    <footer>
        <p>Lenguaje de Programación en Español © 2026 | IDE Web</p>
    </footer>
    
    <script>
        const ejemplos = {
            hola: `escribir("¡Hola, Mundo!");`,
            
            operaciones: `var x = 15;
var y = 8;
escribir("x + y =", x + y);
escribir("x - y =", x - y);
escribir("x * y =", x * y);
escribir("x / y =", x / y);`,
            
            condicionales: `var edad = 18;
si (edad >= 18) {
    escribir("Eres mayor de edad");
} sino {
    escribir("Eres menor de edad");
}`,
            
            bucle: `escribir("Números del 1 al 5:");
para (i = 1; i <= 5; i = i + 1) {
    escribir("Número:", i);
}`,
            
            funciones: `funcion doble(x) {
    retorna x * 2;
}

escribir("Doble de 5:", doble(5));
escribir("Doble de 10:", doble(10));`
        };
        
        function obtenerCodigo() {
            return document.getElementById('codigo').value;
        }
        
        function mostrarSalida(texto, esError = false) {
            const salida = document.getElementById('salida');
            salida.innerHTML = '';
            const clase = esError ? 'error' : 'exito';
            salida.innerHTML = `<span class="${clase}">${escapeHtml(texto)}</span>`;
        }
        
        function mostrarCargando() {
            const salida = document.getElementById('salida');
            salida.innerHTML = '<div class="cargando"><div class="spinner"></div> Ejecutando...</div>';
        }
        
        function escapeHtml(texto) {
            const div = document.createElement('div');
            div.textContent = texto;
            return div.innerHTML;
        }
        
        async function ejecutar() {
            const codigo = obtenerCodigo();
            if (!codigo.trim()) {
                mostrarSalida('Por favor, escribe algo de código', true);
                return;
            }
            
            mostrarCargando();
            
            try {
                const respuesta = await fetch('/ejecutar', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json',
                    },
                    body: JSON.stringify({ codigo: codigo })
                });
                
                const datos = await respuesta.json();
                
                if (datos.exito) {
                    mostrarSalida(datos.resultado || '(sin salida)');
                } else {
                    mostrarSalida('Error: ' + (datos.resultado || 'Error desconocido'), true);
                }
            } catch (error) {
                mostrarSalida('Error de conexión: ' + error.message, true);
            }
        }
        
        function limpiar() {
            document.getElementById('codigo').value = '';
            document.getElementById('salida').innerHTML = 'Escribe código y presiona "Ejecutar"...';
        }
        
        function cargarEjemplo(tipo) {
            if (tipo && ejemplos[tipo]) {
                document.getElementById('codigo').value = ejemplos[tipo];
            }
        }
        
        // Atajo de teclado: Ctrl+Enter para ejecutar
        document.getElementById('codigo').addEventListener('keydown', function(e) {
            if (e.ctrlKey && e.key === 'Enter') {
                ejecutar();
            }
        });
    </script>
</body>
</html>)";
    
    return std::string(html);
}

std::string ServidorHTTP::generar_json_respuesta(const std::string& resultado, bool exito) {
    std::string json = "{\"exito\":" + std::string(exito ? "true" : "false") + ",\"resultado\":\"";
    
    // Escapar caracteres especiales JSON
    for (char c : resultado) {
        switch (c) {
            case '"': json += "\\\""; break;
            case '\\': json += "\\\\"; break;
            case '\n': json += "\\n"; break;
            case '\r': json += "\\r"; break;
            case '\t': json += "\\t"; break;
            default: json += c;
        }
    }
    
    json += "\"}";
    return json;
}

std::string ServidorHTTP::procesar_solicitud(const std::string& solicitud) {
    // Parsear solicitud HTTP
    std::string respuesta_html = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404</h1>";
    
    if (solicitud.find("GET / ") == 0) {
        std::string contenido = generar_respuesta_html();
        std::ostringstream oss;
        oss << "HTTP/1.1 200 OK\r\n"
            << "Content-Type: text/html; charset=utf-8\r\n"
            << "Content-Length: " << contenido.length() << "\r\n"
            << "Connection: close\r\n"
            << "\r\n"
            << contenido;
        return oss.str();
    }
    
    if (solicitud.find("POST /ejecutar") == 0) {
        // Extraer el cuerpo JSON
        size_t pos_headers_fin = solicitud.find("\r\n\r\n");
        if (pos_headers_fin != std::string::npos) {
            std::string cuerpo = solicitud.substr(pos_headers_fin + 4);
            
            // Extraer código del JSON simple
            size_t inicio = cuerpo.find("\"codigo\":\"") + 10;
            size_t fin = cuerpo.rfind("\"");
            
            if (inicio < cuerpo.length() && fin > inicio) {
                std::string codigo = cuerpo.substr(inicio, fin - inicio);
                
                // Desescapar caracteres
                std::string codigo_desescapado;
                for (size_t i = 0; i < codigo.length(); ++i) {
                    if (codigo[i] == '\\' && i + 1 < codigo.length()) {
                        char siguiente = codigo[++i];
                        switch (siguiente) {
                            case 'n': codigo_desescapado += '\n'; break;
                            case 't': codigo_desescapado += '\t'; break;
                            case 'r': codigo_desescapado += '\r'; break;
                            case '"': codigo_desescapado += '"'; break;
                            case '\\': codigo_desescapado += '\\'; break;
                            default: codigo_desescapado += siguiente;
                        }
                    } else {
                        codigo_desescapado += codigo[i];
                    }
                }
                
                // Ejecutar código
                std::string resultado;
                bool exito = false;
                
                try {
                    if (controlador_ejecutar) {
                        resultado = controlador_ejecutar(codigo_desescapado);
                        exito = true;
                    } else {
                        resultado = "Controlador no configurado";
                    }
                } catch (const std::exception& e) {
                    resultado = e.what();
                    exito = false;
                }
                
                std::string respuesta_json = generar_json_respuesta(resultado, exito);
                
                std::ostringstream oss;
                oss << "HTTP/1.1 200 OK\r\n"
                    << "Content-Type: application/json; charset=utf-8\r\n"
                    << "Content-Length: " << respuesta_json.length() << "\r\n"
                    << "Connection: close\r\n"
                    << "\r\n"
                    << respuesta_json;
                return oss.str();
            }
        }
    }
    
    return respuesta_html;
}

void ServidorHTTP::aceptar_conexiones() {
    while (ejecutando) {
        sockaddr_in cliente_addr;
        socklen_t cliente_addr_len = sizeof(cliente_addr);
        
        SOCKET cliente_socket = accept(socket_escucha, (sockaddr*)&cliente_addr, &cliente_addr_len);
        
        if (cliente_socket == INVALID_SOCKET) {
            continue;
        }
        
        // Procesar en un hilo separado
        std::thread([this, cliente_socket]() {
            char buffer[8192] = {0};
            int bytes_recibidos = recv(cliente_socket, buffer, sizeof(buffer) - 1, 0);
            
            if (bytes_recibidos > 0) {
                buffer[bytes_recibidos] = '\0';
                std::string solicitud(buffer);
                std::string respuesta = procesar_solicitud(solicitud);
                send(cliente_socket, respuesta.c_str(), respuesta.length(), 0);
            }
            
            closesocket(cliente_socket);
        }).detach();
    }
}
