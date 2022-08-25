#include "gameStates.h"

#include "renderer.h"

// These have to be here because of extern stuff
gameState* currentState = NULL;

bool running = true;

void initGameState(const gameState* newState){
	if(currentState != NULL) {
		(*(currentState->uninitState))();
	}
	
	(*(newState->initState))();
	// for some reason this gives a warning about the const qualifier being disregarded for newState
	// idk how I would fix this, if I get rid of the const in gameStateRunning then I get tons of "gameStateRunning defined but not used" warnings and if I put const in the parameters it gives the warning for this line
	currentState = newState;
}
