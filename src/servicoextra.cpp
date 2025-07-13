
#include "servicoextra.h"

// Construtor da classe ServicoExtra
ServicoExtra::ServicoExtra(const std::string& nome, double preco, const std::string& descricao)
    : nome(nome), preco(preco), descricao(descricao) {}

// Retorna o nome do serviço extra
std::string ServicoExtra::get_nome() const { return nome; }

// Retorna o preço do serviço extra
double ServicoExtra::get_preco() const { return preco; }

// Retorna a descrição do serviço extra
std::string ServicoExtra::get_descricao() const { return descricao; }

// Define o nome do serviço extra
void ServicoExtra::set_nome(const std::string& nome) { this->nome = nome; }

// Define o preço do serviço extra
void ServicoExtra::set_preco(double preco) { this->preco = preco; }

// Define a descrição do serviço extra
void ServicoExtra::set_descricao(const std::string& descricao) { this->descricao = descricao; }
