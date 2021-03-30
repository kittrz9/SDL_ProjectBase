#include "audio.h"

#include <SDL2/SDL.h>

#include <math.h>

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
	
	return;
}

#define PI 3.141592653589
#define PI2 6.28318530718

// https://gist.github.com/amirrajan/fa6ce9fdc8918e06ca9759c3358e4cd2
// I really need to fix all of this that I messed up lmao, this like barely works
Mix_Chunk* sineWaveSound(float freq, float length){
	// For some reason you have to multiply this by 4 since if you didn't it would only go for a 4th of a second
	size_t size = length * MIX_DEFAULT_FREQUENCY*4;
	float time = 0;
	
	printf("%f\n", freq);
	
	Uint8* audioBuffer = malloc(size * sizeof(Uint8));
	
	for(size_t i = 0; i < size; i++){
		audioBuffer[i] = (Uint8)((128 * sin(time)) + 128);
		
		// Frequency also has to be divided by 8 for some reason to get the actual frequency, idk why
		time += freq/8 * PI2 / MIX_DEFAULT_FREQUENCY;
		if(time >= PI2) { time -= PI2; }
	}
	
	Mix_Chunk* chunk = malloc(sizeof(Mix_Chunk));
	chunk->allocated = 1;
	chunk->abuf = audioBuffer;
	chunk->alen = size;
	chunk->volume = 16;
	
	return chunk;
}
