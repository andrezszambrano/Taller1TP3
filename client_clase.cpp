#include "client_clase.h"
#include <array>
#include <iostream>
#include <string>
#include <sstream>
#include "client_intermediario.h"
#define MAX_PALABRAS 3

Cliente::Cliente() {
}

Cliente::Cliente(int host, int servidor)
        :protocolo(), cliente_activo(true), esperando_mensaje(false) {

}

void cargarTokensDeEntradaEstandar(std::array<std::string, MAX_PALABRAS>& tokens) {
    std::string instruccion;
    std::getline(std::cin, instruccion);
    std::stringstream stream_de_instrucciones(instruccion);
    std::string str_aux;
    for (int i = 0; i < MAX_PALABRAS; i++)
        std::getline(stream_de_instrucciones, tokens[i], ' ');
}

void leerDeEntradaEstandar(std::array<std::string, MAX_PALABRAS>& tokens) {
    do{
        cargarTokensDeEntradaEstandar(tokens);
    } while ((tokens[0] != "exit") && (tokens[0] != "define") &&
             (tokens[0] != "pop") && (tokens[0] != "push"));
}

void Cliente::realizarAccionCorrespondiente(std::array<std::string, MAX_PALABRAS>& tokens,
                                            Intermediario& intermediario) {
    if (tokens[0] == "exit") {
        this->cliente_activo = false;
    } else {
        this->protocolo.comunicarMensaje(tokens, intermediario, this->servidor);
        if (tokens[0] == "pop")
            this->esperando_mensaje = true;
    }
}

void Cliente::leerDeEntradaEstandarYRealizarAccionCorrespondiente(Intermediario& intermediario) {
    std::array<std::string, MAX_PALABRAS> tokens;
    leerDeEntradaEstandar(tokens);
    realizarAccionCorrespondiente(tokens, intermediario);
}


void Cliente::recibirRespuesta(Intermediario& intermediario) {
    if (this->esperando_mensaje)
        this->protocolo.recibirMensaje();
}

void Cliente::ejecutar() {
    while (this->cliente_activo) {
        Intermediario intermediario;
        this->leerDeEntradaEstandarYRealizarAccionCorrespondiente(intermediario);
        this->recibirRespuesta(intermediario);
    }
}

Cliente::~Cliente() {

}
