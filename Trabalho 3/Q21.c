#include <stdio.h>

int tribonacci (int n);

int main(){
  int num = 0;
  printf("Informe um número:\n");
  scanf("%d", &num);
  printf("O termo na posição %d da sequência de Tribonacci é:", num);
  printf(" %d", tribonacci(num));
}

int tribonacci (int n){
  if (n == 0 || n == 1 ){
    return 0;
  }else if (n == 2){
    return 1;
  }else
    return tribonacci(n-1) + tribonacci(n-2) + tribonacci(n-3);
}