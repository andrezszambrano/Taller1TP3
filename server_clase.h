#ifndef TP3FINAL_SERVER_CLASE_H
#define TP3FINAL_SERVER_CLASE_H

#include "server_protocolo.h"
#include "server_colas_thread_safe.h"
#include "common_socket.h"
#include <mutex>
#include <list>
#include "server_maneja_clientes.h"

class Servidor {
private:
    Socket socket_aceptador;
    ProtocoloServidor protocolo;
    MapaDeColasThreadSafe mapa_colas;

public:
    Servidor() = delete;

    //Se crea un servidor dado un host y un servicio. Se reserva los recursos para el socket
    //aceptador. También se crea el mapa de colas.
    Servidor(const char* host, const char* servicio);

    //Se ejecuta el servidor. Si es true el parámetro, se ejecuta el servidor usando solo el hilo
    //main, por lo tanto solo se puede aceptar un cliente a la vez, aceptando 10 clientes nada más.
    //Si no es true, se ejecutan varios hilos, pudiendo tener varios clientes conectados al mismo
    //tiempo, interactuando con el servidor acorde. Cuando se ejecutan con varios hilos, no hay
    //límite acerca de cuántos clientes aceptar al mismo tiempo. Se termina la ejecución cuando se
    //recibe una 'q' por entrada estándar.
    void ejecutar(bool cero_hilos);

    //Se liberan los recursos usados por el servidor.
    ~Servidor() = default;

private:
    //Se inicia ejecución solo usando el hilo main. Se acepta de a un cliente por vez, hasta 10
    //clientes distintos.
    void ejecutarSoloHiloMain();

    //Se inicia la ejecución con hilos. El hilo main convoca al hilo aceptador, que va a recibir
    //conexiones de nuevos clientes, y va creando nuevos hilos para manejar la comunicación con cada
    //uno de los clientes conectados. No hay límite en la cantidad de clientes que pueden
    //conectarse. AGREGAR INFO DE EXCEPCIONES
    void ejecutarConHilos();

    //Función que sirve para convocar el hilo aceptador. Se aceptan clientes hasta que el accept del
    //socket aceptante lance una excepción.
    void ejecutarHiloAceptador();

    //Agrega al nuevo cliente a la lista. AGREGAR INFO DE EXCEPCIONES
    int agregarClienteALista(std::list<ManejaCliente>& hilos_clientes);
};

#endif //TP3FINAL_SERVER_CLASE_H
