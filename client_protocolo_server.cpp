#include "client_protocolo_server.h"
#include <cstring>
#include <arpa/inet.h>
#define MAX_MENSAJE 50

void cargarAccion(const char* mensaje, MensajeProtocolo& info, int& leidos) {
    info.accion = mensaje[0];
    leidos++;
}

int obtenerPalabra(const char* mensaje, char* buf, MensajeProtocolo& info, int& leidos) {
    uint16_t largoBE;
    memcpy(&largoBE, mensaje + leidos, sizeof(uint16_t));
    uint16_t largo = ntohs(largoBE);
    leidos = leidos + 2;
    memcpy(buf, mensaje + leidos, largo);
    leidos = leidos + largo;
    return largo;
}

void agregarIdentificador(const char* mensaje, MensajeProtocolo& info, int& leidos) {
    char str_aux[MAX_MENSAJE];
    int largo = obtenerPalabra(mensaje, str_aux,info, leidos);
    info.nombre_cola.assign(str_aux, largo);
}

void agregarMensajeAdicional(const char* mensaje, MensajeProtocolo& info, int& leidos) {
    char str_aux[MAX_MENSAJE];
    int largo = obtenerPalabra(mensaje, str_aux, info, leidos);
    info.mensaje_adicional.assign(str_aux, largo);
}

void ProtocoloServidor::recibirMensaje(MensajeProtocolo& info, Intermediario& intermediario) {
    char mensaje[MAX_MENSAJE];
    intermediario.recibirMensaje(mensaje);
    int leidos = 0;
    cargarAccion(mensaje, info, leidos);
    agregarIdentificador(mensaje, info, leidos);
    if (mensaje[0] == 'u')
        agregarMensajeAdicional(mensaje, info, leidos);
}


