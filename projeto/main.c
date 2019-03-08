/**
 * Objetivo: Este programa deve rotacionar uma matriz N x M (N linhas por M colunas) 90º no sentido horário.
 * Autor: Pedro Henrique Bernini Silva.
 * Atualizado em: Sex 08 Mar 2019.
**/
 
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "principais.c"
#include "auxiliares.c"

int main(int argc, char *argv[]){

    //Imprime cabeçalho
    header();
   
    //Linhas
    int n;
    char linhas[6];
    strcpy(linhas,argv[1]);
    n = atoi(argv[1]);

    //Colunas
    int m;
    char colunas[6];
    strcpy(colunas,argv[2]);
    m = atoi(argv[2]);

    //Threads
    int nThreads;
    nThreads = atoi(argv[3]);

    //Arquivos
    char nomeArquivo[30];
    char nomeArquivoFinal[30];
    strcpy(nomeArquivo, argv[4]);
    strcpy(nomeArquivoFinal, argv[5]);

    printf("\n| MATRIZ ORIGINAL |\n");
    printf("Nome do arquivo: %s\n", nomeArquivo);
    printf("Linhas: %d\n", n);
    printf("Colunas: %d\n", m);

    printf("\n--------------------------------------------------------\n");
    printf("Rotacionando Matriz com %d Threads...\n", nThreads);
    printf("--------------------------------------------------------\n");
    
    int i;
    int j;
    double elemento;

    double **matrizOrg;
    matrizOrg = (double **) malloc (n * sizeof (double *));
    for (i = 0; i < n; i++)
        matrizOrg[i] = (double *) malloc (m * sizeof (double));

    char diretorio[100] = "";
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,nomeArquivo);
    FILE *arquivo = fopen(diretorio,"r");

    for(i=0;i<n;i++){
	for(j=0;j<m;j++){
            fscanf(arquivo,"%lf",&elemento);
            matrizOrg[i][j] = elemento;
        }
    }

    double **matrizRot;
    matrizRot = (double **) malloc (m * sizeof (double *));
    for (i = 0; i < m; i++)
        matrizRot[i] = (double *) malloc (n * sizeof (double));

    int nLeituras = n*m/nThreads;
    int sobra = n*m%nThreads;
    
    //Cria threads passando argumentos necessários
    for(i=0; i<nThreads; i++){
	vArgumentos[i].idThread = i + 1;
	vArgumentos[i].nLinhas = n;
	vArgumentos[i].nColunas = m;
	vArgumentos[i].nThreads = nThreads;
	vArgumentos[i].nLeituras = nLeituras;
	if(i == (nThreads - 1))
	    vArgumentos[i].nLeituras += sobra;
	vArgumentos[i].posicaoInicial = nLeituras*i + 1;
	vArgumentos[i].matrizOrg = matrizOrg;
	vArgumentos[i].matrizRot = matrizRot;

	pthread_create(&threadID[i], NULL, threadRotacionarValores, (void *)&vArgumentos[i]);
    }

    //Faz com que a main() não termine antes das outras threads
    for(i=0; i<nThreads; i++)
        pthread_join(threadID[i], NULL);

    strcpy(diretorio,"");
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,nomeArquivoFinal);
    FILE *arquivoFinal = fopen(diretorio,"w");

    for(i=0;i<m;i++){
        fprintf(arquivoFinal," ");
	for(j=0;j<n;j++){
	    fprintf(arquivoFinal, "%lf  ", matrizRot[i][j]);
            if(j != (n-1))
		fprintf(arquivoFinal," ");
        }
	fprintf(arquivoFinal,"\n");
    }

    printf("\nMatriz rotacionada com sucesso!\n");
    printf("Nome do arquivo: %s\n\n", nomeArquivoFinal);
    
    return 0;
}
