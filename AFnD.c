#include <stdio.h>

/*
Entrega de trabalho - Nome do trabalho

Nós,

Daniel T. Rodrigues 31839010
Cassia A. Barbosa 31808204

declaramos que

todas as respostas são fruto de nosso próprio trabalho,
não copiamos respostas de colegas externos à equipe,
não disponibilizamos nossas respostas para colegas externos à equipe e
não realizamos quaisquer outras atividades desonestas para nos beneficiar ou prejudicar outros.
*/

int main(void)
{
    char alfabeto[1000];
    FILE *fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("Erro na abertura do arquivo.");
        return 1;
    }

    // Transição de estados afd - linhas: q0, q1; colunas: a, b
    int trans[2][2] = {{0, 1},
                    {1, 0}};

    // Transição de estados para afnd: matriz tridimensional, ou seja, cada célula de uma matriz bidimensional será um vetor.

    fscanf(fp, "%s", alfabeto);
    if (alfabeto == NULL)
    {
        printf("arquivo vazio\n");
    }
    printf("alfabeto = %s", alfabeto);
    fprintf(fp, "teste");
    fclose(fp);
    return 0;
}