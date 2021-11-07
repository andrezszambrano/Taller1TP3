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
    //cantidad de bytes leidos. Si algún campo de info no es válido según el protocolo, se lanza una
    //excepción del tipo MensajesNoSigueFormatoDeProtocoloError a la cual se le puede pedir cuál
    //fue el error.
    int recibirMensaje(Socket& socket, MensajeProtocolo& info);

    //Se envian hasta length bytes de los contenidos del buffer mensaje, a través del socket pasado
    //por parámetro.
    void enviarMensaje(Socket& socket, const char* mensaje, int length);

    ~ProtocoloServidor() = default;

private:
    //Chequea si los atributos de info son válidos. Si algún atributo no corresponde con el
    //protocolo se lanza la excepción MensajesNoSigueFormatoDeProtocoloError a la cual se le puede
    //preguntar cuál fue el error.
    void validarMensajesOLanzarError(const MensajeProtocolo& info);
};

#endif //TP3FINAL_SERVER_PROTOCOLO_H
