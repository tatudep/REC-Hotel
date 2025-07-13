#ifndef GERENCIADOR_QUARTOS_H
#define GERENCIADOR_QUARTOS_H

#include "Quarto.h"
#include <vector>
#include <string>

// Classe responsável por gerenciar os quartos do hotel
class GerenciadorQuartos {
private:
    std::vector<Quarto> quartos; // Vetor para armazenar os quartos

public:
    // Adiciona um novo quarto ao sistema
    void adicionar_quarto(const Quarto& novo_quarto);
    // Lista todos os quartos cadastrados
    void listar_quartos() const;
    // Edita os dados de um quarto pelo número
    void editar_quarto(int numero);
    // Remove um quarto pelo número
    void remover_quarto(int numero);
    // Busca quartos por tipo de acomodação
    std::vector<Quarto> buscar_por_tipo(const std::string& tipo) const;
    // Realiza check-in em um quarto
    void checkin(int numero_quarto);
    // Realiza check-out em um quarto
    void checkout(int numero_quarto);
};

#endif // GERENCIADOR_QUARTOS_H