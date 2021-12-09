#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disciplina.h"


CURSOS *criar_cursos(){

    CURSOS *cursos = (CURSOS*) malloc(sizeof(CURSOS));
    cursos->primeiro = NULL;
    cursos->quantidade = 0;
    cursos->dados.matriculados = 0;
    cursos->dados.aprovados = 0;
    cursos->dados.reprovados = 0;
    for(int i = 0 ; i < 6; i++)
        cursos->dados.mencoes[i] = 0;

    return cursos;
}

CURSO *adicionar_curso(CURSOS *cursos, char nome[3]){

    CURSO *tmp = cursos->primeiro;
    CURSO *novo = (CURSO*) malloc(sizeof(CURSO));
   
    strcpy(novo->nome,nome);
    novo->dados.matriculados = 0;
    novo->dados.aprovados = 0;
    novo->dados.reprovados = 0;
    novo->prox = NULL;
    for(int i = 0 ; i < 6; i++)
        novo->dados.mencoes[i] = 0;
    
    if(tmp == NULL)
        cursos->primeiro = novo;
    else{
        while(tmp->prox != NULL)
            tmp = tmp->prox;

        tmp->prox = novo;
    }
    cursos->quantidade++;

    return novo;
}

CURSO *buscar_curso(CURSOS *cursos, char nome[3]){

    CURSO *curso = cursos->primeiro;

    while(curso != NULL){
        if(!strcmp(curso->nome,nome))
            return curso;
        curso = curso->prox;
    }
    return curso;
}

void remover_da_disciplina(ALUNOS *alunos, DISCIPLINA *materia, int matricula){

    ALUNO *aux = NULL, *anterior = NULL, *aluno = materia->alunos->primeiro;

    while(aluno != NULL){
        if(aluno->dados.matricula == matricula)
            break;
        anterior = aluno;
        aluno = aluno->prox;
    }

    if(aluno == NULL){
        system("clear"); 
        printf("\nAluno não encontrado!\n\n");
        printf("Pressione enter para voltar.");
        getchar();
        getchar();
        return ;
    }
   
    adicionar_sem_disciplina(alunos,aluno->dados.nome,aluno->dados.matricula,aluno->dados.curso);
   
    if(aluno == materia->alunos->primeiro){
            
        aux = materia->alunos->primeiro;
        materia->alunos->primeiro = materia->alunos->primeiro->prox;
        free(aux);
        materia->alunos->quantidade--;

    }else{

        anterior->prox = aluno->prox;
        free(aluno);
        materia->alunos->quantidade--;
    }
    system("clear"); 
    printf("\nAluno removido com sucesso!\n\nPressione enter para voltar.\n");
    getchar();
    getchar();
}

void ordenar(ALUNOS *alunos) {
  
    ALUNO* anterior = NULL;
    ALUNO* atual = alunos->primeiro->prox; 
  
    while (atual != NULL) {
        ALUNO* aux_ant = NULL;
        ALUNO* aux = alunos->primeiro;
        
        while (aux->dados.nota >= atual->dados.nota && aux != atual) {
            aux_ant = aux;
            aux = aux->prox;
        }
        
        if(anterior != NULL && aux != atual) {
            
            anterior->prox = atual->prox;

            if(aux_ant == NULL) 
                alunos->primeiro = atual;
            else 
                aux_ant->prox = atual;
        
            atual->prox = aux;
        }

        anterior = atual;
        atual = atual->prox;
    }
}

void listar_alunos(DISCIPLINA *disciplina){

    ALUNO *aux = disciplina->alunos->primeiro;
    int i;

    system("clear");
    printf("Alunos de %s\n\n",disciplina->nome);
    printf("Matricula   |   Nome   |   Faltas   |   Nota   |   Menção\n");
    for(i = 0;aux != NULL; i++){
        printf("%d       %s\t   %5.2f%%      %5.2f         %s\n",aux->dados.matricula, 
        aux->dados.nome, aux->dados.faltas*100, aux->dados.nota, aux->dados.mencao);
        aux = aux->prox;
    }
    printf("\nPressione enter para voltar.");
    getchar();
    getchar();
}

void atribuir_nota(ALUNO *aluno, float nota){

    if(nota < 0.00 || nota > 10.00){
        system("clear"); 
        printf("\nNota inválida!\n\n");
        printf("Pressione enter para voltar.");
        getchar();
        getchar();
    }else
        aluno->dados.nota = nota;
}

void atribuir_faltas(ALUNO *aluno, float faltas){

    if(faltas < 0.00 || faltas > 100.00){
        system("clear"); 
        printf("\nFaltas inválida!\n\n");
        printf("Pressione enter para voltar.");
        getchar();
        getchar();
    }else
        aluno->dados.faltas = faltas/100;
}

void calcular_mencao(ALUNOS *alunos){

    ALUNO *aluno = alunos->primeiro;

    while(aluno != NULL){

        if(aluno->dados.faltas >= 0.25)
            strcpy(aluno->dados.mencao,"SR");
        else if(aluno->dados.nota >= 9.0)
            strcpy(aluno->dados.mencao,"SS");
        else if(aluno->dados.nota >= 7.0)
            strcpy(aluno->dados.mencao,"MS");
        else if(aluno->dados.nota >= 5.0)
            strcpy(aluno->dados.mencao,"MM");
        else if(aluno->dados.nota >= 3.0)
            strcpy(aluno->dados.mencao,"MI");
        else 
            strcpy(aluno->dados.mencao,"II");

        aluno = aluno->prox;
    }
}

void mencoes(DISCIPLINA *disciplina, CURSOS *cursos){

    CURSO *curso;
    ALUNO *aluno = disciplina->alunos->primeiro;

    while(aluno != NULL){

        curso = buscar_curso(cursos,aluno->dados.curso);

        if(aluno->dados.faltas >= 0.25){
            curso->dados.mencoes[5]++;
            cursos->dados.mencoes[5]++;
        }else if(aluno->dados.nota >= 9.0){
            curso->dados.mencoes[0]++;
            cursos->dados.mencoes[0]++;
        }else if(aluno->dados.nota >= 7.0){
            curso->dados.mencoes[1]++;
            cursos->dados.mencoes[1]++;
        }else if(aluno->dados.nota >= 5.0){
            curso->dados.mencoes[2]++;
            cursos->dados.mencoes[2]++;
        }else if(aluno->dados.nota >= 3.0){
            curso->dados.mencoes[3]++;
            cursos->dados.mencoes[3]++;
        }else{
            curso->dados.mencoes[4]++;
            cursos->dados.mencoes[4]++;
        }

        aluno = aluno->prox;
    }
}

void liberar_cursos(CURSOS *cursos){

    CURSO *aux;

    while(cursos->primeiro != NULL){
        aux = cursos->primeiro;
        cursos->primeiro = cursos->primeiro->prox; 
        free(aux);
    }
}

void dados_cursos(DISCIPLINA *disciplina, CURSOS *cursos){

    CURSO *curso;
    ALUNO *aluno = disciplina->alunos->primeiro;

    while(aluno != NULL){

        curso = buscar_curso(cursos,aluno->dados.curso);
        if(curso == NULL)
            curso = adicionar_curso(cursos,aluno->dados.curso);

        if(aluno->dados.faltas < 0.25 && aluno->dados.nota >= 5.0){
            curso->dados.aprovados++;
            cursos->dados.aprovados++;
        }else{
            curso->dados.reprovados++;
            cursos->dados.reprovados++;
        }
        curso->dados.matriculados++;
        cursos->dados.matriculados++;
        aluno = aluno->prox;
    }

    mencoes(disciplina,cursos);
}

void processar_turma(DISCIPLINA *disciplina){

    CURSOS *cursos = criar_cursos();
    dados_cursos(disciplina,cursos);
    CURSO *curso = cursos->primeiro;

    printf("Informações de %s\n\n",disciplina->nome);
    printf("Curso\tMatriculados\tAprovados\tReprovados\n");
    while(curso != NULL){

        printf("%s           %d          %4d%% (%d)        %4d%% (%d)\n", curso->nome, curso->dados.matriculados,
        (curso->dados.aprovados*100)/curso->dados.matriculados, curso->dados.aprovados, (curso->dados.reprovados*100)/curso->dados.matriculados,curso->dados.reprovados);

        curso = curso->prox;
    }
    printf("Total        %d          %4d%% (%d)        %4d%% (%d)\n\n\n", cursos->dados.matriculados, (cursos->dados.aprovados*100)/cursos->dados.matriculados,
    cursos->dados.aprovados, (cursos->dados.reprovados*100)/cursos->dados.matriculados, cursos->dados.reprovados);

    curso = cursos->primeiro;

    printf("Menções:\n\n");
    printf("Curso\tSS   MS   MM   MI   II   SR\n");
    while(curso != NULL){

        printf("%s\t%d    %d    %d    %d    %d    %d\n", curso->nome, curso->dados.mencoes[0], curso->dados.mencoes[1],
        curso->dados.mencoes[2], curso->dados.mencoes[3], curso->dados.mencoes[4],curso->dados.mencoes[5]);

        curso = curso->prox;
    }
    printf("Total\t%d    %d    %d    %d    %d    %d\n", cursos->dados.mencoes[0], cursos->dados.mencoes[1],
        cursos->dados.mencoes[2], cursos->dados.mencoes[3], cursos->dados.mencoes[4],cursos->dados.mencoes[5]);

    printf("\nPressione enter para voltar.");
    getchar();
    getchar();
    
    liberar_cursos(cursos);
    free(cursos);
}

