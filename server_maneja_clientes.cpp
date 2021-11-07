#include "server_maneja_clientes.h"
#include <iostream>
#include <utility>
#include <string>
#include "common_excepciones_de_protocolo.h"

#define EXITO 0
#define SOCKET_NO_DISPONIBLE -1

ManejaCliente::ManejaCliente(Socket&& socket, ProtocoloServidor& protocolo,
                             MapaDeColasThreadSafe& mapa)
              :socket_cliente(std::move(socket)), protocolo(protocolo) , mapa_colas(mapa) {
}

ManejaCliente::ManejaCliente(ManejaCliente&& otro_cliente)
                :hilo(std::move(otro_cliente.hilo)),
                 socket_cliente(std::move(otro_cliente.socket_cliente)),
                 protocolo(otro_cliente.protocolo),
                 mapa_colas(otro_cliente.mapa_colas) {
}

void ManejaCliente::empezar() {
    this->hilo = std::thread(&ManejaCliente::ejecutarAgarraExcepciones, this);
}

void ManejaCliente::ejecutarAgarraExcepciones() {
    try {
        this->ejecutar();
    } catch (const MensajesNoSigueFormatoDeProtocoloError& error) {
        std::cerr << error.what() << std::endl;
        return;
    } catch (const SocketNoInicializadoError& error) {
        std::cerr << error.what() << std::endl;
        return;
    } catch (...) {
        return;
    }
}

void ManejaCliente::ejecutar() {
    int aux = EXITO;
    while (aux != SOCKET_NO_DISPONIBLE)
        aux = this->recibirMensajeYRealizarAccion();
}

void ManejaCliente::join() {
    if (this->hilo.joinable())
        this->hilo.join();
}

void ManejaCliente::enviarMensajeDeCola(const std::string& nombre_cola) {
    std::string str_aux;
    this->mapa_colas.popDeLaCola(nombre_cola, str_aux);
    const char* mensaje = str_aux.c_str();
    this->protocolo.enviarMensaje(this->socket_cliente, mensaje, str_aux.size());
}


int ManejaCliente::recibirMensajeYRealizarAccion() {
    MensajeProtocolo info;
    int leidos = this->protocolo.recibirMensaje(this->socket_cliente, info);
    if (leidos == 0) //Cerraron el socket
        return SOCKET_NO_DISPONIBLE;
    if (info.accion == 'd')
        this->mapa_colas.definir(info.nombre_cola);
    else if (info.accion == 'u')
        this->mapa_colas.pushearEnCola(info.nombre_cola, std::move(info.mensaje_adicional));
    else if (info.accion == 'o')
        this->enviarMensajeDeCola(info.nombre_cola);
    return EXITO;
}

ManejaCliente::~ManejaCliente() {
}
