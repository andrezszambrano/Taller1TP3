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

    //Se recibe el mensaje siguiendo con el protocolo de comunicación a través del socket
    //pasado por parámetro. Se guarda la información necesaria en el parámetro info. Se retorna la
    //cantidad de bytes leidos.
    int recibirMensaje(Socket& socket, MensajeProtocolo& info);

    //Se envian hasta length bytes de los contenidos del buffer mensaje, a través del socket pasado
    //por parámetro.
    void enviarMensaje(Socket& socket, const char* mensaje, int length);

    ~ProtocoloServidor() = default;
};


#endif //TP3FINAL_SERVER_PROTOCOLO_H
