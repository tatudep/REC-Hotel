
#include "administrador.h"

// Construtor da classe Administrador
Administrador::Administrador(const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(nome, login, senha) {}

// Retorna o tipo do usuário (Administrador)
std::string Administrador::get_tipo() const {
    return "Administrador";
}
