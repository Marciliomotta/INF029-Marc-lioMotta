// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  Cada aluno deve renomear esse arquivo para Aluno<MATRICULA>.c
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Marcílio Motta
//  email: marciliolima597@gmail.com 
//  Matrícula: 20201160043
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016

// #################################################

#include <stdio.h>
#include "MarcilioMotta20201160043.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int somar(int x, int y)
{  
    int soma;
    soma = x + y;
    return soma;
}
int fatorial(int x)
{ 
  int i, fat =1;
    
  for (i= x; i>1; i--)
    fat = fat*i;
  return fat;
}
int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;
    return val;
}

// Q1 = validar data

DataQuebrada quebraData(char data[]);

int q1(char data[])
{
  int datavalida = 1;
  
  DataQuebrada dq = quebraData(data);
  
  if(dq.valido == 0) 
    datavalida = 0;
  else{
    if (dq.iMes ==4 || dq.iMes ==6 || dq.iMes == 9 || dq.iMes == 11){
      if (dq.iDia > 30 || dq.iDia < 1)
        datavalida = 0;
    }else if (dq.iMes == 2){
      if (dq.iAno% 4 == 0 && (dq.iAno % 100!= 0 || dq.iAno % 400== 0)){
        if(dq.iDia > 29 || dq.iDia < 1)
          datavalida = 0;
      }else{
        if(dq.iDia > 28 || dq.iDia < 1)
          datavalida = 0;
      }      
    }else{
      if (dq.iDia > 30 || dq.iDia < 1)
        datavalida = 0;
    } 
  } 

if (datavalida == 1)
      return 1;
  else
      return 0;
}

DataQuebrada quebraData(char data[]){
  
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i;

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ 
		sDia[i] = '\0'; 
	}else{
		dq.valido = 0;
    return dq;
  }

  for (i = 0;sDia[i]!='\0';i++){  
    if(sDia[i] >= ':' || sDia[i] <= '/' ){ 
      dq.valido = 0;
      return dq;
    }
  }	

	int j = i + 1; 
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ 
		sMes[i] = '\0';  
	}else{
		dq.valido = 0;
    return dq;
  }
  
  for (i = 0;sMes[i]!= '\0';i++){
    if(sMes[i] >= ':'|| sMes[i] <= '/'){ 
  		dq.valido = 0;
      return dq;
    }
  }
  
	j = j + 1; 
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){
		sAno[i] = '\0';  
	}else{
		dq.valido = 0;
    return dq;
  }
  
  for (i = 0;sAno[i]!= '\0';i++){
    if(sAno[i] >= ':'|| sAno[i] <= '/'){ 
  		dq.valido = 0;
      return dq;
    }
  } 
  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

  if (dq.iMes >12 || dq.iMes < 1)
    dq.valido = 0;
  else
  	dq.valido = 1;

  return dq;
}

int qtdDiasMesFinal(int mes, int ano);

//  Q2 = diferença entre duas datas

DiasMesesAnos q2(char datainicial[], char datafinal[])
{
  DiasMesesAnos dma;

  DataQuebrada dqInicial = quebraData(datainicial);
  DataQuebrada dqFinal = quebraData(datafinal);

  if (q1(datainicial) == 0){
    dma.retorno = 2;
    return dma;
  }else if (q1(datafinal) == 0){
    dma.retorno = 3;
    return dma;
  }else if (dqInicial.iAno > dqFinal.iAno){
    dma.retorno = 4;
    return dma;
  }else if ((dqInicial.iAno == dqFinal.iAno) && (dqInicial.iMes > dqFinal.iMes)){
    dma.retorno = 4;
    return dma;
  }else if((dqInicial.iAno == dqFinal.iAno) && (dqInicial.iMes == dqFinal.iMes) && (dqInicial.iDia > dqFinal.iDia)){   
    dma.retorno = 4;
    return dma;
  }else{
    if (dqFinal.iDia >= dqInicial.iDia){
      dma.qtdDias = dqFinal.iDia - dqInicial.iDia;
    }else{
      dma.qtdDias = dqFinal.iDia - dqInicial.iDia + qtdDiasMesFinal(dqFinal.iMes - 1, dqFinal.iAno);
    }
    if(dqFinal.iMes >= dqInicial.iMes && dqFinal.iDia >= dqInicial.iDia){
      dma.qtdMeses = dqFinal.iMes - dqInicial.iMes;
    }else if(dqFinal.iMes >= dqInicial.iMes && dqFinal.iDia < dqInicial.iDia){
      dma.qtdMeses = dqFinal.iMes - dqInicial.iMes - 1;
    }else if (dqFinal.iMes < dqInicial.iMes && dqFinal.iDia >= dqInicial.iDia){
      dma.qtdMeses = dqFinal.iMes - dqInicial.iMes + 12;
    }else if (dqFinal.iMes < dqInicial.iMes && dqFinal.iDia < dqInicial.iDia){
      dma.qtdMeses = dqFinal.iMes - dqInicial.iMes + 12 - 1;
    } 
    if (dqFinal.iMes >= dqInicial.iMes || (dqFinal.iMes == dqInicial.iMes && dqFinal.iDia > dqInicial.iDia)){
      dma.qtdAnos = dqFinal.iAno - dqInicial.iAno;
    }else{
      dma.qtdAnos = dqFinal.iAno - dqInicial.iAno - 1;
    }
      
  dma.retorno = 1;
  return dma;
      
  }    
}

int qtdDiasMesFinal(int mes, int ano)
{
  
  if (mes == 0 || mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12) {
    return 31;
  } 
  if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
    return 30;
  } 
  if (mes == 2 && ano % 4 != 0) {
    return 28;
  } 
  if (mes == 2 && ano % 4 == 0 && (ano % 100!= 0 || ano % 400 == 0)) {
    return 29;
  } 
}

//  Q3 = encontrar caracter em texto

int q3(char *texto, char c, int isCaseSensitive)
{
  int qtdOcorrencias = 0;
  int i;
  
  if(isCaseSensitive){
    for (i= 0; i < strlen(texto); i++){
      if(texto[i]== c)
        qtdOcorrencias++;
    }
  }
  else{ 
    for (i= 0; i < strlen(texto); i++){
      if((toupper(texto[i]) == toupper(c)))
        qtdOcorrencias++;
    }
  }
    return qtdOcorrencias;
}

//  Q4 = encontrar palavra em texto

int comparacaoTextos(char busca[], char texto[], int j);

int q4(char strTexto[], char strBusca[], int posicoes[30])
{
  int qtdOcorrencias = 0, i, j = 0;

  for(i = 0; i < strlen(strTexto); i++){
    if(strTexto[i] == strBusca[0] ){
      if(comparacaoTextos(strBusca, strTexto, i) == 1){
        qtdOcorrencias++;
        posicoes[j] = i+1;
        posicoes[j+1] = i+strlen(strBusca);
        j += 2;  
      }
    }
  }
  return qtdOcorrencias;
}

int comparacaoTextos(char busca[], char texto[], int j)
{
  int i;

  for(i = 0; i < strlen(busca); i++){
    if(busca[i] != texto[j]){
      return 0;
    }
      j++;
  }
    return 1;
}

//  Q5 = inverte número

int q5(int num)
{  
  int base, inverso = 0;
  
  if (num >= 0){
    do{
      base = num % 10;
      inverso = inverso * 10 + base;
      num = num / 10;
      
    }while(num > 0);
    
  }else if (num < 1){
    num = num *-1;
    do{
      base = num % 10;
      inverso = inverso * 10 + base;
      num = num / 10;
      
    }while(num != 0);

    num = num * -1;
  }
    return inverso;
}

//  Q6 = ocorrência de um número em outro

int q6(int numerobase, int numerobusca)
{
  int qtdOcorrencias = 0;
  int restoNumerobase;
  int tamanhoBase10 = 1;
  int numerobuscatemporario = numerobusca;
  
  while (numerobuscatemporario > 1){
    numerobuscatemporario = numerobuscatemporario / 10;
    tamanhoBase10 = tamanhoBase10 * 10;
  }
  
  if (numerobase > 0){
    restoNumerobase = numerobase % tamanhoBase10;
    if (restoNumerobase == numerobusca){
      qtdOcorrencias ++;
      numerobase = numerobase / tamanhoBase10;
    }else{
      numerobase = numerobase / 10;
      }
    return qtdOcorrencias + q6(numerobase, numerobusca);
  }
  return qtdOcorrencias;
}