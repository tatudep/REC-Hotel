#ifndef GERENCIADOR_QUARTOS_H
#define GERENCIADOR_QUARTOS_H

#include "Quarto.h"
#include <vector>
#include <string>


class GerenciadorQuartos {


    std::vector<Quarto> quartos; //Criação de vetor para armazenar os quartos e seus atributos

    public:
        //Declaração das funções para o gerenciamento dos quartos
        void adicionar_quarto(const Quarto& novo_quarto);
        void listar_quartos() const;
        void editar_quarto(int numero);
        void remover_quarto(int numero);
        std::vector<Quarto> buscar_por_tipo(const std::string& tipo) const;
        void checkin(int numero_quarto);
        void checkout(int numero_quarto);
};

#endif