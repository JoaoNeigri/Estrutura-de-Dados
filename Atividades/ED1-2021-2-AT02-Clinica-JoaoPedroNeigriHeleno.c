/*----------------------------------------------------------------------------*//*
* @author: João Pedro Neigri Heleno, heleno@alunos.utfpr.edu.br
* @author: Carlos Eduardo da Silva Ribeiro, carlos.2001@alunos.utfpr.edu.br
* @file: ED1-2-AT02-Clinica-JoaoPedroNeigriHeleno
* Description: Programa que ordena de acordo com a entrada os dados passados pelo
* arquivo
*//*----------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define TAMNOME 100

/*----------------------------------------------------------------------------*/
// Lista Ordenada
typedef struct NoLista * ptrNoLista;

typedef struct NoLista{
  int id;
  char nome[TAMNOME];
  char sexo;
  float massa;
  int altura;
  ptrNoLista proximo;
  ptrNoLista anterior;
}NoLista;

typedef struct {
  ptrNoLista inicio;
  ptrNoLista fim;
}ListaOrdenada;
/*----------------------------------------------------------------------------*/
// Implementação da lista ordenada

// Inicialização da lista ordenada
void iniciaLista(ListaOrdenada *l){
  l->inicio = l->fim = NULL;
}//iniciaLista

// Verifica se a lista está vazia
bool verificaVazia(ListaOrdenada *l){
  return (l->inicio == NULL);
}//verificaVazia

// Insere nós na lista
void insereElementosLista(ListaOrdenada *l, int id, char *nome, char sexo, float massa, int altura){

  ptrNoLista no = malloc(sizeof(NoLista));

  //Atribuindo valores para o nó
  no->id = id;
  strcpy(no->nome, nome);
  no->sexo = sexo;
  no->massa = massa;
  no->altura = altura;

  //C1: Lista vazia
  if(verificaVazia(l)){

    // O próximo do nó é o inicio (próximo do nó = NULL)
    no->proximo = l->inicio;
    // O anterior do nó é o fim (anterior do nó = NULL)
    no->anterior = l->fim;
    // O inicio armazena o nó
    l->inicio = no;
    // O fim armazena o nó
    l->fim = no;

  }else if(id <= l->inicio->id){//C2: Caso o elemento se torne o primeiro da lista

    // O próximo do nó é o inicio
    no->proximo = l->inicio;
    // O nó não possui anterior logo é igual a nulo (anterior do nó = NULL)
    no->anterior = NULL;
    // O anterior do próximo nó é o nó
    no->proximo->anterior = no;
    // O inicio armazena o nó
    l->inicio = no;

  }else{//C3: Caso seja posicionado no meio da lista

    ptrNoLista percorre = l->inicio;

    // Procura a posição correta para armazenar o nó
    while(percorre->proximo != NULL && id > percorre->proximo->id){
      percorre = percorre->proximo;
    }
    // O proximo aponta para o próximo do percorre
    no->proximo = percorre->proximo;
    // O anterior do nó aponta para percorre
    no->anterior = percorre;
    // O próximo do percorre aponta para o nó
    percorre->proximo = no;

    // Verifica se o próximo do nó não é nulo, para conseguir atribuir o anterior do próximo nó
    if(no->proximo == NULL){
      l->fim = no;
    }else{
      no->proximo->anterior = no;
    }

  }

}//insereElementosLista

// Imprime os dados em forma crescente de acordo com id
void imprimeCrescente(ListaOrdenada *l, FILE *saida){

  ptrNoLista percorre = l->inicio;

  while(percorre != NULL){
    fprintf(saida, "{%i,%s,%c,%.1f,%d}\n", percorre->id, percorre->nome, percorre->sexo, percorre->massa, percorre->altura);
    percorre = percorre->proximo;
  }

}//imprimeCrescente

// Imprime os dados em forma descrescente de acordo com id
void imprimeDescrescente(ListaOrdenada *l, FILE *saida){

  ptrNoLista percorre = l->fim;

  while(percorre != NULL){
    fprintf(saida, "{%i,%s,%c,%.1f,%d}\n", percorre->id, percorre->nome, percorre->sexo, percorre->massa, percorre->altura);
    percorre = percorre->anterior;
  }
}//imprimeDescrescente

// Pesquisa o id e retorna as informações do id (nome, sexo, massa, altura)
bool pesquisaId(ListaOrdenada *l, int id, FILE *saida){
  // Verifica se a lista está vazia e le o id é valido
  if(verificaVazia(l) || id < l->inicio->id){
    fprintf(saida, "Elemento não encontrado!\n\n");
    return false;
  }

  // Verifica se o id é o primeiro da lista
  if(id == l->inicio->id){
    fprintf(saida, "{%i,%s,%c,%.1f,%d}\n", l->inicio->id, l->inicio->nome, l->inicio->sexo, l->inicio->massa, l->inicio->altura);
    return true;
  }

  ptrNoLista percorre = l->inicio;

  // Procura o id na lista
  while(percorre != NULL && id > percorre->id){
    percorre = percorre->proximo;
  }

  // Verifica se o id está correto
  if(percorre == NULL || id != percorre->id){
    fprintf(saida, "Elemento não encontrado!\n\n");
    return false;
  }

  fprintf(saida, "{%i,%s,%c,%.1f,%d}\n", percorre->id, percorre->nome, percorre->sexo, percorre->massa, percorre->altura);
  return true;

}//pesquisaId

// Destroi a lista ordenada
void destroiLista(ListaOrdenada *l){

  ptrNoLista percorre = l->inicio;
  ptrNoLista aux;

  // Percorre os nós
  while(percorre != NULL){
    // Destroi os nós
    aux = percorre;
    free(aux);
    // percorre recebe o próximo nó
    percorre = percorre->proximo;
  }
  // Reseta o inicio e fim
  l->inicio = NULL;
  l->fim = NULL;

}//destroiLista

/*----------------------------------------------------------------------------*/
// Realiza a leitura do arquivo
char leituraArquivo(ListaOrdenada *l, FILE *entrada){

  NoLista le;
  char caractere, c;

  while((caractere = fgetc(entrada)) == '{'){

    //Leitura do id
    fscanf(entrada, "%i,", &le.id);

    memset(le.nome, 0,sizeof(le.nome));

    //Leitura do nome do paciente
    for(int i = 0; i < TAMNOME; i++){
      c = fgetc(entrada);

      if(c != ','){
        le.nome[i] = c;
      }else{
        break;
      }
    }

    //Leitura do sexo, peso e altura do paciente
    fscanf(entrada, "%c,%f,%d}\n", &le.sexo, &le.massa, &le.altura);

    //Insere os valores na lista
    insereElementosLista(l, le.id, le.nome, le.sexo, le.massa, le.altura);
  }

  return caractere;

}//leituraArquivo

int main(int argc, const char * argv[]){

  FILE *entrada, *saida;
  char c;
  int id;

  if(argc != 3){
    printf("Erro: os parâmetros foram passados incorretamente!\n\nFechando Programa\n\n");
    exit(1);
  }else{

    entrada = fopen(argv[1], "r");
    saida = fopen(argv[2], "w");


    if(entrada == NULL || saida == NULL){
      printf("Erro: ocorreu um problema ao abrir os arquivos!\n\nFechando o programa\n\n");
      exit(1);
    }
  }

  ListaOrdenada lista;
  iniciaLista(&lista);

  c = leituraArquivo(&lista, entrada);

  switch(c){

    case '1':
      imprimeCrescente(&lista, saida);
    break;

    case '2':
      imprimeDescrescente(&lista, saida);
    break;

    case '3':
      fscanf(entrada, "%i", &id);
      pesquisaId(&lista, id, saida);
    break;

    default:
      fprintf(saida, "Arquivo Inválido");
    break;
  }

  destroiLista(&lista);

  return 0;
}//main
