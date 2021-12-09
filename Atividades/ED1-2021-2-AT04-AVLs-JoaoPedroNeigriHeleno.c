/*--------------------------------------------------------------------------*//*
* @author: João Pedro Neigri Heleno, heleno@alunos.utfpr.edu.br
* @author: Carlos Eduardo da Silva Ribeiro, carlos.2001@alunos.utfpr.edu.br
* @file: ED1-2-AT04-AVLs-JoaoPedroNeigriHeleno
* Description: Arvore AVL
*//*--------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/*----------------------------------------------------------------------------*/
// Estrutura arvore AVL
typedef struct arvoreAVL * PtrNoAVL;

typedef struct arvoreAVL{
  int chave;
  int altura;
  int nivel;
  PtrNoAVL noDireita;
  PtrNoAVL noEsquerda;
}arvoreAVL;

/*----------------------------------------------------------------------------*/
// Inicia arvore AVL
void iniciaAVL(PtrNoAVL *no){
  (*no) = NULL;
}//iniciaAVL

/*----------------------------------------------------------------------------*/
// Verifica se a arvore esta vazia
bool verificaVaziaAVL(PtrNoAVL *no){
  return (*no) == NULL;
}//verificaVaziaAVL

/*----------------------------------------------------------------------------*/
// Verifica as alturas dos nós
int verificaAltura(PtrNoAVL no){
  if(no == NULL){
    return 0;
  }else{
    return (no->altura);
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
  PtrNoAVL n = (*no)->noEsquerda;
  (*no)->noEsquerda = n->noDireita;
  n->noDireita = (*no);

  // Atualiza altura
  (*no)->altura = atualizaAltura((*no)->noEsquerda, (*no)->noDireita);
  n->altura = atualizaAltura(n->noEsquerda, n->noDireita);

  // Atualizando referência
  (*no) = n;
}//rotacaoSimplesDireita

/*----------------------------------------------------------------------------*/
// Rotação dupla a direita
void rotacaoDuplaDireita(PtrNoAVL *no){

  // Realização da rotação
  PtrNoAVL n = (*no)->noEsquerda;
  PtrNoAVL m = n->noDireita;

  (*no)->noEsquerda = m->noDireita;
  n->noDireita = m->noEsquerda;

  m->noDireita = (*no);
  m->noEsquerda = n;

  // Atualiza altura
  (*no)->altura = atualizaAltura((*no)->noEsquerda, (*no)->noDireita);
  n->altura = atualizaAltura(n->noEsquerda, n->noDireita);
  m->altura = atualizaAltura(m->noEsquerda, m->noDireita);

  // Atualizando referência
  (*no) = m;
}//rotacaoDuplaDireita

/*----------------------------------------------------------------------------*/
// Rotação simples a esquerda
void rotacaoSimplesEsquerda(PtrNoAVL *no){

  // Realização da rotação
  PtrNoAVL n = (*no)->noDireita;
  (*no)->noDireita = n->noEsquerda;
  n->noEsquerda = (*no);

  // Atualiza altura
  (*no)->altura = atualizaAltura((*no)->noEsquerda, (*no)->noDireita);
  n->altura = atualizaAltura(n->noEsquerda, n->noDireita);

  // Atualizando referência
  (*no) = n;
}//rotacaoSimplesEsquerda

/*----------------------------------------------------------------------------*/
// Rotação simples a esquerda
void rotacaoDuplaEsquerda(PtrNoAVL *no){

  // Realização da rotação
  PtrNoAVL n = (*no)->noDireita;
  PtrNoAVL m = n->noEsquerda;

  (*no)->noDireita = m->noEsquerda;
  n->noEsquerda = m->noDireita;

  m->noEsquerda = (*no);
  m->noDireita = n;

  // Atualiza altura
  (*no)->altura = atualizaAltura((*no)->noEsquerda, (*no)->noDireita);
  n->altura = atualizaAltura(n->noEsquerda, n->noDireita);
  m->altura = atualizaAltura(m->noEsquerda, m->noDireita);

  // Atualizando referência
  (*no) = m;
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
// Insere nó na arvore AVL
bool insereNoAVL(PtrNoAVL *no, int chave){

  bool verificaRecursao;

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

}//insereNoAVL

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
void imprimeArvore(PtrNoAVL *no, int altura, FILE *saida){

  int ae, ad, bf;

  if((*no) == NULL) return;

  if((*no)->nivel == altura){

    ae = verificaAltura((*no)->noEsquerda);
    ad = verificaAltura((*no)->noDireita);

    bf = ad - ae;
    fprintf(saida, "%i (%i),", (*no)->chave, bf);

  }

  imprimeArvore(&(*no)->noEsquerda, altura, saida);
  imprimeArvore(&(*no)->noDireita, altura, saida);
}//emOrdem

/*----------------------------------------------------------------------------*/
// Define a altura de cada nó
void nivelNoAVL(PtrNoAVL *no){
  if((*no) == NULL) return;

  if((*no)->noEsquerda != NULL){
    (*no)->noEsquerda->nivel = (*no)->nivel + 1;
  }
  if((*no)->noDireita != NULL){
    (*no)->noDireita->nivel = (*no)->nivel + 1;
  }
  nivelNoAVL(&(*no)->noEsquerda);
  nivelNoAVL(&(*no)->noDireita);

  return;
}//nivelNoAVL

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

/*----------------------------------------------------------------------------*/
// Controla todas as funções para que o algoritmo funcione corretamente
int main(int argc, const char * argv[]){

/*----------------------------------------------------------------------------*/
/*-----------------------------INICIANDO LEITURA/*----------------------------*/

  if(argc != 3){
    printf("WARNING: quantidade inválida de parâmetros\n\n");
    exit(1);
  }

  PtrNoAVL raiz;
  char linha1[500], linha2[500], opcao, *sub;
  FILE *entrada, *saida;
  int chave, chaveRemocao, altura;

  entrada = fopen(argv[1], "r");
  saida = fopen(argv[2], "w");

  if(entrada == NULL || saida == NULL){
    printf("WARNING: erro ao abrir arquivo(s)");
    exit(1);
  }

  iniciaAVL(&raiz);

/*----------------------------------------------------------------------------*/
/*--------------------LEITURA DA PRIMEIRA LINHA DO ARQUIVO--------------------*/

  fgets(linha1, 500, entrada); // Recebe primeira  linha

  sub = strtok(linha1, ",");
  chave = atoi(sub);
  insereNoAVL(&raiz, chave);

  while(true){
    sub = strtok(NULL, ",");

    if(sub == NULL) break;

    chave = atoi(sub);
    insereNoAVL(&raiz, chave);
  }

/*----------------------------------------------------------------------------*/
/*--------------------LEITURA DA SEGUNDA LINHA DO ARQUIVO---------------------*/

  fgets(linha2, 500, entrada); // Recebe segunda linha
  opcao = fgetc(entrada); // Recebe terceira linha

  if(opcao != 'e' && opcao != 'd'){
    fprintf(saida, "Arquivo inválido!");
    exit(1);
  }

/*----------------------------------------------------------------------------*/
/*--------------------IMPRESSÃO DA ARVORE ANTES DA REMOÇÃO--------------------*/

  fprintf(saida, "[*]antes\n");

  raiz->nivel = 1; // Altura inicial de toda arvore
  nivelNoAVL(&raiz);

  altura = verificaAltura(raiz);

  for(int i = 1; i <= altura; i++){
    imprimeArvore(&raiz, i, saida); // Imprime a arvore antes das remoções
    fprintf(saida, "\n");
  }

/*----------------------------------------------------------------------------*/
/*-----------------------INTERPRETAÇÃO DAS LINHAS 2 E 3-----------------------*/

  sub = strtok(linha2, ",");
  chaveRemocao = atoi(sub);
  removeNoAVL(&raiz, chaveRemocao, opcao);

  while(true){
    sub = strtok(NULL, ",");

    if(sub == NULL) break;

    chaveRemocao = atoi(sub);
    removeNoAVL(&raiz, chaveRemocao, opcao);
  }

/*----------------------------------------------------------------------------*/
/*---------------------IMPRESSÃO DA ARVORE APÓS A REMOÇÃO---------------------*/

  fprintf(saida, "\n[*]depois\n");

  raiz->nivel = 1; // Altura inicial de toda arvore
  nivelNoAVL(&raiz);

  altura = verificaAltura(raiz);

  for(int i = 1; i <= altura; i++){
    imprimeArvore(&raiz, i, saida); // Imprime a arvore depois das remoções
    fprintf(saida, "\n");
  }

/*----------------------------------------------------------------------------*/
/*---------------------------ENCERRANDO PROGRAMA/*----------------------------*/

  destroiAVL(&raiz);
  printf("\nAlgoritmo executado com sucesso!\n\n");
  return 0;
}//main
