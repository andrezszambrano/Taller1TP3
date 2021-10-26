#include "client_server_colas_thread_safe.h"
#include <algorithm>


MapaDeColasThreadSafe::MapaDeColasThreadSafe() {}

void MapaDeColasThreadSafe::definir(const std::string identificador) {
    bool hay_cola_con_identificador = this->colas.count(identificador);
    if (!hay_cola_con_identificador)
        this->colas.emplace(identificador, std::move(ThreadSafeQueue()));
    this->colas[identificador].aniadirId(0);
    //Añado id de cliente (si es que no hay ya)
}

void MapaDeColasThreadSafe::pushearEnCola(const std::string identificador, std::string&& mensaje) {
    bool hay_cola_con_identificador = this->colas.count(identificador);
    if (!hay_cola_con_identificador)
        return;
    this->colas[identificador].push(std::move(mensaje), 0);
}

void MapaDeColasThreadSafe::popDeLaCola(const std::string identificador, std::string& mensaje) {
    bool hay_cola_con_identificador = this->colas.count(identificador);
    if (!hay_cola_con_identificador)
        return;
    this->colas[identificador].pop(mensaje, 0);
}


MapaDeColasThreadSafe::~MapaDeColasThreadSafe() {
}


ThreadSafeQueue::ThreadSafeQueue() {
}

bool ThreadSafeQueue::idSeEncuentraEnListaDeIds(int id_cliente) {
    return (std::find(this->ids_clientes.begin(), this->ids_clientes.end(),
                      id_cliente) != this->ids_clientes.end());
}

void ThreadSafeQueue::push(std::string&& mensaje, int id_cliente) {
    bool id_existe = idSeEncuentraEnListaDeIds(id_cliente);
    if (!id_existe)
        return;
    this->cola.push(std::move(mensaje));
}

void ThreadSafeQueue::pop(std::string& mensaje, int id_cliente) {
    bool id_existe = idSeEncuentraEnListaDeIds(id_cliente);
    if (!id_existe)
        return;
    mensaje = this->cola.front();
    this->cola.pop();
}

void ThreadSafeQueue::aniadirId(int id_cliente) {
    bool id_existe = idSeEncuentraEnListaDeIds(id_cliente);
    if (!id_existe)
        this->ids_clientes.push_back(id_cliente);
}

ThreadSafeQueue::~ThreadSafeQueue() {
}
