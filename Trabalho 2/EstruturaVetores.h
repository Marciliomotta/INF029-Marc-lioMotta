#ifndef TRABALHO2_ESTRUTURAVETORES_H
#define TRABALHO2_ESTRUTURAVETORES_H
#define TAM 10

enum {
  TODAS_ESTRUTURAS_AUXILIARES_VAZIAS = -11,
  NOVO_TAMANHO_INVALIDO = 1,
  NUMERO_INEXISTENTE = 2,
  ESTRUTURA_AUXILIAR_VAZIA = 3,
  TAMANHO_INVALIDO = 4,
  SEM_ESPACO_DE_MEMORIA = 5,
  POSICAO_INVALIDA = 6,
  JA_TEM_ESTRUTURA_AUXILIAR = 7,
  SEM_ESTRUTURA_AUXILIAR = 8,
  SEM_ESPACO = 9,
  SUCESSO = 10
};

typedef struct reg {
  int conteudo;
  struct reg *prox;
} No;

typedef struct dados {
  int *pont;
  int qtd;
  int tam;
}Principal;



int ehPosicaoValida(int posicao);
int criarEstruturaAuxiliar(int posicao, int tamanho);
int inserirNumeroEmEstrutura(int posicao, int valor);
int excluirNumeroDoFinaldaEstrutura(int posicao);
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor);
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]);
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]);
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]);
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho);
int getQuantidadeElementosEstruturaAuxiliar(int posicao);
No *montarListaEncadeadaComCabecote();
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]);
void destruirListaEncadeadaComCabecote(No **inicio);
void inicializar();
void finalizar();

#endif // TRABALHO2_ESTRUTURAVETORES_H