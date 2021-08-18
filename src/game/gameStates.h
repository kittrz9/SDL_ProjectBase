#ifndef GAMESTATES_H
#define GAMESTATES_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct { 
	void (*initState)(); // function pointer to function that initializes the game state
	// parameters: pointer to the current window to render to, pointer to the renderer, delta time
	int (*stateLoop)(float); // the game loop for this game state that gets run every frame
} gameState;

extern gameState* currentState;

//extern int (*gameState)(SDL_Window*, SDL_Renderer*, float);
extern bool running;

void initGameState(gameState* newState);

// includes other game states to be able to switch them from within them
#include "gameStates/gameStateRunning.h"

#endif
