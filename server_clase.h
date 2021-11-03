#ifndef TP3FINAL_SERVER_CLASE_H
#define TP3FINAL_SERVER_CLASE_H

#include "client_intermediario.h"
#include "server_protocolo.h"
#include "server_colas_thread_safe.h"
#include "common_socket.h"

class Servidor {
private:
    Socket socket_aceptador;
    ProtocoloServidor protocolo;
    MapaDeColasThreadSafe mapa_colas;

public:
    Servidor() = default;
    Servidor(const char* servicio);
    void ejecutar();
    int recibirMensajeYRealizarAccion(Socket& socket_cliente);
    ~Servidor() = default;
};

#endif //TP3FINAL_SERVER_CLASE_H
