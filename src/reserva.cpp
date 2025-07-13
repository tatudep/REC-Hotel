#include "reserva.h"
#include <ctime>
#include <cmath>





// Construtor da classe Reserva
Reserva::Reserva(Hospede* hospede, Quarto* quarto, const std::string& data_checkin, const std::string& data_checkout)
    : hospede(hospede), quarto(quarto), data_checkin(data_checkin), data_checkout(data_checkout) {}

// Retorna o hóspede associado à reserva
Hospede* Reserva::get_hospede() const { return hospede; }

// Retorna o quarto associado à reserva
Quarto* Reserva::get_quarto() const { return quarto; }

// Retorna a data de check-in
std::string Reserva::get_data_checkin() const { return data_checkin; }

// Retorna a data de check-out
std::string Reserva::get_data_checkout() const { return data_checkout; }

// Define a data de check-in
void Reserva::set_data_checkin(const std::string& data) { data_checkin = data; }

// Define a data de check-out
void Reserva::set_data_checkout(const std::string& data) { data_checkout = data; }

// Adiciona um serviço extra à reserva
void Reserva::adicionar_servico(const ServicoExtra& servico) {
    servicos.push_back(servico);
}

// Retorna a lista de serviços extras da reserva
const std::vector<ServicoExtra>& Reserva::get_servicos() const {
    return servicos;
}

// Calcula o valor total da reserva (diárias + serviços extras)
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
