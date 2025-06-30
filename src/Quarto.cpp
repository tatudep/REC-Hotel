#include "quarto.h"
#include <string>

//Definindo Construtor
Quarto::Quarto(int numero, const std::string& tipo, double preco)
    : numero(numero), tipo(tipo), preco(preco) {}

//Função que retorna o número do quarto
int Quarto::get_numero() const{
    return numero;
}

//Função que retorna o tipo do quarto
std::string Quarto::get_tipo() const {
    return tipo;
}

//Função que retorna o preço do quarto
double Quarto::get_preco() const {
    return preco;
}

//Função que retorna se o quarto está ocupado ou não
bool Quarto::get_ocupado() const {
    return ocupado;
}

//Função para definir o tipo do quarto
void Quarto::set_tipo(const std::string& novo_tipo) {
    tipo = novo_tipo;
}

//Função para definir o preço do quarto
void Quarto::set_preco(double novo_preco) {
    preco = novo_preco;
}

//Função para definir se o quarto está ocupado ou livre
void Quarto::set_ocupado(bool novo_status) {
    ocupado = novo_status;
}