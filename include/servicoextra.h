#ifndef SERVICOEXTRA_H
#define SERVICOEXTRA_H
#include <string>

// Classe que representa um serviço extra oferecido pelo hotel (ex: lavanderia, café da manhã)
class ServicoExtra {
private:
    std::string nome; // Nome do serviço
    double preco; // Preço do serviço
    std::string descricao; // Descrição detalhada do serviço
public:
    // Construtor da classe ServicoExtra
    ServicoExtra(const std::string& nome, double preco, const std::string& descricao = "");
    // Métodos de acesso aos atributos
    std::string get_nome() const; // Retorna o nome do serviço
    double get_preco() const; // Retorna o preço do serviço
    std::string get_descricao() const; // Retorna a descrição do serviço
    // Métodos para modificar os atributos
    void set_nome(const std::string& nome);
    void set_preco(double preco);
    void set_descricao(const std::string& descricao);
};

#endif // SERVICOEXTRA_H
