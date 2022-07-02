#include<stdio.h>

int Expoente(int k, int n){

	if(n > 0)
		return k * Expoente(k, n - 1);
	else
		return 1;
}


int main(){

	int n1, n2, resultado;
	
	printf("Informe um número :\n");
	scanf("%d", &n1);
  printf("Informe seu expoente :\n");
	scanf("%d", &n2);

	printf("%d elevado a %d é  %d", n1, n2, resultado = Expoente(n1, n2));

	return 0;
}
