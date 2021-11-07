#ifndef TP3FINAL_CLIENT_PROTOCOLO_H
#define TP3FINAL_CLIENT_PROTOCOLO_H

#include <string>
#include <array>
#include <map>
#include "server_clase.h"
#define MAX_PALABRAS 3

class ProtocoloCliente {
private:
    std::map<std::string, char> map;

public:
    ProtocoloCliente();

    //Dado un array de tokens (palabras), el token 0 siendo igual a la operación deseada (define,
    //push o pop), el token 1 igual al nombre de la pila afectada, y si corresponde
    //(token 0 == push) hay un token 2 que contiene el mensaje a pushear. Se forma entonces un
    //buffer con formato [Operacion, largo palabra, token1], y si es una operación push se le
    //agrega un [largo palabra, token2]. Dicho buffer se envía a través del socket mandado
    //por parámetro.
    void comunicarMensaje(Socket& socket, const std::array<std::string, MAX_PALABRAS>& tokens);

    //Se recibe un mensaje a través del socket siguiendo con el protocolo [largo palabra, mensaje].
    //Dicho mensaje se guarda en el string pasado como refer
    void recibirMensaje(Socket& socket, std::string& palabra);

    ~ProtocoloCliente();

private:
    static void checkTokensOLanzarError(const std::array<std::string, MAX_PALABRAS>& tokens);
};

class MensajesNoSigueFormatoDeProtocoloError: public std::exception {
private:
    const char* mensaje_de_error;

public:
    explicit MensajesNoSigueFormatoDeProtocoloError(const char* mensaje_de_error) noexcept;
    virtual const char* what()  const noexcept;
    ~MensajesNoSigueFormatoDeProtocoloError() = default;
};


#endif //TP3FINAL_CLIENT_PROTOCOLO_H
