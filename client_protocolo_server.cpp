#include "client_protocolo_server.h"
#include <cstring>

#define MAX_MENSAJE 50


void ProtocoloServidor::recibirMensaje(char* buf, Intermediario& intermediario) {
    intermediario.recibirMensaje(buf);
}


