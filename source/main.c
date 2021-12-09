#include <stdio.h>
#include <stdlib.h>
#include "disciplina.h"

int menu_inicial(int);
void opcao_inicial(DISCIPLINAS*, ALUNOS*, int);
int menu_disciplina(DISCIPLINA*);
void opcao_disciplina(ALUNOS*, DISCIPLINA*, int);

int main(){

    ALUNOS *semDisciplinas = criar_alunos();
    DISCIPLINAS *disciplinas = criar_disciplinas();
    int opcao;

    carregar_arquivo(semDisciplinas, disciplinas);
    system("clear");

    do{
        opcao = menu_inicial(semDisciplinas->quantidade);
        opcao_inicial(disciplinas,semDisciplinas,opcao);

    }while(opcao != 10);

    return 0;
}

int menu_inicial(int quantidade){

    int opcao;

    printf("Olá Professor,\n\n");
    printf("%d alunos não estão matriculados.\n\n",quantidade);
    printf("O que deseja fazer:\n");
    printf("1. Listar disciplinas\n");
    printf("2. Adicionar disciplina\n");
    printf("3. Remover disciplina\n");
    printf("4. Listar alunos sem disciplina\n");
    printf("5. Adicionar aluno\n");
    printf("6. Remover aluno\n");
    printf("7. Incluir aluno em disciplina\n");
    printf("8. Gerenciar disciplina\n");
    printf("9. Salvar alterações\n");
    printf("10. Sair\n\n");
    printf("Digite a opção: ");
    scanf("%d", &opcao);

    return opcao;
}

void opcao_inicial(DISCIPLINAS *disciplinas, ALUNOS *semDisciplinas, int opcao){

    int  matricula;
    char nome[50], curso[3], sigla[4];
    DISCIPLINA *disciplina;
    ALUNO *aluno;
   
    switch(opcao){
        case 1:
            system("clear");
            listar_disciplinas(disciplinas);
            system("clear");
            break;

        case 2:
            system("clear");
            printf("Adicionar disciplina\n\n");
            printf("Digite a sigla: ");
            scanf("%s",sigla);
            adicionar_disciplina(disciplinas,sigla);
            system("clear");
            break;

        case 3:
            system("clear");
            printf("Remover disciplina\n\n");
            printf("Digite a sigla: ");
            scanf("%s",sigla);
            remover_disciplina(semDisciplinas,disciplinas,sigla);
            system("clear");
            break;

        case 4:
            system("clear");
            listar_sem_disciplina(semDisciplinas);
            system("clear");
            break;

        case 5:
            system("clear");
            printf("Adicionar aluno\n\n");
            printf("Nome: ");
            scanf("%s",nome);
            printf("Matricula: ");
            scanf("%d",&matricula);
            printf("Curso: ");
            scanf("%s",curso);
            adicionar_sem_disciplina(semDisciplinas,nome,matricula,curso);
            system("clear");
            break;

        case 6:
            system("clear");
            printf("Remover aluno\n\n");
            printf("Matricula: ");
            scanf("%d",&matricula);
            remover_do_sistema(semDisciplinas,matricula);
            system("clear");
            break;

        case 7:
            system("clear");
            printf("Incluir aluno: \n");
            printf("\nMatricula: ");
            scanf("%d",&matricula);

            aluno = buscar_aluno(semDisciplinas,matricula);
            if(aluno == NULL){
                system("clear");
                printf("\nAluno inexistente ou já matriculado, impossível adicionar!\n\n");
                break;
            }

            printf("Disciplina: ");
            scanf("%s",sigla);

            disciplina = buscar_disciplina(disciplinas,sigla);
            if(disciplina == NULL){
                system("clear");
                printf("\nDisciplina inexistente, impossível adicionar!\n\n");
                break;
            }
            incluir_aluno(semDisciplinas,aluno,disciplina);
            system("clear");
            break;

        case 8:
            system("clear");
            printf("Gerenciar disciplina: ");
            scanf("%s",sigla);

            disciplina = buscar_disciplina(disciplinas,sigla);
            if(disciplina == NULL){
                system("clear"); 
                printf("\nDisciplina não encontrada!\n\n");
                printf("Pressione enter para voltar.");
                getchar();
                getchar();
                system("clear");
                break;
            }
            system("clear");
            do{
                opcao = menu_disciplina(disciplina);
                opcao_disciplina(semDisciplinas,disciplina,opcao);
            } while(opcao != 6);
            break;

        case 9:
            system("clear");
            salvar_arquivo(semDisciplinas,disciplinas);
            system("clear");
            break;
            
        case 10:
            exit(1);
            break;

        default:
            system("clear");
            printf("\nOpção inválida!\n\n");
            break;
    }
}

int menu_disciplina(DISCIPLINA *disciplina){

    int opcao;

    printf("Gerenciando disciplina %s\n\n",disciplina->nome);
    printf("Quantidade de alunos: %d\n\n",disciplina->alunos->quantidade);
    printf("Opções:\n");
    printf("1. Listar alunos\n");
    printf("2. Remover aluno de disciplina\n");
    printf("3. Atribuir nota a aluno\n");
    printf("4. Atribuir faltas a aluno\n");
    printf("5. Processar turma\n");
    printf("6. Voltar\n\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    return opcao;
}

void opcao_disciplina(ALUNOS *alunos, DISCIPLINA *disciplina, int opcao){
    
    int matricula;
    float nota, faltas;
    ALUNO *aluno;
 
    switch(opcao){

        case 1:
            system("clear");
            if(disciplina->alunos->primeiro == NULL){
                printf("\nDisciplina sem alunos!\n");
                printf("\nPressione enter para voltar.");
                getchar();
                getchar();
                system("clear");
                break;
            }
            ordenar(disciplina->alunos);
            listar_alunos(disciplina);
            system("clear");
            break;

        case 2:
            system("clear");
            printf("Digite a matricula do aluno a ser removido de %s\n\n",disciplina->nome);
            printf("Matricula: ");
            scanf("%d",&matricula);
            remover_da_disciplina(alunos,disciplina,matricula);
            system("clear");
            break;

        case 3:
            system("clear");
            printf("Atribuir nota a aluno de %s\n\n",disciplina->nome);
            printf("Matricula: ");
            scanf("%d",&matricula);

            aluno = buscar_aluno(disciplina->alunos,matricula);

            if(aluno == NULL){
                system("clear"); 
                printf("\nAluno não encontrado!\n\n");
                printf("Pressione enter para voltar.");
                getchar();
                getchar();
                system("clear");
                break;
            }
            printf("Nota: ");
            scanf("%f",&nota);
            atribuir_nota(aluno,nota);
            system("clear");
            break;

        case 4:
            system("clear");
            printf("Atribuir faltas a aluno de %s\n\n",disciplina->nome);
            printf("Matricula: ");
            scanf("%d",&matricula);

            aluno = buscar_aluno(disciplina->alunos,matricula);

            if(aluno == NULL){
                system("clear"); 
                printf("\nAluno não encontrado!\n\n");
                printf("Pressione enter para voltar.");
                getchar();
                getchar();
                system("clear");
                break;
            }
            printf("Faltas: ");
            scanf("%f",&faltas);
            atribuir_faltas(aluno,faltas);
            system("clear");
            break;

        case 5:
            system("clear");
            if(disciplina->alunos->primeiro == NULL){
                printf("\nDisciplina sem alunos, impossível processar!\n");
                printf("\nPressione enter para voltar.");
                getchar();
                getchar();
                system("clear");
                break;
            }
            calcular_mencao(disciplina->alunos);
            processar_turma(disciplina);
            system("clear");
            break;

        case 6:
            system("clear");
            break;

        default:
            system("clear");
            printf("\nOpção inválida!\n\n");
            break;
    }
}







