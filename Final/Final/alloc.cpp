#include "stdafx.h"
#include"alloc.h"

void *my_malloc(size_t size)
{
	void *p;
	p = malloc(size);
	if (!p)
	{
		fatal("out of memory");
	}
	return p;
}

void  my_free(void* pMemory)
{
	if (pMemory) {
		free(pMemory);
	}
}

void *my_realloc(void *p, size_t size)
{
	void *q;
	if (p) {
		q = realloc(p, size);
	}
	else {
		q = malloc(size);
	}
	if (!q)
	{
		fatal("out of memory");
	}
	return q;
}