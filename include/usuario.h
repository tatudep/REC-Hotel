#ifndef USUARIO_H
#define USUARIO_H
#include <string>

// Classe base para todos os tipos de usuários do sistema (administrador, recepcionista, hóspede)
class Usuario {
protected:
    std::string nome; // Nome do usuário
    std::string login; // Login de acesso
    std::string senha; // Senha de acesso
public:
    // Construtor da classe Usuario
    Usuario(const std::string& nome, const std::string& login, const std::string& senha);
    virtual ~Usuario() = default; // Destrutor virtual para permitir herança
    // Métodos de acesso aos atributos
    std::string get_nome() const; // Retorna o nome do usuário
    std::string get_login() const; // Retorna o login
    std::string get_senha() const; // Retorna a senha
    // Métodos para modificar os atributos
    void set_nome(const std::string& nome);
    void set_login(const std::string& login);
    void set_senha(const std::string& senha);
    // Método polimórfico puro para identificar o tipo de usuário
    virtual std::string get_tipo() const = 0; // método polimórfico puro
};

#endif // USUARIO_H
