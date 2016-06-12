#include "stdafx.h"
#include "Arbore_4_3.h"

#define INFINIT 100000
Arbore*  Initializare(pFunctieComparare pCompare)
{
	Arbore * arbore = my_new(Arbore);
	arbore->minimum = my_new(Element);
	arbore->minimum->value = INFINIT;
	arbore->Radacina = NULL;
	arbore->comparare = pCompare;
	return arbore;
}

void Dezalocare(Arbore* arbore)
{
	Dezalocare(arbore->Radacina);
	my_free(arbore);
	arbore->Radacina = NULL;
	arbore = NULL;
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

Element* Index(Arbore* arbore, int index)
{
	NodArbore *n;

	if (!arbore->Radacina)
		return NULL;

	if (index < 0 || index >= numarElemente(arbore->Radacina))
		return NULL;

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

void Dezalocare(Arbore* arbore, NodArbore* Nod)
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

Element* StergereElementIntern(Arbore * arbore, int index)
{
	NodArbore *n;
	Element* retval = my_new(Element);
	int ei = -1;

	retval->value = 0;

	n = arbore->Radacina;
	while (1) {
		while (n) {
			int ki;
			NodArbore *sub;
			if (index < n->numarElementeCopii[0]) {
				ki = 0;
			}
			else if (index -= n->numarElementeCopii[0] + 1, index < 0) {
				ei = 0;
				break;
			}
			else if (index < n->numarElementeCopii[1]) {
				ki = 1;
			}
			else if (index -= n->numarElementeCopii[1] + 1, index < 0) {
				ei = 1;
				break;
			}
			else if (index < n->numarElementeCopii[2]) {
				ki = 2;
			}
			else if (index -= n->numarElementeCopii[2] + 1, index < 0) {
				ei = 2;
				break;
			}
			else {
				ki = 3;
			}
			sub = n->copii[ki];
			if (!sub->chei[1]) {
				if (ki > 0 && n->copii[ki - 1]->chei[1]) {
					NodArbore *sib = n->copii[ki - 1];
					int lastelem = (sib->chei[2] ? 2 :
						sib->chei[1] ? 1 : 0);
					sub->copii[2] = sub->copii[1];
					sub->numarElementeCopii[2] = sub->numarElementeCopii[1];
					sub->chei[1] = sub->chei[0];
					sub->copii[1] = sub->copii[0];
					sub->numarElementeCopii[1] = sub->numarElementeCopii[0];
					sub->chei[0] = n->chei[ki - 1];
					sub->copii[0] = sib->copii[lastelem + 1];
					sub->numarElementeCopii[0] = sib->numarElementeCopii[lastelem + 1];
					if (sub->copii[0])
						sub->copii[0]->parinte = sub;
					n->chei[ki - 1] = sib->chei[lastelem];
					sib->copii[lastelem + 1] = NULL;
					sib->numarElementeCopii[lastelem + 1] = 0;
					sib->chei[lastelem] = NULL;
					n->numarElementeCopii[ki] = numarElemente(sub);
					index += n->numarElementeCopii[ki - 1];
					n->numarElementeCopii[ki - 1] = numarElemente(sib);
					index -= n->numarElementeCopii[ki - 1];
				}
				else if (ki < 3 && n->copii[ki + 1]
					&& n->copii[ki + 1]->chei[1]) {
					NodArbore *sib = n->copii[ki + 1];
					int j;
					sub->chei[1] = n->chei[ki];
					sub->copii[2] = sib->copii[0];
					sub->numarElementeCopii[2] = sib->numarElementeCopii[0];
					if (sub->copii[2])
						sub->copii[2]->parinte = sub;
					n->chei[ki] = sib->chei[0];
					sib->copii[0] = sib->copii[1];
					sib->numarElementeCopii[0] = sib->numarElementeCopii[1];
					for (j = 0; j < 2 && sib->chei[j + 1]; j++) {
						sib->copii[j + 1] = sib->copii[j + 2];
						sib->numarElementeCopii[j + 1] = sib->numarElementeCopii[j + 2];
						sib->chei[j] = sib->chei[j + 1];
					}
					sib->copii[j + 1] = NULL;
					sib->numarElementeCopii[j + 1] = 0;
					sib->chei[j] = NULL;
					n->numarElementeCopii[ki] = numarElemente(sub);
					n->numarElementeCopii[ki + 1] = numarElemente(sib);
				}
				else {
					NodArbore *sib;
					int j;

					if (ki > 0) {
						ki--;
						index += n->numarElementeCopii[ki] + 1;
					}
					sib = n->copii[ki];
					sub = n->copii[ki + 1];

					sub->copii[3] = sub->copii[1];
					sub->numarElementeCopii[3] = sub->numarElementeCopii[1];
					sub->chei[2] = sub->chei[0];
					sub->copii[2] = sub->copii[0];
					sub->numarElementeCopii[2] = sub->numarElementeCopii[0];
					sub->chei[1] = n->chei[ki];
					sub->copii[1] = sib->copii[1];
					sub->numarElementeCopii[1] = sib->numarElementeCopii[1];
					if (sub->copii[1])
						sub->copii[1]->parinte = sub;
					sub->chei[0] = sib->chei[0];
					sub->copii[0] = sib->copii[0];
					sub->numarElementeCopii[0] = sib->numarElementeCopii[0];
					if (sub->copii[0])
						sub->copii[0]->parinte = sub;
					n->numarElementeCopii[ki + 1] = numarElemente(sub);
					my_free(sib);
					for (j = ki; j < 3 && n->copii[j + 1]; j++) {
						n->copii[j] = n->copii[j + 1];
						n->numarElementeCopii[j] = n->numarElementeCopii[j + 1];
						n->chei[j] = j < 2 ? n->chei[j + 1] : NULL;
					}
					n->copii[j] = NULL;
					n->numarElementeCopii[j] = 0;
					if (j < 3)
						n->chei[j] = NULL;

					if (!n->chei[0]) {
						arbore->Radacina = sub;
						sub->parinte = NULL;
						my_free(n);
					}
				}
			}
			n = sub;
		}
		if (!retval)
			retval = n->chei[ei];

		if (ei == -1)
			return NULL;
		if (!n->parinte && !n->chei[1] && !n->copii[0]) {
			my_free(n);
			arbore->Radacina = NULL;
			return retval;
		}
		if (!n->copii[0] && n->chei[1]) {
			int i;
			for (i = ei; i < 2 && n->chei[i + 1]; i++)
				n->chei[i] = n->chei[i + 1];
			n->chei[i] = NULL;
			while (n->parinte) {
				int childnum;
				childnum = (n->parinte->copii[0] == n ? 0 :
					n->parinte->copii[1] == n ? 1 :
					n->parinte->copii[2] == n ? 2 : 3);
				n->parinte->numarElementeCopii[childnum]--;
				n = n->parinte;
			}
			return retval;
		}
		else if (n->copii[ei]->chei[1]) {
			NodArbore *m = n->copii[ei];
			Element* target = my_new(Element);
			while (m->copii[0]) {
				m = (m->copii[3] ? m->copii[3] :
					m->copii[2] ? m->copii[2] :
					m->copii[1] ? m->copii[1] : m->copii[0]);
			}
			target = (m->chei[2] ? m->chei[2] :
				m->chei[1] ? m->chei[1] : m->chei[0]);
			n->chei[ei] = target;
			index = n->numarElementeCopii[ei] - 1;
			n = n->copii[ei];
		}
		else if (n->copii[ei + 1]->chei[1]) {

			NodArbore *m = n->copii[ei + 1];
			Element* target = my_new(Element);;
			while (m->copii[0]) {
				m = m->copii[0];
			}
			target = m->chei[0];
			n->chei[ei] = target;
			n = n->copii[ei + 1];
			index = 0;
		}
		else {
			NodArbore *a = n->copii[ei], *b = n->copii[ei + 1];
			int j;
			a->chei[1] = n->chei[ei];
			a->copii[2] = b->copii[0];
			a->numarElementeCopii[2] = b->numarElementeCopii[0];
			if (a->copii[2])
				a->copii[2]->parinte = a;
			a->chei[2] = b->chei[0];
			a->copii[3] = b->copii[1];
			a->numarElementeCopii[3] = b->numarElementeCopii[1];
			if (a->copii[3])
				a->copii[3]->parinte = a;
			my_free(b);
			n->numarElementeCopii[ei] = numarElemente(a);
			for (j = ei; j < 2 && n->chei[j + 1]; j++) {
				n->chei[j] = n->chei[j + 1];
				n->copii[j + 1] = n->copii[j + 2];
				n->numarElementeCopii[j + 1] = n->numarElementeCopii[j + 2];
			}
			n->chei[j] = NULL;
			n->copii[j + 1] = NULL;
			n->numarElementeCopii[j + 1] = 0;

			if (n->chei[0] == NULL) {
				arbore->Radacina = a;
				a->parinte = NULL;
				my_free(n);
			}
			n = a;
			index = a->numarElementeCopii[0] + a->numarElementeCopii[1] + 1;
		}
	}
}

Element* StergereIndex(Arbore * arbore, int index)
{
	int size = numarElemente(arbore->Radacina);
	if (index < 0 || index >= size)
		return NULL;
	return StergereElementIntern(arbore, index);
}

Element* Cauta(Arbore * arbore, Element* element, pFunctieComparare comparare, Relation relatie, int * index)
{
	NodArbore *n;
	Element* ret = my_new(Element);
	int c;
	int idx, ecount, kcount, cmpret;

	if (arbore->Radacina == NULL)
		return NULL;

	if (comparare == NULL)
		comparare = arbore->comparare;

	n = arbore->Radacina;
	idx = 0;
	ecount = -1;
	cmpret = 0;
	if (element == NULL)
	{
		if (relatie == Relation::LESS)
			cmpret = +1;
		else if (relatie == Relation::GREATER)
			cmpret = -1;
	}
	while (1)
	{
		for (kcount = 0; kcount < 4; kcount++) {
			if (kcount >= 3 || n->chei[kcount] == NULL ||
				(c = cmpret ? cmpret : comparare(element->value, n->chei[kcount]->value)) < 0)
			{
				break;
			}
			if (n->copii[kcount]) 
				idx += n->numarElementeCopii[kcount];
			if (c == 0) {
				ecount = kcount;
				break;
			}
			idx++;
		}
		if (ecount >= 0)
			break;
		if (n->copii[kcount])
			n = n->copii[kcount];
		else
			break;
	}

	if (ecount >= 0) {
		if (relatie != Relation::LESS && relatie != Relation::GREATER) {
			if (index) *index = idx;
			return n->chei[ecount];
		}
		if (relatie == Relation::LESS)
			idx--;
		else
			idx++;
	}
	else {
		if (relatie == Relation::EQUAL)
			return NULL;
		if (relatie == LESS || relatie == LESS_EQUAL) {
			idx--;
		}
	}
	ret = Index(arbore, idx);
	if (ret && index) *index = idx;
	return ret;
}

Element* StergeElement(Arbore * arbore, Element* element)
{
	int index;

	Element * elm = Cauta(arbore, element, NULL, Relation::EQUAL, &index);
	Element * elm2 = my_new(Element);
	ConstruiesteElement(elm2, -1, false);
	if (!elm)
		return NULL;
	if (elm->value == arbore->minimum->value)
	{
		elm = StergereElementIntern(arbore, index);
		Element *inf = my_new(Element);
		inf->value = INFINIT;
		arbore->minimum = minim(arbore->Radacina,inf);
	}
	else
	{
		elm = StergereElementIntern(arbore, index);
	}
	if (index != -1)
		return elm2;
	else
		return elm;

}

Element* Adauga_Arbore(Arbore* arbore, Element* e)
{
	if (arbore->comparare == NULL)
		return NULL;
	return Adauga_Arbore(arbore, e, -1);
}

Element* Adauga_Arbore(Arbore* arbore, Element* e, int index)
{
	NodArbore *n;
	int ki;
	Element* orig_e = e;
	int c;
	if (Compara(arbore->minimum, e) > 0)
	{
		arbore->minimum = e;
	}
	if (arbore->Radacina == NULL)
	{
		arbore->Radacina = my_new(NodArbore);
		arbore->Radacina->chei[1] = arbore->Radacina->chei[2] = NULL;
		arbore->Radacina->copii[0] = arbore->Radacina->copii[1] = NULL;
		arbore->Radacina->copii[2] = arbore->Radacina->copii[3] = NULL;
		arbore->Radacina->numarElementeCopii[0] = arbore->Radacina->numarElementeCopii[1] = 0;
		arbore->Radacina->numarElementeCopii[2] = arbore->Radacina->numarElementeCopii[3] = 0;
		arbore->Radacina->parinte = NULL;
		arbore->Radacina->chei[0] = e;
		arbore->Radacina->min = arbore->Radacina; // root contains the minimum
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
					return NULL;
			}
		}
		else {
			if ((c = arbore->comparare(e->value, n->chei[0]->value)) < 0)
				ki = 0;
			else if (c == 0)
				return n->chei[0];
			else if (n->chei[1] == NULL || (c = arbore->comparare(e->value, n->chei[1]->value)) < 0)
				ki = 1;
			else if (c == 0)
				return n->chei[1];
			else if (n->chei[2] == NULL || (c = arbore->comparare(e->value, n->chei[2]->value)) < 0)
				ki = 2;
			else if (c == 0)
				return n->chei[2];
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

int Inaltime(Arbore* arbore)
{
	int level = 0;
	NodArbore *n = arbore->Radacina;
	while (n) {
		level++;
		n = n->copii[0];
	}
	return level;
}

void Afisare(Arbore* arbore)
{
	Afisare(arbore->Radacina, 0, 0);
}