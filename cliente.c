#include <stdio.h>
#include <string.h>

#include "config.h"
#include "cliente.h"

int cadastrarPerfil();
struct Cliente LerDadosCliente();
int VerificacaoCPF(const char *cpf);
int VerificacaoUsuario();

void Menucliente()
{
    int opcao;

    do {
        printf("\n--- Menu do Cliente ---\n");
        printf("1. Cadastrar perfil\n");
        printf("2. Sair\n");
        printf("Digite uma opcao: ");

        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarPerfil();
                break;
            case 2:
                printf("Saindo do menu.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 2);
}

int cadastrarPerfil()
{

    struct Cliente cliente = LerDadosCliente();

    FILE *arquivo_cliente = fopen(ArqAdotante, "a+");
    if (arquivo_cliente == NULL) {
        printf("Erro ao abrir o arquivo adotante\n");
        return 0;
    }

    if (VerificacaoUsuario(cliente.CPF)) {
        printf("CPF ja cadastrado. Tente outro CPF.\n");
        fclose(arquivo_cliente);
        return 0;  // Retorna 0 para não continuar o cadastro
    }

    fprintf(arquivo_cliente, "%s|%s\n", cliente.nome, cliente.CPF);

    fclose(arquivo_cliente);

    return 1;
}

struct Cliente LerDadosCliente()
{
    struct Cliente cliente;
    printf("Cadastrar um adotante novo!\n");

    printf("Digite o nome do adotante: ");
    fgets(cliente.nome, sizeof(cliente.nome), stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';
    int CPFValido;
    do {
        printf("Digite o CPF do adotante, SEM '. ou /': ");
        fgets(cliente.CPF, sizeof(cliente.CPF), stdin);
        cliente.CPF[strcspn(cliente.CPF, "\n")] = '\0';

        CPFValido = VerificacaoCPF(cliente.CPF);
        if (CPFValido == 0) {
            printf("CPF invalido! Tente novamente.\n");
        }
    } while (CPFValido != 1);

    return cliente;
}


int VerificacaoCPF(const char *cpf)
{

    if (strlen(cpf) != 11)
    {
        return 0;
    }

    for (int i = 0; i < 11; i++)
    {
        if (cpf[i] < '0' || cpf[i] > '9')
        {
            return 0;
        }
    }

    int todos_iguais = 1;
    for (int i = 1; i < 11; i++)
    {
        if (cpf[i] != cpf[0])
        {
            todos_iguais = 0;
            break;
        }
    }
    if (todos_iguais)
    {
        return 0;
    }
    int soma = 0;
    for (int i = 0; i < 9; i++)
    {
        soma += (cpf[i] - '0') * (10 - i);
    }
    int primeiro_digito = (soma * 10) % 11;
    if (primeiro_digito == 10)
    {
        primeiro_digito = 0;
    }
    if (primeiro_digito != (cpf[9] - '0'))
    {
        return 0;
    }

    soma = 0;
    for (int i = 0; i < 10; i++)
    {
        soma += (cpf[i] - '0') * (11 - i);
    }
    int segundo_digito = (soma * 10) % 11;
    if (segundo_digito == 10)
    {
        segundo_digito = 0;
    }
    if (segundo_digito != (cpf[10] - '0'))
    {
        return 0;
    }

    return 1;
}

int VerificacaoUsuario(const char *cpf) {
    FILE *arquivo_cliente = fopen(ArqAdotante, "r");
    if (arquivo_cliente == NULL) {
        printf("Erro ao abrir o arquivo adotante.txt\n");
        return 0;
    }

    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo_cliente) != NULL) {
        char *cpf_arquivo = strchr(linha, '|');
        if (cpf_arquivo != NULL) {
            cpf_arquivo++;
            cpf_arquivo[strcspn(cpf_arquivo, "\n")] = '\0';
            if (strcmp(cpf, cpf_arquivo) == 0) {
                fclose(arquivo_cliente);
                return 1;
            }
        }
    }

    fclose(arquivo_cliente);
    return 0;
}