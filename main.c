// Luis Gustavo de Jesus das Neves - GU 30345658
// Camile de Jesus Nascimento

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main() {
    int opcao, j;
    int codigo, telefone, celular;
    char nome[50], empresa[50], departamento[50], email[50];
    No* lista = NULL, * removido = NULL;

    // Carregar os funcionários automaticamente
    carregar_arquivo(&lista, "funcionarios.bin");

    do {
        printf("\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Buscar\n\t4 - Imprimir\n\t5 - Editar\n\t6 - Salvar\n");
        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            printf("Digite o codigo: ");
            scanf("%d", &codigo);
            printf("Digite o telefone: ");
            scanf("%d", &telefone);
            printf("Digite o celular: ");
            scanf("%d", &celular);
            getchar(); // Consumir o caractere de nova linha
            printf("Digite o nome: ");
            fgets(nome, sizeof(nome), stdin);
            printf("Digite o departamento: ");
            fgets(departamento, sizeof(departamento), stdin);
            printf("Digite o email: ");
            fgets(email, sizeof(email), stdin);
            inserir_ordenado(&lista, codigo, telefone, celular, nome, departamento, email);
            break;
        case 2:
            printf("Digite o codigo do funcionario a ser removido: ");
            scanf("%d", &codigo);
            removido = remover(&lista, codigo);
            if (removido) {
                printf("Elemento a ser removido: %d \n", removido->codigo);
                free(removido);
            }
            break;
        case 3:
            printf("Digite 1 para busca por codigo e 2 para busca por nome\n");
            scanf("%d", &j);
            if(j == 1){
                printf("Digite o codigo do funcionario a ser buscado: ");
                scanf("%d", &codigo);
                buscarPorCodigo(&lista, codigo);
            }else if(j == 2){
                getchar();
                buscarPorNome(&lista);
            }else
                printf("Opcao invalida\n");
            break;
        case 4:
            imprimir(lista);
            break;
        case 5:
            edita(&lista);
            break;
        case 6:
            salvar_arquivo(lista, "funcionarios.bin");
            break;
        case 0:
            printf("Saindo do programa");
            break;
        default:
            if (opcao != 0)
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}
