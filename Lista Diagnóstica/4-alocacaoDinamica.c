/*Faça um programa que leia um valor N e crie dinamicamente um
vetor com essa quantidade de elementos. Em seguida, passe esse vetor para uma
função que vai ler os elementos desse vetor. Depois, no programa principal, imprima os
valores do vetor preenchido. Além disso, antes de finalizar o programa, lembre-se
de liberar a área de memória alocada para armazenar os valores do vetor.*/

//library
#include<stdlib.h>
#include<stdio.h>

void preencheVetor(float *vtr, int *n){
  for(int i = 0; i < *n; i++){
    printf("Insira um valor para a posição %i do vetor: ", i+1);
    scanf("%f", &vtr[i]);
  }//for
}//procedimento que preenche vetor alocado dinamicamente

int main(){

  int n;
  float *vtr;

  printf("Insira um valor para n: ");
  scanf("%i", &n);

  vtr = (float *) malloc(n * sizeof(float));

  preencheVetor(vtr, &n);

  printf("\n\n");

  for(int i = 0; i < n; i++){
    printf("vetor[%i] = %.2f\n", i+1, vtr[i]);
  }

  free(vtr);
  vtr = NULL;

  printf("\n\n");

  return 0;
}//main function
