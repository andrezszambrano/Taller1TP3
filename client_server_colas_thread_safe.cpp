#include "client_server_colas_thread_safe.h"

ListaDeColasThreadSafe::ListaDeColasThreadSafe() {}


ListaDeColasThreadSafe::~ListaDeColasThreadSafe() {

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
