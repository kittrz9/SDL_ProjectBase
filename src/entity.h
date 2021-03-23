#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

#include "types.h"

struct entity {
	// Could probably move these to the object
	//vec2f pos, size, vel;
	
	// Might be a bad approach to having the object be a void pointer to a struct
	// But whatever I'm stupid 
	void* object;

	// Having function pointers does kinda feel like I'm just creating C++ classes but in C but I feel like this could be better since you could probably make a sort of state machine by changing the update function pointer (i.e. changing it from like playerIdle to playerWalk or something when pressing left/right if you really want to have everything be seperate functions)
	void (*draw)(struct entity*, SDL_Renderer*);
	void (*update)(struct entity*, double);
};

// Linked list stuff
struct entListNode{
	struct entity* ent;
	struct entListNode* next;
	struct entListNode* prev;
};
extern struct entListNode* entListHead;
extern struct entListNode* entListCurrent;
extern struct entListNode* entListTail;

void pushToEntityList(struct entity* ent);
void removeFromEntityList(struct entity* ent);
void destroyEntityList();

#endif
