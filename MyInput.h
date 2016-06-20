//13 == ASCII code for "ENTER"
//32 == ASCII code for "SPACE"
//8 == ASCII code for "BACKSPACE"
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <locale.h>

#define TAMANHO_SENHA 9
#define TAMANHO_USUARIO 25
#define TAMANHO_NOME 50
#define TAMANHO_UNIDADE 15

#define MOVE_UP 72
#define MOVE_DOWN 80
#define ESC 27
#define ENTER 13
#define CURSOR 175

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
	int codProduto;
	int quantidadePedido;
	int codigoEmpresa;
} PEDIDO;

typedef struct nomes{
	char nome[TAMANHO_NOME];
	int cod;
	struct nomes *p;
}NOMES;

void TelaDeLogin();
void TelaCadastroLogin();
void MenuEmpresa(EMPRESA empresa,FORNECEDOR fornecedor);
void MenuFornecedor(FORNECEDOR fornecedor,EMPRESA empresa);
void CadastroProdutos (EMPRESA empresa);
void CadastrarMateriaisDisponiveis (FORNECEDOR fornecedor);
void Pedido(EMPRESA empresa);
void ListarProdutos(EMPRESA empresa);
void ListarMateriais(FORNECEDOR fornecedor);

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

void menu(int id,EMPRESA empresa, FORNECEDOR fornecedor){
	system("cls");
	COORD cr,cr2;
	char ch,pm;
	char *locale;
	setlocale(LC_ALL, "");
	FILE *fp;
	int op =1;
	switch(id){
		
		case 1:
			cr.X = 17;
			cr.Y = 8;
			cr2.X = 50;
			cr2.Y = 8;
			fp = fopen("menu.txt", "r");
			while ((pm = fgetc(fp)) != EOF) {
				printf("%c", pm);
			}
			fclose(fp);
			do{
				if(kbhit()){
					ch = getch();
					fflush(stdin);
					switch(ch){
						case MOVE_DOWN:
							if(op==1){
								// apaga os |
								cr.Y = 8;
								cursor(cr, ' ');
								cr.Y = 9;
								cursor(cr, ' ');
								cr.Y = 10;
								cursor(cr, ' ');
								cr2.Y = 8;
								cursor(cr2, ' ');
								cr2.Y = 9;
								cursor(cr2, ' ');
								cr2.Y = 10;
								cursor(cr2, ' ');
								// escreve os |
								cr.Y = 11;
								cursor(cr, '|');
								cr.Y = 12;
								cursor(cr, '|');
								cr.Y = 13;
								cursor(cr, '|');
								cr2.Y = 11;
								cursor(cr2, '|');
								cr2.Y = 12;
								cursor(cr2, '|');
								cr2.Y = 13;
								cursor(cr2, '|');
							}
							op = 2;
						break;
						
						case MOVE_UP:
							if(op==2){
								//apaga os |
								cr.Y = 11;
								cursor(cr, ' ');
								cr.Y = 12;
								cursor(cr, ' ');
								cr.Y = 13;
								cursor(cr, ' ');
								cr2.Y = 11;
								cursor(cr2, ' ');
								cr2.Y = 12;
								cursor(cr2, ' ');
								cr2.Y = 13;
								cursor(cr2, ' ');
								//escreve os |
								cr.Y = 8;
								cursor(cr, '|');
								cr.Y = 9;
								cursor(cr, '|');
								cr.Y = 10;
								cursor(cr, '|');
								cr2.Y = 8;
								cursor(cr2, '|');
								cr2.Y = 9;
								cursor(cr2, '|');
								cr2.Y = 10;
								cursor(cr2, '|');
							}
							op=1;
						break;
						case ENTER:
							cr.X = 0;
							cr.Y = 20;
							cursor(cr,' ');
							if(op==1){
								TelaDeLogin();
							}else if(op==2){
								TelaCadastroLogin();
							}
						break;
					}
				}
			}while(ch!=ESC);
		break;
		case 2:
			cr.X = 18;
			cr.Y = 6;
			cr2.X = 49;
			cr2.Y = 6;
			fp = fopen("menu2.txt", "r");
			while ((pm = fgetc(fp)) != EOF) {
				printf("%c", pm);
			}
			fclose(fp);
			do{
				if(kbhit()){
					ch = getch();
					fflush(stdin);
					switch(ch){
						case MOVE_DOWN:
							if(op<=3){
								switch(op){
									case 1:
										cr.Y =8;
										cursor(cr, ' ');
										cr.Y =9;
										cursor(cr, ' ');
										cr.Y = 10;
										cursor(cr, ' ');
										cr2.Y = 8;
										cursor(cr2, ' ');
										cr2.Y = 9;
										cursor(cr2, ' ');
										cr2.Y = 10;
										cursor(cr2, ' ');
										// escreve os |
										cr.Y = 11;
										cursor(cr, '|');
										cr.Y = 12;
										cursor(cr, '|');
										cr.Y = 13;
										cursor(cr, '|');
										cr2.Y = 11;
										cursor(cr2, '|');
										cr2.Y = 12;
										cursor(cr2, '|');
										cr2.Y = 13;
										cursor(cr2, '|');
										op ++;
									break;
									case 2:
										cr.Y =11;
										cursor(cr, ' ');
										cr.Y =12;
										cursor(cr, ' ');
										cr.Y = 13;
										cursor(cr, ' ');
										cr2.Y = 11;
										cursor(cr2, ' ');
										cr2.Y = 12;
										cursor(cr2, ' ');
										cr2.Y = 13;
										cursor(cr2, ' ');
										// escreve os |
										cr.Y = 14;
										cursor(cr, '|');
										cr.Y = 15;
										cursor(cr, '|');
										cr.Y = 16;
										cursor(cr, '|');
										cr2.Y = 14;
										cursor(cr2, '|');
										cr2.Y = 15;
										cursor(cr2, '|');
										cr2.Y = 16;
										cursor(cr2, '|');
										op++;
									break;
									case 3:
										cr.Y =14;
										cursor(cr, ' ');
										cr.Y =15;
										cursor(cr, ' ');
										cr.Y = 16;
										cursor(cr, ' ');
										cr2.Y = 14;
										cursor(cr2, ' ');
										cr2.Y = 15;
										cursor(cr2, ' ');
										cr2.Y = 16;
										cursor(cr2, ' ');
										// escreve os |
										cr.Y = 17;
										cursor(cr, '|');
										cr.Y = 18;
										cursor(cr, '|');
										cr.Y = 19;
										cursor(cr, '|');
										cr2.Y = 17;
										cursor(cr2, '|');
										cr2.Y = 18;
										cursor(cr2, '|');
										cr2.Y = 19;
										cursor(cr2, '|');
										op++;
									break;
								}								
							}
						break;
						
						case MOVE_UP:
							if(op>=1){
								switch(op){
									case 4:
										cr.Y =14;
										cursor(cr, '|');
										cr.Y =15;
										cursor(cr, '|');
										cr.Y = 16;
										cursor(cr, '|');
										cr2.Y = 14;
										cursor(cr2, '|');
										cr2.Y = 15;
										cursor(cr2, '|');
										cr2.Y = 16;
										cursor(cr2, '|');
										// escreve os |
										cr.Y = 17;
										cursor(cr, ' ');
										cr.Y = 18;
										cursor(cr, ' ');
										cr.Y = 19;
										cursor(cr, ' ');
										cr2.Y = 17;
										cursor(cr2, ' ');
										cr2.Y = 18;
										cursor(cr2, ' ');
										cr2.Y = 19;
										cursor(cr2, ' ');
										op--;
									break;
									case 3:
										cr.Y =14;
										cursor(cr, '|');
										cr.Y =15;
										cursor(cr, '|');
										cr.Y = 16;
										cursor(cr, '|');
										cr2.Y = 14;
										cursor(cr2, '|');
										cr2.Y = 15;
										cursor(cr2, '|');
										cr2.Y = 16;
										cursor(cr2, '|');
										// escreve os |
										cr.Y = 17;
										cursor(cr, ' ');
										cr.Y = 18;
										cursor(cr, ' ');
										cr.Y = 19;
										cursor(cr, ' ');
										cr2.Y = 17;
										cursor(cr2, ' ');
										cr2.Y = 18;
										cursor(cr2, ' ');
										cr2.Y = 19;
										cursor(cr2, ' ');
										op--;
									break;
									case 2:
										cr.Y =11;
										cursor(cr, '|');
										cr.Y =12;
										cursor(cr, '|');
										cr.Y = 13;
										cursor(cr, '|');
										cr2.Y = 11;
										cursor(cr2, '|');
										cr2.Y = 12;
										cursor(cr2, '|');
										cr2.Y = 13;
										cursor(cr2, '|');
										// escreve os |
										cr.Y = 14;
										cursor(cr, ' ');
										cr.Y = 15;
										cursor(cr, ' ');
										cr.Y = 16;
										cursor(cr, ' ');
										cr2.Y = 14;
										cursor(cr2, ' ');
										cr2.Y = 15;
										cursor(cr2, ' ');
										cr2.Y = 16;
										cursor(cr2, ' ');
										op--;
										printf("%d",op);
									break;
									case 1:
										cr.Y =8;
										cursor(cr, '|');
										cr.Y =9;
										cursor(cr, '|');
										cr.Y = 10;
										cursor(cr, '|');
										cr2.Y = 8;
										cursor(cr2, '|');
										cr2.Y = 9;
										cursor(cr2, '|');
										cr2.Y = 10;
										cursor(cr2, '|');
										// escreve os |
										cr.Y = 11;
										cursor(cr, ' ');
										cr.Y = 12;
										cursor(cr, ' ');
										cr.Y = 13;
										cursor(cr, ' ');
										cr2.Y = 11;
										cursor(cr2, ' ');
										cr2.Y = 12;
										cursor(cr2, ' ');
										cr2.Y = 13;
										cursor(cr2, ' ');

								}
							}
						break;
						case ENTER:
							if(cr.Y == 6){
								CadastroProdutos(empresa);
							}else if(cr.Y == 13){
								Pedido(empresa);
							}else if(cr.Y == 16){
								ListarProdutos(empresa);
							}else if(cr.Y == 19){
								
							}
						break;
					}
				}
			}while(ch!=ESC);
		break;
		case 3:
			cr.X = 20;
			cr.Y = 5;	
			printf ("***********************************************************************************************************************\n");
			printf ("********************************************** MENU FORNECEDOR ********************************************************\n");
			printf ("***********************************************************************************************************************\n");
			printf ("***************** DIGITE O NUMERO DA OPCAO DESEJADA. PRESSIONE \"ESC\" PARA VOLTAR AO MENU PRINCIPAL ********************\n");
			printf ("**                                                 Pedidos                                                           **\n");
			printf ("**                                     Cadastrar materiais disponiveis                                               **\n");
			printf ("**                                      Listar materiais disponiveis                                                 **\n");
			printf ("*********************************************************************************************************************** \n");

			do{
				if(kbhit()){
					ch = getch();
					fflush(stdin);
					switch(ch){
						case MOVE_UP:
							if(cr.Y>5){
								cursor(cr,' ');
								cr.Y--;
								cursor(cr,CURSOR);
							}
						break;
						
						case MOVE_DOWN:
							if(cr.Y<7){
								cursor(cr,' ');
								cr.Y++;
								cursor(cr,CURSOR);
							}
						break;
						case ENTER:
							if(cr.Y==5){
								CadastroProdutos(empresa);
							}else if(cr.Y == 6){
								Pedido(empresa);
							}else if(cr.Y == 7){
								ListarProdutos(empresa);
							}
						break;
					}
				}
			}while(ch!=ESC);
		break;
	}
}
