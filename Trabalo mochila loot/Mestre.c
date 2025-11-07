#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

int comparacoes = 0;

// ✅ Declaração da função de busca binária
void buscaBinariaPorNome(No* inicio);

// Inserir item
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
    printf("Prioridade (1 a 10): ");
    scanf("%d", &novo->dados.prioridade);

    novo->proximo = inicio;
    printf("✅ Componente adicionado à mochila.\n");
    return novo;
}

// Remover item
No* removerItemLista(No* inicio) {
    char nome[30];
    printf("Nome do componente a descartar: ");
    scanf(" %[^\n]", nome);

    No *atual = inicio, *anterior = NULL;
    while (atual) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior) anterior->proximo = atual->proximo;
            else inicio = atual->proximo;
            free(atual);
            printf("🗑️ Componente descartado.\n");
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("❌ Componente não encontrado.\n");
    return inicio;
}

// Mostrar lista formatada
void mostrarLista(Item vetor[], int n) {
    printf("┌────────────────────────┬──────────────┬─────────────┬─────────────┐\n");
    printf("│ Nome                   │ Tipo         │ Quantidade  │ Prioridade  │\n");
    printf("├────────────────────────┼──────────────┼─────────────┼─────────────┤\n");
    for (int i = 0; i < n; i++) {
        printf("│ %-22s │ %-12s │ %-11d │ %-11d │\n",
               vetor[i].nome,
               vetor[i].tipo,
               vetor[i].quantidade,
               vetor[i].prioridade);
    }
    printf("└────────────────────────┴──────────────┴─────────────┴─────────────┘\n");
}

// Ordenações
void ordenarPorNome(Item vetor[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {
                Item temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
}

void ordenarPorTipo(Item vetor[], int n) {
    for (int i = 1; i < n; i++) {
        Item chave = vetor[i];
        int j = i - 1;
        while (j >= 0 && strcmp(vetor[j].tipo, chave.tipo) > 0) {
            vetor[j + 1] = vetor[j];
            j--;
        }
        vetor[j + 1] = chave;
    }
}

void ordenarPorPrioridade(Item vetor[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (vetor[j].prioridade < vetor[min].prioridade)
                min = j;
        if (min != i) {
            Item temp = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = temp;
        }
    }
}

// ✅ Função de busca binária por nome
void buscaBinariaPorNome(No* inicio) {
    char chave[30];
    printf("Nome do componente-chave: ");
    scanf(" %[^\n]", chave);

    Item vetor[MAX_ITENS];
    int n = 0;
    No* atual = inicio;
    while (atual && n < MAX_ITENS) {
        vetor[n++] = atual->dados;
        atual = atual->proximo;
    }

    ordenarPorNome(vetor, n);

    int ini = 0, fim = n - 1, meio;
    comparacoes = 0;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        comparacoes++;
        int cmp = strcmp(vetor[meio].nome, chave);
        if (cmp == 0) {
            printf("🔍 Componente encontrado: %s | %s | %d | %d\n",
                   vetor[meio].nome,
                   vetor[meio].tipo,
                   vetor[meio].quantidade,
                   vetor[meio].prioridade);
            printf("Comparações: %d\n", comparacoes);
            return;
        } else if (cmp < 0) {
            ini = meio + 1;
        } else {
            fim = meio - 1;
        }
    }

    printf("❌ Componente não encontrado. Comparações: %d\n", comparacoes);
}

// Submenu de organização
void listarItensLista(No* inicio) {
    int contador = 0;
    No* atual = inicio;
    Item vetor[MAX_ITENS];

    while (atual && contador < MAX_ITENS) {
        vetor[contador++] = atual->dados;
        atual = atual->proximo;
    }

    if (contador == 0) {
        printf("📦 Mochila vazia.\n");
        return;
    }

    int escolha;
    do {
        printf("\n📊 Estratégia de Organização\n");
        printf("Como deseja ordenar os componentes?\n");
        printf("1. Por Nome (Ordem Alfabética)\n");
        printf("2. Por Tipo\n");
        printf("3. Por Prioridade de Montagem\n");
        printf("0. Cancelar\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                ordenarPorNome(vetor, contador);
                mostrarLista(vetor, contador);
                break;
            case 2:
                ordenarPorTipo(vetor, contador);
                mostrarLista(vetor, contador);
                break;
            case 3:
                ordenarPorPrioridade(vetor, contador);
                mostrarLista(vetor, contador);
                break;
            case 0:
                printf("↩️ Organização cancelada.\n");
                break;
            default:
                printf("❌ Opção inválida.\n");
        }
    } while (escolha != 0);
}

// Menu principal
int main() {
    int opcao;
    No* mochila = NULL; // ✅ variável declarada corretamente

    printf("🎮 Mochila de Inventário - Sistema Integrado\n");

    do {
        printf("\n📋 Menu:\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Componentes (Inventário)\n");
        printf("4. Busca Binária por Componente-Chave (por nome)\n");
        printf("0. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                mochila = inserirItemLista(mochila);
                break;
            case 2:
                mochila = removerItemLista(mochila);
                break;
            case 3:
                listarItensLista(mochila);
                break;
            case 4:
                buscaBinariaPorNome(mochila); // ✅ chamada correta
                break;
            case 0:
                printf("🚀 TORRE DE FUGA ATIVADA!\n");
                break;
            default:
                printf("❌ Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}