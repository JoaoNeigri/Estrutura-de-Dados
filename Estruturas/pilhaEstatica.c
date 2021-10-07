#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*                          -Operações de modificação-
* 1 - Inicialização
* 2 - Inserção (push/empilha)
* 3 - Remoção (pop/desempilha)
* 4 - Pesquisa/consulta
*/

/*                          -Operações adicionais ED-
* 5 - Verificar se esta fazia
* 6 - Verificar se esta cheia
* 7 - Quantidade de elementos na estrutura
* 8 - Imprimir estrutura
*/

#define TAM 15

typedef struct{

  int array[TAM];
  int topo;

}pilhaEstatica;

/*Cabeçalho de funções---------------------------------------------------------*/

void iniciaPilha(pilhaEstatica *pilha);

bool VPilhaVazia(pilhaEstatica *pilha);

bool VPilhaCheia(pilhaEstatica *pilha);

void insercaoPilha(pilhaEstatica *pilha, int x);

int remocaoPilha(pilhaEstatica *pilha);

void imprimiPilha(pilhaEstatica *pilha);

int verificaQuantidade(pilhaEstatica *pilha);

/*----------------------------------------------------------------------------*/

int main(){

  pilhaEstatica pilha;
  int opcao, x;

  iniciaPilha(&pilha);

  do{

    printf("Insira opção: ");
    scanf("%i", &opcao);

    switch(opcao){
    case 1:
      if(VPilhaVazia(&pilha))
        printf("A pilha estática está vazia\n\n");
      else
        printf("A pilha estática não está vazia\n\n");
    break;//Verifica se a pilha esta vazia

    case 2:
      if(VPilhaCheia(&pilha))
        printf("A pilha estática está cheia\n\n");
      else
        printf("A pilha estática não está cheia\n\n");
    break;//Verifica se a pilha esta cheia

    case 3:
      printf("Insira um valor na pilha: ");
      scanf("%i", &x);

      insercaoPilha(&pilha, x);
      printf("\n");
    break;//Insere um valor na pilha

    case 4:
      printf("%i \n\n",remocaoPilha(&pilha));
    break;//Remove e imprimi o ultimo valor da pilha

    case 5:
      imprimiPilha(&pilha);
      printf("\n");
    break;//Imprimi pilha

    case 6:
    printf("A quantidade de elementos na pilha é %i\n\n", verificaQuantidade(&pilha));
    break;//Verifica a quantidade de elementos na pilha

    }//switch

  }while(opcao != -1);

  printf("\n\n");

  return 0;
}//main

/*----------------------------------------------------------------------------*/

void iniciaPilha(pilhaEstatica *pilha){
  pilha->topo = 0;
}// Método de Inicialização de pilha

/*----------------------------------------------------------------------------*/

bool VPilhaVazia(pilhaEstatica *pilha){
  return (pilha->topo == 0);
}// Função que retorna se a pilha esta vazia

/*----------------------------------------------------------------------------*/

bool VPilhaCheia(pilhaEstatica *pilha){
  return (pilha->topo == TAM);
}// Função que retorna se a pilha esta cheia

/*----------------------------------------------------------------------------*/

void insercaoPilha(pilhaEstatica *pilha, int x){

  if(pilha->topo < TAM){
    pilha->array[pilha->topo] = x;
    pilha->topo++;
  }else{
    printf("Warning - A pilha está cheia!\n\n");
  }
}// Função que insere valores na pilha

/*----------------------------------------------------------------------------*/

int remocaoPilha(pilhaEstatica *pilha){

  int x = 999;

  if(pilha->topo > 0){
    x = pilha-> array[pilha->topo-1];
    pilha->topo--;
  }else{
    printf("Warning - Não existe elementos para serem removidos");
  }
  return x;
}// Função quee remove valores da pilhaEstatica

/*----------------------------------------------------------------------------*/

void imprimiPilha(pilhaEstatica *pilha){
  for(int i = pilha->topo-1; i >= 0; i--){
    printf("\nPilha [%i] = %i\n", i+1, pilha->array[i]);
  }
}//Imprimi os valores armazenados na pilha

/*----------------------------------------------------------------------------*/

int verificaQuantidade(pilhaEstatica *pilha){
  return pilha->topo;
}//Verifica a quantidade de elementos na pilha

/*----------------------------------------------------------------------------*/
