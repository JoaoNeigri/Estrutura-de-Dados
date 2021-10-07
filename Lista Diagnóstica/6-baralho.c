/*
Faça um baralho com as mesmas funções que estão na tabela 1
           funções                       |                Descrição
void criaBaralho(baralho *baralho);      |   inicia um novo baralho criando todas as cartas nele contido.
int cartasNaoJogadas(Baralho *baralho);  |   Consulta o numero de cartas disponıveis para jogo.
Carta topo(Baralho *baralho);            |   Consulta a carta do topo de um baralho.
Carta fundo(Baralho *baralho);           |   Consulta a carta do fundo de um baralho.
Carta* carteado(Baralho *baralho);       |   Retorna um array com 3 cartas aleatorias para um jogador;
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

typedef struct{
  char valor;
  char naipe;
  bool foiJogada;
}Carta;

typedef struct{
  Carta matriz[13][4];
}Baralho;
//----------------------------------------------------------------------------//


//Cria arrays para os valores das cartas
char naipe[4] = {'O', 'E', 'C', 'P'};
char valores[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'D','J', 'Q', 'K'};

//----------------------------------------------------------------------------//

/*                           -criaBaralho-
*Função que inicia o baralho, utilizando um loop o baralho é criado usando os
*arrays contendo naipe e valor de cartas, ambos declarados no escopo global.
*/

void criaBaralho(Baralho *baralho){

  for(int i = 0; i < 13; i++){
    for(int j = 0; j < 4; j++){
      baralho->matriz[i][j].valor = valores[i];
      baralho->matriz[i][j].naipe = naipe[j];
      baralho->matriz[i][j].foiJogada = false;
    }
  }

}//criaBaralho


//----------------------------------------------------------------------------//

/*                           -resetaCartas-
* Função usada para resetar as cartas do baralho criado.
*/

void resetaCartas(Baralho *baralho){
  for(int i = 0; i < 13; i++){
    for(int j = 0; j < 4; j++){
      baralho->matriz[i][j].foiJogada = false;
    }
  }
}//resetaCartas

//----------------------------------------------------------------------------//

/*                           -consultaCartas-
* Função que consulta quantas cartas ainda não foram jogadas
*/

int consultaCartas(Baralho *baralho){
  int cont = 0;

  for(int i = 0; i < 13; i++){
    for(int j = 0; j < 4; j++){
      if(baralho->matriz[i][j].foiJogada){
        cont++;
      }//if
    }//for int
  }//for ext

  return (52 - cont);

}

//----------------------------------------------------------------------------//

/*                           -carteado-
* Função que destribui três cartas ao jogador
*/

Carta* carteado(Baralho *baralho){
  int contador = 0, valor, naipe;
  time_t t;

  srand((unsigned) time(&t));
  //srand(time(NULL));

  //criar um vetor de cartas de três posições
  Carta *carta = malloc(3 * sizeof(Carta));

  //repetir até que três cartas não jogadas tenham sido selecionadas pelo rand
  while(contador != 3){

    valor = rand() % 14;
    naipe = rand() % 4;
    //caso ela não tenha sido jogada, adicionar no vetor e marcar como true
    if(!baralho->matriz[valor][naipe].foiJogada){
      baralho->matriz[valor][naipe].foiJogada = true;
      carta[contador] = baralho->matriz[valor][naipe];
      contador++;
    }
  }
  //retornar a o endereço da primeira posição do vetor
  return carta;
}

//----------------------------------------------------------------------------//

/*                           -printBaralho-
* Função que imprimi as cartas do baralho.
*/

void printBaralho(Baralho *baralho){
  for(int i = 0; i < 13; i++){
    for(int j = 0; j < 4; j++){
      //printf("Valores: %c\n", baralho->matriz[i][j].valor);
      printf("[%c %c %d] ", baralho->matriz[i][j].valor,  baralho->matriz[i][j].naipe, baralho->matriz[i][j].foiJogada);
    }
    printf("\n");
  }
  printf("\n");
}

//----------------------------------------------------------------------------//

/*                           -topo-
* Função que retorna uma carta aleatoria do topo.
*/

Carta topo(Baralho *baralho){

  int contaCarta = 0, valor, naipe;
  Carta topo;

  srand(time(NULL));

  while(contaCarta != 1){
    valor = rand() % 12;
    naipe = rand() % 3;
    if(!baralho->matriz[valor][naipe].foiJogada){
      topo = baralho->matriz[valor][naipe];
      baralho->matriz[valor][naipe].foiJogada = true;
      contaCarta++;
    }
  }
  return topo;
}
//----------------------------------------------------------------------------//

/*                           -fundo-
* Função que retorna uma carta aleatoria do fundo.
*/

Carta fundo(Baralho *baralho){

  int contaCarta = 0, valor, naipe;
  Carta fundo;

  srand(time(NULL));

  while(contaCarta != 1){
    valor = rand() % 12;
    naipe = rand() % 3;
    if(!baralho->matriz[valor][naipe].foiJogada){
      fundo = baralho->matriz[valor][naipe];
      baralho->matriz[valor][naipe].foiJogada = true;
      contaCarta++;
    }
  }
  return fundo;
}

//----------------------------------------------------------------------------//

/*                           -exibeMenu-
* Método que exibe menu.
*/

void exibeMenu(){
  printf("|---------- Menu Jogo de Baralho ----------|\n");
  printf("|----------- 1 - Imprimi cartas -----------|\n");
  printf("|--------- 2 - Distribuir Cartas ----------|\n");
  printf("|------- 3 - Verificar Carta no Topo ------|\n");
  printf("|------- 4 - Verificar Carta Fundo --------|\n");
  printf("|----- 5 - Exibir Quantidade de cartas ----|\n");
  printf("|----------- 6 - Resetar Baralho ----------|\n");
  printf("|------------- 7 - Limpar tela ------------|\n");
  printf("|------------- 8 - Menu do Jogo -----------|\n");
  printf("|------------ -1 - Sair do Jogo -----------|\n\n");
}

//----------------------------------------------------------------------------//

int main(){

  int qCartas, opcao;
  Baralho baralho;
  Carta *ptr, vTopo, Vfundo;

  criaBaralho(&baralho);
  exibeMenu();

  do{

    printf("Insira a opção desejada: ");
    scanf("%i", &opcao);

    printf("\n");

    switch(opcao){

      case 1:
        printBaralho(&baralho);
      break;//Exibe o baralho

      case 2:
        ptr = carteado(&baralho);

        for(int i = 0; i < 3; i++){
          printf("[%c %c]\n", ptr[i].valor, ptr[i].naipe);
        }
        printf("\n");
      break;//Sorteia 3 cartas do baralho

      case 3:
      vTopo = topo(&baralho);
      printf("A carta do topo é [%c][%c]\n\n", vTopo.valor, vTopo.naipe);
      break;//retira uma carta do topo

      case 4:
      Vfundo = fundo(&baralho);
      printf("A carta do fundo é [%c][%c]\n\n", Vfundo.valor, Vfundo.naipe);
      break;//retira uma carta do fundo

      case 5:
        qCartas = consultaCartas(&baralho);
        printf("O baralho tem %i cartas disponiveis para jogo! \n\n", qCartas);
      break;//exibe a quantidade de cartas no baralho

      case 6:
      resetaCartas(&baralho);
      printf("Baralho resetado com sucesso!\n\n");
      break;//reseta o baralho

      case 7:
        system("clear");
      break;//limpa a tela

      case 8:
        exibeMenu();
      break;

      case -1:
        printf("Obrigado por jogar!\nSaindo!\n\n");
      break;//Sai do jogo

      default:
        printf("Opção Invalida!\n\n");
      break;//caso opçao invalida

    }//switch
  }while(opcao != -1);

  return 0;
}
