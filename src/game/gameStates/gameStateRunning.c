#include "gameStateRunning.h"

#include "gameStates.h"
#include "text.h"
#include "entity.h"
#include "audio.h"
#include "controls.h"
#include "player.h"

// Could probably change this to an enum
const float cMajorScale[] = { 261.6256, 293.6648, 329.6276, 349.2282, 391.9954, 440.0, 493.8833, 523.2511 };
Uint8 scaleIndex = 0;
const synthFunc synths[] = { synthSine, synthSquare, synthSaw, synthTriangle, synthNoise };
Uint8 synthIndex = 0;
synthInstrument inst = {
	.envelope = {
		.attack = 0.05f,
		.decay = 0.05f,
		.sustain = 0.2f,
		.release = 0.5f,
	},
	.synth = synthSine,
};

void initGameStateRunning(SDL_Window* window, SDL_Renderer* renderer){
	// Returns a pointer to the player but does nothing with it lmao
	createPlayer(renderer, 50, 50, 100, 100);
}

int runGameStateRunning(UNUSED SDL_Window* screen, SDL_Renderer* renderer, float deltaTime){
	for(entListCurrent = entListHead; entListCurrent != NULL; entListCurrent = entListCurrent->next){
		// Call the entity's draw function
		(*entListCurrent->ent->draw)(entListCurrent->ent, renderer);
		// Call the entity's update function
		(*entListCurrent->ent->update)(entListCurrent->ent, deltaTime);
	}
	
	if(keys[PLAY_SOUND].pressedTimer > 0.0){
		inst.synth = synths[synthIndex];
		synthData data = {
			.startFreq = cMajorScale[scaleIndex],
			.endFreq = 0,
			.volume = 1.0,
			.length = 0.2f,
			.instrument = &inst,
		};
		if(playSynth(&data)) {
			scaleIndex++;
			if(scaleIndex >= sizeof(cMajorScale)/sizeof(float)) { 
				scaleIndex = 0; 
				synthIndex++;
				if(synthIndex >= sizeof(synths)/sizeof(synthFunc)) {
					synthIndex = 0;
				}
			}
		}
	}
	
	if(keys[EXIT].held) {
		running = false;
	}
	
	// Draw the framerate counter
	sprintf(formatStr, "FPS: %.5f", (1/(deltaTime/1000)));
	drawText(renderer, formatStr, SDL_Color_White, 0, 0, 1.0f);
	
	return 0;
}
