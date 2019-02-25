/* replacementMalloc.h
 * Jack Botelho
 */

#ifndef REPLACMENT_MALLOC_H
#define REPLACMENT_MALLOC_H

#include <stddef.h>

void* myMalloc(size_t size);
void myFree(void* sA);
void myShutDown();

#endif // REPLACEMENT_MALLOC_H