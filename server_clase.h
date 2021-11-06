#ifndef TP3FINAL_SERVER_CLASE_H
#define TP3FINAL_SERVER_CLASE_H

#include "client_intermediario.h"
#include "server_protocolo.h"
#include "server_colas_thread_safe.h"
#include "common_socket.h"
#include <mutex>
#include <list>
#include "server_maneja_clientes.h"

class IntProtegido {
private:
    int num;
    std::mutex mutex;

public:
    IntProtegido();
    void setNum(int num);
    int getNum();
    ~IntProtegido();
};

class Servidor {
private:
    Socket socket_aceptador;
    ProtocoloServidor protocolo;
    MapaDeColasThreadSafe mapa_colas;

public:
    Servidor() = default;
    Servidor(const char* servicio);
    void ejecutar(bool cero_hilos);
    ~Servidor() = default;

private:
    void ejecutarSoloHiloMain();
    void ejecutarConHilos();
    void ejecutarHiloAceptador(IntProtegido& num);
    void agregarClienteALista(std::list<ManejaCliente>& hilos_clientes);
};

#endif //TP3FINAL_SERVER_CLASE_H
