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
* 6 - Verificar se esta fazia
* 7 - Quantidade de elementos na estrutura
* 8 - Imprimir estrutura
*/

typedef struct NoPilha* trNoPilha;

typedef struct{
  int valor;
  ptrNoPilha proximo;
}NoPilha;

typedef struct{
  ptrNoPilha topo;
}pilhaDinamica;

//Inicia pilha dinamica
void inicializaPilha(pilhaDinamica *p){
  p->topo = NULL;
}

//Verifica se a pilha está vazia;
bool verificaPilha(pilhaDinamica *p){
  return (p->topo == 0);
}

int main(){



return 0;
}
