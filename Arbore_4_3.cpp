#include "Arbore_4_3.h"


Arbore*  Initializare()
{
	Arbore * arbore = (Arbore*)malloc(sizeof(Arbore));
	arbore->Radacina = NULL;
	arbore->comparare = NULL;
	return arbore;
}
void Dezalocare(Arbore* arbore)
{
	Dezalocare(arbore->Radacina);
	free(arbore);
}

int numarElemente(Arbore* arbore)
{
	if (arbore->Radacina)
		return numarElemente(arbore->Radacina);
	else
		return 0;
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

int Index(Arbore* arbore, int index)
{
	NodArbore *n;

	if (!arbore->Radacina)
		return NULL;		       /* tree is empty */

	if (index < 0 || index >= numarElemente(arbore->Radacina))
		return NULL;		       /* out of range */

	n = arbore->Radacina;

	while (n) {
		if (index < n->numarElementeCopii[0])
			n = n->copii[0];
		else if (index -= n->numarElementeCopii[0] + 1, index < 0)
			return n->chei[0];
		else if (index < n->numarElementeCopii[1])
			n = n->copii[1];
		else if (index -= n->numarElementeCopii[1] + 1, index < 0)
			return n->chei[1];
		else if (index < n->numarElementeCopii[2])
			n = n->copii[2];
		else if (index -= n->numarElementeCopii[2] + 1, index < 0)
			return n->chei[2];
		else
			n = n->copii[3];
	}
	return NULL;
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

int StergereInterna(Arbore * arbore, int index)
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

int Adauga_Arbore(Arbore* arbore, int e)
{
	if (arbore->comparare == NULL)
		return NULL;
	return Adauga_Arbore(arbore, e, -1);
}

int Adauga_Arbore(Arbore* arbore, int e, int index)
{
	NodArbore *n;
	int ki;
	int orig_e = e;
	int c;

	if (arbore->Radacina == NULL) 
	{
		arbore->Radacina = new(NodArbore);
		arbore->Radacina->chei[1] = arbore->Radacina->chei[2] = NULL;
		arbore->Radacina->copii[0] = arbore->Radacina->copii[1] = NULL;
		arbore->Radacina->copii[2] = arbore->Radacina->copii[3] = NULL;
		arbore->Radacina->numarElementeCopii[0] = arbore->Radacina->numarElementeCopii[1] = 0;
		arbore->Radacina->numarElementeCopii[2] = arbore->Radacina->numarElementeCopii[3] = 0;
		arbore->Radacina->parinte = NULL;
		arbore->Radacina->chei[0] = e;
		return orig_e;
	}

	n = arbore->Radacina;
	while (n) {
		if (index >= 0) {
			if (!n->copii[0]) {
				ki = index;
			}
			else {
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
				else
					return NULL;       /* error: index out of range */
			}
		}
		else {
			if ((c = arbore->comparare(e, n->chei[0])) < 0)
				ki = 0;
			else if (c == 0)
				return n->chei[0];	       /* already exists */
			else if (n->chei[1] == NULL || (c = arbore->comparare(e, n->chei[1])) < 0)
				ki = 1;
			else if (c == 0)
				return n->chei[1];	       /* already exists */
			else if (n->chei[2] == NULL || (c = arbore->comparare(e, n->chei[2])) < 0)
				ki = 2;
			else if (c == 0)
				return n->chei[2];	       /* already exists */
			else
				ki = 3;
		}
		if (!n->copii[ki])
			break;
		n = n->copii[ki];
	}

	Intern_Adauga_Arbore(NULL, e, NULL, &arbore->Radacina, n, ki);
	return orig_e;
}