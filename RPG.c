#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
    #define ESPERAR(segundos) Sleep(segundos * 1000)
#else
    #include <unistd.h>
    #define ESPERAR(segundos) sleep(segundos)
#endif

// Constantes do jogo
#define BRONZE_POR_PRATA 100
#define PRATA_POR_OURO 100
#define BRONZE_POR_OURO (BRONZE_POR_PRATA * PRATA_POR_OURO)
#define MAX_NOME 50
#define MAX_CLASSE 20

// Estruturas de dados
typedef struct {
    char nome[MAX_NOME];
    char classe[MAX_CLASSE];
    int hp;
    int defesa;
    int ataque;
} Personagem;

typedef struct {
    int bronzeTotal;
} Moedas;

typedef struct {
    char nome[30];
    int hp;
    int ataque;
    int defesa;
} Inimigo;

// Variáveis globais
Personagem personagem;
Moedas moedas;
Inimigo goblin = {"Goblin", 60, 6, 3};
Inimigo esqueleto = {"Esqueleto", 80, 8, 5};

// Protótipos de funções
void configurarJogo();
void iniciarJogo();
void mostrarMoedas();
void adicionarMoedas(int ouro, int prata, int bronze);
void batalha(Inimigo *inimigo);
void historiaInicial();
void areaJeakis();
void continuarJornada();
void areaGudsa();
void explorarFloresta();
void procurarInimigos();
void lojaGuerreiro();
void lojaMago();
void lojaLadino();
void mostrarStatus();
int lerOpcao(const char *mensagem);
void pausa();

// Função principal
int main() {
    srand(time(NULL));
    configurarJogo();
    iniciarJogo();
    return 0;
}

void configurarJogo() {
    moedas.bronzeTotal = 0;
    #ifdef _WIN32
        system("chcp 65001 > nul");
    #endif
}

void iniciarJogo() {
    printf("\t== RPG BOLADO ==\n");
    printf("1. Começar jogo\n");
    printf("0. Sair\n");
    
    int opcao = lerOpcao("Escolha uma opção: ");
    if (opcao != 1) exit(0);
    
    printf("\nINICIANDO...\n");
    ESPERAR(2);
    
    // Criação do personagem
    printf("Oh, você acordou!\n");
    ESPERAR(1);
    printf("Você lembra de algo?\n");
    ESPERAR(2);
    printf("Entendo...\n");
    ESPERAR(1);
    
    // Nome do personagem
    printf("Qual é seu nome? (máximo %d caracteres): ", MAX_NOME-1);
    fgets(personagem.nome, MAX_NOME, stdin);
    personagem.nome[strcspn(personagem.nome, "\n")] = 0;
    
    // Classe do personagem
    int classeValida = 0;
    while (!classeValida) {
        printf("O que você é (guerreiro, mago ou ladino)? ");
        fgets(personagem.classe, MAX_CLASSE, stdin);
        personagem.classe[strcspn(personagem.classe, "\n")] = 0;
        
        // Converter para minúsculas
        for (int i = 0; personagem.classe[i]; i++) {
            if (personagem.classe[i] >= 'A' && personagem.classe[i] <= 'Z') {
                personagem.classe[i] += 'a' - 'A';
            }
        }
        
        if (strcmp(personagem.classe, "guerreiro") == 0) {
            personagem.hp = 150;
            personagem.defesa = 8;
            personagem.ataque = 10;
            classeValida = 1;
        } else if (strcmp(personagem.classe, "mago") == 0) {
            personagem.hp = 100;
            personagem.defesa = 5;
            personagem.ataque = 15;
            classeValida = 1;
        } else if (strcmp(personagem.classe, "ladino") == 0) {
            personagem.hp = 120;
            personagem.defesa = 7;
            personagem.ataque = 12;
            classeValida = 1;
        } else {
            printf("Classe inválida! Tente novamente.\n");
        }
    }
    
    printf("\n%s, você é um %s com HP: %d, Ataque: %d, Defesa: %d\n", 
           personagem.nome, personagem.classe, personagem.hp, personagem.ataque, personagem.defesa);
    ESPERAR(2);
    
    // História inicial
    historiaInicial();
    
    // Área principal do jogo
    areaJeakis();
}

void mostrarMoedas() {
    int ouro = moedas.bronzeTotal / BRONZE_POR_OURO;
    int prata = (moedas.bronzeTotal % BRONZE_POR_OURO) / BRONZE_POR_PRATA;
    int bronze = moedas.bronzeTotal % BRONZE_POR_PRATA;
    printf("Você tem: %d ouro, %d prata, %d bronze\n", ouro, prata, bronze);
}

void adicionarMoedas(int ouro, int prata, int bronze) {
    moedas.bronzeTotal += ouro * BRONZE_POR_OURO;
    moedas.bronzeTotal += prata * BRONZE_POR_PRATA;
    moedas.bronzeTotal += bronze;
}

void batalha(Inimigo *inimigo) {
    printf("\n=== BATALHA CONTRA %s ===\n", inimigo->nome);
    
    Inimigo inimigoCopia = *inimigo; // Faz uma cópia para não modificar o original
    
    while (personagem.hp > 0 && inimigoCopia.hp > 0) {
        // Turno do jogador
        int variacao = (rand() % personagem.ataque) - 2;
        int danoJogador = (personagem.ataque - inimigoCopia.defesa) + variacao;
        if (danoJogador < 1) danoJogador = 1;
        
        printf("\n%s ataca %s causando %d de dano!\n", 
               personagem.nome, inimigoCopia.nome, danoJogador);
        inimigoCopia.hp -= danoJogador;
        
        if (inimigoCopia.hp <= 0) {
            printf("\nVocê derrotou o %s!\n", inimigoCopia.nome);
            adicionarMoedas(0, 0, 20);
            printf("Ganhou 20 moedas de bronze!\n");
            mostrarMoedas();
            break;
        }
        
        ESPERAR(2);
        
        // Turno do inimigo
        int variacaoInimigo = (rand() % inimigoCopia.ataque) - 2;
        int danoInimigo = (inimigoCopia.ataque - personagem.defesa) + variacaoInimigo;
        if (danoInimigo < 1) danoInimigo = 1;
        
        printf("%s ataca você causando %d de dano!\n", 
               inimigoCopia.nome, danoInimigo);
        personagem.hp -= danoInimigo;
        
        if (personagem.hp <= 0) {
            printf("\nVocê foi derrotado... Fim de jogo.\n");
            exit(0);
        }
        
        ESPERAR(2);
        
        printf("HP %s: %d | HP %s: %d\n", 
               personagem.nome, personagem.hp, inimigoCopia.nome, inimigoCopia.hp);
        ESPERAR(2);
    }
}

void historiaInicial() {
    printf("\n%s, vou te contar sobre este vilarejo...\n", personagem.nome);
    ESPERAR(2);
    printf("Há muito tempo, este vilarejo era um centro de trocas até que um dragão o destruiu...\n");
    ESPERAR(3);
    printf("Duas semanas atrás, o mesmo dragão voltou e raptou nossa princesa, Julia.\n");
    ESPERAR(3);
    printf("%s! VOCÊ PODE SALVAR NOSSA PRINCESA!\n", personagem.nome);
    ESPERAR(2);
    printf("Este vilarejo se chama Jeakis e fica a Leste do maior comércio, Gudsa\n");
    ESPERAR(3);
    printf("Vou te dar 10 moedas de prata para começar sua jornada!\n");
    ESPERAR(2);
    
    adicionarMoedas(0, 10, 0);
    printf("Você recebeu 10 moedas de prata!\n");
    mostrarMoedas();
    pausa();
}

void areaJeakis() {
    int opcao;
    
    do {
        printf("\n=== JEAKIS ===\n");
        printf("1. Ver Status\n");
        printf("2. Ver Moedas\n");
        printf("3. Continuar Jornada\n");
        printf("0. Sair do Jogo\n");
        
        opcao = lerOpcao("Escolha uma opção: ");
        
        switch (opcao) {
            case 1:
                mostrarStatus();
                break;
            case 2:
                mostrarMoedas();
                break;
            case 3:
                printf("\nVocê sai do vilarejo...\n");
                ESPERAR(2);
                continuarJornada();
                break;
            case 0:
                printf("\nSaindo do jogo... Até logo!\n");
                break;
            default:
                printf("\nOpção inválida!\n");
                break;
        }
    } while (opcao != 0);
}

void continuarJornada() {
    int opcao;
    
    do {
        printf("\n=== ÁREA DE EXPLORAÇÃO ===\n");
        printf("1. Explorar a floresta\n");
        printf("2. Ir para Gudsa\n");
        printf("3. Procurar inimigos\n");
        printf("0. Voltar para Jeakis\n");
        
        opcao = lerOpcao("Escolha uma opção: ");
        
        switch (opcao) {
            case 1:
                explorarFloresta();
                break;
            case 2:
                printf("\nVocê caminha até Gudsa...\n");
                ESPERAR(2);
                areaGudsa();
                break;
            case 3:
                procurarInimigos();
                break;
            case 0:
                printf("\nVoltando para Jeakis...\n");
                ESPERAR(2);
                break;
            default:
                printf("\nOpção inválida!\n");
                break;
        }
    } while (opcao != 0);
}

void explorarFloresta() {
    printf("\nVocê adentra a floresta...\n");
    ESPERAR(2);
    
    int evento = rand() % 10;
    
    if (evento < 6) { // 60% de chance de encontrar inimigo
        Inimigo *inimigo = (rand() % 2 == 0) ? &goblin : &esqueleto;
        printf("Você encontrou um %s!\n", inimigo->nome);
        ESPERAR(2);
        batalha(inimigo);
    } else if (evento < 9) { // 30% de chance de encontrar frutinha
        int cura = 15 + (rand() % 6); // Entre 15 e 20 de cura
        printf("Você achou uma frutinha! Recupera %d de HP.\n", cura);
        personagem.hp += cura;
        printf("Seu HP agora é: %d\n", personagem.hp);
    } else { // 10% de chance de não encontrar nada
        printf("Você explorou a área mas não encontrou nada interessante.\n");
    }
    
    pausa();
}

void procurarInimigos() {
    printf("\nProcurando por inimigos...\n");
    ESPERAR(2);
    
    if (rand() % 100 < 70) { // 70% de chance de encontrar inimigo
        Inimigo *inimigo = (rand() % 2 == 0) ? &goblin : &esqueleto;
        printf("Você encontrou um %s!\n", inimigo->nome);
        ESPERAR(2);
        batalha(inimigo);
    } else {
        printf("Nenhum inimigo foi encontrado!\n");
    }
    
    pausa();
}

void areaGudsa() {
    printf("\n=== GUDSA - CIDADE COMERCIAL ===\n");
    
    // Chance de encontro aleatório ao entrar em Gudsa
    if (rand() % 2 == 0) {
        Inimigo *inimigo = (rand() % 2 == 0) ? &goblin : &esqueleto;
        printf("Um %s te atacou no caminho!\n", inimigo->nome);
        ESPERAR(2);
        batalha(inimigo);
    }
    
    int opcao;
    
    do {
        printf("\n=== GUDSA ===\n");
        printf("1. Ver Status\n");
        printf("2. Ver Moedas\n");
        printf("3. Visitar Loja\n");
        printf("4. Explorar a floresta\n");
        printf("5. Procurar Inimigos\n");
        printf("0. Voltar para Jeakis\n");
        
        opcao = lerOpcao("Escolha uma opção: ");
        
        switch (opcao) {
            case 1:
                mostrarStatus();
                break;
            case 2:
                mostrarMoedas();
                break;
            case 3:
                if (strcmp(personagem.classe, "guerreiro") == 0) {
                    lojaGuerreiro();
                } else if (strcmp(personagem.classe, "mago") == 0) {
                    lojaMago();
                } else {
                    lojaLadino();
                }
                break;
            case 4:
                explorarFloresta();
                break;
            case 5:
                procurarInimigos();
                break;
            case 0:
                printf("\nVoltando para Jeakis...\n");
                ESPERAR(2);
                break;
            default:
                printf("\nOpção inválida!\n");
                break;
        }
    } while (opcao != 0);
}

void lojaGuerreiro() {
    printf("\n=== LOJA DE EQUIPAMENTOS PARA GUERREIRO ===\n");
    printf("1. Espada Longa (+3 de ataque) - 5 prata\n");
    printf("2. Armadura de Placas (+5 de defesa) - 8 prata\n");
    printf("3. Poção de Cura (+30 HP) - 3 prata\n");
    printf("0. Sair\n");
    
    int opcao = lerOpcao("Escolha um item: ");
    int precoPrata = 0;
    int valor = 0;
    char *item = NULL;
    
    switch (opcao) {
        case 1:
            precoPrata = 5;
            item = "Espada Longa";
            valor = 3;
            break;
        case 2:
            precoPrata = 8;
            item = "Armadura de Placas";
            valor = 5;
            break;
        case 3:
            precoPrata = 3;
            item = "Poção de Cura";
            // Para poção, valor é a quantidade de cura
            break;
        case 0:
            return;
        default:
            printf("Item inválido!\n");
            return;
    }
    
    int precoBronze = precoPrata * BRONZE_POR_PRATA;
    
    if (moedas.bronzeTotal >= precoBronze) {
        moedas.bronzeTotal -= precoBronze;
        printf("Você comprou: %s\n", item);
        
        if (opcao == 3) {
            personagem.hp += 30;
            printf("HP recuperado! Seu HP agora é: %d\n", personagem.hp);
        } else if (opcao == 1) {
            personagem.ataque += valor;
            printf("Seu ataque agora é: %d\n", personagem.ataque);
        } else if (opcao == 2) {
            personagem.defesa += valor;
            printf("Sua defesa agora é: %d\n", personagem.defesa);
        }
        
        mostrarMoedas();
    } else {
        printf("Você não tem moedas suficientes!\n");
    }
    
    pausa();
}

void lojaMago() {
    printf("\n=== LOJA DE ITENS MÁGICOS ===\n");
    printf("1. Cajado Arcano (+4 de ataque) - 6 prata\n");
    printf("2. Robes Mágicas (+3 de defesa) - 5 prata\n");
    printf("3. Poção de Mana (recupera 2 feitiços) - 4 prata\n");
    printf("0. Sair\n");
    
    // Implementação similar à lojaGuerreiro
    printf("Loja de Mago em desenvolvimento...\n");
    pausa();
}

void lojaLadino() {
    printf("\n=== LOJA DE EQUIPAMENTOS DE LADINO ===\n");
    printf("1. Adagas Duplas (+4 de ataque) - 5 prata\n");
    printf("2. Armadura de Couro (+4 de defesa) - 6 prata\n");
    printf("3. Poção de Invisibilidade (escape automático) - 7 prata\n");
    printf("0. Sair\n");
    
    // Implementação similar à lojaGuerreiro
    printf("Loja de Ladino em desenvolvimento...\n");
    pausa();
}

void mostrarStatus() {
    printf("\n=== STATUS ===\n");
    printf("Nome: %s\n", personagem.nome);
    printf("Classe: %s\n", personagem.classe);
    printf("HP: %d\n", personagem.hp);
    printf("Ataque: %d\n", personagem.ataque);
    printf("Defesa: %d\n", personagem.defesa);
    pausa();
}

int lerOpcao(const char *mensagem) {
    float temp;
    printf("%s", mensagem);
    if (scanf("%f", &temp) != 1) {
        printf("Entrada inválida!\n");
        while (getchar() != '\n');
        return -1;
    }
    while (getchar() != '\n');
    return (int)floor(temp);
}

void pausa() {
    printf("\nPressione Enter para continuar...");
    getchar();
}