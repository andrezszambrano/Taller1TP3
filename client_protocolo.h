#ifndef TP3FINAL_CLIENT_PROTOCOLO_H
#define TP3FINAL_CLIENT_PROTOCOLO_H

#include <string>
#include <array>
#include <map>
#define MAX_PALABRAS 3
class ProtocoloCliente {
private:
    std::map<std::string, char> map;

public:
    ProtocoloCliente();
    void comunicarMensajes(std::array<std::string, MAX_PALABRAS>& tokens);
    void recibirMensaje();
    ~ProtocoloCliente();
};



#endif //TP3FINAL_CLIENT_PROTOCOLO_H
