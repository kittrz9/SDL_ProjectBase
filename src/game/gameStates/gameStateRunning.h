#ifndef GAMESTATERUNNING_H
#define GAMESTATERUNNING_H

#include <SDL2/SDL.h>
#include "gameStates.h"

void initGameStateRunning();
int runGameStateRunning(float deltaTime);

static const gameState gameStateRunning = {
	.initState = initGameStateRunning,
	.stateLoop = runGameStateRunning
};

#endif
