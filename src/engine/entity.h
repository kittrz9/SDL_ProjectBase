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
	// Also might be a bad idea since it would lead to a lot of repeated code probably
	// Could probably have these function pointers be typedefs so they're more readable I guess but then the parameters would need the struct entity thing to be defined before them, but the struct entity needs the typedefs before it, so idk how I'd get that to work
	void (*draw)(struct entity*);
	void (*update)(struct entity*, double);
	
	// I've slowly and pretty much unintentionally recreated C++ classes lmao
	void (*destructor)();
};

// For stuff that either doesn't need to be drawn or updated I guess
// Doesn't take parameters so the compiler gives warnings but it doesn't do anything to the entity so it doesn't matter
void entityNOP(void);

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
void removeEntity(struct entity* ent);
void destroyEntityList();

#endif
