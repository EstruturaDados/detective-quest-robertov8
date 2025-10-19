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

// ============================================================================
// 🔍 NÍVEL AVENTUREIRO: ESTRUTURAS DE PISTAS
// ============================================================================

// Estrutura para representar uma pista
typedef struct Pista {
    char texto[100];
    struct Pista* esquerda;
    struct Pista* direita;
} Pista;

// ============================================================================
// PROTÓTIPOS DE FUNÇÕES
// ============================================================================

// Funções do Nível Novato
Sala* criarSala(const char* nome);
void explorarSalas(Sala* salaAtual, Pista** pistasColetadas);
void liberarArvore(Sala* raiz);

// Funções do Nível Aventureiro
Pista* criarPista(const char* texto);
Pista* inserirPista(Pista* raiz, const char* texto);
void listarPistas(Pista* raiz);
void liberarPistas(Pista* raiz);
Pista* verificarPistaNaSala(const char* nomeSala, Pista* pistasColetadas);

// ============================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES - NÍVEL NOVATO
// ============================================================================

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

// Função para explorar a mansão interativamente (com coleta de pistas)
void explorarSalas(Sala* salaAtual, Pista** pistasColetadas) {
    if (salaAtual == NULL) {
        printf("\nVocê chegou a uma parede. Não há caminho aqui.\n");
        return;
    }
    
    char opcao;
    int primeiraVisita = 1;
    
    while (1) {
        printf("\n========================================\n");
        printf("Você está em: %s\n", salaAtual->nome);
        printf("========================================\n");
        
        // Verificar se há pistas na sala (apenas na primeira entrada)
        if (primeiraVisita) {
            *pistasColetadas = verificarPistaNaSala(salaAtual->nome, *pistasColetadas);
            primeiraVisita = 0;
        }
        
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
        printf("  [p] - Ver pistas coletadas\n");
        printf("  [s] - Sair da exploração\n");
        printf("\nEscolha sua ação: ");
        scanf(" %c", &opcao);
        
        switch (opcao) {
            case 'e':
            case 'E':
                if (temEsquerda) {
                    salaAtual = salaAtual->esquerda;
                    primeiraVisita = 1;
                } else {
                    printf("\nNão há caminho à esquerda!\n");
                }
                break;
            case 'd':
            case 'D':
                if (temDireita) {
                    salaAtual = salaAtual->direita;
                    primeiraVisita = 1;
                } else {
                    printf("\nNão há caminho à direita!\n");
                }
                break;
            case 'p':
            case 'P':
                printf("\n========================================\n");
                printf("📋 PISTAS COLETADAS (em ordem alfabética):\n");
                printf("========================================\n");
                if (*pistasColetadas == NULL) {
                    printf("  Nenhuma pista coletada ainda.\n");
                } else {
                    listarPistas(*pistasColetadas);
                }
                printf("========================================\n");
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
// IMPLEMENTAÇÃO DAS FUNÇÕES - NÍVEL AVENTUREIRO
// ============================================================================

// Função para criar uma nova pista
Pista* criarPista(const char* texto) {
    Pista* novaPista = (Pista*)malloc(sizeof(Pista));
    if (novaPista == NULL) {
        printf("Erro ao alocar memória para pista!\n");
        exit(1);
    }
    strcpy(novaPista->texto, texto);
    novaPista->esquerda = NULL;
    novaPista->direita = NULL;
    return novaPista;
}

// Função para inserir uma pista na BST
Pista* inserirPista(Pista* raiz, const char* texto) {
    if (raiz == NULL) {
        printf("\n🔍 Nova pista encontrada: \"%s\"\n", texto);
        return criarPista(texto);
    }
    
    int comparacao = strcmp(texto, raiz->texto);
    
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, texto);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, texto);
    }
    // Se comparacao == 0, a pista já existe, não insere novamente
    
    return raiz;
}

// Função para exibir as pistas em ordem alfabética (travessia em ordem)
void listarPistas(Pista* raiz) {
    if (raiz == NULL) return;
    
    listarPistas(raiz->esquerda);
    printf("  - %s\n", raiz->texto);
    listarPistas(raiz->direita);
}

// Função para liberar memória da árvore de pistas
void liberarPistas(Pista* raiz) {
    if (raiz == NULL) return;
    liberarPistas(raiz->esquerda);
    liberarPistas(raiz->direita);
    free(raiz);
}

// Função para verificar se há pistas em uma sala específica
Pista* verificarPistaNaSala(const char* nomeSala, Pista* pistasColetadas) {
    // Definindo quais salas contêm pistas
    if (strcmp(nomeSala, "Biblioteca") == 0) {
        return inserirPista(pistasColetadas, "Livro com pagina rasgada");
    } else if (strcmp(nomeSala, "Sótão") == 0) {
        return inserirPista(pistasColetadas, "Carta antiga amarelada");
    } else if (strcmp(nomeSala, "Escritório") == 0) {
        return inserirPista(pistasColetadas, "Documento assinado");
    } else if (strcmp(nomeSala, "Cofre") == 0) {
        return inserirPista(pistasColetadas, "Joia valiosa escondida");
    } else if (strcmp(nomeSala, "Cozinha") == 0) {
        return inserirPista(pistasColetadas, "Faca com manchas");
    } else if (strcmp(nomeSala, "Despensa") == 0) {
        return inserirPista(pistasColetadas, "Frasco de veneno");
    } else if (strcmp(nomeSala, "Sala de Jantar") == 0) {
        return inserirPista(pistasColetadas, "Taca quebrada");
    } else if (strcmp(nomeSala, "Adega") == 0) {
        return inserirPista(pistasColetadas, "Garrafa de vinho aberta");
    }
    
    return pistasColetadas;
}

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
    printf("\n💡 Dica: Use [p] durante a exploração para ver suas pistas!\n");
    
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
    
    // Inicializar árvore de pistas (BST)
    Pista* pistasColetadas = NULL;
    
    // Iniciar a exploração com coleta de pistas
    explorarSalas(hall, &pistasColetadas);
    
    // Exibir resumo final das pistas
    printf("\n==============================================\n");
    printf("📋 RESUMO DA INVESTIGAÇÃO\n");
    printf("==============================================\n");
    if (pistasColetadas == NULL) {
        printf("Nenhuma pista foi coletada.\n");
    } else {
        printf("Pistas coletadas (em ordem alfabética):\n\n");
        listarPistas(pistasColetadas);
    }
    printf("==============================================\n");
    
    // Liberar memória
    liberarArvore(hall);
    liberarPistas(pistasColetadas);
    
    printf("\n==============================================\n");
    printf("Obrigado por jogar Detective Quest!\n");
    printf("==============================================\n");
    
    return 0;
}

