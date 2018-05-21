#ifndef ENCADEADA_H_INCLUDED
#define ENCADEADA_H_INCLUDED

#include <iostream>
#include <string>
#include "Dado.h"
using namespace std;

struct ElementoEnc {
	Dado dado;
	ElementoEnc *proximo;
};
struct ListaEnc {
	ElementoEnc *primeiro;
	int qtd;
};
void iniciar_lista_encadeada(ListaEnc &l) {
	l.primeiro->dado.dado = "";
	l.primeiro->dado.chave = -1;
	l.primeiro->dado.op = 0;
	l.qtd = 0;
	l.primeiro = NULL;
}
bool inserir_inicio_lista_encadeada(ListaEnc &l, Dado dado) {
	ElementoEnc *e = new ElementoEnc;
	if (e == NULL)
		return false;
	e->dado = dado;
	e->dado.op = 1;
	e->proximo = l.primeiro;
	l.primeiro = e;
	l.qtd++;
	return true;
}
bool inserir_fim_lista_encadeada(ListaEnc &l, Dado dado) {
	if (l.qtd == 0) {
		return inserir_inicio_lista_encadeada(l, dado);
	}
	ElementoEnc *e = new ElementoEnc;
	if (e == NULL)
		return false;
	e->dado = dado;
	e->proximo = NULL;
	ElementoEnc *temp = l.primeiro;
	while (temp->proximo != NULL) {
		temp = temp->proximo;
		temp->dado.op++;
	}
	temp->proximo = e;
	l.qtd++;
	return true;
}

#endif // ENCADEADA_H_INCLUDED
