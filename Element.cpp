#include "Element.h"


void ConstruiesteElement(Element * e, int valoare, bool inList)
{
	e->inList = inList;
	e->value = valoare;
}

bool Compara(Element * stanga, Element * dreapta)
{
	return stanga->value < dreapta->value;
}
