#include <iostream>
#include <limits>
#include <regex>
#include <sstream>
#include <iomanip>
#include "SistemaHotel.h"
#include "administrador.h"
#include "recepcionista.h"
#include "hospede.h"
#include "Quarto.h"
#include "reserva.h"
#include "servicoextra.h"
#include <windows.h>
#include <fstream>
#include <vector>

void exibir_ascii_art() {
    std::cout << "\n";
    std::cout << " ██╗  ██╗  ██████╗  ████████╗ ███████╗ ██╗         \n";
    std::cout << " ██║  ██║ ██╔═══██╗ ╚══██╔══╝ ██╔════╝ ██║         \n";
    std::cout << " ███████║ ██║   ██║    ██║    █████╗   ██║         \n";
    std::cout << " ██╔══██║ ██║   ██║    ██║    ██╔══╝   ██║         \n";
    std::cout << " ██║  ██║ ╚██████╔╝    ██║    ███████╗ ███████╗    \n";
    std::cout << " ╚═╝  ╚═╝  ╚═════╝     ╚═╝    ╚══════╝ ╚══════╝    \n";
    std::cout << "===================================================\n";
    std::cout << "          Sistema de Gestão REC-Hotel              \n";
    std::cout << "===================================================\n";
}

Usuario* login() {
    SistemaHotel* sistema = SistemaHotel::getInstance();
    std::string login, senha;
    std::cout << "===== Login =====\n";
    std::cout << "Login: "; std::getline(std::cin, login);
    std::cout << "Senha: "; std::getline(std::cin, senha);
    for (auto* u : sistema->getUsuarios()) {
        if (u->get_login() == login && u->get_senha() == senha) {
            std::cout << "Bem-vindo, " << u->get_nome() << "!\n";
            return u;
        }
    }
    std::cout << "Login ou senha incorretos!\n";
    return nullptr;
}

// Função utilitária para converter data string para struct tm
std::tm string_to_tm(const std::string& data) {
    std::tm tm = {};
    std::istringstream ss(data);
    ss >> std::get_time(&tm, "%d/%m/%Y");
    return tm;
}

// Função para comparar datas (retorna -1 se a < b, 0 se igual, 1 se a > b)
int compara_data(const std::string& a, const std::string& b) {
    std::tm tma = string_to_tm(a);
    std::tm tmb = string_to_tm(b);
    if (std::mktime(&tma) < std::mktime(&tmb)) return -1;
    if (std::mktime(&tma) > std::mktime(&tmb)) return 1;
    return 0;
}

// Função utilitária para comparar datas no formato dd/mm/aaaa
int comparar_datas(const std::string& data1, const std::string& data2) {
    int d1, m1, a1, d2, m2, a2;
    sscanf(data1.c_str(), "%d/%d/%d", &d1, &m1, &a1);
    sscanf(data2.c_str(), "%d/%d/%d", &d2, &m2, &a2);
    if (a1 != a2) return a1 - a2;
    if (m1 != m2) return m1 - m2;
    return d1 - d2;
}

void menu_principal(Usuario* usuario) {
    SistemaHotel* sistema = SistemaHotel::getInstance();
    int opcao = 0;
    do {
        system("cls"); // Limpa a tela no Windows
        exibir_ascii_art();
        std::cout << "Usuário: " << usuario->get_nome() << " (" << usuario->get_tipo() << ")\n";
        std::cout << "--------------------------------------------------------------------------------\n";
        if (usuario->get_tipo() == "Administrador") {
            std::cout << "[1]  Cadastrar Usuário\n";
            std::cout << "[2]  Listar Usuários\n";
        }
        if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
            std::cout << "[3]  Cadastrar Quarto\n";
            std::cout << "[4]  Listar Quartos\n";
            std::cout << "[5]  Cadastrar Reserva\n";
            std::cout << "[6]  Listar Reservas\n";
            std::cout << "[7]  Cadastrar Serviço Extra\n";
            std::cout << "[8]  Listar Serviços Extras\n";
            std::cout << "[9]  Excluir Usuário\n";
            std::cout << "[10] Excluir Quarto\n";
            std::cout << "[11] Excluir Reserva\n";
            std::cout << "[12] Excluir Serviço Extra\n";
            std::cout << "[13] Editar Usuário\n";
            std::cout << "[14] Editar Quarto\n";
            std::cout << "[15] Editar Reserva\n";
            std::cout << "[16] Editar Serviço Extra\n";
            std::cout << "[17] Finalizar Estadia\n";
            std::cout << "[18] Calcular Faturamento Mensal\n";
        }
        if (usuario->get_tipo() == "Hospede") {
            std::cout << "[8]  Visualizar Minhas Reservas\n";
        }
        std::cout << "[0]  Sair\n";
        std::cout << "================================================================================\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(opcao) {
            case 1:
                if (usuario->get_tipo() == "Administrador") {
                    std::string nome, login, senha;
                    int tipo;
                    std::cout << "Nome: "; std::getline(std::cin, nome);
                    std::cout << "Login: "; std::getline(std::cin, login);
                    std::cout << "Senha: "; std::getline(std::cin, senha);
                    std::cout << "Tipo (1-Administrador, 2-Recepcionista, 3-Hóspede): "; std::cin >> tipo;
                    std::cin.ignore();
                    Usuario* u = nullptr;
                    if (tipo == 1) u = new Administrador(nome, login, senha);
                    else if (tipo == 2) u = new Recepcionista(nome, login, senha);
                    else if (tipo == 3) u = new Hospede(nome, login, senha);
                    if (u) sistema->adicionar_usuario(u);
                    std::cout << "Usuário cadastrado!\n";
                }
                break;
            case 2:
                if (usuario->get_tipo() == "Administrador")
                    sistema->listar_usuarios();
                break;
            case 3:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    int numero;
                    std::string tipo;
                    double preco;
                    std::cout << "Número do quarto: "; std::cin >> numero;
                    std::cin.ignore();
                    std::cout << "Tipo: "; std::getline(std::cin, tipo);
                    std::cout << "Preço: "; std::cin >> preco;
                    std::cin.ignore();
                    sistema->adicionar_quarto(Quarto(numero, tipo, preco));
                    std::cout << "Quarto cadastrado!\n";
                }
                break;
            case 4:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista")
                    sistema->listar_quartos();
                break;
            case 5:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_usuarios();
                    sistema->listar_quartos();
                    int idx_hospede, idx_quarto;
                    std::string data_in, data_out;
                    std::cout << "Índice do hóspede (0-n): "; std::cin >> idx_hospede;
                    std::cout << "Índice do quarto (0-n): "; std::cin >> idx_quarto;
                    std::cin.ignore();
                    std::cout << "Data check-in (dd/mm/aaaa): "; std::getline(std::cin, data_in);
                    std::cout << "Data check-out (dd/mm/aaaa): "; std::getline(std::cin, data_out);
                    std::regex data_regex("^(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[0-2])/\\d{4}$");
                    if (!std::regex_match(data_in, data_regex) || !std::regex_match(data_out, data_regex)) {
                        std::cout << "Formato de data inválido! Use dd/mm/aaaa.\n";
                        break;
                    }
                    auto& usuarios = sistema->getUsuarios();
                    auto& quartos = sistema->getQuartos();
                    if (idx_hospede >= 0 && idx_hospede < (int)usuarios.size() && idx_quarto >= 0 && idx_quarto < (int)quartos.size()) {
                        Hospede* h = dynamic_cast<Hospede*>(usuarios[idx_hospede]);
                        if (h) {
                            // Verificar conflito de reserva aprimorado
                            bool conflito = false;
                            for (const auto& r : sistema->getReservas()) {
                                if (r.get_quarto()->get_numero() == quartos[idx_quarto].get_numero()) {
                                    if (!(comparar_datas(data_out, r.get_data_checkin()) <= 0 || comparar_datas(data_in, r.get_data_checkout()) >= 0)) {
                                        conflito = true;
                                        break;
                                    }
                                }
                            }
                            if (conflito) {
                                std::cout << "Já existe reserva para este quarto neste período!\n";
                            } else {
                                Reserva nova_reserva(h, &quartos[idx_quarto], data_in, data_out);
                                // Adicionar serviços extras à reserva
                                char add_serv;
                                std::cout << "Deseja adicionar serviços extras à reserva? (s/n): ";
                                std::cin >> add_serv;
                                std::cin.ignore();
                                if (add_serv == 's' || add_serv == 'S') {
                                    auto& servicos = sistema->getServicos();
                                    if (servicos.empty()) {
                                        std::cout << "Nenhum serviço extra cadastrado.\n";
                                    } else {
                                        std::cout << "Serviços disponíveis:\n";
                                        for (size_t i = 0; i < servicos.size(); ++i) {
                                            std::cout << i << ": " << servicos[i].get_nome() << " (R$ " << servicos[i].get_preco() << ") - " << servicos[i].get_descricao() << "\n";
                                        }
                                        std::cout << "Digite os índices dos serviços desejados separados por espaço (finalize com -1): ";
                                        int idx_serv;
                                        while (std::cin >> idx_serv && idx_serv != -1) {
                                            if (idx_serv >= 0 && idx_serv < (int)servicos.size()) {
                                                nova_reserva.adicionar_servico(servicos[idx_serv]);
                                            } else {
                                                std::cout << "Índice inválido!\n";
                                            }
                                        }
                                        std::cin.clear();
                                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                    }
                                }
                                sistema->adicionar_reserva(nova_reserva);
                                std::cout << "Reserva cadastrada! Valor total: R$ " << nova_reserva.calcular_valor_total() << "\n";
                            }
                        } else {
                            std::cout << "Usuário selecionado não é hóspede.\n";
                        }
                    } else {
                        std::cout << "Índices inválidos.\n";
                    }
                }
                break;
            case 6:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista")
                    sistema->listar_reservas();
                break;
            case 7:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    std::string nome, descricao;
                    double preco;
                    std::cout << "Nome do serviço: "; std::getline(std::cin, nome);
                    std::cout << "Preço: "; std::cin >> preco;
                    std::cin.ignore();
                    std::cout << "Descrição: "; std::getline(std::cin, descricao);
                    sistema->adicionar_servico(ServicoExtra(nome, preco, descricao));
                    std::cout << "Serviço cadastrado!\n";
                }
                break;
            case 8:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista")
                    sistema->listar_servicos();
                else if (usuario->get_tipo() == "Hospede") {
                    std::cout << "--- Minhas Reservas ---\n";
                    int i = 0;
                    for (const auto& r : sistema->getReservas()) {
                        if (r.get_hospede()->get_login() == usuario->get_login()) {
                            std::cout << i << ": Quarto " << r.get_quarto()->get_numero() << ", Check-in: " << r.get_data_checkin() << ", Check-out: " << r.get_data_checkout() << "\n";
                        }
                        ++i;
                    }
                }
                break;
            case 9:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_usuarios();
                    size_t idx;
                    std::cout << "Índice do usuário para excluir: ";
                    std::cin >> idx;
                    std::cin.ignore();
                    sistema->excluir_usuario(idx);
                    std::cout << "Usuário excluído!\n";
                }
                break;
            case 10:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_quartos();
                    size_t idx;
                    std::cout << "Índice do quarto para excluir: ";
                    std::cin >> idx;
                    std::cin.ignore();
                    sistema->excluir_quarto(idx);
                    std::cout << "Quarto excluído!\n";
                }
                break;
            case 11:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_reservas();
                    size_t idx;
                    std::cout << "Índice da reserva para excluir: ";
                    std::cin >> idx;
                    std::cin.ignore();
                    sistema->excluir_reserva(idx);
                    std::cout << "Reserva excluída!\n";
                }
                break;
            case 12:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_servicos();
                    size_t idx;
                    std::cout << "Índice do serviço para excluir: ";
                    std::cin >> idx;
                    std::cin.ignore();
                    sistema->excluir_servico(idx);
                    std::cout << "Serviço excluído!\n";
                }
                break;
            case 13:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_usuarios();
                    size_t idx;
                    std::string nome, login, senha;
                    std::cout << "Índice do usuário para editar: "; std::cin >> idx; std::cin.ignore();
                    std::cout << "Novo nome: "; std::getline(std::cin, nome);
                    std::cout << "Novo login: "; std::getline(std::cin, login);
                    std::cout << "Nova senha: "; std::getline(std::cin, senha);
                    sistema->editar_usuario(idx, nome, login, senha);
                    std::cout << "Usuário editado!\n";
                }
                break;
            case 14:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_quartos();
                    size_t idx; int numero; std::string tipo; double preco;
                    std::cout << "Índice do quarto para editar: "; std::cin >> idx; std::cin.ignore();
                    std::cout << "Novo número: "; std::cin >> numero; std::cin.ignore();
                    std::cout << "Novo tipo: "; std::getline(std::cin, tipo);
                    std::cout << "Novo preço: "; std::cin >> preco; std::cin.ignore();
                    sistema->editar_quarto(idx, numero, tipo, preco);
                    std::cout << "Quarto editado!\n";
                }
                break;
            case 15:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_reservas();
                    size_t idx;
                    int idx_hospede, idx_quarto;
                    std::string data_in, data_out;
                    std::cout << "Índice da reserva para editar: "; std::cin >> idx; std::cin.ignore();
                    sistema->listar_usuarios();
                    sistema->listar_quartos();
                    std::cout << "Novo índice do hóspede: "; std::cin >> idx_hospede;
                    std::cout << "Novo índice do quarto: "; std::cin >> idx_quarto; std::cin.ignore();
                    std::cout << "Nova data check-in: "; std::getline(std::cin, data_in);
                    std::cout << "Nova data check-out: "; std::getline(std::cin, data_out);
                    auto& usuarios = sistema->getUsuarios();
                    auto& quartos = sistema->getQuartos();
                    Hospede* h = (idx_hospede >= 0 && idx_hospede < (int)usuarios.size()) ? dynamic_cast<Hospede*>(usuarios[idx_hospede]) : nullptr;
                    Quarto* q = (idx_quarto >= 0 && idx_quarto < (int)quartos.size()) ? &quartos[idx_quarto] : nullptr;
                    if (h && q) {
                        // Verificar conflito de reserva aprimorado (ignorando a própria reserva)
                        bool conflito = false;
                        const auto& reservas = sistema->getReservas();
                        for (size_t i = 0; i < reservas.size(); ++i) {
                            if (i == idx) continue; // Ignora a reserva que está sendo editada
                            const auto& r = reservas[i];
                            if (r.get_quarto()->get_numero() == q->get_numero()) {
                                if (!(comparar_datas(data_out, r.get_data_checkin()) <= 0 || comparar_datas(data_in, r.get_data_checkout()) >= 0)) {
                                    conflito = true;
                                    break;
                                }
                            }
                        }
                        if (conflito) {
                            std::cout << "Já existe reserva para este quarto neste período!\n";
                        } else {
                            Reserva nova_reserva(h, q, data_in, data_out);
                            // Adicionar serviços extras à reserva editada
                            char add_serv;
                            std::cout << "Deseja adicionar/alterar serviços extras para esta reserva? (s/n): ";
                            std::cin >> add_serv;
                            std::cin.ignore();
                            if (add_serv == 's' || add_serv == 'S') {
                                auto& servicos = sistema->getServicos();
                                if (servicos.empty()) {
                                    std::cout << "Nenhum serviço extra cadastrado.\n";
                                } else {
                                    std::cout << "Serviços disponíveis:\n";
                                    for (size_t i = 0; i < servicos.size(); ++i) {
                                        std::cout << i << ": " << servicos[i].get_nome() << " (R$ " << servicos[i].get_preco() << ") - " << servicos[i].get_descricao() << "\n";
                                    }
                                    std::cout << "Digite os índices dos serviços desejados separados por espaço (finalize com -1): ";
                                    int idx_serv;
                                    while (std::cin >> idx_serv && idx_serv != -1) {
                                        if (idx_serv >= 0 && idx_serv < (int)servicos.size()) {
                                            nova_reserva.adicionar_servico(servicos[idx_serv]);
                                        } else {
                                            std::cout << "Índice inválido!\n";
                                        }
                                    }
                                    std::cin.clear();
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                                }
                            }
                            sistema->editar_reserva(idx, h, q, data_in, data_out);
                            sistema->getReservas()[idx] = nova_reserva; // Substitui a reserva editada pela nova (com serviços)
                            std::cout << "Reserva editada! Valor total: R$ " << nova_reserva.calcular_valor_total() << "\n";
                        }
                    } else {
                        std::cout << "Dados inválidos.\n";
                    }
                }
                break;
            case 16:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_servicos();
                    size_t idx; std::string nome, descricao; double preco;
                    std::cout << "Índice do serviço para editar: "; std::cin >> idx; std::cin.ignore();
                    std::cout << "Novo nome: "; std::getline(std::cin, nome);
                    std::cout << "Novo preço: "; std::cin >> preco; std::cin.ignore();
                    std::cout << "Nova descrição: "; std::getline(std::cin, descricao);
                    sistema->editar_servico(idx, nome, preco, descricao);
                    std::cout << "Serviço editado!\n";
                }
                break;
            case 17:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    sistema->listar_reservas();
                    auto& reservas = sistema->getReservas();
                    if (reservas.empty()) {
                        std::cout << "Nenhuma reserva para finalizar.\n";
                        break;
                    }
                    size_t idx;
                    std::cout << "Índice da reserva para finalizar: ";
                    std::cin >> idx;
                    std::cin.ignore();
                    if (idx >= reservas.size()) {
                        std::cout << "Índice inválido!\n";
                        break;
                    }
                    char usou;
                    std::cout << "Usou serviços extras? (s/n): ";
                    std::cin >> usou;
                    std::cin.ignore();
                    bool usou_servicos = (usou == 's' || usou == 'S');
                    double valor_final = reservas[idx].calcular_valor_total();
                    if (usou_servicos) {
                        auto& servicos = sistema->getServicos();
                        if (servicos.empty()) {
                            std::cout << "Nenhum serviço extra cadastrado.\n";
                        } else {
                            std::cout << "Serviços disponíveis:\n";
                            for (size_t i = 0; i < servicos.size(); ++i) {
                                std::cout << i << ": " << servicos[i].get_nome() << " (R$ " << servicos[i].get_preco() << ") - " << servicos[i].get_descricao() << "\n";
                            }
                            std::cout << "Digite os índices dos serviços usados separados por espaço (finalize com -1): ";
                            int idx_serv;
                            while (std::cin >> idx_serv && idx_serv != -1) {
                                if (idx_serv >= 0 && idx_serv < (int)servicos.size()) {
                                    valor_final += servicos[idx_serv].get_preco();
                                } else {
                                    std::cout << "Índice inválido!\n";
                                }
                            }
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }
                    sistema->finalizar_estadia(idx, usou_servicos, valor_final);
                    std::cout << "Estadia finalizada e registrada! Valor final: R$ " << valor_final << "\n";
                }
                break;
            case 18:
                if (usuario->get_tipo() == "Administrador" || usuario->get_tipo() == "Recepcionista") {
                    std::string mes_ano;
                    std::cout << "Digite o mês e ano para faturamento (mm/aaaa): ";
                    std::getline(std::cin, mes_ano);
                    std::ifstream festadias("estadias.txt", std::ios::binary);
                    if (!festadias.is_open()) {
                        std::cout << "Nenhuma estadia registrada ainda.\n";
                        break;
                    }
                    std::string linha;
                    bool primeira_linha = true;
                    std::vector<std::string> estadias_mes;
                    double total = 0.0;
                    while (std::getline(festadias, linha)) {
                        if (primeira_linha) {
                            if (linha.size() >= 3 && (unsigned char)linha[0] == 0xEF && (unsigned char)linha[1] == 0xBB && (unsigned char)linha[2] == 0xBF) {
                                linha = linha.substr(3);
                            }
                            primeira_linha = false;
                        }
                        if (linha.empty()) continue;
                        // Formato: nome;numero_quarto;data_in;data_out;usou_servicos;valor_final
                        size_t p1 = linha.find(';');
                        size_t p2 = linha.find(';', p1+1);
                        size_t p3 = linha.find(';', p2+1);
                        size_t p4 = linha.find(';', p3+1);
                        size_t p5 = linha.find(';', p4+1);
                        if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos || p4 == std::string::npos || p5 == std::string::npos) continue;
                        std::string nome = linha.substr(0, p1);
                        std::string numero_quarto = linha.substr(p1+1, p2-p1-1);
                        std::string data_in = linha.substr(p2+1, p3-p2-1);
                        std::string data_out = linha.substr(p3+1, p4-p3-1);
                        std::string usou_servicos = linha.substr(p4+1, p5-p4-1);
                        std::string valor_final_str = linha.substr(p5+1);
                        // data_out no formato dd/mm/aaaa
                        if (data_out.length() == 10 && mes_ano.length() == 7 && data_out.substr(3,7) == mes_ano) {
                            estadias_mes.push_back(linha);
                            try { total += std::stod(valor_final_str); } catch (...) {}
                        }
                    }
                    festadias.close();
                    std::cout << "\n--- Faturamento de " << mes_ano << " ---\n";
                    for (const auto& est : estadias_mes) {
                        std::cout << est << "\n";
                    }
                    std::cout << "Total: R$ " << total << "\n";
                    // Salvar em faturamentomensal.txt
                    std::ofstream ffat("faturamentomensal.txt", std::ios::out | std::ios::binary);
                    const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
                    ffat.write(reinterpret_cast<const char*>(bom), sizeof(bom));
                    ffat << "Faturamento referente a " << mes_ano << "\n";
                    for (const auto& est : estadias_mes) {
                        ffat << est << "\n";
                    }
                    ffat << "Total: R$ " << total << "\n";
                    ffat.close();
                }
                break;
            case 0:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção inválida!\n";
        }
        std::cout << "\nPressione ENTER para continuar...";
        std::cin.get();
    } while (opcao != 0);
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    Usuario* usuario = nullptr;
    do {
        usuario = login();
    } while (!usuario);
    menu_principal(usuario);
    SistemaHotel::getInstance()->salvar_dados();
    return 0;
}
