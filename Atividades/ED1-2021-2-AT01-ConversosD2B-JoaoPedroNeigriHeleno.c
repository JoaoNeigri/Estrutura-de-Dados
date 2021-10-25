/*----------------------------------------------------------------------------*//*
* @author: João Pedro Neigri Heleno, heleno@alunos.utfpr.edu.br
* @author: Carlos Eduardo da Silva Ribeiro, carlos.2001@alunos.utfpr.edu.br
* Name: converte Inteiro Binário
* Description: Programa que faz a conversão de inteiro para binário por meio
* do uso de pilhas e arquivos.
*//*----------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define TAM 15

// Função de Conversão
/*----------------------------------------------------------------------------*/
// Função que Converte inteiro em decimal e insere os valores binários no arquivo de saida
void converte(int valor, FILE * saida){

  int resto, um = 1, zero = 0;

  resto = valor % 2;

  if(1 > valor){// Caso base
    return;
  }else{// Chamada recursiva, que converte o inteiro em binário
    if(resto == 0){
      converte(valor / 2, saida);
      fprintf(saida ,"%i", zero);
    }else{
      converte(valor / 2, saida);
      fprintf(saida ,"%i", um);
    }
  }
}// converte

/*----------------------------------------------------------------------------*/
// Pilha Dinamica
/*----------------------------------------------------------------------------*/

// Estrutura recursica da pilha dinâmica
typedef struct NoPilha *ptrPilha;

// Estrutura do nó da pilha dinâmica
typedef struct NoPilha{

  int chave;
  ptrPilha proximo;

}NoPilha;

//Estrutura da pilha dinâmica
typedef struct{

  ptrPilha topo;
  int quant;

}PilhaDinamica;
/*----------------------------------------------------------------------------*/
// Inicia Pilha Dinâmica
void iniciaPilhaD(PilhaDinamica *p){
  p->topo = NULL;
  p->quant = 0;
}// iniciaPilhaD
/*----------------------------------------------------------------------------*/
// Verifica se a pilha está vazia
bool verificaVaziaPD(PilhaDinamica *p){
  return (p->topo == NULL);
}// verificaVaziaPD
/*----------------------------------------------------------------------------*/
// Inserção da pilha Dinâmica
void inserePilhaD(PilhaDinamica *p, int x){

  // Cria Nó
  ptrPilha no;
  no = malloc(sizeof(NoPilha));

  // O nó recebe o valor a ser inserido na chave e o proximo do nó recebe o endereço que o topo aponta
  no->chave = x;
  no->proximo = p->topo;

  // O topo aponta para o novo nó e incrementa 1 na quantidade nós
  p->topo = no;
  p->quant = p->quant + 1;

}// inserePilhaD
/*----------------------------------------------------------------------------*/
// Retorna a quantidade de elementos da pilha dinâmica
int quantidadePD(PilhaDinamica *p){
  return(p->quant);
}// quantidadePD
/*----------------------------------------------------------------------------*/
// Remove um valor da pilha dinâmica e manda para a função de conversão
int removePilhaD(PilhaDinamica *p, FILE * saida){
  int valor = -999;
  int tamanho = p->quant;

  for(int i = 0; i < tamanho; i++){
    // Condição para verificar se a pilha dinâmica está vazia
    if(!verificaVaziaPD(p)){
      ptrPilha noAux;
      noAux = p->topo;// Nó auxiliar recebe endereço de memória que o topo aponta
      valor = noAux->chave;

      if(valor == 0){
        fprintf(saida, "0");
      }// Caso o numero inteiro seja 0, então passar direto para arquivo final

      p->topo = p->topo->proximo;// O topo recebe o endereço que o próximo do nó auxiliar aponta
      p->quant--;

      free(noAux);

    }else{
      printf("Não é possivel remover mais\n\n");
    }

  // Chamar função que que converte os valores inteiro da pilha em binário
  converte(valor, saida);
  fprintf(saida, "\n");
  }
  return valor;
}// removePilhaD
/*----------------------------------------------------------------------------*/
// Destroi a Pilha Dinâmica
void destroiPD(PilhaDinamica *p){

  while(p->topo != NULL){
    ptrPilha noAux;

    noAux = p->topo;
    p->topo = noAux->proximo;

    free(noAux);
  }

  p->quant = 0;

}// destroiPD

/*----------------------------------------------------------------------------*/
// Pilha Estática
/*----------------------------------------------------------------------------*/

// Estrutura da pilha estática
typedef struct{
  int vetor[TAM];
  int topo;
  int quantidade;
}PilhaEstatica;
/*----------------------------------------------------------------------------*/
// Inicia pilha estática
void iniciaPilhaE(PilhaEstatica *p){
  p->topo = 0;
  p->quantidade = 0;
}// iniciaPilhaE
/*----------------------------------------------------------------------------*/
// Verifica se a pilha estática está vazia
bool verificaVaziaPE(PilhaEstatica *p){
  return (p->topo == 0);
}// verificaVaziaPE
/*----------------------------------------------------------------------------*/
// Verifica se a pilha estática está cheia
bool verificaCheiaPE(PilhaEstatica *p){
  return (p->topo == TAM);
}// verificaCheiaPE
/*----------------------------------------------------------------------------*/
// Retorna a quantidade de elementos da pilha estática
int quantidadePE(PilhaEstatica *p){
  return (p->quantidade);
}// quantidadePE
/*----------------------------------------------------------------------------*/
// Insere um valor na pilha estática
void inserePilhaE(PilhaEstatica *p, int x){
  if(!verificaCheiaPE(p)){
    p->vetor[p->topo] = x;
    p->topo++;
    p->quantidade++;
  }else{
    printf("Não é possivel inserir mais valores\n\n");
  }
}// inserePilhaE
/*----------------------------------------------------------------------------*/
// Remove um valor da pilha estática e manda para a função de conversão
void removePilhaE(PilhaEstatica *p, FILE *saida){
  int valor, tamanho;
  tamanho = p->quantidade;

  for(int i = 0; i < tamanho; i++){
    if(!verificaVaziaPE(p)){
      valor = p->vetor[p->topo-1];
      p->topo--;
      if(valor == 0){
        fprintf(saida, "0");
      }
    }else{
      printf("Não há elementos para serem removidos\n\n");
    }
    converte(valor, saida);
    fprintf(saida, "\n");
  }
}// removePilhaE

/*----------------------------------------------------------------------------*/
// Funções que leem os arquivos e armazenam seus números na pilha correta
/*----------------------------------------------------------------------------*/

// Função que lê os arquivo e converte usando uma pilha estática
void le_PilhaEstatica(FILE *entrada, FILE *saida){

  float numero = -999;
  int aux;
  char verificaFim;
  PilhaEstatica pilhaE;
  iniciaPilhaE(&pilhaE);

  // Percorre o arquivo pegando os numeros a serem convertidos
  while((verificaFim = fgetc(entrada)) != EOF){
    fscanf(entrada, "%f", &numero);

    // Verifica se há números no arquivo
    if(numero == -999){
      fprintf(saida, "Arquivo Inválido!");
      exit(1);
    }

    // Verifica se o número é um float
    aux = numero;
    if(aux != numero){
      fprintf(saida, "Arquivo Inválido!");
      exit(1);
    }

    // Insere valor na pilha
    inserePilhaE(&pilhaE, numero);
  }

  // Chama a função que remove os numeros da pilha estática (dentro da função remove é Chamada
      // a função que realiza a conversão dos números)
  removePilhaE(&pilhaE, saida);
  fprintf(saida, "\n");

  // Fecha os arquivos de entrada e saida
  fclose(entrada);
  fclose(saida);

}// le_PilhaEstatica
/*----------------------------------------------------------------------------*/
// Função que lê os arquivos e converte usando uma pilha dinâmica
void le_PilhaDinamica(FILE *entrada, FILE *saida){

  float numero = -999;
  int aux;
  char verificaFim;
  PilhaDinamica pilhaD;

  iniciaPilhaD(&pilhaD);
  // Percorre o arquivo pegando os numeros a serem convertidos
  while((verificaFim = fgetc(entrada)) != EOF){
    fscanf(entrada, "%f", &numero);

    // Verifica se há números no arquivo
    if(numero == -999){
      fprintf(saida, "Arquivo Inválido!");
      exit(1);
    }

    // Verifica se o número é um float
    aux = numero;
    if(aux != numero){
      fprintf(saida, "Arquivo Inválido!");
      exit(1);
    }

    // Insere valor na pilha
    inserePilhaD(&pilhaD, numero);
  }

  // Chama a função que remove os numeros da pilha dinâmica (dentro da função remove é Chamada
      // a função que realiza a conversão dos números)
  removePilhaD(&pilhaD, saida);
  fprintf(saida, "\n");

  //Destroi a pilha dinâmica
  destroiPD(&pilhaD);
  // Fecha os arquivos de entrada e saida
  fclose(entrada);
  fclose(saida);

}// le_PilhaDinamica
/*----------------------------------------------------------------------------*/

int main(int argc, const char * argv[]){

  FILE * entrada, * saida;
  char c;
  int quantLinha;

  // Verifica se foram passados o número correto de parâmetros
  if(argc != 3){
    printf("Número inválido de parâmetros\n\n");
    exit(1);
  }else{// Abre os arquivos passados por parâmetro

    entrada = fopen(argv[1], "r");
    saida = fopen(argv[2], "w");

    if(entrada == NULL || saida == NULL){
     printf("Erro ao abrir arquivo!\nFechando Programa\n\n");
     exit(1);
    }
  }//else

  c = fgetc(entrada);

  if(c == 'd'){
    le_PilhaDinamica(entrada, saida);
  }else if(c == 'e'){
    le_PilhaEstatica(entrada, saida);
  }else{
    fprintf(saida, "Arquivo Inválido!");
  }

  return 0;
}
