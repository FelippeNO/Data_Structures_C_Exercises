#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//CRIAÇÃO DO TIPO NÓ DE ARVORE----------------------------------------------------------------------------------------------------//
typedef struct NoArvore *PtrNoArvore;
typedef struct NoArvore
{
	char termo[32];
	int paginas[20];
	//NÓ DIREITS E ESQUERDA-----------------------------------------------//
	PtrNoArvore direita;
	PtrNoArvore esquerda;
} NoArvore;

//INICIA A ÁRVORE BINÁRIA---------------------------------------------------------------------------------------------------------//
void iniciaArvoreBinaria(PtrNoArvore *r)
{
	(*r) = NULL;
}

//VERIFICA SE A ÁRVORE ESTÁ VAZIA-------------------------------------------------------------------------------------------------//
bool estaVaziaArvoreBinaria(PtrNoArvore *r)
{
	return ((*r) == NULL);
}

//INSERE OS ELEMENTOS DENTRO DA ÁRVORE E VERIFICA SE É MAIOR OU MENOR QUE O PAI---------------------------------------------------//
bool inserirArvoreBinaria(PtrNoArvore *no, char *valor)
{
	if ((*no) == NULL)
	{
		//ALOCAÇÃO DINAMICA DE MEMÓRIA----------------------------------------//
		(*no) = malloc(sizeof(NoArvore));
		strcpy((*no)->termo, valor);

		//VERIFICAÇÃO DO NÚMERO DA PÁGINA-------------------------------------//
		for (int i = 0; i < 20; i++)
		{
			(*no)->paginas[i] = -1;
		}

		(*no)->direita = NULL;
		(*no)->esquerda = NULL;
		return (true);
	}

	//DIREITA || ESQUERDA-------------------------------------------------//
	if (strcmp((*no)->termo, valor) == 0)
		return (false); // warning

	if (strcmp(valor, (*no)->termo) > 0)
	{
		return (inserirArvoreBinaria(&(*no)->direita, valor));
	}
	else
	{
		return (inserirArvoreBinaria(&(*no)->esquerda, valor));
	}
}

//FUNÇÃO PARA IMPRIMIR EM ORDEM NO ARQUIVO----------------------------------------------------------------------------------------// 
void EmOrdemArvoreBinaria(PtrNoArvore *no, FILE *outputFileName)
{
	if ((*no) == NULL)
		return;

	EmOrdemArvoreBinaria(&(*no)->esquerda, outputFileName);

	fprintf(outputFileName, "%s", (*no)->termo);

	for (int i = 0; i < 20; i++)
	{
		if ((*no)->paginas[i] > 0)
		{
			fprintf(outputFileName, ",%d", (*no)->paginas[i]);
		}
	}
	fprintf(outputFileName, "\n");
	EmOrdemArvoreBinaria(&(*no)->direita, outputFileName);
}

//FUNÇÃO USADA PARA ZERAR O VETOR DE STRING USADA PARA AS COMPARAÇÕES------------------------------------------------------------//
void zeraString(char string[], int n)
{
	for (int i = 0; i != n; i++)
	{
		string[i] = 0;
	}
}

//FUNÇÃO USADA PARA ATRIBUIR O VALOR DOS CHARS AOS VALORES DOS VETORES-----------------------------------------------------------//
char *getDataFromString(char string[], char Line[], int n, int *z, int stop)
{
	zeraString(string, n);
	for (int i = 0; (Line[*z] != stop); i++)
	{
		string[i] = Line[*z];
		(*z)++;
	}
	return string;
}

//FUNÇÃO QUE INCREMENTA AS PÁGINAS-----------------------------------------------------------------------------------------------//
int getQuantidadeDeTermos(char Line[])
{
	int qntidadeDePalavras = 0;
	for (int i = 0; i < strlen(Line); i++)
	{
		if (Line[i] == 44)
		{
			qntidadeDePalavras++;
		}
	}
	return qntidadeDePalavras + 1;
}

//FUNÇÃO PARA QUE COMPARA SE UM TERMO EXISTE NA ÁRVORE E RETORNA UM BOOL TRUE OR FALSE-------------------------------------------//
bool procuraArvore(PtrNoArvore *arvore, char *valor, int paginas)
{

	if (*arvore == NULL)
		return (false);

	if (strcmp((*arvore)->termo, valor) == 0)
	{
		if ((*arvore)->paginas[0] == -1)
		{
			(*arvore)->paginas[0] = paginas;
			return (true);
		}
		else if ((*arvore)->paginas[0] != -1)
		{
			for (int i = 1; i < 20; i++)
			{
				if ((*arvore)->paginas[i] == -1)
				{
					if ((*arvore)->paginas[i - 1] != paginas)
					{
						(*arvore)->paginas[i] = paginas;
						return true;
					}
					return (true);
				}
			}
			return (true);
		}
	}

	if (strcmp(valor, (*arvore)->termo) == 1)
	{
		return (procuraArvore(&(*arvore)->direita, valor, paginas));
	}
	else
	{
		return (procuraArvore(&(*arvore)->esquerda, valor, paginas));
	}
}

//FUNÇÃO QUE TRATA AS EXCEÇÕES REFERENTES AOS ARGS-------------------------------------------------------------------------------//
int ArgumentsException(char *inputFileName, char *outputFileName, int argc)
{
	//DECLARAÇÕES---------------------------------------------------//
	FILE *pInputFile;  //ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE LEITURA//
	FILE *pOutputFile; //ATRIBUI A VARIÁVEL A ABERTURA DO ARQUIVO DE SAÍDA--//
	char *result;      //VARIÁVEL DO RESULTADO DA LINHA---------------------//
	
	//EXCEÇÃO 1: ARGUMENTOS INVÁLIDOS-------------------------------//
	if (argc < 3) //SE TIVER MENOS DE 3 ARGUMENTOS, O PROGRAMA RETORNA 1----//
	{
		printf("EXCEPTION: FALTA DE ARGUMENTOS!\n");
		printf("NUMERO DE ARGUMENTOS ESPERADOS: 3\n");
		printf("NUMERO DE ARGUMENTOS DECLARADOS: %d\n", argc);
		return 1;
	}
	else if (argc > 3) //SE TIVER MAIS DE 3 ARGUMENTOS, O PROGRAMA RETORNA 1//
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

void destroiArvore(PtrNoArvore *node) {
	if((*node) != NULL) {
		destroiArvore(&(*node)->esquerda);
		destroiArvore(&(*node)->direita);
		free(*node);
		*node = NULL;
	}
}

//FUNÇÃO PRINCIPAL DO PROGRAMA---------------------------------------------------------------------------------------------------//
int main(int argc, char *argv[])
{
	
	int exceptionCaught = 0;
	
	//DEBUGS PRINTS--------------------------------------------------//
	printf("ARG[0] = %s\n", argv[0]); //PRINTA O NOME DO PROGRAMA----------------//
	printf("ARG[1] = %s\n", argv[1]); //PRINTA O NOME DO ARQUIVO DE LEITURA------//
	printf("ARG[2] = %s\n", argv[2]); //PRINTA O NOME DO ARQUIVO DE SAÍDA.-------//
	
	exceptionCaught = ArgumentsException(argv[1], argv[2], argc);
	
	if(exceptionCaught == 0){
		
		
		PtrNoArvore raiz;
		iniciaArvoreBinaria(&raiz);
	
	
		if (estaVaziaArvoreBinaria(&raiz))
			{
				printf("Arvore vazia!\n");
			}
		
		FILE *pInputFile;
		FILE *pOutputFile;
		
		pOutputFile = fopen(argv[2], "wt");
		pInputFile = fopen(argv[1], "rt");
		
		char *result;	//VARIÁVEL DO RESULTADO DA LINHA--------------------------//
		char Line[200]; //VARIÁVEL DA LINHA---------------------------------------//
		char *result2;
		int page = 0;
		
		int z = 8;
		int *pont_z = &z;
		char termo[32];
		int qntidadeDePalavras = 0;
		
		char palavraTexto[1000];
		char *pt;
		
		result = fgets(Line, 200, pInputFile);
		qntidadeDePalavras = getQuantidadeDeTermos(Line);
		
		for (int i = 0; i < qntidadeDePalavras; i++)
			{
				
				if (i == qntidadeDePalavras - 1)
					{
						getDataFromString(termo, Line, 32, pont_z, 62);
						inserirArvoreBinaria(&raiz, termo);
					}
				else
					{
						getDataFromString(termo, Line, 32, pont_z, 44);
						inserirArvoreBinaria(&raiz, termo);
						z++;
					}
			}
		
		while (!feof(pInputFile))
			{
				result2 = fgets(Line, 200, pInputFile);
				if (result2)
					{
						if (strstr(result2, "page:"))
							{
								printf("\n------PAGINA %d-----\n", page + 1);
								page++;
							}
						else
							{
								zeraString(palavraTexto, 1000);
								pt = strtok(result2, " ,:;?!().\n");
								while (pt)
									{
										procuraArvore(&raiz, pt, page);
										printf("%s\n", pt);
										pt = strtok(NULL, " ,:;?!().\n");
									}
							}
					}
			}
		//PRINTA, FECHA OS ARQUIVOS E DESTRÓI A ÁRVORE---------------------------------------------------------------------------//
		EmOrdemArvoreBinaria(&raiz, pOutputFile);
		fclose(pInputFile);
		fclose(pOutputFile);
		destroiArvore(&raiz);
	}
}
