#include "server_protocolo.h"
#include <cstring>
#include <arpa/inet.h>
#include "common_excepciones_de_protocolo.h"
#define MAX_MENSAJE 50
#define CERO_BYTES 0

void ProtocoloServidor::validarMensajesOLanzarError(const MensajeProtocolo& info) {
    if ((info.accion != 'd') && (info.accion != 'u') && (info.accion != 'o'))
        throw MensajesNoSigueFormatoDeProtocoloError("Error: mensaje recibido por cliente no es "
                                                     "válido. La primera letra tiene que ser 'd' "
                                                     "para definir una cola, 'u' para pushear en "
                                                     "una cola, o 'o' para popear de una cola");
}


void recibirCaracterYCargarAccion(Socket& socket, MensajeProtocolo& info, int& leidos) {
    char accion;
    int aux = socket.recibirMensaje(&accion, sizeof(char));
    info.accion = accion;
    leidos = leidos + aux;
}

uint16_t recibirLargoDePalabra(Socket& socket, int& leidos) {
    char buf[sizeof(uint16_t)];
    int aux = socket.recibirMensaje(buf, sizeof(uint16_t));
    if (aux == CERO_BYTES)
        return CERO_BYTES;
    uint16_t largoBE;
    memcpy(&largoBE, buf, sizeof(uint16_t));
    leidos = leidos + aux;
    return ntohs(largoBE);
}

void recibirPalabra(Socket& socket, char* buf, uint16_t largo_palabra, int& leidos) {
    int aux = socket.recibirMensaje(buf, largo_palabra);
    leidos = leidos + aux;
}

uint16_t recibirLargoDePalabraYPalabra(Socket& socket, char* buf, int& leidos) {
    uint16_t largo_palabra = recibirLargoDePalabra(socket, leidos);
    recibirPalabra(socket, buf, largo_palabra,leidos);
    return largo_palabra;
}


void recibirYAgregarIdentificador(Socket& socket, MensajeProtocolo& info, int& leidos) {
    char str_aux[MAX_MENSAJE];
    uint16_t largo = recibirLargoDePalabraYPalabra(socket, str_aux,leidos);
    info.nombre_cola.assign(str_aux, largo);
}

void recibirYAgregarMensajeAdicional(Socket& socket, MensajeProtocolo& info, int& leidos) {
    char str_aux[MAX_MENSAJE];
    uint16_t largo = recibirLargoDePalabraYPalabra(socket, str_aux,leidos);
    info.mensaje_adicional.assign(str_aux, largo);
}

int ProtocoloServidor::recibirMensaje(Socket& socket, MensajeProtocolo& info) {
    int leidos = 0;
    recibirCaracterYCargarAccion(socket, info, leidos);
    recibirYAgregarIdentificador(socket, info, leidos);
    if (info.accion == 'u')
        recibirYAgregarMensajeAdicional(socket, info, leidos);
    ProtocoloServidor::validarMensajesOLanzarError(info);
    return leidos;
}

void ProtocoloServidor::enviarMensaje(Socket& socket, const char* mensaje, int length) {
    uint16_t largo = length;
    uint16_t largoBE = htons(largo);
    char buf[2];
    memcpy(buf, &largoBE, sizeof(uint16_t));
    socket.enviarMensaje(buf, sizeof(uint16_t));
    socket.enviarMensaje(mensaje, length);
}
