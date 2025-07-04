#include "administrador.h"

Administrador::Administrador(const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(nome, login, senha) {}

std::string Administrador::get_tipo() const {
    return "Administrador";
}
