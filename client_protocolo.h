#ifndef TP3FINAL_CLIENT_PROTOCOLO_H
#define TP3FINAL_CLIENT_PROTOCOLO_H

#include <string>
#include <array>
#include <map>
#include "client_intermediario.h"
#include "client_server.h"
#define MAX_PALABRAS 3

class ProtocoloCliente {
private:
    std::map<std::string, char> map;
    Intermediario intermediario;
public:
    ProtocoloCliente();
    void comunicarMensaje(std::array<std::string, MAX_PALABRAS>& tokens,
                          Intermediario& intermediario, Servidor& servidor);
    void recibirMensaje(std::string& mensaje, Intermediario& intermediario);
    ~ProtocoloCliente();
};



#endif //TP3FINAL_CLIENT_PROTOCOLO_H
