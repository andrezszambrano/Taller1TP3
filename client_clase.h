#ifndef TP3FINAL_CLIENTE_H
#define TP3FINAL_CLIENTE_H

#include "client_protocolo.h"
#include "common_socket.h"
#include <string>

class Cliente {
private:
    Socket socket_cliente;
    ProtocoloCliente protocolo;
    bool cliente_activo;
    bool esperando_mensaje;

public:
    Cliente() = delete;

    //Recibiendo un host y un servidor, se inicializa un socket cliente que se conectará al socket
    //del servidor.
    Cliente(const char* host, const char* servidor);

    //Se recibe por entrada estándar las operaciones a realizar. La operación define UnNombre define
    //la cola con UnNombre en el servidor. La operación push UnNombre UnMensaje pushea en la cola
    //del servidor con nombre UnNombre el mensaje UnMensaje. Por último, la operación pop UnNombre
    //hace un pop de la cola del servidor con UnNombre, y además muestra por pantalla su contenido.
    //Si no hay ningún elemento en la cola llamada UnNombre, se espera a que otro cliente agregue
    //un elemento para poder sacarlo. Para salir del ciclo de operaciones escribir por entrada
    //estándar un exit.
    void ejecutar();

    //Se destruye el socket cliente.
    ~Cliente();

private:
    //Lee de entrada estándar y se realiza la acción correspondiente. Se lee hasta recibir una
    //operación válida (define, push, pop o exit). Una vez recibida la operación se actúa acorde.
    //Si es una de las primeras tres operaciones dadas se realiza comunicación con el servidor
    //correspondientemente. Si es exit se sale de la ejecución de operación.
    void leerDeEntradaEstandarYRealizarAccionCorrespondiente();

    //Se realiza la acción correspondiente a la recibida por entrada estándar.
    void realizarAccionCorrespondiente(std::array<std::string, MAX_PALABRAS>& tokens);

    //Se recibe una respuesta si es que se realizó una operación pop y se espera una respuesta del
    //servidor.
    void recibirRespuesta();
};



#endif //TP3FINAL_CLIENTE_H
