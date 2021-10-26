#ifndef TP3FINAL_SERVER_CLASE_H
#define TP3FINAL_SERVER_CLASE_H

#include "client_intermediario.h"
#include "client_protocolo_server.h"
#include "client_server_colas_thread_safe.h"

class Servidor {
private:
    ProtocoloServidor protocolo;
    ListaDeColasThreadSafe lista_colas;

public:
    Servidor();
    void notificarMensaje(Intermediario& intermediario);
    ~Servidor() = default;
};

#endif //TP3FINAL_SERVER_CLASE_H
