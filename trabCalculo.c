//KAROLINY ANDRISEN DO PRADO NEPPEL E SARA MACIEL MARTINS - V01//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define TAM 100

//DEFINI��O DAS STRUCTS (REGISTROS)
//PESSOA
struct Pessoas {
    char vNome[TAM];
    int telefone;
    char cpf[TAM];
};
typedef struct Pessoas Pessoa;

//FUNCION�RIO
struct Funcionarios {
    int matricula;
    float salario;
	Pessoa p;
};
typedef struct Funcionarios Funcionario;

//LENDO O NOME
void lerNome(Funcionario *f) {
    int t;
    printf("\nInsira o nome do funcion�rio: ");
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
        printf("\nInv�lido! Insira o telefone: ");
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
	//PROCURAR ITEM POR ITEM NO VETOR VFuncionarios SE H� A MATRICULA DESEJADA
	for (i = 0; i < qtde; i++) {
		//SE A MATRICULA DESEJADA EXISTIR
 		if (vetor[i].matricula == pesq) {
		//RETORNA A POSI��O NO VETOR QUE ELA SE ENCONTRA
		return i;
 		}
	}
	// SE N�O ENTRAR RETORNA -1
	return -1;
}

//LENDO A MATRPICULA
void lerMatricula(Funcionario *f, Funcionario *vFuncionarios, int tamVFunc) {
    int res;
    printf("\nInsira a matr�cula: ");
    scanf("%d", &f->matricula);
    getchar();

	// ANTES DE CADASTRAR VERIFICA SE A MATRICULA JA EXISTE
    res = pesquisarMat(vFuncionarios, tamVFunc, f->matricula);
    while (res != -1) {
		//SE JA EXISTIR PRINTA ESSA MENSAGEM E PEDE PARA INSERIR OUTRA AT� QUE
		//ELA N�O EXISTA
        printf("Matr�cula j� cadastrada! Insira outra matr�cula: ");
        scanf("%d", &f->matricula);
        getchar();
        res = pesquisarMat(vFuncionarios, tamVFunc, f->matricula);
    }
}

//LENDO SAL�RIO
void lerSalario (Funcionario *f){
 	printf("\nInsira o valor fixo do sal�rio: R$ ");
    scanf("%f", &f->salario);
	getchar();

	while (f->salario < 0){
		printf("Inv�lido! Insira um valor maior que zero: R$");
    	scanf("%f", &f->salario);
		getchar();
	}
}

//FUN��O PARA JUNTAR TODAS AS LEITURAS
void inserirFuncionario(Funcionario *f, Funcionario *vFuncionarios, int tamVetor) {
	lerMatricula(f, vFuncionarios, tamVetor);
	lerNome(f);
	lerTelefone(f);
	lerCPF(f);
	lerSalario(f);
}

//FUN��O PARA CADASTRAR NO VETOR
void cadFuncionarios(Funcionario *vFuncionarios, int *tamVetor) {
    char continuar = 'S';
    do {
		//AQUI INSERE NO VETOR QUANDO A OP��O DE ADMITIR FUNCION�RIO � ATIVADA
        inserirFuncionario(&vFuncionarios[*tamVetor], vFuncionarios, *tamVetor);
		//ADICIONA +1 NO TAMVETOR
        (*tamVetor)++;

		//PERGUNTA SE QUER ADICIONAR MAIS OU PARAR
        printf("\nDeseja adicionar mais funcion�rios? (S/N): ");
        scanf(" %c", &continuar);
        getchar();
		//SE DIGITAR QUALQUER LETRA AL�M DE "S" PARA DE CADASTRAR
    } while (toupper(continuar) == 'S');
}

//FUN��O DA OP��O DE PESQUISAR POR MATRICULA
void pesqMatricula(Funcionario *vFuncionarios, int tamVFunc) {
	// SE N�O TIVER NENHUM FUNCIONARIO CADASTRADO N�O DEIXA PESQUISAR
    if (tamVFunc == 0) {
        printf("\nNenhum funcion�rio cadastrado!\n");
        return;
    }

    int res, pesq;
    printf("\nInsira a matr�cula do funcion�rio a ser pesquisada: ");
    scanf("%d", &pesq);

	// PESQUISANDO
    res = pesquisarMat(vFuncionarios, tamVFunc, pesq);

    if (res == -1) {
        printf("\nN�o existe ningu�m cadastrado com essa matr�cula!\n");
    } else {
		//PRINTA O FUNCION�RIO DA MATRICULA CORRESPONDENTE CASO ACHE
        printf("\n\t|Nome: %s\n\t|Telefone: +55 (27) %d\n\t|CPF: %s\n", vFuncionarios[res].p.vNome, vFuncionarios[res].p.telefone, vFuncionarios[res].p.cpf);
        printf("\t|Matr�cula: %d\n\t|Sal�rio: R$ %.2f\n", vFuncionarios[res].matricula, vFuncionarios[res].salario);
    }
}

//FUN��O PARA AUMENTAR SAL�RIO
void aumentarSalario(Funcionario *vFuncionarios, int tamVFunc) {
	int res, matricula;
	float p;
	//PEDE A MATRICULA DO FUNCION�RIO QUE TER� O SAL�RIO AUMENTADO
	printf("\nInsira a matr�cula do funcion�rio: ");
	scanf("%d", &matricula);

	//PESQUISA SE EXISTE
	res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	while (res == -1){
		printf("\nN�o existe nenhum funcion�rio cadastrado com essa matr�cula!\n");
		printf("\nInsira a matr�cula do funcion�rio: ");
		scanf("%d", &matricula);

		res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	}

	if (res != -1) {
		//AQUI INSERE A PORCENTAGEM
		printf("\nInsira o valor do aumento em porcentagem: ");
		scanf("%f", &p);

		while (p < 0){
			printf("\nInv�lido! Insira o valor do aumento em porcentagem: ");
			scanf("%f", &p);
		}
		//APLICA��O DA FUN��O AFIM SENDO "vFuncionarios[res].salario" O VALO "FIXO" MAIS "(vFuncionarios[res].salario * (p / 100))"
		//QUE � A PARTE V�RI�VEL, NO CASO O AUMENTO
		vFuncionarios[res].salario = vFuncionarios[res].salario + (vFuncionarios[res].salario * (p / 100));
		printf("\nSal�rio do funcion�rio de matr�cula %d atualizado!\n", matricula);
	}
	
}

//FUN��O PARA DIMINUIR/DESCONTAR SAL�RIO
void diminuirSalario(Funcionario *vFuncionarios, int tamVFunc) {
	int res, matricula;
	int d, v;
	//PEDE A MATRICULA DO FUNCION�RIO QUE TER� O SAL�RIO DESCONTADO
	printf("\nInsira a matr�cula do funcion�rio: ");
	scanf("%d", &matricula);

	//PESQUISA SE EXISTE
	res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	while (res == -1){
		printf("\nN�o existe nenhum funcion�rio cadastrado com essa matr�cula!\n");
		printf("\nInsira a matr�cula do funcion�rio: ");
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
			printf("\nInv�lido! Insira a quantidade de dias a serem descontados: ");
			scanf("%d", &d);
		}
		//APLICA��O DA FUN��O AFIM SENDO "vFuncionarios[res].salario" O VALO "FIXO" MENOS OS DIAS * O VALOR DO DIA
		//QUE � A PARTE V�RI�VEL, NO CASO O DESCONTO
		vFuncionarios[res].salario = vFuncionarios[res].salario - (d * v);
		printf("\nSal�rio do funcion�rio de matr�cula %d atualizado!\n", matricula);
	}
	
}

//REMOVER FUNCION�RIO DO VETOR
void removerFunc (Funcionario *vetor, int *qtde, int pos) {
	int i;
	//EM C N�O CONSEGUIMOS PAGAR NADA DE UM VETOR, APENAS SOBRESCREVER
	for (i = pos; i < *qtde- 1; i++) {
		vetor[i] = vetor[i+1];
	}
	//TIRA 1 J� QUE EXCLUIU
	(*qtde)--;
}

//FUN��O PARA DEMITIR O FUNCION�RIO
void demitirFuncionario(Funcionario *vFuncionarios, int *tamVFunc) {
	int res, mat;
	//PEDE A MATR�CULA DO FUNCION�RIO QUE VAI SER DEMITIDO
	printf("\nInsira a matr�cula do funcion�rio a ser exclu�do: ");
	scanf("%d", &mat);

	//PESQUISA SE EXISTE
	res = pesquisarMat(vFuncionarios, *tamVFunc, mat);
	while (res == -1){
		printf("\nN�o existe funcion�rio cadastrado com essa matr�cula!\n");
		printf("\nInsira a matr�cula do funcion�rio a ser exclu�do: ");
		scanf("%d", &mat);

		res = pesquisarMat(vFuncionarios, *tamVFunc, mat);
	}

	if (res != -1) {
		//QUANDO RETORNAR A POSI��O DO VETOR, ELE USA A FUN��O DE CIMA
		//PARA DELETAR DO VETOR
		removerFunc(vFuncionarios, tamVFunc, res);
		printf("\nFuncion�rio de matr�cula %d removido com sucesso!\n", mat);
	}
	
}

//LISTA TODOS OS FUNCION�RIOS CADASTRADOS
void mostrarFuncionarios(Funcionario *vFuncionarios, int tamVFunc) {
	int i;

	//PASSA INDICE POR INDICE DO vFuncionarios E PRINTA CADA
	for (i = 0; i < tamVFunc; i++){
	printf("\n\t|Funcion�rio %d|\n", i+1);
	printf("\n\t|Nome: %s\n\t|Telefone: +55 (27) %d\n\t|CPF: %s\n", vFuncionarios[i].p.vNome, vFuncionarios[i].p.telefone, vFuncionarios[i].p.cpf);
	printf("\t|Matr�cula: %d\n\t|Sal�rio: R$ %.2f\n\n", vFuncionarios[i].matricula, vFuncionarios[i].salario);
	}
}

//FUN��O PARA SIMULAR SAL�RIO
void simularSalario(Funcionario *vFuncionarios, int tamVFunc) {
	int res, matricula, d;
	float comissao, simSalario;
	//PEDE A MATRICULA DO FUNCION�RIO QUE VAI TER O SAL�RIO SIMULADO
	printf("\nInsira a matr�cula do funcion�rio: ");
	scanf("%d", &matricula);

	//PESQUISA SE EXISTE
	res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	while (res == -1){
		printf("\nN�o existe nenhum funcion�rio cadastrado com essa matr�cula!\n");
		printf("\nInsira a matr�cula do funcion�rio: ");
		scanf("%d", &matricula);

		res = pesquisarMat(vFuncionarios, tamVFunc, matricula);
	}

	if (res != -1) {
		//PEDE O TOTAL DE VENDAS
		printf("\nInsira o total de vendas: ");
		scanf("%d", &d);
		//PEDE O VALOR DA COMISS�O
		printf("\nInsira o valor da comiss�o (em reais): ");
		scanf("%f", &comissao);

		while (d < 0){
			printf("\nInv�lido! Insira o valor do aumento em porcentagem: ");
			scanf("%d", &d);
		}

		//APLICA��O DA FUN��O AFIM SENDO "vFuncionarios[res].salario" O VALO "FIXO" MAIS "(comissao * d)"
		//QUE � A PARTE V�RI�VEL
		simSalario = vFuncionarios[res].salario + (comissao * d);
		printf("\nSal�rio do funcion�rio de matr�cula %d atualizado para %.2f!\n", matricula, simSalario);
	}
	
}

//MENU PARA MOSTRAR AS OP��ES
int menu() {
	int op;
    printf("\t__________________________________________\n");	
    printf("\n\tFOLHA DE PAGAMENTO\n");
    printf("\t__________________________________________\n");
	printf("\t| 1 | Admitir Funcion�rio\n");
	printf("\t| 2 | Pesquisar por Matr�cula\n");
	printf("\t| 3 | Simular Pr�ximo Sal�rio\n");
	printf("\t| 4 | Aumentar Sal�rio do Funcion�rio\n");
    printf("\t| 5 | Descontar Sal�rio do Funcion�rio\n");
	printf("\t| 6 | Demitir Funcion�rio\n");
	printf("\t| 7 | Mostrar Funcion�rios cadastrados\n");
	printf("\t| 8 | Sair\n");
    printf("\t__________________________________________\n");	do {
		printf("\n\tEscolha sua op��o: ");
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
			//ADMITIR FUNCION�RIO
                cadFuncionarios(vFuncionarios, &tamVetor);
                break;

            case 2:
			//PESQUISAR POR MATRICULA
				pesqMatricula(vFuncionarios, tamVetor);
                break;

            case 3:
			//SIMULAR SAL�RIO
				simularSalario(vFuncionarios, tamVetor);
                break;

            case 4:
			//AUMENTAR SAL�RIO
				aumentarSalario(vFuncionarios, tamVetor);
                break;

            case 5:
			//DESCONTAR SAL�RIO
				diminuirSalario(vFuncionarios, tamVetor);
                break;

            case 6:
			//DEMITIR FUNCION�RIO
				demitirFuncionario(vFuncionarios, &tamVetor);
                break;

			case 7:
			//LISTAR TODOS OS FUNCION�RIO CADASTRADOS
				mostrarFuncionarios(vFuncionarios, tamVetor);
                break;

            case 8:
			//SAI DO PROGRAMA
                break;
        }
		system("PAUSE");
		//SE O USU�RIO DIGITAR 8 O PROGRAMA ENCERRA
    } while (op != 8);

    return 0;
}