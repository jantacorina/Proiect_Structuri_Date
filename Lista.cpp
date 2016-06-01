#include "Lista.h"
#include <string.h>
#include <stdlib.h>


void Initializare(Lista* pLista)
{
	// aloc un element de 
	pLista = (Lista*)calloc(1, sizeof(pLista));
	pLista->size = 0;
}

void Inserare(Lista* pLista, int element)
{
	if (pLista == NULL)
	{
		return;
	}
	Nod * temp = (Nod*)calloc(1, sizeof(Nod));
	temp->valoare = element;

	if (!pLista->pointerUltim)
	{
		pLista->pointerPrim = temp;
		pLista->pointerUltim = temp;
	}
	else
	{
		pLista->pointerUltim->urmator = temp;
		temp->anterior = pLista->pointerUltim;
		pLista->pointerUltim = temp;
	}
}

int Stergere(Lista* pLista, Nod* element)
{
	if (pLista != NULL || !Lungime(pLista))
		return -1;
	if (element == pLista->pointerPrim && element == pLista->pointerUltim)
		pLista->pointerPrim = pLista->pointerUltim = NULL;
	else if (element == pLista->pointerPrim)
	{
		pLista->pointerPrim = element->urmator;
		pLista->pointerPrim->anterior = 0;
	}
	else if (element == pLista->pointerUltim)
	{
		pLista->pointerUltim = element->anterior;
		pLista->pointerUltim->urmator = NULL;
	}
	else {
		Nod* next = element->urmator;
		Nod* prev = element->anterior;
		next->anterior = prev;
		prev->urmator = next;
	}
	pLista->size--;
	return 1;
}

int Lungime(Lista * pLista)
{
	if (pLista == NULL)
		return -1;
	return pLista->size;
}