#include "server_clase.h"

#define MAX_PALABRA 50

Servidor::Servidor(const char* servicio)
        :socket_aceptador(), protocolo(), mapa_colas() {
    socket_aceptador.inicializarServidorConBindYListen(nullptr, servicio);
}

void Servidor::ejecutar() {
    Socket socket_cliente;
    this->socket_aceptador.aceptarSocket(socket_cliente);
    recibirMensajeYRealizarAccion(socket_cliente);
    recibirMensajeYRealizarAccion(socket_cliente);
    recibirMensajeYRealizarAccion(socket_cliente);
}

void Servidor::recibirMensajeYRealizarAccion(Socket& socket_cliente) {
    MensajeProtocolo info;
    this->protocolo.recibirMensaje(socket_cliente, info);
    if (info.accion == 'd') {
        this->mapa_colas.definir(info.nombre_cola);
    } else if (info.accion == 'u') {
        this->mapa_colas.pushearEnCola(info.nombre_cola, std::move(info.mensaje_adicional));
    } else if (info.accion == 'o') {
        std::string str_aux;
        this->mapa_colas.popDeLaCola(info.nombre_cola, str_aux);
        const char* mensaje = str_aux.c_str();
        this->protocolo.enviarMensaje(socket_cliente, mensaje, str_aux.size());
        //socket_cliente.enviarMensaje(mensaje, str_aux.size());
    }
}
