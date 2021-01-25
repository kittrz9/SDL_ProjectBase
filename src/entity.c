#include "entity.h"

#include <SDL2/SDL.h>

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
	printf("Entity %p pust to list at node %p\n", ent, entListCurrent);
	return;
}

void removeFromEntityList(struct entity* ent){
	for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
		if(entListCurrent->ent == ent){
			printf("Freeing entity at %p\n", entListCurrent->ent);
			if(entListHead != entListTail){
				entListCurrent->prev->next = entListCurrent->next;
			}
			free(entListCurrent->ent);
			free(entListCurrent);
			printf("Done\n");
			return;
		}
	}
	printf("Couldn't find entity %p\n", ent);
	return;
}
