#ifndef QUARTO_H
#define QUARTO_H

#include <string>

class Quarto {

    int numero; // Número identificador do quarto
    std::string tipo; // Tipo de acomodação (Single, Duplex, Suite)
    double preco; // Preço da diária
    bool ocupado; // Status de ocupação: true = ocupado, false = livre

public:

    //Declarando o construtor da classe "Quarto"
    Quarto(int numero, const std::string& tipo, double preco);

    //Declarando getters and Setters
    int get_numero() const;
    std::string get_tipo()const;
    double get_preco()const;
    bool get_ocupado() const;

    void set_tipo(const std::string& novo_tipo);
    void set_preco(double novo_preco);
    void set_ocupado(bool ocupado);
    void set_numero(int numero);


};


#endif