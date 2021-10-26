#ifndef TP3FINAL_CLIENT_SOCKET_H
#define TP3FINAL_CLIENT_SOCKET_H

#include <stddef.h>
#include <stdint.h>
#include <unistd.h>

class Socket {
private:
    int fd;

public:
    Socket();
    void inicializarYConectarCliente(const char* host, const char* servicio);
    void inicializarServidorConBindYListen(const char* host, const char* servicio);
    int aceptarSocket(Socket& socket_cliente);
    ssize_t enviarMensaje(const char* buffer, size_t length);
    ssize_t recibirMensaje(char* buffer, size_t length);
    ~Socket();

private:
    void aniadirFileDescriptorValido(int fd);
};




#endif //TP3FINAL_CLIENT_SOCKET_H
