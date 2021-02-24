#include "gameStates.h"

// These have to be here because of extern stuff
int (*gameState)(SDL_Window*, SDL_Renderer*, float) = runGameStateRunning;

bool running = true;
