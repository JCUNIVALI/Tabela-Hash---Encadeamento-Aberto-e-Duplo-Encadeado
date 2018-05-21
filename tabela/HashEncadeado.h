#ifndef HASHENCADEADO_H
#define HASHENCADEADO_H

#include "Encadeada.h"
ofstream arq2("saidaHaschEncadeado.csv", ofstream::app);

using namespace std;

void inserir(ListaEnc vet,Dado d) {
	inserir_fim_lista_encadeada(vet, d);
}
void escrever(ListaEnc vet) {
	ElementoEnc *temp = vet.primeiro;
	int x = 1;
	while (temp != NULL) {
		cout << "Dado: " << vet.primeiro->dado.dado << ", Chave :" << vet.primeiro->dado.chave << ", OP: " << vet.primeiro->dado.op << "\t";
		arq2 << "Dado:" << vet.primeiro->dado.dado << ", Chave :" << vet.primeiro->dado.chave << ", OP: " << vet.primeiro->dado.op << "\t";
		temp = temp->proximo;
		x++;
	}
	arq << "\n";
	cout << "\n";
}
void HashEncadeado(){
	ListaEnc vet[MAX];
	for (int x=0;x<MAX;x++)
		iniciar_lista_encadeada(vet[x]);
	srand(time(NULL));
	for (int x = 0; x < MAX; x++) {
		char t[6];
		for (int i = 0; i < TAMSTRING - 1; i++) { //cria uma string aleatoria para salvar como dado;;
			int z;
			z = rand() % 122;
			while (z<65 || (z>90 && z< 97)) {
				z = rand() % 122;
			}
			t[i] = (char)z;
		}
		t[5] = '\0';
		Dado d;
		d.dado = t;
		d.chave = geraChave(t);  //gera uma chave a partir da string;;
		inserir(vet[d.chave], d);
	}
	arq << "ENTRADAS:\n";
	for (int x = 0; x < MAX; x++) { //exibe os dados salvos no vetor;;
		escrever(vet[x]);
	}
}
#endif