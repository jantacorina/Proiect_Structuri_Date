#pragma once
#include "Arbore_4_3.h"

typedef struct Queap {
	int n;
	int k;
	Element* minimElementeT;
	Arbore* queap_arbore;
	Lista* lista_inlantuita;
}Queap;

void init(Queap* queap);

Element* Insert(Queap* queap, int element);

void Stergere(Queap* queap, Element* element);

Element* Minimum(Queap* queap);

Element* deleteMin(Queap* queap);