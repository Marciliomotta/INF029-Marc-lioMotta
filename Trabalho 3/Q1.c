#include <stdio.h>

int fatorial (int n);

int main(){

  int num, resultado;

  printf("Informe o número que se quer calcular o fatorial: \n");
  scanf("%d", &num);

  resultado = fatorial(num);
  printf("O fatorial é %d", resultado);
  
  return 0;
}

int fatorial (int n){
  if(n == 1)
    return 1;
  else
    return n*fatorial(n-1);
}