#include "gameStates.h"

// These have to be here because of extern stuff
gameState* currentState;

bool running = true;


void startGameState(SDL_Window* window, SDL_Renderer* renderer, gameState* newState){
	(*(newState->startState))(window, renderer);
	currentState = newState;
}
