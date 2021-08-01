#ifndef GAMESTATERUNNING_H
#define GAMESTATERUNNING_H

#include <SDL2/SDL.h>
#include "gameStates.h"

void initGameStateRunning(SDL_Window*, SDL_Renderer*);
int runGameStateRunning(SDL_Window* screen, SDL_Renderer* renderer, float deltaTime);

static const gameState gameStateRunning = {
	.initState = initGameStateRunning,
	.stateLoop = runGameStateRunning
};

#endif
