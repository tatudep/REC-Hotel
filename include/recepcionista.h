#ifndef RECEPCIONISTA_H
#define RECEPCIONISTA_H
#include "usuario.h"

class Recepcionista : public Usuario {
public:
    Recepcionista(const std::string& nome, const std::string& login, const std::string& senha);
    std::string get_tipo() const override;
};

#endif // RECEPCIONISTA_H
