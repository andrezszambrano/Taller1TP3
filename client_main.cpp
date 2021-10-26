#include <iostream>
#include "client_clase.h"
#define EXITO 0
#define PARAMETROS_INCORRECTOS 1
#define ERROR_EXTERNO 2


int main(int argc, char* argv[]) {
    //int host = atoi(argv[1]);
    //int servidor = atoi(argv[2]);
    Cliente cliente(0, 0);
    cliente.ejecutar();
    return EXITO;
}