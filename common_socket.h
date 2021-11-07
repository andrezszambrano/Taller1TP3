#ifndef TP3FINAL_CLIENT_SOCKET_H
#define TP3FINAL_CLIENT_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>
#include <exception>

class Socket {
private:
    int fd;

public:
    //Crea un socket que pasa a tener el fd del otro_socket. Se invalida el otro_socket cambiándole
    //su fd a un fd inválido.
    Socket(Socket&& otro_socket);

    //Se crea y retorna un socket cliente usando el host y el servicio pedido, conectándolo
    //correspondientemente.
    static Socket crearSocketClienteYConectarlo(const char* host, const char* servicio);

    //Crea un socket servidor usando el host y el servicio pedido. Se le hace un bind y un listen,
    //dejandolo el socket en un estado válido para poder aceptar sockets clientes. Se retorna el
    //socket.
    static Socket crearSocketServidorConBindYListen(const char* host, const char* servicio);

    //Se crea y retorna un socket cliente a partir de un socket servidor (inicializado previamente
    //con el método de clase crearSocketServidorConBindYListen).
    Socket aceptarSocket();

    //ELIMINAR
    bool esValido();

    //Se hace un shutdown y close sobre el socket servidor.
    void dejarDeAceptar();

    //Se envían hasta length bytes del contenido de buffer. Se retorna la cantidad de bytes
    //escritos.
    ssize_t enviarMensaje(const char* buffer, size_t length);

    //Se reciben y almacenan en el buffer hasta length bytes. Se retornan la cantidad de bytes
    //leídos
    ssize_t recibirMensaje(char* buffer, size_t length);

    //Se liberan los recursos del socket. Si se tiene un fd válido, se hace un shutdown y un close
    //sobre dicho fd. Si es un fd inválido, se retorna y no se libera nada.
    ~Socket();

private:
    //Crea un socket con fd inicial es un fd inválido.
    Socket();

    //Inicializa el socket gracias a los parámetros host y servicio, y lo conecta al socket servidor
    //correspondientemente.
    void inicializarYConectarCliente(const char* host, const char* servicio);

    //Inicializa el socket servidor, haciéndole un bind y un listen, dejándolo en estado válido para
    //después poder ser usado para aceptar sockets clientes.
    void inicializarServidorConBindYListen(const char* host, const char* servicio);

    //Se crea un socket con el fd pasado por parámetro.
    explicit Socket(int fd_valido);

    //Se hace un shutdown y un close sobre el fd del socket.
    void shutdownYCerrar();
};

class NoSePuedeAceptarSocketError: public std::exception {
private:
    char* mensaje_de_error;

public:
    explicit NoSePuedeAceptarSocketError() noexcept;
    virtual const char* what()  const noexcept;
    ~NoSePuedeAceptarSocketError() = default;
};


#endif //TP3FINAL_CLIENT_SOCKET_H
