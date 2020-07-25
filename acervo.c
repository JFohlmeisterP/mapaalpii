#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define MAX 100
#define ARQUIVO "cadastros_obras.txt"

typedef struct cadastro
{
	char titulo[80];
	char autor[40];
	char editora[30];
	int edicao;
	char isbn[30];
	int ano;
	int quantidadeExemplares;
	int categoria;
	int caixa;
} Obra;

void identificacao();
void cadastrarObra(Obra obras[MAX]);
void listarObras(Obra obras[MAX], int categoria);
void listarObrasCaixa(Obra obras[MAX], int caixa);
int contarRegistro(Obra obras[MAX]);

int main()
{
	Obra obras[MAX];
	setlocale(LC_ALL, "Portuguese");

	int op, caixa;
	do{
		identificacao();
		printf("\n1 - Cadastrar obras");
		printf("\n2 - Listar todos os livros");
		printf("\n3 - Listar todas as revistas");
		printf("\n4 - Listar obras por caixa");
		printf("\n0 - Sair");
		printf("\nDigite a opção:\n");
		scanf("%d", &op);

		switch(op){
			case 1:
				cadastrarObra(obras);
				break;
			case 2:
				listarObras(obras, 1);
				printf("\n");
				system("pause");
				break;
			case 3:
				listarObras(obras, 2);
				printf("\n");
				system("pause");
				break;
			case 4:
				printf("\n Selecione a caixa: \n [1] [2] [3] \n");
				fflush(stdin);
				scanf("%d", &caixa);
				listarObrasCaixa(obras, caixa);
				printf("\n");
				system("pause");
				break;
			case 0:
				printf("\nSistema encerrado.");
				break;
			default:
				printf("Valor indefinido");
				system("pause");
				break;
		}
	}while(op!=0);
	return 0;
}

void identificacao(){
	system("clear");
	int t;
	for(t=0; t<80; t++) printf("-");
	printf("\n JULIANA FOHLMEISTER PASOLD");
	printf("\n RA: 20016676-5");
	printf("\n Engenharia de Software\n");
	for(t=0; t<80; t++) printf("-");
}
void cadastrarObra(Obra obras[MAX])
{
	identificacao();
	int i;
	FILE * arq;

	arq = fopen(ARQUIVO, "a+");

	if(arq != NULL)
	{
		for(i = 0; i < 1; i++){
			printf("\nInforme os dados da obra: ");
	        printf("\n[1] Livros  [2] Revistas ");
	        fflush(stdin);
	        scanf("%d", &obras[i].categoria);
			printf("\nTítulo:\n ");
			fflush(stdin);
			scanf(" %[^\n]s", obras[i].titulo);
			printf("\nAutor:\n");
			fflush(stdin);
			scanf(" %[^\n]s", obras[i].autor);
			printf("\nEditora:\n");
			fflush(stdin);
			scanf(" %[^\n]s", obras[i].editora);
			printf("\nEdição:\n");
			fflush(stdin);
			scanf("%d", &obras[i].edicao);
			printf("\nISBN:\n");
			fflush(stdin);
			scanf(" %[^\n]s", obras[i].isbn);
			printf("\nAno:\n");
			fflush(stdin);
			scanf("%d", &obras[i].ano);
			printf("\nQuantidade de exemplares:\n");
			fflush(stdin);
			scanf("%d", &obras[i].quantidadeExemplares);
			printf("\nSelecione a caixa: \n [1]  [2]  [3] ");
			scanf("%d", &obras[i].caixa);
			fwrite(&obras[i], sizeof(Obra), 1, arq);
		}
		fclose(arq);
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura!\n");
		exit(1);
	}
}

int contarRegistro(Obra obras[MAX])
{
	FILE * arq = fopen(ARQUIVO, "r");
	if(arq != NULL)
	{
		int contador = 0;
		while(1)
		{
			Obra p;

			int registro = fread(&p, sizeof(Obra), 1, arq);

			if(registro < 1)
				break;
			else
				obras[contador] = p;

			contador++;
		}
		fclose(arq);
		return contador;
	}
	else
	{
		printf("\nErro ao abrir o arquivo para leitura.\n");
		exit(1);
	}
}

void listarObras(Obra obras[MAX], int categoria){
	identificacao();

	int quantidadeRegistro = contarRegistro(obras);
	int i;
	int cont = 0;

	if (categoria == 1)
		printf("\nLista de Livros:\n");
	else
		printf("\nLista de Revistas:\n");

	for(i = 0; i < quantidadeRegistro; i++)
	{
		if (categoria == obras[i].categoria)
		{
			cont++;
			printf("\n Item: %d\n Título: %s\n Autor: %s\n Editora: %s\n Edição: %d\n ISBN: %s\n Ano: %d\n Exemplares: %d\n Caixa: %d\n",
                i+1, obras[i].titulo, obras[i].autor, obras[i].editora, obras[i].edicao, obras[i].isbn, obras[i].ano, obras[i].quantidadeExemplares, obras[i].caixa);
		}
	}

	if (categoria == 1)
		printf("\nForam impressos %d livros.\n", cont);
	else
		printf("\nForam impressas %d revistas.\n", cont);
}

void listarObrasCaixa(Obra obras[MAX], int caixa){
	identificacao();

	int quantidadeRegistro = contarRegistro(obras);
	int i;

	printf("\n Lista de obras por caixa: \n");
	printf(" Caixa pesquisada: %d \n", caixa);

	for(i = 0; i < quantidadeRegistro; i++)
	{
		if(obras[i].caixa == caixa){
			printf("\n Item: %d\n Título: %s\n Autor: %s\n Editora: %s\n Edição: %d\n ISBN: %s\n Ano: %d\n Exemplares: %d\n Caixa: %d\n",
                i+1, obras[i].titulo, obras[i].autor, obras[i].editora, obras[i].edicao, obras[i].isbn, obras[i].ano, obras[i].quantidadeExemplares, obras[i].caixa);
		}
	}
}
