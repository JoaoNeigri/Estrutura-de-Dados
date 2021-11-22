/*------------------------------------------------------------------------------
* @author: João Pedro Neigri Heleno
* @github: JoaoNeigri
* Lista ordenada
*///----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*------------------------------------------------------------------------------
*---------------------------------Operações-------------------------------------
* Inicialização da Lista
* Verifica se está vazia
* Inserção da lista
* Remover da lista
* Pesquisar
* Destruir
* Maximo
* Minimo
* Tamanho da Lista
*///------------------------------------------------------------------------------

typedef struct NoLista *ptrNo;

typedef struct NoLista{
  int chave;
  ptrNo proximo;
}NoLista;

typedef struct{
  ptrNo inicio;
  int qElementos;
}ListaOrdenada;

/*----------------------------------------------------------------------------*/

// Inicializa a Lista ordenada
void iniciaLista(ListaOrdenada *l){
  l->inicio = NULL;
  l->qElementos = 0;
}//iniciaLista

/*----------------------------------------------------------------------------*/

// Retorna TRUE se a lista está vazia
bool verificaVazia(ListaOrdenada *l){
  return (l->inicio == NULL);
}//verificaVazia

/*----------------------------------------------------------------------------*/

// Retorna a quantidade de elementos
int qElementos(ListaOrdenada *l){
  return (l->qElementos);
}//qElementos

/*----------------------------------------------------------------------------*/

// Insere um valor na lista ordenada
void insereLista(ListaOrdenada *l, int x){

  // Cria um novo nó
  ptrNo novoNo = malloc(sizeof(NoLista));
  // Insere valor na lista
  novoNo->chave = x;

  if(verificaVazia(l) || (x < l->inicio->chave)){

    // Inicializa o endereço do novo nó e altera o endereço do inicio
    novoNo->proximo = l->inicio;
    l->inicio = novoNo;

  }else{

    // Nó auxiliar que irá buscar a posição de inserção
    ptrNo aux;
    aux = l->inicio;

    // Busca posição de inserção
    while(aux->proximo != NULL && x > aux->proximo->chave){
      aux = aux->proximo;
    }

    // Insere valor
    novoNo->proximo = aux->proximo;
    aux->proximo = novoNo;
  }

  l->qElementos++;

}//insereLista

/*----------------------------------------------------------------------------*/

// Função que remove valores da lista ordenada
bool removeLista(ListaOrdenada *l, int x){

  // x < menor numero || lista estar Vazia
  if((x < l->inicio->chave) || verificaVazia(l)){
    printf("Warning: A lista está vazia ou número a ser retirado não exite na lista\n\n");
    return false;
  }else if(x == l->inicio->chave){// caso x seja igual ao primeiro elemento da fila

    ptrNo aux = l->inicio;
    l->inicio = l->inicio->proximo;
    l->qElementos--;

    free(aux);
    return true;

  }else{
    ptrNo percorre = l->inicio;
    ptrNo aux;

    while(percorre->proximo != NULL && x > percorre->proximo->chave){
      percorre = percorre->proximo;
    }

    if(percorre->proximo->chave == x){
      aux = percorre->proximo;
      percorre->proximo = aux->proximo;
      l->qElementos--;

      free(aux);


      return true;
    }else{
      printf("O elemento %i não existe na lista\n\n", x);
      return false;
    }
  }
}//removeLista

/*----------------------------------------------------------------------------*/

// Pesquisa se existe um número na lista Lista Ordenada
bool pesquisaLista(ListaOrdenada *l, int x){

  if(verificaVazia(l) || x < l->inicio->chave){
    printf("A lista está vazia ou o valor %i não existe na lista\n\n", x);
    return false;
  }

  if(x == l->inicio->chave){
    printf("O valor %i existe na lista\n\n", x);
    return true;
  }

  ptrNo percorre = l->inicio;


  while(percorre->proximo != NULL && x != percorre->proximo->chave){
    percorre = percorre->proximo;
  }

  if(percorre->proximo != NULL){
    printf("O valor %i existe na lista\n\n", x);
    return true;
  }

  printf("O valor %i não existe na fila", x);
  return false;

}//pesquisaLista

/*----------------------------------------------------------------------------*/

// Verifica o menor valor da lista
int verificaMinimo(ListaOrdenada *l){
  return (l->inicio->chave);
}//verificaMinimo

/*----------------------------------------------------------------------------*/

// Verifica o maior valor da lista
int verificaMaximo(ListaOrdenada *l){
  ptrNo percorre = l->inicio;

  while(percorre->proximo != NULL){
    percorre = percorre->proximo;
  }
  return (percorre->chave);
}//verificaMinimo

/*----------------------------------------------------------------------------*/

// Destroi lista ordenada
void destroiLista(ListaOrdenada *l){

  ptrNo aux;
  if(!verificaVazia(l)){

    while(l->inicio != NULL){
      aux = l->inicio;
      l->inicio = l->inicio->proximo;
      l->qElementos--;

      free(aux);
    }
  }
  printf("Lista destruida!!!\n\n");

}//destroiLista

/*----------------------------------------------------------------------------*/

// Imprime a lista ordenada
void imprimeLista(ListaOrdenada *l){
  ptrNo percorre;
  percorre = l->inicio;

  printf("\n\n[ ");
  while(percorre != NULL){
    printf("%i ", percorre->chave);
    percorre = percorre->proximo;
  }
  printf("]\n\n");

}//imprimeLista

/*----------------------------------------------------------------------------*/

// Imprime o menu de opções
void imprimeMenu(ListaOrdenada *l){

  printf("----------- 1. Insere Valores -----------\n");
  printf("----------- 2. Remove Valores -----------\n");
  printf("------ 3. Pesquisa Valor na Lista -------\n");
  printf("------- 4. Verifica se Está Vazia -------\n");
  printf("---- 5. Retorna Quantidade Elementos ----\n");
  printf("------- 6. Maior Valor da Lista ---------\n");
  printf("------- 7. Menor Valor da Lista ---------\n");
  printf("---------- 8. Destroi a Lista -----------\n");
  printf("---------- 9. Imprime o Lista -----------\n");
  printf("---------- 10. Imprime o Menu -----------\n");
  printf("--------- 0. Sair do Programa -----------\n");

}//imprimeMenu

/*----------------------------------------------------------------------------*/

int main(){

  int opcao, valor, tamanho, maximo, minimo;
  ListaOrdenada lista;
  // pesquisaLista(&lista, 95);

  iniciaLista(&lista);
  imprimeMenu(&lista);

  printf("\n\n");

  do{

    printf("Insira a opção: ");
    scanf("%i", &opcao);

    switch(opcao){

      case 1:
        printf("Digite o valor que deseja inserir na lista: ");
        scanf("%i", &valor);

        insereLista(&lista, valor);
      break; // Insere valores na lista

      case 2:
        printf("Digite o valor que deseja remover da lista: ");
        scanf("%i", &valor);

        removeLista(&lista, valor);
      break;// Remove valor da lista

      case 3:
        printf("Insira um valor para pesquisar na lista: ");
        scanf("%i", &valor);

        pesquisaLista(&lista, valor);
      break;// Pesquisa valor na lista

      case 4:
        if(verificaVazia(&lista)){
          printf("A lista está vazia\n\n");
        }else{
          printf("A lista não está vazia\n\n");
        }
      break;// Verifica se a lista está vazia

      case 5:
        tamanho = qElementos(&lista);
        printf("A lista tem %i elementos\n\n", tamanho);
      break;// Retorna quantidade de elementos que existem na lista

      case 6:
        maximo = verificaMaximo(&lista);
        printf("O maior valor da lista é %i\n\n", maximo);
      break;// Verifica valor maximo na lista

      case 7:
        minimo = verificaMinimo(&lista);
        printf("O menor valor da lista é %i\n\n", minimo);
      break;// Verifica menor valor da lista

      case 8:
        destroiLista(&lista);
      break;// Destroi a lista ordenada

      case 9:
        imprimeLista(&lista);
      break;// Imprime lista ordenada

      case 10:
        printf("\n\n");
        imprimeMenu(&lista);
      break;// Imprime o menu

      case 0:
        printf("\nSaindo!!\nAté a próxima");
      break;// Opção de saida

      default:
        printf("Opção Inválido\n\n");
      break;


    }//switch

    printf("\n\n");

  }while(opcao != 0);

  return 0;
}
