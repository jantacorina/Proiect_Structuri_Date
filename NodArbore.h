#pragma once
#include <stdio.h>
#include <stdlib.h>
#include"Nod.h"
struct NodArbore {
	int numarCopii;
	Element* chei[3];
	NodArbore * copii[4];
	int numarElementeCopii[4];
	int esteFrunza;
	NodArbore* parinte;
	NodArbore * min;
};

int InsererazaCheieNod(NodArbore* nod,Element* key);

Element* StergeCheie(NodArbore* nod, int index);

int numarElemente(NodArbore*nod);

Element* minim(NodArbore* nod, Element* oldMin);

int Intern_Adauga_Arbore(NodArbore * left, Element* e, NodArbore * right, NodArbore** root, NodArbore*n, int ki);

/**
*  Transformarea arborelui folosita la stergere.Muta subarborele din stanga
*din copilul @ki al unui nod in nodul precedent.Modifica @k so @index astfel incat ele
* sa pointeze catre aceeasi locatie in arborele modificat.Se presupune ca arborele destinatie
* nu este plin
**/
void TransformareArboreStanga(NodArbore * nod, int ki, int *k, int*index);

void TransformareArboreDreapta(NodArbore * nod, int ki, int *k, int*index);

/***
* Imbina nodurile copii ki si ki+1 ale nodului @nod.Modifica @k si @index
* astfel incat ele sa ramana modificate dupa functie.
*
*/
void ImbinaArbori(NodArbore * nod, int ki, int *k, int*index);



void Dezalocare(NodArbore * nod);