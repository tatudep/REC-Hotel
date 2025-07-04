#ifndef HOSPEDE_H
#define HOSPEDE_H
#include "usuario.h"

class Hospede : public Usuario {
public:
    Hospede(const std::string& nome, const std::string& login, const std::string& senha);
    std::string get_tipo() const override;
};

#endif // HOSPEDE_H
