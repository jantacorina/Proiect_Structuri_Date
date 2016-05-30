#include "Arbore_4_3.h"


Arbore*  Initializare()
{
	Arbore * arbore = (Arbore*)malloc(sizeof(Arbore));
	arbore->Radacina = InitializeazaNod();
	arbore->lungime = 0;
	return arbore;
}

NodArbore* InsereazaInFata(Arbore* arbore, int element)
{
	NodArbore * temporar;
	temporar = InitializeazaNod();
	if (arbore->Radacina->numarCopii == 3)
	{
		temporar->copii[0] = arbore->Radacina;
		temporar->esteFrunza = 0;
		arbore->Radacina = temporar;
		ImparteArbore(temporar, 0);
		return Insereaza(arbore, temporar, element);
	}
	else
	{
		return Insereaza(arbore, arbore->Radacina, element);
	}
}

NodArbore* Insereaza(Arbore* arbore, NodArbore* nod, int element)
{
	int i = 0;
	while (i < nod->numarCopii && element > nod->chei[i])
		i++;
	if (nod->esteFrunza)
	{
		int j;
		for (j = nod->numarCopii; j > i; j--)
			nod->chei[j] = nod->chei[j - 1];
		nod->chei[j] = element;
		nod->numarCopii++;
		arbore->lungime++;
		return nod;
	}
	else
	{
		if (nod->copii[i]->numarCopii == 3)
		{
			ImparteArbore(nod, i);
			if (element > nod->chei[i])
				i++;
		}
	}
	return Insereaza(arbore, nod->copii[i], element);
}

void ImparteArbore(NodArbore* nod, int pozitie)
{
	NodArbore* temporar;
	temporar = nod->copii[pozitie];
	NodArbore * curent;
	curent = InitializeazaNod();
	int i;
	for (i = nod->numarCopii; i > pozitie; i--)
	{
		nod->copii[i + 1] = nod->copii[i];
		nod->chei[i] = nod->chei[i - 1];
	}
	nod->chei[pozitie] = temporar->chei[1];
	nod->copii[pozitie + 1] = curent;
	nod->numarCopii++;

	if (temporar->esteFrunza)
	{
		curent->esteFrunza = 1;
		for (i = 0; i < 1; i++)
		{
			curent->chei[i] = temporar->chei[i + 2];
			curent->numarCopii++;
		}
		temporar->numarCopii = 1;
	}
	else
	{
		curent->esteFrunza = 0;
		for (i = 0; i < 1; i++)
		{
			curent->chei[i] = temporar->chei[i + 2];
			curent->copii[i] = temporar->copii[i + 2];
			curent->numarCopii++;
		}
		curent->copii[1] = temporar->copii[2];
		temporar->numarCopii = 1;
	}
}

NodArbore* Cauta(NodArbore* nod, int element)
{
	if (nod->esteFrunza)
		return nod;
	int i = 0;
	while (i< nod->numarCopii && element > nod->chei[i])
		i++;
	if (element == nod->chei[i])
		return nod;
	else
		return Cauta(nod->copii[i], element);
}

int Lungime(Arbore* arbore)
{
	if (arbore == NULL)
		return -1;
	else
		return arbore->lungime;
}

NodArbore* InitializeazaNod()
{
	NodArbore * temporar = (NodArbore*)malloc(sizeof(NodArbore));
	int i;
	for (i = 0; i < 3; i++)
	{
		temporar->copii[i] = 0;
		temporar->chei[i] = 0;
	}
	temporar->copii[3] = 0;
	temporar->numarCopii = 0;
	temporar->esteFrunza = 1;
	return temporar;
}

void Dezalocare(Arbore* arbore,NodArbore* Nod)
{
	if (arbore->Radacina == NULL)
		return;
	Dezalocare(arbore, arbore->Radacina->copii[0]);
	Dezalocare(arbore, arbore->Radacina->copii[1]);
	Dezalocare(arbore, arbore->Radacina->copii[2]);
	Dezalocare(arbore, arbore->Radacina->copii[3]);
	free(Nod);
}

void Printeaza(NodArbore* nod)
{
	if (!nod) {
		printf("Nu exista niciun nod.\n");
		return;
	}
	else if (1 > nod->numarCopii) {
		printf("Nu exista chei in acest nod.\n");
		return;
	}
	printf("Copii nodului sunt: \n");
	int i;
	for (i = 0; i < nod->numarCopii - 1; i++) {
		printf("Copil %d este: %d.\n", i, nod->chei[i]);
	}
	printf("Child %d is: %d.\n", i, nod->chei[i]);
}