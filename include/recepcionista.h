#ifndef RECEPCIONISTA_H
#define RECEPCIONISTA_H
#include "usuario.h"

// Classe que representa o usuário do tipo recepcionista
class Recepcionista : public Usuario {
public:
    // Construtor da classe Recepcionista
    Recepcionista(const std::string& nome, const std::string& login, const std::string& senha);
    // Retorna o tipo do usuário
    std::string get_tipo() const override;
};

#endif // RECEPCIONISTA_H
