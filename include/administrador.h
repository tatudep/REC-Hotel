#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H
#include "usuario.h"

// Classe que representa o usuário do tipo administrador
class Administrador : public Usuario {
public:
    // Construtor da classe Administrador
    Administrador(const std::string& nome, const std::string& login, const std::string& senha);
    // Retorna o tipo do usuário
    std::string get_tipo() const override;
};

#endif // ADMINISTRADOR_H
