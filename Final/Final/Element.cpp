#include "stdafx.h"
#include "Element.h"


void ConstruiesteElement(Element * e, int valoare, bool inList)
{
	e->inList = inList;
	e->value = valoare;
}

int  Compara(Element * stanga, Element * dreapta)
{
	if (stanga->value > dreapta->value)
		return 1;
	else if (stanga->value < dreapta->value)
	{
		return -1;
	}
	else
		return 0;
}
