#include <stdio.h>
#include <conio.c>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#include <ctype.h>
#include <stdlib.h>
#include "MyInput.h" //Biblioteca exclusiva -> Fun��es para ler strings e senhas

int main() {
	char opcao;
	do {
		system ("cls");	
		printf ("***********************************************************************************************************************\n");
		printf ("*********************************************** MENU PRINCIPAL ********************************************************\n");
		printf ("***********************************************************************************************************************\n");
		printf ("------------------------ SELECIONE O NUMERO DA OPCAO DESEJADA. PRESSIONE \"ESC\" PARA SAIR -----------------------------\n");
		printf (" \n");
		printf ("**                                           Fazer login                                                             **\n");
		printf ("**                                      Cadastrar novo usuario                                                       **\n");

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
	strcpy (usuario, GetString(TAMANHO_USUARIO-1)); // Fun��o para ler string; Funciona igual ao scanf, por�m funciona apenas
	                                                // para strings, al�m de estipular um valor m�ximo de leitura.
	                                                // N�o havendo, ent�o, a possibilidade de ler uma quantidade de caracteres maior
													// que o tamanho do vetor. 
													// Obs.: O par�metro � o TAMANHO-1, pois no �ltimo �ndice haver� um '\0', indicando que a string acabou
	printf ("Senha: ");
	strcpy (senha, GetPassword(TAMANHO_SENHA-1)); // Fun��o para ler senha; Funciona igual ao scanf, por�m imprime "*" no lugar do caractere
	                                              // Obs.: O par�metro � o TAMANHO-1, pois segue a mesma l�gica citada na Obs. acima
	
	while( fread(&empresa, sizeof(EMPRESA), 1, LoginEmpresa)){ // L� todo o arquivo LoginEmpresa procurando o usuario digitado
			if(strcmp(empresa.usuario, usuario) == 0) {        // Descobre se ele existe ou n�o, e ent�o armazena a senha deste para comparar futuramente
           		strcpy (SenhaCorreta, empresa.senha);
           		Tipo = 1;
           		Usuario_SenhaIncorreta = 0;
           		Codigo = empresa.codigo;
           		strcpy(nome, empresa.nome);
		   }
    }
    while( fread(&fornecedor, sizeof(FORNECEDOR), 1, LoginFornecedor)){ // L� todo o arquivo LoginFornecedor procurando o usuario digitado
			if(strcmp(fornecedor.usuario, usuario) == 0) {           // Descobre se ele existe ou n�o, e ent�o armazena a senha deste para comparar futuramente
           		strcpy (SenhaCorreta, fornecedor.senha);
           		Tipo = 2;
           		Usuario_SenhaIncorreta = 0;
           		Codigo = fornecedor.codigo;
           		strcpy(nome, fornecedor.nome);
		   }
    }
	
	if (Usuario_SenhaIncorreta == 1) {  // Se Usuario_SenhaIncorreta retornar 1 significa que o usuario n�o foi encontrado nos arquivos
		printf ("\n\nUsuario nao cadastrado.\n\n");
		fclose(LoginEmpresa);
	    fclose(LoginFornecedor);
		getch();
	}
	else if (strcmp (senha, SenhaCorreta) == 0) { // Senao se SenhaCorreta == senha digitada executa o menu respectivo � seu tipo
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
	else {                // Senao significa que a senha digitada e a SenhaCorreta n�o correspondem
		printf ("\n\nSenha incorreta.");
	    fclose(LoginEmpresa);
	    fclose(LoginFornecedor);
		getch();
	}
}

void TelaCadastroLogin() {
	FILE *loginEmpresa = fopen("LoginEmpresa.dat", "ab+"); // Abre o arquivo "LoginEmpresa.dat" em modo de leitura e altera��o de binarios
	FILE *loginFornecedor = fopen("LoginFornecedor.dat", "ab+"); // Abre o arquivo "LoginFornecedor.dat" em modo de leitura e altera��o de binarios
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
			strcpy (nome, GetString(TAMANHO_NOME-1)); // GetString(MaxSize) == Fun��o para ler string de tamanho previamente estipulado;

		// {	
			while( fread(&empresa, sizeof(EMPRESA), 1, loginEmpresa)){ 
				if(strcmp(empresa.nome, nome) == 0)
		       		JaExiste = 1;
			}
			fseek(loginEmpresa, 0, SEEK_SET);

			// No in�cio do arquivo, pois quando ele termina de ler o arquivo inteiro (sem a fun��o fseek) o cursor fica no final, n�o permitindo que se leia novamente esses dados.
			
			while( fread(&fornecedor, sizeof(FORNECEDOR), 1, loginFornecedor)){
				if(strcmp(fornecedor.nome, nome) == 0)
		       		JaExiste = 1;
			}
			fseek(loginFornecedor, 0, SEEK_SET);

   		// } Esta parte entre chaves verifica se o nome da empresa digitado j� existe, tanto no arquivo empresa, quanto no arquivo fornecedor
    	
    	// {
			maior = 1;
			while( fread(&empresa, sizeof(EMPRESA), 1, loginEmpresa)){
				if(empresa.codigo >= maior)
	           		maior = empresa.codigo+1;
	    	}
	    	fseek(loginEmpresa, 0, SEEK_SET);

		// } Esta parte entre chaves verifica qual o maior c�digo de empresa salvo no arquivo, e o armazena, adicionando-se 1 ao valor, na vari�vel (maior)
		// Funcionando como um contador.
		}
		else {
			printf ("Nome do fornecedor: ");
			strcpy (nome, GetString(TAMANHO_NOME-1));
		
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
	    // } Esta parte entre chaves verifica se o nome do fornecedor digitado j� existe, tanto no arquivo empresa, quanto no arquivo fornecedor
			
			maior = 1;
			while( fread(&fornecedor, sizeof(FORNECEDOR), 1, loginFornecedor)){
				if(fornecedor.codigo >= maior)
	           		maior = fornecedor.codigo+1;
	    	}
	    	fseek(loginFornecedor, 0, SEEK_SET);
	    	
	    	
	    // } Esta parte entre chaves verifica qual o maior c�digo de fornecedor salvo no arquivo, e o armazena, adicionando-se 1 ao valor, na vari�vel (maior)
		// Funcionando como um contador.
		}

		if (JaExiste == 1)
       		printf ("\nJa existe um(a) empresa/fornecedor com este nome. Digite novamente.\n\n");
       	else {
       		if (Tipo == 1)
       			strcpy(empresa.nome,nome);
       		else
       			strcpy(fornecedor.nome,nome);
		}
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
	} while (JaExiste == 1);

	do {
		printf ("Senha: ");
		strcpy (senha1, GetPassword(TAMANHO_SENHA-1));

		printf ("\nConfirme sua senha: ");
		strcpy (senha2, GetPassword(TAMANHO_SENHA-1));

		if (Tipo == 1) {
			empresa.codigo = maior;
			strcpy(empresa.nome, nome);
			strcpy(empresa.usuario, usuario);
			printf ("\nCodigo da empresa: %d", empresa.codigo);
			if (strcmp (senha1, senha2) == 0) {
				strcpy (empresa.senha, senha1);
				fwrite(&empresa, sizeof(EMPRESA), 1, loginEmpresa);
			}
			else
				printf ("\n\nSenhas nao correspondem. Digite novamente.\n\n");
		}
		else {
			fornecedor.codigo = maior;
			strcpy(fornecedor.nome, nome);
			strcpy(fornecedor.usuario, usuario);
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
		textcolor (YELLOW);
		printf("\t\t                                  %s\n\n",empresa.nome);
		textcolor (WHITE);
		printf ("***********************************************************************************************************************\n");
		printf ("************************************************ MENU EMPRESA *********************************************************\n");
		printf ("*************** DIGITE O NUMERO DA OPCAO DESEJADA. PRESSIONE \"ESC\" PARA VOLTAR AO MENU PRINCIPAL **********************\n");
		printf ("***********************************************************************************************************************\n");
		printf ("**                                          Cadastrar Produtos                                                       **\n");
		printf ("**                                             Fazer pedido                                                          **\n");
		printf ("**                                            Listar produtos                                                        **\n");
		printf ("**                                             Listar pedidos                                                        **\n");
		printf ("***********************************************************************************************************************\n");

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
				ListarPedidoEmpresa(empresa);
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
		textcolor (YELLOW);
		printf("\t\t                                  %s\n\n",fornecedor.nome);
		textcolor (WHITE);
		printf ("***********************************************************************************************************************\n");
		printf ("********************************************** MENU FORNECEDOR ********************************************************\n");
		printf ("***********************************************************************************************************************\n");
		printf ("***************** DIGITE O NUMERO DA OPCAO DESEJADA. PRESSIONE \"ESC\" PARA VOLTAR AO MENU PRINCIPAL ********************\n");
		printf ("**                                                 Pedidos                                                           **\n");
		printf ("**                                     Cadastrar materiais disponiveis                                               **\n");
		printf ("**                                      Listar materiais disponiveis                                                 **\n");
		printf ("*********************************************************************************************************************** \n");


		opcao = getch();
		
		switch (opcao) {
			case '1':
				ListarPedidoFornecedor(fornecedor);	
				break;
				
			case '2':
				CadastrarMateriaisDisponiveis (fornecedor);	
				break;
				
			case '3':
				ListarMateriais(fornecedor);
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
void CadastrarMateriais(int CodigoProduto){
	FILE *Material = fopen("material.dat","ab+");
	FILE *MaterialProd = fopen("materialproduto.dat","ab+");
	PRODUTO DadosProduto;
	MATERIAL DadosMaterial;
	MATERIALPRODUTO MatProd;
	int JaExiste=0, maior,maior2, codmat;
	char nome[TAMANHO_NOME],opcao, unidade; 
	JaExiste=0;
	
	printf ("Nome do material: ");
	strcpy(nome, GetString(TAMANHO_NOME-1));
	
	maior=1;
	while( fread(&DadosMaterial, sizeof(MATERIAL), 1, Material)){
  		while( fread(&MatProd, sizeof(MATERIALPRODUTO), 1, MaterialProd)){
   			if(stricmp( DadosMaterial.nomeMaterial, nome ) == 0 && MatProd.codProduto == CodigoProduto)
    			JaExiste=1;
  		}
  		if(JaExiste==0){
   			if(DadosMaterial.codigo >= maior)
           		maior = DadosMaterial.codigo+1;
  		}
 	}
	fseek(Material, 0, SEEK_SET);
	
	if(JaExiste == 1 ){
		printf("\nMaterial ja cadastrado!\n");
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
		printf("\n Digite a quantidade de %s necessario(a) para este produto : ",DadosMaterial.unidade);
		scanf("%f",&MatProd.QuantidadeMateriais);
		
		strcpy(DadosMaterial.nomeMaterial, nome);
		DadosMaterial.codigo = maior;
		MatProd.codMaterial = maior;
		MatProd.codProduto = CodigoProduto;
		fwrite(&MatProd, sizeof(MATERIALPRODUTO), 1, MaterialProd);
		fwrite(&DadosMaterial, sizeof(MATERIAL), 1, Material);
	}
	
	fclose(Material);
	fclose(MaterialProd);
}

void CadastroProdutos (EMPRESA empresa) {
	system("cls");
	FILE *Produto = fopen ("produtos.dat", "ab+");
	FILE *Material = fopen("material.dat","ab+");
	FILE *MaterialProd = fopen("materialproduto.dat","ab+");
	PRODUTO DadosProduto;
	MATERIAL DadosMaterial;
	MATERIALPRODUTO MatProd;
	int JaExiste=0, maior2, codmat;
	char nome[TAMANHO_NOME],opcao, unidade;
	printf ("CADASTRO DE PRODUTOS: \n\n");
	do{
		JaExiste = 0;
		printf ("Nome do produto: ");
		strcpy(nome, GetString(TAMANHO_NOME-1));
		maior2 = 1;
		while( fread(&DadosProduto, sizeof(PRODUTO), 1, Produto)){

			if((stricmp(DadosProduto.nomeProduto, nome) == 0) && (DadosProduto.codigoEmpresa == empresa.codigo)){
           		JaExiste = 1;
			} else if(DadosProduto.codigo >= maior2){
           		maior2 = DadosProduto.codigo +1;
			}
		}
    	fseek(Produto, 0, SEEK_SET);
		 
		if(JaExiste == 1 ){
    		printf("\nProduto ja cadastrado !\n");
    		printf("\n");
		}else{
			strcpy(DadosProduto.nomeProduto, nome);
			DadosProduto.codigo = maior2;
			DadosProduto.codigoEmpresa = empresa.codigo;
			fwrite(&DadosProduto,sizeof(PRODUTO),1,Produto);
			fclose(Produto);
		}
	}while(JaExiste==1);
	
	//--------------------------------------------------------------------//
	do{
		CadastrarMateriais(DadosProduto.codigo);
		printf("\nDeseja adicionar outro material ? (S - sim ou N - nao): \n\n");
		opcao = getch();
	}while(opcao=='s'||opcao=='S');
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
	
	while (fread(&prod, sizeof(PRODUTO), 1, Produto)!=NULL) { 
		if (prod.codigoEmpresa == empresa.codigo) {
			printf(" Codigo: %d\n",prod.codigo);
			printf(" Nome: %s\n",prod.nomeProduto);
			printf (" Materiais: \n");
			
			while (fread(&matProd, sizeof(MATERIALPRODUTO), 1, MaterialProd)!=NULL) {
				if (matProd.codProduto == prod.codigo) {
					while (fread(&mat, sizeof(MATERIAL), 1, Material)!=NULL){
						if (matProd.codMaterial == mat.codigo) {
							printf ("\t%f%s de %s\n", matProd.QuantidadeMateriais, mat.unidade, mat.nomeMaterial);
							existe = 1;
						}
					}
				}
				fseek(Material, 0, SEEK_SET);
			}
			fseek(MaterialProd, 0, SEEK_SET);
			printf ("\n\n");	
		}
	}
	fseek(Produto, 0, SEEK_SET);
	
	if (existe == 0)
		printf ("Nenhum produto cadastrado.\n");
	
	getch();
	fclose (Pedido);
	fclose (Produto);
	fclose (Empresa);
	fclose (Material);
	fclose (MaterialProd);
}

void ListarMateriais(FORNECEDOR fornecedor) {
	system("cls");
	FILE *Material = fopen ("MaterialDoFornecedor.dat", "rb");
	MATERIALFORNECEDOR mat;
	int existe = 0;
	
	while (fread(&mat, sizeof(MATERIALFORNECEDOR), 1, Material)!=NULL) { 
		if (mat.codigoFornecedor == fornecedor.codigo) {
			printf(" Codigo: %d\n",mat.codigo);
			printf(" Nome: %s\n",mat.nomeMaterial);
			printf (" Unidade: %s\n\n", mat.unidade);
			existe = 1;
		}
	}
	fseek(Material, 0, SEEK_SET);
	
	if (existe == 0)
		printf ("Nenhum material cadastrado.\n");
	
	getch();	
	fclose (Material);
}

void CadastrarMateriaisDisponiveis (FORNECEDOR fornecedor) {
	system ("cls");
	
	FILE *Material = fopen ("MaterialDoFornecedor.dat", "ab+");
	MATERIALFORNECEDOR mat;
	char nome[TAMANHO_NOME], unidade;
	int JaExiste, maior;
	
	printf ("CADASTRO DE MATERIAIS: \n\n");
	do{
		JaExiste = 0;
		printf ("Nome do material: ");
		strcpy(nome, GetString(TAMANHO_NOME-1));
		maior = 1;
		while( fread(&mat, sizeof(MATERIALFORNECEDOR), 1, Material)){
			if(strcmp(mat.nomeMaterial, nome) == 0 && mat.codigoFornecedor == fornecedor.codigo)
           		JaExiste = 1;
			else if(mat.codigo >= maior)
           		maior = mat.codigo +1;
		}
    	fseek(Material, 0, SEEK_SET);
		 
		if(JaExiste == 1 ){
    		printf("\nMaterial ja cadastrado !\n");
		}else{
			strcpy(mat.nomeMaterial, nome);
			mat.codigo = maior;
			mat.codigoFornecedor = fornecedor.codigo;
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
	fwrite(&mat, sizeof(MATERIALFORNECEDOR), 1, Material);
	
	fclose (Material);
}

NOMES *novo_nome(NOMES *nomes,char nome[TAMANHO_NOME],int p,int codFornecedor, int codEmpresa, int codMaterial){
	NOMES *novo = (NOMES*)malloc(sizeof(NOMES));
	if (!novo == NULL) {
		NOMES *ax;

		if (p == 0) {
			novo->p = nomes;
			nomes = novo;
			nomes->p = NULL;
		}
		else {
			for (ax = nomes; ax->p != NULL; ax = ax->p);
			
			novo->p = ax->p;
			ax->p = novo;
			
		}
			strcpy(novo->nome,nome);
			novo->codFornecedor = codFornecedor;
			novo->JaFoi = 1;		
			novo->codEmpresa = codEmpresa;
			novo->codMaterial = codMaterial;
		
	}
	return nomes;
}

void Pedido(EMPRESA empresa){
	//ler o produto
	//Ler a Quantidade
	system("cls");
	FILE *Produto = fopen("produtos.dat","rb");
	FILE *Material = fopen("material.dat","rb");
	FILE *MaterialProd = fopen("materialproduto.dat","rb");
	FILE *MaterialFornecedor = fopen ("MaterialDoFornecedor.dat", "rb");
	FILE *Fornecedor = fopen("LoginFornecedor.dat", "rb");
	FILE *Ped;
	PRODUTO prod;
	MATERIAL mat;
	FORNECEDOR fornecedor;
	MATERIALPRODUTO matProd;
	MATERIALFORNECEDOR MatFor;
	PEDIDO pedido;
	NOMES *nomes = NULL;
	NOMES *t,*f;
	int quantidadePedido, CodigoFornecedor, ExisteEsse, maior = 1;
	char produto[TAMANHO_NOME], escolha[TAMANHO_NOME];
	int quantidade, existe = 0, opcao, codigo, Tem = 0,PrimeiroMaterial=0,ContaMateriais = 0,ContaMateriaisExistentes = 0, escolhaCodigo;
	
	printf("Digite o produto desejado : ");
	strcpy(produto,GetString(TAMANHO_NOME-1));
	
	Ped = fopen ("pedido.dat", "rb");
	while (fread (&pedido, sizeof (PEDIDO), 1, Ped)) {
		if (pedido.codigo >= maior)
			maior = pedido.codigo+1;
	}
	fclose (Ped);
	
	while (fread(&prod, sizeof(PRODUTO), 1, Produto)!=NULL) { 
		if(stricmp(prod.nomeProduto, produto)==0) {
			if (prod.codigoEmpresa == empresa.codigo) {
				printf(" Codigo: %d\n",prod.codigo);
				printf(" Nome: %s\n",prod.nomeProduto);
				printf (" Materiais: \n");
				existe = 1;
				
				while (fread(&matProd, sizeof(MATERIALPRODUTO), 1, MaterialProd)!=NULL) {
					if (matProd.codProduto == prod.codigo) {
						while (fread(&mat, sizeof(MATERIAL), 1, Material)!=NULL){
							if (matProd.codMaterial == mat.codigo) {
								printf ("\t%f%s de %s\n", matProd.QuantidadeMateriais, mat.unidade, mat.nomeMaterial);
								codigo = prod.codigo;
								ContaMateriais++;
							}
						}
					}
					fseek(Material, 0, SEEK_SET);
				}
				fseek(MaterialProd, 0, SEEK_SET);	
			}
		}
	}
	fseek(Produto, 0, SEEK_SET);
	
	if(existe == 0){
		printf("Produto %s nao cadastrado.\n", produto);
		getch();
	}else{
		printf("\nEste produto que deseja solicitar ? (S - Sim / N - Nao)");
		opcao = getch();
		if(opcao=='s' || opcao=='S'){
			printf ("\n\nQuantidade de produtos: ");
			scanf ("%d", &quantidadePedido);
			while (fread (&MatFor, sizeof(MATERIALFORNECEDOR), 1, MaterialFornecedor)) {
				while (fread(&matProd, sizeof(MATERIALPRODUTO), 1, MaterialProd)!=NULL) {
					if (matProd.codProduto == codigo) {
						while (fread(&mat, sizeof(MATERIAL), 1, Material)!=NULL){
							if (matProd.codMaterial == mat.codigo) {
								if (stricmp (MatFor.nomeMaterial, mat.nomeMaterial) == 0){
									if(PrimeiroMaterial==0){
										nomes = novo_nome(nomes,mat.nomeMaterial,0,MatFor.codigoFornecedor, empresa.codigo, mat.codigo);
										PrimeiroMaterial=1;
									}else{
										nomes = novo_nome(nomes,mat.nomeMaterial,1,MatFor.codigoFornecedor, empresa.codigo, mat.codigo);										
									}
								}								
							}
						}
						fseek(Material, 0, SEEK_SET);
					}
				}
				fseek(MaterialProd, 0, SEEK_SET);
			} 			
			fseek(MaterialFornecedor, 0, SEEK_SET);
			
			/*
			
			ContaMateriais - Conta quantos materiais sao necessarios para produzir o produto
			
			ContaMateriaisExistentes - conta quantos materiais , do determinado produto, foram encontrados nos materiais dos fornecedores
			
			*/
			
			if(nomes!= NULL){
				for (t = nomes; t != NULL; t = t->p){
					ContaMateriaisExistentes++; // Conta quantos materiais foram encontrados 
				}
			}
			if(ContaMateriais == ContaMateriaisExistentes){
				Tem = 1;
			}else if(ContaMateriaisExistentes > ContaMateriais){
				printf("\n\n Possuem em mais de um fornecedor: ");
				Tem = 2;
			}else{
				Tem = 0;
			}
			
			if (Tem == 1) {
				for(t = nomes; t!=NULL;t = t->p){
					if(t->JaFoi==1){
						FazerPedido(t->codEmpresa, t->codFornecedor, t->codMaterial, codigo, quantidadePedido, maior);
					}
				}
			
			}else if(Tem == 2){
				printf(" \n\n MATERIAIS:");
				for (t = nomes; t != NULL; t = t->p){
					for (f = nomes; f != NULL; f = f->p){
						if(stricmp(t->nome,f->nome)==0 && t->codFornecedor != f->codFornecedor && t->JaFoi == 1){
							printf(" \n\n *%s:", t->nome);
							while (fread (&fornecedor, sizeof (FORNECEDOR), 1, Fornecedor)){
								if (t->codFornecedor == fornecedor.codigo || f->codFornecedor == fornecedor.codigo) {
									printf ("\n\t- %s", fornecedor.nome);
									t->JaFoi = 0;
									f->JaFoi = 0;
								}
							}
							fseek(Fornecedor, 0, SEEK_SET);
							 
							do {
								printf("\n Escreva o nome do fornecedor desejado: ");
								strcpy (escolha, GetString(TAMANHO_NOME-1));
								ExisteEsse = 0;
								while (fread (&fornecedor, sizeof (FORNECEDOR), 1, Fornecedor)){
									if (t->codFornecedor == fornecedor.codigo || f->codFornecedor == fornecedor.codigo) {
										if (stricmp(fornecedor.nome, escolha) == 0) {
											ExisteEsse = 1;
											escolhaCodigo = fornecedor.codigo;
										}
									}
								}
								fseek(Fornecedor, 0, SEEK_SET); 
							} while (ExisteEsse == 0);
							FazerPedido(f->codEmpresa, escolhaCodigo, f->codMaterial, codigo, quantidadePedido, maior);
							
						} else if (t->p == NULL && (stricmp (t->nome, f->nome) != 0) && f->JaFoi == 1) {
							printf ("\n\n *%s:", f->nome);
							printf ("\n\t- %s", fornecedor.nome);
							FazerPedido(f->codEmpresa, fornecedor.codigo, f->codMaterial, codigo, quantidadePedido, maior);
						}
					}
				}
			}else{
				printf ("\n\nMaterial(is) nao disponivel(is).");	
			}
		}
	}
	getch();	
	fclose (Produto);
	fclose (Material);
	fclose (MaterialProd);
	fclose (MaterialFornecedor);
	fclose (Fornecedor);
}

void FazerPedido (int CodigoEmpresa, int CodigoFornecedor, int CodigoMaterial, int CodigoProduto, int quantidade, int codigo) {
	FILE *Pedido = fopen ("pedido.dat", "ab");
	FILE *MatProd = fopen ("materialproduto.dat", "rb");
	PEDIDO pedido;
	MATERIALPRODUTO matProd;
	
	while (fread (&matProd, sizeof (MATERIALPRODUTO), 1, MatProd)) {
		if (CodigoMaterial == matProd.codMaterial) {
			pedido.quantidadePedido = quantidade*matProd.QuantidadeMateriais;
		}
	}
	fseek(MatProd, 0, SEEK_SET);
	
	pedido.codigo = codigo;
	pedido.codigoEmpresa = CodigoEmpresa;
	pedido.codigoFornecedor = CodigoFornecedor;
	pedido.codMaterial = CodigoMaterial;
	pedido.codProduto = CodigoProduto;
	
	fwrite (&pedido, sizeof (PEDIDO), 1, Pedido);
	fclose (Pedido);
}

void ListarPedidoEmpresa(EMPRESA empresa){
	system ("cls");
	
	FILE *Pedido = fopen ("pedido.dat", "rb");
	FILE *Produto = fopen("produtos.dat","rb");
	FILE *Material = fopen("material.dat","rb");
	FILE *MaterialProd = fopen("materialproduto.dat","rb");
	FILE *MaterialFornecedor = fopen ("MaterialDoFornecedor.dat", "rb");
	FILE *Fornecedor = fopen("LoginFornecedor.dat", "rb");
	PEDIDO pedido;
	PRODUTO produto;
	MATERIAL material;
	MATERIALPRODUTO MatProd;
	FORNECEDOR fornecedor;
	int codigoAnterior = 0;
	
	while (fread (&pedido, sizeof (PEDIDO), 1, Pedido)) {
		if (pedido.codigoEmpresa == empresa.codigo) {
			while (fread (&produto, sizeof (PRODUTO), 1, Produto)) {
				if (pedido.codProduto == produto.codigo) {
					if (codigoAnterior != pedido.codigo) {
						printf ("---------------------------------------------------------------------------");
						printf ("\nPRODUTO: %s", produto.nomeProduto);
						printf ("\nMATERIAIS: ");
					}
					while (fread (&material, sizeof (MATERIAL), 1, Material)) {
						if (pedido.codMaterial == material.codigo) {
							while (fread (&MatProd, sizeof (MATERIALPRODUTO), 1, MaterialProd)) {
								if (MatProd.codMaterial == material.codigo && MatProd.codProduto == produto.codigo) {
									while (fread (&fornecedor, sizeof (FORNECEDOR), 1, Fornecedor)) {
										if (pedido.codigoFornecedor == fornecedor.codigo) {
											printf ("\n\t*%d%s de %s - Enviado para %s\n", pedido.quantidadePedido, material.unidade, material.nomeMaterial, fornecedor.nome);
										}
									}
									fseek(Fornecedor, 0, SEEK_SET);
								}
							}
							fseek(MaterialProd, 0, SEEK_SET);
						}
					}
					fseek(Material, 0, SEEK_SET);
				}
			}
			fseek(Produto, 0, SEEK_SET);	
		}
		codigoAnterior = pedido.codigo;
	}
	fseek(Pedido, 0, SEEK_SET);
	getch();
	
	fclose (Pedido);
	fclose (Produto);
	fclose (Material);
	fclose (MaterialProd);
	fclose (MaterialFornecedor);
	fclose (Fornecedor);
}

void ListarPedidoFornecedor(FORNECEDOR fornecedor){
	system ("cls");
	
	FILE *Pedido = fopen ("pedido.dat", "rb");
	FILE *Produto = fopen("produtos.dat","rb");
	FILE *Material = fopen("material.dat","rb");
	FILE *MaterialProd = fopen("materialproduto.dat","rb");
	FILE *MaterialFornecedor = fopen ("MaterialDoFornecedor.dat", "rb");
	FILE *Empresa = fopen("LoginEmpresa.dat", "rb");
	PEDIDO pedido;
	PRODUTO produto;
	MATERIAL material;
	MATERIALPRODUTO MatProd;
	EMPRESA empresa;
	int codigoAnterior = 0;
	
	while (fread (&pedido, sizeof (PEDIDO), 1, Pedido)) {
		if (pedido.codigoFornecedor == fornecedor.codigo) {
			while (fread (&produto, sizeof (PRODUTO), 1, Produto)) {
				if (pedido.codProduto == produto.codigo) {
					if (codigoAnterior != pedido.codigo) {
						printf ("---------------------------------------------------------------------------");
						printf ("\nPRODUTO: %s", produto.nomeProduto);
						printf ("\nMATERIAIS: ");
					}
					while (fread (&material, sizeof (MATERIAL), 1, Material)) {
						if (pedido.codMaterial == material.codigo) {
							while (fread (&MatProd, sizeof (MATERIALPRODUTO), 1, MaterialProd)) {
								if (MatProd.codMaterial == material.codigo && MatProd.codProduto == produto.codigo) {
									while (fread (&empresa, sizeof (EMPRESA), 1, Empresa)) {
										if (pedido.codigoEmpresa == empresa.codigo) {
											printf ("\n\t*%d%s de %s - Solicitado por %s\n", pedido.quantidadePedido, material.unidade, material.nomeMaterial, empresa.nome);
										}
									}
									fseek(Empresa, 0, SEEK_SET);
								}
							}
							fseek(MaterialProd, 0, SEEK_SET);
						}
					}
					fseek(Material, 0, SEEK_SET);
				}
			}
			fseek(Produto, 0, SEEK_SET);	
		}
		codigoAnterior = pedido.codigo;
	}
	fseek(Pedido, 0, SEEK_SET);
	getch();
	
	fclose (Pedido);
	fclose (Produto);
	fclose (Material);
	fclose (MaterialProd);
	fclose (MaterialFornecedor);
	fclose (Empresa);
}

