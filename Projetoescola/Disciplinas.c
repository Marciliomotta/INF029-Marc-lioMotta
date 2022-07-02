#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Disciplinas.h"
#include "aluno.h"
#include "Professores.h"

listaDisc* criarListaDisc() {
    

    listaDisc *list;

    list = (listaDisc *) malloc(sizeof (listaDisc));

    if (list != NULL) {
        list -> qtdDisc = 0;
    }
 
    return list;
}

/*Protótipos de funções exclusivas de Disciplinas */
void imprimirProf(listaDisc *lista, int index);

// Função que insere o banco de dados das Disciplinas disponíveis
void inserirBancoDisciplinas(listaDisc *lista) {
    // Cadastrando a 1ª disciplina no banco de dados
    strcpy(lista -> disciplinas[0].nome, "Laboratório de Programação");
    strcpy(lista -> disciplinas[0].codigo, "LAB21");
    lista -> disciplinas[0].qtdSemestre = 5;
    lista -> disciplinas[0].qtdVagas = TAM_VAGAS;
    lista -> disciplinas[0].contVagas = 0;
    lista -> disciplinas[0].qtdResp = 0;

    // Cadastrando a 2ª disciplina no banco de dados
    strcpy(lista -> disciplinas[1].nome, "Metodologia de Pesquisa");
    strcpy(lista -> disciplinas[1].codigo, "MEP34");
    lista -> disciplinas[1].qtdSemestre = 4;
    lista -> disciplinas[1].qtdVagas = TAM_VAGAS;
    lista -> disciplinas[1].contVagas = 0;
    lista -> disciplinas[1].qtdResp = 0;

    // Cadastrando a 3ª disciplina no banco de dados
    strcpy(lista -> disciplinas[2].nome, "Estrutura de Dados e Algoritmos");
    strcpy(lista -> disciplinas[2].codigo, "EDA14");
    lista -> disciplinas[2].qtdSemestre = 7;
    lista -> disciplinas[2].qtdVagas = TAM_VAGAS;
    lista -> disciplinas[2].contVagas = 0;
    lista -> disciplinas[2].qtdResp = 0;

    // Cadastrando a 4ª disciplina no banco de dados
    strcpy(lista -> disciplinas[3].nome, "Arquitetura de Computadores");
    strcpy(lista -> disciplinas[3].codigo, "AC07");
    lista -> disciplinas[3].qtdSemestre = 3;
    lista -> disciplinas[3].qtdVagas = TAM_VAGAS;
    lista -> disciplinas[3].contVagas = 0;
    lista -> disciplinas[3].qtdResp = 0;

    // Cadastrando a 5ª disciplina no banco de dados
    strcpy(lista -> disciplinas[4].nome, "Disciplina Optativa");
    strcpy(lista -> disciplinas[4].codigo, "DO51");
    lista -> disciplinas[4].qtdSemestre = 1;
    lista -> disciplinas[4].qtdVagas = TAM_VAGAS;
    lista -> disciplinas[4].contVagas = 0;
    lista -> disciplinas[4].qtdResp = 0;
}

// Função que imprime os Professores cadastrados em determinada Disciplina
void imprimirProf(listaDisc *lista, int index) {
    if (lista -> disciplinas[index].qtdResp == 0) {
        printf("\tNão há Professor Cadastrado!\n");
    } else if (lista -> disciplinas[index].qtdResp == 1) {
        printf("Professor(a): %s\n", lista -> disciplinas[index].responsavel[0].nome);
    } else {
        printf("Professores(as): %s e %s\n", lista -> disciplinas[index].responsavel[0].nome,
                                            lista -> disciplinas[index].responsavel[1].nome);
    }
}

// Função que mostra o menu de disciplinas para Professores
int menuDisciplinasProf(listaDisc *lista) {
    int opcao;
    
    puts("Escolha a opção referente a disciplina que irá lecionar:");
    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
        printf("\tOPÇÃO %d\n", i + 1);
        printf("%s - %s\n", lista -> disciplinas[i].nome, lista -> disciplinas[i].codigo);
        imprimirProf(lista, i);
        printf("Vagas: %d\n", lista -> disciplinas[i].qtdVagas);
        puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
    }
    do {
        printf("\nOpção: ");
        scanf("%d", &opcao);
        if (opcao < 1 || lista -> disciplinas[opcao - 1].qtdResp > 2)
            puts("Opção Inválida. Tente Novamente!\n");
    } while (opcao < 1 || lista -> disciplinas[opcao - 1].qtdResp > 2);

    return opcao - 1;
}

// Função que mostra o menu de Disciplinas para Alunos
int menuDisciplinasAluno(listaDisc *lista) {
    int opcao;
    
    puts("Escolha a opção referente a disciplina que irá cursar:");
    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        printf("\tOPÇÃO %d\n", i + 1);
        printf("%s - %s\n", lista -> disciplinas[i].nome, lista -> disciplinas[i].codigo);
        imprimirProf(lista, i);
        printf("Vagas: %d\n", lista -> disciplinas[i].qtdVagas);
        puts("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    }
    do {
        printf("\nOpção: ");
        scanf("%d", &opcao);
        if (opcao < 1 || lista -> disciplinas[opcao - 1].qtdVagas == 0)
            puts("Opção Inválida. Tente Novamente!\n");
    } while (opcao < 1 || lista -> disciplinas[opcao - 1].qtdVagas == 0);

    return opcao - 1;
}

// Função que cadastra um Professor na lista de Disciplinas
void cadastrarProfDisc(professor prof, listaDisc *lista, int opcao) {
    lista -> disciplinas[opcao].responsavel[lista -> disciplinas[opcao].qtdResp] = prof;
    lista -> disciplinas[opcao].qtdResp++;
    puts("Professor Cadastrado na Disciplina!");
}

// Função que cadastra um aluno em uma determinada Disciplina
void cadastrarAlunoDisc(aluno aluno, listaDisc *lista, int opcao) {
    lista -> disciplinas[opcao].vagas[lista -> disciplinas[opcao].contVagas] = aluno;
    lista -> disciplinas[opcao].contVagas++;
    lista -> disciplinas[opcao].qtdVagas--;
    puts("Aluno Cadastrado na Disciplina!");
}

void listarDisc(listaDisc *lista) {
        for (int i = 0; i < MAX_DISCIPLINAS; i++) {
            puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
            printf("Disciplina: %s\n", lista -> disciplinas[i].nome);
            printf("Codigo: %s\n", lista -> disciplinas[i].codigo);
            printf("Semestre: %d\n", lista -> disciplinas[i].qtdSemestre);
            imprimirProf(lista, i);
            printf("Quantidade de Alunos: %d\n", lista -> disciplinas[i].contVagas);
            puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
        }
}


void listarDiscAlunos(listaDisc *lista) {
  int i, opcao;
  do {
  printf("-=-=-=-= Escolha uma das opções -=-=-=-=\n");
  printf("%s -- 1\n", lista -> disciplinas[0].codigo);
  printf("%s -- 2\n", lista -> disciplinas[1].codigo);
  printf("%s -- 3\n", lista -> disciplinas[2].codigo);
  printf("%s -- 4\n", lista -> disciplinas[3].codigo);
  printf("%s -- 5\n", lista -> disciplinas[4].codigo);
  printf("Opção: ");
  scanf("%d", &opcao);

  if (opcao < 1 || opcao > 5)
    puts("Opção inválida. Tente novamente!");
    
  } while (opcao < 1 || opcao > 5);
  opcao--;  
  
  printf("\nDisciplina: %s\n", lista -> disciplinas[opcao].nome);
  printf("Codigo: %s\n", lista -> disciplinas[opcao].codigo);
  printf("Semestre: %d\n", lista -> disciplinas[opcao].qtdSemestre);
  imprimirProf(lista, opcao);
  printf("Quantidade de Alunos: %d\n", lista -> disciplinas[opcao].contVagas);
  
  if(lista -> disciplinas[opcao].contVagas == 0)
    puts("Não possui alunos cadastrados!");
  else{
    puts("Alunos cadrastrados na disciplina:");

    for(i=0; i < lista -> disciplinas[opcao].contVagas; i++){
      puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
      printf("Nome: %s\n", lista -> disciplinas[opcao].vagas[i].nome);
      printf("Matrícula: %d\n", lista -> disciplinas[opcao].vagas[i].matricula);
      puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
    }
  }
       
}

void listarDiscLotada(listaDisc *lista){
  int quantidade=0;
  
  for(int i=0; i < MAX_DISCIPLINAS; i++){
    if (lista -> disciplinas[i].contVagas > 40){
      puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
      printf("Disciplina: %s\n", lista -> disciplinas[i].nome);
      printf("Codigo: %s\n", lista -> disciplinas[i].codigo);
      imprimirProf(lista, i);
      puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
      quantidade++;
    }
  }
  if(quantidade==0)
    puts("Não possui disciplina com mais de 40 vagas.");
}

