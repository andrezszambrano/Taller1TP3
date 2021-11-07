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
    //Se crea una thread safe cola reservando los recursos correspondientes.
    ThreadSafeQueue();

    //Se crea una thread safe queue a partir de otra. Se transfieren los derechos de los recursos
    //de la otra_cola hacia la nueva cola, dejando a la otra_cola en un estado inválido. No se hace
    //un move sobre el mutex, sino que se crea uno de cero.
    ThreadSafeQueue(ThreadSafeQueue&& otra_cola);

    //Se añade a la cola el mensaje pasado por parámetro. El método es thread-safe.
    void push(std::string&& mensaje);

    //Se saca el primer mensaje de la cola, guardándolo en el string pasado por parámetro. Si no hay
    //ningún elemento en la cola, se espera a que alguien más añada algo para poder sacarlo. El
    //método es thread safe.
    void pop(std::string& mensaje);

    //Se liberan los recursos de la cola correspondientemente.
    ~ThreadSafeQueue();
};

class MapaDeColasThreadSafe {
private:
    std::map<std::string, ThreadSafeQueue> colas;
    std::mutex mutex;

public:
    //Se crea un un mapa de colas thread safe reservando los recursos correspondientes.
    MapaDeColasThreadSafe();

    MapaDeColasThreadSafe(MapaDeColasThreadSafe& otro_mapa) = delete;

    MapaDeColasThreadSafe(MapaDeColasThreadSafe&& otro_mapa) = delete;

    //Se define una cola con el identificador dado. Si no existe una cola con el identificador, se
    //crea. Si ya existe no pasa nada.
    void definir(const std::string& identificador);

    //Se pushea en la cola con identificador dado por parámetro, el mensaje dado también por
    //parámetro. El método es thread-safe.
    void pushearEnCola(const std::string& identificador, std::string&& mensaje);

    //Se hace un pop de la cola con identificador dado por parámetro. Se guarda el mensaje en el
    //string pasado por parámetro. El método es thread-safe.
    void popDeLaCola(const std::string& identificador, std::string& mensaje);

    //Se liberan los recursos del mapa de colas acorde.
    ~MapaDeColasThreadSafe();
};

#endif //TP3FINAL_CLIENT_SERVER_COLAS_THREAD_SAFE_H
