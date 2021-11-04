#ifndef TP3FINAL_SERVER_MANEJA_CLIENTES_H
#define TP3FINAL_SERVER_MANEJA_CLIENTES_H

#include "server_protocolo.h"
#include "server_colas_thread_safe.h"
#include "common_socket.h"
#include <thread>

class Thread {
private:
    std::thread hilo;

public:
    Thread();
    void empezar();
    void ejecutarAgarraExcepciones();
    virtual void ejecutar() = 0;
    void join();
    ~Thread();
};

class ManejaCliente: public Thread {
private:
        Socket socket_cliente;
        ProtocoloServidor protocolo;
        MapaDeColasThreadSafe mapa_colas;

public:
    ManejaCliente() = delete;
    ManejaCliente(Socket&& socket, ProtocoloServidor& protocolo, MapaDeColasThreadSafe& mapa);
    void ejecutar();
    ~ManejaCliente();

private:
    int recibirMensajeYRealizarAccion();
};


#endif //TP3FINAL_SERVER_MANEJA_CLIENTES_H
