#ifndef GAMESTATES_H
#define GAMESTATES_H

#include <SDL2/SDL.h>
#include <stdbool.h>

extern int (*gameState)(SDL_Window*, SDL_Renderer*, float);
extern bool running;

#include "gameStates/gameStateRunning.h"

#endif
