#ifndef TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
#define TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H

#include <queue>
#include <list>
#include <string>

class ThreadSafeQueue {
    std::queue<std::string> cola;

public:
    ThreadSafeQueue();

    void push(std::string&& mensaje);

    void pop(std::string& mensaje);

    ~ThreadSafeQueue();
};

class ListaDeColasThreadSafe {
private:
    std::list<ThreadSafeQueue> colas;

public:
    ListaDeColasThreadSafe();
    ~ListaDeColasThreadSafe();
};



#endif //TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
