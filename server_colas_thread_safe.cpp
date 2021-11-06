#include "server_colas_thread_safe.h"
#include <algorithm>


MapaDeColasThreadSafe::MapaDeColasThreadSafe() {}

void MapaDeColasThreadSafe::definir(const std::string& identificador) {
    const std::lock_guard<std::mutex> lock(this->mutex);
    bool hay_cola_con_identificador = this->colas.count(identificador);
    if (!hay_cola_con_identificador)
        this->colas.emplace(identificador, std::move(ThreadSafeQueue()));
}

void MapaDeColasThreadSafe::pushearEnCola(const std::string& identificador, std::string&& mensaje) {
    {
        const std::lock_guard<std::mutex> lock(this->mutex);
        bool hay_cola_con_identificador = this->colas.count(identificador);
        if (!hay_cola_con_identificador)
            return;
    }
    this->colas[identificador].push(std::move(mensaje));
}

void MapaDeColasThreadSafe::popDeLaCola(const std::string& identificador, std::string& mensaje) {
    {
        bool hay_cola_con_identificador = this->colas.count(identificador);
        if (!hay_cola_con_identificador)
            return;
    }
    this->colas[identificador].pop(mensaje);
}

MapaDeColasThreadSafe::~MapaDeColasThreadSafe() {
}

ThreadSafeQueue::ThreadSafeQueue() {
}

ThreadSafeQueue::ThreadSafeQueue(ThreadSafeQueue&& otraCola) {
}

void ThreadSafeQueue::push(std::string&& mensaje) {
    const std::lock_guard<std::mutex> lock(this->mutex);
    this->cola.push(std::move(mensaje));
    this->condition_variable.notify_all();
}

void ThreadSafeQueue::pop(std::string& mensaje) {
    std::unique_lock<std::mutex> uniqueLock(this->mutex);
    while (this->cola.empty())
        this->condition_variable.wait(uniqueLock);
    mensaje = this->cola.front();
    this->cola.pop();
}

ThreadSafeQueue::~ThreadSafeQueue() {
}
