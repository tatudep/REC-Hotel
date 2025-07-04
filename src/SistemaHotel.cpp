#include "SistemaHotel.h"
#include <iostream>
#include <fstream>

SistemaHotel* SistemaHotel::instancia = nullptr;

SistemaHotel::SistemaHotel() {
    carregar_dados();
}

SistemaHotel::~SistemaHotel() {
    salvar_dados();
}

SistemaHotel* SistemaHotel::getInstance() {
    if (!instancia) {
        instancia = new SistemaHotel();
    }
    return instancia;
}

void SistemaHotel::adicionar_usuario(Usuario* usuario) {
    usuarios.push_back(usuario);
}

void SistemaHotel::listar_usuarios() const {
    std::cout << "--- Usuários ---\n";
    for (const auto& u : usuarios) {
        std::cout << u->get_nome() << " (" << u->get_tipo() << ")\n";
    }
}

void SistemaHotel::adicionar_quarto(const Quarto& quarto) {
    quartos.push_back(quarto);
}

void SistemaHotel::listar_quartos() const {
    std::cout << "--- Quartos ---\n";
    for (const auto& q : quartos) {
        std::cout << "Número: " << q.get_numero() << ", Tipo: " << q.get_tipo() << ", Preço: " << q.get_preco() << "\n";
    }
}

void SistemaHotel::adicionar_reserva(const Reserva& reserva) {
    reservas.push_back(reserva);
}

void SistemaHotel::listar_reservas() const {
    std::cout << "--- Reservas ---\n";
    for (const auto& r : reservas) {
        std::cout << "Hóspede: " << r.get_hospede()->get_nome() << ", Quarto: " << r.get_quarto()->get_numero() << ", Check-in: " << r.get_data_checkin() << ", Check-out: " << r.get_data_checkout() << "\n";
    }
}

void SistemaHotel::adicionar_servico(const ServicoExtra& servico) {
    servicos.push_back(servico);
}

void SistemaHotel::listar_servicos() const {
    std::cout << "--- Serviços Extras ---\n";
    for (const auto& s : servicos) {
        std::cout << s.get_nome() << " - R$ " << s.get_preco() << ": " << s.get_descricao() << "\n";
    }
}

void SistemaHotel::salvar_dados() {
    // Usuários
    std::ofstream fusers("usuarios.txt", std::ios::out | std::ios::binary);
    const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    fusers.write(reinterpret_cast<const char*>(bom), sizeof(bom));
    for (const auto& u : usuarios) {
        fusers << u->get_tipo() << ';' << u->get_nome() << ';' << u->get_login() << ';' << u->get_senha() << '\n';
    }
    fusers.close();
    // Quartos
    std::ofstream fquartos("quartos.txt", std::ios::out | std::ios::binary);
    fquartos.write(reinterpret_cast<const char*>(bom), sizeof(bom));
    for (const auto& q : quartos) {
        fquartos << q.get_numero() << ';' << q.get_tipo() << ';' << q.get_preco() << '\n';
    }
    fquartos.close();
    // Reservas
    std::ofstream freservas("reservas.txt", std::ios::out | std::ios::binary);
    freservas.write(reinterpret_cast<const char*>(bom), sizeof(bom));
    for (const auto& r : reservas) {
        freservas << r.get_hospede()->get_nome() << ';' << r.get_quarto()->get_numero() << ';' << r.get_data_checkin() << ';' << r.get_data_checkout() << '\n';
    }
    freservas.close();
    // Serviços extras
    std::ofstream fserv("servicos.txt", std::ios::out | std::ios::binary);
    fserv.write(reinterpret_cast<const char*>(bom), sizeof(bom));
    for (const auto& s : servicos) {
        fserv << s.get_nome() << ';' << s.get_preco() << ';' << s.get_descricao() << '\n';
    }
    fserv.close();
}

void SistemaHotel::carregar_dados() {
    // Usuários
    std::ifstream fusers("usuarios.txt", std::ios::binary);
    if (fusers.is_open()) {
        std::string linha;
        bool primeira_linha = true;
        while (std::getline(fusers, linha)) {
            if (primeira_linha) {
                if (linha.size() >= 3 && (unsigned char)linha[0] == 0xEF && (unsigned char)linha[1] == 0xBB && (unsigned char)linha[2] == 0xBF) {
                    linha = linha.substr(3);
                }
                primeira_linha = false;
            }
            if (linha.empty()) continue;
            size_t p1 = linha.find(';');
            size_t p2 = linha.find(';', p1+1);
            size_t p3 = linha.find(';', p2+1);
            if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos) continue;
            std::string tipo = linha.substr(0, p1);
            std::string nome = linha.substr(p1+1, p2-p1-1);
            std::string login = linha.substr(p2+1, p3-p2-1);
            std::string senha = linha.substr(p3+1);
            Usuario* u = nullptr;
            if (tipo == "Administrador") u = new Administrador(nome, login, senha);
            else if (tipo == "Recepcionista") u = new Recepcionista(nome, login, senha);
            else if (tipo == "Hospede") u = new Hospede(nome, login, senha);
            if (u) usuarios.push_back(u);
        }
        fusers.close();
    }
    // Quartos
    std::ifstream fquartos("quartos.txt", std::ios::binary);
    if (fquartos.is_open()) {
        std::string linha;
        bool primeira_linha = true;
        while (std::getline(fquartos, linha)) {
            if (primeira_linha) {
                if (linha.size() >= 3 && (unsigned char)linha[0] == 0xEF && (unsigned char)linha[1] == 0xBB && (unsigned char)linha[2] == 0xBF) {
                    linha = linha.substr(3);
                }
                primeira_linha = false;
            }
            if (linha.empty()) continue;
            size_t p1 = linha.find(';');
            size_t p2 = linha.find(';', p1+1);
            if (p1 == std::string::npos || p2 == std::string::npos) continue;
            try {
                int numero = std::stoi(linha.substr(0, p1));
                std::string tipo = linha.substr(p1+1, p2-p1-1);
                double preco = std::stod(linha.substr(p2+1));
                quartos.push_back(Quarto(numero, tipo, preco));
            } catch (const std::exception&) { continue; }
        }
        fquartos.close();
    }
    // Reservas
    std::ifstream freservas("reservas.txt", std::ios::binary);
    if (freservas.is_open()) {
        std::string linha;
        bool primeira_linha = true;
        while (std::getline(freservas, linha)) {
            if (primeira_linha) {
                if (linha.size() >= 3 && (unsigned char)linha[0] == 0xEF && (unsigned char)linha[1] == 0xBB && (unsigned char)linha[2] == 0xBF) {
                    linha = linha.substr(3);
                }
                primeira_linha = false;
            }
            if (linha.empty()) continue;
            size_t p1 = linha.find(';');
            size_t p2 = linha.find(';', p1+1);
            size_t p3 = linha.find(';', p2+1);
            if (p1 == std::string::npos || p2 == std::string::npos || p3 == std::string::npos) continue;
            try {
                std::string nome_hospede = linha.substr(0, p1);
                int numero_quarto = std::stoi(linha.substr(p1+1, p2-p1-1));
                std::string data_in = linha.substr(p2+1, p3-p2-1);
                std::string data_out = linha.substr(p3+1);
                // Busca ponteiros
                Hospede* h = nullptr;
                for (auto* u : usuarios) {
                    h = dynamic_cast<Hospede*>(u);
                    if (h && h->get_nome() == nome_hospede) break;
                    h = nullptr;
                }
                Quarto* q = nullptr;
                for (auto& qt : quartos) {
                    if (qt.get_numero() == numero_quarto) { q = &qt; break; }
                }
                if (h && q) reservas.push_back(Reserva(h, q, data_in, data_out));
            } catch (const std::exception&) { continue; }
        }
        freservas.close();
    }
    // Serviços extras
    std::ifstream fserv("servicos.txt", std::ios::binary);
    if (fserv.is_open()) {
        std::string linha;
        bool primeira_linha = true;
        while (std::getline(fserv, linha)) {
            if (primeira_linha) {
                if (linha.size() >= 3 && (unsigned char)linha[0] == 0xEF && (unsigned char)linha[1] == 0xBB && (unsigned char)linha[2] == 0xBF) {
                    linha = linha.substr(3);
                }
                primeira_linha = false;
            }
            if (linha.empty()) continue;
            size_t p1 = linha.find(';');
            size_t p2 = linha.find(';', p1+1);
            if (p1 == std::string::npos || p2 == std::string::npos) continue;
            try {
                std::string nome = linha.substr(0, p1);
                double preco = std::stod(linha.substr(p1+1, p2-p1-1));
                std::string desc = linha.substr(p2+1);
                servicos.push_back(ServicoExtra(nome, preco, desc));
            } catch (const std::exception&) { continue; }
        }
        fserv.close();
    }
}

void SistemaHotel::excluir_usuario(size_t idx) {
    if (idx < usuarios.size()) {
        delete usuarios[idx];
        usuarios.erase(usuarios.begin() + idx);
    }
}

void SistemaHotel::excluir_quarto(size_t idx) {
    if (idx < quartos.size()) {
        quartos.erase(quartos.begin() + idx);
    }
}

void SistemaHotel::excluir_reserva(size_t idx) {
    if (idx < reservas.size()) {
        reservas.erase(reservas.begin() + idx);
    }
}

void SistemaHotel::excluir_servico(size_t idx) {
    if (idx < servicos.size()) {
        servicos.erase(servicos.begin() + idx);
    }
}

void SistemaHotel::editar_usuario(size_t idx, const std::string& nome, const std::string& login, const std::string& senha) {
    if (idx < usuarios.size()) {
        usuarios[idx]->set_nome(nome);
        usuarios[idx]->set_login(login);
        usuarios[idx]->set_senha(senha);
    }
}

void SistemaHotel::editar_quarto(size_t idx, int numero, const std::string& tipo, double preco) {
    if (idx < quartos.size()) {
        quartos[idx].set_numero(numero);
        quartos[idx].set_tipo(tipo);
        quartos[idx].set_preco(preco);
    }
}

void SistemaHotel::editar_reserva(size_t idx, Hospede* hospede, Quarto* quarto, const std::string& data_in, const std::string& data_out) {
    if (idx < reservas.size()) {
        reservas[idx] = Reserva(hospede, quarto, data_in, data_out);
    }
}

void SistemaHotel::editar_servico(size_t idx, const std::string& nome, double preco, const std::string& descricao) {
    if (idx < servicos.size()) {
        servicos[idx].set_nome(nome);
        servicos[idx].set_preco(preco);
        servicos[idx].set_descricao(descricao);
    }
}

void SistemaHotel::finalizar_estadia(size_t idx, bool usou_servicos, double valor_final) {
    if (idx >= reservas.size()) return;
    // Obter dados da reserva
    Reserva& r = reservas[idx];
    std::string nome_hospede = r.get_hospede()->get_nome();
    int numero_quarto = r.get_quarto()->get_numero();
    std::string data_in = r.get_data_checkin();
    std::string data_out = r.get_data_checkout();
    // Remover do vetor
    reservas.erase(reservas.begin() + idx);
    // Atualizar reservas.txt
    std::ofstream freservas("reservas.txt", std::ios::out | std::ios::binary);
    const unsigned char bom[] = {0xEF, 0xBB, 0xBF};
    freservas.write(reinterpret_cast<const char*>(bom), sizeof(bom));
    for (const auto& res : reservas) {
        freservas << res.get_hospede()->get_nome() << ';' << res.get_quarto()->get_numero() << ';' << res.get_data_checkin() << ';' << res.get_data_checkout() << '\n';
    }
    freservas.close();
    // Registrar em estadias.txt
    std::ofstream festadias("estadias.txt", std::ios::app | std::ios::binary);
    // Adiciona BOM se o arquivo estiver vazio
    festadias.seekp(0, std::ios::end);
    if (festadias.tellp() == 0) {
        festadias.write(reinterpret_cast<const char*>(bom), sizeof(bom));
    }
    festadias << nome_hospede << ';' << numero_quarto << ';' << data_in << ';' << data_out << ';' << (usou_servicos ? "Sim" : "Não") << ';' << valor_final << '\n';
    festadias.close();
}
