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
                               const std::string accion, int& escritos) {
    mensaje[0] = map.at(accion);
    escritos++;
}

void agregarLargoPalabra(char* mensaje, const std::string palabra, int& escritos) {
    uint16_t largo = palabra.size();
    uint16_t largoBE = htons(largo);
    memcpy(mensaje + escritos, &largoBE, sizeof(uint16_t));
    escritos = escritos + sizeof(uint16_t);
}

void agregarPalabra(char* mensaje, const std::string palabra, int& escritos) {
    memcpy(mensaje + escritos, palabra.c_str(), strlen(palabra.c_str()));
    escritos = escritos + palabra.size();
}

void agregarLetraLargoPalabraYPalabra(char* mensaje, const std::map<std::string, char>& map,
                                       const std::string accion, const std::string palabra,
                                       int& escritos) {
    agregarLetraDeInstruccion(mensaje, map, accion, escritos);
    agregarLargoPalabra(mensaje, palabra, escritos);
    agregarPalabra(mensaje, palabra, escritos);
}

void agregarLargoYPalabraExtra(char* mensaje, const std::string palabra, int& escritos) {
    agregarLargoPalabra(mensaje, palabra, escritos);
    agregarPalabra(mensaje, palabra, escritos);
}

void ProtocoloCliente::comunicarMensaje(std::array<std::string, MAX_PALABRAS>& tokens,
                                        Intermediario& intermediario, Servidor& servidor) {
    char mensaje[MAX_MENSAJE];
    int escritos = 0;
    agregarLetraLargoPalabraYPalabra(mensaje, this->map, tokens[0], tokens[1], escritos);
    if (tokens[0] == "push")
        agregarLargoYPalabraExtra(mensaje, tokens[2], escritos);
    intermediario.aniadirMensaje(mensaje, escritos);
    servidor.notificarMensaje(intermediario);
}

void ProtocoloCliente::recibirMensaje(std::string& mensaje, Intermediario& intermediario) {
    char mensaje_aux[MAX_MENSAJE];
    int largo = intermediario.recibirMensaje(mensaje_aux);
    //if ((int)mensaje.size() < largo)
      //  mensaje.reserve(largo);
    mensaje.append(mensaje_aux, largo) ;
    //if(largo>100){}

      //mensaje.assign(mensaje, largo);
}

ProtocoloCliente::~ProtocoloCliente() {

}

