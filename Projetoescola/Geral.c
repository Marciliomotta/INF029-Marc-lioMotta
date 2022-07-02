#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Geral.h"
#include "aluno.h"
#include "Professores.h"
#include "Disciplinas.h"
#include "MenuOpcoes.h"
#include "Validacoes.h"

//Essa função busca uma string e verifica 
//se essa string é substring do nome (professor e aluno)
boolean existe(listaAlunos *listaA, listaProf *listaP){
        
    int aux;
    int ok = 0;

  char test[TAM_NOME];
  
  do{
    fflush(stdin);
    getchar();
    printf("Informe quem deseja buscar: ");
    scanf("%s", test);
    if(strlen(test) < 3)
      puts("Digite pelo menos 3 caracteres!");
  } while (strlen(test) < 3);
        
    printf("\n");   

  if(listaAlunosVazia(listaA) && listaProfVazia(listaP)){
    puts("É necessario ocorrer um cadastro primeiro!");
    return false;
  }  
  // Verifica só a lista de alunos
  else if (!listaAlunosVazia(listaA) && listaProfVazia(listaP)) {      
       
       //Laço mais externo que vai variar os nomes
       //Se o parâmetro de busca for maior que o nome, ele sai
        for(int qtd = 0; qtd < listaA -> qtdAlunos; qtd++){        
            if( strlen(test) > strlen(listaA -> alunos[qtd].nome) ){
                return false;
            }
            //Se o parâmetro de busca for igual ao nome, imprime
            if( strcmp(test,listaA -> alunos[qtd].nome) == 0 ){
                printf("Nome: %s\nMatricula: %d\n\n",listaA -> alunos[qtd].nome, 
                                                     listaA -> alunos[qtd].matricula);
                
            }
            /*Verifica se a sequência de caracteres do parâmetro
               está contida em algum lugar da string nome*/                          
             int teste[ strlen(listaA -> alunos[qtd].nome) ];  
              for(int i = 0; i <= strlen(listaA -> alunos[qtd].nome) - strlen(test); i++){
                  if(listaA -> alunos[qtd].nome[i] == test[0]){
                                          
                      for(int k=0;k<strlen(test);k++)
                          teste[k]=0;

                      aux=i;
                      for(int j=0;j<strlen(test);j++){                        
                          if(test[j] == listaA -> alunos[qtd].nome[aux]){
                              teste[j]=1;
                              aux++;
                          }
                      }

                      ok = 1;
                      for(int m=0;m<strlen(test);m++){
                          if(teste[m]==0){
                              ok= -1;
                          }
                      }
                      
                      if( ok == 1 ){
                        printf("Nome: %s\nMatricula: %d\n\n",listaA -> alunos[qtd].nome, 
                                                             listaA -> alunos[qtd].matricula);
                        
                      }
                  }
              }    
            
        }         
    }// Verifica só a lista de professor
    else if (listaAlunosVazia(listaA) && !listaProfVazia(listaP)) {
      
      //Laço mais externo que vai variar os nomes
      //Se o parâmetro de busca for maior que o nome, ele sai
      for(int qtd = 0; qtd < listaP -> qtdProfessores; qtd++) {
            if( strlen(test) > strlen(listaP -> professores[qtd].nome) ){
                return false;
            }
            //Se o parâmetro de busca for igual ao nome, imprime
            if( strcmp(test,listaP -> professores[qtd].nome) == 0 ){
                printf("Nome: %s\nCPF: %s\n\n",listaP -> professores[qtd].nome, 
                                             listaP -> professores[qtd].cpf);
                
            }  
              /*Verifica se a sequência de caracteres do parâmetro
                  está contida em algum lugar da string nome*/       
              int teste[ strlen(listaP -> professores[qtd].nome) ];  
              for(int i = 0; i <= strlen(listaP -> professores[qtd].nome) - strlen(test); i++){
                  if(listaP -> professores[qtd].nome[i] == test[0]){

                      for(int k=0;k<strlen(test);k++)
                          teste[k]=0;

                      aux=i;
                      for(int j=0;j<strlen(test);j++){
                          if(test[j] == listaP -> professores[qtd].nome[aux]){
                              teste[j]=1;
                              aux++;
                          }
                      }

                      ok = 1;
                      for(int m=0;m<strlen(test);m++){
                          if(teste[m]==0){
                              ok= -1;
                          }
                      }

                      if( ok == 1){
                        printf("Nome: %s\nCPF: %s\n\n",listaP -> professores[qtd].nome, 
                                                      listaP -> professores[qtd].cpf);
                          
                      }
                  }
              }    
            
        }            
    }// Verifica ambas as listas
    else {                 

        /*Executa a busca na [LISTA ALUNO] e na [LISTA PROFESSOR]
seguindo o mesmo padrao da busca [apenas de aluno] e [apenas de professor]*/
        for(int qtd = 0; qtd < listaA -> qtdAlunos; qtd++) {
            if( strlen(test) > strlen(listaA -> alunos[qtd].nome) ){
                return false;
            }

            if( strcmp(test,listaA -> alunos[qtd].nome) == 0 ){
                printf("Nome: %s\nMatricula: %d\n\n",listaA -> alunos[qtd].nome, 
                                                     listaA -> alunos[qtd].matricula);
                
            }                      
             int teste[ strlen(listaA -> alunos[qtd].nome) ];  
              for(int i = 0; i <= strlen(listaA -> alunos[qtd].nome) - strlen(test); i++){
                  if(listaA -> alunos[qtd].nome[i] == test[0]){
                                          
                      for(int k=0;k<strlen(test);k++)
                          teste[k]=0;

                      aux=i;
                      for(int j=0;j<strlen(test);j++){                        
                          if(test[j] == listaA -> alunos[qtd].nome[aux]){
                              teste[j]=1;
                              aux++;
                          }
                      }

                      ok= 1;
                      for(int m=0;m<strlen(test);m++){
                          if(teste[m]==0){
                              ok= -1;
                          }
                      }

                      if( ok == 1 ){
                        printf("Nome: %s\nMatricula: %d\n\n",listaA -> alunos[qtd].nome, 
                                                             listaA -> alunos[qtd].matricula);
                          
                      }
                  }
              }    
            
        }         
           
        for(int qtd = 0; qtd < listaP -> qtdProfessores; qtd++) {
            if( strlen(test) > strlen(listaP -> professores[qtd].nome) ){
                return false;
            }

            if( strcmp(test,listaP -> professores[qtd].nome) == 0 ){
                printf("Nome: %s\nCPF: %s\n\n",listaP -> professores[qtd].nome, 
                                             listaP -> professores[qtd].cpf);
                
            }           
              int teste[ strlen(listaP -> professores[qtd].nome) ];  
              for(int i = 0; i <= strlen(listaP -> professores[qtd].nome) - strlen(test); i++){
                  if(listaP -> professores[qtd].nome[i] == test[0]){

                      for(int k=0;k<strlen(test);k++)
                          teste[k]=0;

                      aux=i;
                      for(int j=0;j<strlen(test);j++){
                          if(test[j] == listaP -> professores[qtd].nome[aux]){
                              teste[j]=1;
                              aux++;
                          }
                      }

                      ok= 1;
                      for(int m=0;m<strlen(test);m++){
                          if(teste[m]==0){
                              ok= -1;
                          }
                      }

                      if( ok == 1){
                        printf("Nome: %s\nCPF: %s\n\n",listaP -> professores[qtd].nome, 
                                                      listaP -> professores[qtd].cpf);
                          
                      }
                  }
              }    
            
        }                
    }
    return false;
}

void AniversarioMes(listaProf *listaP, listaAlunos *listaA){
  int mes, quantidadeAniv=0;

  time_t mytime;
  mytime = time(NULL);
  struct tm tm = *localtime(&mytime);

  for (int i = 0; i < listaP -> qtdProfessores; i++) {
      mes = (listaP -> professores[i].nascimento[3] - '0') * 10 + (listaP -> professores[i].nascimento[4] - '0');
      if(mes == (tm.tm_mon+1)){
        puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
        puts("-=-=-=-Professor-=-=-=-");
        printf("Nome: %s\n", listaP -> professores[i].nome);
        printf("Data de Nascimento: %s\n", listaP -> professores[i].nascimento);
        puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
        quantidadeAniv++;
      }
    }
  for (int i = 0; i < listaA -> qtdAlunos; i++) {
      mes = (listaA -> alunos[i].nascimento[3] - '0') * 10 + (listaA -> alunos[i].nascimento[4] - '0');
      if(mes == (tm.tm_mon+1)){
      puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
      puts("-=-=-=-Aluno-=-=-=-");
      printf("Nome: %s\n", listaA -> alunos[i].nome);
      printf("Data de Nascimento: %s\n", listaA -> alunos[i].nascimento);
      puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
      quantidadeAniv++;
      }
        }
  if ((listaP -> qtdProfessores == 0) || (listaA -> qtdAlunos == 0))
    puts("É necessario ocorrer um cadastro primeiro!");
  else if (quantidadeAniv==0)
    puts("Não ocorrerá nenhum aniversário neste mês");
}
