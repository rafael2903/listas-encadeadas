#ifndef _MATRICULA_H_
#define _MATRICULA_H_

typedef struct Dados {
    char nome[50];
    int matricula;
    char curso[3];
    char materia[4];
    float faltas;
    float nota;
    char mencao[3];
} DADOS;

typedef struct Aluno {
    DADOS dados;
    struct Aluno* prox;
} ALUNO;

typedef struct LISTA_DE_ALUNOS {
    int quantidade;
    ALUNO* primeiro;
} ALUNOS;


typedef struct DADOS_CURSO {
    int matriculados;
    int aprovados;
    int reprovados;
    int mencoes[5];
} INFOS;

typedef struct Curso {
    char nome[3];
    INFOS dados;
    struct Curso* prox;
} CURSO;

typedef struct LISTA_DE_CURSOS {
    int quantidade;
    INFOS dados;
    CURSO* primeiro;
} CURSOS;


typedef struct Disciplina {
    char nome[4];
    ALUNOS* alunos;
    struct Disciplina* prox;
} DISCIPLINA;

typedef struct LISTA_DE_DISCIPLINAS {
    int quantidade;
    DISCIPLINA* primeira;
} DISCIPLINAS;


ALUNOS* criar_alunos();
DISCIPLINAS* criar_disciplinas();
ALUNO* criar_aluno(char Nome[50], int Matricula, char Curso[3], char Materia[4], float Faltas, float Nota, char Mencao[3]);

ALUNO* adicionar_sem_disciplina(ALUNOS* alunos, char nome[50], int matricula, char curso[3]);
DISCIPLINA* adicionar_disciplina(DISCIPLINAS* disciplinas, char nome[4]);

void remover_do_sistema(ALUNOS* alunos, int matricula);
void remover_disciplina(ALUNOS* alunos, DISCIPLINAS* disciplinas, char nome[4]);

void incluir_aluno(ALUNOS* alunos, ALUNO* aluno, DISCIPLINA* disciplina);
void carregar_aluno(DISCIPLINA* disciplina, ALUNO* aluno);

ALUNO* buscar_aluno(ALUNOS* alunos, int matricula);
DISCIPLINA* buscar_disciplina(DISCIPLINAS* disciplinas, char disciplina[4]);

void listar_sem_disciplina(ALUNOS* semDisciplinas);
void listar_disciplinas(DISCIPLINAS* disciplinas);

void carregar_arquivo(ALUNOS* semDisciplinas, DISCIPLINAS* disciplinas);
void salvar_arquivo(ALUNOS* alunos, DISCIPLINAS* disciplinas);

#endif