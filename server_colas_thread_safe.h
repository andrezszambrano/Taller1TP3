#ifndef TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
#define TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H

#include <queue>
#include <map>
#include <string>
#include <list>
#include <mutex>
#include <condition_variable>

class ThreadSafeQueue {
    std::queue<std::string> cola;
    std::list<int> ids_clientes;
    std::mutex mutex;
    std::condition_variable condition_variable;

public:
    ThreadSafeQueue();

    ThreadSafeQueue(ThreadSafeQueue&& otraCola);

    void push(std::string&& mensaje);

    void pop(std::string& mensaje);

    ~ThreadSafeQueue();
};

class MapaDeColasThreadSafe {
private:
    std::map<std::string, ThreadSafeQueue> colas;
    std::mutex mutex;

public:
    MapaDeColasThreadSafe();
    MapaDeColasThreadSafe(MapaDeColasThreadSafe& otroMapa) = delete;
    MapaDeColasThreadSafe(MapaDeColasThreadSafe&& otroMapa) = delete;
    void definir(const std::string& identificador);
    void pushearEnCola(const std::string& identificador, std::string&& mensaje);
    void popDeLaCola(const std::string& identificador, std::string& mensaje);
    ~MapaDeColasThreadSafe();
};



#endif //TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
