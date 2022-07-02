#include <stdio.h>

void NumDecrescente(int n){

  if(n >= 0){
    if(n % 2 == 0)
      printf("\n%d\n ", n);
      NumDecrescente(n - 1);
  }
}

int main(){

  int num;

  puts("Informe um número :");
  scanf("%d", &num);
  puts("Seus antecessores pares de forma decrescente:");

  NumDecrescente(num);

  return 0;
}