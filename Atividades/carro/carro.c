#include <stdio.h>
#define TAM_VETOR 50

typedef struct{
  char Marca[TAM_VETOR], Modelo[TAM_VETOR];
  int ano;
}Carro;

void leitor_dados(int *ano, char marca[], char modelo[]){
  printf("Digite o ano:\n");
  scanf("%d", ano); 
  printf("Informe a marca:\n");
  scanf("%s", marca);
  printf("Informe o modelo:\n");
  scanf("%s", modelo);
}

int main(){
  int ano;
  char marca[TAM_VETOR], modelo[TAM_VETOR];
  leitor_dados(&ano, marca, modelo);

  printf("O ano é: %d\n", ano);
  printf("A marca é: %s\n", marca);
  printf("O model é: %s\n", modelo);
  
}