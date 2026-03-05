cmake_minimum_required(VERSION 3.10)
project(LenguajeLd)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Archivos fuente comunes
set(SOURCES_COMUN
    src/Lexer.cpp
    src/Parser.cpp
    src/Interprete.cpp
)

# Ejecutable del intérprete CLI
set(SOURCES_CLI
    ${SOURCES_COMUN}
    main.cpp
)

# Ejecutable de la IDE web
set(SOURCES_IDE
    ${SOURCES_COMUN}
    src/ServidorHTTP.cpp
    ide_main.cpp
)

# Crear ejecutable del intérprete
add_executable(lenguaje ${SOURCES_CLI})
target_include_directories(lenguaje PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Crear ejecutable de la IDE
add_executable(lenguaje_ide ${SOURCES_IDE})
target_include_directories(lenguaje_ide PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Vincular con WinSock en Windows
if(WIN32)
    target_link_libraries(lenguaje_ide ws2_32)
endif()
