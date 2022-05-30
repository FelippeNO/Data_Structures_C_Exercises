#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct no
{
    int valor;
    char nome[60];
    char sexo;
    int idade;
    float peso;
    float altura;
    char telefone[20];
    struct no *proximo;
    struct no *anterior;
} No;

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

// FUNÇÃO QUE FAZ A INSERÇÃO DOS ELEMENTOS NA FILA------------------------------------------------------------
void addNewPerson(No **lista, int num, char *nome, char sexo, int idade, float peso, float altura, char *telefone)
{

    No *aux, *novo = malloc(sizeof(No));

    if (novo)
    {
        novo->valor = num;
        strcpy(novo->nome, nome);
        novo->sexo = sexo;
        novo->idade = idade;
        novo->peso = peso;
        novo->altura = altura;
        strcpy(novo->telefone, telefone);
        if (*lista == NULL)
        {
            novo->proximo = NULL;
            novo->anterior = NULL;
            *lista = novo;
        }
        else if (novo->valor < (*lista)->valor)
        {
            novo->proximo = *lista;
            (*lista)->anterior = novo;
            *lista = novo;
        }
        else
        {
            aux = *lista;
            while (aux->proximo && novo->valor > aux->proximo->valor)
                aux = aux->proximo;
            novo->proximo = aux->proximo;
            if (aux->proximo)
                aux->proximo->anterior = novo;
            novo->anterior = aux;
            aux->proximo = novo;
        }
    }
    else
        printf("Erro ao alocar memoria!\n");
}

// FUNÇÃO QUE VERIFICA SE ELEMENTO ESPECÍFICO ESTÁ NA FILA (BUSCA PELO COD)--------------------------------------------
No *getById(No **lista, int num)
{
    No *aux, *no = NULL;

    aux = *lista;
    while (aux && aux->valor != num)
        aux = aux->proximo;
    if (aux)
        no = aux;
    return no;
}

// FUNÇÃO QUE PRINTA OS ELEMENTOS NO ARQUIVO DE SAÍDA---------------------------------------------------------
void printDataOutputFile(No *no, FILE *outputFileName)
{
    fprintf(outputFileName, "{");
    fprintf(outputFileName, "%d,", (no)->valor);
    fprintf(outputFileName, "%s,", (no)->nome);
    fprintf(outputFileName, "%c,", (no)->sexo);
    fprintf(outputFileName, "%d,", (no)->idade);
    fprintf(outputFileName, "%.2f,", (no)->peso);
    fprintf(outputFileName, "%.2f,", (no)->altura);
    fprintf(outputFileName, "%s", (no)->telefone);
    fprintf(outputFileName, "}\n");
}

// FUNÇÃO QUE CHAMA O PRINT CRESCENTE DE ELEMENTOS NO ARQUIVO DE SAÍDA-------------------------------------------------
void crescentPrint(No *no, FILE *outputFileName)
{

    while (no)
    {
        if (no->valor > 0)
        {
            printDataOutputFile(no, outputFileName);
        }
        no = no->proximo;
    }
    printf("\n");
}

// FUNÇÃO QUE RETORNA O PONTEIRO PARA O ÚLTIMO NÓ DA LISTA--------------------------------------------------
No *last(No **lista)
{
    No *aux = *lista;
    while (aux->proximo)
        aux = aux->proximo;
    return aux;
}

// FUNÇÃO QUE CHAMA O PRINT DECRESCENTE DE ELEMENTOS NO ARQUIVO DE SAÍDA----------------------------------------------
void decrescentPrint(No *no, FILE *outputFileName)
{
    while (no)
    {
        if (no->valor < 0)
        {
            return;
        }
        printDataOutputFile(no, outputFileName);
        no = no->anterior;
    }
}

// FUNÇÃO USADA PARA ZERAR O VETOR DE STRING ATRIBUIDOS AOS DADOS DE CADA CLIENTE------------------------------
void zeroString(char string[], int n)
{
    for (int i = 0; i != n; i++)
    {
        string[i] = 0;
    }
}

// FUNÇÃO USADA PARA FAZER A CONVERSÇÃO ENTRE TIPOS LIDOS NO ARQUIVO------------------------------------------
char *getDataFromString(char string[], char Line[], int n, int *z)
{
    zeroString(string, n);
    for (int i = 0; (Line[*z] != 44); i++)
    {
        string[i] = Line[*z];
        (*z)++;
    }
    return string;
}

// FUNÇÃO QUE FAZ A LEITURA DO ARQUIVO DE ENTRADA E CHAMA AS DEMAIS FUNÇÕES----------------------------
void coreFunction(No **lista, char *inputFileName, FILE *pOutputFile)
{
    FILE *pInputFile;
    char Line[50];
    char *result;

    pInputFile = fopen(inputFileName, "rt");

    if (pInputFile == NULL)
    {
        printf("PROBLEMAS NA ABERTURA DO ARQUIVO DE LEITURA\n");
        return;
    }
    else
    {
        printf("\nARQUIVO ABERTO PARA LEITURA COM SUCESSO!\n");
    }

    bool first = true;

    while (!feof(pInputFile))
    {
        result = fgets(Line, 50, pInputFile);
        if (result[0] != 123 && first == true)
        {
            fprintf(pOutputFile, "ARQUIVO INVALIDO");
            return;
        }
        first = false;

        if (result[0] == 123)
        {
            int z = 1; // Variável usada para guardar a posição na String.
            int *pont_z = &z;
            printf("\n%s\n", Line);
            ///////////////////////////
            char cod[8];                             // String criada que guardar o código do cliente.
            printf("COD POSIT.: %d\n", z);           // Debug print.
            getDataFromString(cod, Line, 8, pont_z); // Função que transforma a Line na String cod.
            int intCodigo = atoi(cod);               // Função que transforma a string em int
            z++;                                     // Incrementa a posição da String
            printf("COD. DATA: %d\n", intCodigo);    // Debug print.
            if (intCodigo == 0)                      // Se o código for 0, o programa para e printa arquivo inválido.
            {
                fprintf(pOutputFile, "ARQUIVO INVALIDO");
                return;
            } // Se tiver vazio se torna uma exceção.
            ///////////////////////////
            char nome[60];
            printf("NOME POSIT.: %d\n", z);
            getDataFromString(nome, Line, 60, pont_z);
            printf("NOME DATA: %s\n", nome);
            z++;
            if (nome[0] == 0)
            {
                fprintf(pOutputFile, "ARQUIVO INVALIDO");
                return;
            }
            ///////////////////////////
            printf("SEXO POSIT.: %d\n", z);
            char sexo = 0;
            sexo = Line[z];
            printf("SEXO DATA: %c\n", sexo);
            if (sexo != 102 && sexo != 109)
            {
                fprintf(pOutputFile, "ARQUIVO INVALIDO");
                return;
            }
            ///////////////////////////
            z++;
            z++;
            char idade[10];
            printf("IDADE POSIT.: %d\n", z);
            getDataFromString(idade, Line, 10, pont_z);
            int idadeInt = atoi(idade);
            printf("IDADE DATA: %d\n", idadeInt);
            if (idadeInt == 0)
            {
                fprintf(pOutputFile, "ARQUIVO INVALIDO");
                return;
            }
            ///////////////////////////
            char peso[10];
            printf("PESO POSIT.: %d\n", z);
            z++;
            getDataFromString(peso, Line, 10, pont_z);
            float pesoFloat = atof(peso);
            printf("PESO DATA: %.2f\n", pesoFloat);
            if (pesoFloat == 0)
            {
                fprintf(pOutputFile, "ARQUIVO INVALIDO");
                return;
            }
            ///////////////////////////
            z++;
            char altura[10];
            printf("ALTURA POSIT.: %d\n", z);
            getDataFromString(altura, Line, 10, pont_z);
            float alturaFloat = atof(altura);
            printf("ALTURA DATA: %.2f\n", alturaFloat);
            if (alturaFloat == 0)
            {
                fprintf(pOutputFile, "ARQUIVO INVALIDO");
                return;
            }
            ///////////////////////////
            char telefone[20];
            zeroString(telefone, 20);
            z++;
            printf("TELEFONE POSIT.: %d\n", z);
            for (int i = 0; (Line[z] != 125); i++)
            {
                telefone[i] = Line[z];
                z++;
            }
            printf("TELEFONE DATA: %s\n", telefone);
            if (telefone[0] == 0)
            {
                fprintf(pOutputFile, "ARQUIVO INVALIDO");
                return;
            }
            printf("--------------------------\n");
            /////////////////////////
            addNewPerson(lista, intCodigo, nome, sexo, idadeInt, pesoFloat, alturaFloat, telefone); // Insere elementos
        }
        else if (result[0] != 123)
        {
            if (result[0] == 50)
            {
                decrescentPrint(last(lista), pOutputFile);
            }
            else if (result[0] == 49)
            {
                crescentPrint(*lista, pOutputFile);
            }
            else if (result[0] == 51)
            {
                result = fgets(Line, 8, pInputFile);
                int codParsed = atoi(result);

                if (codParsed <= 0)
                {
                    fprintf(pOutputFile, "ELEMENTO NAO ENCONTRADO\n");
                }
                else
                {
                    No *achado = getById(lista, codParsed);
                    if (achado == 0)
                    {
                        fprintf(pOutputFile, "ELEMENTO NAO ENCONTRADO\n");
                    }
                    else
                    {
                        printDataOutputFile(achado, pOutputFile);
                    }
                }
            }
            else
            {
                fprintf(pOutputFile, "ARQUIVO INVALIDO");
                return;
            }
        }
    }
    fclose(pOutputFile);
}

// FUNÇÃO QUE TRATA AS EXCEÇÕES REFERENTES AOS ARGS-------------------------------------------
int ArgumentsException(char *inputFileName, char *outputFileName, int argc)
{
    // DECLARAÇÕES--------
    FILE *pInputFile;  // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE LEITURA.
    FILE *pOutputFile; // ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE SAÍDA.
    char *result;      // VARIÁVEL DO RESULTADO DA LINHA.

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
    else
    {
        return 0;
    }
}

// FUNÇÃO MAIN-------------------------------------------
int main(int argc, char *argv[])

{
    int exceptionCaught = 0;
    FILE *pOutputFile = OpenOutputFile(argv[2]);
    exceptionCaught = ArgumentsException(argv[1], argv[2], argc);

    // DEBUGS PRINTS--------
    printf("ARG[0] = %s\n", argv[0]); // PRINTA O NOME DO PROGRAMA.
    printf("ARG[1] = %s\n", argv[1]); // PRINTA O NOME DO ARQUIVO DE LEITURA.
    printf("ARG[2] = %s\n", argv[2]); // PRINTA O NOME DO ARQUIVO DE SAÍDA.

    No *lista = NULL;
    addNewPerson(&lista, -1, "ELEMENTO SENTINELA", ' ', 0, 0, 0, ""); // Insere elemento sentinela.

    if (exceptionCaught == 0)
        coreFunction(&lista, argv[1], pOutputFile);
}
// :::::::::::: BY: FELIPPE NEGRÃO E PEDRO ROMAN ANDREIS :::::::::::: //