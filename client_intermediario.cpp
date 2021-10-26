#include "client_intermediario.h"
#include <cstring>

void Intermediario::aniadirMensaje(const char* mensaje, int largo_mensaje) {
    strncpy(this->mensajee, mensaje, largo_mensaje);
    this->largo_mensajee = largo_mensaje;
}

void Intermediario::recibirMensaje(char* buf) {
    strncpy(buf, this->mensajee, this->largo_mensajee);
}

