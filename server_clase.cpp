#include "server_clase.h"
#include <thread>
#include <iostream>
#include "server_maneja_clientes.h"
#define MAX_PALABRA 50
#define EXITO 0
#define SEGUIR_ACEPTANDO 0
#define DEJAR_DE_ACEPTAR 1

Servidor::Servidor(const char* servicio)
        :socket_aceptador(), protocolo(), mapa_colas() {
    socket_aceptador.inicializarServidorConBindYListen(nullptr, servicio);
}

void joinearHilosClientes(std::list<ManejaCliente>& hilos_clientes) {
    std::list<ManejaCliente>::iterator it;
    for (it = hilos_clientes.begin(); it != hilos_clientes.end(); ++it){
        it->join();
    }
}

void Servidor::agregarClienteALista(std::list<ManejaCliente>& hilos_clientes) {
    Socket socket_cliente;
    this->socket_aceptador.aceptarSocket(socket_cliente);
    ManejaCliente cliente(std::move(socket_cliente), this->protocolo, this->mapa_colas);
    hilos_clientes.push_back(std::move(cliente));
}

void Servidor::ejecutarHiloAceptador(IntProtegido& num) {
    std::list<ManejaCliente> hilos_clientes;
    std::list<ManejaCliente>::iterator it = hilos_clientes.begin(); //Lista vacía al principio
    while (num.getNum() == SEGUIR_ACEPTANDO) {
        this->agregarClienteALista(hilos_clientes);
        it++; //Pasamos a apuntar al nuevo elemento
        it->empezar();
    }
    joinearHilosClientes(hilos_clientes);
}

void Servidor::ejecutar() {
    IntProtegido num;
    std::thread hilo_aceptador(&Servidor::ejecutarHiloAceptador, this, std::ref(num));
    while (std::cin.get() != 'q') {
    }
    num.setNum(DEJAR_DE_ACEPTAR);
    hilo_aceptador.join();
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
