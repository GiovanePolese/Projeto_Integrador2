#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <stdlib.h>
#include "MyInput.h" //Biblioteca exclusiva -> Funções para ler strings e senhas

#define TAMANHO_SENHA 9
#define TAMANHO_USUARIO 25
#define TAMANHO_NOME 50
#define TAMANHO_UNIDADE 15

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
} MATERIAL;

typedef struct{
	int codigo;
	char nomeProduto[TAMANHO_NOME];
	int codigoEmpresa;
}PRODUTO;

typedef struct{
	int codProduto;
	int codMaterial;
	int QuantidadeMateriais;
} MATERIALPRODUTO; // Esta struct se refere a uma conexão entre a struct MATERIAL e a struct PRODUTO
                   // Desta forma apenas um produto pode ter vários materiais necessários para construí-lo
                   
typedef struct{
	int codProduto;
	int quantidadePedido;
} PEDIDO;

void TelaDeLogin();
void TelaCadastroLogin();
void MenuEmpresa(EMPRESA empresa);
void MenuFornecedor(FORNECEDOR fornecedor);
void CadastroProdutos (EMPRESA empresa);
void CadastrarMateriaisDisponiveis ();
void Pedido(EMPRESA empresa);
void ListarProdutos(EMPRESA empresa);

int main() {
	char opcao;
	do {
		system ("cls");	
		printf ("MENU PRINCIPAL:\n\n");
		printf ("DIGITE O NUMERO DA OPCAO DESEJADA. PRESSIONE \"ESC\" PARA SAIR. \n");
		printf ("1. Fazer login.\n");
		printf ("2. Cadastrar novo usuario.\n");

		opcao = getch();
		
		switch (opcao) {
			case '1':	
				printf ("\n");
				TelaDeLogin();
				break;
				
			case '2':
				printf ("\n");
				TelaCadastroLogin();
				break;
								
			default:
				if (opcao != 27) {
					printf ("Opcao invalida.");
					Sleep (500);
				}
				break;
		}
	} while (opcao != 27); // Enquanto (opcao != "ESC");
}

void TelaDeLogin() {
	FILE *LoginEmpresa = fopen("LoginEmpresa.dat", "rb"); // Abre o arquivo "LoginEmpresa.dat" em modo de leitura de binarios
	FILE *LoginFornecedor = fopen("LoginFornecedor.dat", "rb"); // Abre o arquivo "LoginFornecedor.dat" em modo de leitura de binarios
	char usuario[TAMANHO_USUARIO], senha[TAMANHO_SENHA], SenhaCorreta[TAMANHO_SENHA],nome[TAMANHO_NOME];
	int Usuario_SenhaIncorreta = 1, Tipo= 0,Codigo;
	EMPRESA empresa;
	FORNECEDOR fornecedor;
	
	printf ("Usuario: ");
	strcpy (usuario, GetString(TAMANHO_USUARIO-1)); // Função para ler string; Funciona igual ao scanf, porém funciona apenas
	                                                // para strings, além de estipular um valor máximo de leitura.
	                                                // Não havendo, então, a possibilidade de ler uma quantidade de caracteres maior
													// que o tamanho do vetor. 
													// Obs.: O parâmetro é o TAMANHO-1, pois no último índice haverá um '\0', indicando que a string acabou
	printf ("Senha: ");
	strcpy (senha, GetPassword(TAMANHO_SENHA-1)); // Função para ler senha; Funciona igual ao scanf, porém imprime "*" no lugar do caractere
	                                              // Obs.: O parâmetro é o TAMANHO-1, pois segue a mesma lógica citada na Obs. acima
	
	while( fread(&empresa, sizeof(EMPRESA), 1, LoginEmpresa)){ // Lê todo o arquivo LoginEmpresa procurando o usuario digitado
			if(strcmp(empresa.usuario, usuario) == 0) {        // Descobre se ele existe ou não, e então armazena a senha deste para comparar futuramente
           		strcpy (SenhaCorreta, empresa.senha);
           		Tipo = 1;
           		Usuario_SenhaIncorreta = 0;
           		Codigo = empresa.codigo;
           		strcpy(nome, empresa.nome);
		   }
    }
    while( fread(&fornecedor, sizeof(FORNECEDOR), 1, LoginFornecedor)){ // Lê todo o arquivo LoginFornecedor procurando o usuario digitado
			if(strcmp(fornecedor.usuario, usuario) == 0) {           // Descobre se ele existe ou não, e então armazena a senha deste para comparar futuramente
           		strcpy (SenhaCorreta, fornecedor.senha);
           		Tipo = 2;
           		Usuario_SenhaIncorreta = 0;
           		Codigo = fornecedor.codigo;
           		strcpy(nome, fornecedor.nome);
		   }
    }
	
	if (Usuario_SenhaIncorreta == 1) {  // Se Usuario_SenhaIncorreta retornar 1 significa que o usuario não foi encontrado nos arquivos
		printf ("\n\nUsuario nao cadastrado.\n\n");
		fclose(LoginEmpresa);
	    fclose(LoginFornecedor);
		getch();
	}
	else if (strcmp (senha, SenhaCorreta) == 0) { // Senao se SenhaCorreta == senha digitada executa o menu respectivo à seu tipo
		if (Tipo == 1) {
			fclose(LoginEmpresa);
			empresa.codigo = Codigo;
			strcpy(empresa.nome,nome);
			MenuEmpresa(empresa);
		}
		else if (Tipo = 2) {
			fclose(LoginFornecedor);
			fornecedor.codigo = Codigo;
			strcpy(fornecedor.nome,nome);
			MenuFornecedor(fornecedor);
		}
	}
	else {                // Senao significa que a senha digitada e a SenhaCorreta não correspondem
		printf ("\n\nSenha incorreta.");
	    fclose(LoginEmpresa);
	    fclose(LoginFornecedor);
		getch();
	}
}

void TelaCadastroLogin() {
	FILE *loginEmpresa = fopen("LoginEmpresa.dat", "ab+"); // Abre o arquivo "LoginEmpresa.dat" em modo de leitura e alteração de binarios
	FILE *loginFornecedor = fopen("LoginFornecedor.dat", "ab+"); // Abre o arquivo "LoginFornecedor.dat" em modo de leitura e alteração de binarios
	EMPRESA empresa;
	FORNECEDOR fornecedor;
	int JaExiste = 0, Tipo, maior;
	char senha1[TAMANHO_SENHA], senha2[TAMANHO_SENHA], usuario[TAMANHO_USUARIO], nome[TAMANHO_NOME];
	
	do {
		printf("Digite 1 para empresa ou 2 para fornecedor: ");
		scanf ("%d", &Tipo);	
	} while (Tipo != 1 && Tipo != 2);
	
	do {
		JaExiste = 0;
		if (Tipo == 1) {
			printf ("Nome da empresa: ");
			strcpy (nome, GetString(TAMANHO_NOME-1)); // GetString(MaxSize) == Função para ler string de tamanho previamente estipulado;
			strcpy(empresa.nome,nome);

		// {	
			while( fread(&empresa, sizeof(EMPRESA), 1, loginEmpresa)){ 
				if(strcmp(empresa.nome, nome) == 0)
		       		JaExiste = 1;
			}
			fseek(loginEmpresa, 0, SEEK_SET);

			// No início do arquivo, pois quando ele termina de ler o arquivo inteiro (sem a função fseek) o cursor fica no final, não permitindo que se leia novamente esses dados.
			
			while( fread(&fornecedor, sizeof(FORNECEDOR), 1, loginFornecedor)){
				if(strcmp(fornecedor.nome, nome) == 0)
		       		JaExiste = 1;
			}
			fseek(loginFornecedor, 0, SEEK_SET);

   		// } Esta parte entre chaves verifica se o nome da empresa digitado já existe, tanto no arquivo empresa, quanto no arquivo fornecedor
    	
    	// {
			maior = 1;
			while( fread(&empresa, sizeof(EMPRESA), 1, loginEmpresa)){
				if(empresa.codigo >= maior)
	           		maior = empresa.codigo+1;
	    	}
	    	fseek(loginEmpresa, 0, SEEK_SET);

		// } Esta parte entre chaves verifica qual o maior código de empresa salvo no arquivo, e o armazena, adicionando-se 1 ao valor, na variável (maior)
		// Funcionando como um contador.
		}
		else {
			printf ("Nome do fornecedor: ");
			strcpy (nome, GetString(TAMANHO_NOME-1));
			strcpy(fornecedor.nome,nome);
		
		// {	
			while( fread(&empresa, sizeof(EMPRESA), 1, loginEmpresa)){
				if(strcmp(empresa.nome, nome) == 0)
	           		JaExiste = 1;
	    	}
	    	fseek(loginEmpresa, 0, SEEK_SET);
	    	
	    	while( fread(&fornecedor, sizeof(FORNECEDOR), 1, loginFornecedor)){
				if(strcmp(fornecedor.nome, nome) == 0)
	           		JaExiste = 1;
	    	}
	    	fseek(loginFornecedor, 0, SEEK_SET);
	    // } Esta parte entre chaves verifica se o nome do fornecedor digitado já existe, tanto no arquivo empresa, quanto no arquivo fornecedor
			
			maior = 1;
			while( fread(&fornecedor, sizeof(FORNECEDOR), 1, loginFornecedor)){
				if(fornecedor.codigo >= maior)
	           		maior = fornecedor.codigo+1;
	    	}
	    	fseek(loginFornecedor, 0, SEEK_SET);
	    // } Esta parte entre chaves verifica qual o maior código de fornecedor salvo no arquivo, e o armazena, adicionando-se 1 ao valor, na variável (maior)
		// Funcionando como um contador.
		}

		if (JaExiste == 1)
       		printf ("\nJa existe um(a) empresa/fornecedor com este nome. Digite novamente.\n\n");
		else
			if (Tipo == 1)
				strcpy (empresa.nome, nome);
			else
				strcpy (fornecedor.nome, nome);

	} while (JaExiste == 1);
		
	do {
		JaExiste = 0;
		printf ("Usuario: ");
		strcpy (usuario, GetString(TAMANHO_USUARIO-1));

		while( fread(&empresa, sizeof(EMPRESA), 1, loginEmpresa)){
			if(strcmp(empresa.usuario, usuario) == 0)
           		JaExiste = 1;
    	}
    	fseek(loginEmpresa, 0, SEEK_SET);

    	while( fread(&fornecedor, sizeof(FORNECEDOR), 1, loginFornecedor)){
			if(strcmp(fornecedor.usuario, usuario) == 0)
           		JaExiste = 1;
    	}
    	fseek(loginFornecedor, 0, SEEK_SET);
    	if (JaExiste == 1)
       		printf ("\nEste usuario ja existe. Digite novamente.\n\n");
		else
			if (Tipo == 1)
				strcpy (empresa.usuario, usuario);
			else
				strcpy (fornecedor.usuario, usuario);
	} while (JaExiste == 1);

	do {
		printf ("Senha: ");
		strcpy (senha1, GetPassword(TAMANHO_SENHA-1));

		printf ("\nConfirme sua senha: ");
		strcpy (senha2, GetPassword(TAMANHO_SENHA-1));

		if (Tipo == 1) {
			empresa.codigo = maior;
			strcpy(empresa.nome,nome);
			printf ("\nCodigo da empresa: %d", empresa.codigo);
			printf("\nNome da empresa: %s",empresa.nome);
			printf("\nNome do usuario: %s",empresa.usuario);
			if (strcmp (senha1, senha2) == 0) {
				strcpy (empresa.senha, senha1);
				fwrite(&empresa, sizeof(EMPRESA), 1, loginEmpresa);
			}
			else
				printf ("\n\nSenhas nao correspondem. Digite novamente.\n\n");
		}
		else {
			fornecedor.codigo = maior;
			printf ("\nCodigo do fornecedor: %d", fornecedor.codigo);
			
			if (strcmp (senha1, senha2) == 0) {
				strcpy (fornecedor.senha, senha1);
				fwrite(&fornecedor, sizeof(FORNECEDOR), 1, loginFornecedor);
			}
			else
				printf ("\n\nSenhas nao correspondem. Digite novamente.\n\n");
		}
		
	} while  (strcmp (senha1, senha2) != 0);	
	
    fclose(loginEmpresa);
    fclose(loginFornecedor);
    
    printf("\n\nLogin salvo com sucesso!\n\n");
    system("pause");
}

void MenuEmpresa(EMPRESA empresa) {
	char opcao;
	
	do {
		system ("cls");	
		system ("color 6");
		printf("\t\t%s\n\n",empresa.nome);
		system ("color 7");
		printf ("MENU EMPRESA:\n\n");
		printf ("DIGITE O NUMERO DA OPCAO DESEJADA. PRESSIONE \"ESC\" PARA VOLTAR AO MENU PRINCIPAL. \n");
		printf ("1. Cadastrar Produtos.\n");
		printf ("2. Fazer pedido.\n");
		printf ("3. Listar produtos.\n");
		printf ("4. Listar pedidos.\n");

		opcao = getch();
		
		switch (opcao) {
			case '1':
				CadastroProdutos(empresa);
			break;
				
			case '2':
				Pedido(empresa);
			break;
			
			case '3':
				ListarProdutos(empresa);
			break;
				
			case '4':
		
			break;
								
			default:
				if (opcao != 27) {
					printf ("Opcao invalida.");
					Sleep (500);
				}
				break;
		}
	} while (opcao != 27);
}

void MenuFornecedor(FORNECEDOR fornecedor) {
	char opcao;
	
	do {
		system ("cls");	
		printf ("MENU FORNECEDOR:\n\n");
		printf ("DIGITE O NUMERO DA OPCAO DESEJADA. PRESSIONE \"ESC\" PARA VOLTAR AO MENU PRINCIPAL. \n");
		printf ("1. Pedidos.\n");
		printf ("2. Cadastrar materiais disponiveis.\n");

		opcao = getch();
		
		switch (opcao) {
			case '1':	
				break;
				
			case '2':
				CadastrarMateriaisDisponiveis ();	
				break;
								
			default:
				if (opcao != 27) {
					printf ("Opcao invalida.");
					Sleep (500);
				}
				break;
		}
	} while (opcao != 27);
}

void CadastroProdutos (EMPRESA empresa) {
	system("cls");
	FILE *Produto = fopen ("produtos.dat", "ab+");
	FILE *Material = fopen("material.dat","ab+");
	FILE *MaterialProd = fopen("materialproduto.dat","ab+");
	PRODUTO DadosProduto;
	MATERIAL DadosMaterial;
	MATERIALPRODUTO MatProd;
	int JaExiste=0, maior, codmat;
	char nome[TAMANHO_NOME],opcao, unidade;
	printf ("CADASTRO DE PRODUTOS: \n\n");
	do{
		JaExiste = 0;
		printf ("Nome do produto: ");
		strcpy(nome, GetString(TAMANHO_NOME-1));
		maior = 1;
		while( fread(&DadosProduto, sizeof(PRODUTO), 1, Produto)){

			if((stricmp(DadosProduto.nomeProduto, nome) == 0) && (DadosProduto.codigoEmpresa == empresa.codigo)){
           		JaExiste = 1;
			}
           	if(DadosProduto.codigo >= maior){
           			maior = DadosProduto.codigo +1;
			}
		}
    	fseek(Produto, 0, SEEK_SET);
		 
		if(JaExiste == 1 ){
    		printf("\nProduto ja cadastrado !\n");
    		printf("\n");
		}else{
			strcpy(DadosProduto.nomeProduto, nome);
			DadosProduto.codigo = maior;
			DadosProduto.codigoEmpresa = empresa.codigo;
			fwrite(&DadosProduto,sizeof(PRODUTO),1,Produto);
			fclose(Produto);
		}
	}while(JaExiste==1);
	
	//--------------------------------------------------------------------//
	
	maior = 1;
	JaExiste =0;
	do{
		printf ("Nome do material: ");
		strcpy(nome, GetString(TAMANHO_NOME-1));
			
		while( fread(&DadosMaterial, sizeof(MATERIAL), 1, Material)){
			if((strcmp( DadosMaterial.nomeMaterial, nome ) == 0 )){
           		JaExiste = 1;
			}
			if(empresa.codigo >= maior)
	        	maior = DadosMaterial.codigo+1;
    	}
    	fseek(Material, 0, SEEK_SET);
    	
    	if(JaExiste == 1 ){
    		printf("Material ja cadastrado!");
    		printf("\n\n");
		}else{
			do{
				printf("Selecione a unidade de medida: \n 1 para Kg(kilograma)\n 2 para L(litro)\n 3 para Un(unidade): ");
				unidade = getch();
				switch(unidade){
					case '1':
						strcpy(DadosMaterial.unidade,"Kg");
					break;
					
					case '2':
						strcpy(DadosMaterial.unidade,"L");
					break;
					
					case '3':
						strcpy(DadosMaterial.unidade,"Un");
					break;
					
					default:
						unidade=4;
					break;
				}
			}while(unidade==4);
			printf("\nDigite a quantidade de %s necessario(a) para este produto : ",DadosMaterial.unidade);
			scanf("%d",&MatProd.QuantidadeMateriais);
			
			
			strcpy(DadosMaterial.nomeMaterial, nome);
			DadosMaterial.codigo = maior;
			MatProd.codMaterial = maior;
			MatProd.codProduto = DadosProduto.codigo;
			fwrite(&DadosMaterial, sizeof(MATERIAL), 1, Material);
			fwrite(&MatProd, sizeof(MATERIALPRODUTO), 1, MaterialProd);
		}
		printf("\nDeseja adicionar outro material ? (S - sim ou N - nao): \n");
		opcao = getch();
		printf ("\n");
	}while(opcao=='s'||opcao=='S');
	fclose(Material);
	fclose(MaterialProd);
}

void ListarProdutos(EMPRESA empresa) {
	system("cls");
	FILE *Pedido = fopen("pedido.dat","ab");
	FILE *Produto = fopen("produtos.dat","rb");
	FILE *Empresa = fopen("empresa.dat","rb");
	FILE *Material = fopen("material.dat","rb");
	FILE *MaterialProd = fopen("materialproduto.dat","rb");
	PEDIDO pedido;
	PRODUTO prod;
	MATERIAL mat;
	MATERIALPRODUTO matProd;
	int existe = 0;
	
	while (fread(&prod, sizeof(PRODUTO), 1, Produto)) { 
		if (prod.codigoEmpresa == empresa.codigo) {
			if (existe != 1) {
				printf(" Codigo: %d\n",prod.codigo);
				printf(" Nome: %s\n",prod.nomeProduto);
				printf (" Materiais: \n");
			}
			while (fread(&matProd, sizeof(MATERIALPRODUTO), 1, MaterialProd)) {
				if (matProd.codProduto == prod.codigo) {
					while (fread(&mat, sizeof(MATERIAL), 1, Material)){
						if (matProd.codMaterial == mat.codigo) {
							printf ("\t%d%s de %s\n", matProd.QuantidadeMateriais, mat.unidade, mat.nomeMaterial);
						}
					}
					fseek(MaterialProd, 0, SEEK_SET);	
				}
			}
			existe = 1;
			fseek(Material, 0, SEEK_SET);
		}
	}
	fseek(Produto, 0, SEEK_SET);
	getch();
	fclose (Pedido);
	fclose (Produto);
	fclose (Empresa);
	fclose (Material);
	fclose (MaterialProd);
}

void CadastrarMateriaisDisponiveis () {
	system ("cls");
	
	FILE *Material = fopen ("MaterialDoFornecedor.dat", "ab+");
	MATERIAL mat;
	char nome[TAMANHO_NOME], unidade;
	int JaExiste, maior;
	
	printf ("CADASTRO DE MATERIAIS: \n\n");
	do{
		JaExiste = 0;
		printf ("Nome do material: ");
		strcpy(nome, GetString(TAMANHO_NOME-1));
		maior = 1;
		while( fread(&mat, sizeof(MATERIAL), 1, Material)){

			if(strcmp(mat.nomeMaterial, nome) == 0){
           		JaExiste = 1;
			}
           	if(mat.codigo >= maior){
           			maior = mat.codigo +1;
			}
		}
    	fseek(Material, 0, SEEK_SET);
		 
		if(JaExiste == 1 ){
    		printf("\nMaterial ja cadastrado !\n");
    		printf("\n");
		}else{
			strcpy(mat.nomeMaterial, nome);
			mat.codigo = maior;
		}
	}while(JaExiste==1);
	
	do{
		printf("Selecione a unidade de medida: \n 1 para Kg(kilograma)\n 2 para L(litro)\n 3 para Un(unidade) \n");
		unidade = getch();
		switch(unidade){
			case '1':
				strcpy(mat.unidade,"Kg");
			break;
			
			case '2':
				strcpy(mat.unidade,"L");
			break;
			
			case '3':
				strcpy(mat.unidade,"Un");
			break;
			
			default:
				unidade=4;
			break;
		}
	}while(unidade==4);
	
	fclose (Material);
}
void Pedido(EMPRESA empresa){
	//ler o produto
	//Ler a Quantidade
	system("cls");
	FILE *Pedido = fopen("pedido.dat","ab");
	FILE *Produto = fopen("produtos.dat","rb");
	FILE *Empresa = fopen("empresa.dat","rb");
	FILE *Material = fopen("material.dat","rb");
	FILE *MaterialProd = fopen("materialproduto.dat","rb");
	PEDIDO pedido;
	PRODUTO prod;
	MATERIAL mat;
	MATERIALPRODUTO matProd;
	char produto[TAMANHO_NOME];
	int quantidade,existe = 0,opcao;
	
	printf("Digite o produto desejado : ");
	strcpy(produto,GetString(TAMANHO_NOME-1));
	
	while (fread(&prod, sizeof(PRODUTO), 1, Produto)) { 
		if(stricmp(prod.nomeProduto, produto)==0){
			if (prod.codigoEmpresa == empresa.codigo) {
				if (existe != 1) {
					printf("\tCodigo: %d",prod.codigo);
					printf("\tNome: %s",prod.nomeProduto);
					printf ("\tMateriais: ");
				}
				while (fread(&matProd, sizeof(MATERIALPRODUTO), 1, MaterialProd)) {
					printf ("\nCodigo do produto - %d; Material Produto - %d", prod.codigo, matProd.codProduto);
					if (matProd.codProduto == prod.codigo) {
						printf ("\nEntrou no 1\n");
						while (fread(&mat, sizeof(MATERIAL), 1, Material)){
							if (matProd.codMaterial == mat.codigo) {
								printf ("Entrou no 2 ");
								//printf ("\n\t%d%s de %s", matProd.QuantidadeMateriais, mat.unidade, mat.nomeMaterial);
							}
						}
					}
				}
				existe = 1;
			}
		}
	}
	fseek(Material, 0, SEEK_SET);
	fseek(MaterialProd, 0, SEEK_SET);
	fseek(Produto, 0, SEEK_SET);
	
	if(existe == 0){
		printf("Produto %s nao cadastrado.\n",produto);
	}else{
		printf("Este produto que deseja solicitar ? (S - Sim / N - Nao)");
		opcao = getch();
		do{
			if(opcao=='s' || opcao=='S'){
				// TODAS AS OPERAÇÕES			
			
			/*}else{
				MenuEmpresa(empresa);
			*/
			}
		}while(opcao!='S' && opcao !='s' && opcao !='N' && opcao !='n');
	}
		
	system("pause");
	fclose (Pedido);
	fclose (Produto);
	fclose (Empresa);
	fclose (Material);
	fclose (MaterialProd);
}

