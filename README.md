# REC-Hotel

**REC-Hotel** é um sistema de gerenciamento para hotéis, desenvolvido em C++. Ele permite o controle de reservas, hóspedes, quartos e usuários. O sistema utiliza arquivos `.txt` como base de dados e oferece diferentes níveis de acesso conforme o usuário.

---

## 📁 Estrutura do Projeto

- `src/` — Contém o código-fonte do programa (`.cpp`).
- `include/` — Contém os arquivos de cabeçalho (`.h`).
- Arquivos `.txt` — Base de dados com usuários, hóspedes, reservas etc.

---

## ✅ Pré-requisitos

- Compilador C++ (recomendado: `g++`)
- Sistema operacional:
  - Windows, Linux ou macOS
- Terminal (cmd, PowerShell, bash, etc.)

---

## 🔧 Compilação

### No Windows

Abra o terminal, navegue até a pasta `src` e execute:

```bash
g++ *.cpp -I../include -o rec_hotel.exe
```

### No Linux/macOS

```bash
g++ *.cpp -I../include -o rec_hotel
```


⸻

## ▶️ Execução

### No Windows

```bash
.\rec_hotel.exe
```

### No Linux/macOS

```bash
./rec_hotel
```


⸻

## 🔐 Login

Ao iniciar o programa, você será solicitado a inserir um usuário e senha. Essas informações estão armazenadas no arquivo usuarios.txt.
	•	Usuário administrador (com acesso completo):
	•	Login: admin
	•	Senha: 1234

⸻

## 🧭 Navegação

Após o login, será exibido um menu com as funcionalidades do sistema. A navegação é feita por números e é bastante intuitiva.

⸻

## 🗂️ Base de dados

Os dados são armazenados em arquivos .txt no diretório do projeto. Evite modificá-los manualmente para não corromper o sistema.
