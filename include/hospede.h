#ifndef HOSPEDE_H
#define HOSPEDE_H
#include "usuario.h"

// Classe que representa o usuário do tipo hóspede
class Hospede : public Usuario {
public:
    // Construtor da classe Hospede
    Hospede(const std::string& nome, const std::string& login, const std::string& senha);
    // Retorna o tipo do usuário
    std::string get_tipo() const override;
};

#endif // HOSPEDE_H
