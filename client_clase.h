#ifndef TP3FINAL_CLIENTE_H
#define TP3FINAL_CLIENTE_H

#include "client_protocolo.h"
#include "client_server.h"

class Cliente {
private:
    ProtocoloCliente protocolo;
    Servidor servidor;
    bool cliente_activo;
    bool esperando_mensaje;

public:
    Cliente();
    Cliente(int host, int servidor);
    void ejecutar();
    void leerDeEntradaEstandarYRealizarAccionCorrespondiente(Intermediario& intermediario);
    void recibirRespuesta(Intermediario& intermediario);
    ~Cliente();

private:
    void realizarAccionCorrespondiente(std::array<std::string, MAX_PALABRAS>& tokens,
                                        Intermediario& intermediario);
};



#endif //TP3FINAL_CLIENTE_H
