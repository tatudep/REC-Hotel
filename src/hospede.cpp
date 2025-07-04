#include "hospede.h"

Hospede::Hospede(const std::string& nome, const std::string& login, const std::string& senha)
    : Usuario(nome, login, senha) {}

std::string Hospede::get_tipo() const {
    return "Hospede";
}
