#pragma once
#include "stdafx.h"
#include "Arbore_4_3.h"
/***
* Structura de date principala contine toate elementele necesare cozii 
**/
/// <summary>
/// Struct Queap
/// </summary>
typedef struct Queap {
	/// <summary>
	/// Numarul de elemente toatle
	/// </summary>
	int n;
	/// <summary>
	/// Numarul de elemente din arbore
	/// </summary>
	int k;
	/// <summary>
	/// Elementul minim din arbore
	/// </summary>
	Element* minimElementeT;
	/// <summary>
	/// Pointer catre arborele 2-3-4
	/// </summary>
	Arbore* queap_arbore;
	/// <summary>
	/// O lista dublu inlantuita
	/// </summary>
	Lista* lista_inlantuita;
}Queap;

/***
* Initializeaza structura de date de tip queape
* @param queap - Pointer catre structura de date
*/
void init(Queap* queap);

/***
* Insereaza un nou element de tip intreg in structura de date
* @param queap - Pointer catre structura de date
* @element - elementul ce urmeaza sa fie inserat
* @return Returneaza elementul tocmai inserat
**/
Element* Insert(Queap* queap, int element);

/***
* Sterge un elemnt dat din structura de date
* @param queap - Pointer catre structura de date
* @element - elementul ce urmeaza sa fie sters
* @return Elementul sters sau NULL daca acesta nu este gasit
**/
Element* Stergere(Queap* queap, Element* element);

Element* Stergere(Queap* queap, int  element);

/***
* Returneaza minimul elemenelor din queap
* @param queap - Pointer catre structura de date
* @return Elementul minim
**/
Element* Minimum(Queap* queap);
/***
* Sterge minimul elementelor din @param queap
* @return Elementul sters
*/
Element* deleteMin(Queap* queap);

void Afisare(Queap* queap);

void Clean(Queap * queap);