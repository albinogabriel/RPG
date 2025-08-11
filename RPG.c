#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#define BRONZE_POR_PRATA 100
#define PRATA_POR_OURO 100
#define BRONZE_POR_OURO (BRONZE_POR_PRATA * PRATA_POR_OURO)

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
};

struct classes{
    char classe[20];
    int hp;
    int defesa;
    int ataque;
};

// Agora moedas é armazenada em BRONZE apenas
struct moedas{
    int bronzeTotal;
};

struct prota personagem;
struct classes classe;
struct moedas moedas;

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
            fgets(classe.classe, sizeof(classe.classe), stdin);
            classe.classe[strcspn(classe.classe, "\n")] = 0;
            strToLower(classe.classe);

        if (strcmp(classe.classe, "guerreiro") == 0) {
            classe.hp = 150;
            classe.defesa = 8;
            classe.ataque = 10;
            break;
        } else if (strcmp(classe.classe, "mago") == 0) {
            classe.hp = 100;
            classe.defesa = 5;
            classe.ataque = 15;
            break;
        } else if (strcmp(classe.classe, "ladino") == 0) {
            classe.hp = 120;
            classe.defesa = 7;
            classe.ataque = 12;
            break;
        } else {
            printf("Você tem certeza de que era isso? Tente se lembrar!\n");
        }
    }

    esperar(2);

    printf("Classe escolhida: %s\n", classe.classe);
    printf("HP: %d, Ataque: %d, Defesa: %d\n", classe.hp, classe.ataque, classe.defesa);

    esperar(2);

    printf("Muito bom %s! Meu nome é Favern! É um prazer conhecer você!\n", personagem.nome);
}

//HISTÓRIA
void iniHist() {
    printf("%s, vou te contar um pouco da história desse vilarejo...\n", personagem.nome);
    esperar(1);
    printf("Há muito tempo, esse vilarejo foi criado como centro de trocas até que um dragão veio e destruiu essa aldeia...\n");
    esperar(2);
    printf("Agora a duas semanas atrás, o mesmo dragão voltou e rapitou nossa princesa, Julia.\n");
    esperar(1);
    printf("...\n");
    esperar(1);
    printf("...\n");
    esperar(1);
    printf("Calma...\n");
    esperar(1);
    printf("%s! VOCÊ PODE SALVAR NOSSA PRINCESA!\n", personagem.nome);
    printf("VOCÊ COMO O INCRÍVEL %s QUE VOCÊ É TENHO CERTEZA DE QUE CONSEGUIRÁ\n", classe.classe);
    esperar(4);
    printf("Esse vilarejo se chama Jeakis e fica ao Leste do maior comércio, Gudsa\n");
    esperar(1);
    printf("Tiveram que reconstruir um lugar para comércios depois que aqui foi destruído...\n");
    esperar(2);
    printf("Vou te dar 10 moedas de prata para começar sua jornada, o dragão foi a Nordeste daqui, %s, TRAGA NOSSA PRINCESA DEVOLTA POR FAVOR!\n", personagem.nome);
    esperar(2);
    
    adicionarMoedas(0, 10, 0);
    printf("Você recebeu 10 moedas de prata de Favern!\n");
    mostrarMoedas();
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

    return 0;
}