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

int NumarElemente(Arbore * arbore)
{
	if (arbore->Radacina)
		return numarElemente(arbore->Radacina);
	else
		return 0;
}

int  StergereInterna(Arbore * arbore, int index)
{
	NodArbore *n;
	void* retval;
	int retValInt;
	int ki, i;
	retval = NULL;
	n = arbore->Radacina;
	while (1) 
	{
		NodArbore *sub;
		if (index <= n->numarElementeCopii[0]) {
			ki = 0;
		}
		else if (index -= n->numarElementeCopii[0] + 1, index <= n->numarElementeCopii[1]) {
			ki = 1;
		}
		else if (index -= n->numarElementeCopii[1] + 1, index <= n->numarElementeCopii[2]) {
			ki = 2;
		}
		else if (index -= n->numarElementeCopii[2] + 1, index <= n->numarElementeCopii[3]) {
			ki = 3;
		}
		else {
			exit(1);
		}
		if (!n->copii[0])
			break;
		// verificam daca am gasit nodul tinta.Daca da alegem o alta tinta 
		if (index == n->numarElementeCopii[ki]) {
			NodArbore *m;
			ki++; index = 0;
			for (m = n->copii[ki]; m->copii[0]; m = m->copii[0])
				continue;
			retval = n->copii[ki - 1];
			n->chei[ki - 1] = m->chei[0];
		}
		sub = n->copii[ki];
		if (!sub->chei[1]) {
			if (ki > 0 && n->copii[ki - 1]->chei[1])
				TransformareArboreDreapta(n, ki - 1, &ki, &index);
		}
		else if (ki < 3 && n->copii[ki + 1] &&
			n->copii[ki + 1]->chei[1]) {
			/*
			*Copilul ki are un singur element dar ki+1 are cel putin 2 copii.Muta arborele ki+1 sub ki
			*/
			TransformareArboreStanga(n, ki + 1, &ki, &index);
		}
		else {
			ImbinaArbori(n, ki > 0 ? ki - 1 : ki, &ki, &index);
			sub = n->copii[ki];

			if (!n->chei[0]) {
				arbore->Radacina = sub;
				sub->parinte = NULL;
				free(n);
				n = NULL;
			}
		}
		if (n)
			n->numarElementeCopii[ki]--;
		n = sub;
	}
	if(!retval)
		retValInt = n->chei[ki];

	for (i = ki; i < 2 && n->chei[i + 1]; i++)
		n->chei[i] = n->chei[i + 1];
	n->chei[i] = NULL;

	if (!n->chei[0]) {
		free(n);
		arbore->Radacina = NULL;
	}
	return retValInt;
}

int Stergere(Arbore * arbore, int index)
{
	if (index < 0 || numarElemente(arbore->Radacina))
		return NULL;
	return StergereInterna(arbore, index);
}

int Inaltime(Arbore * arbore)
{
	int level = 0;
	NodArbore *n = arbore->Radacina;
	while (n) {
		level++;
		n = n->copii[0];
	}
	return level;
}
