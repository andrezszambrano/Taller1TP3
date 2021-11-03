#ifndef TP3FINAL_CLIENTE_H
#define TP3FINAL_CLIENTE_H

#include "client_protocolo.h"
#include "common_socket.h"
class Cliente {
private:
    Socket socket_cliente;
    ProtocoloCliente protocolo;
    bool cliente_activo;
    bool esperando_mensaje;

public:
    Cliente();
    Cliente(const char* host, const char* servidor);
    void ejecutar();
    ~Cliente();

private:
    void leerDeEntradaEstandarYRealizarAccionCorrespondiente();
    void recibirRespuesta();
    void realizarAccionCorrespondiente(std::array<std::string, MAX_PALABRAS>& tokens);
};



#endif //TP3FINAL_CLIENTE_H
