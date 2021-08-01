#include "gameStates.h"

// These have to be here because of extern stuff
gameState* currentState;

bool running = true;


void initGameState(SDL_Window* window, SDL_Renderer* renderer, gameState* newState){
	(*(newState->initState))(window, renderer);
	currentState = newState;
}
