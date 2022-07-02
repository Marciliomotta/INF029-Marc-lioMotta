#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aluno.h"
#include "Professores.h"
#include "Validacoes.h"
#include "Disciplinas.h"

/* Protótipos de funções apenas de Alunos */
int confirmarCadastroAluno(aluno aluno);
int confirmarDeleteAluno(listaAlunos *list, int index);
int qtdCadastroAlunos(listaAlunos *list);
void imprimirDisciplinasAluno(aluno aluno);

void cadastrarAlunos(aluno aluno, listaAlunos *list, listaDisc *listD, listaProf *listP);
void matricularAluno(listaAlunos *listA, listaDisc *listD);
void excluirAluno(listaAlunos *list, listaDisc *listD);
void desmatricularAluno(listaAlunos *listA, listaDisc *listD);

// Função responsável por criar uma lista de Alunos.
listaAlunos* criarListaAlunos() {
    
    // Criado um ponteiro para a estrutura lista
    listaAlunos *list;
    
    /* Alocando um espaço de memória para o ponteiro,
    assim ele pode ser realmente trabalhado como uma lista*/
    list = (listaAlunos *) malloc(sizeof (listaAlunos));
    
    /* Condição que verifica se a lista foi criada com sucesso. Quando o espaço alocado for 
    diferente de NULL, logo temos que nossa lista foi criada.*/
    if (list != NULL) {
        /* Setando o valor inicial da variável que irá contro-
        lar a quantidade de alunos na lista.*/
        list -> qtdAlunos = 0;
    }
    // Por fim retornamos a nossa lista criada;
    return list;
}

// Função que verifica se a lista de alunos está no limite.
int listaAlunosCheia(listaAlunos *list) {
    if (list == NULL) return -1;
    // Verifica se a condição é verdadeira e retorna esse resultado
    return list -> qtdAlunos == MAX_Aluno;
}

// Função que verifica se a lista de alunos está vazia
int listaAlunosVazia(listaAlunos *list) {
    if (list == NULL) return -1;
    return list -> qtdAlunos == 0;
}

// Função que imprime as Disciplinas de um aluno
void imprimirDisciplinasAluno(aluno aluno) {
    if (aluno.qtdCursos == 0 || aluno.qtdCursos == 1) puts("Disciplina:");
    else puts("Disciplinas:");

    for (int i = 0; i <= aluno.qtdCursos; i++) {
        fflush(stdin);
        printf("%s ", aluno.curso[i]);
        fflush(stdin);
    }
    puts("");
}

// Função que pede a quantidade de Alunos a ser cadastrada e retorna essa quantidade
int qtdCadastroAlunos(listaAlunos *list) {
    int quantidade, maxCadastro = MAX_Aluno - (list -> qtdAlunos);

    do {
        printf("\nAlunos Cadastrados = %d | Limite da Lista = %d\n", list -> qtdAlunos, MAX_Aluno);
        printf("Insira a quantidade de alunos que você deseja cadastrar: ");
        scanf("%d", &quantidade);

        if (quantidade < 0)
            puts("Opção de quantidade inválida, tente novamente!");
        else if (quantidade == 0)
            puts("É necessário cadastrar ao menos 1 Aluno!");
        else if (quantidade > maxCadastro) {
            puts("Opção excede a quantidade máxima de alunos disponíveis.");
            printf("Quantidade = %d\n", maxCadastro);
        }
    } while (quantidade <= 0 || quantidade > maxCadastro);
    return quantidade;
}

//Função que cadastra o Aluno na lista de Alunos
void cadastrarAlunos(aluno aluno, listaAlunos *list, listaDisc *listD, listaProf *listP) {
    int confirmacaoCad;

    if (list == NULL)
        puts("Impossível cadastrar aluno no sistema. A lista não existe!");
    if (listaAlunosCheia(list))
        puts("Impossível cadastrar aluno. A lista está cheia!");
    else {
        int quantidade = qtdCadastroAlunos(list);

        for (int i = 0; i < quantidade; i++) {
            confirmacaoCad = 1;
            boolean erro, erroCPF;
            int indexDisciplina;

            aluno.qtdCursos = 0;

            while (confirmacaoCad == 1) {
                // temos que colocar a matricula
                getchar();
                printf("Digite o nome do aluno/a: ");
                scanf("%[^\n]", aluno.nome);
                getchar();
                aluno.erros[0] = validarNome(aluno.nome);

                printf("Digite o sexo do aluno/a [m/f/o]: ");
                scanf("%c", &aluno.sexo);
                getchar();
                if (aluno.sexo == 'M' || aluno.sexo == 'F' || aluno.sexo == 'O')
                    aluno.sexo = tolower(aluno.sexo);
                aluno.erros[1] = validarSexo(aluno.sexo);

                indexDisciplina = menuDisciplinasAluno(listD);
                
                strcpy(aluno.curso[aluno.qtdCursos], listD -> disciplinas[indexDisciplina].codigo);

                printf("Insira o CPF do aluno/a: ");
                scanf("%s", aluno.cpf);
                aluno.erros[2] = validarCPF(aluno.cpf);
                erroCPF = verificarCPF(aluno.cpf, list, listP);
                getchar();

                printf("Insira a data de nascimento do aluno/a: ");
                scanf("%[^\n]", aluno.nascimento);
                getchar();
                aluno.erros[3] = validarNascimento(aluno.nascimento);

                confirmacaoCad = confirmarCadastroAluno(aluno);
            }

            erro = verificaErros(aluno.erros);

            if (!erro && !erroCPF) {
                aluno.matricula = 202100 + list -> qtdAlunos + 1;
                // Cadastrando aluno na Disciplina
                aluno.qtdCursos++;
                cadastrarAlunoDisc(aluno, listD, indexDisciplina);
                // Cadastrando aluno na lista de alunos
                list -> alunos[list -> qtdAlunos] = aluno;
                tratarNomeAluno(aluno.nome, list);
                list -> qtdAlunos++;
                puts("\nAluno Cadastrado com Sucesso!\n");
            } else {
                puts("\nNão foi possível cadastrar o Aluno!\n");
            }
        }
    }
}

// Função que assegura o usuário do cadastro que ele está fazendo.
int confirmarCadastroAluno(aluno aluno) {
    int opcao;
    
    do {
        puts("");
        puts("Você está prestes a cadastrar um aluno com as seguintes informações:");
        printf("Nome: %s\n", aluno.nome);
        printf("Sexo: %c\n", aluno.sexo);
        printf("CPF: %s\n", aluno.cpf);
        imprimirDisciplinasAluno(aluno);
        printf("Data de Nascimento: %s\n", aluno.nascimento);

        puts("Deseja alterar o cadastro?");
        puts("[ 1 ] Sim [ 0 ] Não");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 1)
            puts("Opção inválida. Tente novamente!");
    } while (opcao < 0 || opcao > 1);
    
    return opcao;
}

// Função que lista os Alunos cadastrados.
void listarAlunos(listaAlunos *list) {
    if (list == NULL) puts("Impossível executar. A lista não existe!");
    if (listaAlunosVazia(list)) puts("Impossível executar. A lista está vazia!");
    else {
        for (int i = 0; i < list -> qtdAlunos; i++) {
            puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
            printf("Matrícula: %d\n", list -> alunos[i].matricula);
            printf("Nome: %s\n", list -> alunos[i].nome);
            imprimirDisciplinasAluno(list -> alunos[i]);
            printf("Sexo: %c\n", list -> alunos[i].sexo);
            printf("CPF: %s\n", list -> alunos[i].cpf);
            printf("Data de Nascimento: %s\n", list -> alunos[i].nascimento);
            puts("-=-=-=-=-=-=-=-=-=-=-=-=-");
        }
    }
}

// Função que exclui um Aluno a partir de um nome ou CPF.
void excluirAluno(listaAlunos *list, listaDisc *listD) {
    if (list == NULL) puts("Impossível executar. A lista não existe!");
    if (listaAlunosVazia(list)) puts("Impossível executar. A lista está vazia!");
    else {
        int opcao;
        do {
            puts("Escolha por qual opção você deseja excluir um Aluno/a:");
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
                    printf("Digite o nome do Aluno/a: ");
                    scanf("%[^\n]", nome);
                    while (i < list -> qtdAlunos && strcmp(list -> alunos[i].nome, nome) != 0)
                        i++;
                    if (i == list -> qtdAlunos) {
                        puts("\nAluno não encontrado!");
                        confirmacaoDel = 0;
                        erro = true;
                    } else { confirmacaoDel = confirmarDeleteAluno(list, i); }
                }

                if (!erro) {
                    /* Removendo Aluno das Disciplinas Matriculadas */
                    int localAlunoDisc[MAX_DISCIPLINAS];
                    // Procurando os locais de disciplinas do aluno
                    for (int j = 0; j < MAX_DISCIPLINAS; j++) {
                        for (int k = 0; k < TAM_VAGAS; k++) {
                            if (strcmp(listD -> disciplinas[j].vagas[k].cpf, list -> alunos[i].cpf) == 0) {
                                localAlunoDisc[j] = k; break; 
                            }
                        }
                    }
                    
                    // Removendo ocorrências do aluno em cada disciplina
                    for (int j = 0; j < list -> alunos[i].qtdCursos; j++) {
                        for (int k = localAlunoDisc[j]; k < TAM_VAGAS; k++) {
                            listD -> disciplinas[j].vagas[k] = listD -> disciplinas[j].vagas[k + 1];
                        }
                        listD -> disciplinas[j].contVagas--;
                        listD -> disciplinas[j].qtdVagas++;
                    }
                    // Removendo Aluno da Lista de Alunos
                    for (int j = i; j < list -> qtdAlunos - 1; j++) {
                        list -> alunos[j] = list -> alunos[j + 1];
                    }
                    list -> qtdAlunos--;
                    puts("\nAluno Removido com Sucesso!");
                }
            } break;
            case 2:{
                char cpf[15];
                int confirmacaoDel = 1;
                int i = 0;
                boolean erro = false;

                while (confirmacaoDel == 1) {
                    printf("Digite o CPF do Aluno/a: ");
                    scanf("%s", cpf);
                    while (i < list -> qtdAlunos && strcmp(list -> alunos[i].cpf, cpf) != 0)
                        i++;
                    if (i == list -> qtdAlunos) {
                        puts("\nAluno não encontrado!");
                        confirmacaoDel = 0;
                        erro = true;
                    } else { confirmacaoDel = confirmarDeleteAluno(list, i); }
                }

                if (!erro) {
                    /* Removendo Aluno das Disciplinas Matriculadas */
                    
                    // Percorrendo a lista de Disciplinas
                    for (int x = 0; x < list -> alunos[i].qtdCursos; x++) {
                        // Procurando as disciplinas que o aluno está matriculado
                        if (strcmp(listD -> disciplinas[x].codigo, list -> alunos[i].curso[x]) == 0) {
                            // Retirando o aluno das vagas da disciplina
                            for (int y = i; y < TAM_VAGAS; y++) {
                                listD -> disciplinas[x].vagas[y] = listD -> disciplinas[x].vagas[y + 1];
                            }
                            listD -> disciplinas[x].contVagas--;
                            listD -> disciplinas[x].qtdVagas++;
                        }
                    }
                    // Removendo aluno da Lista de Alunos
                    for (int j = i; j < list -> qtdAlunos - 1; j++) {
                        list -> alunos[j] = list -> alunos[j + 1];
                    }
                    list -> qtdAlunos--;
                    puts("\nAluno Removido com Sucesso!");
                }
            } break;
            default: puts("\nOperação Cancelada!");
        }
    }
}

// Função que confirma o delete de um Aluno da lista.
int confirmarDeleteAluno(listaAlunos *list, int index) {
    int opcao;
    
    do {
        puts("");
        puts("Você está prestes a excluir um Aluno com as seguintes informações:");
        printf("Matrícula: %d\n", list -> alunos[index].matricula);
        printf("Nome: %s\n", list -> alunos[index].nome);
        printf("Sexo: %c\n", list -> alunos[index].sexo);
        printf("CPF: %s\n", list -> alunos[index].cpf);
        imprimirDisciplinasAluno(list -> alunos[index]);
        printf("Data de Nascimento: %s\n", list -> alunos[index].nascimento);

        puts("Deseja alterar o Aluno a ser excluído?");
        puts("[ 1 ] Sim [ 0 ] Não");
        printf("Opção: ");
        scanf("%d", &opcao);

        if (opcao < 0 || opcao > 1)
            puts("Opção inválida. Tente novamente!");
    } while (opcao < 0 || opcao > 1);
    
    return opcao;
}

// Função que lista os Alunos divididos por Sexo.
void listarAlunosSexo(listaAlunos *list) {
    int qtdSexo[3] = {0};
    aluno aux;

    for (int i = 0; i < list -> qtdAlunos; i++) {
        for (int j = i + 1; j < list -> qtdAlunos; j++) {
            // Verifica se o sexo da posição anterior é maior que o da próxima
            if (list -> alunos[i].sexo > list -> alunos[j].sexo) {
                aux = list -> alunos[j];
                list -> alunos[j] = list -> alunos[i];
                list -> alunos[i] = aux;
            }
        }

        if (list -> alunos[i].sexo == 'm')
            qtdSexo[0] += 1;
        else if (list -> alunos[i].sexo == 'f')
            qtdSexo[1] += 1;
        else
            qtdSexo[2] += 1;

        printf("Matrícula: %d\n", list -> alunos[i].matricula);
        printf("\nNome: %s\n", list -> alunos[i].nome);
        printf("Sexo: %c\n", list -> alunos[i].sexo);
        imprimirDisciplinasAluno(list -> alunos[i]);
        printf("CPF: %s\n", list -> alunos[i].cpf);
        printf("Data de Nascimento: %s\n", list -> alunos[i].nascimento);
        puts("******************\n");
    }

    puts("Quantidade de Alunos divididos por Sexo:");
    printf("Masculino: %d\n", qtdSexo[0]);
    printf("Feminino: %d\n", qtdSexo[1]);
    printf("Outro: %d\n", qtdSexo[2]);
}

// Função que lista os Alunos por Nome.
void listarAlunosNome(listaAlunos *list) {
    aluno aux;

    for (int i = 0; i < list -> qtdAlunos; i++) {
        for (int j = i + 1; j < list -> qtdAlunos; j++) {
            // Verifica se o nome na posição anterior é maior que o da próxima
            if (strcmp(list -> alunos[i].nome, list -> alunos[j].nome) > 0) {
                aux = list -> alunos[j];
                list -> alunos[j] = list -> alunos[i];
                list -> alunos[i] = aux;
            }
        }

        printf("Matrícula: %d\n", list -> alunos[i].matricula);
        printf("\nNome: %s\n", list -> alunos[i].nome);
        printf("Sexo: %c\n", list -> alunos[i].sexo);
        imprimirDisciplinasAluno(list -> alunos[i]);
        printf("CPF: %s\n", list -> alunos[i].cpf);
        printf("Data de Nascimento: %s\n", list -> alunos[i].nascimento);
        puts("******************\n");
    }
}

// Função que lista os Alunos por Data de Nascimento.
void listarAlunosNascimento(listaAlunos *list) {
    char *pData1, *pData2;
    char data1[9], data2[9], auxData1[11], auxData2[11];
    aluno aux;

    for (int i = 0; i < list -> qtdAlunos; i++) {
        strcpy(auxData1, list -> alunos[i].nascimento);
        
        pData1 = strtok(auxData1, "/");
        strcat(data1, pData1);
        pData1 = strtok(NULL, "/");
        strcat(data1, pData1);
        pData1 = strtok(NULL, "/");
        strcat(data1, pData1);

        for (int j = i + 1; j < list -> qtdAlunos; j++) {
            strcpy(auxData2, list -> alunos[j].nascimento);
            
            pData2 = strtok(auxData2, "/");
            strcat(data2, pData2);
            pData2 = strtok(NULL, "/");
            strcat(data2, pData2);
            pData2 = strtok(NULL, "/");
            strcat(data2, pData2);

            if (strcmp(data1, data2) > 0) {
                aux = list -> alunos[j];
                list -> alunos[j] = list -> alunos[i];
                list -> alunos[i] = aux;
            }
        }

        printf("Matrícula: %d\n", list -> alunos[i].matricula);
        printf("\nNome: %s\n", list -> alunos[i].nome);
        printf("Sexo: %c\n", list -> alunos[i].sexo);
        imprimirDisciplinasAluno(list -> alunos[i]);
        printf("CPF: %s\n", list -> alunos[i].cpf);
        printf("Data de Nascimento: %s\n", list -> alunos[i].nascimento);
        puts("******************\n");
    }
}

void matricularAluno(listaAlunos *listA, listaDisc *listD) {
    if (listaAlunosVazia(listA)) puts("Não há aluno cadastrado no sistema!\n");
    else {
        int opcao;
        
        do {
            puts("\tPor qual opção você deseja matricular o aluno?");
            puts("[ 1 ] CPF [ 2 ] Nº de Matrícula [ 3 ] Cancelar Operação");
            printf("Opção: ");
            scanf("%d", &opcao);

            if (opcao < 1 || opcao > 3)
                puts("Opção Inválida. Tente Novamente!\n");
        } while (opcao < 1 || opcao > 3);

        if (opcao == 1) {
            char cpf[TAM_CPF];
            int i, confirmacao = 1;

            while (confirmacao == 1) {
                printf("Insira o CPF do Aluno: ");
                scanf("%s", cpf);
                getchar();

                for (i = 0; i < listA -> qtdAlunos; i++) {
                    if (strcmp(cpf, listA -> alunos[i].cpf) == 0) break;
                }

                if (i == listA -> qtdAlunos) puts("Aluno não encontrado.\n");
                else {
                    confirmacao = confirmarCadastroAluno(listA -> alunos[i]);
                    if (confirmacao == 0) {
                        int indexDisciplina;
                        boolean erro;

                        do {
                            erro = false;
                            indexDisciplina = menuDisciplinasAluno(listD);

                            for (int j = 0; j < listA -> alunos[i].qtdCursos; j++) {
                                if (strcmp(listA -> alunos[i].curso[j],
                                     listD -> disciplinas[indexDisciplina].codigo) == 0) {
                                    erro = true; 
                                    puts("Aluno já está cadastrado nesse curso. Tente novamente!\n");
                                    break;
                                }
                            }
                        } while (erro);

                        strcpy(listA -> alunos[i].curso[listA -> alunos[i].qtdCursos + 1], 
                                listD -> disciplinas[indexDisciplina].codigo);
                        listA -> alunos[i].qtdCursos++;
                        cadastrarAlunoDisc(listA -> alunos[i], listD, indexDisciplina);
                    }
                }
            }
        } else if (opcao == 2) {
            int mat;
            int confirmacao = 1;

            while (confirmacao == 1) {
                printf("Insira o Número de Matrícula do Aluno: ");
                scanf("%d", &mat);
                mat--;

                if (mat > listA -> qtdAlunos) puts("Nº de Matrícula Inexistente!\n");
                else {
                    confirmacao = confirmarCadastroAluno(listA -> alunos[mat]);
                    if (confirmacao == 0) {
                        int indexDisciplina;
                        boolean erro;

                        do {
                            erro = false;
                            indexDisciplina = menuDisciplinasAluno(listD);

                            for (int j = 0; j < listA -> alunos[mat].qtdCursos; j++) {
                                if (strcmp(listA -> alunos[mat].curso[j],
                                    listD -> disciplinas[indexDisciplina].codigo) == 0) {
                                        erro = true;
                                        puts("Aluno já está matriculado nesse curso. Tente Novamente!\n");
                                        break;
                                    }
                            }
                        } while (erro);

                        strcpy(listA -> alunos[mat].curso[listA -> alunos[mat].qtdCursos + 1], 
                                listD -> disciplinas[indexDisciplina].codigo);
                        listA -> alunos[mat].qtdCursos++;
                        cadastrarAlunoDisc(listA -> alunos[mat], listD, indexDisciplina);
                    }
                }
            }
        } else { puts("OPERAÇÃO CANCELADA!\n"); }
    }
}

// Função que desmatricula um aluno existente de uma determinada Disciplina
void desmatricularAluno(listaAlunos *listA, listaDisc *listD) {
    if (listaAlunosVazia(listA)) puts("Não há aluno cadastrado no sistema.\n");
    else {
        int opcao;

        do {
            puts("\tEscolha por qual opção você deseja desmatricular um aluno:");
            puts("[ 1 ] CPF [ 2 ] Nº de Matrícula [ 3 ] Cancelar Operação");
            printf("Opção: ");
            scanf("%d", &opcao);
            if (opcao < 1 || opcao > 3)
                puts("Opção inválida. Tente novamente!\n");
        } while (opcao < 1 || opcao > 3);

        switch (opcao) {
            case 1:{
                char cpf[TAM_CPF];
                int i, continua = 0;

                while (continua == 0) {
                    printf("Digite o CPF do Aluno: ");
                    scanf("%s", cpf);

                    for (i = 0; i < listA -> qtdAlunos; i++) {
                        if (strcmp(cpf, listA -> alunos[i].cpf) == 0) {
                            puts("-------------------------------------");
                            puts("Você irá desmatricular este aluno:");
                            printf("Matrícula: %d\n", listA -> alunos[i].matricula);
                            printf("Nome: %s\n", listA -> alunos[i].nome);
                            printf("Sexo: %c\n", listA -> alunos[i].sexo);
                            printf("CPF: %s\n", listA -> alunos[i].cpf);
                            puts("-------------------------------------");                        
                            break;
                        }
                    }
                    puts("Deseja continuar?");
                    puts("[ 1 ] Sim [ 0 ] Não");
                    printf("Opção: ");
                    scanf("%d", &continua);
                    if (continua < 0 || continua > 1) puts("Opção Inválida. Tente Novamente!\n");
                }

                if (i == listA -> qtdAlunos) puts("Aluno não encontrado.\n");
                else {                    
                    int opt = 0, contAux = 0, escolha;
                    int localizacao;
                    char auxDisciplinas[MAX_DISCIPLINAS][TAM_COD] = {0};

                    puts("############################");
                    for (int j = 0; j < MAX_DISCIPLINAS; j++) {
                        for (int k = 0; k < TAM_VAGAS; k++) {
                            if (strcmp(listD -> disciplinas[j].vagas[k].cpf, listA -> alunos[i].cpf) == 0) {
                                localizacao = k;

                                puts("Disciplinas Matriculadas:");
                                printf("%s - [ %d ]\n", listD -> disciplinas[j].codigo, opt);
                                strcpy(auxDisciplinas[contAux], listD -> disciplinas[j].codigo);
                                contAux++;
                                opt++;
                                break;
                            }
                        }
                    }
                    printf("############################\n");

                    do {
                        printf("Escolha uma das opções para desmatricular o aluno: ");
                        scanf("%d", &escolha);
                        if (escolha < 0 || escolha > opt) puts("Opção inválida. Tente Novamente!\n");
                    } while (escolha < 0 || escolha > opt);

                    int indexCurso;
                    for (int j = 0; j < listA -> alunos[i].qtdCursos; j++) {
                        if (strcmp(listA -> alunos[i].curso[j], auxDisciplinas[j]) == 0) {
                            indexCurso = j; break;
                        }
                    }

                    for (int j = indexCurso; j < listA -> alunos[i].qtdCursos; j++) {
                        strcpy(listA -> alunos[i].curso[j], listA -> alunos[i].curso[j + 1]);
                    }
                    listA -> alunos[i].qtdCursos--;

                    int indexDisciplina;
                    for (int j = 0; j < MAX_DISCIPLINAS; j++) {
                        if (strcmp(listD -> disciplinas[j].codigo, auxDisciplinas[escolha]) == 0) {
                            indexDisciplina = j; break;
                        }
                    }

                    for (int j = localizacao; j < TAM_VAGAS; j++) {
                        listD -> disciplinas[indexDisciplina].vagas[j] = 
                        listD -> disciplinas[indexDisciplina].vagas[j + 1];
                    }
                    listD -> disciplinas[indexDisciplina].qtdVagas++;
                    listD -> disciplinas[indexDisciplina].contVagas--;
                }
                puts("\nAluno Desmatriculado com sucesso!\n");
            } break;
            case 2:{
                int mat;
                int i;
                int continua = 0;

                while (continua == 0) {
                    printf("Digite o Nº de Matrícula do Aluno: ");
                    scanf("%d", &mat);

                    for (i = 0; i < listA -> qtdAlunos; i++) {
                        if (listA -> alunos[i].matricula == mat) break;
                    }
                    if (i == listA -> qtdAlunos) puts("Aluno não encontrado!\n");
                    else {
                        puts("-------------------------------------");
                        puts("Você irá desmatricular este aluno:");
                        printf("Matrícula: %d\n", listA -> alunos[i].matricula);
                        printf("Nome: %s\n", listA -> alunos[i].nome);
                        printf("Sexo: %c\n", listA -> alunos[i].sexo);
                        printf("CPF: %s", listA -> alunos[i].cpf);
                        puts("-------------------------------------");
                        puts("\nDeseja continuar?");
                        puts("[ 1 ] Sim [ 0 ] Não");
                        printf("Opção: ");
                        scanf("%d", &continua);
                        if (continua != 1 || continua != 0) puts("Opção Inválida. Tente Novamente!\n");
                    }

                    int opt = 0, contAux = 0, escolha;
                    int localizacao;
                    char auxDisciplinas[MAX_DISCIPLINAS][TAM_COD] = {0};

                    puts("############################");
                    for (int j = 0; j < MAX_DISCIPLINAS; j++) {
                        for (int k = 0; k < TAM_VAGAS; k++) {
                            if (listD -> disciplinas[j].vagas[k].matricula == listA -> alunos[i].matricula) {
                                localizacao = k;

                                puts("Disciplinas Matriculadas:");
                                printf("%s - [ %d ]\n", listD -> disciplinas[j].codigo, opt);
                                strcpy(auxDisciplinas[contAux], listD -> disciplinas[j].codigo);
                                contAux++;
                                opt++;
                                break;
                            }
                        }
                    }
                    printf("############################\n");

                    do {
                        printf("Escolha uma das opções para desmatricular o aluno: ");
                        scanf("%d", &escolha);
                        if (escolha < 0 || escolha > opt) puts("Opção inválida. Tente Novamente!\n");
                    } while (escolha < 0 || escolha > opt);

                    int indexCurso;
                    for (int j = 0; j < listA -> alunos[i].qtdCursos; j++) {
                        if (strcmp(listA -> alunos[i].curso[j], auxDisciplinas[j]) == 0) {
                            indexCurso = j; break;
                        }
                    }

                    for (int j = indexCurso; j < listA -> alunos[i].qtdCursos; j++) {
                        strcpy(listA -> alunos[i].curso[j], listA -> alunos[i].curso[j + 1]);
                    }
                    listA -> alunos[i].qtdCursos--;

                    int indexDisciplina;
                    for (int j = 0; j < MAX_DISCIPLINAS; j++) {
                        if (strcmp(listD -> disciplinas[j].codigo, auxDisciplinas[escolha]) == 0) {
                            indexDisciplina = j; break;
                        }
                    }

                    for (int j = localizacao; j < TAM_VAGAS; j++) {
                        listD -> disciplinas[indexDisciplina].vagas[j] = 
                        listD -> disciplinas[indexDisciplina].vagas[j + 1];
                    }
                    listD -> disciplinas[indexDisciplina].qtdVagas++;
                    listD -> disciplinas[indexDisciplina].contVagas--;
                }
                puts("\nAluno Desmatriculado com sucesso!\n");
            } break;
            default: puts("OPERAÇÃO CANCELADA!\n");
        }
    }
}

// Função que lista os alunos matriculados em menos de 3 Disciplinas
void listarAlunosMenosDe3(listaAlunos *list) {
    int quantidade = 0;

    for (int i = 0; i < list -> qtdAlunos; i++) {
        if (list -> alunos[i].qtdCursos < 3) {
            puts("-=-=-=-=-=-=-=-=-=-=-=-=-=");
            printf("Nome: %s\n", list -> alunos[i].nome);
            printf("Disciplinas: ");
            for (int j = 0; j < list -> alunos[i].qtdCursos; j++) {
                printf("%s ", list -> alunos[i].curso[j]);
            }
            puts("");
            printf("CPF: %s\n", list -> alunos[i].cpf);
            puts("-=-=-=-=-=-=-=-=-=-=-=-=-=");
            
            quantidade++;
        }
        printf("Quantidade de Alunos Matriculados em menos de 3 Disciplinas = %d.\n", quantidade);
    }
}