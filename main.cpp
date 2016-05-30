#include"Arbore_4_3.h"
#include <assert.h>
int main()
{
	printf("Initializing.\n");
	Arbore *t = Initializare();
	printf("Size is: %d.\n", Lungime(t));

	printf("----------------------------\n");

	int i;
	for (i = 0; i < 10; i++) {
		printf("Inserting %d into Two Four Tree.\n", i);
		InsereazaInFata(t, i);
	}

	NodArbore* n = Cauta(t->Radacina, 1);
	//printf((char const *)n->esteFrunza);

	printf("----------------------------\n");
	Printeaza(t->Radacina);

	return 0;
}

