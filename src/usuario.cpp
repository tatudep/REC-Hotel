
#include "usuario.h"

// Construtor da classe Usuario
Usuario::Usuario(const std::string& nome, const std::string& login, const std::string& senha)
    : nome(nome), login(login), senha(senha) {}

// Retorna o nome do usuário
std::string Usuario::get_nome() const { return nome; }

// Retorna o login do usuário
std::string Usuario::get_login() const { return login; }

// Retorna a senha do usuário
std::string Usuario::get_senha() const { return senha; }

// Define o nome do usuário
void Usuario::set_nome(const std::string& nome) { this->nome = nome; }

// Define o login do usuário
void Usuario::set_login(const std::string& login) { this->login = login; }

// Define a senha do usuário
void Usuario::set_senha(const std::string& senha) { this->senha = senha; }
