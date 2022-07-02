#include <stdio.h>

int Fibonacci(int n);

int main(){

  int num, resultado;

  printf("Informe o N-ésimo número que quer saber da sequencia fibonacci: ");
  scanf("%d", &num);

  resultado = Fibonacci(num);
  printf("O termo solicitado é %d : ", resultado);
  
  return 0;
}

int Fibonacci(int n){
  if (n == 1) 
    return 0;
  if (n == 2 || n == 3)
    return 1;

  return Fibonacci(n - 2) + Fibonacci(n - 1); 
}