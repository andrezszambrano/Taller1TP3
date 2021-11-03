#include "server_clase.h"

#include <iostream>
#define MAX_PALABRA 50
#define EXITO 0
#define SOCKET_NO_DISPONIBLE -1

Servidor::Servidor(const char* servicio)
        :socket_aceptador(), protocolo(), mapa_colas() {
    socket_aceptador.inicializarServidorConBindYListen(nullptr, servicio);
}

void Servidor::ejecutar() {
    Socket socket_cliente;
    this->socket_aceptador.aceptarSocket(socket_cliente);
    int aux = EXITO;
    while (aux != SOCKET_NO_DISPONIBLE)
        aux = recibirMensajeYRealizarAccion(socket_cliente);
    std::cout << "Cerraron el socket!" <<std::endl;
}

int Servidor::recibirMensajeYRealizarAccion(Socket& socket_cliente) {
    MensajeProtocolo info;
    int leidos = this->protocolo.recibirMensaje(socket_cliente, info);
    if (leidos == 0) //Cerraron el socket
        return SOCKET_NO_DISPONIBLE;
    if (info.accion == 'd') {
        this->mapa_colas.definir(info.nombre_cola);
    } else if (info.accion == 'u') {
        this->mapa_colas.pushearEnCola(info.nombre_cola, std::move(info.mensaje_adicional));
    } else if (info.accion == 'o') {
        std::string str_aux;
        this->mapa_colas.popDeLaCola(info.nombre_cola, str_aux);
        const char* mensaje = str_aux.c_str();
        this->protocolo.enviarMensaje(socket_cliente, mensaje, str_aux.size());
    }
    return EXITO;
}
