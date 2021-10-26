#include "client_server_colas_thread_safe.h"
#include <algorithm>


MapaDeColasThreadSafe::MapaDeColasThreadSafe() {}

void MapaDeColasThreadSafe::definir(std::string identificador) {
    bool hay_cola_con_identificador = this->colas.count(identificador);
    if (!hay_cola_con_identificador)
        this->colas.emplace(identificador, std::move(ThreadSafeQueue()));
    this->colas[identificador].aniadirId(0);
    //Añado id de cliente (si es que no hay ya)
}

MapaDeColasThreadSafe::~MapaDeColasThreadSafe() {
}


ThreadSafeQueue::ThreadSafeQueue() {
}

void ThreadSafeQueue::push(std::string&& mensaje) {
    this->cola.push(std::move(mensaje));
}

void ThreadSafeQueue::pop(std::string& mensaje) {
    mensaje = this->cola.front();
    this->cola.pop();
}

void ThreadSafeQueue::aniadirId(int id_cliente) {
    bool id_existe = (std::find(this->ids_clientes.begin(), this->ids_clientes.end(),
                                            id_cliente) != this->ids_clientes.end());
    if (!id_existe)
        this->ids_clientes.push_back(id_cliente);
}

ThreadSafeQueue::~ThreadSafeQueue() {
}
