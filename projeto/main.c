/**
 * Objetivo: Este programa deve rotacionar uma matriz N x M (N linhas por M colunas) 90º no sentido horário.
 * Autor: Pedro Henrique Bernini Silva.
 * Atualizado em: Sex 11 Mar 2019.
**/
 
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#include "principais.c"
#include "auxiliares.c"

int main(int argc, char *argv[]){

    //Medir tempo de todo o programa
    clock_t tempos[4];
    tempos[0] = clock();
    
    if(argc != 6){
	printf("\nArgumentos invalidos!\n");
	printf("Tente: ./<Nome do Executavel> <Quantidade de Linhas> <Quantidade de Colunas> <Numero de Threads> <Nome do Arquivo de Entrada> <Nome do Arquivo de Saida>\n\n");
	return 0;
    }
	
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

    if (arquivo == NULL) {
	printf("\nO arquivo '%s' não existe na pasta '../arquivos/matrizes/'\n", nomeArquivo);
	printf("Finalizando programa.\n\n");
	return 0;
    }

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
    
    //Medir tempo de execução da rotação da matriz
    tempos[2] = clock();

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
    
    tempos[3] = clock();
    double TempoRotacao = (tempos[3] - tempos[2]) * 1000.0 / CLOCKS_PER_SEC;

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

    tempos[1] = clock();
    double TempoPrograma = (tempos[1] - tempos[0]) * 1000.0 / CLOCKS_PER_SEC;

    printf("\nMatriz rotacionada com sucesso!\n");
    printf("Nome do arquivo: %s\n\n", nomeArquivoFinal);
    printf("Tempo gasto para rotacionar a matriz -> %g ms.\n", TempoRotacao);
    printf("Tempo total do programa -> %g ms.\n\n", TempoPrograma);

    return 0;
}
