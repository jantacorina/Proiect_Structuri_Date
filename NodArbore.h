#pragma once
#include <stdio.h>
#include <stdlib.h>
typedef struct NodArbore {
	int numarCopii;
	int chei[3];
	NodArbore * copii[4];
	int numarElementeCopii[4];
	int esteFrunza;
	NodArbore* parinte;

};

int InsererazaCheieNod(NodArbore* nod,int key);

int StergeCheie(NodArbore* nod, int index)
{
	int cheie = nod->chei[index];

	for (int i = index; i < nod->numarCopii; i++)
		nod->chei[i] = nod->chei[i + 1];

	--nod->numarCopii;
	return cheie;
}

int numarElemente(NodArbore*nod);

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


