#include "gameStates.h"

// These have to be here because of extern stuff
gameState* currentState;

bool running = true;

void initGameState(SDL_Window* window, SDL_Renderer* renderer, gameState* newState){
	(*(newState->initState))(window, renderer);
	// for some reason this gives a warning about the const qualifier being disregarded for newState
	// idk how I would fix this, if I get rid of the const in gameStateRunning then I get tons of "gameStateRunning defined but not used" warnings and if I put const in the parameters it gives the warning for this line
	currentState = newState;
}
