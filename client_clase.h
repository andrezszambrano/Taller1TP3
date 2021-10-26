#ifndef TP3FINAL_CLIENTE_H
#define TP3FINAL_CLIENTE_H

#include "client_protocolo.h"

class Cliente {
private:
    ProtocoloCliente protocolo;
    bool cliente_activo;
    bool esperando_mensaje;

public:
    Cliente();
    Cliente(int host, int servidor);
    void ejecutar();
    void leerDeEntradaEstandarYRealizarAccionCorrespondiente();
    void recibirRespuesta();
    ~Cliente();

private:
    void realizarAccionCorrespondiente(std::array<std::string, MAX_PALABRAS>& tokens);
};



#endif //TP3FINAL_CLIENTE_H
