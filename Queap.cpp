#include "Queap.h"

void init(Queap * queap)
{
	Initializare(queap->lista_inlantuita);
//	queap->queap_arbore = Initializare();
}

void Insert(Queap * queap, int element)
{
	if (queap->n == 0)
		queap->minimElementeT = element;
	Inserare(queap->lista_inlantuita, element);
	if (element < queap->minimElementeT)
		queap->minimElementeT = element;
}
