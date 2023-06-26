#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no {
    int codigo, telefone, celular;
    char nome[50], empresa[50], departamento[50], email[50];
    struct no* proximo;
} No;

char tranformaEmMinusculo(char nome[]);
void inserir_ordenado(No** lista, int codigo, int telefone, int celular, char nome[50], char departamento[50], char email[50]);
No* remover(No** lista, int codigo);
void imprimir_funcionario(No* funcionario);
void buscarPorCodigo(No** lista, int codigo);
void buscarPorNome(No** lista);
void salvar_arquivo(No* lista, char* nome_arquivo);
void carregar_arquivo(No** lista, char* nome_arquivo);
void imprimir(No* no);
void edita(No **lista);
