/**
 * Objetivo: Este programa deve rotacionar uma matriz N x M (N linhas por M colunas) 90º no sentido horário.
 * Autor: Pedro Henrique Bernini Silva.
 * Atualizado em: Seg 01 Mar 2019.
**/
 
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "principais.c"
#include "auxiliares.c"

int main(){

    //Imprime cabeçalho
    header();

    //Variáveis de tratamento (PARTE 1)
    int potencia;
    int inteiro = 0;
    int valido;
    int i;
    char validador;
    
    /* PARTE 1 - GERAR MATRIZ */
    printf("\n| PARTE 1 - GERANDO MATRIZ ORIGINAL |\n");
    printf("\nPara gerar a matriz, entre com...\n");

	//Trata entrada de linhas
        int m;
        char linhas[6];
        do{
            printf("\n\tNumero de linhas [M]: ");
            fgets(linhas,6,stdin);	
	    potencia = strlen(linhas)-1;

            i = 0;
	    valido = 1;
            validador = linhas[i];
            do{
                if(!validaInt(validador,&inteiro,potencia--))
                    valido = 0;
                i++;
                validador = linhas[i];
            }while(validador!='\n');

            if(valido){
                linhas[i] = ' ';
	        m = inteiro;
            }else{
                printf("\tCaractere invalido!\n");
                printf("\tDigite novamente...\n");
	    }
        }while(!valido);

	//Trata entrada de colunas
        inteiro = 0;
        int n;
        char colunas[6];
        do{
            printf("\n\tNumero de colunas [N]: ");
            fgets(colunas,6,stdin);
	    potencia = strlen(colunas)-1;

            i = 0;
            valido = 1;
            validador = colunas[i];
            do{
                if(!validaInt(validador,&inteiro,potencia--))
                    valido = 0;
                i++;
                validador = colunas[i];
            }while(validador!='\n');

            if(valido){
                colunas[i] = ' ';
	        n = inteiro;
            }else{
                printf("\tCaractere invalido!\n");
                printf("\tDigite novamente...\n");
	    }
        }while(!valido);

	//Recebe entrada do arquivo
        char nomeArquivo[30];
        printf("\n\tNome do arquivo: ");
	fgets(nomeArquivo,30,stdin);

	//Gera matriz m*n no arquivo
        printf("\n--------------------------------------------------------\n");
        geraMatriz(linhas,colunas,nomeArquivo);
        printf("--------------------------------------------------------\n");
    /**/

    /* PARTE 2 - ESCOLHER NUMERO DE THREADS */
    printf("\n| PARTE 2 - NUMERO DE THREADS PARA ROTACIONAR A MATRIZ |\n");
    printf("\n** O numero de threads deve ser entre 1 e 16 e menor ou igual MxN **\n");

	//Trata entrada de threads
	int nThreads;
	printf("\n\tNumero de threads [T]: ");
	scanf("%d",&nThreads);

	while(nThreads<=0 || nThreads>16 || nThreads>m*n){
	    printf("\tNumero invalido!\n");
	    printf("\tDigite novamente...\n");

	    printf("\n\tNumero de threads (T): ");
	    scanf("%d",&nThreads);
	}

	printf("\n--------------------------------------------------------\n");
        printf("Rotacionando Matriz...\n");
	printf("--------------------------------------------------------\n");
    /**/


    /* PARTE 3 - ROTACIONAR MATRIZ */
    double matrizRot[n][m];

    int nLeituras = m*n/nThreads;
    int sobra = m*n%nThreads;

    //Cria threads passando argumentos necessários
    for(i=0; i<nThreads; i++){
	vArgumentos[i].idThread = i + 1;
	vArgumentos[i].nLinhas = m;
	vArgumentos[i].nColunas = n;
	vArgumentos[i].nThreads = nThreads;
	vArgumentos[i].nLeituras = nLeituras;
	if(i == (nThreads - 1))
	    vArgumentos[i].nLeituras += sobra;
	vArgumentos[i].posicaoInicial = nLeituras*i + 1;
	strcpy(vArgumentos[i].nomeArquivo,nomeArquivo);
	vArgumentos[i].elemento = matrizRot[0];

	pthread_create(&threadID[i], NULL, threadRotacionarValores, (void *)&vArgumentos[i]);
    }

    //Faz com que a main() não termine antes das outras threads
    for(i=0; i<nThreads; i++)
        pthread_join(threadID[i], NULL);

    /* PARTE 4 - SALVAR NOVA MATRIZ ROTACIONADA */
    char diretorio[100] = "";
    strcat(diretorio,"../arquivos/matrizes/");
    strcat(diretorio,nomeArquivo);
    strcat(diretorio,".rot");
    FILE *arquivo = fopen(diretorio,"w");

    int j;
    for(i=0;i<n;i++){
        fprintf(arquivo," ");
	for(j=0;j<m;j++){
	    fprintf(arquivo, "%lf  ", matrizRot[i][j]);
            if(j != (m-1))
		fprintf(arquivo," ");
        }
	fprintf(arquivo,"\n");
    }

    printf("\nMatriz rotacionada com sucesso!\n");
    printf("Nome da matriz original: %s.dat\n", nomeArquivo);
    printf("Nome da matriz rotacionada: %s.rot\n\n", nomeArquivo);
    
    return 0;
}
