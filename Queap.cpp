#include "Queap.h"

#define INFINIT 100000
/// <summary>
/// Comparaties implicita.Folosita in procesul de inserare,stergere
/// </summary>
/// <param name="av">Parametru din stanga.</param>
/// <param name="bv">Parametrul din dreapta.</param>
/// <returns>int.</returns>
int comparatieImplicita(int av, int bv) {
	if (av > bv)
		return 1;
	else if (av < bv)
		return -1;
	return 0;
}

/// <summary>
/// Initializeaza structura de date
/// </summary>
/// <param name="queap">The queap.</param>
void init(Queap * queap)
{
	Initializare(&queap->lista_inlantuita);
	queap->queap_arbore = Initializare(comparatieImplicita);
	queap->n = 0;
	queap->k = 0;
}
/// <summary>
/// Inserts the specified queap.
/// </summary>
/// <param name="queap">The queap.</param>
/// <param name="element">The element.</param>
/// <returns>Element *.</returns>
Element* Insert(Queap * queap, int element)
{
	// creez un nou element
	Element *e = my_new(Element);
	ConstruiesteElement(e, element, true);
	// daca nu am niciun element atunci elementul ce urmeaza sa fie inserat devine minim
	if (queap->n == 0)
		queap->minimElementeT = e;
	// inserez elementul in lista
	Inserare(queap->lista_inlantuita, e);
	//il compar cu minimul
	if (Compara(e,queap->minimElementeT) == true)
		queap->minimElementeT = e;
	//incrementez numaru de elemente
	queap->n++;
	//returnez elementul inserat
	return e;

}

void Stergere(Queap* queap, Element* element)
{
	//  verifica, daca elementul se afla in lista
	if (element->inList == true)
	{
		// parcurgem lista
		Nod* nod_lista = queap->lista_inlantuita->pointerPrim;
		while (nod_lista != NULL)
		{
			//setam bitul inList pe false
			nod_lista->valoare->inList = false;
			Adauga_Arbore(queap->queap_arbore, nod_lista->valoare);
			nod_lista = nod_lista->urmator;
		}
		// golim lista
		Clean(queap->lista_inlantuita);
		// setam minimul pe INFINIT
		Element *elm = my_new(Element);
		ConstruiesteElement(elm,INFINIT, true);
		queap->minimElementeT = elm;
		queap->n = queap->k;
		StergeElement(queap->queap_arbore, element);
	}
	else
	{
		//stergem elementul din arbore
		StergeElement(queap->queap_arbore, element);
		//decrementam nr de elemente totale sin din arbore
		--queap->n;
		--queap->k;
	}

}

Element* Minimum(Queap* queap)
{
	if (Compara(queap->minimElementeT, queap->queap_arbore->minimum) < 0)
	{
		return queap->minimElementeT;
	}
	else
	{
		return queap->queap_arbore->minimum;
	}
}

Element* deleteMin(Queap* queap)
{
	Element* min = Minimum(queap);
	Stergere(queap, min);
	return min;
}