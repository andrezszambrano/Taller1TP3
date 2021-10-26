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

    void aniadirId(int id_cliente);

    ~ThreadSafeQueue();
};

class MapaDeColasThreadSafe {
private:
    std::map<std::string, ThreadSafeQueue> colas;

public:
    MapaDeColasThreadSafe();
    void definir(std::string identificador);
    ~MapaDeColasThreadSafe();
};



#endif //TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
