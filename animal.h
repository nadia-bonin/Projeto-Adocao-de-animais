#ifndef ANIMAL_H
#define ANIMAL_H

enum StatusAnimal {
	Disponivel = 'D',
	Adotado = 'A',
};

enum GatoOuCachorro {
	Cachorro = 'C',
	Gato = 'G',
};

struct Animal {
	int ID;
	enum GatoOuCachorro especie;
	char nome[50];
	char raca[50];
	char descricao[250];
	enum StatusAnimal status;
};

extern int menuAnimal();

#endif // ANIMAL_H
