# Autômato Finito não Determinístico

## Introdução

Esse trabalho foi desenvolvido para a disciplina Linguagens Formais e Autômatos na Universidade Presbiteriana Mackenzie.

## Objetivo

O objetivo deste trabalho é escrever um programa que tenha como entrada um AFND especificado em um arquivo texto, o programa deve simular qualquer AFND informado pelo arquivo e testar várias palavras sobre alfabeto do AFND. O arquivo texto deverá ter a seguinte configuração:

1. Na primeira linha, os símbolos do alfabeto de entrada (), com letras sempre em minúsculo, em ordem alfabética sempre começando por a, e sem espaços em branco entre os símbolos, o tamanho do alfabeto é limitado a 10 símbolos na primeira linha. Por exemplo se quiser um alfabeto com 5 símbolos como teríamos (abcde) tudo junto.
2. Na segunda linha, o número de Q estados, para facilitar a implementação o estado inicial será sempre o primeiro estado (q0) e qualquer AFND terá no máximo 20 estados (q0, q1, .... q19), ou seja, |Q|<=20.
3. Na terceira linha temos um número F indicando a quantidade de estados finais e na linha seguinte (quarta linha) a lista dos estados finais separados por espaço em branco na mesma linha, considere que F <= Q.
4. Na quinta linha temos o número de N transições do AFND, e nas N linhas seguintes as transições especificadas no seguinte formato, separadas por espaço em branco:
   \<estado corrente\> branco \<símbolo em  \> branco \<estado chegada\>
5. Ao final das N transições, teremos uma linha com um inteiro T especificando o número de palavras que deverão ser testadas no AFND, as palavras estarão cada uma em uma linha contendo somente os símbolos do alfabeto de entrada (). Considere também, que cada palavra terá no máximo 100 caracteres.

### Saída

O programa deverá, conforme especificado no arquivo de entrada, processar a as palavras, usando AFND especificado, e depois, escrever o resultado na tela com as seguintes sentenças: palavra processada e a informação "OK" caso do AFND tenha parado o processamento no estado de aceitação e "not OK" caso contrário.

Considere que termos as seguintes restrições para cada conjunto:

#### Exemplos

| Entrada |      Saída      |
| :-----: | :-------------: |
|   ab    |    1: aab OK    |
|    3    |  2: aababab OK  |
|    1    | 3: ababb not OK |
|    2    | 4: bbaa not OK  |
|    4    |   5: b not OK   |
|  0 a 0  |                 |
|  0 a 1  |                 |
|  0 b 0  |                 |
|  1 b 2  |                 |
|    5    |                 |
|   aab   |                 |
| aababab |                 |
|  ababb  |                 |
|  bbaa   |                 |
|    b    |                 |

## Instruções para executar o programa

_OBS: Se você não tiver GCC instalado em sua máquina, troque o compilador no [Makefile](./Makefile)._

Clone esse repositório em sua máquina, insira no arquivo `input.txt` a entrada do seu AFnD esperada, acesse o diretório do programa em um shell e execute o comando `make`.
