#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include <ctype.h>

char* transformaEmMinusculo(char nome[]) { // essa fun��o pega o nome do funcion�rio e o passa para min�sculo
    int i = 0;
    char* nomeMinusculo = malloc(strlen(nome) + 1);
    while (nome[i] != '\0') {
        nomeMinusculo[i] = tolower(nome[i]);
        i++;
    }
    nomeMinusculo[i] = '\0';
    return nomeMinusculo;
}


void inserir_ordenado(No** lista, int codigo, int telefone, int celular, char nome[50], char departamento[50], char email[50]) {
    No* aux = *lista; // a variavel aux ira ser usada para percorrer a lista.
    No* novo = malloc(sizeof(No)); // alocando memoria para o novo no.
    char empresa[] = "ACME S.A";
    if (novo) {
        novo->codigo = codigo;
        novo->telefone = telefone;
        novo->celular = celular;
        strcpy(novo->nome, transformaEmMinusculo(nome)); // para o nome ser salvo em letras minusculas
        strcpy(novo->empresa, empresa);
        strcpy(novo->departamento, departamento);
        strcpy(novo->email, email);

        if (*lista == NULL) { // verifica se a lista esta vazia, se sim, o conte�do de lista ser� esse novo n� e o proximo n� ser� definido como nulo, pois como esse � o primeiro valor, o proximo n�o existe.
            novo->proximo = NULL;
            *lista = novo;
        } else if (novo->codigo < (*lista)->codigo) { // verifica se o c�digo do novo valor a ser adicionado � menor que o valor do atual primeiro n�, caso seja, "*lista" passar� a apontar para esse novo n�, e esse novo n� ir� apontar para o atual primeiro valor da lista.
            novo->proximo = *lista;
            *lista = novo;
        } else {
            aux = *lista;
            while (aux->proximo && novo->codigo > aux->proximo->codigo)//percorre a lista at� que o codigo desse novo n� seja menor que o codigo de algum n� da lista. quando ele encontrar um valor maior que ele, esse novo n� passar� a apontar para o n� maior e assumira a sua posi��o.
                aux = aux->proximo;
                novo->proximo = aux->proximo;
                aux->proximo = novo;
        }
    } else {
        printf("Erro ao alocar mem�ria\n");
    }
}

No* remover(No** lista, int codigo) {
    No* aux, * remover = NULL; // a variavel aux ira ser usada para percorrer a lista.

    if (*lista) { // verifica se a lista n�o � nula.
        if ((*lista)->codigo == codigo) { // verifica se o codigo a ser removido esta na primeira posi��o da lista.
            remover = *lista;
            *lista = remover->proximo;
        } else {
            aux = *lista;
            while (aux->proximo && aux->proximo->codigo != codigo) // caso os pr�ximos valores da lista n�o seja nulo e diferentes do valor do c�digo, a lista ser� percorrida at� que o valor que foi enviado no parametro da fun��o seja encontrado.
                aux = aux->proximo;
            if (aux->proximo) { // quando a repeti��o for quebrada significa que um dos requisitos foi atingido. Aqui � verificado se a lista n�o � nula, caso n�o seja, significa que a condi��o atingida foi a de que o campo codigo do n� � tem o mesmo valor que o codigo recebido no parametro da fun��o.
                remover = aux->proximo;
                aux->proximo = remover->proximo;
            }
        }
    }

    return remover;
}

void imprimir_funcionario(No* funcionario) { //essa fun��o foi feita para imprimir funcionarios individualmente.
    system("cls");
    printf("------ Funcionario(a) encontrado ------\n");
    printf("\nCodigo do funcionario: %d\n", funcionario->codigo);
    printf("Telefone: %d\n", funcionario->telefone);
    printf("Celular: %d\n", funcionario->celular);
    printf("Nome: %s", funcionario->nome);
    printf("Empresa: %s\n", funcionario->empresa);
    printf("Departamento: %s", funcionario->departamento);
    printf("Email: %s\n", funcionario->email);
    printf("-----------------------------------\n");
}


void buscarPorCodigo(No** lista, int codigo) {
    No* aux = *lista;
    int encontrado = 0;

    while (aux != NULL) {
        if (aux->codigo == codigo) { // procura pelo codigo, caso seja encontrado ele ir� chamar a fun��o acima que tem o objetivo de imprimir apenas um �nico funcion�rio por vez.
            imprimir_funcionario(aux);
            encontrado = 1;
        }
        aux = aux->proximo;
    }

    if (!encontrado) {
        printf("Funcionario(a) com c�digo %d nao encontrado.\n", codigo);
    }
}

void buscarPorNome(No** lista) {
    int i = 0;
    char nome[50];
    printf("Digite o nome a ser procurado\n");
    fgets(nome, sizeof(nome), stdin);
    while(nome[i] != '\0'){
        nome[i] = tolower(nome[i]);
        i++;
    }nome[i] = '\0';
    No* aux = *lista;
    int encontrado = 0;

    while (aux != NULL) {
        if (strcmp(aux->nome, nome) == 0) {
            imprimir_funcionario(aux);
            encontrado = 1;
        }
        aux = aux->proximo;
    }

    if (!encontrado) {
        printf("Funcionario(a) com nome %s nao encontrado.\n", nome);
    }
}

void salvar_arquivo(No* lista, char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "wb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    No* aux = lista;
    while (aux != NULL) {
        fwrite(aux, sizeof(No), 1, arquivo);
        aux = aux->proximo;
    }

    fclose(arquivo);
    printf("Dados salvos com sucesso no arquivo '%s'.\n", nome_arquivo);
}

void carregar_arquivo(No** lista, char* nome_arquivo) {
    FILE* arquivo = fopen(nome_arquivo, "rb");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    No funcionario;
    while (fread(&funcionario, sizeof(No), 1, arquivo) == 1) {
        inserir_ordenado(lista, funcionario.codigo, funcionario.telefone, funcionario.celular, funcionario.nome, funcionario.departamento, funcionario.email);
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso do arquivo '%s'.\n", nome_arquivo);
}

void imprimir(No* no) { // essa fun��o foi feita para imprimir todos os funcion�rios.
    system("cls");
    printf("\n\tLista:\n");
    int i = 1;
    while (no) {
        printf("------funcionario %d ------\n", i);
        printf("Codigo do funcionario: %d\n\n", no->codigo);
        printf("Telefone: %d\n\n", no->telefone);
        printf("Celular: %d\n\n", no->celular);
        printf("Nome: %s\n", no->nome);
        printf("Empresa: %s\n\n", no->empresa);
        printf("Departamento:%s\n", no->departamento);
        printf("email: %s\n", no->email);
        i=i+1;
        no = no->proximo;
    }
    printf("\n\n");
}

void edita(No **lista) {
    int codigo, telefone, celular;
    char nome[50], empresa[50], departamento[50], email[50];

    printf("Digite o codigo do funcionario a ser editado: ");
    scanf("%d", &codigo);

    No* aux = *lista;
    while (aux != NULL) { //inicia um la�o de repeti��o que percorre a lista encadeada at� encontrar o n� com o c�digo correspondente ao fornecido pelo usu�rio.
        if (aux->codigo == codigo) // verifica se o c�digo inserido pelo usu�rio � igual ao codigo do no da lista.
            break; // Se o c�digo for igual, o la�o � interrompido utilizando break, pois o n� a ser editado foi encontrado.
        aux = aux->proximo; // caso n�o seja, ele ir� para o proximo no.
    }

    if (aux == NULL) {
        printf("Funcionario com codigo %d nao encontrado.\n", codigo);
        return;
    } // caso o c�dogo n�o seja encontrado at� o final da lista essa mensagem ir� aparecer.

    //caso o codigo seja encontrado o programa ir� pedir as novas informa��es.

    printf("Digite o novo telefone: ");
    scanf("%d", &telefone);
    printf("Digite o novo celular: ");
    scanf("%d", &celular);
    getchar();
    printf("Digite o novo nome: ");
    fgets(nome, sizeof(nome), stdin);
    printf("Digite o novo departamento: ");
    fgets(departamento, sizeof(departamento), stdin);
    printf("Digite o novo email: ");
    fgets(email, sizeof(email), stdin);

    aux->telefone = telefone;
    aux->celular = celular;
    strcpy(aux->nome, transformaEmMinusculo(nome));
    strcpy(aux->departamento, departamento);
    strcpy(aux->email, email);

    printf("Funcionario editado com sucesso.\n");
}
