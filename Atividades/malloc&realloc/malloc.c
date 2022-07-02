include <stdio.h>
include <stdlib.h>

int main(){
  int *p;
  int a, i;

  a= 30;
  p= malloc(a*sizeof(int));

  if(!p){
    printf("** Erro: Memoria Insuficciente **");
    exit;
  }

  
  
}