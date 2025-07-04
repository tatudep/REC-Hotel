#ifndef USUARIO_H
#define USUARIO_H
#include <string>

class Usuario {
protected:
    std::string nome;
    std::string login;
    std::string senha;
public:
    Usuario(const std::string& nome, const std::string& login, const std::string& senha);
    virtual ~Usuario() = default;
    std::string get_nome() const;
    std::string get_login() const;
    std::string get_senha() const;
    void set_nome(const std::string& nome);
    void set_login(const std::string& login);
    void set_senha(const std::string& senha);
    virtual std::string get_tipo() const = 0; // método polimórfico puro
};

#endif // USUARIO_H
