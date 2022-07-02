#ifndef __DISCIPLINAS_H_
#define __DISCIPLINAS_H_
#define TAM_NOME 100
#define TAM_VAGAS 50
#define TAM_COD 6
#define MAX_DISCIPLINAS 5 // Tamanho máximo das disciplinas
#define MAX_PROF 2 // Máximo de Professores responsáveis por disciplina

#include "aluno.h"
#include "Professores.h"

    typedef struct {
        char nome[TAM_NOME], codigo[TAM_COD];
        int qtdSemestre, qtdVagas;
        int contVagas;
        aluno vagas[TAM_VAGAS];
        int qtdResp;
        professor responsavel[MAX_PROF];
    } disciplina;

    typedef struct {
        int qtdDisc;
        disciplina disciplinas[MAX_DISCIPLINAS];
    } listaDisc;

    void inserirBancoDisciplinas(listaDisc *lista);
    int menuDisciplinasProf(listaDisc *lista);
    int menuDisciplinasAluno(listaDisc *lista);
    void cadastrarProfDisc(professor prof, listaDisc *lista, int opcao);
    void listarDisc(listaDisc *lista);
    void listarDiscAlunos(listaDisc *lista);
    void listarDiscLotada(listaDisc *lista);
    void cadastrarAlunoDisc(aluno aluno, listaDisc *lista, int opcao);

 listaDisc* criarListaDisc();
#endif // __DISCIPLINAS_H_