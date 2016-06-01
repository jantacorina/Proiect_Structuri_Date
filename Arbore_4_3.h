#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "NodArbore.h"

typedef struct Arbore_4_3 {
	NodArbore * Radacina;
	int lungime;
}Arbore;


Arbore*  Initializare();

NodArbore* Cauta(NodArbore* nod, int element);

NodArbore* InsereazaInFata(Arbore* arbore, int element);

NodArbore* Insereaza(Arbore* arbore, NodArbore* nod, int element);

void ImparteArbore(NodArbore* nod, int pozitie);

int Lungime(Arbore* arbore);

NodArbore* InitializeazaNod();

void Dezalocare(Arbore* arbore,NodArbore* Nod);

void Printeaza(NodArbore* nod);

int NumarElemente(Arbore* arbore);

int StergereInterna(Arbore* arbore, int index);

int Stergere(Arbore* arbore, int index);

int Inaltime(Arbore * arbore);








