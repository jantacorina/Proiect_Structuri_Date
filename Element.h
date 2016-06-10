#pragma once
#include"alloc.h"
struct Element {
	int value;
	bool inList;
};
void ConstruiesteElement(Element* e,int, bool);

int Compara(Element* stanga,Element* dreapta);
