/*
* @author: João Pedro Neigri Heleno, heleno@alunos.utfpr.edu.br
* @Github: @JoaoNeigri
* @file: arvoreBinaria.c
* Description: Programa que implementa uma arvore binária
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*------------------------------------------------------------------------------
*---------------------------------Operações-------------------------------------
* Inicialização da arvore
* Verificar se a arvore esta vazia
* Inserção na arvore
* Remoção de nós
* Destruição da arvores
* Impressão (pré-ordem, pós-ordem, em ordem)
* Pesquisa de nós
*///----------------------------------------------------------------------------

typedef struct NoArvore *ptrNo;

typedef struct NoArvore{
  int chave;
  ptrNo noDireita;
  ptrNo noEsquerda;
}NoArvore;

//------------------------------------------------------------------------------
// Inicia a arvore
void iniciaArvore(ptrNo * no){
  (*no) = NULL;
}//iniciaArvore

//------------------------------------------------------------------------------
// Verifica se a arvore esta vazia
bool verificaVazia (ptrNo * no){
  return ((*no) == NULL);
}//verificaVazia

//------------------------------------------------------------------------------
// Insere nós na arvore
bool insereArvore(ptrNo * no, int x){

  // Verica o nó para fazer a inserção (Ponto de Inserção)
  if((*no) == NULL){
    // Aloca o nó
    (*no) = malloc(sizeof(NoArvore));
    // Insere o valor ao nó
    (*no)->chave = x;
    // Inicializa os nós da sequência
    (*no)->noDireita = (*no)->noEsquerda = NULL;
    return (true);
  }

  // Verifica se o x não repete dentro da arvore
  if((*no)->chave == x){
    printf("Warning: O valor %i ja existe na arvore!\n\n", x);
    return (false);
  }


  // Faz a chamada recursiva para o nó da direita
  if(x > ((*no)->chave)){
    return (insereArvore(&(*no)->noDireita, x));
  }// Faz a chamada recursiva para o nó da esquera
  else{
    return (insereArvore(&(*no)->noEsquerda, x));
  }
}//insereArvore

//------------------------------------------------------------------------------
// Busca ordem crescrente
void ordemCresc(ptrNo * no){
  if((*no) == NULL) return;

  ordemCresc(&(*no)->noEsquerda);
  printf("%i ", (*no)->chave);
  ordemCresc(&(*no)->noDireita);
}//preordem

//------------------------------------------------------------------------------
// Busca pré-ordem
void preOrdem(ptrNo * no){
  if((*no) == NULL) return;

  printf("%i ", (*no)->chave);
  preOrdem(&(*no)->noEsquerda);
  preOrdem(&(*no)->noDireita);
}//preordem

//------------------------------------------------------------------------------
// Busca pós-ordem
void posOrdem(ptrNo * no){
  if((*no) == NULL) return;

  posOrdem(&(*no)->noEsquerda);
  posOrdem(&(*no)->noDireita);
  printf("%i ", (*no)->chave);
}//preordem

//------------------------------------------------------------------------------
// Busca numero
bool buscaNumero(ptrNo * no, int x){
  if((*no) == NULL) return false;// Caso base

  if(x == (*no)->chave) return true;// Caso base

  if(x > (*no)->chave){// Casos recursivo
    return buscaNumero(&(*no)->noDireita, x);
  }else{
    return buscaNumero(&(*no)->noEsquerda, x);
  }
}//buscaNumero

//------------------------------------------------------------------------------
// Busca o maior elemento da subarvore da esquerda
ptrNo maiorElementoEsquerda(ptrNo * no){
  ptrNo maiorNo;

  if((*no)->noDireita == NULL){
    maiorNo = (*no);
    (*no) = (*no)->noEsquerda;
    return maiorNo;
  }else{
    return (maiorElementoEsquerda(&(*no)->noDireita));
  }
}//maiorElementoEsquerda

//------------------------------------------------------------------------------
// Remove elemento da arvore
bool removeArvore (ptrNo * no, int x){

  // Caso base
  if((*no) == NULL) return false;

  if((*no)->chave == x){

    ptrNo aux = (*no);

    //c1: Caso o nó seja uma folha ou tenha nó a direita e na esquerda seja NULL
    if(((*no)->noDireita == NULL && (*no)->noEsquerda == NULL) || ((*no)->noDireita != NULL && (*no)->noEsquerda == NULL)){
      (*no) = (*no)->noDireita;
    }else if((*no)->noDireita == NULL && (*no)->noEsquerda != NULL){//c2: Caso tenha nó a esquerda e na direita seja NULL
      (*no) = (*no)->noEsquerda;
    }else{//c3: Caso tenha nó em ambas subarvores
      // Buscar o maior elemento da subarvore da esquerda
      aux = maiorElementoEsquerda(&(*no)->noEsquerda);
      // Substituir as chaves entre o nó a ser removido e o maior elemento da subarvore da esquerda
      (*no)->chave = aux->chave;
    }

    free(aux);
    return true;
  }

  if(x > (*no)->chave){// Chamadas recursivas
    return (removeArvore(&(*no)->noDireita, x));
  }else{
    return (removeArvore(&(*no)->noEsquerda, x));
  }
}//removeArvore

//------------------------------------------------------------------------------
// Destroi arvores
void destroiArvore(ptrNo * no){
  if((*no) != NULL) {
    destroiArvore(&(*no)->noEsquerda);
    destroiArvore(&(*no)->noDireita);
    free(*no);
    (*no) = NULL;
  }
}//destroiArvore

//------------------------------------------------------------------------------
// Imprime o menu de opções
void imprimeMenu(){

  printf("___________________________________________\n");
  printf("|----------- 1. Insere Valores -----------|\n");
  printf("|----------- 2. Remove Valores -----------|\n");
  printf("|------- 3. Verifica se Está Vazia -------|\n");
  printf("|----------- 4. Pesquisa Valor -----------|\n");
  printf("|---- 5. Imprime em ordem crescrente -----|\n");
  printf("|-------- 6. Imprime em pré-ordem --------|\n");
  printf("|-------- 7. Imprime em pós-ordem --------|\n");
  printf("|---------- 8. Destroi a arvore ----------|\n");
  printf("|----------- 9. Imprime o Menu -----------|\n");
  printf("|--------- 0. Sair do Programa -----------|\n");
  printf("\n");

}//imprimeMenu


int main(){

  ptrNo arvore;
  int opcao, x;

  iniciaArvore(&arvore);

  imprimeMenu();

  do{
    printf("Insira sua opção: ");
    scanf("%i", &opcao);

    switch(opcao){
      case 1://Inserção
        printf("Digite um elemento para ser inserido na arvore: ");
        scanf("%d", &x);
        insereArvore(&arvore, x);
      break;

      case 2://Remoção
        printf("Digite um elemento para ser removido da arvore: ");
        scanf("%d", &x);
        if(removeArvore(&arvore, x)){
          printf("O elemento %d, foi removido\n",x);
        }else{
          printf("O elemento %d, não foi removido\n",x);
        }

      break;

      case 3://Verifica se está vazia
        if(verificaVazia(&arvore)){
          printf("Esta vazia!\n");
        }else{
          printf("Não esta vazia!\n");
        }
      break;

      case 4://Pesquisa valor
        printf("Digite um elemento para ser pesquisado na arvore: ");
        scanf("%d", &x);
        if(buscaNumero(&arvore, x)){
          printf("Foi encontrado!\n");
        }else{
          printf("Não foi encontrado\n");
        }
      break;

      case 5://Ordem crescrente
        printf("Exibição em ordem\n{ ");
        ordemCresc(&arvore);
        printf("}\n");
      break;

      case 6://Pré-ordem
        printf("Exibição em pré-ordem\n{ ");
        preOrdem(&arvore);
        printf("}\n");
      break;

      case 7://Pós-ordem
        printf("Exibição em pós-ordem\n{ ");
        posOrdem(&arvore);
        printf("}\n");
      break;

      case 8://Destroi arvore
        destroiArvore(&arvore);
      break;

      case 9:
        imprimeMenu();
      break;

      case 0:
        printf("Fechando Programa\n\n");
      break;

      default:
        printf("Opção Inválida!\n");
      break;
    }
    printf("\n");
  }while(opcao != 0);

  return 0;
}
