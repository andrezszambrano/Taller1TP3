#ifndef TP3FINAL_CLIENT_PROTOCOLO_H
#define TP3FINAL_CLIENT_PROTOCOLO_H

#include <string>
#include <array>
#include <map>
#include "client_intermediario.h"
#include "server_clase.h"
#define MAX_PALABRAS 3

class ProtocoloCliente {
private:
    std::map<std::string, char> map;

public:
    ProtocoloCliente();
    void comunicarMensaje(Socket& socket, std::array<std::string, MAX_PALABRAS>& tokens);
    std::string recibirMensaje(Socket& socket);
    ~ProtocoloCliente();
};



#endif //TP3FINAL_CLIENT_PROTOCOLO_H
