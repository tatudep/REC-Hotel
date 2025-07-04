#ifndef RESERVA_H
#define RESERVA_H
#include <string>
#include <vector>
#include "hospede.h"
#include "Quarto.h"
#include "servicoextra.h"

class Reserva {
private:
    Hospede* hospede;
    Quarto* quarto;
    std::string data_checkin;
    std::string data_checkout;
    std::vector<ServicoExtra> servicos;
public:
    Reserva(Hospede* hospede, Quarto* quarto, const std::string& data_checkin, const std::string& data_checkout);
    Hospede* get_hospede() const;
    Quarto* get_quarto() const;
    std::string get_data_checkin() const;
    std::string get_data_checkout() const;
    void set_data_checkin(const std::string& data);
    void set_data_checkout(const std::string& data);
    void adicionar_servico(const ServicoExtra& servico);
    const std::vector<ServicoExtra>& get_servicos() const;
    double calcular_valor_total() const;
};

#endif // RESERVA_H
