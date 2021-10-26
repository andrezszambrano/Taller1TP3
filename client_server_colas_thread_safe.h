#ifndef TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
#define TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H

#include <queue>
#include <map>
#include <string>

class ThreadSafeQueue {
    std::queue<std::string> cola;

public:
    ThreadSafeQueue();

    void push(std::string&& mensaje);

    void pop(std::string& mensaje);

    ~ThreadSafeQueue();
};

class MapaDeColasThreadSafe {
private:
    std::map<char, ThreadSafeQueue> colas;

public:
    MapaDeColasThreadSafe();
    ~MapaDeColasThreadSafe();
};



#endif //TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
