#include <stdio.h>

void Numdecrescente(int n){

  if(n >= 0){
    printf("\n%d\n", n);
    Numdecrescente(n - 1);
  }
}

int main(){

  int num;

  printf("Informe um número para imprimir seus antecessores de forma decrescente:\n");
  scanf("%d", &num);

  Numdecrescente(num);

  return 0;
}