//KAROLINY ANDRISEN DO PRADO NEPPEL - V01//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define TAM_MAX 100

//STRUCTS
struct Pessoa {
    char vNome[TAM_MAX];
    int telefone;
    char vEmail[TAM_MAX];
};
typedef struct Pessoa Pessoa;

struct Funcionario {
    int matricula;
    float salario;
	Pessoa p1;
};
typedef struct Funcionario Funcionario;

FILE * abrirArquivo(char *nomeArq, char *modo) {
    // ABRIR o arquivo
    FILE * arq;
    arq = fopen(nomeArq, modo);
    if ( arq == NULL) {
        printf("ERRO ao abrir o arquivo.");
        //exit(-1);
    }
    return arq;
}

void gravarArquivo(Funcionario *vetor, int qtde) {

    FILE * arquivo;

    arquivo = abrirArquivo("funcionarios.bin", "wb");    
    
    fwrite(&qtde, sizeof(int), 1, arquivo);
    fwrite(vetor, sizeof(Funcionario), qtde, arquivo);


    fclose(arquivo);  
}


void lerArquivo(Funcionario *vetor, int *qtde) {

    FILE * arquivo;

    arquivo = abrirArquivo("funcionarios.bin", "rb");    
    
    fread(qtde, sizeof(int), 1, arquivo);
    fread(vetor, sizeof(Funcionario), *qtde, arquivo);

    fclose(arquivo);
    
}

//FUNÇ?O PESQUISAR MATRICULA
int pesquisarMat (Funcionario *vetor, int qtde, int pesq) {
	int i;
	for (i = 0; i < qtde; i++) {
 		if (vetor[i].matricula == pesq) {
		return i;
 		}
	}
	return -1;
}

//FUNÇ?O PESQUISAR NOME
int pesquisarNome (Funcionario *vetor, int qtde, char *pesq) {
	for (int i = 0; i < qtde; i++) {

		//STRCMP PARA COMPARAR DUAS STRINGS
        if (strcmp(vetor[i].p1.vNome, pesq) == 0) {
            return i;
        }
    }
    return -1;
}

//LER NOME
void lerNome(Funcionario *f1) {
	int t;
	printf("\nInsira o nome do funcionário: ");
    fgets(f1->p1.vNome, TAM_MAX, stdin);

    t = strlen(f1->p1.vNome);

    f1->p1.vNome[t - 1] = '\0';
}

//LER TELEFONE
void lerTelefone(Funcionario *f1) {
	printf("\nInsira o telefone: +55 (27) ");
    scanf("%d", &f1->p1.telefone);
	getchar();

	while (f1->p1.telefone < 0) {
		printf("\nInválido! Insira o telefone: ");
    	scanf("%d", &f1->p1.telefone);
		getchar();
	}
}

//LER E-MAIL
void lerEmail(Funcionario *f1){
	int t;
	printf("\nInsira o e-mail: ");
    fgets(f1->p1.vEmail, TAM_MAX, stdin);
	    
	t = strlen(f1->p1.vEmail);

    f1->p1.vEmail[t - 1] = '\0';
}

//LER MATRICULA
void lerMatricula (Funcionario *f1, Funcionario *vFuncionarios, int tamVFunc) {
	int res;
	printf("\nInsira a matrícula: ");
	scanf("%d", &f1->matricula);
    getchar();

	//PESQUISA SE JÁ HÁ AQUELA MATRICULA CADASTRADA
	res = pesquisarMat(vFuncionarios, tamVFunc, f1->matricula);
	//SE SIM, RETORNA A POSIÇ?O QUE ELA SE ENCONTRA E FAZ ISSO ATÉ O USUÁRIO DIGITAR
	//UMA MATRICULA QUE N?O ESTEJA CADASTRADA
	while (res != -1){
		printf("Matrícula já cadastrada! Insira uma nova matrícula: ");
		scanf("%d", &f1->matricula);
    	getchar();

		res = pesquisarMat(vFuncionarios, tamVFunc, f1->matricula);
	}

}

//LER SALARIO
void lerSalario (Funcionario *f1){
 	printf("\nInsira o salário atual: R$ ");
    scanf("%f", &f1->salario);
	getchar();

	while (f1->salario < 0){
		printf("Inválido! Insira um valor maior que zero: R$");
    	scanf("%f", &f1->salario);
		getchar();
	}
}

//FUNÇ?O PARA JUNTAR TODAS AS CHAMADAS DE ENTRADA DE DADOS
void inserirFunc(Funcionario *f1, Funcionario *vFuncionarios, int tamVFunc) {
	lerMatricula(f1, vFuncionarios, tamVFunc);
	lerNome(f1);
	lerTelefone(f1);
	lerEmail(f1);
	lerSalario(f1);
}

//CADASTRAR FUNCIONÁRIOS NO VFUNCIONARIOS
void cadFunc(Funcionario *vFuncionarios, int *tamVFunc){
	char continuar = 'S';
	do {
		//INSERE OS DADOS DOS USUÁRIOS NO VETOR VFUNCIONARIOS E ATUALIZA O TAMANHO
		inserirFunc(&vFuncionarios[*tamVFunc], vFuncionarios, *tamVFunc);
		(*tamVFunc)++;

		printf("\nDeseja adicionar mais funcionários? (S/N): ");
		scanf("%c", &continuar);
	} while (toupper(continuar) == 'S');
}

//PESQUISAR FUNCIONÁRIO POR MATRÍCULA
void pesqMat (Funcionario *vFuncionarios, int tamVFunc){
	int res, pesq;
	//PEDE A MATRICULA PARA PESQUISAR
	printf("\nInsira a matrácula a ser pesquisada: ");
	scanf("%d", &pesq);

	//VERFIFICAR SE A MATRICULA EXISTE
	res = pesquisarMat(vFuncionarios, tamVFunc, pesq);
	while (res == -1){
		//SE N?O EXISTE, PEDE PARA DIGITAR OUTRA
		printf("\nNão existe ninguám cadastrado com essa matrícula!\n");
		printf("\nInsira a matrícula a ser pesquisada: ");
		scanf("%d", &pesq);

		res = pesquisarMat(vFuncionarios, tamVFunc, pesq);
	}
	//SE EXISTIR RETORNA OS DADOS
	if (res != -1) {
		printf("\nNome: %s\nTelefone: +55 (27) %d\nE-mail: %s\n", vFuncionarios[res].p1.vNome, vFuncionarios[res].p1.telefone, vFuncionarios[res].p1.vEmail);
		printf("Matrícula: %d\nSalário: R$ %.2f\n", vFuncionarios[res].matricula, vFuncionarios[res].salario);
	}
	
}

//PESQUISAR FUNCIONÁRIO POR NOME
void pesqNome (Funcionario *vFuncionarios, int tamVFunc){
	int res;
	char pesq[100];
	int t;
	//PEDE O NOME PARA PESQUISAR
	printf("\nInsira o nome completo do funcionário: ");
	fgets(pesq, TAM_MAX, stdin);
	t = strlen(pesq);
	pesq[t - 1] = '\0';

	//VERIFICA SE O NOME EXISTE
	res = pesquisarNome(vFuncionarios, tamVFunc, pesq);
	while (res == -1) {
		//SE N?O EXISTIR PEDE NOVAMENTE ATá COLOCAR UM QUE EXISTA
		printf("\nNão existe funcionário cadastrado com esse nome!\n");
		printf("\nInsira o nome completo do funcionário: ");
		fgets(pesq, TAM_MAX, stdin);
		t = strlen(pesq);
		pesq[t - 1] = '\0';

		res = pesquisarNome(vFuncionarios, tamVFunc, pesq);
	}
	//SE EXISTIR RETORNA OS DADOS
	if (res != -1){
		printf("\nNome: %s\nTelefone: +55 (27) %d\nE-mail: %s\n", vFuncionarios[res].p1.vNome, vFuncionarios[res].p1.telefone, vFuncionarios[res].p1.vEmail);
		printf("Matrícula: %d\nSalário: R$ %.2f", vFuncionarios[res].matricula, vFuncionarios[res].salario);
		printf("\n");
		res = pesquisarNome(vFuncionarios, tamVFunc, pesq);
		
	}
	
}

//FUNÇ?O REMOVER
void removerFunc (Funcionario *vetor, int *qtde, int pos) {
	int i;
	for (i = pos; i < *qtde- 1; i++) {
		vetor[i] = vetor[i+1];
	}
	(*qtde)--;
}

//REMOVENDO FUNCIONÁRIO
void removerFuncionario(Funcionario *vFuncionarios, int *tamVFunc) {
	int res, mat;
	//PEDE A MATRÍCULA A SER EXCLUÍDA
	printf("\nInsira a matrícula do funcionário a ser excluído: ");
	scanf("%d", &mat);

	//VERIFICA SE EXISTE AQUELA MATRÍCULA CADASTRADA
	res = pesquisarMat(vFuncionarios, *tamVFunc, mat);
	while (res == -1){
		//SE N?O EXISTIR, PEDE NOVAMENTE ATÉ DIGITAR UMA VÁLIDA
		printf("\nNão existe funcionário cadastrado com essa matrícula!\n");
		printf("\nInsira a matrícula do funcionário a ser excluído: ");
		scanf("%d", &mat);

		res = pesquisarMat(vFuncionarios, *tamVFunc, mat);
	}

	if (res != -1) {
		//SE EXISTIR REMOVE O FUNCIONÁRIO DO VFUNCIONARIOS E MOSTRA A MENSAGEM DE SUCESSO
		removerFunc(vFuncionarios, tamVFunc, res);
		printf("\nFuncionário removido com sucesso!\n");
	}
	
}

//AUMENTAR SALÁRIO
void aumentarSalario(Funcionario *vFuncionarios, int tamVFunc) {
	int res, mat;
	float p;
	//PEDE A MATRÍCULA
	printf("\nInsira a matrícula do funcionário: ");
	scanf("%d", &mat);

	//PESQUISA SE ESSA MATRÍCULA EXISTE
	res = pesquisarMat(vFuncionarios, tamVFunc, mat);
	while (res == -1){
		//SE N?O EXISTIR, PEDE NOVAMENTE ATá DIGITAR UMA VáLIDA
		printf("\nNão existe funcionário cadastrado com essa matrícula!\n");
		printf("\nInsira a matrícula do funcionário: ");
		scanf("%d", &mat);

		res = pesquisarMat(vFuncionarios, tamVFunc, mat);
	}

	//SE EXISTIR
	if (res != -1) {
		//PEDE O VALOR DO AUMENTO
		printf("\nInsira o valor do aumento em porcentagem: ");
		scanf("%f", &p);

		//VERIFICA SE O VALOR É VÁLIDO
		while (p < 0){
			printf("\nInválido! Insira o valor do aumento: ");
			scanf("%f", &p);
		}

		//ATUALIZANDO VALOR
		vFuncionarios[res].salario += (vFuncionarios[res].salario * (p / 100));
		printf("\nSalário atualizado!\n");
	}
	
}

//DESCOBRIR MAIOR SALÁRIO
void maiorSalario(Funcionario *vFuncionarios, int tamVFunc){
	//COLOCA O MAIOR SALÁRIO SENDO O PRIMEIRO APENAS PARA COMPARAÇ?O
	int i, maior = vFuncionarios[0].salario, maiorI = 0;

	//COM O FOR PASSA ÍNDICE POR ÍNDICE
	for(i = 0; i < tamVFunc; i++){
		//SE OUTRO ÍNDICE POSSUIR O SALÁRIO MAIOR QUE O ANTERIOR ENT?O A
		//VARIÁVEL MAIOR RECEBE O NOVO MAIOR
		if (vFuncionarios[i].salario > maior){
			maior = vFuncionarios[i].salario;
			maiorI = i;
		}
	}

	//PRINT DO FUNCIONÁRIO COM MAIOR SALÁRIO
	printf("O funcionário de maior salário é: \n");
	printf("\nNome: %s\nTelefone: +55 (27) %d\nE-mail: %s\n", vFuncionarios[maiorI].p1.vNome, vFuncionarios[maiorI].p1.telefone, vFuncionarios[maiorI].p1.vEmail);
	printf("Matrícula: %d\nSalário: R$ %.2f\n", vFuncionarios[maiorI].matricula, vFuncionarios[maiorI].salario);
}

//LISTAR FUNCIONÁRIOS
void listarFunc(Funcionario *vFuncionarios, int tamVFunc) {
	int i, n = 1;
	//LISTA TODOS OS FUNCIONARIOS APENAS MATRÍCULA E SALÁRIO
	for (i = 0; i < tamVFunc; i++){
	printf("\nFuncionário %d", n);
	printf("\nMatrícula: %d\nSalário: R$ %.2f\n", vFuncionarios[i].matricula, vFuncionarios[i].salario);
	n++;
	}
}


int menu() {
	int op;
	system("@cls||clear");  
	printf("\n\nSISTEMA DE FOLHA DE PAGAMENTO\n\n");
	printf("1 - Inserir Funcionário\n");
	printf("2 - Pesquisar por Matrícula\n");
	printf("3 - Pesquisar por Nome de Funcionário\n");
	printf("4 - Aumentar Salário\n");
	printf("5 - Maior Salário\n");
	printf("6 - Excluir Funcionário\n");
	printf("7 - Listar Funcionário\n");
	printf("0 - Sair\n");
	do {
		printf("Escolha sua opção: ");
		scanf(" %d", &op);
		getchar();
	} while(op < 0 || op > 7);
	return op;
}

int main() {
	setlocale(LC_ALL, "Portuguese");
	int op;
	Funcionario vFuncionarios[TAM_MAX];
	int tamVFunc = 0;

	lerArquivo(vFuncionarios, &tamVFunc);

	do {
		op = menu();
		switch (op) {
			case 0:
				gravarArquivo(vFuncionarios, tamVFunc);
				break;
			case 1:
			//INSERIR FUNCIONÁRIOS
                cadFunc(vFuncionarios, &tamVFunc);
				break;
			case 2:
			//PESQUISAR POR MATRÍCULA
				pesqMat(vFuncionarios, tamVFunc);
				break;
			case 3:
			//PESQUISAR POR NOME
				pesqNome(vFuncionarios, tamVFunc);
				break;
			case 4:
			//AUMENTAR SALÁRIO
				aumentarSalario(vFuncionarios, tamVFunc);
				break;
			case 5:
			//MAIOR SALÁRIO
				maiorSalario(vFuncionarios, tamVFunc);
				break;
			case 6:
			//REMOVER FUNCIONÁRIO
				removerFuncionario(vFuncionarios, &tamVFunc);
				break;
			case 7:
			//LISTAR FUNCIONÁRIOS
				listarFunc(vFuncionarios, tamVFunc);
				break;
			default:
				printf ("\n\nOpção inválida!\n\n");
		}

		system("PAUSE");
	} while (op != 0);

	
	return 0;
}