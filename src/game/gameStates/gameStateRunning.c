#include "gameStateRunning.h"

#include "text.h"
#include "entity.h"
#include "audio.h"
#include "controls.h"

// Could probably change this to an enum
float cMajorScale[] = { 261.6256, 293.6648, 329.6276, 349.2282, 391.9954, 440.0, 493.8833, 523.2511 };
Uint8 scaleIndex = 0;

int runGameStateRunning(UNUSED SDL_Window* screen, SDL_Renderer* renderer, float deltaTime){
	for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
		// Call the entity's draw function
		(*entListCurrent->ent->draw)(entListCurrent->ent, renderer);
		// Call the entity's update function
		(*entListCurrent->ent->update)(entListCurrent->ent, deltaTime);
	}
	
	if(keys[PLAY_SOUND].pressedTimer > 0.0){
		playSound(SOUND_TEST, 0);
		sounds[SOUND_TEST] = createSound(cMajorScale[scaleIndex], 1.0f, synthSquare);
		scaleIndex++;
		if(scaleIndex > sizeof(cMajorScale)/sizeof(float) - 1) {scaleIndex = 0;}
	}
	
	// Draw the framerate counter
	sprintf(formatStr, "FPS: %.5f", (1/(deltaTime/1000)));
	drawText(renderer, formatStr, SDL_Color_White, 0, 0, 2.0f);
	
	return 0;
}
