
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

/* ------------------------------------------------------- */
/* ------------------------------------------------------- */

int COMPARATION = 0;
clock_t start, end, diff;

typedef void (*func)(void);

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(int arr[], int n, int i)
{

    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
    {
        COMPARATION++;
        largest = left;
    }

    if (right < n && arr[right] > arr[largest])
    {
        COMPARATION++;
        largest = right;
    }

    if (largest != i)
    {
        COMPARATION++;
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int zero, int n, int end)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

/* ------------------------------------------------------- */
/* ------------------------------------------------------- */

void printArray(int *v, int tam)
{
    printf("Array = [");
    for (int i = 0; i < tam; i++)
    {
        printf("%d ", v[i]);
    }
    printf("]\n");
}

/* ------------------------------------------------------- */
/* ------------------------------------------------------- */

void bubbleSort(int *v, int op, int n, int end)
{

    if (op != 0 && op != 2)
    {
        printf("Warning: not valid option. Please, choose 1 (ascending) or 2 (descending).\n");
        return;
    }
    bool changed = true;
    while (changed)
    {

        changed = false;
        for (int i = 0; i < n - 1; i++)
        {
            COMPARATION++;
            if (op == 0)
            {
                if (v[i] > v[i + 1])
                {
                    swap(&v[i], &v[i + 1]);
                    changed = true;
                }
            }
            else
            {
                if (v[i] < v[i + 1])
                {
                    swap(&v[i], &v[i + 1]);
                    changed = true;
                }
            }
        }
    }
}

/* ------------------------------------------------------- */
/* ------------------------------------------------------- */

void selectionSort(int *v, int zero, int n, int end)
{
    int i, j, min, aux;
    for (i = 0; i < n - 1; i++)
    {
        COMPARATION++;
        min = i;
        for (j = i + 1; j < n; j++)
        {
            if (v[j] < v[min])
            {
                min = j;
            }
        }
        if (i != min)
        {
            aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
}

/* ------------------------------------------------------- */
/* ------------------------------------------------------- */

void insertionSort(int *v, int zero, int n, int end)
{

    int i, j, chosen;
    for (i = 1; i < n; i++)
    {
        COMPARATION++;
        chosen = v[i];
        j = i - 1;
        while (j >= 0 && chosen < v[j])
        {
            v[j + 1] = v[j];
            j = j - 1;
        }
        v[j + 1] = chosen;
    }
}

/* ------------------------------------------------------- */
/* ------------------------------------------------------- */

void merge(int *v, int start, int middle, int end)
{
    int *temp;
    int i, j, k;
    int p1, p2;
    int vecSize;

    bool finished1 = false;
    bool finished2 = false;

    vecSize = (end - start) + 1;

    p1 = start;
    p2 = middle + 1;

    temp = (int *)malloc(vecSize * sizeof(int));

    if (temp != NULL)
    {
        for (i = 0; i < vecSize; i++)
        {
            if (!finished1 && !finished2)
            {
                COMPARATION++;
                if (v[p1] < v[p2])
                {
                    temp[i] = v[p1++];
                }
                else
                {
                    temp[i] = v[p2++];
                }

                if (p1 > middle)
                {
                    finished1 = true;
                }
                if (p2 > end)
                {
                    finished2 = true;
                }
            }
            else
            {
                COMPARATION++;
                if (!finished1)
                {
                    temp[i] = v[p1++];
                }
                else
                {
                    temp[i] = v[p2++];
                }
            }
        }
        for (j = 0, k = start; j < vecSize; j++, k++)
        {
            COMPARATION++;
            v[k] = temp[j];
        }
    }
    free(temp);
}

/* ------------------------------------------------------- */
/* ------------------------------------------------------- */

void mergeSort(int *v, int start, int size, int end)
{
    int middle;

    if (start < end)
    {
        middle = (int)floor((start + end) / 2);
        mergeSort(v, start, size, middle);
        mergeSort(v, (middle + 1), size, end);
        merge(v, start, middle, end);
    }
}

/* ------------------------------------------------------- */
/* ------------------------------------------------------- */

int particiona(int vet[], int inicio, int fim)
{
    int pivo, pivo_indice, i;

    pivo = vet[fim];
    pivo_indice = inicio;

    for (i = inicio; i < fim; i++)
    {
        if (vet[i] <= pivo)
        {
            COMPARATION++;
            swap(&vet[i], &vet[pivo_indice]);
            pivo_indice++;
        }
    }

    swap(&vet[pivo_indice], &vet[fim]);

    return pivo_indice;
}

void quickSort(int *v, int start, int size, int end)
{
    int pivot;
    if (end > start)
    {
        pivot = particiona(v, start, end);
        quickSort(v, start, size, pivot - 1);
        quickSort(v, pivot + 1, size, end);
    }
}

/* ------------------------------------------------------- */
/* ------------------------------------------------------- */

void copyIntArray(int *destination, int *source, int size)
{
    for (int i = 0; i < size; i++)
        destination[i] = source[i];
}

void runSort(void (*func)(), int *vetorMatriz, int n, char *name, FILE *pOutputFile)
{
    int vetorNovo[n];
    copyIntArray(vetorNovo, vetorMatriz, n);
    start = clock();
    (*func)(vetorNovo, 0, n, n - 1);
    end = clock();
    diff = (end - start) / (CLOCKS_PER_SEC / 1000);

    fprintf(pOutputFile, "%s:", name);
    for (int i = 0; i < n; i++)
        fprintf(pOutputFile, " %d", vetorNovo[i]);

    fprintf(pOutputFile, ", %d comp, ", COMPARATION);
    fprintf(pOutputFile, "%ld ms\n", diff);
    COMPARATION = 0;
}

void runSorts(int *vetorMatriz, int n, char *outputFileName)
{

    FILE *pOutputFile;
    pOutputFile = fopen(outputFileName, "wt");

    void (*func1)() = &insertionSort;
    void (*func2)() = &selectionSort;
    void (*func3)() = &bubbleSort;
    void (*func4)() = &mergeSort;
    void (*func5)() = &quickSort;
    void (*func6)() = &heapSort;

    runSort(*func1, vetorMatriz, n, "Insertion Sort", pOutputFile);
    runSort(*func2, vetorMatriz, n, "Selection Sort", pOutputFile);
    runSort(*func3, vetorMatriz, n, "Bubble Sort", pOutputFile);
    runSort(*func4, vetorMatriz, n, "Merge Sort", pOutputFile);
    runSort(*func5, vetorMatriz, n, "Quick Sort", pOutputFile);
    runSort(*func6, vetorMatriz, n, "Heap Sort", pOutputFile);
    fclose(pOutputFile);
}

void runRandomic(int n, char *outputFileName)
{
    printf("\nRANDOMIC\n");
    int vetorMatriz[n];
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        vetorMatriz[i] = rand() % 32000;
    runSorts(vetorMatriz, n, outputFileName);
}

void runIncremented(int n, char *outputFileName)
{
    printf("\nINCREMENTED\n");
    int vetorMatriz[n];
    for (int i = 0; i < n; i++)
        vetorMatriz[i] = i + 1;

    runSorts(vetorMatriz, n, outputFileName);
}

void runDecremented(int n, char *outputFileName)
{
    printf("\nDECREMENTED\n");
    int vetorMatriz[n];
    for (int i = 0; i < n; i++)
        vetorMatriz[i] = n - i;

    runSorts(vetorMatriz, n, outputFileName);
}

// FUNÇÃO QUE TRATA AS EXCEÇÕES REFERENTES AOS ARGS-------------------------------------------------------------------------------//
int ArgumentsException(int argc)
{
    // EXCEÇÃO 1: ARGUMENTOS INVÁLIDOS-------------------------------//
    if (argc < 3) // SE TIVER MENOS DE 3 ARGUMENTOS, O PROGRAMA RETORNA 1----//
    {
        printf("EXCEPTION: FALTA DE ARGUMENTOS!\n");
        printf("NUMERO DE ARGUMENTOS ESPERADOS: 3\n");
        printf("NUMERO DE ARGUMENTOS DECLARADOS: %d\n", argc);
        return 1;
    }
    else if (argc > 3) // SE TIVER MAIS DE 3 ARGUMENTOS, O PROGRAMA RETORNA 1//
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

int main(int argc, char *argv[])
{
    FILE *pInputFile;
    char *result;
    char Line[30];
    int exceptionCaught = 0;
    FILE *exceptionOutput;

    exceptionCaught = ArgumentsException(argc);

    if (exceptionCaught == 1)
    {
        return 999;
    }

    pInputFile = fopen(argv[1], "rt");

    if (pInputFile == NULL)
        printf("PROBLEMAS NA ABERTURA DO ARQUIVO DE LEITURA\n");
    else
        printf("\nARQUIVO ABERTO PARA LEITURA COM SUCESSO!");

    result = fgets(Line, 100, pInputFile);

    if (result == NULL)
    {
        exceptionOutput = fopen(argv[2], "wt");
        fprintf(exceptionOutput, "Arquivo vazio!");
        return 999;
    }

    int n = atoi(result);
    printf("\n%d", n);

    if (n <= 1)
    {
        exceptionOutput = fopen(argv[2], "wt");
        fprintf(exceptionOutput, "Arquivo invalido!");
        return 999;
    }

    result = fgets(Line, 100, pInputFile);
    char mode = result[0];
    printf("\n%c", mode);

    if (mode == 'c')
        runIncremented(n, argv[2]);

    else if (mode == 'd')
        runDecremented(n, argv[2]);

    else if (mode == 'r')
        runRandomic(n, argv[2]);

    else
    {
        exceptionOutput = fopen(argv[2], "wt");
        fprintf(exceptionOutput, "Arquivo invalido!");
        return 999;
    }

    fclose(pInputFile);
}