#include <stdio.h>

int pell(int n);

int main(){
  int num = 0;
  printf("Favor inserir um número:\n");
  scanf("%d", &num);
  printf("O número na posiçÃo %d da sequência de Pell é: %d", num, pell(num));
}

int pell(int n){
  if (n == 0){
    return 0;
  }else if (n == 1){
    return 1;
  }else
    return (2*pell(n-1)) + pell(n-2);
}