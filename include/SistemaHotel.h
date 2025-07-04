#ifndef SISTEMAHOTEL_H
#define SISTEMAHOTEL_H
#include <vector>
#include "usuario.h"
#include "administrador.h"
#include "recepcionista.h"
#include "hospede.h"
#include "Quarto.h"
#include "reserva.h"
#include "servicoextra.h"

class SistemaHotel {
private:
    static SistemaHotel* instancia;
    std::vector<Usuario*> usuarios;
    std::vector<Quarto> quartos;
    std::vector<Reserva> reservas;
    std::vector<ServicoExtra> servicos;
    SistemaHotel();
public:
    static SistemaHotel* getInstance();
    ~SistemaHotel();
    // Métodos CRUD básicos
    void adicionar_usuario(Usuario* usuario);
    void listar_usuarios() const;
    void adicionar_quarto(const Quarto& quarto);
    void listar_quartos() const;
    void adicionar_reserva(const Reserva& reserva);
    void listar_reservas() const;
    void adicionar_servico(const ServicoExtra& servico);
    void listar_servicos() const;
    void excluir_usuario(size_t idx);
    void excluir_quarto(size_t idx);
    void excluir_reserva(size_t idx);
    void excluir_servico(size_t idx);
    void editar_usuario(size_t idx, const std::string& nome, const std::string& login, const std::string& senha);
    void editar_quarto(size_t idx, int numero, const std::string& tipo, double preco);
    void editar_reserva(size_t idx, Hospede* hospede, Quarto* quarto, const std::string& data_in, const std::string& data_out);
    void editar_servico(size_t idx, const std::string& nome, double preco, const std::string& descricao);
    void finalizar_estadia(size_t idx, bool usou_servicos, double valor_final);
    // Persistência
    void salvar_dados();
    void carregar_dados();
    // Getters para integração
    std::vector<Usuario*>& getUsuarios() { return usuarios; }
    std::vector<Quarto>& getQuartos() { return quartos; }
    std::vector<Reserva>& getReservas() { return reservas; }
    std::vector<ServicoExtra>& getServicos() { return servicos; }
};

#endif // SISTEMAHOTEL_H
