/* Memory Manager Header
 * memoryManager.h
 * Jack Botelho
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef MM_H_
#define MM_H_

void* allocate(size_t size);

void mmFree(void* sA);

void heapList();

void mmSD();

#endif // MM_H_