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
    double **matrizOrg;
    double **matrizRot;
}argumentos;

//Vari�veis globais do programa
pthread_t threadID[16];
argumentos vArgumentos[16];

/**
 * Fun��o que representa uma thread gen�rica que deve percorrer
 * o arquivo a partir de um ponto inicial e modificar a matriz rotacionada
 *
 * @param *vArgumentos - ponteiro para uma estrutura de argumentos
**/
void *threadRotacionarValores(void *vArgumentos){
    argumentos *argumentos = vArgumentos;

    //Calcula a posi��o de refer�ncia na matriz que equivale a posi��o [0][0] da matriz original
    int linhaReferencia = 0; 
    int colunaReferencia = argumentos->nLinhas - 1;

    //Calcula �ndice linha segundo posi��o inicial
    int linha;
    if(argumentos->posicaoInicial%argumentos->nColunas > 0 || argumentos->posicaoInicial/argumentos->nColunas == 0)
        linha = argumentos->posicaoInicial/argumentos->nColunas;
    else
        linha = argumentos->posicaoInicial/argumentos->nColunas - 1;

    //Calcula �ndice coluna segundo posi��o inicial
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

    //L� um elemento e salva na matriz rotacionada nLeitura vezes
    int j;
    for(j=0;j<argumentos->nLeituras;j++){

        elemento = argumentos->matrizOrg[linha][coluna];
    
        linhaRot = coluna;
        colunaRot = colunaReferencia - linha;

	//Coloca o elemento da matriz original na posi��o correta da matriz rotacionada
	argumentos->matrizRot[linhaRot][colunaRot] = elemento; 

	if(coluna == argumentos->nColunas-1){
	    coluna = 0;
	    linha++;
	}else
	    coluna++;
    }

    //Finaliza thread
    pthread_exit(NULL);
}
