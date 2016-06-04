#include "NodArbore.h"
#include "alloc.h"

void Dezalocare(NodArbore * nod)
{
		if (!nod)
			return;
		Dezalocare(nod->copii[0]);
		Dezalocare(nod->copii[1]);
		Dezalocare(nod->copii[2]);
		Dezalocare(nod->copii[3]);
		free(nod);
}

int InsererazaCheieNod(NodArbore * nod,int key)
{
	for (auto i = nod->numarCopii - 1; i >= 0; --i) {

		if (key < nod->chei[i]) { //daca key[i] este mai mare

			nod->chei[i + 1] = nod->chei[i]; // muta mai la dreapta

		}
		else {

			nod->chei[i + 1] = key; // insereaza element nou
			++nod->numarCopii;        // mareste numarul total de elemente
			return i + 1;      // returneaza indexul cheii inserate
		}
	}
	// cheia este asemena ca celelalte chei deci inserez pe prima pozitie
	nod->chei[0] = key;
	++nod->numarCopii; //mareste numarul total de elemente
	return 0;
}

int numarElemente(NodArbore * nod)
{
	int count = 0;
	int i;
	if (nod == 0)
		return 0;
	for (i = 0; i < 4; i++)
		count += nod->numarElementeCopii[i];
	for (i = 0; i < 3; i++)
		if (nod->chei[i])
			count++;
	return count;
}

void TransformareArboreStanga(NodArbore * nod, int ki, int * k, int * index)
{
	NodArbore *src, *dest;
	int i, adjust;

	src = nod->copii[ki];
	dest = nod->copii[ki - 1];
	i = (dest->chei[1] ? 2 : dest->chei[0] ? 1 : 0);
	dest->chei[i] = nod->chei[ki - 1];
	nod->chei[ki - 1] = src->chei[0];
	dest->copii[i + 1] = src->copii[0];  
	dest->numarElementeCopii[i + 1] = src->numarElementeCopii[0];
	if (dest->copii[i + 1])
		dest->copii[i + 1]->parinte = dest;
	src->copii[0] = src->copii[1];     
	src->numarElementeCopii[0] = src->numarElementeCopii[1];
	src->chei[0] = src->chei[1];
	src->copii[1] = src->copii[2];    
	src->numarElementeCopii[1] = src->numarElementeCopii[2];
	src->chei[1] = src->chei[2];
	src->copii[2] = src->copii[3];     
	src->numarElementeCopii[2] = src->numarElementeCopii[3];
	src->chei[2] = 0;
	src->copii[3] = 0;              
	src->numarElementeCopii[3] = 0;
	adjust = dest->numarElementeCopii[i + 1] + 1;
	nod->numarElementeCopii[ki] -= adjust;
	nod->numarElementeCopii[ki - 1] += adjust;
	if (k) {
		if ((*k) == ki) {
			(*index) -= adjust;
			if ((*index) < 0) {
				(*index) += nod->numarElementeCopii[ki - 1] + 1;
				(*k)--;
			}
		}
	}

}

void TransformareArboreDreapta(NodArbore * n, int ki, int * k, int * index)
{
	NodArbore *src, *dest;
	int i, srclen, adjust;

	src = n->copii[ki];
	dest = n->copii[ki + 1];

	dest->copii[3] = dest->copii[2];    
	dest->numarElementeCopii[3] = dest->numarElementeCopii[2];
	dest->chei[2] = dest->chei[1];
	dest->copii[2] = dest->copii[1];    
	dest->numarElementeCopii[2] = dest->numarElementeCopii[1];
	dest->chei[1] = dest->chei[0];
	dest->copii[1] = dest->copii[0];    
	dest->numarElementeCopii[1] = dest->numarElementeCopii[0];

	i = (src->chei[2] ? 2 : src->chei[1] ? 1 : 0);

	dest->chei[0] = n->chei[ki];
	n->chei[ki] = src->chei[i];
	src->chei[i] = NULL;

	dest->copii[0] = src->copii[i + 1];  
	dest->numarElementeCopii[0] = src->numarElementeCopii[i + 1];
	src->copii[i + 1] = NULL;           
	src->numarElementeCopii[i + 1] = 0;
	if (dest->copii[0]) 
		dest->copii[0]->parinte = dest;
	adjust = dest->numarElementeCopii[0] + 1;

	n->numarElementeCopii[ki] -= adjust;
	n->numarElementeCopii[ki + 1] += adjust;

	srclen = n->numarElementeCopii[ki];

	if (k) {
		if ((*k) == ki && (*index) > srclen) {
			(*index) -= srclen + 1;
			(*k)++;
		}
		else if ((*k) == ki + 1) {
			(*index) += adjust;
		}
	}
}

void ImbinaArbori(NodArbore * nod, int ki, int * k, int * index)
{
	NodArbore *left, *right;
	int i, leftlen, rightlen, lsize, rsize;

	left = nod->copii[ki];              
	leftlen = nod->numarElementeCopii[ki];
	right = nod->copii[ki + 1];            
	rightlen = nod->numarElementeCopii[ki + 1];

	lsize = (left->chei[1] ? 2 : left->chei[0] ? 1 : 0);
	rsize = (right->chei[1] ? 2 : right->chei[0] ? 1 : 0);

	left->chei[lsize] = nod->chei[ki];

	for (i = 0; i < rsize + 1; i++) {
		left->chei[lsize + 1 + i] = right->chei[i];
		left->numarElementeCopii[lsize + 1 + i] = right->numarElementeCopii[i];
		if (left->copii[lsize + 1 + i])
			left->copii[lsize + 1 + i]->parinte = left;
		if (i < rsize)
			left->chei[lsize + 1 + i] = right->chei[i];
	}

	nod->numarElementeCopii[ki] += rightlen + 1;
	free(right);


	for (i = ki + 1; i < 3; i++) {
		nod->copii[i] = nod->copii[i + 1];
		nod->numarElementeCopii[i] = nod->numarElementeCopii[i + 1];
	}
	for (i = ki; i < 2; i++) {
		nod->chei[i] = nod->chei[i + 1];
	}
	nod->copii[3] = NULL;
	nod->numarElementeCopii[3] = 0;
	nod->chei[2] = NULL;

	if (k) {
		if ((*k) == ki + 1) {
			(*k)--;
			(*index) += leftlen + 1;
		}
		else if ((*k) > ki + 1) {
			(*k)--;
		}
	}
}

int StergeCheie(NodArbore* nod, int index)
{
	int cheie = nod->chei[index];

	for (int i = index; i < nod->numarCopii; i++)
		nod->chei[i] = nod->chei[i + 1];

	--nod->numarCopii;
	return cheie;
}

int Intern_Adauga_Arbore(NodArbore * left, int e, NodArbore * right, NodArbore** root, NodArbore*n, int ki)
{
	int lcount, rcount;
	lcount = numarElemente(left);
	rcount = numarElemente(right);
	while (n) {
		if (n->chei[1] == NULL) {
			/*
			* Inserarea in stanga unui  nod cu 2 chei
			*/
			if (ki == 0) {
				n->copii[2] = n->copii[1];
				n->numarElementeCopii[2] = n->numarElementeCopii[1];
				n->chei[1] = n->chei[0];
				n->copii[1] = right;
				n->numarElementeCopii[1] = rcount;
				n->chei[0] = e;
				n->copii[0] = left;
				n->numarElementeCopii[0] = lcount;
			}
			else
			{
				/*
				* Inserarea in dreapta unui  nod cu 2 chei
				*/
				n->copii[2] = right;
				n->numarElementeCopii[2] = rcount;
				n->chei[1] = e;
				n->copii[1] = left;
				n->numarElementeCopii[1] = lcount;
			}
			if (n->copii[0]) n->copii[0]->parinte = n;
			if (n->copii[1]) n->copii[1]->parinte = n;
			if (n->copii[2]) n->copii[2]->parinte = n;
			break;
		}
		else if (n->chei[2] == NULL) {
			/*
			* Inserarea int-un nod cu 3 chei
			*/
			if (ki == 0) {
				/*
				* Inserarea in stanga unui  nod cu 3 chei
				*/
				n->copii[3] = n->copii[2];
				n->numarElementeCopii[3] = n->numarElementeCopii[2];
				n->chei[2] = n->chei[1];
				n->copii[2] = n->copii[1];
				n->numarElementeCopii[2] = n->numarElementeCopii[1];
				n->chei[1] = n->chei[0];
				n->copii[1] = right;
				n->numarElementeCopii[1] = rcount;
				n->chei[0] = e;
				n->copii[0] = left;
				n->numarElementeCopii[0] = lcount;
			}
			else if (ki == 1) {
				/*
				* Inserarea in mijlocul unui  nod cu 3 chei
				*/
				n->copii[3] = n->copii[2];
				n->numarElementeCopii[3] = n->numarElementeCopii[2];
				n->chei[2] = n->chei[1];
				n->copii[2] = right;
				n->numarElementeCopii[2] = rcount;
				n->chei[1] = e;
				n->copii[1] = left;
				n->numarElementeCopii[1] = lcount;
			}
			else { /* ki == 2 */
				   /*
				   * Inserarea in dreapta unui  nod cu 3 chei
				   */
				n->copii[3] = right;         n->numarElementeCopii[3] = rcount;
				n->chei[2] = e;
				n->copii[2] = left;          n->numarElementeCopii[2] = lcount;
			}
			if (n->copii[0]) n->copii[0]->parinte = n;
			if (n->copii[1]) n->copii[1]->parinte = n;
			if (n->copii[2]) n->copii[2]->parinte = n;
			if (n->copii[3]) n->copii[3]->parinte = n;
			break;
		}
		else
		{
			NodArbore *m = my_new(NodArbore);
			m->parinte = n->parinte;
			/*
			* Impartirea unui nod cu 4 chei ...
			*;
			/*
			* Inserarere intr-un nod cu 4 chei impartirea in doua noduri cu 3/2 chei
			* si mutarea cu un nivel mai sus
			*Nu conteaza ordinea in care le asezam
			*/
			if (ki == 0)
			{
				m->copii[0] = left;          m->numarElementeCopii[0] = lcount;
				m->chei[0] = e;
				m->copii[1] = right;         m->numarElementeCopii[1] = rcount;
				m->chei[1] = n->chei[0];
				m->copii[2] = n->copii[1];    m->numarElementeCopii[2] = n->numarElementeCopii[1];
				e = n->chei[1];
				n->copii[0] = n->copii[2];    n->numarElementeCopii[0] = n->numarElementeCopii[2];
				n->chei[0] = n->chei[2];
				n->copii[1] = n->copii[3];    n->numarElementeCopii[1] = n->numarElementeCopii[3];
			}
			else if (ki == 1) {
				m->copii[0] = n->copii[0];    m->numarElementeCopii[0] = n->numarElementeCopii[0];
				m->chei[0] = n->chei[0];
				m->copii[1] = left;          m->numarElementeCopii[1] = lcount;
				m->chei[1] = e;
				m->copii[2] = right;         m->numarElementeCopii[2] = rcount;
				e = n->chei[1];
				n->copii[0] = n->copii[2];    n->numarElementeCopii[0] = n->numarElementeCopii[2];
				n->chei[0] = n->chei[2];
				n->copii[1] = n->copii[3];    n->numarElementeCopii[1] = n->numarElementeCopii[3];
			}
			else if (ki == 2) {
				m->copii[0] = n->copii[0];    m->numarElementeCopii[0] = n->numarElementeCopii[0];
				m->chei[0] = n->chei[0];
				m->copii[1] = n->copii[1];    m->numarElementeCopii[1] = n->numarElementeCopii[1];
				m->chei[1] = n->chei[1];
				m->copii[2] = left;          m->numarElementeCopii[2] = lcount;
				/* e = e; */
				n->copii[0] = right;         n->numarElementeCopii[0] = rcount;
				n->chei[0] = n->chei[2];
				n->copii[1] = n->copii[3];    n->numarElementeCopii[1] = n->numarElementeCopii[3];
			}
			else { /* ki == 3 */
				m->copii[0] = n->copii[0];    m->numarElementeCopii[0] = n->numarElementeCopii[0];
				m->chei[0] = n->chei[0];
				m->copii[1] = n->copii[1];    m->numarElementeCopii[1] = n->numarElementeCopii[1];
				m->chei[1] = n->chei[1];
				m->copii[2] = n->copii[2];    m->numarElementeCopii[2] = n->numarElementeCopii[2];
				n->copii[0] = left;          n->numarElementeCopii[0] = lcount;
				n->chei[0] = e;
				n->copii[1] = right;         n->numarElementeCopii[1] = rcount;
				e = n->chei[2];
			}
			m->copii[3] = n->copii[3] = n->copii[2] = NULL;
			m->numarElementeCopii[3] = n->numarElementeCopii[3] = n->numarElementeCopii[2] = 0;
			m->chei[2] = n->chei[2] = n->chei[1] = NULL;
			if (m->copii[0]) m->copii[0]->parinte = m;
			if (m->copii[1]) m->copii[1]->parinte = m;
			if (m->copii[2]) m->copii[2]->parinte = m;
			if (n->copii[0]) n->copii[0]->parinte = n;
			if (n->copii[1]) n->copii[1]->parinte = n;
			left = m;  lcount = numarElemente(left);
			right = n; rcount = numarElemente(right);
		}
		if (n->parinte)
			ki = (n->parinte->copii[0] == n ? 0 :
				n->parinte->copii[1] == n ? 1 :
				n->parinte->copii[2] == n ? 2 : 3);
		n = n->parinte;
	}
	if (n) {
		while (n->parinte) {
			int count = numarElemente(n);
			int childnum;
			childnum = (n->parinte->copii[0] == n ? 0 :
				n->parinte->copii[1] == n ? 1 :
				n->parinte->copii[2] == n ? 2 : 3);
			n->parinte->numarElementeCopii[childnum] = count;
			n = n->parinte;
		}
		return 0;
	}
	else
	{
		(*root) = my_new(NodArbore);
		(*root)->copii[0] = left;     (*root)->numarElementeCopii[0] = lcount;
		(*root)->chei[0] = e;
		(*root)->copii[1] = right;    (*root)->numarElementeCopii[1] = rcount;
		(*root)->chei[1] = NULL;
		(*root)->copii[2] = NULL;     (*root)->numarElementeCopii[2] = 0;
		(*root)->chei[2] = NULL;
		(*root)->copii[3] = NULL;     (*root)->numarElementeCopii[3] = 0;
		(*root)->parinte = NULL;
		if ((*root)->copii[0]) (*root)->copii[0]->parinte = (*root);
		if ((*root)->copii[1]) (*root)->copii[1]->parinte = (*root);

		return 1;
	}
}

