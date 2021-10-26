#ifndef TP3FINAL_INTERMEDIARIO_H
#define TP3FINAL_INTERMEDIARIO_H

#define MAX_PALABRA 50

class Intermediario {
private:
    char mensajee[MAX_PALABRA];
    int largo_mensajee;

public:
    Intermediario() = default;
    void aniadirMensaje(const char* mensaje, int largo_mensaje);
    void recibirMensaje(char* buf);
    ~Intermediario() = default;
};

#endif //TP3FINAL_INTERMEDIARIO_H
