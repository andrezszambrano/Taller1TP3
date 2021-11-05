#ifndef TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
#define TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H

#include <queue>
#include <map>
#include <string>
#include <list>

class ThreadSafeQueue {
    std::queue<std::string> cola;
    std::list<int> ids_clientes;

public:
    ThreadSafeQueue();

    void push(std::string&& mensaje);

    void pop(std::string& mensaje);

    ~ThreadSafeQueue();

};

class MapaDeColasThreadSafe {
private:
    std::map<std::string, ThreadSafeQueue> colas;

public:
    MapaDeColasThreadSafe();
    MapaDeColasThreadSafe(MapaDeColasThreadSafe& otroMapa);
    MapaDeColasThreadSafe(MapaDeColasThreadSafe&& otroMapa);
    void definir(const std::string& identificador);
    void pushearEnCola(const std::string& identificador, std::string&& mensaje);
    void popDeLaCola(const std::string& identificador, std::string& mensaje);
    ~MapaDeColasThreadSafe();
};



#endif //TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
