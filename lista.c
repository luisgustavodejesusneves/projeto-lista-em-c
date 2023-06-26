#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#include <ctype.h>

char* transformaEmMinusculo(char nome[]) { // essa função pega o nome do funcionário e o passa para minúsculo
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

        if (*lista == NULL) { // verifica se a lista esta vazia, se sim, o conteúdo de lista será esse novo nó e o proximo nó será definido como nulo, pois como esse é o primeiro valor, o proximo não existe.
            novo->proximo = NULL;
            *lista = novo;
        } else if (novo->codigo < (*lista)->codigo) { // verifica se o código do novo valor a ser adicionado é menor que o valor do atual primeiro nó, caso seja, "*lista" passará a apontar para esse novo nó, e esse novo nó irá apontar para o atual primeiro valor da lista.
            novo->proximo = *lista;
            *lista = novo;
        } else {
            aux = *lista;
            while (aux->proximo && novo->codigo > aux->proximo->codigo)//percorre a lista até que o codigo desse novo nó seja menor que o codigo de algum nó da lista. quando ele encontrar um valor maior que ele, esse novo nó passará a apontar para o nó maior e assumira a sua posição.
                aux = aux->proximo;
                novo->proximo = aux->proximo;
                aux->proximo = novo;
        }
    } else {
        printf("Erro ao alocar memória\n");
    }
}

No* remover(No** lista, int codigo) {
    No* aux, * remover = NULL; // a variavel aux ira ser usada para percorrer a lista.

    if (*lista) { // verifica se a lista não é nula.
        if ((*lista)->codigo == codigo) { // verifica se o codigo a ser removido esta na primeira posição da lista.
            remover = *lista;
            *lista = remover->proximo;
        } else {
            aux = *lista;
            while (aux->proximo && aux->proximo->codigo != codigo) // caso os próximos valores da lista não seja nulo e diferentes do valor do código, a lista será percorrida até que o valor que foi enviado no parametro da função seja encontrado.
                aux = aux->proximo;
            if (aux->proximo) { // quando a repetição for quebrada significa que um dos requisitos foi atingido. Aqui é verificado se a lista não é nula, caso não seja, significa que a condição atingida foi a de que o campo codigo do nó é tem o mesmo valor que o codigo recebido no parametro da função.
                remover = aux->proximo;
                aux->proximo = remover->proximo;
            }
        }
    }

    return remover;
}

void imprimir_funcionario(No* funcionario) { //essa função foi feita para imprimir funcionarios individualmente.
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
        if (aux->codigo == codigo) { // procura pelo codigo, caso seja encontrado ele irá chamar a função acima que tem o objetivo de imprimir apenas um único funcionário por vez.
            imprimir_funcionario(aux);
            encontrado = 1;
        }
        aux = aux->proximo;
    }

    if (!encontrado) {
        printf("Funcionario(a) com código %d nao encontrado.\n", codigo);
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

void imprimir(No* no) { // essa função foi feita para imprimir todos os funcionários.
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
    while (aux != NULL) { //inicia um laço de repetição que percorre a lista encadeada até encontrar o nó com o código correspondente ao fornecido pelo usuário.
        if (aux->codigo == codigo) // verifica se o código inserido pelo usuário é igual ao codigo do no da lista.
            break; // Se o código for igual, o laço é interrompido utilizando break, pois o nó a ser editado foi encontrado.
        aux = aux->proximo; // caso não seja, ele irá para o proximo no.
    }

    if (aux == NULL) {
        printf("Funcionario com codigo %d nao encontrado.\n", codigo);
        return;
    } // caso o códogo não seja encontrado até o final da lista essa mensagem irá aparecer.

    //caso o codigo seja encontrado o programa irá pedir as novas informações.

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
