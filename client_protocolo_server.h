#ifndef TP3FINAL_SERVER_PROTOCOLO_H
#define TP3FINAL_SERVER_PROTOCOLO_H

#include "client_intermediario.h"

class ProtocoloServidor {
private:

public:
    ProtocoloServidor() = default;
    void recibirMensaje(char* buf, Intermediario& intermediario);
    ~ProtocoloServidor() = default;

};



#endif //TP3FINAL_SERVER_PROTOCOLO_H
