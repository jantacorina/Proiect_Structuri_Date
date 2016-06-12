#include "stdafx.h"
#include "Lista.h"
#include <string.h>
#include <stdlib.h>


void Initializare(Lista** pLista)
{
	// aloc un element de 
	*pLista = my_new(Lista);
	(*pLista)->size = 0;
	(*pLista)->pointerPrim = (*pLista)->pointerUltim = NULL;
}

void Inserare(Lista* pLista, Element* element)
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

void Clean(Lista * pLista)
{
	Nod * pNod = pLista->pointerPrim;
	Nod * pTemp = pNod;
	while (pNod != NULL)
	{
		pTemp = pNod->urmator;
		free(pNod);
		pNod = pTemp;
	}
	pLista->pointerPrim = pLista->pointerUltim = NULL;
	pLista = NULL;
}

void Afisare(Lista* pLista)
{
	printf("Lista = ");
	Nod * pNod = pLista->pointerPrim;
	while (pNod != NULL)
	{
		printf("%d, ", pNod->valoare);
		pNod = pNod->urmator;
	}
	printf("\n");
}

void Afisare(Lista* pLista, HDC hdc,int startX,int startY,int arcLength)
{
	if (pLista == NULL || pLista->pointerPrim == NULL)
		return;
	HPEN hLinePen, hPenOld;
	COLORREF qLineColor  = RGB(0,0,255);
	int curentIndexX = startX;
	int curentIndexY = startY;
	Nod * pNod = pLista->pointerPrim;
	char temp[10];
	wchar_t wtext[10];


	while (pNod != NULL)
	{
		sprintf(temp, "%d", pNod->valoare->value);
		mbstowcs(wtext, temp, strlen(temp) + 1);
		TextOut(hdc, curentIndexX, curentIndexY, wtext, strlen(temp)+1);

		hLinePen = CreatePen(PS_SOLID, 2, qLineColor);
		hPenOld = (HPEN)SelectObject(hdc, hLinePen);
		Arc(hdc, curentIndexX- arcLength, curentIndexY - arcLength/2, curentIndexX + arcLength, curentIndexY+arcLength/2, 0, 0, 0, 0);
		
		SelectObject(hdc, hPenOld);
		DeleteObject(hLinePen);

		pNod = pNod->urmator;
		if (pNod != NULL)
		{
			qLineColor = RGB(0, 0, 255);
			hLinePen = CreatePen(PS_SOLID, 2, qLineColor);
			hPenOld = (HPEN)SelectObject(hdc, hLinePen);
			MoveToEx(hdc, curentIndexX, curentIndexY, NULL);
			LineTo(hdc, curentIndexX + 3 * arcLength, curentIndexY);
			SelectObject(hdc, hPenOld);
			DeleteObject(hLinePen);
		}
		curentIndexX += 3*arcLength;
	}
}

Element* Cauta(Lista* pLista,int element)
{
	Nod * pNod = pLista->pointerPrim;
	while (pNod != NULL)
	{
		if (pNod->valoare->value == element)
			return pNod->valoare;
		pNod = pNod->urmator;
	}
	return NULL;
}