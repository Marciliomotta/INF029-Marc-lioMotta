#include <stdio.h>

void NumCrescente(int n){

  if(n >= 0){
    NumCrescente(n - 1);
      if(n % 2 == 0)
      printf("\n%d\n", n);
  }
}

int main(){

  int num;

  printf("Informe um número para imprimir seus antecessores pares de forma crescente:\n");
  scanf("%d", &num);

  NumCrescente(num);

  return 0;
}
