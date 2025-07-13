
#include "recepcionista.h"

// Construtor da classe Recepcionista
Recepcionista::Recepcionista(const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(nome, login, senha) {}

// Retorna o tipo do usuário (Recepcionista)
std::string Recepcionista::get_tipo() const {
    return "Recepcionista";
}
