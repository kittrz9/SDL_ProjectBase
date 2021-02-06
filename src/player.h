#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

#include "entity.h"
#include "controls.h"

void drawPlayer(struct entity* ent, SDL_Renderer* renderer);

void updatePlayer(struct entity* ent, double deltaTime);

#endif
