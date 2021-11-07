#include "common_excepciones_de_protocolo.h"

MensajesNoSigueFormatoDeProtocoloError::MensajesNoSigueFormatoDeProtocoloError(
        const char* mensaje_de_error) noexcept
        :mensaje_de_error(mensaje_de_error) {
}

const char* MensajesNoSigueFormatoDeProtocoloError::what() const noexcept {
    return this->mensaje_de_error;
}

