#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Desafio Detective Quest
// Tema 4 - Árvores e Tabela Hash
// Este código inicial serve como base para o desenvolvimento das estruturas de navegação, pistas e suspeitos.
// Use as instruções de cada região para desenvolver o sistema completo com árvore binária, árvore de busca e tabela hash.

// ============================================================================
// 🌱 NÍVEL NOVATO: MAPA DA MANSÃO COM ÁRVORE BINÁRIA
// ============================================================================

// Estrutura para representar cada sala da mansão
typedef struct Sala {
    char nome[50];
    struct Sala* esquerda;
    struct Sala* direita;
} Sala;

// Função para criar uma nova sala
Sala* criarSala(const char* nome) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro ao alocar memória!\n");
        exit(1);
    }
    strcpy(novaSala->nome, nome);
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    return novaSala;
}

// Função para explorar a mansão interativamente
void explorarSalas(Sala* salaAtual) {
    if (salaAtual == NULL) {
        printf("\nVocê chegou a uma parede. Não há caminho aqui.\n");
        return;
    }
    
    char opcao;
    
    while (1) {
        printf("\n========================================\n");
        printf("Você está em: %s\n", salaAtual->nome);
        printf("========================================\n");
        
        // Verificar se há caminhos disponíveis
        int temEsquerda = (salaAtual->esquerda != NULL);
        int temDireita = (salaAtual->direita != NULL);
        
        if (!temEsquerda && !temDireita) {
            printf("Esta é uma sala sem saída! Você chegou ao fim do caminho.\n");
            printf("Pressione 's' para sair: ");
            scanf(" %c", &opcao);
            return;
        }
        
        printf("\nOpções de navegação:\n");
        if (temEsquerda) {
            printf("  [e] - Ir para esquerda\n");
        }
        if (temDireita) {
            printf("  [d] - Ir para direita\n");
        }
        printf("  [s] - Sair da exploração\n");
        printf("\nEscolha sua ação: ");
        scanf(" %c", &opcao);
        
        switch (opcao) {
            case 'e':
            case 'E':
                if (temEsquerda) {
                    salaAtual = salaAtual->esquerda;
                } else {
                    printf("\nNão há caminho à esquerda!\n");
                }
                break;
            case 'd':
            case 'D':
                if (temDireita) {
                    salaAtual = salaAtual->direita;
                } else {
                    printf("\nNão há caminho à direita!\n");
                }
                break;
            case 's':
            case 'S':
                printf("\nVocê decidiu sair da exploração.\n");
                return;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    }
}

// Função para liberar a memória da árvore
void liberarArvore(Sala* raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esquerda);
    liberarArvore(raiz->direita);
    free(raiz);
}

// ============================================================================
// 🔍 NÍVEL AVENTUREIRO: ARMAZENAMENTO DE PISTAS COM ÁRVORE DE BUSCA
// ============================================================================

// - Crie uma struct Pista com campo texto (string).
// - Crie uma árvore binária de busca (BST) para inserir as pistas coletadas.
// - Ao visitar salas específicas, adicione pistas automaticamente com inserirBST().
// - Implemente uma função para exibir as pistas em ordem alfabética (emOrdem()).
// - Utilize alocação dinâmica e comparação de strings (strcmp) para organizar.
// - Não precisa remover ou balancear a árvore.
// - Use funções para modularizar: inserirPista(), listarPistas().
// - A árvore de pistas deve ser exibida quando o jogador quiser revisar evidências.

// ============================================================================
// 🧠 NÍVEL MESTRE: RELACIONAMENTO DE PISTAS COM SUSPEITOS VIA HASH
// ============================================================================

// - Crie uma struct Suspeito contendo nome e lista de pistas associadas.
// - Crie uma tabela hash (ex: array de ponteiros para listas encadeadas).
// - A chave pode ser o nome do suspeito ou derivada das pistas.
// - Implemente uma função inserirHash(pista, suspeito) para registrar relações.
// - Crie uma função para mostrar todos os suspeitos e suas respectivas pistas.
// - Adicione um contador para saber qual suspeito foi mais citado.
// - Exiba ao final o "suspeito mais provável" baseado nas pistas coletadas.
// - Para hashing simples, pode usar soma dos valores ASCII do nome ou primeira letra.
// - Em caso de colisão, use lista encadeada para tratar.
// - Modularize com funções como inicializarHash(), buscarSuspeito(), listarAssociacoes().

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

int main() {
    printf("==============================================\n");
    printf("    🔍 DETECTIVE QUEST - A MANSÃO MISTERIOSA\n");
    printf("==============================================\n");
    printf("\nBem-vindo, detetive! Um crime ocorreu nesta mansão.\n");
    printf("Explore os cômodos para encontrar pistas e resolver o mistério.\n");
    
    // Construindo a árvore binária da mansão
    // Estrutura:
    //                    Hall de Entrada
    //                   /                \
    //            Biblioteca           Cozinha
    //           /         \           /       \
    //       Sótão    Escritório  Despensa  Sala de Jantar
    //                     \                      /
    //                   Cofre            Adega
    
    Sala* hall = criarSala("Hall de Entrada");
    hall->esquerda = criarSala("Biblioteca");
    hall->direita = criarSala("Cozinha");
    
    hall->esquerda->esquerda = criarSala("Sótão");
    hall->esquerda->direita = criarSala("Escritório");
    hall->esquerda->direita->direita = criarSala("Cofre");
    
    hall->direita->esquerda = criarSala("Despensa");
    hall->direita->direita = criarSala("Sala de Jantar");
    hall->direita->direita->esquerda = criarSala("Adega");
    
    // Iniciar a exploração
    explorarSalas(hall);
    
    // Liberar memória
    liberarArvore(hall);
    
    printf("\n==============================================\n");
    printf("Obrigado por jogar Detective Quest!\n");
    printf("==============================================\n");
    
    return 0;
}

