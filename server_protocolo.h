#ifndef TP3FINAL_SERVER_PROTOCOLO_H
#define TP3FINAL_SERVER_PROTOCOLO_H

#include <string>
#include "common_socket.h"
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
public:
    ProtocoloServidor() = default;
    int recibirMensaje(Socket& socket, MensajeProtocolo& info);
    void enviarMensaje(Socket& socket, const char* mensaje, int length);
    ~ProtocoloServidor() = default;
};


#endif //TP3FINAL_SERVER_PROTOCOLO_H
