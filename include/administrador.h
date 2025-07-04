#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include "usuario.h"

class Administrador : public Usuario {
public:
    Administrador(const std::string& nome, const std::string& login, const std::string& senha);
    std::string get_tipo() const override;
};

#endif // ADMINISTRADOR_H
