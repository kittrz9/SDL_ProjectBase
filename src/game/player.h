#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "entity.h"
#include "controls.h"
#include "animation.h"

typedef struct {
	vec2f pos, size, vel;
	float jumpTimer;
	animationStruct* animation;
	
	// Probably a really dumb way to draw the character looking a specific direction when moving
	bool facingLeft;
	bool moving;
} playerStruct;

struct entity* createPlayer(SDL_Renderer* renderer, float x, float y, float w, float h);

void drawPlayer(struct entity* ent, SDL_Renderer* renderer);
void destroyPlayer();
void updatePlayerInAir(struct entity* ent, double deltaTime);
void updatePlayerOnGround(struct entity* ent, double deltaTime);

#endif
