#include <iostream>
#include "server_clase.h"
#define EXITO 0
#define PARAMETROS_INCORRECTOS 1
#define ERROR_EXTERNO 2


int main(int argc, char* argv[]) {
    bool cero_hilos = false;
    if (argv[2])
        cero_hilos = atoi(argv[2]); //Desactivo hilos si argv[2] existe y != 0
    try {
        Servidor servidor(argv[1]);
        servidor.ejecutar(cero_hilos);
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return ERROR_EXTERNO;
    } catch (...) {
        return ERROR_EXTERNO;
    }
    return EXITO;
}

