#include <iostream>
#include "server_clase.h"
#define EXITO 0
#define PARAMETROS_INCORRECTOS 1
#define ERROR_EXTERNO 2


int main(int argc, char* argv[]) {
    try {
        Servidor servidor(argv[1]);
        servidor.ejecutar();
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return ERROR_EXTERNO;
    } catch (...) {
        return ERROR_EXTERNO;
    }
    return EXITO;
}

