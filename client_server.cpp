#include "client_server.h"

#define MAX_PALABRA 50

Servidor::Servidor(){

}



void Servidor::notificarMensaje(Intermediario& intermediario) {
    char mensaje[MAX_PALABRA];
    this->protocolo.recibirMensaje(mensaje, intermediario);

}
