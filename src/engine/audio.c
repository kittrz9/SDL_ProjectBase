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

#define PI  3.14159265358
#define PI2 6.28318530718

// https://gist.github.com/amirrajan/fa6ce9fdc8918e06ca9759c3358e4cd2
// I really need to fix all of this that I messed up lmao, this like barely works
Mix_Chunk* sineWaveSound(float freq, float length){
	// For some reason this is just kinda messed up and idk how to fix the length of the sound
	size_t size = length * MIX_DEFAULT_FREQUENCY*8;
	float time = 0;
	
	printf("%f\n", freq);
	
	Uint16* audioBuffer = malloc(size * sizeof(Uint16));
	
	// Really jank way of getting 2^(size/2) since the pow function returns a double instead of an int
	int offset = 1;
	for(size_t i = 1; i < sizeof(audioBuffer[0])*8; i++){
		offset *= 2;
	}
	
	for(size_t i = 0; i < size; i++){
		audioBuffer[i] = (Uint16)((offset*sin(time))+offset);
		
		// Frequency also has to be divided by 8 for some reason to get the actual frequency, idk why
		time += freq/8 * PI2 / MIX_DEFAULT_FREQUENCY;
		if(time >= PI2) { time -= PI2; }
	}
	
	Mix_Chunk* chunk = malloc(sizeof(Mix_Chunk));
	chunk->allocated = 1;
	chunk->abuf = (Uint8*)audioBuffer;
	chunk->alen = size;
	chunk->volume = 16;
	
	return chunk;
}


Mix_Chunk* squareWaveSound(float freq, float length){
	// Really bad repeated code lmao
	size_t size = length * MIX_DEFAULT_FREQUENCY*8;
	float time = 0;
	Uint16* audioBuffer = malloc(size * sizeof(Uint16));
	
	int offset = 1;
	for(size_t i = 1; i < sizeof(Uint16)*8; i++){
		offset *= 2;
	}
	
	for(size_t i = 0; i < size; i++){
		audioBuffer[i] = (Uint16)((offset * (time < PI ? 0 : 1)) + offset);
		
		time += freq/8 * PI2 / MIX_DEFAULT_FREQUENCY;
		if(time >= PI2) { time -= PI2; }
	}
	
	Mix_Chunk* chunk = malloc(sizeof(Mix_Chunk));
	chunk->allocated = 1;
	chunk->abuf = (Uint8*)audioBuffer;
	chunk->alen = size;
	chunk->volume = 16;
	
	return chunk;
}
