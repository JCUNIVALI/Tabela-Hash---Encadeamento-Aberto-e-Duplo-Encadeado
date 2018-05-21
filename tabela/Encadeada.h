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
	l.qtd = 0;
	l.primeiro = NULL;
}
bool inserir_inicio_lista_encadeada(ListaEnc &l, Dado dado) {
	ElementoEnc *e = new ElementoEnc;
	if (e == NULL)
		return false;
	e->dado = dado;
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
	e->dado = dado;
	e->dado.op++;
	e->proximo = NULL;
	ElementoEnc *temp = l.primeiro;
	while (temp->proximo != NULL) {
		temp = temp->proximo;
		e->dado.op++;
	}
	temp->proximo = e;
	l.qtd++;
	return true;
}

#endif // ENCADEADA_H_INCLUDED
