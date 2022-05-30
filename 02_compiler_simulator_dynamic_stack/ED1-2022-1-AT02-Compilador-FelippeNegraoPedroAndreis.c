
//---------------------------------------------------------------- LIBRARIES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//---------------------------------------------------------------- GLOBAL

#define LENGTH 50
typedef struct NoPilha *PtrNoPilha;

struct NoPilha
{
    int elemento;
    PtrNoPilha proximo;
} NoPilha;

typedef struct
{
    PtrNoPilha topo;
    int qtde;
} PilhaDinamica;

char OPERANDO1 = ' '; // VARIÁVEL GLOBAL DO OPERANDO1
char OPERANDO2 = ' '; // VARIÁVEL GLOBAL DO OPERANDO2
int COUNT_TEMP = 1;   // VARIÁVEL GLOBAL DOS TEMPS.

//---------------------------------------------------------------- FUNCTIONS
void iniciaPilhaDinamica(PilhaDinamica *p)
{
    p->qtde = 0;
    p->topo = NULL;
}

bool estaVaziaPilhaDinamica(PilhaDinamica *p)
{
    return (p->topo == NULL);
}

int tamanhoPilhaDinamica(PilhaDinamica *p)
{
    return (p->qtde);
}

void pushPilhaDinamica(PilhaDinamica *p, int num)
{
    printf("EMPILHANDO\n");

    PtrNoPilha Aux = malloc(sizeof(NoPilha));

    Aux->elemento = num;

    Aux->proximo = p->topo;

    p->topo = Aux;

    p->qtde++;
    printf("EMPILHOU\n");
}

int popPilhaDinamica(PilhaDinamica *p, FILE *outputFileName)
{
    if (!estaVaziaPilhaDinamica(p))
    {
        printf("DESEMPILHANDO\n");

        PtrNoPilha aux;

        aux = p->topo;

        p->topo = p->topo->proximo;

        printf("ELEMENTO: %c\n", aux->elemento);
        int num = aux->elemento;

        p->qtde--;
        free(aux);
        printf("DESEMPILHOU\n");
        return num;
    }
    else
    {
        printf("Warning: pilha está vazia!\n");
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

// Função que analisa se o caracter é operador e organiza os prints no arquivo de saída. //
void analisaTudo(char *operacao, PilhaDinamica *Stack1, FILE *pOutputFile, char *Line, int i)
{
    // CORPO--------
    OPERANDO2 = popPilhaDinamica(Stack1, pOutputFile);
    if (OPERANDO2 >= 1 && OPERANDO2 <= 9)
    {
        fprintf(pOutputFile, "LDR TEMP%d\n", OPERANDO2);
    }
    else
    {
        fprintf(pOutputFile, "LDR %c\n", OPERANDO2);
    }

    OPERANDO1 = popPilhaDinamica(Stack1, pOutputFile);
    if (OPERANDO1 >= 1 && OPERANDO1 <= 9)
    {
        fprintf(pOutputFile, "LDR TEMP%d\n", OPERANDO1);
    }
    else
    {
        fprintf(pOutputFile, "LDR %c\n", OPERANDO1);
    }

    printf("OPERANDO 1::::: %d\n", OPERANDO1);
    printf("OPERANDO 2::::: %d\n", OPERANDO2);

    // CASO -> OPERANDO 1: LETRA, OPERANDO2: LETRA
    if ((OPERANDO1 >= 65 && OPERANDO1 <= 90) && (OPERANDO2 >= 65 && OPERANDO2 <= 90))
    {
        fprintf(pOutputFile, "%s %c %c\n", operacao, OPERANDO2, OPERANDO1);
    }

    // CASO -> OPERANDO 1: LETRA, OPERANDO2: NUMERO
    else if ((OPERANDO1 >= 65 && OPERANDO1 <= 90) && (OPERANDO2 >= 1 && OPERANDO2 <= 9))
    {
        fprintf(pOutputFile, "%s TEMP%d %c\n", operacao, OPERANDO2, OPERANDO1);
    }

    // CASO -> OPERANDO 1: NUMERO, OPERANDO2: NUMERO
    else if ((OPERANDO1 >= 1 && OPERANDO1 <= 9) && (OPERANDO2 >= 1 && OPERANDO2 <= 9))
    {
        fprintf(pOutputFile, "%s TEMP%d TEMP%d\n", operacao, OPERANDO2, OPERANDO1);
    }

    // CASO -> OPERANDO 1: NUMERO, OPERANDO2: LETRA
    else if (((OPERANDO1 >= 1) && (OPERANDO1 <= 9)) && ((OPERANDO2 >= 65) && (OPERANDO2 <= 90)))
    {
        fprintf(pOutputFile, "%s %c TEMP%d\n", operacao, OPERANDO2, OPERANDO1);
    }

    if (Line[i + 1] != '\0') // SE O ÚLTIMO CARACTER FOR VAZIO
    {
        pushPilhaDinamica(Stack1, COUNT_TEMP);
        fprintf(pOutputFile, "STR TEMP%d\n", COUNT_TEMP);
        COUNT_TEMP++; // INCREMENTA A VARIÁVEL DA TEMP
    }
}

// Função que roda o programa e atribuiu os prints ao arquivo de saída. //
void CoreFunction(char *inputFileName, char *outputFileName, PilhaDinamica *Stack1)
{
    // DECLARAÇÕES--------
    FILE *pOutputFile = OpenOutputFile(outputFileName); // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE SAÍDA.
    FILE *pInputFile;                                   // VARIÁVEL DO ARQUIVO DE ENTRADA.
    char Line[200];                                     // VARIÁVEL DA LINHA.
    char *result;                                       // VARIÁVEL DO RESULTADO DA LINHA.

    // FUNÇÕES INICIALIZADAS--------             // INICIALIZA A PILHA 2.
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
        char caracter = ' ';
        result = fgets(Line, 100, pInputFile);
        for (int i = 0; i != strlen(result); i++)
        {
            caracter = Line[i];
            printf("CARACTER PARA ENTRAR: %c\n", caracter);

            if ((caracter >= 65) && (caracter <= 90)) // ANALISA SE É CARACTER DE A a Z E JOGA PARA PILHA
            {
                pushPilhaDinamica(Stack1, caracter);
            }
            else if (caracter == 42) // ANALISA SE É CARACTER *
            {
                analisaTudo("MUL", Stack1, pOutputFile, Line, i);
            }
            else if (caracter == 43) // ANALISA SE É CARACTER +
            {
                analisaTudo("ADD", Stack1, pOutputFile, Line, i);
            }
            else if (caracter == 45) // ANALISA SE É CARACTER -
            {
                analisaTudo("SUB", Stack1, pOutputFile, Line, i);
            }
            else if (caracter == 47) // ANALISA SE É CARACTER /
            {
                analisaTudo("DIV", Stack1, pOutputFile, Line, i);
            }
        }
        if (estaVaziaPilhaDinamica(Stack1))
        {
            printf("\nVAZIA: TUDO DEU CERTO!\n");
            fclose(pInputFile);  // FECHA O ARQUIVO DE ENTRADA
            fclose(pOutputFile); // FECHA O ARQUIVO DE SAÍDA
        }
        else
        {
            printf("\nPILHA NAO FICOU VAZIA! EXCEPTION CAUGHT\n"); // SE A PILHA NÃO FICOU VAZIA, O ARQUIVO É RESETADO.
            fclose(pInputFile);
            fclose(pOutputFile);

            OpenOutputFile(outputFileName);
            fprintf(pOutputFile, "EXPRESSAO INVALIDA!\n");
            fclose(pOutputFile);
        }
    }
}

// Função que trata as exceções. //
int CoreException(char *inputFileName, char *outputFileName, int argc)
{
    // DECLARAÇÕES--------
    FILE *pInputFile;   // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE LEITURA.
    FILE *pOutputFile;  // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE SAÍDA.
    char *result;       // VARIÁVEL DO RESULTADO DA LINHA.
    char Line[100];     // VARIÁVEL DA LINHA.
    int operandos = 0;  // VARIÁVEL CONTADORA DOS OPERANDOS.
    int operadores = 0; // VARIÁVEL CONTADORA DOS OPERADORES.

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

    // EXCEÇÃO 2: EXCEÇÃO DOS ARQUIVOS--------
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

    if (pOutputFile == NULL)
    {
        printf("PROBLEMAS NA ABERTURA DO ARQUIVO DE ESCRITA\n");
    }
    else
    {
        printf("\nARQUIVO ABERTO PARA ESCRITA COM SUCESSO!\n");
    }

    while (!feof(pInputFile))
    {

        result = fgets(Line, 100, pInputFile);
        if (result)
        {
            for (int i = 0; i != strlen(result); i++)
            {
                // EXCEÇÃO 3: CARACTERES DIFERENTES DO PREVISTO--------
                if (((Line[i] < 65) || (Line[i] > 90)) && (Line[i] != 10) &&
                    (Line[i] != 42) && (Line[i] != 43) && (Line[i] != 45) && (Line[i] != 47))
                {
                    // DEBUG PRINT: Avisa que deu a exceção e demonstra a onde foi.
                    printf("EXCEPTION NON-VALID: Linha [%d], Caracter: %d\n", i, Line[i]);
                    fprintf(pOutputFile, "EXPRESSAO INVALIDA!\n"); // PRINTA NO ARQUIVO DE SAÍDA A MENSAGEM.
                    fclose(pInputFile);                            // FECHA ARQUIVO DE LEITURA.
                    fclose(pOutputFile);                           // FECHA ARQUIVO DE SAÍDA.
                    return 1;                                      // RETORNA 1. EXCEÇÃO.
                }
            }

            // EXCEÇÃO 4: SEGUNDO CARACTER NÃO PODE SER OPERADOR--------
            if (Line[1] >= 42 && Line[1] <= 47) // SEGUNDO CARACTER NÃO PODE SER OPERADOR
            {
                fprintf(pOutputFile, "EXPRESSAO INVALIDA!\n");
                printf("CHEGOU AQUI E DEU ERRADO\n");
                fclose(pInputFile);
                fclose(pOutputFile);
                return 1;
            }

            // EXCEÇÃO 5: QUANTIDADE DE OPERANDOS E OPERADORES--------
            for (int i = 0; i != strlen(result); i++)
            {

                if ((Line[i] == 42) || (Line[i] == 43) || (Line[i] == 45) || (Line[i] == 47))
                {
                    operadores++;
                }
                else if ((Line[i] >= 65) || (Line[i] <= 90))
                {
                    operandos++;
                }
            }
            if (operadores >= operandos)
            {
                fprintf(pOutputFile, "EXPRESSAO INVALIDA!\n");
                printf("EXCEPTION: MAIS OPERADORES QUE OPERANDOS\n");
                printf("OPERADORES: %d\n", operadores);
                printf("OPERANDOS: %d\n", operandos);
                fclose(pInputFile);
                fclose(pOutputFile);
                return 1;
            }
            else if ((operandos - operadores) >= 2)
            {
                fprintf(pOutputFile, "EXPRESSAO INVALIDA!\n");
                printf("EXCEPTION: OPERANDOS EM EXCESSO\n");
                printf("OPERADORES: %d\n", operadores);
                printf("OPERANDOS: %d\n", operandos);
                fclose(pInputFile);
                fclose(pOutputFile);
                return 1;
            }
            else
            {
                printf("ENTRADA VALIDA\n");
                printf("OPERADORES: %d\n", operadores);
                printf("OPERANDOS: %d\n", operandos);
            }
        }

        // EXCEÇÃO 6: ARQUIVO VAZIO--------
        else if (result == NULL)
        {
            // DEBUG PRINT: Avisa a exceção.
            printf("EXCEPTION: ARQUIVO VAZIO!\n");
            fprintf(pOutputFile, "EXPRESSAO INVALIDA\n"); // PRINTA NO ARQUIVO DE SAÍDA A MENSAGEM.
            fclose(pInputFile);                           // FECHA ARQUIVO DE LEITURA.
            fclose(pOutputFile);                          // FECHA ARQUIVO DE SAÍDA.
            return 1;                                     // RETORNA 1. EXCEÇÃO.
        }
    }
}

// Função principal. //
int main(int argc, char *argv[])
{
    // DECLARAÇÕES--------
    int exceptionCaught = 0; // VARIÁVEL DE CONTROLE DE EXCEÇÃO.
    PilhaDinamica pilha;     // DECLARAÇÃO DA PILHA.

    // DEBUGS PRINTS--------
    printf("ARG[0] = %s\n", argv[0]); // PRINTA O NOME DO PROGRAMA.
    printf("ARG[1] = %s\n", argv[1]); // PRINTA O NOME DO ARQUIVO DE LEITURA.
    printf("ARG[2] = %s\n", argv[2]); // PRINTA O NOME DO ARQUIVO DE SAÍDA.

    // TESTES--------
    exceptionCaught = CoreException(argv[1], argv[2], argc); // CHAMA A FUNÇÃO DE EXCEÇÃO.

    iniciaPilhaDinamica(&pilha); // INICIA A PILHA.

    if (estaVaziaPilhaDinamica(&pilha)) // CONFERE SE A PILHA ESTÁ VAZIA.
    {
        printf("Pilha esta vazia!\n");
    }
    else
    {
        printf("Tem algum elemento na pilha!\n");
        exceptionCaught = 1; // SENÃO, DEIXA A VARIÁVEL DE CONTROLE DE EXCEÇÃO COMO 1.
    }

    int tam = tamanhoPilhaDinamica(&pilha);
    printf("Tamanho = %d\n", tam);

    // EXECUÇÃO--------
    if (exceptionCaught != 1) // SE NÃO VOLTAR EXCEÇÃO, O PROGRAMA EXECUTA.
    {
        CoreFunction(argv[1], argv[2], &pilha); // CHAMA A FUNÇÃO DE FUNCIONAMENTO.
    }
    printf("-------------ACABOU--------------");
}
// :::::::::::: BY: FELIPPE NEGRÃO E PEDRO ROMAN ANDREIS :::::::::::: //