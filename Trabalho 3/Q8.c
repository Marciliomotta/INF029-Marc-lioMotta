#include <stdio.h>

int mdc(int x, int y);

int main(){

	int x, y;

	printf("Informe dois números para encontrar o MDC:\n");
	scanf("%d %d", &x, &y);

	printf("O MDC é %d", mdc(x, y));

	return 0;
}

int mdc(int x, int y){

	if(y == 0)
		return x;

	return mdc(y, x % y);
}