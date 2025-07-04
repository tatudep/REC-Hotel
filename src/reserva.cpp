#include "reserva.h"
#include <ctime>
#include <cmath>

Reserva::Reserva(Hospede* hospede, Quarto* quarto, const std::string& data_checkin, const std::string& data_checkout)
    : hospede(hospede), quarto(quarto), data_checkin(data_checkin), data_checkout(data_checkout) {}

Hospede* Reserva::get_hospede() const { return hospede; }
Quarto* Reserva::get_quarto() const { return quarto; }
std::string Reserva::get_data_checkin() const { return data_checkin; }
std::string Reserva::get_data_checkout() const { return data_checkout; }
void Reserva::set_data_checkin(const std::string& data) { data_checkin = data; }
void Reserva::set_data_checkout(const std::string& data) { data_checkout = data; }

void Reserva::adicionar_servico(const ServicoExtra& servico) {
    servicos.push_back(servico);
}

const std::vector<ServicoExtra>& Reserva::get_servicos() const {
    return servicos;
}

double Reserva::calcular_valor_total() const {
    if (!quarto) return 0.0;
    // Calcular número de diárias
    std::tm tm_in = {};
    std::tm tm_out = {};
    sscanf(data_checkin.c_str(), "%d/%d/%d", &tm_in.tm_mday, &tm_in.tm_mon, &tm_in.tm_year);
    sscanf(data_checkout.c_str(), "%d/%d/%d", &tm_out.tm_mday, &tm_out.tm_mon, &tm_out.tm_year);
    tm_in.tm_mon -= 1; tm_in.tm_year -= 1900;
    tm_out.tm_mon -= 1; tm_out.tm_year -= 1900;
    time_t t_in = mktime(&tm_in);
    time_t t_out = mktime(&tm_out);
    int dias = (int)std::round(std::difftime(t_out, t_in) / (60*60*24));
    if (dias < 1) dias = 1;
    double total = dias * quarto->get_preco();
    for (const auto& s : servicos) {
        total += s.get_preco();
    }
    return total;
}
