#include <stdio.h>
#include "MenuOpcoes.h"

/* Protótipos das funções apenas de Menu Opções */
int menuCadastro();
int menuRelatorios();

// Função que mostra o menu inicial do programa, retornando a opção escolhida.
int menuPrincipal() {
    int opcao;
    do {
        puts("\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
        puts("\t * GERENCIAMENTO DE ESCOLA *");
        puts("\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

        puts("\tEscolha uma das opções abaixo: ");
        puts("[ 1 ] Cadastro [ 2 ] Relatórios [ 3 ] Sair");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao < 1 || opcao > 3)
            puts("Opção inválida. Tente novamente!");
    } while (opcao < 1 || opcao > 3);
    return opcao;
}

// Função que mostra o menu de cadastro do programa retornando a opção escolhida.
int menuCadastro() {
    int opcao;
    do {
        puts("\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
        puts("\t    * MENU DE CADASTRO *");
        puts("\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

        puts("\tEscolha uma das opções abaixo: ");
        puts("[ 1 ] Cadastrar Aluno [ 2 ] Excluir Aluno");
        puts("[ 3 ] Cadastrar Professor [ 4 ] Excluir Professor");
        puts("[ 5 ] Matricular Aluno [ 6 ] Desmatricular Aluno");
        puts("[ 7 ] Voltar [ 8 ] Sair");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao < 1 || opcao > 8)
            puts("Opção inválida. Tente novamente!");
    } while (opcao < 1 || opcao > 8);
    return opcao;
}

// Função que mostra o menu de relatórios do programa retornando a opção escolhida.
int menuRelatorios() {
    int opcao;
    do {
        puts("\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
        puts("\t   * MENU DE RELATÓRIOS *");
        puts("\t-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

        puts("\tEscolha uma das opções abaixo:");
        puts("-> Alunos");
        puts("[ 1 ] Listar Alunos");
        puts("[ 2 ] Listar Alunos por Nome");
        puts("[ 3 ] Listar Alunos por Sexo");
        puts("[ 4 ] Listar Alunos por Nascimento");
        puts("[ 5 ] Listar Alunos matriculados em menos de 3 disciplinas");
        puts("-> Professores");
        puts("[ 6 ] Listar Professores");
        puts("[ 7 ] Listar Professores por Nome");
        puts("[ 8 ] Listar Professores por Sexo");
        puts("[ 9 ] Listar Professores por Nascimento");
        puts("-> Disciplinas");
        puts("[ 10 ] Listar todas as disciplinas");
        puts("[ 11 ] Listar uma disciplina");
        puts("[ 12 ] Listar disciplinas com mais de 40 vagas");
        puts("-> Geral");
        puts("[ 13 ] Buscar pessoa");
        puts("[ 14 ] Aniversariante do Mês");
        puts("[ 15 ] Voltar [ 16 ] Sair");

        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao < 1 || opcao > 16)
        puts("Opção inválida. Tente novamente!");
    } while (opcao < 1 || opcao > 16);
    return opcao;
}

// Função responsável por administrar a escolha das opções feitas pelo usuário.
int gerenciaEscolha(int array[]) {
    while (array[0] != 3 && (array[1] == 0 && array[2] == 0)) {
        array[0] = menuPrincipal();
        switch (array[0]) {
            case 1:
                array[1] = menuCadastro();
                switch (array[1]) {
                    case 7: array[1] = 0; break;
                    default: return array[1];
                } break;
            case 2:
                array[2] = menuRelatorios();
                switch (array[2]) {
                    case 15: array[2] = 0; break;
                    default: return array[2];
                }
        }
    }
    return array[0];
}