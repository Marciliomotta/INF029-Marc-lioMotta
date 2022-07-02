#ifndef __ALUNO_H_
#define __ALUNO_H_

#define true 1
#define false 0

#define MAX_Aluno 5 // Quantidade máxima de alunos
#define MAX_DISCIPLINAS 5
#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_COD 6

    typedef int boolean;

    // Estrutura que compõe um aluno
    typedef struct {
        char nome[TAM_NOME], cpf[TAM_CPF], sexo;
        char curso[MAX_DISCIPLINAS][TAM_COD], nascimento[TAM_DATA];
        int matricula;
        int qtdCursos;
        boolean erros[4];
    } aluno;

    // Lista de Alunos
    typedef struct {
        int qtdAlunos;
        aluno alunos[MAX_Aluno];
    } listaAlunos;

    /* Protótipos das funções de Professor */

    listaAlunos* criarListaAlunos();
    int listaAlunosCheia(listaAlunos *list);
    int listaAlunosVazia(listaAlunos *list);
    
    void listarAlunos(listaAlunos *list);
    void listarAlunosSexo(listaAlunos *list);
    void listarAlunosNome(listaAlunos *list);
    void listarAlunosNascimento(listaAlunos *list);
    void listarAlunosMenosDe3(listaAlunos *list);

#endif // __ALUNOS_H_