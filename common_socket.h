#ifndef TP3FINAL_CLIENT_SOCKET_H
#define TP3FINAL_CLIENT_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

class Socket {
private:
    int fd;

public:
    Socket(Socket&& otro_socket);
    static Socket crearSocketClienteYConectarlo(const char* host, const char* servicio);
    static Socket crearSocketServidorConBindYListen(const char* host, const char* servicio);
    Socket aceptarSocket();
    bool esValido();
    void dejarDeAceptar();
    ssize_t enviarMensaje(const char* buffer, size_t length);
    ssize_t recibirMensaje(char* buffer, size_t length);
    ~Socket();

private:
    Socket();
    void inicializarYConectarCliente(const char* host, const char* servicio);
    void inicializarServidorConBindYListen(const char* host, const char* servicio);
    explicit Socket(int fd_valido);
    void shutdownYCerrar();
};




#endif //TP3FINAL_CLIENT_SOCKET_H
