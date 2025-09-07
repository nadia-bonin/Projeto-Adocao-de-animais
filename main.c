// PowerShell ou terminal
// gcc main.c animal.c -o animal.exe || gcc main.c cliente.c -o cliente.exe || gcc main.c cliente.c animal.c -o main.exe
// .\animal.exe || .\cliente.exe || .\main.exe

#include "animal.h"
#include "cliente.h"
#include <stdio.h>

extern int menuAnimal();
extern void Menucliente();

int main() {

int escolha_main;

    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Entrar no Menu Animal\n");
        printf("2. Entrar no Menu Cliente\n");
        printf("3. Sair\n");
        printf("Digite uma opcao: ");
        scanf("%d", &escolha_main);
        getchar();

        switch (escolha_main) {
            case 1:
                menuAnimal();
                break;
            case 2:
                Menucliente();
                break;
            case 3:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (escolha_main != 3);

    return 0;
}