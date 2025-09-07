#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include "animal.h"
#include "config.h"

void VaiParaIncluirAnimal();
void VaiParaListarAnimais();
void VaiParaExcluirAnimal();

void VaiParaIncluirAnimal();
void MostrarAnimal(struct Animal* animal);
void VaiParaListarAnimais();
void VaiParaExcluirAnimal();
void ListarAnimais();
struct Animal LerDadosAnimalX();
int IncluirNovoAnimalX(struct Animal* animal);
int LerUltimoIDX(FILE* arquivo_animal);
int IDDesejado();
int ExcluirAnimalPorID(int iD);

int menuAnimal() {

    while(1)
    {
        char opcao = ' ';

        printf("\n1. Incluir Animal\n");
        printf("2. Excluir Animal\n");
        printf("3. Listar Animais\n");
        printf("4. Retornar\n");

        printf("Digite uma opcao: ");
        do {
            opcao = getchar();
        }
        while(opcao == '\n');


        switch (opcao)
        {
            case '1':
                VaiParaIncluirAnimal();
                break;
            
            case '2':
                VaiParaExcluirAnimal();
                break;
            
            case '3':
                VaiParaListarAnimais();
                break;
            
            case '4':
                return 1;

            default:
                printf("... Tente novamente");
                break;
        }
    }
}

void VaiParaIncluirAnimal()
{
    struct Animal animal = LerDadosAnimalX();
    IncluirNovoAnimalX(&animal);
}

void VaiParaListarAnimais()
{
    ListarAnimais();
}

void VaiParaExcluirAnimal()
{
    int iD;
    int excluido;
    printf("Excluindo animal....");
    ListarAnimais();
    iD = IDDesejado();
    excluido = ExcluirAnimalPorID(iD);
    if (excluido) {
        printf("Animal com ID %d excluido com sucesso.\n", iD);
    } else {
        printf("Animal com ID %d nao encontrado.\n", iD);
    }
}

void MostrarAnimal(struct Animal* animal)
{
    printf("\nID: %d\n", animal->ID);
    if (animal->especie == Gato)
        printf("Especie: Gato\n");
    else
        printf("Especie: Cachorro\n");
    if (animal->status == Disponivel)
        printf("Status: Disponivel\n");
    else
        printf("Status: Adotado\n");
    printf("Nome: %s\n", animal->nome);
    printf("Rava: %s\n", animal->raca);
    printf("Descricao: %s\n", animal->descricao);
}

void ListarAnimais()
{
    printf("Listando animal....\n");
    struct Animal animal;
    char str[300];
    
    FILE *arquivo_animal = fopen(ArqAnimal, "a+");
    if (arquivo_animal == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    fseek(arquivo_animal, 0, SEEK_SET);

    while (fgets(str, sizeof(str), arquivo_animal) != NULL) {
        char *token = strtok(str, "|");
        
        if (token != NULL) {
            animal.ID = atoi(token);
        }

        token = strtok(NULL, "|");
        if (token != NULL) {
            animal.especie = (enum GatoOuCachorro) token[0];
        }

        token = strtok(NULL, "|");
        if (token != NULL) {
            animal.status = (enum StatusAnimal) token[0];
        }

        token = strtok(NULL, "|");
        if (token != NULL) {
            strncpy(animal.nome, token, sizeof(animal.nome) - 1);
            animal.nome[sizeof(animal.nome) - 1] = '\0';
        }

        token = strtok(NULL, "|");
        if (token != NULL) {
            strncpy(animal.raca, token, sizeof(animal.raca) - 1);
            animal.raca[sizeof(animal.raca) - 1] = '\0';
        }

        token = strtok(NULL, "|");
        if (token != NULL) {
            strncpy(animal.descricao, token, sizeof(animal.descricao) - 1);
            animal.descricao[sizeof(animal.descricao) - 1] = '\0';
        }

        // Mostra as informações do animal
        MostrarAnimal(&animal);
    }

    printf("\n");
    fclose(arquivo_animal);
}

struct Animal LerDadosAnimalX()
{
    struct Animal animal;

    printf("Cadastrar um animal novo!\n");

    //especie do animal, usando enum
    char variavel1;
    do {
        printf("Digite a especie do animal (G para gato, C para cachorro): ");
        scanf(" %c", &variavel1);
        if (variavel1 == 'G' || variavel1 == 'g') {
            animal.especie = Gato;
        } else if (variavel1 == 'C' || variavel1 == 'c') {
            animal.especie = Cachorro;
        } else {
            printf("Entrada inválida. APENAS G ou C.\n");
        }
    } while (variavel1 != 'G' && variavel1 != 'g' && variavel1 != 'C' && variavel1 != 'c');
    getchar();

    printf("Digite o nome do animal: ");
    fgets(animal.nome, sizeof(animal.nome), stdin);
    animal.nome[strcspn(animal.nome, "\n")] = '\0';

    printf("Digite a raca do animal: ");
    fgets(animal.raca, sizeof(animal.raca), stdin);
    animal.raca[strcspn(animal.raca, "\n")] = '\0';

    printf("Digite a descricao do animal: ");
    fgets(animal.descricao, sizeof(animal.descricao), stdin);
    animal.descricao[strcspn(animal.descricao, "\n")] = '\0';
    //animal automaticamente disponivel pra adoção
    animal.status = Disponivel;

    return animal;
}

int IncluirNovoAnimalX(struct Animal* animal)
{
    FILE *arquivo_animal = fopen(ArqAnimal, "a+");
    if (arquivo_animal == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    int ultimoId = LerUltimoIDX(arquivo_animal);
    fseek(arquivo_animal, 0, SEEK_END);
    animal->ID = ultimoId + 1;

    fprintf(arquivo_animal, "%d|%c|%c|%s|%s|%s\n", animal->ID, animal->especie, animal->status, animal->nome, animal->raca, animal->descricao);

    fclose(arquivo_animal);

    return animal->ID;
}

int LerUltimoIDX(FILE* arquivo_animal)
{
    char str[300];
    int ultimoId = 0;

    fseek(arquivo_animal, 0, SEEK_SET);
    while (fgets(str, sizeof(str), arquivo_animal) != NULL) {
        char *token = strtok(str, "|");
        if (token != NULL) {
            ultimoId = atoi(token);
        }
    }
    return ultimoId;
}

int IDDesejado()
{
    int id;
    printf("qual animal voce deseja apagar, pelo ID?");
    scanf("%i", &id);
    return id;
}

int ExcluirAnimalPorID(int iD)
{
    struct Animal animal;
    char str[300];
    int encontrou = 0;

    FILE *arquivo_animal = fopen(ArqAnimal, "a+");
    if (arquivo_animal == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }

    // Abrindo o arquivo original em modo leitura
    FILE *tempFile = fopen("temp_animal.txt", "w");
    if (tempFile == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        return 0;
    }

    // Voltar para o início do arquivo
    fseek(arquivo_animal, 0, SEEK_SET);

    // Lê cada linha do arquivo e verifica se o ID é o desejado
    while (fgets(str, sizeof(str), arquivo_animal) != NULL) {
        char tmp[300];
        strcpy(tmp, str);
        char *token = strtok(tmp, "|");

        if (token != NULL) {
            animal.ID = atoi(token);  // Lê o ID do animal
        }

        if (animal.ID != iD) {
            // Se não for o animal a ser excluído, copia para o arquivo temporário
            fputs(str, tempFile);
        }
        else
        {
            encontrou = 1;
        }
    }

    fclose(arquivo_animal);  // Fecha o arquivo original
    fclose(tempFile);  // Fecha o arquivo temporário

    // Se o animal foi encontrado, substitui o arquivo original
    if (encontrou) {
        // Remove o arquivo original
        remove(ArqAnimal);
        // Renomeia o arquivo temporário para o nome original
        rename("temp_animal.txt", ArqAnimal);
        return 1;
    } else {
        // Se o animal não foi encontrado, remove o arquivo temporário
        remove("temp_animal.txt");
        return 0;
    }
}

// int desativarAnimal(struct Animal animal, int id, FILE *arquivo_animal) {
//     //buscar pelo id e desativar o animal = animal adotado
//     animal.status = Adotado;
//     return 0;
// }
