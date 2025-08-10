#include <stdio.h>
#include <string.h>
#include <locale.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void esperar(int segundos) {
    #ifdef _WIN32
        Sleep(segundos * 1000);
    #else
        sleep(segundos);
    #endif
}


struct prota
{
    char nome[200];
    int hp;
    int ataque;
    int defesa;
    int ouro;
};

struct prota personagem;

//MENU
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

    printf("Muito bem! %s\n", personagem.nome);
    esperar(1);
    printf("Vou te contar um pouco da história desse vilarejo!\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    start();

    esperar(4);

    persona();
}