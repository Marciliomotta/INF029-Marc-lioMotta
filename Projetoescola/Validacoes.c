
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "Validacoes.h"

/* Protótipos de Funções exclusivas de Validações */
boolean ehBissexto(int ano);

// Função que verifica se um número é ou não bissexto.
boolean ehBissexto(int ano) {
    boolean bis;

    if (ano % 4 == 0 && !(ano % 100 == 0)) bis = true;
    else if (ano % 4 == 0 && (ano % 100 == 0 && ano % 400 == 0)) bis = true;
    else bis = false;

    return bis;
}

// Função que verifica a idade mínima para ser um professor
boolean validarIdade(char data[]) {
    boolean erro = false;

    int ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    int anoAtual = tm.tm_year + 1900;
    
    const int idadeMinima = 21;

    if (ano < 1900 || (anoAtual - ano < idadeMinima)) {
        erro = true;
        printf("A idade mínima para ser um Professor(a) é %d anos.\n", idadeMinima);
    }
    
    return erro;
}

// Função responsável por validar a data de nascimento, retornando se tem ou não um erro.
boolean validarNascimento(char data[]) {
    boolean erro = false;

    if (strlen(data) != TAM_DATA - 1 || (data[2] != '/' || data[5] != '/')) {
        erro = true;
    } else {
        int dia, mes, ano;

        dia = (data[0] - '0') * 10 + (data[1] - '0');
        mes = (data[3] - '0') * 10 + (data[4] - '0');
        ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

        switch (mes) {
            case Janeiro: if (dia < 0 || dia > 31) erro = true; break;
            case Fevereiro:
                if (ehBissexto(ano)) {
                    if (dia < 0 || dia > 29) erro = true;
                } else {
                    if (dia < 0 || dia > 28) erro = true;
                } break;
            case Marco: if (dia < 0 || dia > 31) erro = true; break;
            case Abril: if (dia < 0 || dia > 30) erro = true; break;
            case Maio: if (dia < 0 || dia > 31) erro = true; break;
            case Junho: if (dia < 0 || dia > 30) erro = true; break;
            case Julho: if (dia < 0 || dia > 31) erro = true; break;
            case Agosto: if (dia < 0 || dia > 31) erro = true; break;
            case Setembro: if (dia < 0 || dia > 30) erro = true; break;
            case Outubro: if (dia < 0 || dia > 31) erro = true; break;
            case Novembro: if (dia < 0 || dia > 30) erro = true; break;
            case Dezembro: if (dia < 0 || dia > 31) erro = true; break;
            default: erro = true;
        }
    }
    
    return erro;
}

// Função responsável por validar o CPF, retornando se tem ou não um erro.
boolean validarCPF(char cpf[]) {
    boolean erro = false;

    int contDigitos = 0;

    if (strlen(cpf) != TAM_CPF - 1 || !(cpf[3] == '.' || cpf[7] == '.' || cpf[11] == '-')) {
        erro = true;
    } else {
        for (int i = 0; i < TAM_CPF - 1 && !erro; i++) {
            if (contDigitos < 3) {
                if (!(cpf[i] >= '0' && cpf[i] <= '9')) {
                    erro = true;
                    break;
                }
                contDigitos++;
            } else {
                contDigitos = 0;
            }
        }
    }
    return erro;
}

// Função responsável por validar o sexo, retornando se tem ou não um erro.
boolean validarSexo(char sexo) {
    boolean erro = false;

    if (!(sexo == 'm' || sexo == 'f' || sexo == 'o'))
        erro = true;
    return erro;
}

// Função responsável por validar um nome, retornando se tem ou não um erro.
boolean validarNome(char nome[]) {
    boolean erro = false;

    for (int i = 0; nome[i] != '\0'; i++) {
        if ((!(nome[i] >= 'a' && nome[i] <= 'z') && !(nome[i] >= 'A' && nome[i] <= 'Z')) 
            && !(nome[i] == ' ')) {
            erro = true; break;
        }
    }
    
    return erro;
}

// Função que realiza o tratamento do nome.
void tratarNomeProf(char nome[], listaProf *lista) {
    char auxNome[100] = {0};
    int tamAuxNome;

    // Tratando o nome (retirando espaços excedentes)
    char *pNome = strtok(nome, " ");
    while (pNome != NULL) {
        strcat(auxNome, pNome);
        strcat(auxNome, " ");
        pNome = strtok(NULL, " ");
    }

    tamAuxNome = strlen(auxNome) - 1;
    auxNome[tamAuxNome] = '\0'; // Removendo o espaço final extra
    strcpy(lista -> professores[lista -> qtdProfessores].nome, auxNome); // Colocando o nome tratado na lista de Professores
}

// Função que realiza o tratamento do nome.
void tratarNomeAluno(char nome[], listaAlunos *lista) {
    char auxNome[100] = {0};
    int tamAuxNome;

    // Tratando o nome (retirando espaços excedentes)
    char *pNome = strtok(nome, " ");
    while (pNome != NULL) {
        strcat(auxNome, pNome);
        strcat(auxNome, " ");
        pNome = strtok(NULL, " ");
    }

    tamAuxNome = strlen(auxNome) - 1;
    auxNome[tamAuxNome] = '\0'; // Removendo o espaço final extra
    strcpy(lista -> alunos[lista -> qtdAlunos].nome, auxNome); // Colocando o nome tratado na lista de Professores
}

// Função que faz a verificação de todas as validações, retornando se teve ou não algum erro.
boolean verificaErros(boolean erros[]) {
    boolean erro = false;
    
    if (erros[0]) {
        puts("Algo no Nome é inválido.");
        erro = true;
    } if (erros[1]) {
        puts("Sexo inválido");
        erro = true;
    } if (erros[2]) {
        puts("CPF inválido.");
        erro = true;
    } if (erros[3]) {
        puts("Data de Nascimento Inválida.\n");
        erro = true;
    }

    return erro;
}

boolean verificarCPF(char cpf[], listaAlunos *listaA, listaProf *listaP){
  boolean erro = false;

    int aux, aux2;
  
    if (!listaAlunosVazia(listaA) && listaProfVazia(listaP)) {
        // Verifica só a lista de alunos
        for(int iCont = 0; iCont < listaA -> qtdAlunos; iCont++){
          aux = strcmp(cpf, listaA -> alunos[iCont].cpf);
           if(aux == 0) {
            printf("CPF já existe para outro aluno!\n");
            erro = true;
            return erro;
           }
        }

    } else if (listaAlunosVazia(listaA) && !listaProfVazia(listaP)) {
        // Verifica só a lista de professor
          for(int jCont = 0; jCont < listaP -> qtdProfessores; jCont++){
             aux2 = strcmp(cpf, listaP -> professores[jCont].cpf);
                if(aux2 == 0){
                    printf("CPF já existe para algum professor!\n");
                    erro = true;
                    return erro; 
                }
          }        
    } else {
        // Verifica ambas as listas
        for(int iCont = 0; iCont < listaA -> qtdAlunos; iCont++){
          aux = strcmp(cpf, listaA -> alunos[iCont].cpf);
           if(aux == 0) {
                printf("CPF já existe para outro aluno!\n");
                erro = true;
                return erro;
           }
        }
        for(int jCont = 0; jCont < listaP -> qtdProfessores; jCont++){
            aux2 = strcmp(cpf, listaP -> professores[jCont].cpf);
            if(aux2 == 0){
                printf("CPF já existe para algum professor!\n");
                erro = true;
                return erro;   
            }     
        }
    } 

  return erro;
}
