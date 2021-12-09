#ifndef _DISCIPLINA_H_
#define _DISCIPLINA_H_

#include "matricula.h"

CURSOS *criar_cursos();
CURSO *adicionar_curso(CURSOS *cursos, char nome[3]);
CURSO *buscar_curso(CURSOS *cursos, char nome[3]);

void remover_da_disciplina(ALUNOS *alunos, DISCIPLINA *materia, int matricula);

void ordenar(ALUNOS *alunos);
void listar_alunos(DISCIPLINA *disciplina);

void atribuir_nota(ALUNO *aluno, float nota);
void atribuir_faltas(ALUNO *aluno, float faltas);

void calcular_mencao(ALUNOS *alunos);
void mencoes(DISCIPLINA *disciplina, CURSOS *cursos);

void liberar_cursos(CURSOS *cursos);
void dados_cursos(DISCIPLINA *disciplina, CURSOS *cursos);
void processar_turma(DISCIPLINA *disciplina);

#endif