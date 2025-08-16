//KAROLINY ANDRISEN DO PRADO NEPPEL E SARA MACIEL MARTINS - V01//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define TAM 100

//DEFINIÇÃO DAS STRUCTS (REGISTROS)
//PESSOA
struct Pessoas {
    char vNome[TAM];
    int telefone;
    char cpf[TAM];
};
typedef struct Pessoas Pessoa;

//FUNCIONÁRIO
struct Funcionarios {
    int matricula;
    float salario;
	Pessoa p;
};
typedef struct Funcionarios Funcionario;

//LENDO O NOME
void lerNome(Funcionario *f) {
    int t;
    printf("\nInsira o nome do funcionário: ");
    fgets(f->p.vNome, TAM, stdin);

    t = strlen(f->p.vNome);

    if (t > 0 && f->p.vNome[t - 1] == '\n') {
        f->p.vNome[t - 1] = '\0'; 
    }
}

//LENDO TELEFONE
void lerTelefone(Funcionario *f) {
    printf("\nInsira o telefone: +55 (27) ");
    scanf("%d", &f->p.telefone);
    getchar();

    while (f->p.telefone < 0) {
        printf("\nInválido! Insira o telefone: ");
        scanf("%d", &f->p.telefone);
        getchar();
    }
}

//LENDO CPF
void lerCPF(Funcionario *f) {
    int t;
    printf("\nInsira o CPF: ");
    fgets(f->p.cpf, TAM, stdin);

    t = strlen(f->p.cpf);

    if (t > 0 && f->p.cpf[t - 1] == '\n') {
        f->p.cpf[t - 1] = '\0';
    }
}

//PESQUISAR POR MATRICULA
int pesquisarMat (Funcionario *vetor, int qtde, int pesq) {
	int i;
	//PROCURAR ITEM POR ITEM NO VETOR VFuncionarios SE HÁ A MATRICULA DESEJADA
	for (i = 0; i < qtde; i++) {
		//SE A MATRICULA DESEJADA EXISTIR
 		if (vetor[i].matricula == pesq) {
		//RETORNA A POSIÇÃO NO VETOR QUE ELA SE ENCONTRA
		return i;
 		}
	}
	// SE NÃO ENTRAR RETORNA -1
	return -1;
}

//LENDO A MATRPICULA
void lerMatricula(Funcionario *f, Funcionario *vFuncionarios, int tamVFunc) {
    int res;
    printf("\nInsira a matrícula: ");
    scanf("%d", &f->matricula);
    getchar();

	// ANTES DE CADASTRAR VERIFICA SE A MATRICULA JA EXISTE
    res = pesquisarMat(vFuncionarios, tamVFunc, f->matricula);
    while (res != -1) {
		//SE JA EXISTIR PRINTA ESSA MENSAGEM E PEDE PARA INSERIR OUTRA ATÉ QUE
		//ELA NÃO EXISTA
        printf("Matrícula já cadastrada! Insira outra matrícula: ");
        scanf("%d", &f->matricula);
        getchar();
        res = pesquisarMat(vFuncionarios, tamVFunc, f->matricula);
    }
}

//LENDO SALÁRIO
void lerSalario (Funcionario *f){
 	printf("\nInsira o valor fixo do salário: R$ ");
    scanf("%f", &f->salario);
	getchar();

	while (f->salario < 0){
		printf("Inválido! Insira um valor maior que zero: R$");
    	scanf("%f", &f->salario);
		getchar();
	}
}

//FUNÇÃO PARA JUNTAR TODAS AS LEITURAS
void inserirFuncionario(Funcionario *f, Funcionario *vFuncionarios, int tamVetor) {
	lerMatricula(f, vFuncionarios, tamVetor);
	lerNome(f);
	lerTelefone(f);
	lerCPF(f);
	lerSalario(f);
}

//FUNÇÃO PARA CADASTRAR NO VETOR
void cadFuncionarios(Funcionario *vFuncionarios, int *tamVetor) {
    char continuar = 'S';
    do {
		//AQUI INSERE NO VETOR QUANDO A OPÇÃO DE ADMITIR FUNCIONÁRIO É ATIVADA
        inserirFuncionario(&vFuncionarios[*tamVetor], vFuncionarios, *tamVetor);
		//ADICIONA +1 NO TAMVETOR
        (*tamVetor)++;

		//PERGUNTA SE QUER ADICIONAR MAIS OU PARAR
        printf("\nDeseja adicionar mais funcionários? (S/N): ");
        scanf(" %c", &continuar);
        getchar();
		//SE DIGITAR QUALQUER LETRA ALÉM DE "S" PARA DE CADASTRAR
    } while (toupper(continuar) == 'S');
}

//FUNÇÃO DA OPÇÃO DE PESQUISAR POR MATRICULA
void pesqMatricula(Funcionario *vFuncionarios, int tamVFunc) {
	// SE NÃO TIVER NENHUM FUNCIONARIO CADASTRADO NÃO DEIXA PESQUISAR
    if (tamVFunc == 0) {
        printf("\nNenhum funcionário cadastrado!\n");
        return;
    }

    int res, pesq;
    printf("\nInsira a matrícula do funcionário a ser pesquisada: ");
    scanf("%d", &pesq);

	// PESQUISANDO
    res = pesquisarMat(vFuncionarios, tamVFunc, pesq);

    if (res == -1) {
        printf("\nNão existe ninguém cadastrado com essa matrícula!\n");
    } else {
		//PRINTA O FUNCIONÁRIO DA MATRICULA CORRESPONDENTE CASO ACHE
        printf("\n\t|Nome: %s\n\t|Telefone: +55 (27) %d\n\t|CPF: %s\n", vFuncionarios[res].p.vNome, vFuncionarios[res].p.telefone, vFuncionarios[res].p.cpf);
        printf("\t|Matrícula: %d\n\t|Salário: R$ %.2f\n", vFuncionarios[res].matricula, vFuncionarios[res].salario);
    }
}

//FUNÇÃO PARA AUMENTAR SALÁRIO
void aumentarSalario(Funcionario *vFuncionarios, int tamVFunc) {
	int res, matricula;
	float p;
	//PEDE A MATRICULA DO FUNCIONÁRIO QUE TERÁ O SALÁRIO AUMENTADO
	printf("\nInsira a matrícula do funcionário: ");
	scanf("%d", &matricula);

	//PESQUISA SE EXISTE
	res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	while (res == -1){
		printf("\nNão existe nenhum funcionário cadastrado com essa matrícula!\n");
		printf("\nInsira a matrícula do funcionário: ");
		scanf("%d", &matricula);

		res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	}

	if (res != -1) {
		//AQUI INSERE A PORCENTAGEM
		printf("\nInsira o valor do aumento em porcentagem: ");
		scanf("%f", &p);

		while (p < 0){
			printf("\nInválido! Insira o valor do aumento em porcentagem: ");
			scanf("%f", &p);
		}
		//APLICAÇÃO DA FUNÇÃO AFIM SENDO "vFuncionarios[res].salario" O VALO "FIXO" MAIS "(vFuncionarios[res].salario * (p / 100))"
		//QUE É A PARTE VÁRIÁVEL, NO CASO O AUMENTO
		vFuncionarios[res].salario = vFuncionarios[res].salario + (vFuncionarios[res].salario * (p / 100));
		printf("\nSalário do funcionário de matrícula %d atualizado!\n", matricula);
	}
	
}

//FUNÇÃO PARA DIMINUIR/DESCONTAR SALÁRIO
void diminuirSalario(Funcionario *vFuncionarios, int tamVFunc) {
	int res, matricula;
	int d, v;
	//PEDE A MATRICULA DO FUNCIONÁRIO QUE TERÁ O SALÁRIO DESCONTADO
	printf("\nInsira a matrícula do funcionário: ");
	scanf("%d", &matricula);

	//PESQUISA SE EXISTE
	res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	while (res == -1){
		printf("\nNão existe nenhum funcionário cadastrado com essa matrícula!\n");
		printf("\nInsira a matrícula do funcionário: ");
		scanf("%d", &matricula);

		res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	}

	if (res != -1) {
		//PEDE A QUANTIDADE DE DIAS A SEREM DESCONTADOS
		printf("\nInsira a quantidade de dias a serem descontados: ");
		scanf("%d", &d);

		//VALOR DO DIA TRABALHADO
		printf("\nInsira o valor do dia trabalhado: ");
		scanf("%d", &v);

		while (d < 0){
			printf("\nInválido! Insira a quantidade de dias a serem descontados: ");
			scanf("%d", &d);
		}
		//APLICAÇÃO DA FUNÇÃO AFIM SENDO "vFuncionarios[res].salario" O VALO "FIXO" MENOS OS DIAS * O VALOR DO DIA
		//QUE É A PARTE VÁRIÁVEL, NO CASO O DESCONTO
		vFuncionarios[res].salario = vFuncionarios[res].salario - (d * v);
		printf("\nSalário do funcionário de matrícula %d atualizado!\n", matricula);
	}
	
}

//REMOVER FUNCIONÁRIO DO VETOR
void removerFunc (Funcionario *vetor, int *qtde, int pos) {
	int i;
	//EM C NÃO CONSEGUIMOS PAGAR NADA DE UM VETOR, APENAS SOBRESCREVER
	for (i = pos; i < *qtde- 1; i++) {
		vetor[i] = vetor[i+1];
	}
	//TIRA 1 JÁ QUE EXCLUIU
	(*qtde)--;
}

//FUNÇÃO PARA DEMITIR O FUNCIONÁRIO
void demitirFuncionario(Funcionario *vFuncionarios, int *tamVFunc) {
	int res, mat;
	//PEDE A MATRÍCULA DO FUNCIONÁRIO QUE VAI SER DEMITIDO
	printf("\nInsira a matrícula do funcionário a ser excluído: ");
	scanf("%d", &mat);

	//PESQUISA SE EXISTE
	res = pesquisarMat(vFuncionarios, *tamVFunc, mat);
	while (res == -1){
		printf("\nNão existe funcionário cadastrado com essa matrícula!\n");
		printf("\nInsira a matrícula do funcionário a ser excluído: ");
		scanf("%d", &mat);

		res = pesquisarMat(vFuncionarios, *tamVFunc, mat);
	}

	if (res != -1) {
		//QUANDO RETORNAR A POSIÇÃO DO VETOR, ELE USA A FUNÇÃO DE CIMA
		//PARA DELETAR DO VETOR
		removerFunc(vFuncionarios, tamVFunc, res);
		printf("\nFuncionário de matrícula %d removido com sucesso!\n", mat);
	}
	
}

//LISTA TODOS OS FUNCIONÁRIOS CADASTRADOS
void mostrarFuncionarios(Funcionario *vFuncionarios, int tamVFunc) {
	int i;

	//PASSA INDICE POR INDICE DO vFuncionarios E PRINTA CADA
	for (i = 0; i < tamVFunc; i++){
	printf("\n\t|Funcionário %d|\n", i+1);
	printf("\n\t|Nome: %s\n\t|Telefone: +55 (27) %d\n\t|CPF: %s\n", vFuncionarios[i].p.vNome, vFuncionarios[i].p.telefone, vFuncionarios[i].p.cpf);
	printf("\t|Matrícula: %d\n\t|Salário: R$ %.2f\n\n", vFuncionarios[i].matricula, vFuncionarios[i].salario);
	}
}

//FUNÇÃO PARA SIMULAR SALÁRIO
void simularSalario(Funcionario *vFuncionarios, int tamVFunc) {
	int res, matricula, d;
	float comissao, simSalario;
	//PEDE A MATRICULA DO FUNCIONÁRIO QUE VAI TER O SALÁRIO SIMULADO
	printf("\nInsira a matrícula do funcionário: ");
	scanf("%d", &matricula);

	//PESQUISA SE EXISTE
	res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	while (res == -1){
		printf("\nNão existe nenhum funcionário cadastrado com essa matrícula!\n");
		printf("\nInsira a matrícula do funcionário: ");
		scanf("%d", &matricula);

		res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	}

	if (res != -1) {
		//PEDE O TOTAL DE VENDAS
		printf("\nInsira o total de vendas: ");
		scanf("%d", &d);
		//PEDE O VALOR DA COMISSÃO
		printf("\nInsira o valor da comissão (em reais): ");
		scanf("%f", &comissao);

		while (d < 0){
			printf("\nInválido! Insira o valor do aumento em porcentagem: ");
			scanf("%d", &d);
		}

		//APLICAÇÃO DA FUNÇÃO AFIM SENDO "vFuncionarios[res].salario" O VALO "FIXO" MAIS "(comissao * d)"
		//QUE É A PARTE VÁRIÁVEL
		simSalario = vFuncionarios[res].salario + (comissao * d);
		printf("\nSalário do funcionário de matrícula %d atualizado para %.2f!\n", matricula, simSalario);
	}
	
}

//MENU PARA MOSTRAR AS OPÇÕES
int menu() {
	int op;
    printf("\t__________________________________________\n");	
    printf("\n\tFOLHA DE PAGAMENTO\n");
    printf("\t__________________________________________\n");
	printf("\t| 1 | Admitir Funcionário\n");
	printf("\t| 2 | Pesquisar por Matrícula\n");
	printf("\t| 3 | Simular Próximo Salário\n");
	printf("\t| 4 | Aumentar Salário do Funcionário\n");
    printf("\t| 5 | Descontar Salário do Funcionário\n");
	printf("\t| 6 | Demitir Funcionário\n");
	printf("\t| 7 | Mostrar Funcionários cadastrados\n");
	printf("\t| 8 | Sair\n");
    printf("\t__________________________________________\n");	do {
		printf("\n\tEscolha sua opção: ");
		scanf(" %d", &op);
		getchar();
	} while(op < 1 || op > 7);
	return op;
}

//PROGRAMA PRINCIPAL
int main() {
    setlocale(LC_ALL, "Portuguese");
    int op;
    Funcionario vFuncionarios[TAM];
    int tamVetor = 0;

    do {
        op = menu();
        switch (op){
            case 1:
			//ADMITIR FUNCIONÁRIO
                cadFuncionarios(vFuncionarios, &tamVetor);
                break;

            case 2:
			//PESQUISAR POR MATRICULA
				pesqMatricula(vFuncionarios, tamVetor);
                break;

            case 3:
			//SIMULAR SALÁRIO
				simularSalario(vFuncionarios, tamVetor);
                break;

            case 4:
			//AUMENTAR SALÁRIO
				aumentarSalario(vFuncionarios, tamVetor);
                break;

            case 5:
			//DESCONTAR SALÁRIO
				diminuirSalario(vFuncionarios, tamVetor);
                break;

            case 6:
			//DEMITIR FUNCIONÁRIO
				demitirFuncionario(vFuncionarios, &tamVetor);
                break;

			case 7:
			//LISTAR TODOS OS FUNCIONÁRIO CADASTRADOS
				mostrarFuncionarios(vFuncionarios, tamVetor);
                break;

            case 8:
			//SAI DO PROGRAMA
                break;
        }
		system("PAUSE");
		//SE O USUÁRIO DIGITAR 8 O PROGRAMA ENCERRA
    } while (op != 8);

    return 0;
}