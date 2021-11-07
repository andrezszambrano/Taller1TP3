#ifndef TP3FINAL_SERVER_MANEJA_CLIENTES_H
#define TP3FINAL_SERVER_MANEJA_CLIENTES_H

#include "server_protocolo.h"
#include "server_colas_thread_safe.h"
#include "common_socket.h"
#include <thread>

class ManejaCliente {
private:
        std::thread hilo;
        Socket socket_cliente;
        ProtocoloServidor protocolo;
        MapaDeColasThreadSafe& mapa_colas;

public:
    ManejaCliente() = delete;

    //Se crea un maneja cliente reservando los recursos correspondientes, y guardando los parámetros
    //pedidos.
    ManejaCliente(Socket&& socket, ProtocoloServidor& protocolo, MapaDeColasThreadSafe& mapa);

    //Se crea un nuevo maneja cliente, dejando el otro en un estado inválido.
    ManejaCliente(ManejaCliente&& otro_cliente);

    //Se crea un nuevo hilo de trabajo.
    void empezar();

    //Se ejecuta la comunicación entre el maneja cliente y su respectivo cliente, hasta que se
    //detecte que el socket cliente se desconectó.
    void ejecutar();

    //Se joinea el hilo del maneja cliente con el hilo convocante.
    void join();

    //Se liberan los recursos acorde.
    ~ManejaCliente();

private:
    //Se ejecuta la función, agarrando las excepciones si es que las hay.
    void ejecutarAgarraExcepciones();

    //Recibe mensaje a través del socket y realiza la acción correspondiente, alterando el mapa de
    //colas.
    int recibirMensajeYRealizarAccion();
};


#endif //TP3FINAL_SERVER_MANEJA_CLIENTES_H
