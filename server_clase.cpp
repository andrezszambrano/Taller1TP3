#include "server_clase.h"
#include <thread>
#include <iostream>
#include <utility>
#include "server_maneja_clientes.h"

#define MAX_PALABRA 50
#define EXITO 0
#define ERROR -1
#define SEGUIR_ACEPTANDO 0
#define DEJAR_DE_ACEPTAR 1
#define MAX_CLIENTES_CERO_HILOS 10
Servidor::Servidor(const char* servicio)
        :socket_aceptador(std::move(Socket::crearSocketServidorConBindYListen(nullptr,
                                                                              servicio))),
         protocolo(), mapa_colas() {
}

void joinearHilosClientes(std::list<ManejaCliente>& hilos_clientes) {
    std::list<ManejaCliente>::iterator it;
    for (it = hilos_clientes.begin(); it != hilos_clientes.end(); ++it){
        it->join();
    }
}

int Servidor::agregarClienteALista(std::list<ManejaCliente>& hilos_clientes) {
    Socket socket_cliente = this->socket_aceptador.aceptarSocket();
    if (!socket_cliente.esValido())
        return ERROR;
    ManejaCliente cliente(std::move(socket_cliente), this->protocolo, this->mapa_colas);
    hilos_clientes.push_back(std::move(cliente));
    return EXITO;
}

void Servidor::ejecutarSoloHiloMain() {
    for (int i = 0; i < MAX_CLIENTES_CERO_HILOS; i++) {
        Socket socket_cliente = this->socket_aceptador.aceptarSocket();
        ManejaCliente cliente(std::move(socket_cliente), this->protocolo, this->mapa_colas);
        cliente.ejecutar();
    }
}

void Servidor::ejecutarHiloAceptador(IntProtegido& num) {
    std::list<ManejaCliente> hilos_clientes;
    std::list<ManejaCliente>::iterator it = hilos_clientes.begin(); //Lista vacía al principio
    while (num.getNum() == SEGUIR_ACEPTANDO) {
        int aux = this->agregarClienteALista(hilos_clientes);
        if (aux == ERROR) {
            joinearHilosClientes(hilos_clientes);
            return;
        }
        ++it; //Pasamos a apuntar al nuevo elemento
        it->empezar();
    }
    joinearHilosClientes(hilos_clientes);
}

void Servidor::ejecutarConHilos() {
    IntProtegido num;
    std::thread hilo_aceptador(&Servidor::ejecutarHiloAceptador, this, std::ref(num));
    while (std::cin.get() != 'q') {
    }
    this->socket_aceptador.dejarDeAceptar();
    num.setNum(DEJAR_DE_ACEPTAR);
    hilo_aceptador.join();
}

void Servidor::ejecutar(bool cero_hilos) {
    if (cero_hilos)
        ejecutarSoloHiloMain();
    else
        ejecutarConHilos();
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
