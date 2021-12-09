#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matricula.h"

ALUNOS *criar_alunos(){

    ALUNOS *alunos = (ALUNOS*) malloc(sizeof(ALUNOS));
    alunos->quantidade = 0;
    alunos->primeiro = NULL;

    return alunos;
}

DISCIPLINAS *criar_disciplinas(){

    DISCIPLINAS *disciplinas = (DISCIPLINAS*) malloc(sizeof(DISCIPLINAS));
    disciplinas->quantidade = 0;
    disciplinas->primeira = NULL;

    return disciplinas;
}

ALUNO *criar_aluno(char Nome[50], int Matricula, char Curso[3], char Materia[4], float Faltas, float Nota, char Mencao[3] ){

    ALUNO *aluno = (ALUNO*) malloc(sizeof(ALUNO));
    
    strcpy(aluno->dados.nome,Nome);
    aluno->dados.matricula = Matricula;
    strcpy(aluno->dados.curso,Curso);
    strcpy(aluno->dados.materia,Materia);
    aluno->dados.faltas = Faltas;
    aluno->dados.nota = Nota;
    strcpy(aluno->dados.mencao,Mencao);

    aluno->prox = NULL;

    return aluno;
}

ALUNO *adicionar_sem_disciplina(ALUNOS *alunos, char nome[50], int matricula, char curso[3]){

    ALUNO *novo = (ALUNO*) malloc(sizeof(ALUNO));
    ALUNO *aux = alunos->primeiro;

    novo->prox = NULL;
    strcpy(novo->dados.nome,nome);
    strcpy(novo->dados.curso,curso);
    novo->dados.matricula = matricula;
    novo->dados.nota = 0.00;
    novo->dados.faltas = 0.00;
    strcpy(novo->dados.materia,"*");
    strcpy(novo->dados.mencao,"*");
    
    if(aux == NULL)
        alunos->primeiro = novo;
    else{
        while(aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novo;
    }
    alunos->quantidade++;

    return novo;
}

DISCIPLINA *adicionar_disciplina(DISCIPLINAS *disciplinas,char nome[4]){

    if(buscar_disciplina(disciplinas,nome)){
        system("clear");
        printf("\nDisciplina já cadastrada!\n\n");
        printf("Pressione enter para voltar.");
        getchar();
        getchar();
        return NULL;
    }

    DISCIPLINA *tmp = disciplinas->primeira;
    DISCIPLINA *novo = (DISCIPLINA*) malloc(sizeof(DISCIPLINA));
   
    novo->alunos = criar_alunos();
    strcpy(novo->nome,nome);
    novo->prox = NULL;
    
    if(tmp == NULL)
        disciplinas->primeira = novo;
    else{
        while(tmp->prox != NULL)
            tmp = tmp->prox;

        tmp->prox = novo;
    }
    disciplinas->quantidade++;

    return novo;
}

void remover_do_sistema(ALUNOS *alunos, int matricula){

    ALUNO *anterior = NULL,*aux, *aluno = alunos->primeiro;
    
    while(aluno != NULL){
        if(aluno->dados.matricula == matricula)
            break;
        anterior = aluno;
        aluno = aluno->prox;
    }

    if(aluno == NULL){
        system("clear"); 
        printf("\nAluno inexistente ou já matriculado, impossível remover!\n\n");
        printf("Pressione enter para voltar.");
        getchar();
        getchar();
        return ;
    }

    if(aluno == alunos->primeiro){
            
        aux = alunos->primeiro;
        alunos->primeiro = alunos->primeiro->prox;
        free(aux);
        alunos->quantidade--;

    }else{

        anterior->prox = aluno->prox;
        free(aluno);
        alunos->quantidade--;
    }
}

void remover_disciplina(ALUNOS *alunos, DISCIPLINAS *disciplinas, char nome[4]){
  
    DISCIPLINA *anterior = NULL, *materia = disciplinas->primeira, *aux2;
   
    while(materia != NULL){
        if(!strcmp(materia->nome,nome))
            break;
        anterior = materia;
        materia = materia->prox;
    }

    if(materia == NULL){
        system("clear"); 
        printf("\nDisciplina não encontrada!\n\n");
        printf("Pressione enter para voltar.");
        getchar();
        getchar();
        return ;
    }

    ALUNO *aux = NULL, *aluno = materia->alunos->primeiro;

    while(aluno != NULL){
        adicionar_sem_disciplina(alunos,aluno->dados.nome,aluno->dados.matricula,aluno->dados.curso);
        aux = aluno->prox;
        free(aluno);
        aluno = aux;
    }
   
    if(materia == disciplinas->primeira){

        aux2 = disciplinas->primeira;
        disciplinas->primeira = disciplinas->primeira->prox;
        free(aux2);
        disciplinas->quantidade--;
    }else{

        anterior->prox = materia->prox;
        free(materia);
        disciplinas->quantidade--;
    }

    system("clear"); 
    printf("\nDisciplina removida com sucesso!\n\nPressione enter para voltar.\n");
    getchar();
    getchar();
}

void incluir_aluno(ALUNOS *alunos, ALUNO *aluno, DISCIPLINA *materia){

    ALUNO *aux = materia->alunos->primeiro;
    ALUNO *novo = (ALUNO*) malloc(sizeof(ALUNO));

    novo->prox = NULL;
    strcpy(novo->dados.nome,aluno->dados.nome);
    strcpy(novo->dados.curso,aluno->dados.curso);
    novo->dados.matricula = aluno->dados.matricula;
    novo->dados.nota = 0.00;
    novo->dados.faltas = 0.00;
    strcpy(novo->dados.materia,materia->nome);
    strcpy(novo->dados.mencao,"*");

    if(aux == NULL)
        materia->alunos->primeiro = novo;
    else{
        while(aux->prox != NULL)
            aux = aux->prox;
        
        aux->prox = novo;
    }
    materia->alunos->quantidade++;

    remover_do_sistema(alunos,aluno->dados.matricula);
}

void carregar_aluno(DISCIPLINA *materia, ALUNO *aluno){

    ALUNO *aux = materia->alunos->primeiro;

   if(aux == NULL)
        materia->alunos->primeiro = aluno;
    else{
        while(aux->prox != NULL)
            aux = aux->prox;
        
        aux->prox = aluno;
    }
    materia->alunos->quantidade++;
}


ALUNO *buscar_aluno(ALUNOS *alunos, int matricula){

    ALUNO *aluno = alunos->primeiro;

    while(aluno != NULL){
        if(aluno->dados.matricula == matricula)
            return aluno;
        aluno = aluno->prox;
    }
    return aluno;
}

DISCIPLINA *buscar_disciplina(DISCIPLINAS *disciplinas, char disciplina[4]){

    DISCIPLINA *materia = disciplinas->primeira;

    while(materia != NULL){
        if(!strcmp(materia->nome,disciplina))
            return materia;
        materia = materia->prox;
    }
    return materia;
}

void listar_sem_disciplina(ALUNOS *semDisciplina){

    ALUNO* tmp = semDisciplina->primeiro;

    if(tmp == NULL){
        printf("\nTodos os alunos estão matriculados!\n");
        printf("\nPressione enter para voltar.");
        getchar();
        getchar();
        return ;
    }

    printf("Alunos sem disciplina\n\n");
    printf("Nome\t  Matricula\tCurso\n");
    while(tmp != NULL){
        printf("%s",tmp->dados.nome);
        printf("\t  %d",tmp->dados.matricula);
        printf("\t%s\n",tmp->dados.curso);
        tmp = tmp->prox;
    }
    printf("\nPressione enter para voltar.");
    getchar();
    getchar();
}

void listar_disciplinas(DISCIPLINAS *disciplinas){

    DISCIPLINA *aux = disciplinas->primeira;

    if(aux == NULL){
        printf("\nSem disciplinas!\n");
        printf("\nPressione enter para voltar.");
        getchar();
        getchar();
        return ;
    }

    printf("Disciplina\tAlunos\n");
    while(aux != NULL){
        printf("%s\t\t%3d\n",aux->nome,aux->alunos->quantidade);
        aux = aux->prox;
    }
    printf("\nPressione enter para voltar.");
    getchar();
    getchar();
}


void carregar_arquivo(ALUNOS *semDisciplinas, DISCIPLINAS *disciplinas){
    
    int i, matricula;
    char c, nome[50], curso[3], disciplina[4],mencao[3];
    float faltas, nota;

    FILE *file = fopen("alunos.txt", "r");
    DISCIPLINA *materia;
    ALUNO *aluno;

    if(file == NULL){
        file = fopen("alunos.txt","w");
        fclose(file);
        return ;
    }
    
    while(1){

        i = 0;
        do{
            c = fgetc(file);
            if(c == EOF){
                fclose(file);
                return ;
            }
            if(c != ';' && c != '\n'){
                nome[i] = c;
                i++;
            }
        }while(c != ';');

        nome[i] = '\0';
        
        fscanf(file,"%d",&matricula);
        fgetc(file);

        i = 0;
        do{
            c = fgetc(file);
            if(c != ';')
                curso[i] = c;
            i++;
        }while(c != ';');

        curso[i-1] = '\0';

        i = 0;
        do{
            c = fgetc(file);
            if(c != ';')
                disciplina[i] = c;
            i++;
        }while(c != ';');
        disciplina[i-1] = '\0';


        fscanf(file,"%f",&faltas);
        fgetc(file);
        
        fscanf(file,"%f",&nota);
        fgetc(file);

        for(i=0; i < 2 && c != '*'; i++){
            c = fgetc(file);
            mencao[i] = c;
        } 
        mencao[i] = '\0';
    
        if(!strcmp(disciplina,"*"))
             adicionar_sem_disciplina(semDisciplinas,nome,matricula,curso);
        else{

            materia =  buscar_disciplina(disciplinas,disciplina);
           
            if(materia == NULL){
                materia = adicionar_disciplina(disciplinas,disciplina);
                aluno = criar_aluno(nome,matricula,curso,disciplina,faltas,nota,mencao);
                carregar_aluno(materia,aluno);  
            }else{
                aluno = criar_aluno(nome,matricula,curso,disciplina,faltas,nota,mencao);
                carregar_aluno(materia,aluno);
            }
        }
    }

    fclose(file);
}

void salvar_arquivo(ALUNOS *alunos, DISCIPLINAS *disciplinas){

    FILE *file = fopen("alunos.txt", "w");
    ALUNO *aluno = alunos->primeiro;
    DISCIPLINA *disciplina = disciplinas->primeira;
    
    while(aluno != NULL){

        fprintf(file,"%s;%d;%s;%s;%.2f;%.2f;%s\n",aluno->dados.nome,aluno->dados.matricula,
        aluno->dados.curso,aluno->dados.materia,aluno->dados.faltas,aluno->dados.nota,aluno->dados.mencao);

        aluno = aluno->prox;
    }
    
    while(disciplina != NULL){

        aluno = disciplina->alunos->primeiro;

        while(aluno != NULL){

            fprintf(file,"%s;%d;%s;%s;%.2f;%.2f;%s\n",aluno->dados.nome,aluno->dados.matricula,
            aluno->dados.curso,aluno->dados.materia,aluno->dados.faltas,aluno->dados.nota,aluno->dados.mencao);

            aluno = aluno->prox;
        }
        disciplina = disciplina->prox; 
    }

    fclose(file); 
    printf("\nAlterações salvas com sucesso!\n\n");
    printf("Pressione enter para voltar.");
    getchar();
    getchar();
}