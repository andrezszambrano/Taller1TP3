#ifndef TP3FINAL_COMMON_EXCEPCIONES_DE_PROTOCOLO_H
#define TP3FINAL_COMMON_EXCEPCIONES_DE_PROTOCOLO_H

#include <exception>

class MensajesNoSigueFormatoDeProtocoloError: public std::exception {
private:
    const char* mensaje_de_error;

public:
    explicit MensajesNoSigueFormatoDeProtocoloError(const char* mensaje_de_error) noexcept;
    virtual const char* what()  const noexcept;
    ~MensajesNoSigueFormatoDeProtocoloError() = default;
};



#endif //TP3FINAL_COMMON_EXCEPCIONES_DE_PROTOCOLO_H
