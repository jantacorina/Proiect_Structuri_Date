#pragma once
struct Element {
	int value;
	bool inList;
};


void ConstruiesteElement(Element* e,int, bool);

bool Compara(Element* stanga,Element* dreapta);
