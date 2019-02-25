/* Main class
 * Jack Botelho CSC 412 Assignment 1
 */

#define USE_REPLACEMENT_MANAGER	1

#include <stdio.h>

#if USE_REPLACEMENT_MANAGER
	
	#undef malloc
	#define malloc myMalloc
	
	#undef free
	#define free myFree
	
	#include "replacementMalloc.h"

#else

	#include <stdlib.h>
	void* (*f)(size_t s) = malloc;
#endif

int main(int argc, const char * argv[]){

	char* a = (char*) malloc(300);
    printf("Round 2 \n");
	char* b = (char*) malloc(200);
    printf("Round 3 \n");
	char* c = (char*) malloc(100);
    printf("Round 4 \n");
    free(c);
    printf("Round 5 \n");
    free(b);
    printf("Round 6 \n");
    free(a);

   	if(USE_REPLACEMENT_MANAGER == 1){
   		myShutDown();
   	}


	return 0;
}
