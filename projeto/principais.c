#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

//Estrutura de argumentos para threads
typedef struct Argumentos{
    int idThread;
    int nLinhas;
    int nColunas;
    int nThreads;
    int nLeituras;
    int posicaoInicial;
    char nomeArquivo[30];
    double **elemento;
}argumentos;

//Variáveis globais do programa
pthread_t threadID[16];
argumentos vArgumentos[16];

/**
 * Função que representa uma thread genérica que deve percorrer
 * o arquivo a partir de um ponto inicial e modificar a matriz rotacionada
 *
 * @param *vArgumentos - ponteiro para uma estrutura de argumentos
**/
void *threadRotacionarValores(void *vArgumentos){
    argumentos *argumentos = vArgumentos;

    //Calcula a posição de referência na matriz que equivale a posição [0][0] da matriz original
    int linhaReferencia = 0; 
    int colunaReferencia = argumentos->nLinhas - 1;

    //Abre arquivo da matriz
    char diretorio[100] = "";
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,argumentos->nomeArquivo);
    strcat(diretorio,".dat");
    FILE *arquivo = fopen(diretorio,"r");

    //Calcula índice linha segundo posição inicial
    int linha;
    if(argumentos->posicaoInicial%argumentos->nColunas > 0 || argumentos->posicaoInicial/argumentos->nColunas == 0)
        linha = argumentos->posicaoInicial/argumentos->nColunas;
    else
        linha = argumentos->posicaoInicial/argumentos->nColunas - 1;

    //Calcula índice coluna segundo posição inicial
    int coluna;
    if(argumentos->posicaoInicial-argumentos->nColunas < 0)
        coluna = (argumentos->posicaoInicial-argumentos->nColunas)%argumentos->nColunas + argumentos->nColunas;
    else if((argumentos->posicaoInicial-argumentos->nColunas)%argumentos->nColunas == 0)
        coluna = argumentos->nColunas;
    else
	coluna = (argumentos->posicaoInicial-argumentos->nColunas)%argumentos->nColunas;
    coluna--;

    double elemento;
    int linhaRot;
    int colunaRot;

    //Percorre matriz até a posição inicial 
    register int i;
    argumentos->posicaoInicial--;
    for(i=1;i<=argumentos->posicaoInicial;i++){
        fscanf(arquivo,"%lf",&elemento);
    }

    //Lê um elemento e salva na matriz rotacionada nLeitura vezes
    int j;
    for(j=0;j<argumentos->nLeituras;j++){

        fscanf(arquivo,"%lf",&elemento);
    
        linhaRot = coluna;
        colunaRot = colunaReferencia - linha;

	//Coloca o elemento da matriz original na posição correta da matriz rotacionada
	argumentos->elemento[linhaRot][colunaRot] = elemento; 

	if(coluna == argumentos->nColunas-1){
	    coluna = 0;
	    linha++;
	}else
	    coluna++;
    }

    //Finaliza thread
    pthread_exit(NULL);
}
