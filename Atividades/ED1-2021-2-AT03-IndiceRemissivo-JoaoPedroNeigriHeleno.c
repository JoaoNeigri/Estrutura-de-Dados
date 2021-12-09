/*----------------------------------------------------------------------------*//*
* @author: João Pedro Neigri Heleno, heleno@alunos.utfpr.edu.br, @github: JoaoNeigri
* @author: Carlos Eduardo da Silva Ribeiro, carlos.2001@alunos.utfpr.edu.br
* @file: ED13-AT03-IndiceRemissivo-JoaoPedroNeigriHeleno
* @Description: Programa utiliza arvores binárias e listas ordenadas para estrutu
rar um índice remissivo
*//*----------------------------------------------------------------------------*/

#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

/*----------------------------------------------------------------------------*/
// Declaração da estrutura de uma lista ordenada
/*----------------------------------------------------------------------------*/

typedef struct NoLista * PtrNoLista;

typedef struct NoLista{
  int pagina;
  PtrNoLista proximo;
}NoLista;

typedef struct{
  PtrNoLista inicio;
}ListaOrdenada;

/*----------------------------------------------------------------------------*/
// Declaração da estrutura de uma arvore binária
/*----------------------------------------------------------------------------*/

typedef struct{
  char palavra[60];
  ListaOrdenada lista;
}Objeto;

typedef struct NoArvore *PtrArvore;

typedef struct NoArvore{
  Objeto objeto;
  PtrArvore noDireita;
  PtrArvore noEsquerda;
}NoArvore;

/*----------------------------------------------------------------------------*/
// Funções que compõem uma lista ordenada
/*----------------------------------------------------------------------------*/
// Inicia lista ordenada
void iniciaLista(ListaOrdenada *l){
  l->inicio = NULL;
}//iniciaLista

/*----------------------------------------------------------------------------*/
// Verifica se a lista ordenada esta vazia
bool verificaVaziaLista(ListaOrdenada *l){
  return (l->inicio == NULL);
}//verificaVaziaLista

/*----------------------------------------------------------------------------*/
// Insere os nós (contendo as páginas a serem armazenadas) na lista ordenada
void insereNoLista(ListaOrdenada * l, int pagina){//l, pagina

  PtrNoLista aux = l->inicio;

  while(aux != NULL){// Verifica se existe o elemento lista.
    if(pagina == aux->pagina) return;// Caso exista a inserção é abortada

    aux = aux->proximo;
  }

  PtrNoLista no;
  no = malloc(sizeof(NoLista));
  // Copia o valor do elemento para chave do no
  no->pagina = pagina;

  //C1: pagina <= primeira pagina || Lista vazia = (true)
  if((verificaVaziaLista(l)) || (pagina < l->inicio->pagina)){
    no->proximo = l->inicio;
    l->inicio = no;
  }else{//C2: Pagina > primeira página

    PtrNoLista percorre;

    percorre = l->inicio;
    while((percorre->proximo!= NULL) && (pagina > percorre->proximo->pagina)) {
      percorre = percorre->proximo;
    }

    no->proximo = percorre->proximo;
    percorre->proximo = no;
  }

}//insereNoLista

/*----------------------------------------------------------------------------*/
// Imprime lista ordenada
void imprimeLista(ListaOrdenada *l, FILE * saida){
  PtrNoLista percorre = l->inicio;

  while(percorre != NULL){
    fprintf(saida, ",%d", percorre->pagina);
    percorre = percorre->proximo;
  }
}//imprimeLista

/*----------------------------------------------------------------------------*/
//Destroi a lista ordenada
void destroiLista(ListaOrdenada *l){

  PtrNoLista percorre;
  if(!verificaVaziaLista(l)){

    while(l->inicio != NULL){
      percorre = l->inicio;
      l->inicio = l->inicio->proximo;

      free(percorre);
    }
  }
}//destroiLista

/*----------------------------------------------------------------------------*/
// Funções que compõem uma arvore binária
/*----------------------------------------------------------------------------*/
// Inicia arvore binária
void iniciaArvore(PtrArvore *no){
  (*no) = NULL;
}//iniciaArvore

/*----------------------------------------------------------------------------*/
// Verifica se a arvore está vazia
bool verificaVazia(PtrArvore *no){
  return ((*no) == NULL);
}//verificaVazia

/*----------------------------------------------------------------------------*/
// Insere nós na arvore binária
bool insereNoArvore(PtrArvore *no, char *str){

  if((*no) == NULL){//Caso Base

    (*no) = malloc(sizeof(NoArvore));
    (*no)->noDireita = (*no)->noEsquerda = NULL;
    iniciaLista(&((*no)->objeto.lista));
    strcpy((*no)->objeto.palavra, str);

    return true;
  }

  if(strcmp((*no)->objeto.palavra, str) == 0){//Caso Base
    // printf("Palavra ja existente no indice remissivo\n\n");
    return false;
  }

  if(strcmp(str, (*no)->objeto.palavra) > 0){// Chamada Recursiva
    return insereNoArvore(&(*no)->noDireita, str);
  }else{// Chamada Recursiva
    return insereNoArvore(&(*no)->noEsquerda, str);
  }

}//insereNoArvore

/*----------------------------------------------------------------------------*/

// Verifica se a palavra que foi pega no texto é igual à alguma da arvore
bool verificaPalavras(PtrArvore *no, char *str, int pagina){

  if((*no) == NULL){//Caso Base
    return false;
  }

  //Caso Base, Adiciona pagina na lista se as palavras (sub e (*no)->objeto.palavra) são igual,
  if(strcmp((*no)->objeto.palavra, str) == 0){
    insereNoLista(&((*no)->objeto.lista), pagina);
    return true;
  }

  if(strcmp(str, (*no)->objeto.palavra) > 0){// Chamada Recursiva
    return verificaPalavras(&(*no)->noDireita, str, pagina);
  }else{// Chamada Recursiva
    return verificaPalavras(&(*no)->noEsquerda, str, pagina);
  }
}//verificaPalavra

/*----------------------------------------------------------------------------*/
void emOrdem(PtrArvore *no, FILE *saida){
  if((*no) == NULL) return;

  emOrdem(&(*no)->noEsquerda, saida);
  //printf("%s", (*no)->objeto.palavra);
  fprintf(saida, "%s", (*no)->objeto.palavra);
  imprimeLista(&(*no)->objeto.lista, saida);
  fprintf(saida, "\n");
  emOrdem(&(*no)->noDireita, saida);
}//emOrdem

/*----------------------------------------------------------------------------*/
// Destroi a arvore binária
void destroiArvore(PtrArvore *no){
  if((*no) != NULL){// Chamada recursiva para a destruição da arvore e da lista

    destroiArvore(&(*no)->noEsquerda);
    destroiArvore(&(*no)->noDireita);
    destroiLista(&(*no)->objeto.lista);
    free(*no);
    (*no) = NULL;
  }
}//destroiArvore

/*----------------------------------------------------------------------------*/
// Converte as strings para minusculo
char * stringMinuculo(char * string){
  for(int i = 0; i < strlen(string); i++){// For que percorre todas as posições da string
    string[i] = tolower(string[i]);
  }
  return string;
}

int main(int argc, const char * argv[]){

  if(argc != 3){// Verificação de erro, numero de parâmetros inválidos
    printf("Numero de parâmetros inválidos\n\n");
    exit(1);
  }

  FILE *entrada, *saida;
  NoArvore *arvore;
  char primeiraLinha[500], texto[500], *sub;
  int contaPagina = 0;

  entrada = fopen(argv[1], "r");
  saida = fopen(argv[2], "w");

  if(entrada == NULL || saida == NULL){// Verificação de erro, erro ao abrir arquivo
    printf("WARNING: Erro ao abrir arquivo!\n\n");
    exit(1);
  }

  iniciaArvore(&arvore);

  fscanf(entrada, "%s", primeiraLinha);// Recebe a primeira linha com os termos a serem colocado no indice remissivo
  sub = strtok(primeiraLinha, " ,.<>(){}/:");// Quebra a string em sub strings

  if(strcmp(sub, "termos") != 0) exit(1);// Controle de erros

  while(true){
    sub = strtok(NULL, " ,.<>(){}/:");// Quebra a string em sub strings
    if(sub == NULL) break;// condição loop

    sub = stringMinuculo(sub);

    insereNoArvore(&arvore, sub);// Insere os indices na arvore
  }


  while(fgets(texto, 500, entrada) != NULL){

    sub = strtok(texto, " ,.<>(){}/:\n");

    while(sub != NULL){
      sub = stringMinuculo(sub);
      if(strcmp(sub, "page") == 0) contaPagina++;

      verificaPalavras(&arvore, sub, contaPagina);
      // printf("SUB: %s | PAGINA: %d\n", sub, contaPagina);
      sub = strtok(NULL, " ,.<>(){}/:\n");
    }
  }

  emOrdem(&arvore, saida);// Imprime os índices em ordem crescente em um arquivo
  printf("\n");

  destroiArvore(&arvore);

  //Encerramento das variaveis de arquivo
  fclose(entrada);
  fclose(saida);
  saida = entrada = NULL;

  printf("Algoritmo executado com sucesso!\n\n");

  return 0;
}
