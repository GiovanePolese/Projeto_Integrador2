//13 == ASCII code for "ENTER"
//32 == ASCII code for "SPACE"
//8 == ASCII code for "BACKSPACE"

#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

#define TAMANHO_SENHA 9
#define TAMANHO_USUARIO 25
#define TAMANHO_NOME 50
#define TAMANHO_UNIDADE 15

#define MOVE_UP 38
#define MOVE_DOWN 80
#define MOVE_RIGHT 77
#define ESC 27
#define ENTER 13

typedef struct {
	int codigo;
	char nome[TAMANHO_NOME];
	char usuario[TAMANHO_USUARIO];
	char senha[TAMANHO_SENHA];
}FORNECEDOR;

typedef struct {
	int codigo;
	char nome[TAMANHO_NOME];
	char usuario[TAMANHO_USUARIO];
	char senha[TAMANHO_SENHA];
}EMPRESA;

typedef struct {
	int codigo;
	char nomeMaterial[TAMANHO_NOME];
	char unidade[TAMANHO_UNIDADE];
}MATERIAL;

typedef struct{
	int codigo;
	char nomeProduto[TAMANHO_NOME];
	int codigoEmpresa;
}PRODUTO;

typedef struct{
	int codigo;
	char nomeMaterial[TAMANHO_NOME];
	int codigoFornecedor;
	char unidade[TAMANHO_UNIDADE];
}MATERIALFORNECEDOR;

typedef struct{
	int codProduto;
	int codMaterial;
	float QuantidadeMateriais;
} MATERIALPRODUTO; // Esta struct se refere a uma conexão entre a struct MATERIAL e a struct PRODUTO
                   // Desta forma apenas um produto pode ter vários materiais necessários para construí-lo
                   
typedef struct{
	int codigo;
	int codProduto;
	int codMaterial;
	int quantidadePedido;
	int codigoEmpresa;
	int codigoFornecedor;
} PEDIDO;

typedef struct nomes{
	char nome[TAMANHO_NOME];
	int codFornecedor;
	int codEmpresa;
	int codMaterial;
	int QuantidadeDoMaterial;
	int JaFoi = 1;
	struct nomes *p;
}NOMES;



void TelaDeLogin();
void TelaCadastroLogin();
void MenuEmpresa(EMPRESA empresa);
void MenuFornecedor(FORNECEDOR fornecedor);
void CadastroProdutos (EMPRESA empresa);
void CadastrarMateriaisDisponiveis (FORNECEDOR fornecedor);
void Pedido(EMPRESA empresa);
void ListarProdutos(EMPRESA empresa);
void ListarMateriais(FORNECEDOR fornecedor);
void FazerPedido (int CodigoEmpresa, int CodigoFornecedor, int CodigoMaterial, int CodigoProduto, int quantidade, int codigo);
void ListarPedidoEmpresa(EMPRESA empresa);
void ListarPedidoFornecedor(FORNECEDOR fornecedor);

// Needs the argument MaxSize, which is the maximum size of the password
// Returns the string password

void cursor(COORD coord,char c) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	printf("%c", c);
}

char *GetPassword (int MaxSize) {
	
	char *password, character;
	int j = 0;
		
	while (character != 13) {
		if (j <= MaxSize)
			character = getch();
			
		if (j < MaxSize) {
			if (isalnum(character)) {
					password[j] = character;
					j++;
					printf ("*");
			}
		}
		if (!isalnum(character) && character == 8) {
			if (j > 0) {
				password[j] = '\0';
				printf ("\b \b");
				j--;
			}
		}
	}
	password[j] = '\0';
	
	return password;
}

// Needs the argument MaxSize, which is the maximum size of the string
// Returns the string
char *GetString (int MaxSize) {
	
	char *string, character;
	int j = 0;
		
	while (character != 13) {
		if (j <= MaxSize)
			character = getch();
			
		if (j < MaxSize) {
			if (isalnum(character) || character == 32) {
					string[j] = character;
					j++;
					printf ("%c", character);
			}
		}
		if (!isalnum(character) && character == 8) {
			if (j > 0) {
				string[j] = '\0';
				printf ("\b \b");
				j--;
			}
		}
	}
	string[j] = '\0';
	
	printf ("\n");
	
	return string;
}

void menu(int id){
	COORD cr;
	char ch;
		 
	switch(id){
		
		case 1:
			cr.X = 20;
			cr.Y = 6;
			system ("cls");	
			printf ("***********************************************************************************************************************\n");
			printf ("*********************************************** MENU PRINCIPAL ********************************************************\n");
			printf ("***********************************************************************************************************************\n\n");
			printf ("------------------------ SELECIONE O NUMERO DA OPCAO DESEJADA. PRESSIONE \"ESC\" PARA SAIR ----------------------------\n");
			printf (" \n");
			printf ("**                                           Fazer login                                                             **\n");
			printf ("**                                      Cadastrar novo usuario                                                       **\n");
			do {
				if (kbhit()){
					ch = getch(); 
					printf("%c",ch);
					switch (ch){
						case MOVE_UP:
							printf("PRA CIMA PORRAAAAAAAAAAAAAAAA");
						break;
					}
				}
			}while(ch!=ESC);
			
//			switch (ch) {
//				case '1':	
//					printf ("\n");
//					TelaDeLogin();
//					break;
//					
//				case '2':
//					printf ("\n");
//					TelaCadastroLogin();
//					break;
//									
//				default:
//					if (ch != 27) {
//						printf ("Opcao invalida.");
//						Sleep (500);
//					}
//					break;
//			}
		break;
		case 2:
		
		break;
		case 3:
		
		break;
	}
}
