#include "gameStateRunning.h"

#include "text.h"
#include "entity.h"

int runGameStateRunning(UNUSED SDL_Window* screen, SDL_Renderer* renderer, float deltaTime){
	for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
		// Call the entity's draw function
		(*entListCurrent->ent->draw)(entListCurrent->ent, renderer);
		// Call the entity's update function
		(*entListCurrent->ent->update)(entListCurrent->ent, deltaTime);
	}
	
	// Draw the framerate counter
	// Casting the framerate to an int to get the framerate without any decimals
	sprintf(formatStr, "FPS: %.5f", 1/(deltaTime * 0.001));
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 200;
	rect.h = 50;
	drawText(renderer, formatStr, SDL_Color_White, rect.x, rect.y, 2.0f);
	
	return 0;
}
