#include <stdio.h>

int FatN(int n){
  if(n == 1)
    return 1;
  return n * FatN(n - 1);
}

int SuperFat(int n){
  if(n == 1)
      return 1;
  return FatN(n) * SuperFat(n - 1);
}

int main(){
  int num;

  printf("Informe um valor para calcular o superfatorial: \n");
  scanf("%d", &num);

  printf("O super fatorial de %d é %d\n", num, SuperFat(num));

  return 0;
}