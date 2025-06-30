#include "gerenciadorQuartos.h"
#include <vector>
#include <string>
#include <iostream>

//Função para adicionar um novo quarto ao vetor "quartos"
void GerenciadorQuartos::adicionar_quarto(const Quarto& novo_quarto) {

   quartos.push_back(novo_quarto);

}

//Função para listar todos os quartos do vetor "quartos" e seus respectivos atributos
void GerenciadorQuartos::listar_quartos() const {

   std::cout << "--- Lista de Quartos ---\n";

   for(size_t i = 0; i < quartos.size(); i++) {

      std::cout << "Número: " << quartos[i].get_numero() << "\n";
      std::cout << "Tipo: " << quartos[i].get_tipo() << "\n";
      std::cout << "Preço: " << quartos[i].get_preco() << "\n\n";

   }

   std::cout << "-------------------------";
}

//Função para editar os atributos de um quarto, localizando através do número e sendo possível alterar o tipo e o valor da diária
void GerenciadorQuartos::editar_quarto(int numero) {

   for (size_t i = 0; i < quartos.size(); i++) {
      if (quartos[i].get_numero() == numero) {

         std::cout << "Novo tipo: ";
         std::string novo_tipo;
         std::cin  >> novo_tipo;
         quartos[i].set_tipo(novo_tipo);

         std::cout << "Novo preco: ";
         double novo_preco;
         std::cin  >> novo_preco;
         quartos[i].set_preco(novo_preco);

         std::cout << "Quarto " << numero << " editado com sucesso.\n";
         return;
         
      }
   }    
      
   std::cout << "Quarto " << numero << " Não encontrado.\n";
}

//Função para remover um quarto de número X do vetor "quartos"
void GerenciadorQuartos::remover_quarto(int numero) {

   for (size_t i = 0; i < quartos.size(); i++) {

      if (quartos[i].get_numero() == numero) {
         quartos.erase(quartos.begin() + i);
         std::cout << "Quarto " << numero << " removido com sucesso!\n";
         return;
      }
   }
   std::cout << "Quarto " << numero << " não encontrado";
}

//Função para listar os quartos por tipo de quarto, criando um novo vetor chamado lista_filtrada e adicionando nesse vetor os quartos do tipo buscado
//e depois retorna a lista com o filtragem aplicada
std::vector<Quarto> GerenciadorQuartos::buscar_por_tipo(const std::string& tipo) const{

   std::vector<Quarto> lista_filtrada;

   for (size_t i = 0; i < quartos.size(); ++i) {
      if (quartos[i].get_tipo() == tipo) {
        lista_filtrada.push_back(quartos[i]);
    }
}

return lista_filtrada;


}

//Função para realizar o checkin de um hóspede em um quarto alterando o estado do quarto para ocupado, verifica também se o quarto já foi feito checkin
void GerenciadorQuartos::checkin(int numero_quarto) {

   for (size_t i = 0; i < quartos.size(); i++) {
      if ( quartos[i].get_numero() == numero_quarto) {
         if (quartos[i].get_ocupado() == true) {
            std::cout << "Quarto " << numero_quarto << " já está ocupado.\n";
            return;
         }
         else {
         quartos[i].set_ocupado(true);
         std::cout << "Checkin do quarto " << numero_quarto << " realizado com sucesso!\n";
         return;
         }
      }
   }
   std::cout << "Quarto " << numero_quarto << " não encontrado.\n";
}

//Função para realizar o checkout de um hóspede de um quarto alterando o estado do quarto para livre, verifica também se o quarto já foi feito checkout 
void GerenciadorQuartos::checkout(int numero_quarto) {

   for(size_t i = 0; i < quartos.size(); i++) {
      if ( quartos[i].get_numero() == numero_quarto) {
         if (quartos[i].get_ocupado() == true) {
            quartos[i].set_ocupado(false);
            std::cout << "Checkout do quarto " << numero_quarto << " realizado com sucesso!\n";
            return;
         }
         else {
            std::cout << "Checkout do quarto " << numero_quarto << " já foi realizado e o quarto está livre!\n";
            return;
         }
      }
   }
   std::cout << "Quarto " << numero_quarto << " não encontrado.\n";
}