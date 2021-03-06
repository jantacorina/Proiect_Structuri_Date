#pragma once
#include "NodArbore.h"
/**
*  Structura de tip Lista.
*  @pointerPrim - Pointer la primul element din lista
*  @pointerUltim - Poiner la ultimul element din lista
**/
struct Lista {
	Nod * pointerPrim;
	Nod*  pointerUltim;
	int size;
};
/***
	Initializez lista
	@pLista pointer la lista care urmeaza sa fie initializata
**/
void Initializare(Lista** pLista);

/***
* Insereaza element in lista inlantuita
*  @pLista - Pointer la elementul ce urmmeaza sa fie inserat
*  @element - Elementul care urmeaza sa fie inserat
**/
void Inserare(Lista* pLista, Element* element);

/***
* Sterge un elemnt din lista inlantuita
* @pLista - Pointer la inceputul listei 
* @nod    - Elementul care urmeaza sa fie sters
* @return  1 - Daca elementul a fost sters cu succes
*		  -1 - Daca stergerea nu a fost efectuata cu succes ( elementul nu a fost gasit)
**/
int Stergere(Lista* pLista, Nod* nod);

/***
* Returneaza numarul de elemente din lista primita ca parametru
* @pLista  - Pointer la lista 
* @return  - returneaza numarul de elemente dinn lista inlantuita
**/
int Lungime(Lista * pLista);


/***
*Dezaloca intreaga lista
* @pLista  - Pointer la lista 
**/
void Clean(Lista * pLista);


void Afisare(Lista* Lista);

void Afisare(Lista* pLista, HDC hdc, int startX, int startY, int arcLength);

Element* Cauta(Lista* pLista,int element);

