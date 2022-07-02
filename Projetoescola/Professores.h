#ifndef __PROFESSORES_H_
#define __PROFESSORES_H_

#define true 1
#define false 0

#define MAX 5 // Quantidade máxima de professores
#define TAM_NOME 100
#define TAM_CPF 15
#define TAM_DATA 11
#define TAM_COD 6

    typedef int boolean;

    // Estrutura que compõe um professor
    typedef struct {
        char nome[TAM_NOME], cpf[TAM_CPF], sexo;
        char curso[TAM_COD], nascimento[TAM_DATA];
        boolean erros[4];
    } professor;

    // Lista de Professores
    typedef struct {
        int qtdProfessores;
        professor professores[MAX];
    } listaProf;

    /* Protótipos das funções de Professor */

    listaProf* criarListaProf();
    int listaProfCheia(listaProf *list);
    int listaProfVazia(listaProf *list);
    
    void listarProfessores(listaProf *list);
    void listarProfSexo(listaProf *list);
    void listarProfNome(listaProf *list);
    void listarProfNascimento(listaProf *list);

#endif // __PROFESSORES_H_