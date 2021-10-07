/*Defina um tipo abstrato de dados que irá representar bandas de música.
Essa estrutura deve ter o nome da banda, que tipo de música ela toca, o número de
integrantes, e em que posição do ranking essa banda está dentre as suas 5 bandas
favoritas.

a) Crie uma função para preencher as 5 estruturas de bandas criadas no exemplo passado;

b) Após criar e preencher, exiba todas as informações das bandas/estruturas. Não se
esqueça de usar o operador → para preencher os membros das structs;

c) Crie uma função que peça ao usuário um número de 1 até 5. Em seguida, seu programa
deve exibir informações da banda cuja posição no seu ranking é a que foi solicitada
pelo usuário.*/

//library
#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string.h>

typedef struct{
  char nomeBanda[16]; //Noma da banda
  char estilo[16];// Estilo musical
  int integrantes;// Numero de integrantes
  int posicao;// Posição da banda entre as preferidas
}Bandas;// Estrutura Banda


void preencheBanda(Bandas *banda){
  for(int i = 0; i < 5; i++){
    __fpurge(stdin);

    printf("Insira o nome da %iº banda: ", i+1);
    fgets(banda[i].nomeBanda, 16, stdin);
    banda[i].nomeBanda[strcspn(banda[i].nomeBanda, "\n")] = '\0';

    __fpurge(stdin);
    printf("Qual o estilo da %iº banda: ", i+1);
    fgets(banda[i].estilo, 16, stdin);
    banda[i].estilo[strcspn(banda[i].estilo, "\n")] = '\0';

    __fpurge(stdin);
    printf("Insira o número de integrantes da banda %i: ", i+1);
    scanf("%i", &banda[i].integrantes);

    printf("Qual a posição da banda %i entre as favoritas: ", i+1);
    scanf("%i", &banda[i].posicao);

    system("clear");

  }//for
}// preenche os dados das 5 bandas

void imprimeBandas(Bandas *banda){
  printf("------------------------------BANDAS------------------------------\n\n");
  for(int i = 0; i < 5; i++){
    printf("------------------------------------------------------------------\n");
    printf("A banda %i se chama: %s\n", i+1, banda[i].nomeBanda);
    printf("A banda %s toca %s\n", banda[i].nomeBanda, banda[i].estilo);
    printf("A banda %s tem %i membros\n", banda[i].nomeBanda, banda[i].integrantes);
    printf("A banda %s esta na posição %i entre as preferidas\n\n", banda[i].nomeBanda, banda[i].posicao);
  }
}// Exibe as Bandas inseridas pelo o Usuário

void imprimeEscolha(Bandas *banda){
  int escolha;

  do{
    printf("Insira a posição que deseja consultar: ");//2, 3, 4, 5
    scanf("%i", &escolha);

    system("clear");

    for(int i = 0; i < 5; i++){
      if(escolha == banda[i].posicao){
        printf("A banda da posição %i se chama: %s\n", escolha, banda[i].nomeBanda);
        printf("A banda %s toca %s\n", banda[i].nomeBanda, banda[i].estilo);
        printf("A banda %s tem %i membros\n", banda[i].nomeBanda, banda[i].integrantes);
      }
    }

  }while(escolha <= 1 && escolha >= 5);// Do/While
}// imprime a banda da posição que o usuário escolheu

int main(){

  Bandas banda[5];
  int verifica;

  preencheBanda(&banda[0]);
  imprimeBandas(&banda[0]);
  do{
    imprimeEscolha(&banda[0]);
    printf("\n\n");
    printf("Pressione 1 para continuar escolhendo: ");
    scanf("%i", &verifica);

  }while(verifica == 1);

  return 0;
}//main function
