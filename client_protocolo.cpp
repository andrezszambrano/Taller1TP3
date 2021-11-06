#include "client_protocolo.h"
#include <iostream>
#include <stdint.h>
#include <arpa/inet.h>
#include <cstring>

#define MAX_MENSAJE 50

ProtocoloCliente::ProtocoloCliente()
                :map({{"define", 'd'}, {"push", 'u'}, {"pop", 'o'},}) {
}

void agregarLetraDeInstruccion(char* mensaje, const std::map<std::string, char>& map,
                               const std::string& accion, int& escritos) {
    mensaje[0] = map.at(accion);
    escritos++;
}

void agregarLargoPalabra(char* mensaje, const std::string& palabra, int& escritos) {
    uint16_t largo = palabra.size();
    uint16_t largoBE = htons(largo);
    memcpy(mensaje + escritos, &largoBE, sizeof(uint16_t));
    escritos = escritos + sizeof(uint16_t);
}

void agregarPalabra(char* mensaje, const std::string& palabra, int& escritos) {
    memcpy(mensaje + escritos, palabra.c_str(), strlen(palabra.c_str()));
    escritos = escritos + palabra.size();
}

void agregarLetraLargoPalabraYPalabra(char* mensaje, const std::map<std::string, char>& map,
                                       const std::string& accion, const std::string& palabra,
                                       int& escritos) {
    agregarLetraDeInstruccion(mensaje, map, accion, escritos);
    agregarLargoPalabra(mensaje, palabra, escritos);
    agregarPalabra(mensaje, palabra, escritos);
}

void agregarLargoYPalabraExtra(char* mensaje, const std::string& palabra, int& escritos) {
    agregarLargoPalabra(mensaje, palabra, escritos);
    agregarPalabra(mensaje, palabra, escritos);
}

void ProtocoloCliente::comunicarMensaje(Socket& socket,
                                        const std::array<std::string, MAX_PALABRAS>& tokens) {
    char mensaje[MAX_MENSAJE];
    int escritos = 0;
    agregarLetraLargoPalabraYPalabra(mensaje, this->map, tokens[0], tokens[1], escritos);
    if (tokens[0] == "push")
        agregarLargoYPalabraExtra(mensaje, tokens[2], escritos);
    socket.enviarMensaje(mensaje, escritos);
}

uint16_t recibirLargoDePalabra(Socket& socket, int& leidos) {
    char buf[2];
    int aux = socket.recibirMensaje(buf, sizeof(uint16_t));
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

void ProtocoloCliente::recibirMensaje(Socket& socket, std::string& palabra) {
    int leidos = 0;
    char mensaje_aux[MAX_MENSAJE];
    memset(mensaje_aux, 0, MAX_MENSAJE*sizeof(char));
    recibirLargoDePalabraYPalabra(socket, mensaje_aux, leidos);
    palabra = mensaje_aux;
  //  mensaje.resize(largo + 1);
    //mensaje.assign(mensaje_aux, largo);
}

ProtocoloCliente::~ProtocoloCliente() {
}

