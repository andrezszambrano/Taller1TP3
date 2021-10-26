#include "client_intermediario.h"
#include <cstring>

void Intermediario::aniadirMensaje(const char* mensaje, int largo_mensaje) {
    memcpy(this->mensajee, mensaje, largo_mensaje);
    this->largo_mensajee = largo_mensaje;
}

void Intermediario::recibirMensaje(char* buf) {
    memcpy(buf, this->mensajee, this->largo_mensajee);
}

