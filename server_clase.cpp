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

Servidor::Servidor(const char* host, const char* servicio)
        :socket_aceptador(std::move(Socket::crearSocketServidorConBindYListen(host,
                                                                              servicio))),
         protocolo(), mapa_colas() {
}

void joinearHilosClientes(std::list<ManejaCliente>& hilos_clientes) {
    std::list<ManejaCliente>::iterator it;
    for (it = hilos_clientes.begin(); it != hilos_clientes.end(); ++it){
        it->join();
    }
}

void Servidor::agregarClienteALista(std::list<ManejaCliente>& hilos_clientes) {
    Socket socket_cliente = this->socket_aceptador.aceptarSocket();
    ManejaCliente cliente(std::move(socket_cliente), this->protocolo, this->mapa_colas);
    hilos_clientes.push_back(std::move(cliente));
}

void Servidor::ejecutarSoloHiloMain() {
    for (int i = 0; i < MAX_CLIENTES_CERO_HILOS; i++) {
        Socket socket_cliente = this->socket_aceptador.aceptarSocket();
        ManejaCliente cliente(std::move(socket_cliente), this->protocolo, this->mapa_colas);
        cliente.ejecutarAgarraExcepciones();
    }
}

void Servidor::ejecutarHiloAceptador() {
    std::list<ManejaCliente> hilos_clientes;
    std::list<ManejaCliente>::iterator it = hilos_clientes.begin(); //Lista vacía al principio
    while (true) {
        try {
            this->agregarClienteALista(hilos_clientes);
        } catch (const NoSePuedeAceptarSocketError& error) {
            joinearHilosClientes(hilos_clientes);
            return;
        }
        ++it; //Pasamos a apuntar al nuevo elemento
        it->empezar(); //Empezamos la ejecución
    }
}

void Servidor::ejecutarConHilos() {
    std::thread hilo_aceptador(&Servidor::ejecutarHiloAceptador, this);
    while (std::cin.get() != 'q') {
    }
    this->socket_aceptador.dejarDeAceptar();
    hilo_aceptador.join();
}

void Servidor::ejecutar(bool cero_hilos) {
    if (cero_hilos)
        ejecutarSoloHiloMain();
    else
        ejecutarConHilos();
}
