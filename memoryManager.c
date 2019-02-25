/* Memory Manager
 * memoryManager.c
 * Jack Botelho
 */

#include <stdlib.h>
#include <stdio.h>

#define VERBOSE 1

typedef enum BlockType
{
	HOLE = 0,
	ALLOC
} BlockType;

typedef struct Node
{
	BlockType type;
	size_t size;
	char* startAddress;
	struct Node* prev;
	struct Node* next;
} Node;

//Local functions
void newHeap(void);
Node* newNode(Node* prev, size_t size);
void mergeHoles(Node* curr);
void heapLoop(Node* curr);
void shutDown(Node* curr);

//File-Level Global Variables
#define HEAP_SIZE 1000
char* heap_ = NULL;
Node* blockList_= NULL;

//Main funcs
void* allocate(size_t size_){
	if(heap_ == NULL){
		newHeap();
	}

	Node* test = blockList_; //holds the next node in the array
	do{	
		if(size_ <= test->size && test->type == HOLE){
			size_t newSize = test->size - size_;
			test->type = ALLOC;
			test->size = size_;
			test->next = newNode(test, newSize);
            if(VERBOSE == 1){
                heapLoop(blockList_);
            }
			return test->startAddress;
		}
        test = test->next;
	} while(test != NULL);
    
    if(VERBOSE == 1){
        heapLoop(blockList_);
    }
	return NULL;
}

void mmFree(void* sA){
	Node* test = blockList_;
	while(test != NULL){
		if(test->startAddress == sA){
			mergeHoles(test);
            if(VERBOSE == 1){
                heapLoop(blockList_);
            }
			return;
		}
        test = test->next;
	}
	printf("Error: Address not found!\n");
    if(VERBOSE == 1){
        heapLoop(blockList_);
    }
	return;
}

void heapList(){
	if(blockList_ == NULL){
		printf("No blockList_!\n");
		return;
	}
	else{
		heapLoop(blockList_);
		return;
	}
}

void mmSD(){
	printf("Starting shutdown!\n");
	shutDown(blockList_);
	free(heap_);
	printf("Memory Freed.\n");
}

//Local functions
void newHeap(void){
	heap_ = malloc(sizeof(char*) * HEAP_SIZE);
    struct Node* temp = (struct Node *)malloc(sizeof(struct Node));
    *temp = (struct Node){ HOLE, HEAP_SIZE, heap_, NULL, NULL};
    blockList_ = temp;
}

Node* newNode(Node* prev, size_t size){
    struct Node* newGuy = (struct Node *)malloc(sizeof(struct Node));
    *newGuy = (struct Node){ HOLE, size, (prev->startAddress + size), prev, prev->next};
	return newGuy;
}

void mergeHoles(Node* curr){
	curr->type = HOLE;
	if(curr->next != NULL && curr->next->type == HOLE){
		size_t newSize = curr->size + curr->next->size;
		curr->size = newSize;
		curr->next = curr->next->next;
		mergeHoles(curr);
	}
	else if(curr->prev != NULL && curr->prev->type == HOLE){
		size_t newSize = curr->size + curr->prev->size;
		curr->size = newSize;
		curr->prev = curr->prev->prev;
		mergeHoles(curr);
	}
	else{
		return;
	}

}

void heapLoop(Node* curr){
	if(curr->type == ALLOC){
		printf("NODE IS ALLOC, SIZE: %zu. \n", curr->size);
	}
	else{
		printf("NODE IS FREE, SIZE: %zu. \n", curr->size);
	}

	if(curr->next != NULL){
		heapLoop(curr->next);
	}
	else{
		return;
	}
}

void shutDown(Node* curr){
	while(curr->next != NULL){
		shutDown(curr->next);
	}
	free(curr);
	return;
}
