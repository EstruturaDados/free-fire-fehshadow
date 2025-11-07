#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// 📦 Estrutura que representa um item da mochila
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// 🔗 Estrutura para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// 🔢 Contador de comparações
int comparacoesSequencial = 0;

// 📥 Inserir item na lista encadeada
No* inserirItemLista(No* inicio) {
    int contador = 0;
    No* temp = inicio;
    while (temp) {
        contador++;
        temp = temp->proximo;
    }

    if (contador >= MAX_ITENS) {
        printf("⚠️ Mochila cheia!\n");
        return inicio;
    }

    No* novo = (No*)malloc(sizeof(No));
    if (!novo) return inicio;

    printf("Nome: ");
    scanf(" %[^\n]", novo->dados.nome);
    printf("Tipo: ");
    scanf(" %[^\n]", novo->dados.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = inicio;
    printf("✅ Item inserido na lista.\n");
    return novo;
}

// 🗑️ Remover item da lista encadeada
No* removerItemLista(No* inicio) {
    char nome[30];
    printf("Nome do item a remover: ");
    scanf(" %[^\n]", nome);

    No *atual = inicio, *anterior = NULL;
    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior) anterior->proximo = atual->proximo;
            else inicio = atual->proximo;
            free(atual);
            printf("🗑️ Item removido da lista.\n");
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("❌ Item não encontrado.\n");
    return inicio;
}

// 📋 Listar itens da lista encadeada (estilizado)
void listarItensLista(No* inicio) {
    int contador = 0;
    No* atual = inicio;

    printf("\n📦 Mochila (lista encadeada):\n");

    // Contar itens
    while (atual) {
        contador++;
        atual = atual->proximo;
    }

    printf("Itens na mochila: %d/%d\n", contador, MAX_ITENS);

    if (contador == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    printf("┌────────────────────────┬──────────────┬─────────────┐\n");
    printf("│ Nome                   │ Tipo         │ Quantidade  │\n");
    printf("├────────────────────────┼──────────────┼─────────────┤\n");

    atual = inicio;
    while (atual) {
        printf("│ %-22s │ %-12s │ %-11d │\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }

    printf("└────────────────────────┴──────────────┴─────────────┘\n");
}

// 🔍 Buscar item na lista encadeada
void buscarItemLista(No* inicio) {
    char nome[30];
    comparacoesSequencial = 0;
    printf("Nome do item a buscar: ");
    scanf(" %[^\n]", nome);

    No* atual = inicio;
    while (atual) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0) {
            printf("🔍 Encontrado: %s | %s | %d\n",
                   atual->dados.nome,
                   atual->dados.tipo,
                   atual->dados.quantidade);
            printf("Comparações: %d\n", comparacoesSequencial);
            return;
        }
        atual = atual->proximo;
    }
    printf("❌ Item não encontrado. Comparações: %d\n", comparacoesSequencial);
}

// 🕹️ Menu principal
int main() {
    int opcao;
    No* lista = NULL;

    printf("🎮 Mochila de Inventário - Lista Encadeada\n");

    do {
        printf("\n📋 Menu:\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: lista = inserirItemLista(lista); break;
            case 2: lista = removerItemLista(lista); break;
            case 3: listarItensLista(lista); break;
            case 4: buscarItemLista(lista); break;
            case 0: printf("👋 Encerrando o sistema.\n"); break;
            default: printf("❌ Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}