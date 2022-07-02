#include <stdio.h>

void Numcrescente(int n){

  if(n >= 0){
    Numcrescente(n - 1);
    printf("\n%d\n ", n);
  }
}

int main(){

  int num;

  printf("Informe um número para imprimir seus antecessores de forma crescente:\n");
  scanf("%d", &num);

  Numcrescente(num);

  return 0;
}