#ifndef TP3FINAL_SERVER_MANEJA_CLIENTES_H
#define TP3FINAL_SERVER_MANEJA_CLIENTES_H

#include "server_protocolo.h"
#include "server_colas_thread_safe.h"
#include "common_socket.h"
#include <thread>

class ManejaCliente {
private:
        std::thread hilo;
        Socket socket_cliente;
        ProtocoloServidor protocolo;
        MapaDeColasThreadSafe& mapa_colas;

public:
    ManejaCliente() = delete;
    ManejaCliente(ManejaCliente&& otroCliente);
    ManejaCliente(Socket&& socket, ProtocoloServidor& protocolo, MapaDeColasThreadSafe& mapa);
    void empezar();
    void join();
    ~ManejaCliente();

private:
    void ejecutarAgarraExcepciones();
    void ejecutar();
    int recibirMensajeYRealizarAccion();
};


#endif //TP3FINAL_SERVER_MANEJA_CLIENTES_H
