/* Lista Aninhada 2 
   26-03-2025
   Tarefa Avaliativa
   
   Trabalho em Dupla:
   
   (1)KAROLINY ANDRISEN DO PRADO NEPPEL
   (2)SARA MACIEL MARTINS
   
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef char string[40];

typedef struct tipoPreRequisito {
    struct tipoDisciplina *preRequisito;
    struct tipoPreRequisito *prox;
} TPreRequisito;

typedef struct tipoDisciplina {
    string nome;
    int cargaHoraria;
    struct tipoDisciplina *prox; 
    TPreRequisito *preRequisitos;	
} TDisciplina;

typedef struct tipoGrade {
    TDisciplina *disciplina;
    int periodo;
    struct tipoGrade *prox; 
} TGrade;

typedef struct tipoCurso {
    string nome;
    struct tipoCurso *ante; 
    struct tipoCurso *prox; 
    TGrade *gradeCurricular;
} TCurso;

typedef struct tipoLista {
	TCurso *cursos;
	TDisciplina *disciplinas;
}TLista;

TLista lista;

void inicializa(TLista *L);
int menu();
int pesquisarDisciplina(TLista *L, int numUsuarios, char *pesq);
int inserirDisciplina(TLista *L);
void inserirCurso(TLista *L);
void registrarPreRequisito(TLista *L);
void registrarGradeCurricular(TLista *L) ;
void imprimeListaDisciplinas(TLista L);
void imprimeListaCursos(TLista L);
void excluirDisciplina(TLista *L);
void excluirCurso(TLista *L);
void excluirPreRequisito(TLista *L);
void excluirGradeCurricular (TLista *L);
void listarPreRequisitos(TLista L);
void imprimeListaGrade(TLista L);

int main(){
	setlocale(LC_ALL, "Portuguese");
    int opcao;
    
    inicializa(&lista);

    do {
        opcao = menu(); 

        switch (opcao) {
            case 1:
                inserirDisciplina(&lista);
                break;
            case 2:
            	excluirDisciplina(&lista);
            	break;
            case 3:
            	inserirCurso(&lista);
            	break;
            case 4:
            	excluirCurso(&lista);
            	break;
            case 5:
				registrarPreRequisito(&lista);
            	break;
            case 6:
            	excluirPreRequisito(&lista);
            	break;
            case 7:
            	registrarGradeCurricular(&lista);
            	break;
            case 8:
            	excluirGradeCurricular(&lista);
            	break;
            case 9:
            	imprimeListaDisciplinas(lista);
            	break;
            case 10:
            	imprimeListaCursos(lista);
            	break;
            case 11:
            	listarPreRequisitos(lista);
            	break;
            case 12:
            	imprimeListaGrade(lista);
            	break;
        }
    } while (opcao != 0);
}
//===| Funções |==================================================
void inicializa(TLista *L){
	L->cursos = NULL;
	L->disciplinas = NULL;	
}
//================================================================
int menu(){
	int opcao;
	system("CLS");
	printf("\n\n\n\t\t=======| MENU |=======\n\n");
	printf("\t0 - SAIR (Encerrar Aplicacao).\n\n");
	printf("\t1 - Inserir DISCIPLINAS.\n");
	printf("\t2 - Excluir DISCIPLINAS.\n\n"); 
	printf("\t3 - Inserir CURSOS.\n");
	printf("\t4 - Excluir CURSOS.\n"); 
	printf("\t5 - Registrar PRE-REQUISITOS para DISCIPLINA.\n");
	printf("\t6 - Excluir PRE-REQUISITO de DISCIPLINA.\n\n"); 
	printf("\t7 - Registrar GRADE CURRICULAR para CURSO.\n");
	printf("\t8 - Excluir item da GRADE CURRICULAR de CURSO.\n\n"); 
	printf("\t9 - Listar DISCIPLINAS.\n");
	printf("\t10- Listar CURSOS.\n");
	printf("\t11- Listar PRE REQUISITOS de DISCIPLINA especifica.\n");
	printf("\t12- Listar GRADE CURRICULAR de CURSO especifico.\n\n"); 
	
	printf("\t\tInforme a OPCAO desejada: ");
	scanf("%d", &opcao);
	
	if((opcao < 0) || (opcao > 12)){
		printf("\n\n\n\tERRO: OPCAO invalida!\n\tTente Novamente\n\n");
		system("PAUSE");
	}//if
	return opcao;
}
//================================================================
int inserirDisciplina(TLista *L){
	char continuar = 's';
	int cont = 0;
	
	printf("\n\n\t\t=====| CADASTRO DE DISCIPLINAS |=====\n\n");
	do {
		TDisciplina *novo, *atual;
		novo = (TDisciplina *)malloc(sizeof(TDisciplina));
		
		novo->prox = NULL;
	    
		printf("\n\tNome da disciplina: ");
		fflush(stdin);
		gets(novo->nome);
		
		printf("\n\tCarga horária: ");
		scanf("%d", &novo->cargaHoraria);
	    getchar();
	    
		
		if(L->disciplinas == NULL){
			L->disciplinas = novo;
		} else {
	    	atual = L->disciplinas;
	    	while(atual->prox != NULL){
	    		atual = atual->prox;
	    	}
			atual->prox = novo;
		}
		
		printf("\n\tDISCIPLINA CADASTRADA COM SUCESSO!\n");
		cont++;
		printf("\n\tDeseja continuar cadastrando disciplinas?(S/N): ");
		scanf("%c", &continuar);
	} while (continuar == 's' || continuar == 'S'); 
	system("PAUSE");
	return cont;
}
//================================================================
void inserirCurso(TLista *L){
	char continuar = 's';
	
	printf("\n\n\t\t=====| CADASTRO DE CURSOS |=====\n\n");
	
	do {
		TCurso *novo, *atual;
		novo = (TCurso *)malloc(sizeof(TCurso));
		novo->gradeCurricular = NULL; 
		
		novo->prox = NULL;
	    
		printf("\n\tNome do curso: ");
		fflush(stdin);
		gets(novo->nome);
	    
		
		if(L->cursos == NULL){
			L->cursos = novo;
		} else {
	    	atual = L->cursos;
	    	while(atual->prox != NULL){
	    		atual = atual->prox;
	    	}
			atual->prox = novo;
		}
		
		printf("\n\tCURSO CADASTRADO COM SUCESSO!");
		printf("\n\tDeseja continuar cadastrando cursos?(S/N): ");
		scanf("%c", &continuar);
	} while (continuar == 's' || continuar == 'S'); 
	system("PAUSE");
}
//================================================================
void imprimeListaDisciplinas(TLista L) {
    TDisciplina *atual = L.disciplinas;
    int cont = 0;

    printf("\n\n\t\t=======| LISTA DE DISCIPLINAS |=======\n\n");

    if (atual == NULL) {
        printf("\tNenhuma disciplina cadastrada.\n\n");
        return;
    }

    while (atual != NULL) {
        printf("\t(%d) - %s | Carga Horária: %d horas\n", ++cont, atual->nome, atual->cargaHoraria);
        atual = atual->prox;
    }

    printf("\n\n");
    system("PAUSE");
}
//================================================================
void imprimeListaCursos(TLista L) {
    TCurso *atual = L.cursos;
    int cont = 0;

    printf("\n\n\t\t=======| LISTA DE CURSOS |=======\n\n");

    if (atual == NULL) {
        printf("\tNenhum curso cadastrado!");
        return;
    }

    while (atual != NULL) {
        printf("\t(%d) - %s\n", ++cont, atual->nome);
        atual = atual->prox;
    }

    printf("\n\n");
    system("PAUSE");
}
//================================================================
void registrarPreRequisito(TLista *L) {
    char continuar = 's';
    char nomeDisciplina[40], nomePreReq[40];

    printf("\n\n\t\t=======| CADASTRAR PRÉ-REQUISITOS PARA DISCIPLINA |=======\n\n");

    do {
    	TPreRequisito *novo;
    	novo = (TPreRequisito *)malloc(sizeof(TPreRequisito));
    	novo->prox = NULL;
        TDisciplina *disciplinaSelecionada = NULL;
        TDisciplina *preRequisitoSelecionado = NULL;
		
		printf("\n\tDigite o nome da disciplina para a qual deseja registrar pré-requisitos: ");
        fflush(stdin);
        gets(nomeDisciplina);
        

        disciplinaSelecionada = L->disciplinas;
        while (disciplinaSelecionada != NULL && strcmp(disciplinaSelecionada->nome, nomeDisciplina) != 0) {
            disciplinaSelecionada = disciplinaSelecionada->prox;
        }

        if (disciplinaSelecionada == NULL) {
            printf("\n\tDisciplina não encontrada!\n");
            continue; 
        }

        printf("\n\tDigite o nome do pré-requisito: ");
        fflush(stdin);
        gets(nomePreReq);

        preRequisitoSelecionado = L->disciplinas;
        while (preRequisitoSelecionado != NULL && strcmp(preRequisitoSelecionado->nome, nomePreReq) != 0) {
            preRequisitoSelecionado = preRequisitoSelecionado->prox;
        }

        if (preRequisitoSelecionado == NULL) {
            printf("\n\tPré-requisito não encontrado!\n");
            continue;
        }
        
        novo->preRequisito = preRequisitoSelecionado;
		
		if (disciplinaSelecionada->preRequisitos == NULL) {
    		disciplinaSelecionada->preRequisitos = novo;
		} else {
    		TPreRequisito *atual = disciplinaSelecionada->preRequisitos;
    		while (atual->prox != NULL) {
        		atual = atual->prox;
    		}
    	atual->prox = novo;
		}

        printf("\n\tPré-requisito cadastrado com sucesso!\n");

        printf("\n\tDeseja continuar cadastrando? (s/n): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n');
    } while (continuar == 's' || continuar == 'S');
}
//================================================================
void registrarGradeCurricular(TLista *L) {
    char continuar = 's';
    char nomeCurso[40], nomeDisciplina[40];
    int periodo;

    printf("\n\n\t\t=======| CADASTRAR GRADE CURRICULAR PARA CURSO |=======\n\n");

    do {
        TCurso *cursoSelecionado = NULL;
        TDisciplina *disciplinaSelecionada = NULL;

        printf("\n\tDigite o nome do curso para cadastrar a grade curricular: ");
        fflush(stdin);
        gets(nomeCurso);

        cursoSelecionado = L->cursos;
        while (cursoSelecionado != NULL && strcmp(cursoSelecionado->nome, nomeCurso) != 0) {
            cursoSelecionado = cursoSelecionado->prox;
        }

        if (cursoSelecionado == NULL) {
            printf("\n\tCurso não encontrado!\n");
            continue;
        }

        do {
            printf("\n\tDigite o nome da matéria a ser adicionada na grade (Para sair, digite '0'): ");
            fflush(stdin);
            gets(nomeDisciplina);

            if (strcmp(nomeDisciplina, "0") == 0) {
                break;
            }

            disciplinaSelecionada = L->disciplinas;
            while (disciplinaSelecionada != NULL && strcmp(disciplinaSelecionada->nome, nomeDisciplina) != 0) {
                disciplinaSelecionada = disciplinaSelecionada->prox;
            }

            if (disciplinaSelecionada == NULL) {
                printf("\n\tDisciplina não encontrada!\n");
                continue;
            }

            printf("\tDigite o período da disciplina: ");
            scanf("%d", &periodo);
            while (getchar() != '\n'); 

            TGrade *novo = (TGrade *)malloc(sizeof(TGrade));
            novo->disciplina = disciplinaSelecionada;
            novo->periodo = periodo;
            novo->prox = NULL;

            if (cursoSelecionado->gradeCurricular == NULL) {
                cursoSelecionado->gradeCurricular = novo;
            } else {
                TGrade *atual = cursoSelecionado->gradeCurricular;
                while (atual->prox != NULL) {
                    atual = atual->prox;
                }
                atual->prox = novo;
            }

            printf("\n\tDisciplina adicionada à grade com sucesso!\n");

        } while (1);

        printf("\n\tDeseja continuar cadastrando para outro curso? (s/n): ");
        scanf(" %c", &continuar);
        while (getchar() != '\n');

    } while (continuar == 's' || continuar == 'S');
}
//================================================================
void excluirDisciplina (TLista *L){
	char nome[20];
	
	printf("\n\n\t\t=======| EXCLUIR DISCIPLINA |=======\n\n");
	
	printf("\n\tInsira o nome da disciplina que você quer excluir: ");
	scanf(" %19[^\n]", nome);
	TDisciplina *atual = L->disciplinas;
    TDisciplina *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("\n\tDisciplina não encontrada!\n");
        return;
    }

    if (anterior == NULL) {
        L->disciplinas = atual->prox; 
    } else {
        anterior->prox = atual->prox; 
    }

    free(atual);
    printf("\n\tDisciplina excluída com sucesso!\n");
	
	printf("\n\n");
    system("PAUSE");
	
}
//================================================================
void excluirCurso (TLista *L) {
	TCurso *atualC = L->cursos;
	TCurso *anterior;
	char cursoExclusao[40];
	
	printf("\n\n\n\t\t=====| EXCLUIR CURSO |=====\n\n");
	printf("\tInsira o nome do curso a ser excluído: ");
	fflush(stdin);
	gets(cursoExclusao);
	
	if(atualC == NULL){
		printf("\n\n\tNenhuma curso cadastrado!\n\n");
		system("PAUSE");
	} else {
		while(atualC != NULL){
			if(strcmp(atualC->nome, cursoExclusao) == 0){
				if(atualC == L->cursos){
					L->cursos = atualC->prox;
				} else {
					anterior = L->cursos;
					while(anterior->prox != atualC){
						anterior = anterior->prox;	
					}
					anterior->prox = atualC->prox;
				}
				free(atualC);
				printf("\n\tCurso excluído com sucesso!\n\n");
				system("PAUSE");
				break;
			}
			atualC = atualC->prox;
		}
	}
}
//================================================================
void excluirPreRequisito(TLista *L) {
    char nomeDisc[20], nomePReq[20];
    
    printf("\n\n\t\t=======| EXCLUIR PRÉ-REQUISITO ESPECÍFICO |=======\n\n");
    
    printf("\n\tInsira o nome da disciplina: ");
    scanf(" %19[^\n]", nomeDisc);
    
    TDisciplina *disciplinaSelec = L->disciplinas;
    
    while (disciplinaSelec != NULL && strcmp(disciplinaSelec->nome, nomeDisc) != 0) {
        disciplinaSelec = disciplinaSelec->prox;
    }

    if (disciplinaSelec == NULL) {
        printf("\n\tDisciplina não encontrada!\n");
        return;
    }
    
    printf("\n\tInsira o nome do pré-requisito que você quer excluir: ");
    scanf(" %19[^\n]", nomePReq);
    
    TPreRequisito *atual = disciplinaSelec->preRequisitos;
    TPreRequisito *anterior = NULL;
    
    while (atual != NULL && strcmp(atual->preRequisito->nome, nomePReq) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("\n\tPré-requisito não encontrado!\n");
        return;
    }
    
    if (anterior == NULL) {
        disciplinaSelec->preRequisitos = atual->prox; 
    } else {
        anterior->prox = atual->prox; 
    }

    free(atual);
    printf("\n\tPré-requisito excluído com sucesso!\n");
    printf("\n\n");
    system("PAUSE");
}
//================================================================
void excluirGradeCurricular (TLista *L){
	char nomeC[20], nomeD[20];
	
	printf("\n\n\t\t=======| EXCLUIR ITEM DA GRADE CURRICULAR |=======\n\n");
	
	printf("\n\tInsira o nome do curso: ");
    scanf(" %19[^\n]", nomeC);
    
    TCurso *cursoSelec = L->cursos;
    while (cursoSelec != NULL && strcmp(cursoSelec->nome, nomeC) != 0) {
        cursoSelec = cursoSelec->prox;
    }
    
	if (cursoSelec == NULL) {
        printf("\n\tCurso não encontrado!\n");
        return;
    }
	printf("\n\tInsira o nome da disciplina que deseja excluir da grade curricular: ");
	scanf(" %19[^\n]", nomeD);
	
	TGrade *atual = cursoSelec->gradeCurricular;
    TGrade *anterior = NULL;
    
    while (atual != NULL && strcmp(atual->disciplina->nome, nomeD) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    
    if (atual == NULL) {
        printf("\n\tDisciplina não encontrada!\n");
        return;
    }
     if (anterior == NULL) {
        cursoSelec->gradeCurricular = atual->prox; 
    } else {
        anterior->prox = atual->prox; 
    }

    free(atual);
    printf("\n\tDisciplina excluída da grade curricular com sucesso!\n");
    printf("\n\n");
    system("PAUSE");
}
//================================================================
void listarPreRequisitos(TLista L) {
    TDisciplina *disciplinaProcurada = NULL;
    TPreRequisito *preReq = NULL;
    char nomeDisciplina[40];

    printf("\n\n\t\t=======| LISTA DE PRÉ-REQUISITOS POR DISCIPLINA |=======\n\n");

    if (L.disciplinas == NULL) {
        printf("\tNenhuma disciplina cadastrada!\n");
        return;
    }

    printf("\n\tDigite o nome da disciplina: ");
    fflush(stdin);
    gets(nomeDisciplina);


    disciplinaProcurada = L.disciplinas;
    while (disciplinaProcurada != NULL && strcmp(disciplinaProcurada->nome, nomeDisciplina) != 0) {
        disciplinaProcurada = disciplinaProcurada->prox;
    }

    if (disciplinaProcurada == NULL) {
        printf("\n\tDisciplina não encontrada!\n");
    } else {
        printf("\n\tDisciplina: %s\n", disciplinaProcurada->nome);
        printf("\tPré-Requisitos:\n");

        preReq = disciplinaProcurada->preRequisitos;
		if (preReq == NULL) {
    		printf("\t(Nenhum pré-requisito cadastrado)\n");
		} else {
    	while (preReq != NULL) {
        	if (preReq->preRequisito != NULL) {
            	printf("\t- %s\n", preReq->preRequisito->nome);
        } else {
            printf("\t- (Pré-requisito inválido ou não definido)\n");
        }
        preReq = preReq->prox;
    }
}	

    printf("\n\n");
    system("PAUSE");
}
}
//================================================================
void imprimeListaGrade(TLista L) {
    char nomeCurso[40];
    TCurso *cursoSelecionado = NULL;
    TGrade *gradeAtual;

    printf("\n\n\t\t=======| LISTAR GRADE CURRICULAR DE CURSO |=======\n\n");

    printf("\n\tDigite o nome do curso: ");
    fflush(stdin);
    gets(nomeCurso);

    cursoSelecionado = L.cursos;

    while (cursoSelecionado != NULL && strcmp(cursoSelecionado->nome, nomeCurso) != 0) {
        cursoSelecionado = cursoSelecionado->prox;
    }

    if (cursoSelecionado == NULL) {
        printf("\n\tCurso não encontrado!\n");
        system("PAUSE");
        return;
    }

    printf("\n\tGrade curricular do curso: %s\n", cursoSelecionado->nome);
    if (cursoSelecionado->gradeCurricular == NULL) {
        printf("\tNenhuma disciplina cadastrada na grade curricular.\n");
        system("PAUSE");
        return;
    }

    gradeAtual = cursoSelecionado->gradeCurricular;
    while (gradeAtual != NULL) {
        printf("\t- %s | Carga Horária: %d horas | Período: %d\n", gradeAtual->disciplina->nome, gradeAtual->disciplina->cargaHoraria, gradeAtual->periodo);
        gradeAtual = gradeAtual->prox;
    }

    printf("\n");
    system("PAUSE");
}
//================================================================
