#ifndef DADO_H
#define DADO_H
using namespace std;

#include <fstream>
ofstream arq2("saidaHaschEncadeado.csv", ofstream::app);
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
		chave = chave % MAX;
	}
	chave--;
	if (chave < 0)
		chave = 0;
	return chave;
}
#endif
