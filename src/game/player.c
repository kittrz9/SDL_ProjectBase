#include "player.h"

#include "defines.h"

#define playerObj ((playerStruct*)(ent->object))

struct entity* createPlayer(float x, float y, float w, float h){
	// Create player entity
	struct entity* ent = malloc(sizeof(struct entity));
	ent->object = malloc(sizeof(playerStruct));
	playerObj->pos.x = x;
	playerObj->pos.y = y;
	playerObj->size.x = w;
	playerObj->size.y = h;
	ent->draw = drawPlayer;
	ent->update = updatePlayer;
	pushToEntityList(ent);
	return ent;
}

void drawPlayer(struct entity* ent, SDL_Renderer* renderer){
	SDL_Rect rect;
	rect.x = playerObj->pos.x;
	rect.y = playerObj->pos.y;
	rect.w = playerObj->size.x;
	rect.h = playerObj->size.y;

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	SDL_RenderDrawRect(renderer, &rect);
}

void updatePlayer(struct entity* ent, double deltaTime){
	playerObj->pos.x += playerObj->vel.x * deltaTime;
	playerObj->pos.y += playerObj->vel.y * deltaTime;

	// Probably should have the controls be passed by like a pointer but it feels weird to have the controls be passed to every entity
	if(keys[UP].held) {
		playerObj->vel.y = -2;
	} else if(keys[DOWN].held) {
		playerObj->vel.y =  2;
	} else {
		playerObj->vel.y =  0;
	}
	
	if(keys[LEFT].held) {
		playerObj->vel.x = -2;
	} else if(keys[RIGHT].held) {
		playerObj->vel.x =  2;
	} else {
		playerObj->vel.x =  0;
	}
	
	
	// Boundary check
	if(playerObj->pos.x < 0) {playerObj->pos.x = 0;}
	if(playerObj->pos.y < 0) {playerObj->pos.y = 0;}
	if(playerObj->pos.x > WIDTH - playerObj->size.x) {playerObj->pos.x = WIDTH - playerObj->size.x;}
	if(playerObj->pos.y > HEIGHT - playerObj->size.y) {playerObj->pos.y = HEIGHT - playerObj->size.y;}
}
