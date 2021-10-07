/*Um ponteiro pode ser usado para dizer a uma funcao onde ela deve depositar
o resultado de seus calculos. Escreva uma funcao que converta uma quantidade de minutos na notacao horas/minutos. A funcao recebe como parametro:
  • um numero inteiro (totalMinutos); e
  • os enderecos de duas variaveis inteiras, horas e minutos.
A funcao deve entao atribuir valores as variaveis passadas por referencia, de
modo que os valores atribuıdos respeitem as seguintes condicoes:
  •minutos < 60
  •60 ∗ horas + minutos = totalMinutos
Escreva tambem a funcao principal (main) que use a funcao desenvolvida.*/

//library
#include<stdlib.h>
#include<stdio.h>


//Função convertMinutos, usada para converter minutos para horas/minutos
void convertMinutos(int totalMinutos, int *hor, int *min){

  while(totalMinutos >= 60){
     *hor+= 1;
    totalMinutos -= 60;
  }
  *min = totalMinutos;
}

int main(){
  int totalMinutos;
  int hor = 0, min;

  printf("Insira o total de minutos: ");
  scanf("%i", &totalMinutos);

  convertMinutos(totalMinutos, &hor, &min);

  printf("%i:%i\n\n", hor, min);

  return 0;
}//main function
