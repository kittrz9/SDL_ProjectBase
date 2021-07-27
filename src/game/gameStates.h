#ifndef GAMESTATES_H
#define GAMESTATES_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct { 
	void (*startState)(SDL_Window*, SDL_Renderer*); // function pointer to function that starts the game state
	// parameters: pointer to the current window to render to, pointer to the renderer, delta time
	int (*stateLoop)(SDL_Window*, SDL_Renderer*, float); // the game loop for this game state that gets run every frame
} gameState;

extern gameState* currentState;

//extern int (*gameState)(SDL_Window*, SDL_Renderer*, float);
extern bool running;

void startGameState(SDL_Window* window, SDL_Renderer* renderer, gameState* newState);

// includes other game states to be able to switch them from within them
#include "gameStates/gameStateRunning.h"

#endif
