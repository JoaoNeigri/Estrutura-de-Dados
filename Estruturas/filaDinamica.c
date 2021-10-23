#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*                          -Operações de modificação-
* 1 - Inicialização
* 2 - Enfileira
* 3 - Desenfileirar
* 4 - Pesquisa/consulta
* 5 - Destruir dado
*/

/*                          -Operações adicionais ED-
* 6 - Verificar se esta vazia
* 7 - Quantidade de elementos na estrutura
* 8 - Imprimir estrutura
*/

typedef struct NoFila* ptrNo;

typedef struct NoFila{
  int chave;
  ptrNo proximo;
}NoFila;

typedef struct{
  ptrNo inicio;
  ptrNo fim;
  int quantidade;
}filaDinamica;

/*----------------------------------------------------------------------------*/

// Inicia a fila dinâmica

void inicializaFila(filaDinamica *f){
  f->inicio = f->fim = NULL;
  f->quantidade = 0;
}

/*----------------------------------------------------------------------------*/

// Verifica se a pilha esta vazia

bool verificaVazia(filaDinamica *f){
  return (f->quantidade == 0);
}

/*----------------------------------------------------------------------------*/

// Retorna a quantidade de elementos na fila

int quantidadeElementos(filaDinamica *f){
  return f->quantidade;
}

/*----------------------------------------------------------------------------*/

// Insere um valor na fila dinâmica

void insereFila(filaDinamica *f, int x){

  ptrNo no = malloc(sizeof(NoFila));

  no->chave = x;

  if(verificaVazia(f)){
    f->inicio = no;

    f->fim = no;

    no->proximo = NULL;
  }else{

    no->proximo = f->fim->proximo;

    f->fim->proximo = no;

    f->fim = f->fim->proximo;

  }

  f->quantidade++;
}

/*----------------------------------------------------------------------------*/

// Remove um elemento da fila

int removeElemento(filaDinamica *f){

  int x = -99999;

  if(!verificaVazia(f)){
    ptrNo aux;

    aux = f->inicio;

    x = aux->chave;

    f->inicio = f->inicio->proximo;

    free(aux);

    f->quantidade--;

  }else{
    printf("Warning, não há elementos para remover!\n\n");
  }

  return x;
}

/*----------------------------------------------------------------------------*/

// Imprime a fila

void imprimiFila(filaDinamica *f){

  ptrNo ptr;

  printf("[ ");
  for(ptr = f->inicio; ptr != NULL; ptr = ptr->proximo){
    printf("%i ", ptr->chave);
  }
  printf("]\n\n");
}

/*----------------------------------------------------------------------------*/

// Retorna o inicio da fila

int verificaPrimeiroElemento(filaDinamica *f){
  if(!verificaVazia(f))
    return (f->inicio->chave);
  else
    return -999;
}

/*----------------------------------------------------------------------------*/

// Retorna o ultimo valor da fila

int verificaUltimoElemento(filaDinamica *f){
  if(!verificaVazia(f))
    return (f->fim->chave);
  else
    return -999;
}

/*----------------------------------------------------------------------------*/

// Destroi Fila

void destroiFila(filaDinamica *f){
  while(f->inicio != NULL){

    // Cria um nó
    ptrNo noAux;
    // O nó criado recebe o endereço do inicio
    noAux = f->inicio;
    // O inicio recebe o endereço do proximo do inicio
    f->inicio = f->inicio->proximo;
    // Libera o nó
    free(noAux);
  }
  // Define a quantidade de elementos para 0
  f->quantidade = 0;
}

/*----------------------------------------------------------------------------*/

void imprimeMenu(){
  printf("----------- 1. Insere Valores ---------\n");
  printf("----------- 2. Remove Valores ---------\n");
  printf("----- 3. Retorna Primeiro Elemento ----\n");
  printf("----- 4. Retorna Ultimo Elemento ------\n");
  printf("- 5. Retorna Quantidade de Elementos --\n");
  printf("---------- 6. Destroi a Fila ----------\n");
  printf("------- 7. Verifica se Está Vazia -------");
  printf("----------- 8. Imprime a Fila -----------");
  printf("----------- 9. Imprime o Menu -----------");

}

/*----------------------------------------------------------------------------*/

int main(){

  filaDinamica fila;
  int opcao, valor, remocao, primeiroElemento, ultimoElemento, elementos;

  inicializaFila(&fila);

  imprimeMenu();

  do{

    printf("Escolha uma opção: ");
    scanf("%i", &opcao);

    printf("\n");

    switch(opcao){

      case 1:
        printf("Digite um valor para inserir na fila: ");
        scanf("%i", &valor);

        insereFila(&fila, valor);
      break;

      case 2:
        remocao = removeElemento(&fila);
        printf("O valor removido é: %i\n", remocao);
      break;

      case 3:
        primeiroElemento = verificaPrimeiroElemento(&fila);
        printf("O primeiro elemento da fila é %i\n", primeiroElemento);
      break;

      case 4:
        ultimoElemento = verificaUltimoElemento(&fila);
        printf("O ultimo elemento da fila é %i\n", ultimoElemento);
      break;

      case 5:
        elementos = quantidadeElementos(&fila);
        printf("A fila tem %i elementos\n", elementos);
      break;

      case 6:
        destroiFila(&fila);
      break;

      case 7:
        if(verificaVazia(&fila)){
          printf("A lista está vazia! \n");
        }else{
          printf("A pilha não está vazia\n");
        }
      break;

      case 8:
        imprimiFila(&fila);
      break;

      case 9:
        imprimeMenu();
      break

      default:
        printf("Opção inválida!\n");
      break;

    }

    printf("\n");
  }while(opcao != 0);


  return 0;
}
