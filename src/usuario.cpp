#include "usuario.h"

Usuario::Usuario(const std::string& nome, const std::string& login, const std::string& senha)
    : nome(nome), login(login), senha(senha) {}

std::string Usuario::get_nome() const { return nome; }
std::string Usuario::get_login() const { return login; }
std::string Usuario::get_senha() const { return senha; }
void Usuario::set_nome(const std::string& nome) { this->nome = nome; }
void Usuario::set_login(const std::string& login) { this->login = login; }
void Usuario::set_senha(const std::string& senha) { this->senha = senha; }
