#ifndef ENDERECAMENTOABERTO_H
#define ENDERECAMENTOABERTO_H

#include <string>
#include <iostream>
#include <time.h>
using namespace std;
const int MAX = 1000;
struct Dado {
	string dado;
	int chave;
	int op;
};
int geraChave(string t) {
	int chave = 1;
	for (int x = 0; x < 3; x++) {
		chave *= (int)t[x];
	}
	if (chave > MAX) {
		chave= chave % MAX;
	}
	chave--;
	if (chave < 0)
		chave = 0;
	return chave;
}
void iniciarVet(Dado vet[]) {
	for (int x = 0; x < MAX; x++) {
		vet[x].dado = "";
		vet[x].chave = NULL;
		vet[x].op = 1;
	}
}
bool inserir(Dado vet[],Dado *d) {
	int chave = d->chave, i = 1;
	while (chave <MAX) {
		if (vet[chave].dado == "") {	//acha um local pra salvar o dado;;
			vet[chave].dado = d->dado;
			vet[chave].chave = d->chave;
			vet[chave].op = i;			//numero de vezes em que entrou no while pra achar o local;;
			return true;
		}
		i++;
		chave++;					//incrementa o local do vetor q vai ser verificado se esta vazio;;
	}
	return false;
}
void tabela() {
	Dado vet[MAX];
	iniciarVet(vet);
	srand(time(NULL));
	for (int x = 0; x < MAX; x++) {
		char t[6];
		for (int i = 0; i < 5; i++) { //cria uma string aleatoria para salvar como dado;;
			int z;
			z= rand() % 122;
			while (z < 97) {
				z = rand() % 122;
			}
			t[i] = (char)z;
		}
		t[5] = '\0';
		Dado d;
		d.dado = t;
		d.chave = geraChave(t);  //gera uma chave a partir da string;;
		inserir(vet, &d);
	}
	for (int x= 0; x < MAX; x++) { //exibe os dados salvos no vetor;;
		cout << "Dado: " << vet[x].dado << endl << "chave: " << vet[x].chave << endl <<"OP: "<<vet[x].op<<endl<< endl;
	}

}
/*VER COMO GERAR A PLANILHA*/



#endif
