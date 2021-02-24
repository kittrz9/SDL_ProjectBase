#include "entity.h"

#include <SDL2/SDL.h>

#define free(x) printf("Freeing %p\n", x); free(x); printf("Done\n");

struct entListNode* entListHead    = NULL;
struct entListNode* entListCurrent = NULL;
struct entListNode* entListTail    = NULL;

void pushToEntityList(struct entity* ent){
	if(!entListHead){
		printf("Initializing entity list\n");

		entListHead = (struct entListNode*) malloc(sizeof(struct entity));
		entListTail = entListHead;
		entListCurrent = entListHead;

		entListHead->ent = ent;
		entListHead->next = NULL;
		entListTail->prev = NULL;
	} else {
		printf("Pushing entity at %p to list\n", ent);

		entListCurrent = entListTail;
		entListCurrent->next = (struct entListNode*) malloc(sizeof(struct entListNode));
		entListCurrent->next->ent = ent;
		entListCurrent->next->next = NULL;
		entListCurrent->next->prev = entListCurrent;
		entListTail = entListCurrent->next;
	}
	printf("Entity %p pushed to list at node %p\n", ent, entListCurrent);
	return;
}

void removeFromEntityList(struct entity* ent){
	struct entListNode* temp;
	for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
		// Check if there's only one entity left in the list
		if(entListHead == entListTail){
			free(entListHead);
			return;
		}
		if(entListCurrent->ent == ent){
			temp = entListCurrent->next;
			if(entListCurrent == entListHead){
				entListHead = entListHead->next;
			}
			if(entListCurrent == entListTail){
				entListTail = entListTail->prev;
			}
			free(entListCurrent);
			entListCurrent = temp;
			return;
		}
	}
	printf("Could not find entity at %p\n", ent);
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
