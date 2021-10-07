/*Escreva uma função recursiva para calcular o valor de um número inteiro de base
x elevada a um expoente inteiro y.*/

//library
#include<stdlib.h>
#include<stdio.h>

int xelevadoy(int x, int y){

  if(y == 0)
    return 1;
  else
    return x * xelevadoy(x, y - 1);
}

int main(){

  int x, y;

  printf("Insira x: ");
  scanf("%i", &x);

  printf("Insira y: ");
  scanf("%i", &y);

  printf("%i elevado a %i = %i\n\n", x, y, xelevadoy(x, y));

  return 0;
}//main function
