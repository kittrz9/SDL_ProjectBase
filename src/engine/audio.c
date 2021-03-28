#include "audio.h"

#include <SDL2/SDL.h>

Mix_Chunk* sounds[SOUNDS_LENGTH];

void loadSound(enum SOUND_ID sound, SDL_RWops* rw){
	printf("Loading sound %i\n", sound);
	
	sounds[sound] = Mix_LoadWAV_RW(rw, 1);
	
	if(sounds[sound] == NULL) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not load sound: %s\n", SDL_GetError());
		return;
	}
	
	return;
}

void playSound(enum SOUND_ID sound, int loops){
	for(int i = 0; i < AUDIO_CHANNELS_AMOUNT; i++){
		if(Mix_Playing(i) == 0){
			Mix_PlayChannel(i, sounds[sound], loops);
			break;
		}
	}
	
	/*if(Mix_Playing(channel) == 0){
		Mix_PlayChannel(-1, sounds[sound], loops);
	}*/
	
	return;
}
