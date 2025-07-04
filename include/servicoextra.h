#ifndef SERVICOEXTRA_H
#define SERVICOEXTRA_H
#include <string>

class ServicoExtra {
private:
    std::string nome;
    double preco;
    std::string descricao;
public:
    ServicoExtra(const std::string& nome, double preco, const std::string& descricao = "");
    std::string get_nome() const;
    double get_preco() const;
    std::string get_descricao() const;
    void set_nome(const std::string& nome);
    void set_preco(double preco);
    void set_descricao(const std::string& descricao);
};

#endif // SERVICOEXTRA_H
