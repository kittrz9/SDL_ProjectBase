#ifndef ENTITY_H
#define ENTITY_H

#include <SDL2/SDL.h>

typedef struct {
	float x, y;
} vec2f;

struct entity {
	vec2f pos, size, vel;

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

#endif
