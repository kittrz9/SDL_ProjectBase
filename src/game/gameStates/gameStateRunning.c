#include "gameStateRunning.h"

#include "text.h"
#include "entity.h"
#include "audio.h"
#include "controls.h"

int runGameStateRunning(UNUSED SDL_Window* screen, SDL_Renderer* renderer, float deltaTime){
	for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
		// Call the entity's draw function
		(*entListCurrent->ent->draw)(entListCurrent->ent, renderer);
		// Call the entity's update function
		(*entListCurrent->ent->update)(entListCurrent->ent, deltaTime);
	}
	
	if(keys[PLAY_SOUND].pressedTimer > 0.0){
		playSound(SOUND_TEST, 0);
	}
	
	// Draw the framerate counter
	sprintf(formatStr, "FPS: %.5f", 1/(deltaTime * 0.001));
	drawText(renderer, formatStr, SDL_Color_White, 0, 0, 2.0f);
	
	return 0;
}
