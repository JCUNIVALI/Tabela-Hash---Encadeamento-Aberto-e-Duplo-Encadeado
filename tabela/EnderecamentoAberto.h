#ifndef ENDERECAMENTOABERTO_H
#define ENDERECAMENTOABERTO_H

#include <fstream>
#include <string>
#include <iostream>
#include <time.h>
using namespace std;
const int MAX = 1000;
const int TAMSTRING = 6;
ofstream arq("saida.csv", ofstream::app);		//Tornei global para gravar as buscas tamb�m;;
struct Dado {
	string dado;
	int chave;
	int op;
};
int geraChave(string t) {
	long int chave = 1;
	for (int x = 0; x <3; x++) {
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
		vet[x].chave = -1;
		vet[x].op =0;
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
bool verificaDado(Dado vet[],string t, int &op) {		//retorna verdadeiro se o dado ja existir no vetor;;
	int chave = geraChave(t);
	if (vet[chave].dado == t) {
		op = vet[chave].op;
		return true;
	}
	int temp= geraChave(t);
	while (chave <MAX) {
		if (vet[chave].chave == temp && vet[chave].dado == t) {
			op = vet[chave].op;
			return true;
		}
		chave++;
	}
	return false;
}
Dado buscaDado(Dado vet[], string t, int op) {			//retorna um dado que ja existe no vetor;;
	int chave = geraChave(t);
	if (vet[chave].dado == t && vet[chave].op==op)
		return vet[chave];
	int temp = geraChave(t);
	while (chave <MAX) {
		if (vet[chave].chave == temp && vet[chave].dado == t && vet[chave].op == op) {
			return vet[chave];
		}
		chave++;
	}
}
void procurarDado(Dado vet[],string t) {				//procura o dado, e escreve tudo sobre ele se ele existir;;
	int opTemp = 1;
	if (verificaDado(vet, t, opTemp)) {
		Dado temp = buscaDado(vet, t, opTemp);
		arq<< "Dado: " << temp.dado << " Chave : " << temp.chave << " OP : " << temp.op<<"\n";
		cout << "Busca-->Dado: " << temp.dado << " Chave: " << temp.chave << " OP: " << temp.op << endl;
	}
}
void simulacaoBusca(Dado vet[]) {
	int busca, cont = 0, cont2 = 0;
	cout << "Digite uma quantidade de tentativas de busca: " << endl;
	cin >> busca;
	string *temp = new string[busca];
	arq << "BUSCAS SIMULADAS - Tentativas("<<busca<<"):\n";
	for (int x = 0; x < busca; x++) {
		char t[6];
		for (int i = 0; i < TAMSTRING-1; i++) { //cria uma string aleatoria;;
			int z;
			z = rand() % 122;
			while (z<65 || (z>90 && z< 97)) {
				z = rand() % 122;
			}
			t[i] = (char)z;
		}
		t[5] = '\0';
		temp[cont] = t;
		int opTemp = 1;
		if (verificaDado(vet, temp[cont], opTemp))
			cont2++;
		procurarDado(vet, temp[cont]);
		cont++;
	}
	if (cont2 == 0) {
		arq << "Nenhum dos dados gerados Aleatoriamente foram encontrados na tabela.\n";
		cout << "Nenhum dos dados gerados Aleatoriamente foram encontrados na tabela." << endl;
	}
	char opcao;
	cout << "Deseja visualizar os dados que foram gerados aleatoriamente para a busca? (s/n)" << endl;
	cin >> opcao;
	for (int x = 0; x < busca; x++) {
		if (opcao == 's' || opcao == 'S')
			cout << x << "- Dado gerado: " << temp[x] << endl;
		arq << x << "- Dado gerado: " << temp[x] << "\n";
	}
}
void tabela() {
	Dado vet[MAX];
	iniciarVet(vet);
	srand(time(NULL));
	for (int x = 0; x < MAX; x++) {
		char t[6];
		for (int i = 0; i < TAMSTRING-1; i++) { //cria uma string aleatoria para salvar como dado;;
			int z;
			z= rand() % 122;
			while (z<65 || (z>90 && z< 97)) {
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
	arq << "ENTRADAS:\n";
	for (int x= 0; x < MAX; x++) { //exibe os dados salvos no vetor;;
		arq << "Dado:"<<vet[x].dado << ", Chave :" << vet[x].chave << ", OP: " << vet[x].op<<"\n";
		cout << "Dado: " << vet[x].dado << " Chave: " << vet[x].chave <<" OP: "<<vet[x].op<<endl;
	}
	simulacaoBusca(vet);
}



#endif
