#ifndef RESERVA_H
#define RESERVA_H
#include <string>
#include <vector>
#include "hospede.h"
#include "Quarto.h"
#include "servicoextra.h"

// Classe que representa uma reserva feita por um hóspede
class Reserva {
private:
    Hospede* hospede; // Ponteiro para o hóspede que fez a reserva
    Quarto* quarto; // Ponteiro para o quarto reservado
    std::string data_checkin; // Data de entrada
    std::string data_checkout; // Data de saída
    std::vector<ServicoExtra> servicos; // Serviços extras utilizados na reserva
public:
    // Construtor da classe Reserva
    Reserva(Hospede* hospede, Quarto* quarto, const std::string& data_checkin, const std::string& data_checkout);
    // Métodos de acesso aos atributos
    Hospede* get_hospede() const; // Retorna o hóspede
    Quarto* get_quarto() const; // Retorna o quarto
    std::string get_data_checkin() const; // Retorna a data de entrada
    std::string get_data_checkout() const; // Retorna a data de saída
    // Métodos para modificar as datas
    void set_data_checkin(const std::string& data);
    void set_data_checkout(const std::string& data);
    // Adiciona um serviço extra à reserva
    void adicionar_servico(const ServicoExtra& servico);
    // Retorna a lista de serviços extras
    const std::vector<ServicoExtra>& get_servicos() const;
    // Calcula o valor total da reserva
    double calcular_valor_total() const;
};

#endif // RESERVA_H
