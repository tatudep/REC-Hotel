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

// Classe principal que gerencia todas as operações do hotel
class SistemaHotel {
private:
    static SistemaHotel* instancia; // Instância única (Singleton)
    std::vector<Usuario*> usuarios; // Lista de usuários cadastrados
    std::vector<Quarto> quartos; // Lista de quartos disponíveis
    std::vector<Reserva> reservas; // Lista de reservas realizadas
    std::vector<ServicoExtra> servicos; // Lista de serviços extras disponíveis
    SistemaHotel(); // Construtor privado para Singleton
public:
    // Retorna a instância única do sistema
    static SistemaHotel* getInstance();
    ~SistemaHotel(); // Destrutor
    // Métodos CRUD básicos para cada entidade
    void adicionar_usuario(Usuario* usuario); // Adiciona um novo usuário
    void listar_usuarios() const; // Lista todos os usuários
    void adicionar_quarto(const Quarto& quarto); // Adiciona um novo quarto
    void listar_quartos() const; // Lista todos os quartos
    void adicionar_reserva(const Reserva& reserva); // Adiciona uma nova reserva
    void listar_reservas() const; // Lista todas as reservas
    void adicionar_servico(const ServicoExtra& servico); // Adiciona um novo serviço extra
    void listar_servicos() const; // Lista todos os serviços extras
    void excluir_usuario(size_t idx); // Remove usuário pelo índice
    void excluir_quarto(size_t idx); // Remove quarto pelo índice
    void excluir_reserva(size_t idx); // Remove reserva pelo índice
    void excluir_servico(size_t idx); // Remove serviço extra pelo índice
    void editar_usuario(size_t idx, const std::string& nome, const std::string& login, const std::string& senha); // Edita dados do usuário
    void editar_quarto(size_t idx, int numero, const std::string& tipo, double preco); // Edita dados do quarto
    void editar_reserva(size_t idx, Hospede* hospede, Quarto* quarto, const std::string& data_in, const std::string& data_out); // Edita dados da reserva
    void editar_servico(size_t idx, const std::string& nome, double preco, const std::string& descricao); // Edita dados do serviço extra
    void finalizar_estadia(size_t idx, bool usou_servicos, double valor_final); // Finaliza estadia de um hóspede
    // Persistência
    void salvar_dados();
    void carregar_dados();
    // Getters para integração
    std::vector<Usuario*>& getUsuarios();
    std::vector<Quarto>& getQuartos();
    std::vector<Reserva>& getReservas();
    std::vector<ServicoExtra>& getServicos();
};

#endif // SISTEMAHOTEL_H
