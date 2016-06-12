#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Lista.h"

typedef int(*pFunctieComparare)(int, int);


enum Relation {
	GREATER,
	EQUAL,
	LESS,
	LESS_EQUAL,
	GREATER_EQUAL
};

typedef struct Arbore_4_3 {
	NodArbore * Radacina;
	Element* minimum;
	pFunctieComparare comparare;
}Arbore;

Arbore*  Initializare(pFunctieComparare);

void Dezalocare(Arbore* arbore);

int numarElemente(Arbore* arbore);

Element* Adauga_Arbore(Arbore* arbore, Element* e, int index);

Element* Adauga_Arbore(Arbore* arbore, Element* e);

Element* Index(Arbore* nod, int element);

void ImparteArbore(NodArbore* nod, int pozitie);

NodArbore* InitializeazaNod();

void Printeaza(NodArbore* nod);

Element* StergereIndex(Arbore * arbore, int index);

Element* Cauta(Arbore* arbore, Element* element, pFunctieComparare comparare, Relation relatie, int * index);

Element* StergeElement(Arbore* arbore, Element* element);

Element* StergereElementIntern(Arbore * arbore, int index);

void Afisare(Arbore* arbore);









