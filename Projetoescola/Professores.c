#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Disciplinas.h"
#include "Professores.h"
#include "aluno.h"
#include "Validacoes.h"

void cadastrarProfessor(professor prof, listaProf *list, listaDisc *listD, listaAlunos * listA);
void excluirProfessor(listaProf *list, listaDisc *listD);
/* Protótipos de funções apenas de Professores */
int confirmarCadastro(professor prof);
int confirmarDelete(listaProf *list, int index);
int qtdCadastroProf(listaProf *list);

// Função responsável por criar uma lista de Professores.
listaProf* criarListaProf() {
    
    // Criado um ponteiro para a estrutura lista
    listaProf *list;
    
    /* Alocando um espaço de memória para o ponteiro,
    assim ele pode ser realmente trabalhado como uma lista*/
    list = (listaProf *) malloc(sizeof (listaProf));
    
    /* Condição que verifica se a lista foi criada com sucesso. Quando o espaço alocado for 
    diferente de NULL, logo temos que nossa lista foi criada.*/
    if (list != NULL) {
        /* Setando o valor inicial da variável que irá contro-
        lar a quantidade de professores na lista.*/
        list -> qtdProfessores = 0;
    }
    // Por fim retornamos a nossa lista criada;
    return list;
}

// Função que verifica se a lista de professores está no limite.
int listaProfCheia(listaProf *list) {
    if (list == NULL) return -1;
    // Verifica se a condição é verdadeira e retorna esse resultado
    return list -> qtdProfessores == MAX;
}

// Função que verifica se a lista de professores está vazia
int listaProfVazia(listaProf *list) {
    if (list == NULL) return -1;
    return list -> qtdProfessores == 0;
}

// Função que pede a quantidade de professores a ser cadastrada e retorna essa quantidade
int qtdCadastroProf(listaProf *list) {
    int quantidade, maxCadastro = MAX - (list -> qtdProfessores);

    do {
        printf("\nProfessores Cadastrados = %d | Limite da Lista = %d\n", list -> qtdProfessores, MAX);
        printf("Insira a quantidade de professores que você deseja cadastrar: ");
        scanf("%d", &quantidade);

        if (quantidade < 0)
            puts("Opção de quantidade inválida, tente novamente!");
        else if (quantidade == 0)
            puts("É necessário cadastrar ao menos 1 Professor!");
        else if (quantidade > maxCadastro) {
            puts("Opção excede a quantidade máxima de professores disponíveis.");
            printf("Quantidade = %d\n", maxCadastro);
        }
    } while (quantidade <= 0 || quantidade > maxCadastro);
    return quantidade;
}

//Função que cadastra o professor na lista de professores
void cadastrarProfessor(professor prof, listaProf *list, listaDisc *listD, listaAlunos *listA) {
    int confirmacaoCad;

    if (list == NULL)
        puts("Impossível cadastrar professor no sistema. A lista não existe!");
    if (listaProfCheia(list))
        puts("Impossível cadastrar professor. A lista está cheia!");
    else {
        int quantidade = qtdCadastroProf(list);

        for (int i = 0; i < quantidade; i++) {
            confirmacaoCad = 1;
            int indexDisciplina;
            boolean erro, erroCPF, erroIdade;

            while (confirmacaoCad == 1) {
                getchar();
                printf("Digite o nome do professor/a: ");
                scanf("%[^\n]", prof.nome);
                getchar();
                prof.erros[0] = validarNome(prof.nome);

                printf("Digite o sexo do professor/a [m/f/o]: ");
                scanf("%c", &prof.sexo);
                getchar();
                if (prof.sexo == 'M' || prof.sexo == 'F' || prof.sexo == 'O')
                    prof.sexo = tolower(prof.sexo);
                prof.erros[1] = validarSexo(prof.sexo);

                indexDisciplina = menuDisciplinasProf(listD);
                strcpy(prof.curso, listD -> disciplinas[indexDisciplina].codigo);

                printf("Insira o CPF do professor/a: ");
                scanf("%s", prof.cpf);
                prof.erros[2] = validarCPF(prof.cpf);
                erroCPF = verificarCPF(prof.cpf, listA, list);
                getchar();

                printf("Insira a data de nascimento do professor/a: ");
                scanf("%[^\n]", prof.nascimento);
                getchar();
                prof.erros[3] = validarNascimento(prof.nascimento);
                erroIdade = validarIdade(prof.nascimento);

                confirmacaoCad = confirmarCadastro(prof);
            }

            fflush(stdin);
            erro = verificaErros(prof.erros);

            if (!erro && !erroCPF && !erroIdade) {
                // Cadastrando o Professor na lista de Professores
                list -> professores[list -> qtdProfessores] = prof;
                tratarNomeProf(prof.nome, list);
                list -> qtdProfessores++;
                // Cadastrando o Professor na Disciplina
                cadastrarProfDisc(prof, listD, indexDisciplina);
                puts("\nProfessor Cadastrado com Sucesso!\n");
            } else {
                puts("\nNão foi possível cadastrar o Professor!\n");
            }
        }
    }
}

// Função que assegura o usuário do cadastro que ele está fazendo.
int confirmarCadastro(professor prof) {
    int opcao;
    
    do {
        puts("");
        puts("Você está prestes a cadastrar um professor com as seguintes informações:");
        printf("Nome: %s\n", prof.nome);
        printf("Sexo: %c\n", prof.sexo);
        printf("CPF: %s\n", prof.cpf);
        printf("Disciplina: %s\n", prof.curso);
        printf("Data de Nascimento: %s\n", prof.nascimento);

        puts("Deseja alterar o cadastro?");
        puts("[ 1 ] Sim [ 0 ] Não");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 1)
            puts("Opção inválida. Tente novamente!");
    } while (opcao < 0 || opcao > 1);
    
    return opcao;
}

// Função que lista os Professores cadastrados.
void listarProfessores(listaProf *list) {
    if (list == NULL) puts("Impossível executar. A lista não existe!");
    if (listaProfVazia(list)) puts("Impossível executar. A lista está vazia!");
    else {
        for (int i = 0; i < list -> qtdProfessores; i++) {
            puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
            printf("Nome: %s\n", list -> professores[i].nome);
            printf("Curso: %s\n", list -> professores[i].curso);
            printf("Sexo: %c\n", list -> professores[i].sexo);
            printf("CPF: %s\n", list -> professores[i].cpf);
            printf("Data de Nascimento: %s\n", list -> professores[i].nascimento);
            puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
        }
    }
}

// Função que exclui um Professor a partir de um nome ou CPF.
void excluirProfessor(listaProf *list, listaDisc *listD) {
    if (list == NULL) puts("Impossível executar. A lista não existe!");
    if (listaProfVazia(list)) puts("Impossível executar. A lista está vazia!");
    else {
        int opcao;
        do {
            puts("Escolha por qual opção você deseja excluir um Professor/a:");
            puts("[ 1 ] Nome [ 2 ] CPF [ 3 ] Cancelar Operação");
            printf("Opção: ");
            scanf("%d", &opcao);
    
            if (opcao < 1 || opcao > 3)
                puts("Opção Inválida. Tente novamente!");
        } while (opcao < 1 || opcao > 3);
        
        switch (opcao) {
            case 1:{
                char nome[100];
                int confirmacaoDel = 1;
                int i = 0;
                boolean erro = false;
                
                while (confirmacaoDel == 1) {
                    getchar();
                    printf("Digite o nome do Professor/a: ");
                    scanf("%[^\n]", nome);
                    while (i < list -> qtdProfessores && strcmp(list -> professores[i].nome, nome) != 0)
                        i++;
                    if (i == list -> qtdProfessores) {
                        puts("\nProfessor não encontrado!");
                        confirmacaoDel = 0;
                        erro = true;
                    } else { confirmacaoDel = confirmarDelete(list, i); }
                }
                
                if (!erro) {
                    /* Removendo Professor das Disciplinas Matriculadas */
                    
                    // Percorrendo a lista de Disciplinas
                    for (int x = 0; x < MAX_DISCIPLINAS; x++) {
                        // Procurando as disciplinas que o Professor está lecionando
                        if (strcmp(list -> professores[i].curso,
                            listD -> disciplinas[x].responsavel[0].curso) == 0) {
                                listD -> disciplinas[x].responsavel[0] = listD -> disciplinas[x].responsavel[1];
                                // Limpando o Professor do Cadastro da Disciplina
                                listD -> disciplinas[x].responsavel[1].nome[0] = '\0';
                                listD -> disciplinas[x].responsavel[1].curso[0] = '\0';
                                listD -> disciplinas[x].responsavel[1].cpf[0] = '\0';
                                listD -> disciplinas[x].responsavel[1].sexo = '\0';
                                listD -> disciplinas[x].responsavel[1].nascimento[0] = '\0';

                                listD -> disciplinas[x].qtdResp--;
                                break;
                        }
                        else if (strcmp(list -> professores[i].curso,
                            listD -> disciplinas[x].responsavel[1].curso) == 0) {
                                // Limpando o Professor do Cadastro da Disciplina
                                listD -> disciplinas[x].responsavel[1].nome[0] = '\0';
                                listD -> disciplinas[x].responsavel[1].curso[0] = '\0';
                                listD -> disciplinas[x].responsavel[1].cpf[0] = '\0';
                                listD -> disciplinas[x].responsavel[1].sexo = '\0';
                                listD -> disciplinas[x].responsavel[1].nascimento[0] = '\0';

                                listD -> disciplinas[x].qtdResp--;
                                break;
                        }
                        
                    }
                    // Removendo o Professor da Lista de Professores
                    for (int j = i; j < list -> qtdProfessores - 1; j++) {
                        list -> professores[j] = list -> professores[j + 1];
                    }
                    list -> qtdProfessores--;
                    puts("\nProfessor Removido com Sucesso!");
                }
            } break;
            case 2:{
                char cpf[15];
                int confirmacaoDel = 1;
                int i = 0;
                boolean erro = false;
                
                while (confirmacaoDel == 1) {
                    printf("Digite o CPF do Professor/a: ");
                    scanf("%s", cpf);
                    while (i < list -> qtdProfessores && strcmp(list -> professores[i].cpf, cpf) != 0)
                        i++;
                    if (i == list -> qtdProfessores) {
                        puts("\nProfessor não encontrado!");
                        confirmacaoDel = 0;
                        erro = true;
                    } else { confirmacaoDel = confirmarDelete(list, i); }
                }
                
                if (!erro) {
                    for (int j = i; j < list -> qtdProfessores - 1; j++) {
                        list -> professores[j] = list -> professores[j + 1];
                    }
                    list -> qtdProfessores--;
                    puts("\nProfessor Removido com Sucesso!");
                }
            } break;
            default: puts("\nOperação Cancelada!");
        }
    }
}

// Função que confirma o delete de um Professor da lista.
int confirmarDelete(listaProf *list, int index) {
    int opcao;
    
    do {
        puts("");
        puts("Você está prestes a excluir um professor com as seguintes informações:");
        printf("Nome: %s\n", list -> professores[index].nome);
        printf("Sexo: %c\n", list -> professores[index].sexo);
        printf("CPF: %s\n", list -> professores[index].cpf);
        printf("Disciplina: %s\n", list -> professores[index].curso);
        printf("Data de Nascimento: %s\n", list -> professores[index].nascimento);

        puts("Deseja alterar o Professor a ser excluído?");
        puts("[ 1 ] Sim [ 0 ] Não");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 1)
            puts("Opção inválida. Tente novamente!");
    } while (opcao < 0 || opcao > 1);
    
    return opcao;
}

// Função que lista os Professores divididos por Sexo.
void listarProfSexo(listaProf *list) {
    int qtdSexo[3] = {0};
    professor aux;

    for (int i = 0; i < list -> qtdProfessores; i++) {
        for (int j = i + 1; j < list -> qtdProfessores; j++) {
            // Verifica se o sexo da posição anterior é maior que o da próxima
            if (list -> professores[i].sexo > list -> professores[j].sexo) {
                aux = list -> professores[j];
                list -> professores[j] = list -> professores[i];
                list -> professores[i] = aux;
            }
        }

        if (list -> professores[i].sexo == 'm')
            qtdSexo[0] += 1;
        else if (list -> professores[i].sexo == 'f')
            qtdSexo[1] += 1;
        else
            qtdSexo[2] += 1;

        printf("\nNome: %s\n", list -> professores[i].nome);
        printf("Sexo: %c\n", list -> professores[i].sexo);
        printf("Disciplina: %s\n", list -> professores[i].curso);
        printf("CPF: %s\n", list -> professores[i].cpf);
        printf("Data de Nascimento: %s\n", list -> professores[i].nascimento);
        puts("******************\n");
    }

    puts("Quantidade de Professores divididos por Sexo:");
    printf("Masculino: %d\n", qtdSexo[0]);
    printf("Feminino: %d\n", qtdSexo[1]);
    printf("Outro: %d\n", qtdSexo[2]);
}

// Função que lista os Professores por Nome.
void listarProfNome(listaProf *list) {
    professor aux;

    for (int i = 0; i < list -> qtdProfessores; i++) {
        for (int j = i + 1; j < list -> qtdProfessores; j++) {
            // Verifica se o nome na posição anterior é maior que o da próxima
            if (strcmp(list -> professores[i].nome, list -> professores[j].nome) > 0) {
                aux = list -> professores[j];
                list -> professores[j] = list -> professores[i];
                list -> professores[i] = aux;
            }
        }

        printf("\nNome: %s\n", list -> professores[i].nome);
        printf("Sexo: %c\n", list -> professores[i].sexo);
        printf("Disciplina: %s\n", list -> professores[i].curso);
        printf("CPF: %s\n", list -> professores[i].cpf);
        printf("Data de Nascimento: %s\n", list -> professores[i].nascimento);
        puts("******************\n");
    }
}

// Função que lista os Professores por Data de Nascimento.
void listarProfNascimento(listaProf *list) {
    char *pData1, *pData2;
    char data1[9], data2[9], auxData1[11], auxData2[11];
    professor aux;

    for (int i = 0; i < list -> qtdProfessores; i++) {
        strcpy(auxData1, list -> professores[i].nascimento);
        
        pData1 = strtok(auxData1, "/");
        strcat(data1, pData1);
        pData1 = strtok(NULL, "/");
        strcat(data1, pData1);
        pData1 = strtok(NULL, "/");
        strcat(data1, pData1);

        for (int j = i + 1; j < list -> qtdProfessores; j++) {
            strcpy(auxData2, list -> professores[j].nascimento);
            
            pData2 = strtok(auxData2, "/");
            strcat(data2, pData2);
            pData2 = strtok(NULL, "/");
            strcat(data2, pData2);
            pData2 = strtok(NULL, "/");
            strcat(data2, pData2);

            if (strcmp(data1, data2) > 0) {
                aux = list -> professores[j];
                list -> professores[j] = list -> professores[i];
                list -> professores[i] = aux;
            }
        }

        printf("\nNome: %s\n", list -> professores[i].nome);
        printf("Sexo: %c\n", list -> professores[i].sexo);
        printf("Disciplina: %s\n", list -> professores[i].curso);
        printf("CPF: %s\n", list -> professores[i].cpf);
        printf("Data de Nascimento: %s\n", list -> professores[i].nascimento);
        puts("******************\n");
    }
}
