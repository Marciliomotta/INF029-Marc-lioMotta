"Faça um programa que imprima o seu nome, sua matrícula, eo seu semestre de ingresso no curso. Cada informação em uma linha."
#include <stdio.h>

int main(){
  char Nome[9]= "Marcilio";
  int  matricula= 20201160043;
  float  semestre= 2020.1;

  printf("Meu nome: %s\nMinha matricula: %d\nSemestre: %f.1", Nome, matricula, semestre);
  
  return 0;
}