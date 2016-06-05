#include "Queap.h"

void init(Queap * queap)
{
	Initializare(&queap->lista_inlantuita);
	queap->queap_arbore = my_new(Arbore_4_3);
	queap->n = 0;
	queap->k = 0;
}

void Insert(Queap * queap, int element)
{
	Element *e = my_new(Element);
	ConstruiesteElement(e, element, true);
	if (queap->n == 0)
		queap->minimElementeT = e;
	Inserare(queap->lista_inlantuita, *e);
	if (Compara(e,queap->minimElementeT) == true)
		queap->minimElementeT = e;
	queap->n++;

}

void Stergere(Queap* queap, int element)
{
	NodArbore arbore;
}
