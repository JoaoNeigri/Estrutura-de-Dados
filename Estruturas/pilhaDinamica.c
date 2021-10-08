#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*                          -Operações de modificação-
* 1 - Inicialização
* 2 - Inserção (push/empilha)
* 3 - Remoção (pop/desempilha)
* 4 - Pesquisa/consulta
* 5 - Destruir dado
*/

/*                          -Operações adicionais ED-
* 6 - Verificar se esta vazia
* 7 - Quantidade de elementos na estrutura
* 8 - Imprimir estrutura
*/

typedef struct NoPilha* ptrNoPilha;

typedef struct NoPilha{
  int valor;
  ptrNoPilha proximo;
}NoPilha;

typedef struct{
  ptrNoPilha topo;
  int qtde;
}pilhaDinamica;

/*----------------------------------------------------------------------------*/

//Inicia pilha dinamica
void inicializaPilha(pilhaDinamica *p){
  p->topo = NULL;
  p->qtde = 0;
}

/*----------------------------------------------------------------------------*/

// Verifica se a pilha está vazia;
bool verificaPilha(pilhaDinamica *p){
  return (p->topo == NULL);
}

/*----------------------------------------------------------------------------*/

// Retorna a quantidade de elementos na estrutura
int quantEstrutura(pilhaDinamica *p){
  return p->qtde;
}

/*----------------------------------------------------------------------------*/

// Empilha um valor na pilha dinâmica
void pushPilha(pilhaDinamica *p, int x){

  // Cria um nó
  ptrNoPilha no;
  no = malloc(sizeof(NoPilha));
  // Elemento do nó recebe um valor
  no->valor = x;
  // Proximo aponta pro nó antigo
  no->proximo = p->topo;
  // Topo aponta pro nó
  p->topo = no;
  // Incrementa quantidade de elementos
  p->qtde++;
}

/*----------------------------------------------------------------------------*/

// Desempilha valores da pilha dinâmica
int popPilha(pilhaDinamica *p){

  int x = -9999;

  if(!verificaPilha(p)){
    //Cria ponteiro auxiliar
    ptrNoPilha aux;
    // Auxiliar aponta pro Topo
    aux = p->topo;
    // Armazenar o valor do nó em uma variável de retorno
    x = aux->valor;
    // Topo aponta para o proximo nó do nó atual
    p->topo = p->topo->proximo;
    // Libera memória
    free(aux);
    // Decrementa total de elementos da pilhaDinamica
    p->qtde--;
    // retorna o valor do nó antigo
  }else{
    // Retornar Warning
    printf("Warning - Não existe mais nós para ser removido!\n");
  }


  return x;

}

/*----------------------------------------------------------------------------*/

// Pesquisa o valor do nó que o topo aponta
int pesquisaTopo(pilhaDinamica *p){

  // Criar variavel para armazenar o valor do nó do Topo
  int x = -9999;

  // Verifica se a pilha tem nós
  if(!verificaPilha(p)){
    // Armazenar valor do nó
    x = p->topo->valor;
  }else{
    // Exibir Warninig
    printf("Warning - Não existem nós para verificar valor! ");
  }
  return x;
}

/*----------------------------------------------------------------------------*/

// Destroi pilha
void destroiPilha(pilhaDinamica *p){
  // Verifica se há nós para Destruir
  while(!verificaPilha(p)){
    // Chama função desempilha para destruir nó
    popPilha(p);
  }
  printf("Pilha destruida!\n\n");
}

/*----------------------------------------------------------------------------*/

// Imprimi a pilha dinâmica
void imprimiPilha(pilhaDinamica *p){

  ptrNoPilha ptr;

  printf("[ ");
  for(ptr = p->topo; ptr != NULL; ptr = ptr->proximo){
    printf("%i ", ptr->valor);
  }
  printf("]\n\n");
}

/*----------------------------------------------------------------------------*/

// Exibe o menu
void exibeMenu(){
  printf("|---------- Menu - Pilha Dinâmica ---------|\n");
  printf("|----------- 1 - Empilha Valor ------------|\n");
  printf("|--------- 2 - Desempilha Valor -----------|\n");
  printf("|-------- 3 - Verificar Quantos Nós -------|\n");
  printf("|-------- 4 - Verificar Nó do Topo --------|\n");
  printf("|------------ 5 - Destroi Pilha -----------|\n");
  printf("|--- 6 - Verifica se a Pilha esta Vazia ---|\n");
  printf("|------------ 7 - Imprime Pilha------------|\n");
  printf("|------------- 8 - Limpar tela ------------|\n");
  printf("|------------- 9 - Menu do Jogo -----------|\n");
  printf("|------------- 0 - Sair do Jogo -----------|\n\n");
}

/*----------------------------------------------------------------------------*/


int main(){

  pilhaDinamica p;
  int opcao, x, pop, valorTopo, qElementos;

  inicializaPilha(&p);

  exibeMenu();

  do{
    printf("\nInsira sua opção: ");
    scanf("%i", &opcao);

    switch(opcao){

      case 1:
        printf("Insira um valor para ser empilhado: ");
        scanf("%i", &x);
        pushPilha(&p, x);
      break;// Empilha dados na pilha dinâmica

      case 2:
        pop = popPilha(&p);
        printf("%i \n\n", pop);
      break;// Desempilha dados na pilha dinâmica

      case 3:
        qElementos = quantEstrutura(&p);
        printf("%i\n\n", qElementos);
      break; // Verifica quantos elementos existem na pilha

      case 4:
        valorTopo = pesquisaTopo(&p);
        printf("O valor do topo é %i\n\n", valorTopo);
      break;// Verifica o valor do nó que o topo aponta

      case 5:
        destroiPilha(&p);
      break;// Destroi pilha

      case 6:
        if(!verificaPilha(&p)){
          printf("A pilha não está vazia!\n\n");
        }else{
          printf("A pilha está vazia!\n\n");
        }
      break;// Verifica se a pilha está vazia

      case 7:
        imprimiPilha(&p);
      break;// Imprimi a pilha

      case 8:
        system("clear");
      break;// Limpa a tela

      case 9:
        exibeMenu();
      break;// Exibe o menu

      case 0:
        printf("Saindo!\n\n");
      break;// Sai do programa

      default:
        printf("Opção Inválido!\nPor favor insira a opção novamente\n\n");
      break;// Opção Inválida

    }
  }while(opcao != 0);

return 0;
}
