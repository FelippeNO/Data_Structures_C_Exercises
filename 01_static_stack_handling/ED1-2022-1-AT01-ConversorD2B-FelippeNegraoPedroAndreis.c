
//---------------------------------------------------------------- LIBRARIES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//---------------------------------------------------------------- GLOBAL

#define LENGTH 50
typedef struct
{
    int vector[LENGTH];
    int top;
} StaticStack;

//---------------------------------------------------------------- FUNCTIONS

// Função que inicializa a pilha. //
void initializeStack(StaticStack *p)
{
    p->top = 0;
}

// Função que verifica se a pilha está vazia. //
bool isEmptyStaticStack(StaticStack *p)
{
    return (p->top == 0);
}

// Função que verifica se a pilha está cheia. //
bool isFullStaticStack(StaticStack *p)
{
    return (p->top == LENGTH);
}

// Função que insere um elemento na pilha. //
int stackLength(StaticStack *p)
{
    return (p->top);
}

// Função que adiciona um elemento da pilha. //
void pushStack(StaticStack *stack, int x)
{

    if (!isFullStaticStack(stack))
    {
        // DEBUG PRINT: Printa o valor do topo antes de inserir um novo elemento.
        printf("TAMANHO PILHA INICIAL EMP: %d\n", stackLength(stack));
        stack->vector[stack->top] = x;
        stack->top++;
        // DEBUG PRINT: Printa o valor do topo depois de inserir um novo elemento.
        printf("TAMANHO PILHA FINAL EMP: %d\n", stackLength(stack));
    }
    else
    {
        // DEBUG PRINT: Avisa que a pilha está cheia.
        printf("Aviso: pilha cheia!\n");
    }
}

// Função que remove um elemento da pilha. //
int popStack(StaticStack *stack, int x)
{
    if (!isEmptyStaticStack(stack))
    {
        // DEBUG PRINT: Printa o valor do topo antes de remover um novo elemento.
        printf("TAMANHO PILHA DESEMP INICIAL: %d\n", stackLength(stack));
        x = stack->vector[stack->top - 1];
        stack->top--;
        // DEBUG PRINT: Printa o valor do topo depois de remover um novo elemento.
        printf("TAMANHO PILHA DESEMP FINAL: %d\n", stackLength(stack));
        return x;
    }
    else
    {
        // DEBUG PRINT: Avisa que a pilha está vazia.
        printf("\nWarning: pilha esta vazia!\n");
        return 202;
    }
}

// Função que abre o arquivo de saída. //
FILE *OpenOutputFile(char *outputFileName)
{
    // DECLARAÇÕES--------
    FILE *pOutputFile; // CRIA A VARIÁVEL DO ARQUIVO DE SAÍDA.

    // FUNÇÕES INICIALIZADAS--------
    pOutputFile = fopen(outputFileName, "wt"); // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE SAÍDA.

    // CORPO--------
    if (pOutputFile == NULL) // SE HOUVER ERRO NA ABERTURA RETORNA NULO, SE NÃO, RETORNA O ARQUIVO.
    {
        // DEBUG PRINT: Avisa que houve problema na abertura do arquivo de saída.
        printf("PROBLEMAS NA ABERTURA DO ARQUIVO DE SAIDA\n");
        return NULL;
    }
    else
    {
        // DEBUG PRINT: Avisa que não houve problema na abertura do arquivo de saída.
        printf("\nARQUIVO ABERTO PARA ESCRITA COM SUCESSO!\n");
        return pOutputFile;
    }
}

// Função que converte, empilha e desempilha os elementos da pilha. //
int ConvertPushPop(StaticStack *Stack1, int intNum)
{
    // DECLARAÇÕES--------
    int binDigit; // VARIÁVEL QUE RECEBE O VALOR DO DIGITO BINÁRIO.

    // CORPO--------
    while (isEmptyStaticStack(Stack1) == true) //
    {
        do
        {
            binDigit = intNum % 2;       // ATRIBUI O RESTO DA DIVISÃO POR 2 AO DIGITO BINÁRIO.
            pushStack(Stack1, binDigit); // EMPILHA O DÍGITO NA PILHA 1.
            intNum = intNum / 2;         // DIVIDE O NÚMERO NORMAL PELO 2.
        } while (intNum != 0);
    }

    printf("\n"); // EMPILHAMENTO FINALIZADO.

    while (isEmptyStaticStack(Stack1) == false)
    {
        int digitBin = (popStack(Stack1, binDigit)); // VARIÁVEL QUE PUXA O VALOR DO DIGITO BINÁRIO DA PILHA 1.
        char binNumToChar[8];                        // VARIÁVEL STRING QUE ARMAZENARÁ O VALOR EM BINÁRIO.
        int binInt;                                  // VARIÁVEL INT QUE ARMAZENARÁ O VALOR EM BINÁRIO.
        int i = 0;                                   // VARIÁVEL DE INCREMENTO.

        for (i = 0; i <= 7; i++)
        {
            if (digitBin == 0)
            {
                binNumToChar[i] = 48;                    // ATRIBUI AO binNumToChar[i] 48 = 0 em ASCII.
                digitBin = (popStack(Stack1, binDigit)); // RETIRA DA PILHA 1 O PRÓXIMO DIGITO BINÁRIO.
            }
            else if (digitBin == 1)
            {
                binNumToChar[i] = 49;                    // ATRIBUI AO binNumToChar[i] 49 = 1 EM ASCII.
                digitBin = (popStack(Stack1, binDigit)); // RETIRA DA PILHA 1 O PRÓXIMO DIGITO BINÁRIO.
            }
            else if ((digitBin != 0) && (digitBin != 1))
            {
                binNumToChar[i] = 0; // ATRIBUI UM CARACTERE NULLO PARA NÃO SER CONVERTIDO.
                // DEBUG PRINT: Avisa que não pôde converter o dígito pois era diferente de 0 e 1.
                printf(" %d = NAO CONVERTEU!\n", i);
                digitBin = (popStack(Stack1, binDigit)); // RETIRA DA PILHA 1 O PRÓXIMO DIGITO BINÁRIO.
            }
        }

        for (i = 0; i <= 7; i++)
        {
            // DEBUG PRINT: Demonstra os valores que foram convertidos corretamente.
            printf("%c = %d\n", binNumToChar[i], binNumToChar[i]);
        }

        binInt = atoi(binNumToChar); // CONVERTE A STRING INTEIRA PARA BINARIO.
        // DEBUG PRINT: Confere pela última vez se a coversão foi bem sucedida.
        printf("BIN INTEGER = %d\n", binInt);
        return binInt; // RETORNA O NÚMERO BINÁRIO COMO INT.
    }
}

// Função que inicializa a segunda pilha, abre os arquivos de entrada e saída, e chama a função de conversão. //
void CoreFunction(char *inputFileName, char *outputFileName, StaticStack *Stack1)
{
    // DECLARAÇÕES--------
    FILE *pOutputFile = OpenOutputFile(outputFileName); // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE SAÍDA.
    FILE *pInputFile;                                   // VARIÁVEL DO ARQUIVO DE ENTRADA.
    StaticStack Stack2;                                 // VARIÁVEL DA PILHA 2.
    char Line[200];                                     // VARIÁVEL DA LINHA.
    char *result;                                       // VARIÁVEL DO RESULTADO DA LINHA.
    int intNum;                                         // VARIÁVEL QUE SERVIRÁ PARA TRANSFORMAR A LINHA EM INTEIRO.
    int k = 1;                                          // VARIÁVEL DE INCREMENTO DE CONTROLE.

    // FUNÇÕES INICIALIZADAS--------
    initializeStack(&Stack2);                // INICIALIZA A PILHA 2.
    pInputFile = fopen(inputFileName, "rt"); // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE ENTRADA.

    // CORPO--------
    if (pInputFile == NULL) // SE HOUVER ERRO NA ABERTURA RETORNA NULO, SE NÃO, O PROGRAMA SEGUE.
    {
        // DEBUG PRINT: Avisa que houve problema na abertura do arquivo de leitura.
        printf("PROBLEMAS NA ABERTURA DO ARQUIVO DE LEITURA\n");
        return;
    }
    else
    {
        // DEBUG PRINT: Avisa que não houve problema na abertura do arquivo de leitura.
        printf("\nARQUIVO ABERTO PARA LEITURA COM SUCESSO!\n");
    }

    while (!feof(pInputFile))
    {

        result = fgets(Line, 100, pInputFile); // LÊ A LINHA DO ARQUIVO DE LEITURA E ATRIBUI A STRING A RESULT.
        {
            intNum = atoi(Line); // PARSE DA STRING X EM INTEIRO.
            // DEBUG PRINT: Demonstra o número que vai ser convertido para binário.
            printf("\n---CONVERTENDO NUMERO: %d---\n\n", intNum);
            int convertedNumber = ConvertPushPop(Stack1, intNum); // ATRIBUI A VARIÁVEL COM O NUM JÁ CONVERTIDO EM BIN.
            pushStack(&Stack2, convertedNumber);                  // EMPILHA O NUMERO CONVERTIDO DE BIN PARA A PILHA 2.
            // DEBUG PRINT: Demonstra o número já convertido em bin e int para começar a printar no arquivo.
            printf("NUMERO CONVERTIDO PARA PRINTAR NO ARQUIVO DE SAIDA: %d\n", convertedNumber);
        }
    }
    // DEBUG PRINT: Avisa que vai começar a printar os números bin, inteiros, no arquivo de saída.
    printf("\nINICIANDO PRINT DOS NUMEROS NO ARQUIVO:\n");
    while (isEmptyStaticStack(&Stack2) == false)
    {
        // DEBUG PRINT: Avisa que vai começar a printar o número no arquivo de saída.
        printf("INICIO DO PRINT DO %do NUMERO\n", k);
        fprintf(pOutputFile, "%d\n", popStack(&Stack2, intNum)); // DESEMPILHA O NUMERO DA PILHA 2 E PRINTA NO ARQUIVO.
        // DEBUG PRINT: Avisa que printou o número no arquivo de saída.
        printf("PRINTOU O %do NUMERO\n", k);
        k++; // INCREMENTA CONTADOR DE CONTROLE.
    }
    fclose(pInputFile);  // FECHA ARQUIVO DE LEITURA.
    fclose(pOutputFile); // FECHA ARQUIVO DE SAÍDA.
}

// Função que trata as exceções. //
int CoreException(char *inputFileName, char *outputFileName, int argc)
{
    // DECLARAÇÕES--------
    FILE *pInputFile;  // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE LEITURA.
    FILE *pOutputFile; // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE SAÍDA.
    char *result;      // VARIÁVEL DO RESULTADO DA LINHA.
    char Line[100];    // VARIÁVEL DA LINHA.

    // EXCEÇÃO 1: ARGUMENTOS INVÁLIDOS--------
    if (argc < 3) // SE TIVER MENOS DE 3 ARGUMENTOS, O PROGRAMA RETORNA 1.
    {
        printf("EXCEPTION: FALTA DE ARGUMENTOS!\n");
        printf("NUMERO DE ARGUMENTOS ESPERADOS: 3\n");
        printf("NUMERO DE ARGUMENTOS DECLARADOS: %d\n", argc);
        return 1;
    }
    else if (argc > 3) // SE TIVER MAIS DE 3 ARGUMENTOS, O PROGRAMA RETORNA 1.
    {
        printf("EXCEPTION: EXCESSO DE ARGUMENTOS!\n");
        printf("NUMERO DE ARGUMENTOS ESPERADOS: 3\n");
        printf("NUMERO DE ARGUMENTOS DECLARADOS: %d\n", argc);
        return 1;
    }

    // EXCEÇÃO DOS ARQUIVOS--------
    pInputFile = fopen(inputFileName, "rt"); // ABRE ARQUIVO DE LEITURA.

    if (pInputFile == NULL)

    {
        printf("PROBLEMAS NA ABERTURA DO ARQUIVO DE LEITURA\n");
    }
    else
    {
        printf("\nARQUIVO ABERTO PARA LEITURA COM SUCESSO!");
    }

    pOutputFile = fopen(outputFileName, "wt"); // ABRE ARQUIVO DE SAÍDA.

    if (pInputFile == NULL)
    {
        printf("PROBLEMAS NA ABERTURA DO ARQUIVO DE ESCRITA\n");
    }
    else
    {
        printf("\nARQUIVO ABERTO PARA ESCRITA COM SUCESSO!\n");
    }

    // EXCEÇÃO 2: CARACTERES DIFERENTES DE INTEIRO--------
    while (!feof(pInputFile))
    {
        result = fgets(Line, 100, pInputFile);
        if (result)
        {
            for (int i = 0; i <= strlen(result) - 1; i++)
            {
                if (((Line[i] < 48) || (Line[i] > 57)) && (Line[i] != 10)) // SE FOR ALGUM CHAR DIFERENTE DE INTEIRO
                {
                    // DEBUG PRINT: Avisa que deu a exceção e demonstra a onde foi.
                    printf("EXCEPTION NON-INTEGER: Linha [%d], Caracter: %d\n", i, Line[i]);
                    fprintf(pOutputFile, "ARQUIVO INVALIDO!\n"); // PRINTA NO ARQUIVO DE SAÍDA A MENSAGEM.
                    fclose(pInputFile);                          // FECHA ARQUIVO DE LEITURA.
                    fclose(pOutputFile);                         // FECHA ARQUIVO DE SAÍDA.
                    return 1;                                    // RETORNA 1. EXCEÇÃO.
                }
            }
        }
        // EXCEÇÃO 3: ARQUIVO VAZIO--------
        else if (result == NULL)
        {
            // DEBUG PRINT: Avisa a exceção.
            printf("EXCEPTION: ARQUIVO VAZIO!\n");
            fprintf(pOutputFile, "ARQUIVO INVALIDO!\n"); // PRINTA NO ARQUIVO DE SAÍDA A MENSAGEM.
            fclose(pInputFile);                          // FECHA ARQUIVO DE LEITURA.
            fclose(pOutputFile);                         // FECHA ARQUIVO DE SAÍDA.
            return 1;                                    // RETORNA 1. EXCEÇÃO.
        }
        else
        // SEM EXCEÇÃO--------
        {
            fclose(pInputFile);  // FECHA ARQUIVO DE LEITURA.
            fclose(pOutputFile); // FECHA ARQUIVO DE SAÍDA.
            return 0;            // RETORNO 0, SEM EXCEÇÃO. PROGRAMA RODA.
        }
    }
}

// Função principal. //
int main(int argc, char *argv[])
{
    // DECLARAÇÕES--------
    int exceptionCaught = 0; // VARIÁVEL DE CONTROLE DE EXCEÇÃO.

    // DEBUGS PRINTS--------
    printf("ARG[0] = %s\n", argv[0]); // PRINTA O NOME DO PROGRAMA.
    printf("ARG[1] = %s\n", argv[1]); // PRINTA O NOME DO ARQUIVO DE LEITURA.
    printf("ARG[2] = %s\n", argv[2]); // PRINTA O NOME DO ARQUIVO DE SAÍDA.

    // TESTES--------
    exceptionCaught = CoreException(argv[1], argv[2], argc); // CHAMA A FUNÇÃO DE EXCEÇÃO.

    // EXECUÇÃO--------
    if (exceptionCaught != 1) // SE NÃO VOLTAR EXCEÇÃO, O PROGRAMA EXECUTA.
    {
        StaticStack Stack1;                      // DECLARAÇÃO DA PILHA 1.
        initializeStack(&Stack1);                // INICIALIZAÇÃO DA PILHA 1.
        CoreFunction(argv[1], argv[2], &Stack1); // CHAMA A FUNÇÃO DE FUNCIONAMENTO.
    }
}
// :::::::::::: BY: FELIPPE NEGRÃO E PEDRO ROMAN ANDREIS :::::::::::: //