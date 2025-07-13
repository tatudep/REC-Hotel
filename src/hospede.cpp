
#include "hospede.h"

// Construtor da classe Hospede
Hospede::Hospede(const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(nome, login, senha) {}

// Retorna o tipo do usuário (Hospede)
std::string Hospede::get_tipo() const {
    return "Hospede";
}
