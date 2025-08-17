#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define BRONZE_POR_PRATA 100
#define PRATA_POR_OURO 100
#define BRONZE_POR_OURO (BRONZE_POR_PRATA * PRATA_POR_OURO)

// FUNÇÃO PARA LER FLOAT COMO INT (EVITA BUGS COM VÍRGULA)
int lerIntComFloor(const char *mensagem) {
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

// FUNÇÃO DE ESPERAR
void esperar(int segundos) {
    #ifdef _WIN32
        Sleep(segundos * 1000);
    #else
        sleep(segundos);
    #endif
}

// Função para converter string para minúsculas
void strToLower(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';
    }
}

struct prota{
    char nome[200]; 
    char nclasse[20];
    int hp;
    int defesa;
    int ataque;
};

// Agora moedas é armazenada em BRONZE apenas
struct moedas{
    int bronzeTotal;
};

struct inimigos {
    char nome[30];
    int hp;
    int ataque;
    int defesa;
};

//variavel personagem
struct prota personagem;

//vaiavel moeda
struct moedas moedas;

//vaiaveis para inimigos
struct inimigos goblin = {"Goblin", 60, 6, 3};
struct inimigos esqueleto = {"Esqueleto", 80, 8, 5};

// Função para mostrar moedas formatadas
void mostrarMoedas() {
    int ouro = moedas.bronzeTotal / BRONZE_POR_OURO;
    int prata = (moedas.bronzeTotal % BRONZE_POR_OURO) / BRONZE_POR_PRATA;
    int bronze = moedas.bronzeTotal % BRONZE_POR_PRATA;

    printf("Você tem: %d ouro, %d prata, %d bronze\n", ouro, prata, bronze);
}

// Função para adicionar moedas (em bronze)
void adicionarMoedas(int ouro, int prata, int bronze) {
    moedas.bronzeTotal += ouro * BRONZE_POR_OURO;
    moedas.bronzeTotal += prata * BRONZE_POR_PRATA;
    moedas.bronzeTotal += bronze;
}

//SISTEMA DE LUTA
void batalha(struct prota *personagem, struct inimigos *inimigos) {
    printf("\nUMA BATALHA INCIOU\n");

    while (personagem->hp > 0 && inimigos->hp > 0)
    {
        //FUNÇÃO DENTRO DO WHILE PARA O DANO DO JOGADOR E DO INIMIGO
        int variacao = (rand() % personagem->ataque) - 2;
        int danoJogador = (personagem->ataque - inimigos->defesa) + variacao;
        if(danoJogador < 1) danoJogador = 1;

        int variacaoInimigo = (rand() % inimigos->ataque) - 2;
        int danoInimigo = (inimigos->ataque - personagem->defesa) + variacaoInimigo;
        if(danoInimigo < 1) danoInimigo = 1;

        //TURNO DO JOGADOR
        printf("\n%s você deu %d de dano!\n", personagem->nome, danoJogador);
        inimigos->hp - danoJogador;
        if(inimigos->hp <= 0){
            printf("\n%s, parabéns você derrotou um %s", personagem->nome, inimigos->nome);
            adicionarMoedas(0, 0, 20);
            printf("Foi adicionado 20 moedas de bronze!\n");
            mostrarMoedas();
            break;
        }

    esperar(2);

        //TURNO DO INIMIGO
        printf("\nVocê recebeu %d de dano!\n", danoInimigo);
        personagem->hp - danoInimigo;
        if(personagem->hp <= 0){
            printf("Você foi derrotado...\n");
        }

    esperar(1);

        printf("HP %s: %d | HP %s: %d", personagem->nome, personagem->hp, inimigos->nome, inimigos->hp);
    }
}

//START
void start() {
    int start;

    printf("\t==RPG BOLADO==\n");
    printf("DIGITE 1 PARA COMEÇAR: ");
    scanf("%d", &start);

    getchar();

    switch (start)
    {
    case 1: printf("\nINICIANDO...\n"); break;
    
    default: printf("OPÇÃO INVÁLIDA\n"); break;
    }
}

//PERSONAGEM
void persona() {
    printf("Oh, você acordou!\n");
    esperar(1);
    printf("Hummmmmm \n");
    esperar(1);
    printf("Você lembra de algo?\n");
    esperar(5);
    printf("Entendo...\n");
    esperar(2);

    printf("Hummmmm, ok então qual é seu nome? \n");
    
    while (1){
        printf("Digite seu nome (máximo de 9 carácteres): ");

        fgets(personagem.nome, sizeof(personagem.nome), stdin);
        personagem.nome[strcspn(personagem.nome, "\n")] = 0;

        if(strlen(personagem.nome) > 9){
            printf("QUE NOME GRANDE! Você tem algum apelido?\n");
        }else if(strlen(personagem.nome) == 0) {
            printf("Você não se lembra? Tente se lembrar!\n");
        }else {
        break;
        }
    }

    esperar(2);

    printf("Muito bem! %s!\n", personagem.nome);
    esperar(1);

    while(1) {
        printf("O que você é (guerreiro, mago ou ladino)? ");
            fgets(personagem.nclasse, sizeof(personagem.nclasse), stdin);
            personagem.nclasse[strcspn(personagem.nclasse, "\n")] = 0;
            strToLower(personagem.nclasse);

        if (strcmp(personagem.nclasse, "guerreiro") == 0) {
            personagem.hp = 150;
            personagem.defesa = 8;
            personagem.ataque = 10;
            break;
        } else if (strcmp(personagem.nclasse, "mago") == 0) {
            personagem.hp = 100;
            personagem.defesa = 5;
            personagem.ataque = 15;
            break;
        } else if (strcmp(personagem.nclasse, "ladino") == 0) {
            personagem.hp = 120;
            personagem.defesa = 7;
            personagem.ataque = 12;
            break;
        } else {
            printf("Você tem certeza de que era isso? Tente se lembrar!\n");
        }
    }

    esperar(2);

    printf("Classe escolhida: %s\n", personagem.nclasse);
    printf("HP: %d, Ataque: %d, Defesa: %d\n", personagem.hp, personagem.ataque, personagem.defesa);

    esperar(2);

    printf("Muito bom %s! Meu nome é Favern! É um prazer conhecer você!\n", personagem.nome);
}

//HISTÓRIA
void iniHist() {
    printf("%s, vou te contar um pouco da história desse vilarejo...\n", personagem.nome);
    esperar(3);
    printf("Há muito tempo, esse vilarejo foi criado como centro de trocas até que um dragão veio e destruiu essa aldeia...\n");
    esperar(5);
    printf("Agora a duas semanas atrás, o mesmo dragão voltou e rapitou nossa princesa, Julia.\n");
    esperar(3);
    printf("...\n");
    esperar(1);
    printf("...\n");
    esperar(1);
    printf("Calma...\n");
    esperar(3);
    printf("%s! VOCÊ PODE SALVAR NOSSA PRINCESA!\n", personagem.nome);
    esperar(2);
    printf("VOCÊ COMO O INCRÍVEL %s QUE VOCÊ É TENHO CERTEZA DE QUE CONSEGUIRÁ\n", personagem.nclasse);
    esperar(4);
    printf("Esse vilarejo se chama Jeakis e fica ao Leste do maior comércio, Gudsa\n");
    esperar(3);
    printf("Tiveram que reconstruir um lugar para comércios depois que aqui foi destruído...\n");
    esperar(3);
    printf("Vou te dar 10 moedas de prata para começar sua jornada, o dragão foi a Nordeste daqui, %s, TRAGA NOSSA PRINCESA DEVOLTA POR FAVOR!\n", personagem.nome);
    esperar(5);
    
    adicionarMoedas(0, 10, 0);
    printf("Você recebeu 10 moedas de prata de Favern!\n");
    mostrarMoedas();
}

//CONTINUAR JORNADA
void continuar () {
    int opcao;

    printf("\nVocê saí do vilarejo...\n");
    esperar(2);

    printf("O que deseja fazer?\n");

    printf("1. Explorar a floresta\n");
    printf("2. Ir para Gudsa\n");
    printf("3. Procurar inimigos\n");
    printf("0. Voltar para o Menu\n");

    opcao = lerIntComFloor("Escolha uma opção: ");

    switch (opcao)
    {
    case 1:
        printf("Você adentrou a floresta...");
        break;

    case 2:
        printf("Você caminha até Gudsa");
        break;

    case 3:
        printf("Você procura por inimigos");
        break;
    
    default:
        printf("\nOpção Inválida\n");
        break;
    }

}

//MENU
void menu () {
    int opcao;

do{
    printf("==MENU==\n");
    printf("1. Ver Status\n");
    printf("2. Ver Moedas\n");
    printf("3. Continuar Jornada\n");
    printf("0. Sair do Jogo\n");

    opcao = lerIntComFloor("Escolha uma opção: ");

    switch (opcao)
    {
    case 1:
        printf("\n==Status==\n");
        printf("Nome: %s\n", personagem.nome);
        printf("Classe: %s\n", personagem.nclasse);
        printf("HP: %d | Def: %d | Atq: %d\n", personagem.hp, personagem.defesa, personagem.ataque);
        break;

    case 2:
        printf("\n==Moedas==\n");
        mostrarMoedas();
        break;
    
    case 3:
        continuar();
        break;
    
    case 0:
        printf("\nSaindo do jogo... Até a próxima\n");
        break;

    default:
        printf("\nOpção inválida!\n");
        break;
    }
}while (opcao != 0);
}

//FUNÇÃO PRINCIPAL
int main() {
    setlocale(LC_ALL, "Portuguese");

    moedas.bronzeTotal = 0;

    start();
    esperar(4);
    persona();
    esperar(3);
    iniHist();

    menu();

    return 0;
}