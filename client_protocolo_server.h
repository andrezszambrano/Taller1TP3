#ifndef TP3FINAL_SERVER_PROTOCOLO_H
#define TP3FINAL_SERVER_PROTOCOLO_H

#include "client_intermediario.h"
#include <string>

class MensajeProtocolo {
public:
    char accion;
    std::string nombre_cola;
    std::string mensaje_adicional;

public:
    MensajeProtocolo() = default;
    ~MensajeProtocolo() = default;
};

class ProtocoloServidor {
private:

public:
    ProtocoloServidor() = default;
    void recibirMensaje(MensajeProtocolo& info, Intermediario& intermediario);
    ~ProtocoloServidor() = default;

};


#endif //TP3FINAL_SERVER_PROTOCOLO_H
