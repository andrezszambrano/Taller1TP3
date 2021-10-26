#include "client_server.h"

#define MAX_PALABRA 50

Servidor::Servidor(){

}


void Servidor::notificarMensaje(Intermediario& intermediario) {
    MensajeProtocolo info;
    this->protocolo.recibirMensaje(info, intermediario);
    if (info.accion == 'd') {
        this->mapa_colas.definir(info.nombre_cola);
    } else if (info.accion == 'u') {
        this->mapa_colas.pushearEnCola(info.nombre_cola, std::move(info.mensaje_adicional));
    } else if (info.accion == 'o') {
        std::string str_aux;
        this->mapa_colas.popDeLaCola(info.nombre_cola, str_aux);
        const char* mensaje = str_aux.c_str();
        intermediario.aniadirMensaje(mensaje, str_aux.size());
    }
}
