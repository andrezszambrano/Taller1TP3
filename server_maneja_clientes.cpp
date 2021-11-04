#include "server_maneja_clientes.h"
#include <iostream>
#define EXITO 0
#define SOCKET_NO_DISPONIBLE -1

Thread::Thread() {
}

void Thread::ejecutarAgarraExcepciones() {
    this->ejecutar();

}

void Thread::empezar() {
    this->hilo = std::thread(&Thread::ejecutarAgarraExcepciones, this);
}


void Thread::join() {
    this->hilo.join();
}

Thread::~Thread() {
}

ManejaCliente::ManejaCliente(Socket&& socket, ProtocoloServidor& protocolo,
                             MapaDeColasThreadSafe& mapa)
              :socket_cliente(std::move(socket)), protocolo(protocolo) , mapa_colas(mapa) {
}

void ManejaCliente::ejecutar() {
    int aux = EXITO;
    while (aux != SOCKET_NO_DISPONIBLE)
        aux = this->recibirMensajeYRealizarAccion();
    std::cout << "Cerraron el socket!" <<std::endl;
}


int ManejaCliente::recibirMensajeYRealizarAccion() {
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

ManejaCliente::~ManejaCliente() {
}
