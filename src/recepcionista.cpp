#include "recepcionista.h"

Recepcionista::Recepcionista(const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(nome, login, senha) {}

std::string Recepcionista::get_tipo() const {
    return "Recepcionista";
}
