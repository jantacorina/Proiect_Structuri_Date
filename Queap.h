#pragma once
#include "Arbore_4_3.h"
#include "Lista.h"

typedef struct Queap {
	int n;
	int k;
	int minimElementeT;
	Arbore* queap_arbore;
	Lista* lista_inlantuita;
}Queap;

void init(Queap* queap);

void Insert(Queap* queap, int element);