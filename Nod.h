#pragma once
#include "Element.h"
#include "Nod.h"
struct Nod {
	Element* valoare;
	Nod * urmator;
	Nod* anterior;
};

