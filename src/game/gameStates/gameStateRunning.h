#ifndef GAMESTATERUNNING_H
#define GAMESTATERUNNING_H

#include <SDL2/SDL.h>
#include "gameStates.h"

void startGameStateRunning(SDL_Window*, SDL_Renderer*);
int runGameStateRunning(SDL_Window* screen, SDL_Renderer* renderer, float deltaTime);

static const gameState gameStateRunning = {
	.startState = startGameStateRunning,
	.stateLoop = runGameStateRunning
};

#endif
