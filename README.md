# Rotaciona Matriz

## Objetivo
Este programa utiliza múltiplas threads para rotacionar uma matriz N x M (N linhas por M colunas) 90º no sentido horário. O programa deverá ser escrito para o sistema operacional Linux e obrigatoriamente utilizar a biblioteca POSIX Threads.

## Descrição do problema a ser resolvido
Considere uma matriz N x M (N linhas por M colunas) que contém valores em ponto flutuante, positivos ou negativos.  O  programa  deverá  utilizar  múltiplos threads  para  rotacionar  essa  matriz  em  90º. Os dados da matriz original devem vir de um arquivo e a matriz resultante deve ser gravada em arquivo com a extensão .rot. O programa deve ser testado para 2, 4, 8 e 16 threads, com matrizes 1000 x 1000.
    
## Entradas e saídas de valores para o programa
Entradas: os valores N, M, T, <Arquivo Entrada> e <Arquivo Saída>  -- respectivamente, as dimensões da matriz (N x M); o número de threads; e o arquivo onde estão os dados de entrada e o arquivo onde devem estar os dados de saída -- devem ser informados pelo usuário no início do programa. Para os testes, considere valoresgrandes (maiores ou iguais a 100) para N e M.

Saídas: arquivo com a matriz rotacionada. O arquivo gerado deve ter o mesmo nome do arquivo original com a extensão .rot.
