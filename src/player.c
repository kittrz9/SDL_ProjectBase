#include "player.h"
 
void drawPlayer(struct entity* ent, SDL_Renderer* renderer){
	SDL_Rect rect; // Maybe like unoptimal to have this always being created every time the player needs to be drawn but idk maybe the compiler will optimize it? I also feel like it's better than when I just had the SDL_Rect in the entity's struct
	rect.x = ent->pos.x;
	rect.y = ent->pos.y;
	rect.w = ent->size.x;
	rect.h = ent->size.y;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
}

void updatePlayer(struct entity* ent, double deltaTime){
	ent->pos.x += ent->vel.x * deltaTime;
	ent->pos.y += ent->vel.y * deltaTime;

	// Probably should have the controls be passed by like a pointer but it feels weird to have the controls be passed to every entity
	if(keys[UP].held) {
		ent->vel.y = -2;
	} else if(keys[DOWN].held) {
		ent->vel.y =  2;
	} else {
		ent->vel.y =  0;
	}
	
	if(keys[LEFT].held) {
		ent->vel.x = -2;
	} else if(keys[RIGHT].held) {
		ent->vel.x =  2;
	} else {
		ent->vel.x =  0;
	}
	
	
	// Boundary check
	if(ent->pos.x < 0) {ent->pos.x = 0;}
	if(ent->pos.y < 0) {ent->pos.y = 0;}
	// Really need to fix these numbers here but I don't really want to right now
	if(ent->pos.x > 800 - ent->size.x) {ent->pos.x = 800 - ent->size.x;}
	if(ent->pos.y > 600 - ent->size.y) {ent->pos.y = 600 - ent->size.y;}
}
