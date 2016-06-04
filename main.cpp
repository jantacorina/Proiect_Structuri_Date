#include"Arbore_4_3.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


Arbore * arbore;
int *array;
int arraylen, arraysize;
pFunctieComparare cmp;

int comparatie(int av, int bv) {
	if (av > bv)
		return 1;
	else if (av < bv)
		return -1;
	return 0;
}

#define NSTR lenof(ints)
#define lenof(x) ( sizeof((x)) / sizeof(*(x)) )

int ints[] = {
	1, 2, 3, 23,33,22,11,123,1,22,45,34,78,98,
	44,66,344,234,111,156,532,123,878,1111,91,
	12,24,65,99,96,10,7,1200,2100,2344,2354,2900,
	3276,3287,4343,657
#if 0
	"a", "ab", "absque", "coram", "de",
	"palam", "clam", "cum", "ex", "e",
	"sine", "tenus", "pro", "prae",
	"banana", "carrot", "cabbage", "broccoli", "onion", "zebra",
	"penguin", "blancmange", "pangolin", "whale", "hedgehog",
	"giraffe", "peanut", "bungee", "foo", "bar", "baz", "quux",
	"murfl", "spoo", "breen", "flarn", "octothorpe",
	"snail", "tiger", "elephant", "octopus", "warthog", "armadillo",
	"aardvark", "wyvern", "dragon", "elf", "dwarf", "orc", "goblin",
	"pixie", "basilisk", "warg", "ape", "lizard", "newt", "shopkeeper",
	"wand", "ring", "amulet"
#endif
};

void error(char *fmt, ...) {
	va_list ap;
	printf("ERROR: ");
	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	va_end(ap);
	printf("\n");
}
typedef struct {
	char **levels;
} dispctx;

typedef struct {
	int treedepth;
	int elemcount;
} chkctx;
int chknode(chkctx *ctx, int level, NodArbore *node,
	int lowbound, int highbound);
void internal_addtest(int elem, int index, int realret);
void delpostest(int i);

void verifytree(Arbore *tree, int *array, int arraylen) {
	chkctx ctx;
	int i;
	int p;

	ctx.treedepth = -1;               
	ctx.elemcount = 0;                

	if (tree->Radacina) {
		if (tree->Radacina->parinte != NULL)
			error("Radacina->Radacina is %p should be null", tree->Radacina);
		chknode(&ctx, 0, tree->Radacina, NULL, NULL);
	}
	printf("tree depth: %d\n", ctx.treedepth);
	/*
	* Enumerate the tree and ensure it matches up to the array.
	*/
	for (i = 0; NULL != (p = Index(tree, i)); i++) {
		if (i >= arraylen)
			error("tree contains more than %d elements", arraylen);
		if (array[i] != p)
			error("enum at position %d: array says %s, tree says %s",
				i, array[i], p);
	}
	if (ctx.elemcount != i) {
		error("tree really contains %d elements, enum gave %d",
			ctx.elemcount, i);
	}
	if (i < arraylen) {
		error("enum gave only %d elements, array has %d", i, arraylen);
	}
	i = numarElemente(tree);
	if (ctx.elemcount != i) {
		error("tree really contains %d elements, count234 gave %d",
			ctx.elemcount, i);
	}
}
void verify(void) { verifytree(arbore, array, arraylen); }

int chknode(chkctx *ctx, int level, NodArbore *node,
	int lowbound, int highbound) {
	int ncopii, nchei;
	int i;
	int count;

	/* Count the non-NULL copii. */
	for (ncopii = 0; ncopii < 4 && node->copii[ncopii]; ncopii++);
	/* Ensure no copii beyond the first NULL are non-NULL. */
	for (i = ncopii; i < 4; i++)
		if (node->copii[i]) {
			error("node %p: ncopii=%d but copii[%d] non-NULL",
				node, ncopii, i);
		}
		else if (node->numarElementeCopii[i]) {
			error("node %p: copii[%d] NULL but count[%d]=%d nonzero",
				node, i, i, node->numarElementeCopii[i]);
		}

		/* Count the non-NULL elements. */
		for (nchei = 0; nchei < 3 && node->chei[nchei]; nchei++);
		/* Ensure no elements beyond the first NULL are non-NULL. */
		for (i = nchei; i < 3; i++)
			if (node->chei[i]) {
				error("node %p: nchei=%d but chei[%d] non-NULL",
					node, nchei, i);
			}

		if (ncopii == 0) {
			/*
			* If ncopii==0, this is a leaf node; verify that the tree
			* depth is the same everywhere.
			*/
			if (ctx->treedepth < 0)
				ctx->treedepth = level;    /* we didn't know the depth yet */
			else if (ctx->treedepth != level)
				error("node %p: leaf at depth %d, previously seen depth %d",
					node, level, ctx->treedepth);
		}
		else {
			/*
			* If ncopii != 0, then it should be nchei+1, unless nchei
			* is 0 in which case ncopii should also be 0 (and so we
			* shouldn't be in this condition at all).
			*/
			int shouldcopii = (nchei ? nchei + 1 : 0);
			if (ncopii != shouldcopii) {
				error("node %p: %d chei should mean %d copii but has %d",
					node, nchei, shouldcopii, ncopii);
			}
		}

		/*
		* nchei should be at least 1.
		*/
		if (nchei == 0) {
			error("node %p: no chei", node, ncopii);
		}

		/*
		* Add nchei to the running element count of the whole tree.
		*/
		ctx->elemcount += nchei;

		/*
		* Check ordering property: all elements should be strictly >
		* lowbound, strictly < highbound, and strictly < each other in
		* sequence. (lowbound and highbound are NULL at edges of tree
		* - both NULL at root node - and NULL is considered to be <
		* everything and > everything. IYSWIM.)
		*/
		if (cmp) {
			for (i = -1; i < nchei; i++) {
				int lower = (i == -1 ? lowbound : node->chei[i]);
				int higher = (i + 1 == nchei ? highbound : node->chei[i + 1]);
				if (lower && higher && cmp(lower, higher) >= 0) {
					error("node %p: kid comparison [%d=%s,%d=%s] failed",
						node, i, lower, i + 1, higher);
				}
			}
		}

		/*
		* Check parent pointers: all non-NULL copii should have a
		* parent pointer coming back to this node.
		*/
		for (i = 0; i < ncopii; i++)
			if (node->copii[i]->parinte != node) {
				error("node %p kid %d: parent ptr is %p not %p",
					node, i, node->copii[i]->parinte, node);
			}
		count = nchei;

		for (i = 0; i < ncopii; i++) {
			int lower = (i == 0 ? lowbound : node->chei[i - 1]);
			int higher = (i >= nchei ? highbound : node->chei[i]);
			int subcount = chknode(ctx, level + 1, node->copii[i], lower, higher);
			if (node->numarElementeCopii[i] != subcount) {
				error("node %p kid %d: count says %d, subtree really has %d",
					node, i, node->numarElementeCopii[i], subcount);
			}
			count += subcount;
		}

		return count;
}
void addtest(int elem) {
	int i;
	int realret;
	realret = Adauga_Arbore(arbore, elem);
	i = 0;
	while (i < arraylen && arbore->comparare(elem, array[i]) > 0)
		i++;
	if (i < arraylen && !arbore->comparare(elem, array[i])) {
		int retval = array[i];       /* expect that returned not elem */
		if (realret != retval) {
			error("add: retval was %p expected %p", realret, retval);
		}
	}
	else
		internal_addtest(elem, i, realret);
}

void internal_addtest(int elem, int index, int realret) {
	int i, j;
	int retval;

	if (arraysize < arraylen + 1) {
		arraysize = arraylen + 1 + 256;
		array = (int*)(array == NULL ? my_malloc(arraysize * sizeof(*array)) :
			my_realloc(array, arraysize * sizeof(*array)));
	}

	i = index;
	/* now i points to the first element >= elem */
	retval = elem;                  /* expect elem returned (success) */
	for (j = arraylen; j > i; j--)
		array[j] = array[j - 1];
	array[i] = elem;                /* add elem to array */
	arraylen++;

	if (realret != retval) {
		error("add: retval was %p expected %p", realret, retval);
	}

	verify();
}

int randomnumber(unsigned *seed) {
	*seed *= 1103515245;
	*seed += 12345;
	return ((*seed) / 65536) % 32768;
}
void deltest(int elem) {
	int i;
	i = 0;
	while (i < arraylen && arbore->comparare(elem, array[i]) > 0)
		i++;
	if (i >= arraylen || arbore->comparare(elem, array[i]) != 0)
		return;                        /* don't do it! */
	delpostest(i);
}
void delpostest(int i) {
	int index = i;
	int elem = array[i],ret;
	while (i < arraylen - 1) {
		array[i] = array[i + 1];
		i++;
	}
	arraylen--;
	if (arbore->comparare)
		ret = StergereElement(arbore, elem);
	else
		ret = StergereIndex(arbore, index);

	if (ret != elem) {
		error("del returned %p, expected %p", ret, elem);
	}
	verify();
}
int main()
{
	int in[NSTR];
	int i, j, k;
	int tworoot, tmplen;
	unsigned seed = 0;
	Arbore *tree2, *tree3, *tree4;
	int c;
	for (i = 0; i < (int)NSTR; i++) 
		in[i] = 0;

	array = NULL;
	arraylen = arraysize = 0;
	arbore = Initializare(comparatie);

	verify();
	for (i = 0; i < 10000; i++) {
		j = randomnumber(&seed);
		j %= NSTR;
		printf("trial: %d\n", i);
		if (in[j]) {
			printf("deleting %d (%d)\n", ints[j], j);
			deltest(ints[j]);
			in[j] = 0;
		}
		else {
			printf("adding %d (%d)\n", ints[j], j);
			addtest(ints[j]);
			in[j] = 1;
		}
		//disptree(tree);
		//findtest();
	}
	//freetree234(tree);
}