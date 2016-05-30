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
	/*if (pLista == NULL)
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
		pLista->pointerUltim->n
	}*/
}