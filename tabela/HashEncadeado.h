#ifndef HASHENCADEADO_H
#define HASHENCADEADO_H

#include "Encadeada.h"
ofstream arq2("saidaHaschEncadeado.csv", ofstream::app);

using namespace std;

bool buscaDireta(ListaEnc l, string t) {
	ElementoEnc *temp = l.primeiro;
	if (temp == NULL)
		return false;
	while (temp != NULL) {
		if (temp->dado.dado == t) {
			cout << "Dado Encontrado: Dado: " << temp->dado.dado << ", Chave :" << temp->dado.chave << ", OP: " << temp->dado.op << endl;
			arq2<< "Dado Encontrado: Dado: " << temp->dado.dado << ", Chave :" << temp->dado.chave << ", OP: " << temp->dado.op << "\n";
			return true;
		}
		temp = temp->proximo;
	}
	arq2 << "Dado nao encontrado: Dado: " + t + "\n";
	cout << "Dado nao encontrado: Dado: " + t << endl;
	return false;

}
void busca(ListaEnc l[], string t) {
	int chave = geraChave(t);
	buscaDireta(l[chave], t);
}
void buscaSimulada(ListaEnc l[]) {
	char opcao;
	cout << "Desejas fazer uma busca simulada onde sera gerado dados aleatorios e feito a pesquisa?(s/n)" << endl;
	cin >> opcao;
	if (opcao != 's' && opcao != 'S')
		return;
	int buscas;
	cout << "Digite a quantidade de buscas simuladas: " << endl;
	cin >> buscas;
	cout << "Buscas simuladas:" << endl;
	arq2 << "Buscas simuladas --> Tentativas de busca (" << buscas << ")\n";
	for (int x = 0; x < buscas; x++) {
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
		string temp = t;
		busca(l, temp);
	}
	arq2 << "Fim buscas simuladas.\n";
	cout << "Fim buscas simuladas." << endl;
}
void buscaManual(ListaEnc l[]) {
	char opcao;
	int buscas;
	cout << "Desejas realizar uma busca manual? (s/n)" << endl;
	cin >> opcao;
	if (opcao != 's' && opcao != 'S')
		return;
	cout << "Digite a quantidade de buscas que desejas realizar: " << endl;
	cin >> buscas;
	string *temp = new string[buscas];
	cout << "Preencha os dados a serem buscados: " << endl;
	for (int x = 0; x < buscas; x++) {
		cout << x << "-";
		cin >> temp[x];
	}
	arq2 << "Buscas Manual --> Tentativas de busca (" << buscas << ")\n";
	for (int x = 0; x < buscas; x++) {
		busca(l, temp[x]);
	}
}
void escrever(ListaEnc l, int c) {
	ElementoEnc *temp = l.primeiro;
	cout << "CHAVE [" << c << "]:" << endl;
	arq2 << "CHAVE [" << c << "]:\n";
	while (temp != NULL) {
		arq2 << "Dado" << temp->dado.dado << ", Chave :" << temp->dado.chave <<", OP: " <<temp->dado.op << "\t";
		cout << "Dado: " << temp->dado.dado << ", Chave :" << temp->dado.chave << ", OP: " << temp->dado.op << "\t";
		temp = temp->proximo;
	}
	arq2 << "\n";
	cout << "\n";
}
void HashEncadeado(){
	ListaEnc l[1000];
	for (int x = 0; x<MAX; x++)
		iniciar_lista_encadeada(l[x]);
	srand(time(NULL));
	arq2 << "Entradas:\n";
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
		d.op = 1;
		d.dado = t;
		d.chave = geraChave(t);  //gera uma chave a partir da string;;
		inserir_fim_lista_encadeada(l[d.chave], d);
	}
	for (int x = 0; x<MAX; x++)
		escrever(l[x], x);
	buscaSimulada(l);
	buscaManual(l);
}


#endif