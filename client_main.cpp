#include <iostream>
#include "client_clase.h"
#include "client_protocolo.h"

#define EXITO 0
#define PARAMETROS_INCORRECTOS 1
#define ERROR_EXTERNO 2


int main(int argc, char* argv[]) {
    try {
        Cliente cliente(argv[1], argv[2]);
        cliente.ejecutar();
    } catch (const MensajesNoSigueFormatoDeProtocoloError& error) {
        std::cerr << error.what() << std::endl;
        return ERROR_EXTERNO;
    } catch (...) {
        return ERROR_EXTERNO;
    }
    return EXITO;
}
