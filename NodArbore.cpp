#include "NodArbore.h"

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
	dest->copii[i + 1] = src->copii[0];   dest->numarElementeCopii[i + 1] = src->numarElementeCopii[0];
	if (dest->copii[i + 1])
		dest->copii[i + 1]->parinte = dest;
	src->copii[0] = src->copii[1];      src->numarElementeCopii[0] = src->numarElementeCopii[1];
	src->chei[0] = src->chei[1];
	src->copii[1] = src->copii[2];      src->numarElementeCopii[1] = src->numarElementeCopii[2];
	src->chei[1] = src->chei[2];
	src->copii[2] = src->copii[3];      src->numarElementeCopii[2] = src->numarElementeCopii[3];
	src->chei[2] = 0;
	src->copii[3] = 0;              src->numarElementeCopii[3] = 0;
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


