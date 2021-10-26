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
                               const std::string accion, int& largo_mensaje) {
    mensaje[0] = map.at(accion);
    largo_mensaje++;
}

void agregarLargoPalabra(char* mensaje, int offset, const std::string palabra, int& largo_mensaje) {
    uint16_t largoLE = palabra.size();
    uint16_t largoBE = htons(largoLE);
    memcpy(mensaje + offset, &largoBE, sizeof(uint16_t));
    largo_mensaje = largo_mensaje + sizeof(uint16_t);
}

void agregarPalabra(char* mensaje, int offset, const std::string palabra, int& largo_mensaje) {
    memcpy(mensaje + offset, palabra.c_str(), strlen(palabra.c_str()));
    largo_mensaje = largo_mensaje + palabra.size();
}

void agregarLetraLargoPalabraYPalabra(char* mensaje, const std::map<std::string, char>& map,
                                       const std::string accion, const std::string palabra,
                                       int& largo_mensaje) {
    agregarLetraDeInstruccion(mensaje, map, accion, largo_mensaje);
    agregarLargoPalabra(mensaje, largo_mensaje, palabra, largo_mensaje);
    agregarPalabra(mensaje, largo_mensaje, palabra, largo_mensaje);
}

void agregarLargoYPalabraExtra(char* mensaje, const std::string palabra, int& largo_mensaje) {
    agregarLargoPalabra(mensaje, largo_mensaje, palabra, largo_mensaje);
    agregarPalabra(mensaje, largo_mensaje, palabra, largo_mensaje);
}

void ProtocoloCliente::comunicarMensaje(std::array<std::string, MAX_PALABRAS>& tokens,
                                        Intermediario& intermediario, Servidor& servidor) {
    char mensaje[MAX_MENSAJE];
    int largo_mensaje = 0;
    agregarLetraLargoPalabraYPalabra(mensaje, this->map, tokens[0], tokens[1], largo_mensaje);
    if (tokens[0] == "push")
        agregarLargoYPalabraExtra(mensaje, tokens[2], largo_mensaje);
    intermediario.aniadirMensaje(mensaje, largo_mensaje);
    servidor.notificarMensaje(intermediario);
}

void ProtocoloCliente::recibirMensaje() {

}

ProtocoloCliente::~ProtocoloCliente() {

}

