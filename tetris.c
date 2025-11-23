#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5 // Tamanho fixo da fila

// Struct Peça: tipo ('I', 'O', 'T', 'L') + identificador numérico
struct Peca {
    char tipo;
    int id;
};

// Variáveis globais para controle da fila circular
struct Peca fila[TAM_FILA];
int inicio = 0, fim = 0, quantidade = 0;
int proxId = 0; // Identificador único gerado automaticamente

// Função que gera uma nova peça automaticamente
struct Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    struct Peca nova;
    nova.tipo = tipos[rand() % 4]; // Seleciona um tipo aleatório
    nova.id = proxId++;            // Atribui ID único
    return nova;
}

// Insere peça no final da fila (enqueue)
void enqueue() {
    if (quantidade == TAM_FILA) {
        printf("Fila cheia! Nao eh possivel inserir nova peca.\n");
        return;
    }
    fila[fim] = gerarPeca();
    fim = (fim + 1) % TAM_FILA; // Fila circular
    quantidade++;
    printf("Peca adicionada com sucesso!\n");
}

// Remove a peça da frente da fila (dequeue)
void dequeue() {
    if (quantidade == 0) {
        printf("Fila vazia! Nenhuma peca para jogar.\n");
        return;
    }
    printf("Peca [%c %d] jogada!\n", fila[inicio].tipo, fila[inicio].id);
    inicio = (inicio + 1) % TAM_FILA;
    quantidade--;
}

// Exibe o estado atual da fila
void exibirFila() {
    printf("\n=== Fila de Pecas ===\n");

    if (quantidade == 0) {
        printf("Fila vazia.\n");
        return;
    }

    int i = inicio;
    for (int j = 0; j < quantidade; j++) {
        printf("[%c %d] ", fila[i].tipo, fila[i].id);
        i = (i + 1) % TAM_FILA;
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    // Inicialização com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        exibirFila();

        printf("\nOpcoes:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
