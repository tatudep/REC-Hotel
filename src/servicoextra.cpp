#include "servicoextra.h"

ServicoExtra::ServicoExtra(const std::string& nome, double preco, const std::string& descricao)
    : nome(nome), preco(preco), descricao(descricao) {}

std::string ServicoExtra::get_nome() const { return nome; }
double ServicoExtra::get_preco() const { return preco; }
std::string ServicoExtra::get_descricao() const { return descricao; }
void ServicoExtra::set_nome(const std::string& nome) { this->nome = nome; }
void ServicoExtra::set_preco(double preco) { this->preco = preco; }
void ServicoExtra::set_descricao(const std::string& descricao) { this->descricao = descricao; }
