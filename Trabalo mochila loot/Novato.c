#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10  // Capacidade máxima da mochila

// 📦 Estrutura que representa um item da mochila
typedef struct {
    char nome[30];     // Nome do item (ex: Pistola, Bandagem)
    char tipo[20];     // Tipo do item (ex: arma, munição, cura, ferramenta)
    int quantidade;    // Quantidade do item
} Item;

// 🎒 Vetor de structs que representa a mochila
Item mochila[MAX_ITENS];
int totalItens = 0;  // Contador de itens cadastrados

// 📝 Função para inserir um novo item na mochila
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novoItem;
    printf("\n🔧 Cadastro de novo item:\n");
    printf("Nome: ");
    scanf(" %[^\n]", novoItem.nome);
    printf("Tipo (arma, munição, cura, ferramenta): ");
    scanf(" %[^\n]", novoItem.tipo);
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);

    mochila[totalItens++] = novoItem;
    printf("✅ Item \"%s\" adicionado com sucesso!\n", novoItem.nome);
}

// 🗑️ Função para remover um item da mochila pelo nome
void removerItem() {
    char nomeRemover[30];
    printf("\nDigite o nome do item a remover: ");
    scanf(" %[^\n]", nomeRemover);

    int encontrado = 0;
    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            totalItens--;
            printf("🗑️ Item \"%s\" removido da mochila.\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("❌ Item \"%s\" não encontrado na mochila.\n", nomeRemover);
    }
}

// 📋 Função para listar todos os itens da mochila
void listarItens() {
    printf("\n📦 Itens atuais na mochila:\n");

    if (totalItens == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < totalItens; i++) {
        printf(" - Nome: %s | Tipo: %s | Quantidade: %d\n",
               mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}

// 🔍 Função de busca sequencial por nome de item
void buscarItem() {
    char nomeBusca[30];
    printf("\nDigite o nome do item a buscar: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("🔍 Item encontrado:\n");
            printf(" - Nome: %s | Tipo: %s | Quantidade: %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }

    printf("❌ Item \"%s\" não encontrado na mochila.\n", nomeBusca);
}

// 🕹️ Função principal com menu interativo
int main() {
    int opcao;

    printf("🎮 Bem-vindo ao Sistema de Inventário - Mochila de Loot Inicial!\n");

    do {
        printf("\n📋 Menu de opções:\n");
        printf("1. Inserir item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("👋 Encerrando o sistema. Até a próxima!\n");
                break;
            default:
                printf("❌ Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}