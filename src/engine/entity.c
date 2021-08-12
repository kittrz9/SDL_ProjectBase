#include "entity.h"

#include <SDL2/SDL.h>

#include <stdio.h>

// Printf needs the pointer to be a void* to not get a warning with the -Wall option
#define free(x) printf("Freeing %p\n", (void*)x); free(x); printf("Done\n");

// For stuff that either doesn't need to be drawn or updated I guess
void entityNOP(void){return;}

struct entListNode* entListHead    = NULL;
struct entListNode* entListCurrent = NULL;
struct entListNode* entListTail    = NULL;

void pushToEntityList(struct entity* ent){
	if(entListHead == NULL){
		printf("Initializing entity list\n");
		entListHead = (struct entListNode*) malloc(sizeof(struct entity));
		entListTail = entListHead;
		entListCurrent = entListHead;
		entListCurrent->prev = NULL;
	} else {
		// Creates new entity at the end of the entity list
		entListTail->next = malloc(sizeof(struct entity));
		entListTail->next->prev = entListTail;
		entListTail = entListTail->next;
		entListCurrent = entListTail;
	}
	entListCurrent->ent = ent;
	entListCurrent->next = NULL;
	printf("Entity %p pushed to list at node %p\n", (void*)ent, (void*)entListCurrent);
	return;
}

void removeEntity(struct entity* ent){
	if(entListHead == NULL){
		printf("Entity list is empty\n");
		return;
	}
	
	// If there is only one entity in the list
	if(entListHead == entListTail){
		free(entListHead);
		entListHead = NULL;
		entListTail = NULL;
		entListCurrent = NULL;
		return;
	}
	
	for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
		if(entListCurrent->ent == ent){
			struct entListNode* temp;
			// Handling the entities at the ends of the list specifically because they're weird
			// Could probably do something much better than this but whatever
			if(entListCurrent == entListHead){
				entListHead->next->prev = NULL;
				temp = entListHead->next;
				free(entListHead);
				entListHead = temp;
				return;
			}
			if(entListCurrent == entListTail){
				entListHead->prev->next = NULL;
				temp = entListTail->prev;
				free(entListTail);
				entListTail = temp;
				return;
			}
			
			entListCurrent->prev->next = entListCurrent->next;
			entListCurrent->next->prev = entListCurrent->prev;
			free(entListCurrent);
			return;
		}
	}
	printf("Could not find entity at %p in the entity list\n", (void*)ent);
	return;
}

void destroyEntityList(){
	struct entListNode* temp;
	for(entListCurrent = entListHead; entListCurrent != NULL;){
		if(entListHead == entListTail){
			free(entListHead);
			return;
		}
		temp = entListCurrent->next;
		free(entListCurrent);
		entListCurrent = temp;
	}
	return;
}
