#include "server_clase.h"
#include <thread>
#include <iostream>

#define MAX_PALABRA 50
#define EXITO 0
#define SOCKET_NO_DISPONIBLE -1
#define SEGUIR_ACEPTANDO 0
#define DEJAR_DE_ACEPTAR 1

Servidor::Servidor(const char* servicio)
        :socket_aceptador(), protocolo(), mapa_colas() {
    socket_aceptador.inicializarServidorConBindYListen(nullptr, servicio);
}

void Servidor::ejecutarHiloAceptador(IntProtegido& num) {
    while (num.getNum() == SEGUIR_ACEPTANDO) {
        Socket socket_cliente;
        this->socket_aceptador.aceptarSocket(socket_cliente);
        ejecutarCliente(socket_cliente);
    }
}

void Servidor::ejecutar() {
    IntProtegido num;
    std::thread hilo_aceptador(&Servidor::ejecutarHiloAceptador, this, std::ref(num));
    hilo_aceptador.join();
}

void Servidor::ejecutarCliente(Socket& socket_cliente) {
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

IntProtegido::IntProtegido()
            :num(0) {
}

void IntProtegido::setNum(int num) {
    const std::lock_guard<std::mutex> lock(this->mutex);
    this->num = num;
}

int IntProtegido::getNum() {
    const std::lock_guard<std::mutex> lock(this->mutex);
    return num;
}

IntProtegido::~IntProtegido() {
}
