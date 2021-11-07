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
    //por parámetro. Si algún token (en especial el token 0) no es un token válido, se lanza una
    //excepción del tipo MensajesNoSigueFormatoDeProtocoloError a la cual se le puede consultar
    //el mensaje de error.
    void comunicarMensaje(Socket& socket, const std::array<std::string, MAX_PALABRAS>& tokens);

    //Se recibe un mensaje a través del socket siguiendo con el protocolo [largo palabra, mensaje].
    //Dicho mensaje se guarda en el string pasado como refer
    void recibirMensaje(Socket& socket, std::string& palabra);

    ~ProtocoloCliente();

private:
    //Chequea si los tokens son válidos. Si algún token no corresponde con el protocolo se lanza la
    //excepción MensajesNoSigueFormatoDeProtocoloError a la cual se le puede preguntar cuál fue el
    //error.
    static void checkTokensOLanzarError(const std::array<std::string, MAX_PALABRAS>& tokens);
};

#endif //TP3FINAL_CLIENT_PROTOCOLO_H
