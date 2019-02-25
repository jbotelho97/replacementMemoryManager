/* replacementMalloc.c
 * Jack Botelho
 */

#include "memoryManager.h"
#include "replacementMalloc.h"

void* myMalloc(size_t size){
	return allocate(size);
}

void myFree(void* sA){
	mmFree(sA);
}

void myShutDown(){
	mmSD();
}
