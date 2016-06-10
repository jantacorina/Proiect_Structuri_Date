#include"Queap.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int main()
{

	Queap *q = my_new(Queap);
	init(q);
	Element* twoElement = Insert(q, 2);
	Insert(q, 3);
	Insert(q, 4);
	Insert(q, 5);
	Insert(q, 6);
	Insert(q, 7);
	Insert(q, 8);
	Insert(q, 9);
	Insert(q, 10);
	Insert(q, 11);
	Insert(q,12);
	Insert(q, 13);
	Insert(q, 14);
	Insert(q, 15);
	Insert(q, 16);
	Insert(q, 17);
	Insert(q, 18);
	Stergere(q, twoElement);
}