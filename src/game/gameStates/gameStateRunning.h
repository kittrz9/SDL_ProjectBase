#ifndef GAMESTATERUNNING_H
#define GAMESTATERUNNING_H

#include <SDL2/SDL.h>
#include "gameStates.h"

void initGameStateRunning();
void uninitGameStateRunning();
int runGameStateRunning(float deltaTime);

static const gameState gameStateRunning = {
	.initState = initGameStateRunning,
	.uninitState = uninitGameStateRunning,
	.stateLoop = runGameStateRunning
};

#endif
