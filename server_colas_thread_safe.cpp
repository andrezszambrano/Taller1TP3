#include "server_colas_thread_safe.h"
#include <algorithm>


MapaDeColasThreadSafe::MapaDeColasThreadSafe() {}

MapaDeColasThreadSafe::MapaDeColasThreadSafe(MapaDeColasThreadSafe& otroMapa)
        :colas(otroMapa.colas) {
}

MapaDeColasThreadSafe::MapaDeColasThreadSafe(MapaDeColasThreadSafe&& otroMapa)
                    :colas(std::move(otroMapa.colas)) {
}

void MapaDeColasThreadSafe::definir(const std::string& identificador) {
    bool hay_cola_con_identificador = this->colas.count(identificador);
    if (!hay_cola_con_identificador)
        this->colas.emplace(identificador, std::move(ThreadSafeQueue()));
}

void MapaDeColasThreadSafe::pushearEnCola(const std::string& identificador, std::string&& mensaje) {
    bool hay_cola_con_identificador = this->colas.count(identificador);
    if (!hay_cola_con_identificador)
        return;
    this->colas[identificador].push(std::move(mensaje));
}

void MapaDeColasThreadSafe::popDeLaCola(const std::string& identificador, std::string& mensaje) {
    bool hay_cola_con_identificador = this->colas.count(identificador);
    if (!hay_cola_con_identificador)
        return;
    this->colas[identificador].pop(mensaje);
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

ThreadSafeQueue::~ThreadSafeQueue() {
}
