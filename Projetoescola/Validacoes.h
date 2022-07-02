#ifndef __VALIDACOES_H_
#define __VALIDACOES_H_
#define true 1
#define false 0
#include "aluno.h"
#include "Professores.h"

    typedef int boolean;

    enum meses{Janeiro = 1, Fevereiro, Marco, Abril, Maio, Junho, Julho, Agosto, 
                Setembro, Outubro, Novembro, Dezembro};

    void tratarNomeProf(char nome[], listaProf *lista);
    void tratarNomeAluno(char nome[], listaAlunos *lista);
    boolean verificaErros(boolean erros[]);
    boolean verificarCPF(char cpf[], listaAlunos *listaA, listaProf *listaP);

    boolean validarNome(char nome[]);
    boolean validarSexo(char sexo);
    boolean validarCPF(char cpf[]);
    boolean validarNascimento(char data[]);
    boolean validarIdade(char data[]);

#endif // __VALIDACOES_H_