#include <stdio.h>

int Multip_Rec(int n1, int n2){
  
  if(n2 == 0)
    return 0;
  else
    return n1 + Multip_Rec(n1, n2-1);

}

int main() {
  
  int a, b;

  printf("Digite 2 números para a multiplicação: \n");
  scanf("%d%d", &a, &b);

  printf("%d", Multip_Rec(a,b));
  
  return 0;
}