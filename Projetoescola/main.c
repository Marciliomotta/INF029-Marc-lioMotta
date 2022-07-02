#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "Professores.h"
#include "Disciplinas.h"
#include "MenuOpcoes.h"
#include "Validacoes.h"
#include "Geral.h"

void cadastrarAlunos(aluno aluno, listaAlunos *list, listaDisc *listD, listaProf *listP);
void cadastrarProfessor(professor prof, listaProf *list, listaDisc *listD, listaAlunos * listA);
void matricularAluno(listaAlunos *listA, listaDisc *listD);
void desmatricularAluno(listaAlunos *listA, listaDisc *listD);
void excluirAluno(listaAlunos *list, listaDisc *listD);
void excluirProfessor(listaProf *list, listaDisc *listD);

int main(void) {
    listaProf *listaP;
    listaAlunos *listaA;
    listaDisc *listaD;

    listaP = criarListaProf();
    listaA = criarListaAlunos();
    listaD = criarListaDisc();

    inserirBancoDisciplinas(listaD);

    int gerOpcoes[3] = {0};
    int escolha;

    while (gerOpcoes[0] != 3 && gerOpcoes[1] != 8 && gerOpcoes[2] != 16) {
        gerOpcoes[0] = 0;
        gerOpcoes[1] = 0;
        gerOpcoes[2] = 0;

        escolha = gerenciaEscolha(gerOpcoes);
        
        if (gerOpcoes[1] != 0) {
            switch (escolha) {
                case 1:{
                  aluno a1;
                  cadastrarAlunos(a1, listaA, listaD, listaP);
                } break;
                case 2: excluirAluno(listaA, listaD); break;
                case 3:{
                    professor p1;
                    cadastrarProfessor(p1, listaP, listaD, listaA);
                } break;
                case 4: excluirProfessor(listaP, listaD); break;
                case 5: matricularAluno(listaA, listaD); break;
                case 6: desmatricularAluno(listaA, listaD); break;
                default: puts("\nPROGRAMA FINALIZADO");
            }
        }
        else if (gerOpcoes[2] != 0) {
            switch (escolha) {
                case 1: listarAlunos(listaA); break;
                case 2: listarAlunosNome(listaA); break;
                case 3: listarAlunosSexo(listaA); break;
                case 4: listarAlunosNascimento(listaA); break;
                case 5: listarAlunosMenosDe3(listaA); break;
                case 6: listarProfessores(listaP); break;
                case 7: listarProfNome(listaP); break;
                case 8: listarProfSexo(listaP); break;
                case 9: listarProfNascimento(listaP); break;
                case 10: listarDisc(listaD); break;
                case 11: listarDiscAlunos(listaD); break;
                case 12: listarDiscLotada(listaD); break;
                case 13: existe(listaA, listaP); break;
                case 14: AniversarioMes(listaP, listaA);break;
                default: puts("\nPROGRAMA FINALIZADO!");
            }
        } else {
            puts("\nPROGRAMA FINALIZADO!");
        }
    }
    
    return 0;
}