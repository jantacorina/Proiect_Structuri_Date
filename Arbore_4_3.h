#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NodArbore.h"

typedef int(*pFunctieComparare)(int, int);

typedef struct Arbore_4_3 {
	NodArbore * Radacina;
	pFunctieComparare comparare;
}Arbore;

Arbore*  Initializare();

void Dezalocare(Arbore* arbore);

int numarElemente(Arbore* arbore);

int Adauga_Arbore(Arbore* arbore, int e, int index);

int Adauga_Arbore(Arbore* arbore, int e);

int Index(Arbore* nod, int element);

void ImparteArbore(NodArbore* nod, int pozitie);

NodArbore* InitializeazaNod();

void Printeaza(NodArbore* nod);

int StergereInterna(Arbore* arbore, int index);

int Stergere(Arbore* arbore, int index);









