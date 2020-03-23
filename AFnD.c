#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Entrega de trabalho - Simulador de AFnD

Nós,

Daniel T. Rodrigues 31839010
Cassia A. Barbosa 31808204

declaramos que

todas as respostas são fruto de nosso próprio trabalho,
não copiamos respostas de colegas externos à equipe,
não disponibilizamos nossas respostas para colegas externos à equipe e
não realizamos quaisquer outras atividades desonestas para nos beneficiar ou prejudicar outros.
*/

// OBS: Estamos usando o formatador de código em C padrão do VSCode

void printPalavra(char *p);

int main(void)
{

    // Leitura do arquivo de entrada
    FILE *fp;
    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("ERRO: Arquivo 'input.txt' não encontrado.\n");
        return 1;
    }

    fseek(fp, 0, SEEK_END);
    int tamanho = ftell(fp);
    rewind(fp);

    char *entradas = malloc(sizeof(char) * (tamanho + 1));
    size_t tamanhoLido = fread(entradas, sizeof(char), tamanho, fp);
    if ((int)tamanhoLido != tamanho)
    {
        printf("ERRO: Arquivo não lido corretamente.\n");
        return 1;
    }
    entradas[tamanho] = '\0';
    fclose(fp);

    //
    // Linha 1: Definir alfabeto
    //

    int i = 0;
    char simboloEsperado = 'a';
    char alfabeto[10] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'};
    while (entradas[i] != '\n')
    {
        if (i == 10)
        {
            printf("\nERRO: São permitidos no máximo 10 símbolos no alfabeto.\n");
            return 1;
        }
        if (entradas[i] != simboloEsperado)
        {
            printf("\nERRO: São aceitas somente letras minúsculas e em ordem alfabética para o alfabeto.\n");
            return 1;
        }
        alfabeto[i] = entradas[i];
        i++;
        simboloEsperado++;
    }
    int tamanhoAlfabeto = i;

    //
    // Linha 2: Definir número de estados
    //

    i++;
    char entradaEstados[2] = {' ', ' '};
    int contador = 0;
    while (entradas[i] != '\n')
    {
        if (contador > 1)
        {
            printf("\nERRO: Número máximo de estados: 20.\n");
            return 1;
        }
        entradaEstados[contador] = entradas[i];
        i++;
        contador++;
    }
    int nEstados = atoi(entradaEstados);
    if (nEstados > 20)
    {
        printf("\nERRO: Número máximo de estados: 20.\n");
        return 1;
    }

    //
    // Linha 3: Número de estados finais
    //

    i++;
    contador = 0;
    char entradaFinais[2] = {' ', ' '};
    while (entradas[i] != '\n')
    {
        entradaFinais[contador] = entradas[i];
        i++;
        contador++;
    }
    int nFinais = atoi(entradaFinais);
    if (nFinais > nEstados)
    {
        printf("\nERRO: Número de estados finais deve ser menor ou igual ao de estados.\n");
        return 1;
    }

    //
    // Linha 4: Estados finais
    //

    i++;
    int estadosFinais[nFinais];
    contador = 0;
    int contadorEstadosFinais = 0;
    char estadoFinal[2] = {' ', ' '};
    while (1)
    {
        if (entradas[i] == ' ')
        {
            int e = atoi(estadoFinal);
            if (e > nEstados)
            {
                printf("\nERRO: Estado final %d inválido.\n", e);
                return 1;
            }
            estadosFinais[contadorEstadosFinais] = e;
            contadorEstadosFinais++;
            contador = 0;
            estadoFinal[1] = ' ';
        }
        else if (entradas[i] == '\n')
        {
            int e = atoi(estadoFinal);
            if (e > nEstados)
            {
                printf("\nERRO: Estado final %d inválido.\n", e);
                return 1;
            }
            estadosFinais[contadorEstadosFinais] = e;
            break;
        }
        else
        {
            estadoFinal[contador] = entradas[i];
            contador++;
        }
        i++;
    }

    //
    // Linha 5: Número de transições
    //

    i++;
    contador = 0;
    char entradaTransicoes[4] = {' ', ' ', ' ', ' '};
    while (entradas[i] != '\n')
    {
        entradaTransicoes[contador] = entradas[i];
        i++;
        contador++;
    }
    int nTransicoes = atoi(entradaTransicoes);
    if (nTransicoes > nEstados * tamanhoAlfabeto * nEstados)
    {
        printf("\nERRO: Número de transações deve ser menor ou igual ao número de estados ao quadrado vezes o tamanho do alfabeto.\n");
        return 1;
    }

    //
    // Linhas 6 até (5 + nTransicoes): Definições das transições
    //

    i++;
    // Inicializar matriz de transições com valores -1 para marcar fim de estados possíveis
    int matrizTransicoes[nEstados][tamanhoAlfabeto][nEstados];
    for (int lin = 0; lin < nEstados; lin++)
    {
        for (int col = 0; col < tamanhoAlfabeto; col++)
        {
            for (int alt = 0; alt < nEstados; alt++)
            {
                matrizTransicoes[lin][col][alt] = -1;
            }
        }
    }

    // Entrar com valores de transição na matriz
    char entradaTransicao[2] = {' ', ' '};
    contador = 0;
    char *tipo = "INT"; // Essa flag irá avaliar se o tipo de entrada
    // será um número ou símbolo (forma de tratar é diferente)
    int estadoPrevio, simbolo, estadoFuturo, contadorMatriz, t = 0;
    // Estado prévio e símbolo são as chaves i e j da matriz de transição
    // Estado futuro entra como valor da matriz[i][j][k] e contador matriz é a chave k
    // t é o contador do número de transições
    while (t < nTransicoes)
    {
        if (entradas[i] == '\n')
        {
            contador = 0;
            estadoFuturo = atoi(entradaTransicao);
            if (estadoFuturo > nEstados)
            {
                printf("\nERRO: Estado %d inválido.\n", estadoFuturo);
                return 1;
            }
            contadorMatriz = 0;
            while (matrizTransicoes[estadoPrevio][simbolo][contadorMatriz] != -1)
                contadorMatriz++;
            matrizTransicoes[estadoPrevio][simbolo][contadorMatriz] = estadoFuturo;
            t++;
        }
        else if (entradas[i] == ' ')
        {
            contador = 0;
            if (strncmp(tipo, "INT", 3) == 0)
            {
                estadoPrevio = atoi(entradaTransicao);
                if (estadoPrevio > nEstados)
                {
                    printf("\nERRO: Estado %d inválido.\n", estadoPrevio);
                    return 1;
                }
                tipo = "CHAR";
            }
            else if (strncmp(tipo, "CHAR", 3) == 0)
            {
                simbolo = entradaTransicao[0] - 'a';
                tipo = "INT";
            }
        }
        else
        {
            if (strncmp(tipo, "INT", 3) == 0)
            {
                entradaTransicao[contador] = entradas[i];
                contador++;
            }
            else
            {
                entradaTransicao[0] = entradas[i];
            }
        }
        i++;
    }

    // Printar matriz de transições para verificação
    // Descomente o comentário abaixo (linha 265-289) para ver a matriz de transição na tela de saída.

    // printf("\nMatriz de transições:\n[\n\t");
    // for (int lin = 0; lin < nEstados; lin++)
    // {
    //     for (int col = 0; col < tamanhoAlfabeto; col++)
    //     {
    //         for (int alt = 0; alt < nEstados; alt++)
    //         {
    //             if (alt == 0)
    //             {
    //                 printf("[%d, ", matrizTransicoes[lin][col][alt]);
    //             }
    //             else if (alt == nEstados - 1)
    //             {
    //                 printf("%d]", matrizTransicoes[lin][col][alt]);
    //             }
    //             else
    //             {
    //                 printf("%d, ", matrizTransicoes[lin][col][alt]);
    //             }
    //         }
    //         printf("\t");
    //     }
    //     printf("\n\t");
    // }
    // printf("\n]\n");

    //
    // Linha (6 + nTransicoes): Número de palavras a serem testadas
    //

    contador = 0;
    char entradaPalavras[3] = {' ', ' ', ' '};
    while (entradas[i] != '\n')
    {
        entradaPalavras[contador] = entradas[i];
        i++;
        contador++;
    }
    int nPalavras = atoi(entradaPalavras);

    //
    // Linhas (7 + nTransicoes) até (7 + nTransicoes + nPalavras): Testes
    //

    i++;
    char palavra[100];
    int q[nEstados];       // Armazenará os possíveis estados do AFnD, com 1 está ativo e 0 quando não está.
    int qFuturo[nEstados]; // Armazenará os próximos estados;
    char *res;             // Armazenará o resultado do AFnD na palavra
    for (int p = 1; p <= nPalavras; p++)
    {
        q[0] = 1; // Começará no estado q0.
        for (int e = 1; e < nEstados; e++)
            q[e] = 0; // Outros estados começam inativos.
        contador = 0;
        for (int l = 0; l < 100; l++)
        {
            // Reinicializar a palavra
            palavra[l] = ' ';
        }
        while (entradas[i] != '\n' && entradas[i] != '\0')
        {
            if (contador >= 100)
            {
                printf("\nERRO: Número máximo de caracteres permitido para uma palavra é 100.\n");
                return 1;
            }
            palavra[contador] = entradas[i];
            i++;
            contador++;
        }
        // Temos a palavra, agora executar o AFnD nela
        contador = 0;
        while (contador < 100 && palavra[contador] != ' ')
        {
            for (int e = 0; e < nEstados; e++)
            {
                // Reinicializar estados futuros
                qFuturo[e] = 0;
            }
            for (int e = 0; e < nEstados; e++)
            {
                // Achar estados ativos e aplicar AFnD neles
                if (q[e])
                {
                    contadorMatriz = 0;
                    while (contadorMatriz < nEstados && matrizTransicoes[e][palavra[contador] - 'a'][contadorMatriz] != -1)
                    {
                        qFuturo[matrizTransicoes[e][palavra[contador] - 'a'][contadorMatriz]] = 1;
                        contadorMatriz++;
                    }
                }
            }
            for (int e = 0; e < nEstados; e++)
            {
                // Tornar qFuturo o q atual
                q[e] = qFuturo[e];
            }
            contador++;
        }
        res = "not OK";
        // Avaliar se algum dos estados é estado final
        for (int k = 0; k < nFinais; k++)
        {
            if (q[estadosFinais[k]])
            {
                res = "OK";
            }
        }
        printf("%d: ", p);
        printPalavra(palavra);
        printf(" %s\n", res);
        i++;
    }
    return 0;
}

void printPalavra(char *p)
{
    int i = 0;
    while (p[i] != ' ')
        printf("%c", p[i++]);
}
