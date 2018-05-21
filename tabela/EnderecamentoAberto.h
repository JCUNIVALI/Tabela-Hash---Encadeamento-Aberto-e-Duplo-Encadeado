#ifndef ENDERECAMENTOABERTO_H
#define ENDERECAMENTOABERTO_H
#include <string>
#include <iostream>
#include "stdafx.h"
#include <fstream>
#include <time.h>
using namespace std;
ofstream arq("saida.csv", ofstream::app);		//Tornei global para gravar as buscas também;;

void iniciarVet(Dado vet[]) {
	for (int x = 0; x < MAX; x++) {
		vet[x].dado = "";
		vet[x].chave = -1;
		vet[x].op =0;
	}
}
bool inserir(Dado vet[],Dado *d) {
	int chave = d->chave, i = 1, volta = 1;
	while (true) {
		if (vet[chave].dado == "") {	//acha um local pra salvar o dado;;
			vet[chave].dado = d->dado;
			vet[chave].chave = d->chave;
			vet[chave].op = i;			//numero de vezes em que entrou no while pra achar o local;;
			return true;
		}
		i++;
		if (chave == MAX) {
			chave = 0;
			volta++;
		}
		if (volta == 3)
			return false;
		else
			chave++;		//incrementa o local do vetor q vai ser verificado se esta vazio;;
	}
}
bool verificaDado(Dado vet[],string t, int &op) {		//retorna verdadeiro se o dado ja existir no vetor;;
	int chave = geraChave(t), volta = 1;
	if (vet[chave].dado == t) {
		op = vet[chave].op;
		return true;
	}
	int temp= geraChave(t);
	while (true) {
		if (vet[chave].chave == temp && vet[chave].dado == t) {
			op = vet[chave].op;
			return true;
		}
		if (chave == MAX) {
			chave = 0;
			volta++;
		}
		if (volta == 3)
			return false;
		else
			chave++;
	}
}
Dado buscaDado(Dado vet[], string t, int op) {			//retorna um dado que ja existe no vetor;;
	int chave = geraChave(t);
	if (vet[chave].dado == t && vet[chave].op==op)
		return vet[chave];
	int temp = geraChave(t);
	while (true) {
		if (vet[chave].chave == temp && vet[chave].dado == t && vet[chave].op == op) {
			return vet[chave];
		}
		if (chave == MAX)
			chave = 0;
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
void buscaManual(Dado vet[], string t) {
	int opTemp = 1;
	if (verificaDado(vet, t, opTemp))
		procurarDado(vet,t);
}
void realizarBuscaManual(Dado vet[]) {
	cout << "Desejas realizar uma busca manual de um dado? (s/n)" << endl;
	char opcao;
	cin >> opcao;
	if (opcao != 's' && opcao != 'S')
		return;
	cout << "Quantas busca desejas fazer?" << endl;
	int buscas;
	cin >> buscas;
	string *temp = new string[buscas];
	arq <<"Busca manual realiazda: "<< "\n";
	for (int i = 0; i < buscas; i++) {
		cout << i << "- Dado a ser pesquisado: ";
		cin >> temp[i];
		arq <<i<<"- Dado ["+temp[i]+"]"<< "\n";
	}
	for (int i = 0; i < buscas; i++) {
		int opTemp = 1;
		if (verificaDado(vet, temp[i], opTemp))
			procurarDado(vet, temp[i]);
		else {
			cout << "Busca-->Dado nao encontrado [" + temp[i] + "]" << endl;
			arq << "Busca-->Dado nao encontrado [" + temp[i] + "]\n";
		}
	}
}
void EnderecamentoAberto() {
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
	realizarBuscaManual(vet);
}



#endif
