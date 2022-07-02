// Marcílio Motta- 20201160043
#include <stdio.h>
#include <stdlib.h>
#define TAM 10
#include "EstruturaVetores.h"

typedef struct {
  int *vetPrincipal;
  int qtdElemento;
  int tamAux; 
} Vetor;

Vetor vetor[TAM];

void inicializar(){
  int i;
  for(i = 0; i < TAM ; i++){
    vetor[i].vetPrincipal = NULL;
  }
}

int criarEstruturaAuxiliar(int posicao, int tamanho){
  
  int i; 
  if(vetor[posicao].vetPrincipal != NULL)
    return JA_TEM_ESTRUTURA_AUXILIAR;
  else if (posicao > 10 || posicao < 1)
    return POSICAO_INVALIDA;
  else if(tamanho < 1)
    return TAMANHO_INVALIDO;
  else {
    vetor[posicao].vetPrincipal = (int*) malloc(tamanho * sizeof(int));
    vetor[posicao].tamAux = tamanho;
    vetor[posicao].qtdElemento = 0;
    
    return SUCESSO;
    }
}

int inserirNumeroEmEstrutura(int posicao, int valor){
    
  int i, j, retorno, ret;

  ret = ehPosicaoValida(posicao);
  if(ret == POSICAO_INVALIDA)
    retorno = POSICAO_INVALIDA;
  else{ 
    if(vetor[posicao].vetPrincipal != NULL){
      if(vetor[posicao].qtdElemento < vetor[posicao].tamAux){
        vetor[posicao].vetPrincipal[vetor[posicao].qtdElemento] = valor;
        vetor[posicao].qtdElemento ++;    
        retorno = SUCESSO;
      }
      else{
        retorno = SEM_ESPACO;
      }
    } 
    else{
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }

  return retorno;
}


int excluirNumeroDoFinaldaEstrutura(int posicao){
  
  int retorno, ret;

  ret = ehPosicaoValida(posicao);
  if(ret == POSICAO_INVALIDA)
    retorno = POSICAO_INVALIDA;
  else{
    if(vetor[posicao].vetPrincipal != NULL) {
      if(vetor[posicao].qtdElemento > 0){
        vetor[posicao].qtdElemento --;    
        retorno = SUCESSO;
      }
      else{
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
      }
    } 
    else{
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }
  return retorno;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor){
  
  int i, retorno, encontrado, ret;
  
  ret = ehPosicaoValida(posicao);
  if(ret == POSICAO_INVALIDA)
    retorno = POSICAO_INVALIDA;
  else{ 
    if(vetor[posicao].vetPrincipal != NULL){
      if(vetor[posicao].qtdElemento > 0){
        for(i= 0, encontrado= 0; i < vetor[posicao].qtdElemento && encontrado == 0; i++){
          if(valor == vetor[posicao].vetPrincipal[i])
            encontrado = 1;   
        }
        if (encontrado == 1){
          for(i= i-1; i< vetor[posicao].qtdElemento; i++){
            vetor[posicao].vetPrincipal[i] = vetor[posicao].vetPrincipal[i+1];
          }
          vetor[posicao].qtdElemento--;
          retorno = SUCESSO;
        }
        else 
        retorno = NUMERO_INEXISTENTE;
      }
      else{
      retorno = ESTRUTURA_AUXILIAR_VAZIA;
      }
    } 
    else{
    retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }
  return retorno;
}

int ehPosicaoValida(int posicao){
  
    int retorno = 0;
    if(posicao < 1 || posicao > 10){
      retorno = POSICAO_INVALIDA;
    }
    else
      retorno = SUCESSO;
    return retorno;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
  
  int i, retorno, ret;
  
  ret = ehPosicaoValida(posicao);
  if(ret == POSICAO_INVALIDA)
    retorno = POSICAO_INVALIDA;
  else{ // verificar se já existe a estrutura auxiliar
    if(vetor[posicao].vetPrincipal != NULL){
      if(vetor[posicao].qtdElemento > 0){
        for(i= 0; i< vetor[posicao].qtdElemento; i++){
         vetorAux[i] = vetor[posicao].vetPrincipal[i];
        }
        retorno = SUCESSO;
      }
    }       
    else{
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }
  
  return retorno;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){
  
  int i, j, retorno, auxiliar, ret;
    
  ret = ehPosicaoValida(posicao);
  if(ret == POSICAO_INVALIDA)
    retorno = POSICAO_INVALIDA;
  else{ 
    if(vetor[posicao].vetPrincipal != NULL){
      if(vetor[posicao].qtdElemento > 0){
        for(i= 0; i< vetor[posicao].qtdElemento; i++)
          vetorAux[i] = vetor[posicao].vetPrincipal[i];
        for(i= 0; i < vetor[posicao].qtdElemento; i++){
          for(j= i + 1; j < vetor[posicao].qtdElemento; j++){
            if(vetorAux[i] > vetorAux[j]){
              auxiliar = vetorAux[i];
              vetorAux[i] = vetorAux[j];
              vetorAux[j] = auxiliar;
            }
          }
        }
        retorno = SUCESSO;
      }
    }         
    else{
      retorno = SEM_ESTRUTURA_AUXILIAR;
    }
  }
  return retorno;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){

  int i, contador= 0;
  int j, retorno;
  
  for(i= 0; i< TAM; i++){
    if(vetor[i].vetPrincipal != NULL){
      if(vetor[i].qtdElemento > 0){
       // jogando valores no vetor aux
        for(j= 0; j< vetor[i].qtdElemento; j++){
          vetorAux[contador] = vetor[i].vetPrincipal[j];
          contador++;
        }
      }
    }
  }
  if(contador> 0)
    retorno = SUCESSO;
  else
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  return retorno;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){

  int i, auxiliar, contador = 0;
  int j, retorno = 0;
  
  for(i = 0; i< TAM; i++){
    if(vetor[i].vetPrincipal != NULL){
      if(vetor[i].qtdElemento > 0){
       // jogando valores no vetor aux
        for(j= 0; j< vetor[i].qtdElemento; j++){
          vetorAux[contador] = vetor[i].vetPrincipal[j];
          contador++;
        }
      }
    }
  }

  if(contador>0){
    for(i= 0; i< contador; i++){
      for(j= i + 1; j< contador; j++){
        if(vetorAux[i] > vetorAux[j]){
          auxiliar = vetorAux[i];
          vetorAux[i] = vetorAux[j];
          vetorAux[j] = auxiliar;
        }
      }
    }
  }
  
  if(contador > 0)
    retorno = SUCESSO;
  else
    retorno = TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
  
  return retorno;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){
  
  int ret, retorno = 0;
  novoTamanho = novoTamanho + vetor[posicao].tamAux;

  ret = ehPosicaoValida(posicao);
  if(ret == POSICAO_INVALIDA)
    retorno = POSICAO_INVALIDA;
  else{
    if(novoTamanho< 1){
      retorno = NOVO_TAMANHO_INVALIDO;
      return retorno;
    }
    if(vetor[posicao].vetPrincipal != NULL){
      vetor[posicao].vetPrincipal = realloc(vetor[posicao].vetPrincipal, (novoTamanho * sizeof(int)));
      if(!vetor[posicao].vetPrincipal)
            retorno = SEM_ESPACO_DE_MEMORIA;
      else{
        vetor[posicao].tamAux = novoTamanho;
        if(vetor[posicao].tamAux < vetor[posicao].qtdElemento)
          vetor[posicao].qtdElemento = vetor[posicao].tamAux;
        retorno = SUCESSO;
      }
    }       
    else
      retorno = SEM_ESTRUTURA_AUXILIAR;
  }
  
  return retorno;
}


int getQuantidadeElementosEstruturaAuxiliar(int posicao){
  
  int ret, retorno = 0;

  ret = ehPosicaoValida(posicao);
  if(ret == POSICAO_INVALIDA)
    retorno = POSICAO_INVALIDA;
  else{
    if(vetor[posicao].vetPrincipal != NULL){
      if (vetor[posicao].qtdElemento > 0){
        if (vetor[posicao].tamAux < vetor[posicao].qtdElemento)
          vetor[posicao].qtdElemento = vetor[posicao].tamAux;
        retorno = vetor[posicao].qtdElemento;
      }
      else 
        retorno = ESTRUTURA_AUXILIAR_VAZIA;
    }
    else
      retorno = SEM_ESTRUTURA_AUXILIAR;
  } 
  return retorno;
}

void inserirNoFinal(No *inicio, int val){
		No* novo = (No*)malloc(sizeof(No));
  	novo->conteudo = val;
  	novo->prox = NULL;
  	  if(inicio->prox == NULL){
  		inicio->prox = novo;
  	}else{
		  while(inicio->prox != NULL)
  			inicio = inicio->prox;
      inicio->prox = novo;
	}
}

No *montarListaEncadeadaComCabecote()
{
  int i, j, retorno=0, aux=0;
  No *cabecote = (No*) malloc(sizeof(No));  
  for (i = 0; i < TAM; i++){
    if (vetor[i].vetPrincipal != NULL){ 
      if (vetor[i].qtdElemento > 0){
        aux++;
        for (j = 0; j < vetor[i].qtdElemento; j++)
        {
          inserirNoFinal(cabecote, vetor[i].vetPrincipal[j]); 
        }
      }
    }
  }
  if (aux > 0)
    return cabecote;
  else
    return NULL;
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
  {
  No *leitor;
  int i = 0;
  for (leitor = inicio->prox; leitor != NULL; leitor = leitor->prox){
    vetorAux[i] = leitor->conteudo;
    i++;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio)
{
  No* atual = *inicio;
	No* tmp;

	while(atual != NULL){
		tmp = atual->prox;
		free(atual);
		atual = tmp;
	}

  *inicio = NULL;
}

void finalizar()
{
  int i;
  for(i= 0; i< TAM; i++){
    if(vetor[i].vetPrincipal != NULL)
        free (vetor[i].vetPrincipal);
  }
}