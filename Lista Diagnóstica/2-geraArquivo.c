/*Faça um programa que receba do usuário um arquivo texto. Crie outro arquivo
texto de saída contendo o texto do arquivo de entrada original, porém substituindo
todas as vogais pelo caractere ‘*’. Além disso, mostre na tela quantas linhas esse
arquivo possui. Dentro do programa faça o controle de erros, isto é, insira comandos
que mostre se os arquivos foram abertos com sucesso, e caso contrário, imprima uma
mensagem de erro encerrando o programa*/

//library
#include<stdio.h>
#include<stdlib.h>
#include<stdio_ext.h>
#include<string.h>
#include<ctype.h>

int main(){

  FILE *arq;
  char arquivo[16], c, *str;
  int aux = 0, contalinha = 0;


  arq = fopen("arquivo", "r");

  if(arq == NULL){
    printf("Erro!\nFechando Programa\n\n");
    exit(1);
  }//verifica se houve um erro ao abrir o arquivo desejado

  str = (char*) malloc(1);

  while((c = fgetc(arq)) != EOF){
    c = toupper(c);


    /*estrutura if/else que verifica se a letra é uma vogal, caso seja atribui
    a str '*', caso contrario atribui a consoante ou '\n*/
    if(c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'){
      str[aux] = '*';
    }else{
      str[aux] = c;
    }

    /*verifica se o caractere é uma quebra de linha, caso seja é somado 1 à variavel
    que conta as linhas*/
    if(c == '\n'){
      contalinha++;
    }

    aux++;
    str = realloc(str, aux + 1);// realoca tamanho da str
  }//while,

  fclose(arq);

  arq = fopen("aGerado.txt", "w");//abre um arquivo ser gerado

  if(arq == NULL){
    printf("Erro!\nFechando Programa\n\n");
    exit(1);
  }//verifica se houve um erro ao abrir o arquivo desejado

  aux = fputs(str, arq);// atribui a str ao arquivo gerado
  free(str);

  if(aux == EOF){
    printf("Erro na gravação do arquivo\n\n");
  }//verifica se há erro na gravação do arquivo

  fprintf(arq, "Quantidade de linhas: %i", contalinha);

  fclose(arq);

  return 0;
}//main function
