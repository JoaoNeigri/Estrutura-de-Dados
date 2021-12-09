/*--------------------------------------------------------------------------*//*
* @author: João Pedro Neigri Heleno, heleno@alunos.utfpr.edu.br
* @Github: @JoaoNeigri
* @file: arvoreAVL.c
* Description: Programa que implementa uma arvore binária AVL
*//*--------------------------------------------------------------------------*/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdbool.h>

/*----------------------------------------------------------------------------*/
// Declaração da estrutura de uma arvore AVL

typedef struct arvoreAVL *PtrNoAVL;

typedef struct arvoreAVL{
  int chave;
  PtrNoAVL noDireita;
  PtrNoAVL noEsquerda;
  int altura;
}arvoreAVL;

/*----------------------------------------------------------------------------*/
// Inicialização da arvore AVL
void iniciaArvore(PtrNoAVL *no){
  (*no) = NULL;
}//iniciaArvore

/*----------------------------------------------------------------------------*/
// Verifica se a arvore AVL está vazia
bool verificaVazia(PtrNoAVL *no){
  return ((*no) == NULL);
}//verificaVazia

/*----------------------------------------------------------------------------*/
// Verifica as alturas dos nós
int verificaAltura(PtrNoAVL no){
  if(no == NULL){
    return 0;
  }else{
    return (no->altura);
    printf("altura: %i\n\t", no->altura);
  }
}//verificaAltura

/*----------------------------------------------------------------------------*/
// Atualiza a altura das listas
int atualizaAltura(PtrNoAVL esquerda, PtrNoAVL direita){
  int ae = verificaAltura(esquerda);
  int ad = verificaAltura(direita);

  if(ae > ad){
    return(ae + 1);
  }else{
    return(ad + 1);
  }
}//atualizaAltura

/*----------------------------------------------------------------------------*/
// Rotação simples a direita
void rotacaoSimplesDireita(PtrNoAVL *no){

  // Realização da rotação
  PtrNoAVL u = (*no)->noEsquerda;
  (*no)->noEsquerda = u->noDireita;
  u->noDireita = (*no);

  // Atualiza altura
  (*no)->altura = atualizaAltura((*no)->noEsquerda, (*no)->noDireita);
  u->altura = atualizaAltura(u->noEsquerda, u->noDireita);

  // Atualizando referência
  (*no) = u;
}//rotacaoSimplesDireita

/*----------------------------------------------------------------------------*/
// Rotação dupla a direita
void rotacaoDuplaDireita(PtrNoAVL *no){

  // Realização da rotação
  PtrNoAVL u = (*no);
  PtrNoAVL p = u->noEsquerda;
  PtrNoAVL q = p->noDireita;

  u->noEsquerda = q->noDireita;
  p->noDireita = q->noEsquerda;

  q->noDireita = u;
  q->noEsquerda = p;

  // Atualiza altura
  u->altura = atualizaAltura(u->noEsquerda, u->noDireita);
  p->altura = atualizaAltura(p->noEsquerda, p->noDireita);
  q->altura = atualizaAltura(q->noEsquerda, q->noDireita);

  // Atualizando referência
  (*no) = q;
}//rotacaoDuplaDireita

/*----------------------------------------------------------------------------*/
// Rotação simples a esquerda
void rotacaoSimplesEsquerda(PtrNoAVL *no){

  // Realização da rotação
  PtrNoAVL u = (*no)->noDireita;
  (*no)->noDireita = u->noEsquerda;
  u->noEsquerda = (*no);

  // Atualiza altura
  (*no)->altura = atualizaAltura((*no)->noEsquerda, (*no)->noDireita);
  u->altura = atualizaAltura(u->noEsquerda, u->noDireita);

  // Atualizando referência
  (*no) = u;
}//rotacaoSimplesEsquerda

/*----------------------------------------------------------------------------*/
// Rotação simples a esquerda
void rotacaoDuplaEsquerda(PtrNoAVL *no){

  // Realização da rotação
  PtrNoAVL u = (*no);
  PtrNoAVL p = u->noDireita;
  PtrNoAVL q = p->noEsquerda;

  p->noEsquerda = q->noDireita;
  u->noDireita = q->noEsquerda;

  q->noEsquerda = u;
  q->noDireita = p;

  // Atualiza altura
  u->altura = atualizaAltura(u->noEsquerda, u->noDireita);
  p->altura = atualizaAltura(p->noEsquerda, p->noDireita);
  q->altura = atualizaAltura(q->noEsquerda, q->noDireita);

  // Atualizando referência
  (*no) = q;
}//rotacaoDuplaEsquerda

/*----------------------------------------------------------------------------*/
// Aplica rotações para balancear a arvore
void balanceamento(PtrNoAVL *no){

  // Recebe as alturas dos nós sequentes
  int ad = verificaAltura((*no)->noDireita);
  int ae = verificaAltura((*no)->noEsquerda);

  PtrNoAVL temp;
  int temp_ad, temp_ae;

  // Rotações a direita
  if(ae > ad){
    temp = (*no)->noEsquerda;
    temp_ad = verificaAltura(temp->noDireita);
    temp_ae = verificaAltura(temp->noEsquerda);

    if(temp_ae >= temp_ad){// Rotação simples
      rotacaoSimplesDireita(&(*no));
    }else{// Rotação dupla
      rotacaoDuplaDireita(&(*no));
    }

  }else{// Rotações a esquerda
    temp = (*no)->noDireita;
    temp_ad = verificaAltura(temp->noDireita);
    temp_ae = verificaAltura(temp->noEsquerda);

    if(temp_ad >= temp_ae){// Rotação simples
      rotacaoSimplesEsquerda(&(*no));
    }else{// Rotação dupla
      rotacaoDuplaEsquerda(&(*no));
    }
  }
}//balanceamento

/*----------------------------------------------------------------------------*/
// Insere nós na arvore AVL
bool insereNoAVL(PtrNoAVL *no, int chave){

  // Ponto de inserção (true)
  if((*no) == NULL){
    (*no) = (PtrNoAVL)malloc(sizeof(arvoreAVL));
    (*no)->chave = chave;
    (*no)->noDireita = (*no)->noEsquerda = NULL;
    (*no)->altura = 1;
    return true;
  }

  // Chave repetida (false)
  if((*no)->chave == chave){
    return false;
  }

  bool verificaRecursao;

  // Chamadas recursivas
  if(chave > (*no)->chave){
    verificaRecursao = insereNoAVL(&(*no)->noDireita, chave);
  }else{
    verificaRecursao = insereNoAVL(&(*no)->noEsquerda, chave);
  }

  // Verificação recursão
  if(!verificaRecursao) return false;

  // Recebe as alturas dos nós para verificar se a arvore deve ser balanceada
  int ae = verificaAltura((*no)->noEsquerda);
  int ad = verificaAltura((*no)->noDireita);

  // Realização de balanceamento
  if((ad - ae) >= 2 || (ad - ae) <= -2){
    balanceamento(&(*no));
  }

  // Atualização de altura
  (*no)->altura = atualizaAltura((*no)->noEsquerda, (*no)->noDireita);
  return true;

}//insereNaAVL

/*----------------------------------------------------------------------------*/
// Pega maior valor da subarvore da esquerda
PtrNoAVL maiorEsquerda(PtrNoAVL *no){
  PtrNoAVL aux;

  if((*no)->noDireita == NULL){
    aux = (*no);
    (*no) = (*no)->noEsquerda;
    return aux;
  }
  return maiorEsquerda(&(*no)->noDireita);
}//maiorEsquerda

/*----------------------------------------------------------------------------*/
// Pega menor valor da subarvore da direita
PtrNoAVL menorDireita(PtrNoAVL *no){
  PtrNoAVL aux;

  if((*no)->noEsquerda == NULL){
    aux = (*no);
    (*no) = (*no)->noDireita;
    return aux;
  }
  return menorDireita(&(*no)->noEsquerda);
}//menorDireita

/*----------------------------------------------------------------------------*/
// Remove nós da arvore AVL
bool removeNoAVL(PtrNoAVL *no, int chave, char opcao){

  bool verificaRecursao;

  // Caso não se ache o nó a ser removido
  if((*no) == NULL){
    printf("Warning: Elemento %i não encontrado\n\n", chave);
    return false;
  }

  // Ponto de remoção
  if(chave == (*no)->chave){
    PtrNoAVL aux = (*no);


    if(((*no)->noDireita == NULL && (*no)->noEsquerda == NULL) || ((*no)->noDireita != NULL && (*no)->noEsquerda == NULL)){// Caso 1, só existe apenas o nó da esquerda
      (*no) = (*no)->noDireita;
    }else if((*no)->noDireita == NULL && (*no)->noEsquerda != NULL){// Caso 2, só existe apenas o nó da direita
      (*no) = (*no)->noEsquerda;
    }else{// Caso 3, existe os dois nós (direita e esquerda)

      if(opcao == 'e'){
        aux = maiorEsquerda(&(*no)->noEsquerda);
      }
      if(opcao == 'd'){
        aux = menorDireita((&(*no)->noDireita));
      }

      (*no)->chave = aux->chave;
    }

    free(aux);
    return true;
  }

  // Chamada recursiva
  if(chave > (*no)->chave){
    verificaRecursao = removeNoAVL(&(*no)->noDireita, chave, opcao);
  }else{
    verificaRecursao = removeNoAVL(&(*no)->noEsquerda, chave, opcao);
  }

  if(!verificaRecursao){
    return false;
  }else{
    // Recebe as alturas dos nós para verificar se a arvore deve ser balanceada
    int ae = verificaAltura((*no)->noEsquerda);
    int ad = verificaAltura((*no)->noDireita);

    // Realização de balanceamento
    if((ad - ae) >= 2 || (ad - ae) <= -2){
      balanceamento(&(*no));
    }

    // Atualização de altura
    (*no)->altura = atualizaAltura((*no)->noEsquerda, (*no)->noDireita);
    return true;
  }
}//removeNoAVL

/*----------------------------------------------------------------------------*/
// Imprime AVL em pré-ordem
void preOrdem(PtrNoAVL *no){

  if((*no) == NULL) return;

  printf("%i ", (*no)->chave);
  preOrdem(&(*no)->noEsquerda);
  preOrdem(&(*no)->noDireita);
}//preOrdem

/*----------------------------------------------------------------------------*/
// Procura um número na arvore
bool buscaNumero(PtrNoAVL *no, int chave){

  if((*no) == NULL){// Caso base
    printf("WARNING: valor não encontrado!\n");
    return false;
  }

  if((*no)->chave == chave){// Caso base
    printf("O elemento %i está na arvore!\n", chave);
    return true;
  }

  if(chave > (*no)->chave){// Chamada recurisva
    return buscaNumero(&(*no)->noDireita, chave);
  }else{
    return buscaNumero(&(*no)->noEsquerda, chave);
  }

}//buscaNumero

/*----------------------------------------------------------------------------*/
// Destroi arvore AVL
void destroiAVL(PtrNoAVL *no){
  if((*no) != NULL){
    destroiAVL(&(*no)->noEsquerda);
    destroiAVL(&(*no)->noDireita);
    free((*no));
    (*no) = NULL;
  }
}//destroiAVL

//------------------------------------------------------------------------------
// Imprime o menu de opções
void imprimeMenu(){

  printf("___________________________________________\n");
  printf("|----------- 1. Insere Valores -----------|\n");
  printf("|----------- 2. Remove Valores -----------|\n");
  printf("|----------- 3. Pesquisa Valor -----------|\n");
  printf("|------- 4. Verifica se Está Vazia -------|\n");
  printf("|-------- 5. Imprime em pré-ordem --------|\n");
  printf("|---------- 6. Destroi a arvore ----------|\n");
  printf("|----------- 7. Imprime o Menu -----------|\n");
  printf("|--------- 0. Sair do Programa -----------|\n");
  printf("\n");

}//imprimeMenu


int main(){

  int opcao, valor;
  char metodo;

  PtrNoAVL raiz;
  iniciaArvore(&raiz);

  imprimeMenu();

  do{
    printf("Escolha uma opção: ");
    scanf("%i", &opcao);
    printf("\n");

    switch(opcao){

      case 1:
        printf("Digite um valor a ser inserido: ");
        scanf("%i", &valor);

        insereNoAVL(&raiz, valor);
      break;// Insere valores na arvore AVL

      case 2:
        printf("Digite um valor a ser removido: ");
        scanf("%i", &valor);

        setbuf(stdin, NULL);

        printf("Insira o método de remoção que será utilizado: ");
        scanf("%c", &metodo);

        if(tolower(metodo) != 'e' && tolower(metodo) != 'd') break;

        removeNoAVL(&raiz, valor, metodo);
      break;// Remove valores da arvore AVL

      case 3:
        printf("Insira um valor para ser pesquisado na arvore: ");
        scanf("%i", &valor);

        buscaNumero(&raiz, valor);
      break;// Pesquisa valores na arvore AVL

      case 4:
        if(!verificaVazia(&raiz)){
          printf("A arvore não está vazia!\n");
        }else{
          printf("A arvore está vazia!\n");
        }
      break;// Verifica se a arvore está vazia

      case 5:
        preOrdem(&raiz);
      break;// Imprime a arvore em pré-ordem

      case 6:
        destroiAVL(&raiz);
        printf("Arvore destruida!\n");
      break;// Arvore destruida

      case 7:
        imprimeMenu(&raiz);
      break;// Imprime menu de opções

      case 0:
        printf("Fechando Programa!\n");
      break; // Fecha programa

      default:
        printf("Opção inválida!\n");
      break;// Operação inválida
    }

    printf("\n\n");

  }while(opcao != 0);


  destroiAVL(&raiz);

  return 0;
}
