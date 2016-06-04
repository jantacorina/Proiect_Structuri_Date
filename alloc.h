#pragma once
#include <stdio.h>
#include <stdlib.h>

#ifndef size_t
typedef unsigned int size_t;
#endif // !size_t

#define fatal(error) printf(" %s " , error);exit(1);

void *my_malloc(size_t size);

void  my_free(void*pMemory);

void *my_realloc(void *p, size_t size);

#define my_new(type) \
    ( (type *) my_malloc (sizeof (type)) )

